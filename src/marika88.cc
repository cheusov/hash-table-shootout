#include <inttypes.h>
#include <string>
#include <marika.h>
#include <assert.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

#define HASH_TYPE_INT void *
#define CREATE_INT NULL
#define RESERVE_INT(int_hash, size)
#define INSERT_INT(int_hash, key, value) \
	*mar8U8Uins(&int_hash, key, NULL) = value;
#define DELETE_INT(int_hash, key)
//	mar8U8Udel(&int_hash, key, NULL); // return value is not checked because key is 32-bit in size
#define FIND_INT_EXISTING(int_hash, key) \
	mar8U8Uget(int_hash, key); // return value is not checked because key is 32-bit in size
#define FIND_INT_MISSING(int_hash, key) \
	mar8U8Uget(int_hash, key); // return value is not checked because key is 32-bit in size
#define FIND_INT_EXISTING_COUNT(int_hash, key, count) \
	mar8U8Uget(int_hash, key); // count is not incremented because key is 32-bit in size
#define CHECK_INT_ITERATOR_VALUE(int_hash, iterator, value)
//#define ITERATE_INT(int_hash, it)				\
//	uint64_t key = 0;								  \
//	uint64_t *p_value = mar8U8Ufirst(int_hash, &key); \
//	for (; p_value != NULL; p_value = mar8U8Unext(int_hash, &key))
#define ITERATE_INT(int_hash, it)				\
	marika_iterator_t it; \
	uint64_t *p_value; \
	uint64_t key; \
	mar8U8Uiterator_init(int_hash, &it); \
	while (p_value = mar8U8Uiterate(&it, &key), p_value) { \
		*p_value = 1; \
	} \
	mar8U8Uiterator_destroy(&it);
#define LOAD_FACTOR_INT_HASH(int_hash) 0
#define CLEAR_INT(int_hash) mar8U8Ufree(&int_hash)

#include "template.cc"
