#include "kv.h"

namespace ps {

#ifndef MY_ALGO

template<typename KEY, typename VAL>
bool KVstore<KEY, VAL>::OptimizerTraverse() {}

#endif

#ifndef MY_SAVER

template<typename KEY, typename VAL>
bool KVstore<KEY, VAL>::Snapshot(const std::string fname) {}

#endif

}
