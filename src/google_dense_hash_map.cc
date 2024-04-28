#include <inttypes.h>
#include <string>
#include <google/dense_hash_map>

typedef google::dense_hash_map<int64_t, int64_t, std::hash<int64_t>> hash_t;
typedef google::dense_hash_map<std::string, int64_t, std::hash<std::string>> str_hash_t;


#include "hash_map_int_base.h"
#include "hash_map_str_base.h"


#undef HASH_TYPE_INT
#define HASH_TYPE_INT hash_t

#define PREPARE_INT(int_hash)	\
	int_hash.set_empty_key(-1); \
	int_hash.set_deleted_key(-2)

#undef RESERVE_INT
#define RESERVE_INT(int_hash, size) int_hash.resize(size)


#undef HASH_TYPE_STR
#define HASH_TYPE_STR str_hash_t

#define PREPARE_STR(str_hash)	\
	str_hash.set_empty_key(""); \
	str_hash.set_deleted_key("d")

#undef RESERVE_STR
#define RESERVE_STR(str_hash, size) str_hash.resize(size)


#include "template.cc"
