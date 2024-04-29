#include <string>
#include <iostream>
#include <leveldb/db.h>
#include <stdlib.h>

static const std::string kDBPathPrefix = "/tmp/str_leveldb";

struct str_hash_t {
public:
	static int instance_number;
	leveldb::DB* db;

private:
	std::string kDBPath;
	leveldb::Options options;
	std::string rem_leveldb_cmd;

public:
	str_hash_t() {
		kDBPath = kDBPathPrefix + std::to_string(instance_number++);
		rem_leveldb_cmd = std::string("rm -rf ") + kDBPath;
		options.create_if_missing = true;
		db = NULL;
	}

	void initdb() {
		system(rem_leveldb_cmd.c_str());
		leveldb::Status status = leveldb::DB::Open(options, kDBPath, &db);
		if (!status.ok()) {
			std::cerr << "Open() failed\n";
			exit(1);
		}
	}

	void clear() {
		delete db;
		system(rem_leveldb_cmd.c_str());
	}
};

int str_hash_t::instance_number = 0;

#define HASH_TYPE_STR str_hash_t

#define CREATE_STR

#define PREPARE_STR(str_hash) str_hash.initdb()

#define RESERVE_STR(str_hash, size)

#define INSERT_STR(str_hash, key, value) \
	if (!str_hash.db->Put(leveldb::WriteOptions(), key, std::to_string(value)).ok()){ \
		std::cerr << "Put() failed\n";									\
		exit(1);														\
	}

#define DELETE_STR(str_hash, key) \
	if (!str_hash.db->Delete(leveldb::WriteOptions(), key).ok()){	\
		std::cerr << "Delete() failed\n";						\
		exit(2);												\
	}

#define FIND_STR_EXISTING(str_hash, key)						  \
	if (!str_hash.db->Get(leveldb::ReadOptions(), key, &s_val).ok()){  \
		std::cerr << "error 2\n";								  \
		exit(3);												  \
	}

#define FIND_STR_MISSING(str_hash, key)							\
	if (str_hash.db->Get(leveldb::ReadOptions(), key, &s_val).ok()){	\
		std::cerr << "error 4\n";									\
		exit(4);													\
	}

#define FIND_STR_EXISTING_COUNT(str_hash, key, count)				\
	if (str_hash.db->Get(leveldb::ReadOptions(), key, &s_val).ok()){\
		count++;													\
	}

#define LOAD_FACTOR_STR_HASH(str_hash) 0.0f

#define CLEAR_STR(str_hash) str_hash.clear()

#include "template.cc"
