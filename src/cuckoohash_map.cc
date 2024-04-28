#include <inttypes.h>
#include <string>
#include <libcuckoo/cuckoohash_map.hh>

typedef libcuckoo::cuckoohash_map<int64_t, int64_t, std::hash<int64_t>> hash_t;
typedef libcuckoo::cuckoohash_map<std::string, int64_t, std::hash<std::string>> str_hash_t;

#include "hash_map_int_base.h"
#include "hash_map_str_base.h"


#undef HASH_TYPE_STR
#define HASH_TYPE_STR str_hash_t::locked_table

#undef CREATE_STR
#define CREATE_STR(str_hash) \
	(new str_hash_t())->lock_table() // I know there is a memory leak here

#undef INSERT_STR
#define INSERT_STR(str_hash, key, value) \
  str_hash.insert(key, value);


#undef HASH_TYPE_INT
#define HASH_TYPE_INT hash_t::locked_table

#undef CREATE_INT
#define CREATE_INT(int_hash) \
	(new hash_t())->lock_table() // I know there is a memory leak here

#undef INSERT_INT
#define INSERT_INT(int_hash, key, value)\
  int_hash.insert(key, value);

#undef CHECK_INT_ITERATOR_VALUE
#define CHECK_INT_ITERATOR_VALUE(int_hash, iterator, value)


#include "template.cc"
