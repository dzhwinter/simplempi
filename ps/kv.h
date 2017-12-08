#include <unordered_map>

namespace ps {

/**
 * @brief KVstore is a distributed kv map
 */

template<typename KEY, typename VAL>
class KVstore {
public:
private:
  std::unordered_map<KEY, VAL> _store;
};
}
