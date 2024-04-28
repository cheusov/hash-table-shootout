#include <inttypes.h>
#include <string>
#include <map>

typedef std::map<int64_t, int64_t> hash_t;
typedef std::map<std::string, int64_t> str_hash_t;

#include "hash_map_int_base.h"
#include "hash_map_str_base.h"

#undef RESERVE_INT
#define RESERVE_INT(int_hash, size)

#undef RESERVE_STR
#define RESERVE_STR(str_hash, size)

#undef LOAD_FACTOR_INT_HASH
#define LOAD_FACTOR_INT_HASH(int_hash) 0.0f

#undef LOAD_FACTOR_STR_HASH
#define LOAD_FACTOR_STR_HASH(str_hash) 0.0f

#include "template.cc"
