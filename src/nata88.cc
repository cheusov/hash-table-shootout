#include <inttypes.h>
#include <string>
#include <nata.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

#define HASH_TYPE_INT void *
#define CREATE_INT NULL
#define RESERVE_INT(int_hash, size)
#define INSERT_INT(int_hash, key, value) \
	*nata88ins(&int_hash, key, NULL) = value;
#define DELETE_INT(int_hash, key) \
	if (!nata88del(&int_hash, key, NULL)){ \
		std::cerr << "error\n"; \
		exit(1); \
	}
#define FIND_INT_EXISTING(int_hash, key) \
	if (nata88get(int_hash, key) == NULL) { \
		std::cerr << "error\n"; \
		exit(2); \
	}
#define FIND_INT_MISSING(int_hash, key) \
	if (nata88get(int_hash, key) != NULL) { \
		std::cerr << "error\n"; \
		exit(3); \
	}
#define FIND_INT_EXISTING_COUNT(int_hash, key, count) \
	if (nata88get(int_hash, key) != NULL) { \
		count++; \
	}
#define CHECK_INT_ITERATOR_VALUE(int_hash, iterator, value)
#define ITERATE_INT(int_hash, it)				\
	uint64_t key = 0; \
	uint64_t *p_value = nata88first(int_hash, &key); \
	for (; p_value != NULL; p_value = nata88next(int_hash, &key))
#define LOAD_FACTOR_INT_HASH(int_hash) (0.0f)
#define CLEAR_INT(int_hash) nata88free(&int_hash)

#include "template.cc"
