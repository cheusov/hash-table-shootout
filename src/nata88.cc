#include <inttypes.h>
#include <string>
#include <nata.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

#define SETUP_INT void *int_hash = NULL;
#define RESERVE_INT(size)
#define INSERT_INT(key, value) \
	*nata88ins(&int_hash, key, NULL) = value;
#define DELETE_INT(key) \
	if (!nata88del(&int_hash, key, NULL)){ \
		std::cerr << "error\n"; \
		exit(1); \
	}
#define FIND_INT_EXISTING(key) \
	if (nata88get(int_hash, key) == NULL) { \
		std::cerr << "error\n"; \
		exit(2); \
	}
#define FIND_INT_MISSING(key) \
	if (nata88get(int_hash, key) != NULL) { \
		std::cerr << "error\n"; \
		exit(3); \
	}
#define FIND_INT_EXISTING_COUNT(key, count) \
	if (nata88get(int_hash, key) != NULL) { \
		count++; \
	}
#define CHECK_INT_ITERATOR_VALUE(iterator, value)
#define ITERATE_INT(it) \
	uint64_t key = 0; \
	uint64_t *p_value = nata88first(int_hash, &key); \
	for (; p_value != NULL; p_value = nata88next(int_hash, &key))
#define LOAD_FACTOR_INT_HASH(h) (0.0f)
#define CLEAR_INT nata88free(&int_hash)

#include "template.cc"
