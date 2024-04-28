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

typedef std::unordered_map<int64_t, int64_t> hash_t;
typedef tsl::array_map<char, int64_t, str_hash<char>> str_hash_t;

#include "hash_map_str_base.h"

#undef INSERT_STR
#define INSERT_STR(str_hash, key, value) str_hash.insert(key, value)

#include "template.cc"
