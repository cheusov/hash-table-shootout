#define SETUP_INT hash_t int_hash;
#define RESERVE_INT(size) int_hash.reserve(size)
#define LOAD_FACTOR_INT_HASH(hash) int_hash.load_factor()
#define INSERT_INT(key, value) int_hash.insert(hash_t::value_type(key, value))
#define DELETE_INT(key) int_hash.erase(key)
#define FIND_INT_EXISTING(key) if(int_hash.find(key) == int_hash.end()) { printf("error"); exit(1); }
#define FIND_INT_MISSING(key) if(int_hash.find(key) != int_hash.end()) { printf("error"); exit(1); }
#define FIND_INT_EXISTING_COUNT(key, count) if(int_hash.find(key) != int_hash.end()) { count++; }
#define CHECK_INT_ITERATOR_VALUE(iterator, value) if(iterator.second != value) { printf("error"); exit(1); }
#define CLEAR_INT
