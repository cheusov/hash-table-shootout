#include <inttypes.h>
#include <string>
#include <nina.h>
#include <assert.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

#define SETUP_INT void *int_hash = NULL;
#define RESERVE_INT(size) \
	nina48resize(&int_hash, (size));
#define INSERT_INT(key, value) \
	*nina48ins(&int_hash, key, NULL) = value;
#define DELETE_INT(key) \
	nina48del(&int_hash, key, NULL); // return value is not checked because key is 32-bit in size
#define FIND_INT_EXISTING(key) \
	nina48get(int_hash, key); // return value is not checked because key is 32-bit in size
#define FIND_INT_MISSING(key) \
	nina48get(int_hash, key); // return value is not checked because key is 32-bit in size
#define FIND_INT_EXISTING_COUNT(key, count) \
	nina48get(int_hash, key); // count is not incremented because key is 32-bit in size
#define CHECK_INT_ITERATOR_VALUE(iterator, value)
#define ITERATE_INT(it) \
	nina_iterator_t it; \
	uint64_t *p_value; \
	uint32_t key; \
	nina48iterator_init(int_hash, &it); \
	while (p_value = nina48iterate(&it, &key), p_value) { \
		*p_value = 1; \
	}
#define LOAD_FACTOR_INT_HASH(int_hash) (float)nina48lf(int_hash) / 0x100000
#define CLEAR_INT nina48free(&int_hash)

#include "template.cc"
