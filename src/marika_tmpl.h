#include <inttypes.h>
#include <string>
#include <assert.h>

#include <marika.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

#define HASH_TYPE_INT void *
#define CREATE_INT NULL
#define RESERVE_INT(int_hash, size)
#define INSERT_INT(int_hash, key, value) \
	*MARIKA_INS(&int_hash, key, NULL) = value;
#define DELETE_INT(int_hash, key)
//	mar8U8Udel(&int_hash, key, NULL); // return value is not checked because key is 32-bit in size
#define FIND_INT_EXISTING(int_hash, key) \
	if (!MARIKA_GET(int_hash, key)) { printf("error"); exit(1); }
#define FIND_INT_MISSING(int_hash, key) \
	if (MARIKA_GET(int_hash, key)) { printf("error"); exit(1); }
#define FIND_INT_EXISTING_COUNT(int_hash, key, count) \
	if (MARIKA_GET(int_hash, key)) { ++count; }
#define CHECK_INT_ITERATOR_VALUE(int_hash, iterator, value)
//#define ITERATE_INT(int_hash, it)				\
//	uint64_t key = 0;								  \
//	uint64_t *p_value = mar8U8Ufirst(int_hash, &key); \
//	for (; p_value != NULL; p_value = mar8U8Unext(int_hash, &key))
#define ITERATE_INT(int_hash, it)				\
	marika_iterator_t it; \
	MARIKA_VALUE_TYPE *p_value; \
	MARIKA_KEY_TYPE key; \
	MARIKA_ITERATOR_INIT(int_hash, &it); \
	while (p_value = MARIKA_ITERATE(&it, &key), p_value) { \
		*p_value = 1; \
	} \
	MARIKA_ITERATOR_DESTROY(&it);
#define LOAD_FACTOR_INT_HASH(int_hash) 0
#define CLEAR_INT(int_hash) MARIKA_FREE(&int_hash)

#include "template.cc"
