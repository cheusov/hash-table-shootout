#include <inttypes.h>
#include <string>
#include <include/tsl/hopscotch_map.h>

typedef tsl::hopscotch_map<int64_t, int64_t, std::hash<int64_t>> hash_t;
typedef tsl::hopscotch_map<std::string, int64_t, std::hash<std::string>> str_hash_t;

#include "hash_map_int_base.h"
#include "hash_map_str_base.h"

#undef SETUP
#define SETUP \
	hash_t int_hash; int_hash.max_load_factor(0.5f); \
	str_hash_t str_hash; str_hash.max_load_factor(0.5f);

#include "template.cc"
