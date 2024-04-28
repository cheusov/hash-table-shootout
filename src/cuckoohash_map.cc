#include <inttypes.h>
#include <string>
#include <libcuckoo/cuckoohash_map.hh>

typedef libcuckoo::cuckoohash_map<int64_t, int64_t, std::hash<int64_t>> hash_t;
typedef libcuckoo::cuckoohash_map<std::string, int64_t, std::hash<std::string>> str_hash_t;

#include "hash_map_int_base.h"
#include "hash_map_str_base.h"

#undef SETUP_STR
#define SETUP_STR(str_hash)			\
	str_hash_t mt_str_hash; \
	str_hash_t::locked_table str_hash = mt_str_hash.lock_table();

#undef SETUP_INT
#define SETUP_INT(int_hash)  \
  hash_t mt_int_hash; \
  hash_t::locked_table int_hash = mt_int_hash.lock_table()

#undef INSERT_INT
#define INSERT_INT(int_hash, key, value)\
  int_hash.insert(key, value);

#undef CHECK_INT_ITERATOR_VALUE
#define CHECK_INT_ITERATOR_VALUE(int_hash, iterator, value)

#undef INSERT_STR
#define INSERT_STR(str_hash, key, value) \
  str_hash.insert(key, value);

#include "template.cc"
