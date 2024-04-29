#include <string>
#include <kchashdb.h>
#include <stdlib.h>

template <typename DBType>
struct str_hash_t {
public:
	static int instance_number;
	DBType db;

private:
	std::string kDBPath;
	std::string rem_db_cmd;

public:
	str_hash_t() {
	}

	void initdb(std::string db_path_prefix) {
		system(rem_db_cmd.c_str());
		auto options = kyotocabinet::HashDB::OWRITER | kyotocabinet::HashDB::OCREATE;
		kDBPath = db_path_prefix + std::to_string(instance_number++);
		rem_db_cmd = std::string("rm -rf ") + kDBPath;
		auto status = db.open(kDBPath, options);
		if (!status) {
			std::cerr << "Open() failed\n";
			exit(1);
		}
	}

	void clear() {
		db.close();
		system(rem_db_cmd.c_str());
	}
};

template <typename DBType>
int str_hash_t<DBType>::instance_number = 0;

#define RESERVE_STR(str_hash, size)

#define INSERT_STR(str_hash, key, value) str_hash.db.set(key, std::to_string(value))

#define DELETE_STR(str_hash, key) str_hash.db.remove(key)

#define FIND_STR_EXISTING(str_hash, key)			\
	{												\
		std::string s_val;							\
		if(!str_hash.db.get(key, &s_val)) {		\
			std::cerr << "error 2\n";				\
			exit(2);								\
		}											\
	}

#define FIND_STR_MISSING(str_hash, key)			\
	if(str_hash.db.get(key, &s_val)) {				\
		std::cerr << "error 4\n";					\
		exit(4);									\
	}

#define FIND_STR_EXISTING_COUNT(str_hash, key, count)	\
	if(str_hash.db.get(key, &s_val)) {					\
		count++;										\
	}

#define LOAD_FACTOR_STR_HASH(str_hash) 0.0f

#define CLEAR_STR(str_hash) str_hash.clear();
