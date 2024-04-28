#include <inttypes.h>
#include <string>
#include <iostream>
#include <leveldb/db.h>
#include <stdlib.h>

static std::string kDBPath = "/tmp/str_leveldb";

#undef HASH_TYPE_STR
#define HASH_TYPE_STR leveldb::DB*

#define CREATE_STR(str_hash)

#define PREPARE_STR(str_hash)						\
	static leveldb::Options options;				\
	options.create_if_missing = true;				\
	std::string rem_leveldb_cmd = std::string("rm -rf ") + kDBPath;		\
	system(rem_leveldb_cmd.c_str());										\
	leveldb::Status status = leveldb::DB::Open(options, kDBPath, &str_hash);	\
	if (!status.ok()) {													\
		std::cerr << "Open() failed\n";									\
		exit(1);															\
	}

#undef RESERVE_STR
#define RESERVE_STR(str_hash, size)

#undef INSERT_STR
#define INSERT_STR(str_hash, key, value) \
	if (!str_hash->Put(leveldb::WriteOptions(), key, std::to_string(value)).ok()){ \
		std::cerr << "Put() failed\n";									\
		exit(1);														\
	}

#undef DELETE_STR
#define DELETE_STR(str_hash, key) \
	if (!str_hash->Delete(leveldb::WriteOptions(), key).ok()){	\
		std::cerr << "Delete() failed\n";						\
		exit(2);												\
	}

#undef FIND_STR_EXISTING
#define FIND_STR_EXISTING(str_hash, key)						  \
	if (!str_hash->Get(leveldb::ReadOptions(), key, &s_val).ok()){  \
		std::cerr << "error 2\n";								  \
		exit(3);												  \
	}

#undef FIND_STR_MISSING
#define FIND_STR_MISSING(str_hash, key)							\
	if (str_hash->Get(leveldb::ReadOptions(), key, &s_val).ok()){	\
		std::cerr << "error 4\n";									\
		exit(4);													\
	}

#undef FIND_STR_EXISTING_COUNT
#define FIND_STR_EXISTING_COUNT(str_hash, key, count)				   \
	if (str_hash->Get(leveldb::ReadOptions(), key, &s_val).ok()){	   \
		count++;												   \
	}

#undef LOAD_FACTOR_STR_HASH
#define LOAD_FACTOR_STR_HASH(str_hash) 0.0f

#undef CLEAR_STR
#define CLEAR_STR(str_hash) delete str_hash; system(rem_leveldb_cmd.c_str());

#include "template.cc"
