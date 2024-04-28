#include <inttypes.h>
#include <string>
#include <kchashdb.h>
#include <stdlib.h>

typedef kyotocabinet::HashDB hash_t;
typedef kyotocabinet::HashDB str_hash_t;

static std::string dbpath = "/tmp/str_kyotocabinet_hash.dat";
static std::string rem_kyotodb_hash_cmd = std::string("rm -rf ") + dbpath;

#undef HASH_TYPE_INT
#define HASH_TYPE_INT hash_t

#undef CREATE_INT
#define CREATE_INT(int_hash)

#define PREPARE_INT(int_hash)											\
	system(rem_kyotodb_hash_cmd.c_str());								\
	if (!int_hash.open(dbpath, hash_t::OWRITER | hash_t::OCREATE)){	\
		std::cerr << "error 5\n";										\
		exit(1);														\
	}

#undef HASH_TYPE_STR
#define HASH_TYPE_STR str_hash_t

#undef CREATE_STR
#define CREATE_STR(str_hash)

#define PREPARE_STR(str_hash)											\
	system(rem_kyotodb_hash_cmd.c_str());								\
	if (!str_hash.open(dbpath, str_hash_t::OWRITER | str_hash_t::OCREATE)){	\
		std::cerr << "error 6\n";										\
		exit(1);														\
	}

#undef RESERVE_INT
#define RESERVE_INT(int_hash, size)

#undef RESERVE_STR
#define RESERVE_STR(str_hash, size)

#undef INSERT_INT
#define INSERT_INT(int_hash, key, value) \
	int_hash.set(std::to_string(key), std::to_string(value))

#undef INSERT_STR
#define INSERT_STR(str_hash, key, value) \
	str_hash.set(key, std::to_string(value))

#undef DELETE_INT
#define DELETE_INT(int_hash, key) \
	int_hash.remove(std::to_string(key))

#undef DELETE_STR
#define DELETE_STR(str_hash, key) str_hash.remove(key)

#undef FIND_INT_EXISTING
#define FIND_INT_EXISTING(int_hash, key)			 \
	{												 \
		std::string s_val;							 \
		if(!int_hash.get(std::to_string(key), &s_val)) { \
			std::cerr << "error 1\n";				 \
			exit(1);								 \
		}											 \
	}

#undef FIND_STR_EXISTING
#define FIND_STR_EXISTING(str_hash, key)			\
	{												\
		std::string s_val;							\
		if(!str_hash.get(key, &s_val)) {			\
			std::cerr << "error 2\n";				\
			exit(2);								\
		}											\
	}

#undef FIND_INT_MISSING
#define FIND_INT_MISSING(int_hash, key)			\
	{												\
		std::string s_val;							\
		if(int_hash.get(std::to_string(key), &s_val)) { \
			std::cerr << "error 3\n";				\
			exit(3);								\
		}											\
	}

#undef FIND_STR_MISSING
#define FIND_STR_MISSING(str_hash, key)			\
	if(str_hash.get(key, &s_val)) {				\
		std::cerr << "error 4\n";					\
		exit(4);									\
	}

#undef FIND_INT_EXISTING_COUNT
#define FIND_INT_EXISTING_COUNT(int_hash, key, count)	\
	if(int_hash.get(std::to_string(key), &s_val)) {	\
		count++;									\
	}

#undef FIND_STR_EXISTING_COUNT
#define FIND_STR_EXISTING_COUNT(str_hash, key, count)	\
	if(str_hash.get(key, &s_val)) {					\
		count++;									\
	}

#undef ITERATE_INT
#define ITERATE_INT(int_hash, it)

#undef CHECK_INT_ITERATOR_VALUE
#define CHECK_INT_ITERATOR_VALUE(int_hash, it, value)

#undef LOAD_FACTOR_INT_HASH
#define LOAD_FACTOR_INT_HASH(int_hash) 0.0f

#undef LOAD_FACTOR_STR_HASH
#define LOAD_FACTOR_STR_HASH(str_hash) 0.0f

#undef CLEAR_INT
#define CLEAR_INT(int_hash) int_hash.close(); system(rem_kyotodb_hash_cmd.c_str())

#undef CLEAR_STR
#define CLEAR_STR(str_hash) str_hash.close(); system(rem_kyotodb_hash_cmd.c_str())

#include "template.cc"
