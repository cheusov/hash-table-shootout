#define HASH_TYPE_STR str_hash_t
#define CREATE_STR(str_hash)
#define RESERVE_STR(str_hash, size) \
	str_hash.reserve(size);
#define LOAD_FACTOR_STR_HASH(str_hash) \
	str_hash.load_factor()
#define INSERT_STR(str_hash, key, value) \
	str_hash.insert(str_hash_t::value_type(key, value));
#define DELETE_STR(str_hash, key) \
	str_hash.erase(key);
#define FIND_STR_EXISTING(str_hash, key) \
	if(str_hash.find(key) == str_hash.end()) { \
		std::cerr << "error\n"; \
		exit(4); \
	}
#define FIND_STR_MISSING(str_hash, key) \
	if(str_hash.find(key) != str_hash.end()) { \
		std::cerr << "error\n"; \
		exit(5); \
	}
#define FIND_STR_EXISTING_COUNT(str_hash, key, count) \
	if(str_hash.find(key) != str_hash.end()) { \
		count++; \
	}
#define CLEAR_STR(str_hash)
