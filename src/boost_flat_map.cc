#include <inttypes.h>
#include <string>
#include <boost/container/flat_map.hpp>

typedef boost::container::flat_map<int64_t, int64_t> hash_t;
typedef boost::container::flat_map<std::string, int64_t> str_hash_t;

#include "hash_map_int_base.h"
#include "hash_map_str_base.h"

#undef  LOAD_FACTOR_INT_HASH
#define LOAD_FACTOR_INT_HASH(hash) (double(hash.size())/double(hash.capacity()))
#undef  LOAD_FACTOR_STR_HASH
#define LOAD_FACTOR_STR_HASH(hash) (double(hash.size())/double(hash.capacity()))


#include "template.cc"
