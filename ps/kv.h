#include <unordered_map>
#include <string>

namespace ps {

/**
 * @brief KVstore is a distributed kv map
 */

template<typename KEY, typename VAL>
class KVstore {
public:
  VAL get(const KEY &key) const {
    if (_store.find(key) != _store.end()) {
      return _store[key];
    }
    return VAL();
  }

  void set(const KEY &key, const VAL &val) {
    _store[key] = val;
  }

  size_t Size() { return _store.size(); } 

  bool OptimizerTraverse();
  bool Snapshot(const std::string fname);

private:
  std::unordered_map<KEY, VAL> _store;
};
}
