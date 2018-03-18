#pragma once
#include <memory>
#include <typeindex>
#include <vector>

#include "arena.h"
#include "macros.h"
#include "place.h"

namespace ps {

class Tensor;

void TensorCopy(const Tensor& src, Place place, Tensor* dst);

class Tensor {
public:
  Tensor() : holder_(nullptr) {}
  Tensor(const std::vector<int>& shape) : shape_(shape), holder_(nullptr) {}

  /**
   * @brief resize the tensor shape. must be called before allocating.
   */
  void Resize(const std::vector<int>& shape) {
    shape_.reserve(shape.size());
    for (auto& w : shape) {
      shape_.push_back(w);
    }
  }
  /**
   * @brief return tensor description information
   */
  std::vector<int> Shape() const { return shape_; }
  std::type_index Type() const {
    CHECK(holder_ != nullptr) << "Uninit Tensor.";
    return holder_->type();
  }
  Place place() const {
    CHECK(holder_ != nullptr) << "Uninit Tensor.";
    return holder_->place();
  }
  /**
   * @brief allocate the real memory
   */
  template <typename T>
  T* mutable_data(const std::vector<int>& shape, Place place) {
    Resize(shape);
    return this->mutable_data<T>(place);
  }
  template <typename T>
  T* mutable_data(Place place) {
    std::type_index type(typeid(T));
    this->mutable_data(place, type);
    CHECK(holder_ != nullptr) << "UnInit Tensor.";
    return static_cast<T*>(holder_.get());
  }
  /**
   * @brief mutable_data without template type
   */
  void mutable_data(Place place, std::type_index type) {
    CHECK(shape_.size() != 0UL) << "Please Call Resize First.";
    size_t size = 1UL;
    for (auto& i : shape_) {
      size *= i;
    }
    if (is_gpu_place(place)) {
      holder_.reset(new PlaceholderImpl<GPUPlace>(
          size * SizeofType(type), boost::get<GPUPlace>(place), type));
    } else if (is_cpu_place(place)) {
      holder_.reset(new PlaceholderImpl<CPUPlace>(
          size * SizeofType(type), boost::get<CPUPlace>(place), type));
    } else {
      // TODO(dzhwinter): throw exception
    }
  }
  /**
   * @brief return the data pointer
   */
  template <typename T>
  T* data() const {
    CHECK(holder_ != nullptr) << "UnInit Tensor.";
    return static_cast<T*>(holder_.get());
  }
  template <typename T>
  T* data() {
    CHECK(holder_ != nullptr) << "UnInit Tensor.";
    return static_cast<T*>(holder_.get());
  }

  size_t size() { return holder_->capacity() / SizeofType(holder_->type()); }
  size_t capacity() { return holder_->capacity(); }

private:
  /**
   * @brief Placeholder reference to a block of consecutive memory.
   */
  struct Placeholder {
    virtual Place place() const = 0;
    virtual size_t capacity() const = 0;
    virtual void* ptr() = 0;
    virtual std::type_index type() const = 0;
  };
  template <typename Place>
  class PlaceholderImpl : public Placeholder {
  public:
    PlaceholderImpl(size_t size, Place place, std::type_index t)
        : capacity_(size),
          place_(place),
          type_(t),
          ptr_(static_cast<uint8_t*>(Alloc<Place>(size)), PoDDeleter<Place>()) {
    }
    ~PlaceholderImpl() { capacity_ = 0; }
    ps::Place place() const { return place_; }
    size_t capacity() const { return capacity_; }
    void* ptr() { return reinterpret_cast<void*>(ptr_.get()); }
    std::type_index type() const { return type_; }

  private:
    ps::Place place_;
    size_t capacity_;
    std::type_index type_;
    std::unique_ptr<uint8_t> ptr_;
  };
  std::vector<int> shape_;
  std::shared_ptr<Placeholder> holder_;
  DISABLE_ASSIGN_AND_COPY(Tensor);
};
}
