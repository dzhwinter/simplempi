#pragma once
#include <memory>
#include <typeindex>
#include <vector>

#include "arena.h"
#include "macros.h"
#include "place.h"

namespace ps {

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
   * @brief allocate the real memory
   */
  template <typename T>
  void mutable_data(const std::vector<int>& shape, Place place) {
    Resize(shape);
    mutable_data<T>(place);
  }
  template <typename T>
  void mutable_data(Place place) {}

private:
  /**
   * @brief Placeholder reference to a block of consecutive memory.
   */
  struct Placeholder {
    virtual ~Placeholder();
    virtual Place place() const = 0;
    virtual size_t size() const = 0;
    virtual void* ptr() const = 0;
    virtual std::type_index type() const = 0;
  };
  template <typename Place>
  class PlaceholderImpl : public Placeholder {
  public:
    PlaceholderImpl(size_t size, Place place, std::type_index t)
        : size_(size),
          place_(place),
          type_(t),
          ptr_(static_cast<uint8_t*>(Alloc<Place>(size)), PoDDeleter<Place>()) {
    }
    ~PlaceholderImpl() { size_ = 0; }
    Place place() { return place_; }
    size_t size() { return size_; }
    void* ptr() { return reinterpret_cast<void*>(ptr_.get()); }
    std::type_index type() { return type_; }

  private:
    Place place_;
    size_t size_;
    std::type_index type_;
    std::unique_ptr<uint8_t> ptr_;
  };
  std::vector<int> shape_;
  std::shared_ptr<Placeholder> holder_;
  DISABLE_ASSIGN_AND_COPY(Tensor);
};
}
