#include <inttypes.h>
#include <string>
#include <map>

typedef std::map<int64_t, int64_t> hash_t;
typedef std::map<std::string, int64_t> str_hash_t;

#include "hash_map_int_base.h"
#include "hash_map_str_base.h"

#undef RESERVE_INT
#define RESERVE_INT(size)

#undef RESERVE_STR
#define RESERVE_STR(size)

#undef LOAD_FACTOR_INT_HASH
#define LOAD_FACTOR_INT_HASH(h) 0.0f

#undef LOAD_FACTOR_STR_HASH
#define LOAD_FACTOR_STR_HASH(h) 0.0f

#include "template.cc"
