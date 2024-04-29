#include <inttypes.h>
#include <string>
#include <kcstashdb.h>
#include <stdlib.h>

typedef kyotocabinet::StashDB hash_t;
typedef kyotocabinet::StashDB str_hash_t;

static std::string dbpath = "/tmp/str_kyotocabinet_stash.dat";
static std::string rem_kyotodb_stash_cmd = std::string("rm -rf ") + dbpath;

#undef HASH_TYPE_STR
#define HASH_TYPE_STR str_hash_t

#undef CREATE_STR
#define CREATE_STR(str_hash)

#define PREPARE_STR(str_hash)											\
	system(rem_kyotodb_stash_cmd.c_str());								\
	if (!str_hash.open(dbpath, str_hash_t::OWRITER | str_hash_t::OCREATE)){	\
		std::cerr << "error 6\n";										\
		exit(1);														\
	}

#undef RESERVE_STR
#define RESERVE_STR(str_hash, size)

#undef INSERT_STR
#define INSERT_STR(str_hash, key, value) str_hash.set(key, std::to_string(value))

#undef DELETE_STR
#define DELETE_STR(str_hash, key) str_hash.remove(key)

#undef FIND_STR_EXISTING
#define FIND_STR_EXISTING(str_hash, key)			\
	{												\
		std::string s_val;							\
		if(!str_hash.get(key, &s_val)) {			\
			printf("error\n");						\
			exit(1);								\
		}											\
	}

#undef FIND_STR_MISSING
#define FIND_STR_MISSING(str_hash, key)			\
	if(str_hash.get(key, &s_val)) {				\
		printf("error\n");							\
		exit(1);									\
	}

#undef FIND_STR_EXISTING_COUNT
#define FIND_STR_EXISTING_COUNT(str_hash, key, count)	\
	if(str_hash.get(key, &s_val)) {					\
		count++;										\
	}

#undef LOAD_FACTOR_STR_HASH
#define LOAD_FACTOR_STR_HASH(str_hash) 0.0f

#undef CLEAR_STR
#define CLEAR_STR(str_hash) str_hash.close(); system(rem_kyotodb_stash_cmd.c_str());

#include "template.cc"
