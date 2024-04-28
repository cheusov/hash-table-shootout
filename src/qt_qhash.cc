#include <inttypes.h>
#include <functional>
#include <string>

uint qHash(const std::string &key) {
    return std::hash<std::string>()(key);
}

#include <QHash>
typedef QHash<int64_t, int64_t> hash_t;
typedef QHash<std::string, int64_t> str_hash_t;

#include "hash_map_int_base.h"
#include "hash_map_str_base.h"

#undef LOAD_FACTOR_INT_HASH
#define LOAD_FACTOR_INT_HASH(int_hash) 0.0f
#undef INSERT_INT
#define INSERT_INT(int_hash, key, value) int_hash.insert(key, value)
#undef DELETE_INT
#define DELETE_INT(int_hash, key) int_hash.remove(key)
#undef CHECK_INT_ITERATOR_VALUE
#define CHECK_INT_ITERATOR_VALUE(int_hash, iterator, val)	\
	if(iterator != val) { \
		printf("error\n"); \
		exit(3); \
	}
#undef LOAD_FACTOR_STR_HASH
#define LOAD_FACTOR_STR_HASH(int_hash) 0.0f
#undef INSERT_STR
#define INSERT_STR(key, value) str_hash.insert(key, value)
#undef DELETE_STR
#define DELETE_STR(key) str_hash.remove(key);

#include "template.cc"
