#include <inttypes.h>
#include <string>
#include <Judy.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

#define HASH_TYPE_INT void *
#define CREATE_INT(int_hash) NULL
#define RESERVE_INT(int_hash, size)
#define INSERT_INT(int_hash, key, value) \
	*(Word_t *)JudyLIns(&int_hash, key, NULL) = value;
#define DELETE_INT(int_hash, key) \
	JudyLDel(&int_hash, key, NULL);
#define FIND_INT_EXISTING(int_hash, key) \
	if (JudyLGet(int_hash, key, NULL) == NULL) { \
		printf("error"); \
		exit(1); \
	}
#define FIND_INT_MISSING(int_hash, key) \
	if (JudyLGet(int_hash, key, NULL) != NULL) { \
		printf("error"); \
		exit(1); \
	}
#define FIND_INT_EXISTING_COUNT(int_hash, key, count) \
	if (JudyLGet(int_hash, key, NULL) != NULL) { \
		count++; \
	}
#define CHECK_INT_ITERATOR_VALUE(int_hash, iterator, value)
#define ITERATE_INT(int_hash, it) \
	Word_t key = 0; \
	Word_t *p_value = (Word_t *)JudyLFirst(int_hash, &key, NULL); \
	for (; p_value != NULL; p_value = (Word_t *)JudyLNext(int_hash, &key, NULL))
#define LOAD_FACTOR_INT_HASH(int_hash) (0.0f)
#define CLEAR_INT

#include "template.cc"
