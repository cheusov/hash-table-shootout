#include <inttypes.h>
#include <string>
#include <nina.h>
#include <assert.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

#define HASH_TYPE_INT void *
#define CREATE_INT NULL
#define RESERVE_INT(int_hash, size) \
	nina48resize(&int_hash, (size));
#define INSERT_INT(int_hash, key, value) \
	*nina48ins(&int_hash, key, NULL) = value;
#define DELETE_INT(int_hash, key) \
	nina48del(&int_hash, key, NULL); // return value is not checked because key is 32-bit in size
#define FIND_INT_EXISTING(int_hash, key) \
	nina48get(int_hash, key); // return value is not checked because key is 32-bit in size
#define FIND_INT_MISSING(int_hash, key) \
	nina48get(int_hash, key); // return value is not checked because key is 32-bit in size
#define FIND_INT_EXISTING_COUNT(int_hash, key, count) \
	nina48get(int_hash, key); // count is not incremented because key is 32-bit in size
#define CHECK_INT_ITERATOR_VALUE(int_hash, iterator, value)
#define ITERATE_INT(int_hash, it)				\
	nina_iterator_t it; \
	uint64_t *p_value; \
	uint32_t key; \
	nina48iterator_init(int_hash, &it); \
	while (p_value = nina48iterate(&it, &key), p_value) { \
		*p_value = 1; \
	}
#define LOAD_FACTOR_INT_HASH(int_hash) (float)nina48lf(int_hash) / 0x100000
#define CLEAR_INT(int_hash) nina48free(&int_hash)

#include "template.cc"
