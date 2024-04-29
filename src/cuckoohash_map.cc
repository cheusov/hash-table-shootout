#include <inttypes.h>
#include <string>
#include <libcuckoo/cuckoohash_map.hh>

typedef libcuckoo::cuckoohash_map<int64_t, int64_t, std::hash<int64_t>> hash_t;
typedef libcuckoo::cuckoohash_map<std::string, int64_t, std::hash<std::string>> str_hash_t;

#include "hash_map_int_base.h"
#include "hash_map_str_base.h"



#undef HASH_TYPE_STR
#define HASH_TYPE_STR str_hash_t

#undef FIND_STR_EXISTING
#define FIND_STR_EXISTING(str_hash, key) if(!str_hash.find(key)) { printf("error"); exit(1); }

#undef FIND_STR_MISSING
#define FIND_STR_MISSING(str_hash, key) if(str_hash.find(key)) { printf("error"); exit(1); }

#undef FIND_STR_EXISTING_COUNT
#define FIND_STR_EXISTING_COUNT(str_hash, key, count) if(str_hash.find(key)) { count++; }

#undef CREATE_STR
#define CREATE_STR

#undef INSERT_STR
#define INSERT_STR(str_hash, key, value) str_hash.insert(key, value);

#define ITERATE_STR(str_hash, it) for (const auto& it : str_hash.lock_table())

//#undef CHECK_STR_ITERATOR_VALUE
//#define CHECK_STR_ITERATOR_VALUE(str_hash, iterator, value)



#undef HASH_TYPE_INT
#define HASH_TYPE_INT hash_t

#undef FIND_INT_EXISTING
#define FIND_INT_EXISTING(int_hash, key) if(!int_hash.find(key)) { printf("error"); exit(1); }

#undef FIND_INT_MISSING
#define FIND_INT_MISSING(int_hash, key) if(int_hash.find(key)) { printf("error"); exit(1); }

#undef FIND_INT_EXISTING_COUNT
#define FIND_INT_EXISTING_COUNT(int_hash, key, count) if(int_hash.find(key)) { count++; }

#undef CREATE_INT
#define CREATE_INT

#undef INSERT_INT
#define INSERT_INT(int_hash, key, value) int_hash.insert(key, value);

#define ITERATE_INT(int_hash, it) for (const auto& it : int_hash.lock_table())

#undef CHECK_INT_ITERATOR_VALUE
#define CHECK_INT_ITERATOR_VALUE(int_hash, iterator, value)



#include "template.cc"
