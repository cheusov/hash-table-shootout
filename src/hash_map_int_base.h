#define SETUP_INT(int_hash) hash_t int_hash;
#define RESERVE_INT(int_hash, size) int_hash.reserve(size)
#define LOAD_FACTOR_INT_HASH(int_hash) int_hash.load_factor()
#define INSERT_INT(int_hash, key, value) int_hash.insert(hash_t::value_type(key, value))
#define DELETE_INT(int_hash, key) int_hash.erase(key)
#define FIND_INT_EXISTING(int_hash, key) if(int_hash.find(key) == int_hash.end()) { printf("error"); exit(1); }
#define FIND_INT_MISSING(int_hash, key) if(int_hash.find(key) != int_hash.end()) { printf("error"); exit(1); }
#define FIND_INT_EXISTING_COUNT(int_hash, key, count) if(int_hash.find(key) != int_hash.end()) { count++; }
#define CHECK_INT_ITERATOR_VALUE(int_hash, iterator, value) if(iterator.second != value) { printf("error"); exit(1); }
#define CLEAR_INT(int_hash)
