#include <inttypes.h>
#include <string>
#include <unordered_map>
#include <tsl/array_map.h>

#include <experimental/string_view>
template<class CharT>
struct str_hash {
	std::size_t operator()(const CharT* key, std::size_t key_size) const {
		return std::hash<std::experimental::string_view>()(std::experimental::string_view(key, key_size));
	}
};

typedef tsl::array_map<char, int64_t, str_hash<char>> str_hash_t;

#include "hash_map_str_base.h"

#undef HASH_TYPE_STR
#define HASH_TYPE_STR str_hash_t

#define PREPARE_STR(str_hash) str_hash.max_load_factor(1.0f)

#undef INSERT_STR
#define INSERT_STR(str_hash, key, value) str_hash.insert(key, value)

#include "template.cc"
