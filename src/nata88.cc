#include <inttypes.h>
#include <string>
#include <nata.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

#define SETUP_INT void *hash_int = NULL;
#define RESERVE_INT(size)
#define INSERT_INT(key, value) \
	*nata88ins(&hash_int, key, NULL) = value;
#define DELETE_INT(key) \
	nata88del(&hash_int, key, NULL);
#define FIND_INT_EXISTING(key) \
	if (nata88get(hash_int, key) == NULL) { \
		std::cerr << "error\n"; \
		exit(1); \
	}
#define FIND_INT_MISSING(key) \
	if (nata88get(hash_int, key) != NULL) { \
		std::cerr << "error\n"; \
		exit(1); \
	}
#define FIND_INT_EXISTING_COUNT(key, count) \
	if (nata88get(hash_int, key) != NULL) { \
		count++; \
	}
#define CHECK_INT_ITERATOR_VALUE(iterator, value)
#define ITERATE_INT(key) \
	uint64_t key = 0; \
	uint64_t *p_value = nata88first(hash_int, &key); \
	for (; p_value != NULL; p_value = nata88next(hash_int, &key))
#define LOAD_FACTOR_INT_HASH(hash) (0.0f)
#define CLEAR_INT

#include "template.cc"
