#include <inttypes.h>
#include <string>
#include <iostream>
#include <rocksdb/db.h>
#include <rocksdb/slice.h>
#include <rocksdb/options.h>
#include <stdlib.h>

static std::string kDBPath = "/tmp/str_rocksdb";

#undef HASH_TYPE_STR
#define HASH_TYPE_STR rocksdb::DB*

#undef CREATE_STR
#define CREATE_STR

#define PREPARE_STR(str_hash)						\
	static rocksdb::Options options;				\
	options.create_if_missing = true;				\
	options.wal_bytes_per_sync = 0;				\
	options.max_total_wal_size = 0;									\
	options.WAL_ttl_seconds = 0;										\
	options.WAL_size_limit_MB = 0;										\
	static rocksdb::WriteOptions write_options;						\
	write_options.disableWAL = true;									\
	std::string rem_rocksdb_cmd = std::string("rm -rf ") + kDBPath;	\
	system(rem_rocksdb_cmd.c_str());									\
	rocksdb::Status status = rocksdb::DB::Open(options, kDBPath, &str_hash); \
	if (!status.ok()) {												\
		std::cerr << "Open() failed\n";								\
		exit(1);														\
	}

#undef RESERVE_STR
#define RESERVE_STR(str_hash, size)

#undef INSERT_STR
#define INSERT_STR(str_hash, key, value) \
	if (!str_hash->Put(write_options, key, std::to_string(value)).ok()){	\
		std::cerr << "Put() failed\n";									\
		exit(1);														\
	}

#undef DELETE_STR
#define DELETE_STR(str_hash, key) \
	if (!str_hash->Delete(write_options, key).ok()){				\
		std::cerr << "Delete() failed\n";						\
		exit(2);												\
	}

#undef FIND_STR_EXISTING
#define FIND_STR_EXISTING(str_hash, key)						\
	if (!str_hash->Get(rocksdb::ReadOptions(), key, &s_val).ok()){\
		std::cerr << "error 2\n";								\
		exit(3);												\
	}

#undef FIND_STR_MISSING
#define FIND_STR_MISSING(str_hash, key)							\
	rocksdb::Status status;										\
	if (status = str_hash->Get(rocksdb::ReadOptions(), key, &s_val), status.ok()){ \
		std::cerr << "error 4\n";									\
		std::cerr << "status " << status.code() << "\n";			\
		exit(4);													\
	}

#undef FIND_STR_EXISTING_COUNT
#define FIND_STR_EXISTING_COUNT(str_hash, key, count)				\
	if (str_hash->Get(rocksdb::ReadOptions(), key, &s_val).ok()){	\
		count++;													\
	}

#undef LOAD_FACTOR_STR_HASH
#define LOAD_FACTOR_STR_HASH(str_hash) 0.0f

#undef CLEAR_STR
#define CLEAR_STR(str_hash) delete str_hash; system(rem_rocksdb_cmd.c_str());

#include "template.cc"
