#include <inttypes.h>
#include <string>
#include <google/sparse_hash_map>

typedef google::sparse_hash_map<int64_t, int64_t, std::hash<int64_t>> hash_t;
typedef google::sparse_hash_map<std::string, int64_t, std::hash<std::string>> str_hash_t;

#include "hash_map_int_base.h"
#include "hash_map_str_base.h"

#undef SETUP_INT
#define SETUP_INT(int_hash) hash_t int_hash; int_hash.set_deleted_key(-1);

#undef RESERVE_INT
#define RESERVE_INT(int_hash, size) int_hash.resize(size)

#undef SETUP_STR
#define SETUP_STR str_hash_t str_hash; str_hash.set_deleted_key("");

#undef RESERVE_STR
#define RESERVE_STR(size) str_hash.resize(size)

#include "template.cc"
