#include <inttypes.h>
#include <string>
#include <tsl/robin_map.h>

typedef tsl::robin_map<int64_t, int64_t, std::hash<int64_t>> hash_t;
typedef tsl::robin_map<std::string, int64_t, std::hash<std::string>> str_hash_t;

#include "hash_map_int_base.h"
#include "hash_map_str_base.h"

#undef SETUP_INT
#define SETUP_INT(int_hash) hash_t int_hash; int_hash.max_load_factor(0.9f);

#undef SETUP_STR
#define SETUP_STR str_hash_t str_hash; str_hash.max_load_factor(0.9f);

#include "template.cc"
