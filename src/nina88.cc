#include <inttypes.h>
#include <string>
#include <nina.h>
#include <assert.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

#define SETUP_INT void *int_hash = NULL;
#define RESERVE_INT(size) \
	nina88resize(&int_hash, (size));
#define INSERT_INT(key, value) \
	*nina88ins(&int_hash, key, NULL) = value;
#define DELETE_INT(key) \
	nina88del(&int_hash, key, NULL);
#define FIND_INT_EXISTING(key) \
	nina88get(int_hash, key);
#define FIND_INT_MISSING(key) \
	nina88get(int_hash, key);
#define FIND_INT_EXISTING_COUNT(key, count) \
	nina88get(int_hash, key);
#define CHECK_INT_ITERATOR_VALUE(iterator, value)
#define ITERATE_INT(it) \
	nina_iterator_t it; \
	uint64_t *p_value; \
	uint64_t key; \
	nina88iterator_init(int_hash, &it); \
	while (p_value = nina88iterate(&it, &key), p_value) { \
		*p_value = 1; \
	}
#define LOAD_FACTOR_INT_HASH(int_hash) (float)nina88lf(int_hash) / 0x100000
#define CLEAR_INT nina88free(&int_hash)

#include "template.cc"
