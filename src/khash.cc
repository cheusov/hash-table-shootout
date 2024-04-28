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

#define HASH_TYPE_INT khash_t(kh64) *
#define HASH_TYPE_STR khash_t(khstr) *

#define CREATE_INT(int_hash) kh_init(kh64)
#define CREATE_STR(str_hash) kh_init(khstr)

#define RESERVE_INT(int_hash, n) \
	kh_resize(kh64, int_hash, (khint_t)(n / __ac_HASH_UPPER + 1));
#define RESERVE_STR(str_hash, n) \
	kh_resize(khstr, str_hash, (khint_t)(n / __ac_HASH_UPPER + 1));
#define INSERT_INT(int_hash, key, value)								\
	int r;																\
	khint_t k = kh_put(kh64, int_hash, key, &r);						\
	if (r > 0) {														\
		kh_value(int_hash, k) = value;									\
	}
#define INSERT_STR(str_hash, key, value)								\
	int r;																\
	char *istr = strdup(key.c_str());									\
	khint_t k = kh_put(khstr, str_hash, istr, &r);						\
	if (r > 0) {														\
		kh_value(str_hash, k) = value;									\
	} else																\
		free(istr);
#define DELETE_INT(int_hash, key)					\
	khint_t k = kh_get(kh64, int_hash, key);		\
	if (k != kh_end(int_hash))						\
		kh_del(kh64, int_hash, k);
#define DELETE_STR(str_hash, key)										\
	khint_t k = kh_get(khstr, str_hash, key.c_str());					\
	if (k != kh_end(str_hash)) {										\
		char *istr = (char *) kh_key(str_hash, k);						\
		kh_del(khstr, str_hash, k);									\
		free(istr);													\
	}
#define FIND_INT_EXISTING(int_hash, key)								\
	khint_t k = kh_get(kh64, int_hash, (key));							\
	if (k == kh_end(int_hash)) {										\
		std::cerr << "error 1\n";										\
		exit(1);														\
	}
#define FIND_STR_EXISTING(str_hash, key)								\
	khint_t k = kh_get(khstr, str_hash, (key.c_str()));				\
	if (k == kh_end(str_hash)) {										\
		std::cerr << "error 2\n";										\
		exit(1);														\
	}
#define FIND_INT_MISSING(int_hash, key)								\
	khint_t k = kh_get(kh64, int_hash, key);							\
	if (k != kh_end(int_hash)) {										\
		std::cerr << "error 3\n";										\
		exit(1);														\
	}
#define FIND_STR_MISSING(str_hash, key)								\
	khint_t k = kh_get(khstr, str_hash, key.c_str());					\
	if (k != kh_end(str_hash)) {										\
		std::cerr << "error 4\n";										\
		exit(1);														\
	}
#define FIND_INT_EXISTING_COUNT(int_hash, key, count)					\
	khint_t k = kh_get(kh64, int_hash, key);							\
	if (k == kh_end(int_hash)) {										\
		++count;														\
	}
#define FIND_STR_EXISTING_COUNT(str_hash, key, count)					\
	khint_t k = kh_get(khstr, str_hash, key.c_str());					\
	if (k == kh_end(str_hash)) {										\
		++count;														\
	}
#define ITERATE_INT(int_hash, it)										\
	khiter_t it;														\
	for (it = kh_begin(int_hash); it != kh_end(int_hash); ++it){		\
		if (kh_exist(int_hash, it)){									\
			kh_value(int_hash, it) = 1;								\
		}																\
	}
#define CHECK_INT_ITERATOR_VALUE(int_hash, it, value)

#define LOAD_FACTOR_INT_HASH(h) \
	(float)(h)->n_occupied / (h)->n_buckets
#define LOAD_FACTOR_STR_HASH(h) \
	(float)(h)->n_occupied / (h)->n_buckets
#define CLEAR_INT(int_hash)
#define CLEAR_STR(str_hash)

#include "template.cc"
