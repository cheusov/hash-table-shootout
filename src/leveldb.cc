#include <inttypes.h>
#include <string>
#include <iostream>
#include <leveldb/db.h>
#include <stdlib.h>

static std::string kDBPath = "/tmp/str_leveldb";

#undef SETUP_STR
#define SETUP_STR \
	static leveldb::DB* str_db;						\
	static leveldb::Options options;				\
	options.create_if_missing = true;				\
	std::string rem_leveldb_cmd = std::string("rm -rf ") + kDBPath;		\
	system(rem_leveldb_cmd.c_str());									\
	leveldb::Status status = leveldb::DB::Open(options, kDBPath, &str_db);	\
	if (!status.ok()) {													\
		std::cerr << "Open() failed\n";									\
		exit(1);														\
	}

#undef RESERVE_STR
#define RESERVE_STR(size)

#undef INSERT_STR
#define INSERT_STR(key, value) \
	if (!str_db->Put(leveldb::WriteOptions(), key, std::to_string(value)).ok()){ \
		std::cerr << "Put() failed\n";									\
		exit(1);														\
	}

#undef DELETE_STR
#define DELETE_STR(key) \
	if (!str_db->Delete(leveldb::WriteOptions(), key).ok()){	\
		std::cerr << "Delete() failed\n";						\
		exit(2);												\
	}

#undef FIND_STR_EXISTING
#define FIND_STR_EXISTING(key)									  \
    if (!str_db->Get(leveldb::ReadOptions(), key, &s_val).ok()){  \
		std::cerr << "error 2\n";								  \
		exit(3);												  \
	}

#undef FIND_STR_MISSING
#define FIND_STR_MISSING(key)										  \
    if (str_db->Get(leveldb::ReadOptions(), key, &s_val).ok()){		  \
		std::cerr << "error 4\n";									  \
		exit(4);													  \
	}

#undef FIND_STR_EXISTING_COUNT
#define FIND_STR_EXISTING_COUNT(key, count)						  \
    if (str_db->Get(leveldb::ReadOptions(), key, &s_val).ok()){	   \
		count++;												   \
	}

#undef ITERATE_INT
#define ITERATE_INT(it)

#undef LOAD_FACTOR_STR_HASH
#define LOAD_FACTOR_STR_HASH(h) 0.0f

#undef CLEAR_STR
#define CLEAR_STR delete str_db; system(rem_leveldb_cmd.c_str());

#include "template.cc"
