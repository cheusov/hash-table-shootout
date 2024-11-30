#include <inttypes.h>
#include <string>
#include <marika.h>
#include <assert.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

#define HASH_TYPE_INT void *
#define CREATE_INT NULL
#define RESERVE_INT(int_hash, size)
#define INSERT_INT(int_hash, key, value) \
	*mar4U4Uins(&int_hash, key, NULL) = value;
#define DELETE_INT(int_hash, key)
//	mar4U4Udel(&int_hash, key, NULL); // return value is not checked because key is 32-bit in size
#define FIND_INT_EXISTING(int_hash, key) \
	mar4U4Uget(int_hash, key); // return value is not checked because key is 32-bit in size
#define FIND_INT_MISSING(int_hash, key) \
	mar4U4Uget(int_hash, key); // return value is not checked because key is 32-bit in size
#define FIND_INT_EXISTING_COUNT(int_hash, key, count) \
	mar4U4Uget(int_hash, key); // count is not incremented because key is 32-bit in size
#define CHECK_INT_ITERATOR_VALUE(int_hash, iterator, value)
#define ITERATE_INT(int_hash, it)				\
	uint32_t key = 0;								  \
	uint32_t *p_value = mar4U4Ufirst(int_hash, &key); \
	for (; p_value != NULL; p_value = mar4U4Unext(int_hash, &key))
#define LOAD_FACTOR_INT_HASH(int_hash) 0
#define CLEAR_INT(int_hash) mar4U4Ufree(&int_hash)

#include "template.cc"
