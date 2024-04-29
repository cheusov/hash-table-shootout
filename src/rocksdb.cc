#include <string>
#include <iostream>
#include <rocksdb/db.h>
#include <rocksdb/slice.h>
#include <rocksdb/options.h>
#include <stdlib.h>

static std::string kDBPathPrefix = "/tmp/str_rocksdb";

struct str_hash_t {
public:
	static int instance_number;
	rocksdb::DB* db;
	rocksdb::WriteOptions write_options;

private:
	std::string kDBPath;
	rocksdb::Options options;
	std::string rem_db_cmd;

public:
	str_hash_t() {
		kDBPath = kDBPathPrefix + std::to_string(instance_number++);
		rem_db_cmd = std::string("rm -rf ") + kDBPath;

		options.create_if_missing = true;
		options.wal_bytes_per_sync = 0;
		options.max_total_wal_size = 0;
		options.WAL_ttl_seconds = 0;
		options.WAL_size_limit_MB = 0;

		write_options.disableWAL = true;

		db = NULL;
	}

	void initdb() {
		system(rem_db_cmd.c_str());
		rocksdb::Status status = rocksdb::DB::Open(options, kDBPath, &db);
		if (!status.ok()) {
			std::cerr << "Open() failed\n";
			exit(1);
		}
	}

	void clear() {
		delete db;
		system(rem_db_cmd.c_str());
	}
};

int str_hash_t::instance_number = 0;

#define HASH_TYPE_STR str_hash_t

#define CREATE_STR

#define PREPARE_STR(str_hash) str_hash.initdb()

#define RESERVE_STR(str_hash, size)

#define INSERT_STR(str_hash, key, value) \
	if (!str_hash.db->Put(str_hash.write_options, key, std::to_string(value)).ok()){	\
		std::cerr << "Put() failed\n";									\
		exit(1);														\
	}

#define DELETE_STR(str_hash, key) \
	if (!str_hash.db->Delete(str_hash.write_options, key).ok()){\
		std::cerr << "Delete() failed\n";						\
		exit(2);												\
	}

#define FIND_STR_EXISTING(str_hash, key)						\
	if (!str_hash.db->Get(rocksdb::ReadOptions(), key, &s_val).ok()){\
		std::cerr << "error 2\n";								\
		exit(3);												\
	}

#define FIND_STR_MISSING(str_hash, key)							\
	rocksdb::Status status;										\
	if (status = str_hash.db->Get(rocksdb::ReadOptions(), key, &s_val), status.ok()){ \
		std::cerr << "error 4\n";									\
		std::cerr << "status " << status.code() << "\n";			\
		exit(4);													\
	}

#define FIND_STR_EXISTING_COUNT(str_hash, key, count)				\
	if (str_hash.db->Get(rocksdb::ReadOptions(), key, &s_val).ok()){\
		count++;													\
	}

#define LOAD_FACTOR_STR_HASH(str_hash) 0.0f

#define CLEAR_STR(str_hash) str_hash.clear()

#include "template.cc"
