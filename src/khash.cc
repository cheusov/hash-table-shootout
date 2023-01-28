#include <khash.h>
#include <stdint.h>

#define __UNCONST(p) ((void *)((char*)NULL+((const char*)p-(const char*)NULL)))

static kh_inline khint_t murmur_hash2(const char *key);

KHASH_MAP_INIT_INT64(kh64, int64_t)

// A performance of default khash hash function is extreamly bad!
// That's why we use murmur_hash2 implementation here
// KHASH_MAP_INIT_STR(khstr, int64_t)
KHASH_INIT(khstr, kh_cstr_t, int64_t, 1, murmur_hash2, kh_str_hash_equal)

static kh_inline khint_t murmur_hash2(const char *key)
{
	const uint32_t m = 0x5bd1e995;
	const uint32_t seed = 0;
	const int r = 24;
	size_t len = strlen(key);

	uint32_t h = seed ^ len;

	const unsigned char * data = (const unsigned char *)key;
	uint32_t k;

	while (len >= 4){
		k  = data[0];
		k |= data[1] << 8;
		k |= data[2] << 16;
		k |= data[3] << 24;

		k *= m;
		k ^= k >> r;
		k *= m;

		h *= m;
		h ^= k;

		data += 4;
		len -= 4;
	}

	switch (len)
	{
		case 3:
			h ^= data[2] << 16;
		case 2:
			h ^= data[1] << 8;
		case 1:
			h ^= data[0];
			h *= m;
	};

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}

#define SETUP_INT khash_t(kh64) *hash = kh_init(kh64);
#define SETUP_STR khash_t(khstr) *str_hash = kh_init(khstr);

#define RESERVE_INT(n) \
	kh_resize(kh64, hash, (khint_t)(n / __ac_HASH_UPPER + 1));
#define RESERVE_STR(n) \
	kh_resize(khstr, str_hash, (khint_t)(n / __ac_HASH_UPPER + 1));
#define INSERT_INT(key, value)											\
	int r;																\
	khint_t k = kh_put(kh64, hash, key, &r);							\
	if (r > 0) {														\
		kh_value(hash, k) = value;										\
	}
#define INSERT_STR(key, value)											\
	int r;																\
	char *istr = strdup(key.c_str());									\
	khint_t k = kh_put(khstr, str_hash, istr, &r);						\
	if (r > 0) {														\
		kh_value(str_hash, k) = value;									\
	} else																\
		free(istr);
#define DELETE_INT(key)							\
	khint_t k = kh_get(kh64, hash, key);		\
	if (k != kh_end(hash))						\
		kh_del(kh64, hash, k);
#define DELETE_STR(key)													\
	khint_t k = kh_get(khstr, str_hash, key.c_str());					\
	if (k != kh_end(str_hash)) {										\
		char *istr = (char *) kh_key(str_hash, k);						\
		kh_del(khstr, str_hash, k);										\
		free(istr);														\
	}
#define FIND_INT_EXISTING(key)											\
	khint_t k = kh_get(kh64, hash, (key));								\
	if (k == kh_end(hash)) {											\
		std::cerr << "error 1\n";										\
		exit(1);														\
	}
#define FIND_STR_EXISTING(key)											\
	khint_t k = kh_get(khstr, str_hash, (key.c_str()));					\
	if (k == kh_end(str_hash)) {										\
		std::cerr << "error 2\n";										\
		exit(1);														\
	}
#define FIND_INT_MISSING(key)											\
	khint_t k = kh_get(kh64, hash, key);								\
	if (k != kh_end(hash)) {											\
		std::cerr << "error 3\n";										\
		exit(1);														\
	}
#define FIND_STR_MISSING(key)											\
	khint_t k = kh_get(khstr, str_hash, key.c_str());					\
	if (k != kh_end(str_hash)) {										\
		std::cerr << "error 4\n";										\
		exit(1);														\
	}
#define FIND_INT_EXISTING_COUNT(key, count)								\
	khint_t k = kh_get(kh64, hash, key);								\
	if (k == kh_end(hash)) {											\
		++count;														\
	}
#define FIND_STR_EXISTING_COUNT(key, count)								\
	khint_t k = kh_get(khstr, str_hash, key.c_str());					\
	if (k == kh_end(str_hash)) {										\
		++count;														\
	}
#define ITERATE_INT(key)												\
	khiter_t it;														\
	for (it = kh_begin(hash); it != kh_end(hash); ++it){				\
		if (kh_exist(hash, it)){										\
			kh_value(hash, it) = 1;										\
		}																\
	}
#define CHECK_INT_ITERATOR_VALUE(it, value)

#define LOAD_FACTOR_INT_HASH(h) 0.0f
#define LOAD_FACTOR_STR_HASH(h) 0.0f
#define CLEAR_INT
#define CLEAR_STR

#include "template.cc"
