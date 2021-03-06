#include <inttypes.h>
#include <string>
#include <nata.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

#define SETUP_INT \
	void *hash_int = NULL;
#define RESERVE_INT(size)
#define INSERT_INT(key, value) \
	*nata88ins(&hash_int, key, NULL) = value;
#define DELETE_INT(key) \
	std::cerr << "nata88del is not implemented yet"; \
	exit(72); //nata88del(&hash_int, key, NULL);
#define FIND_INT_EXISTING(key) \
	if (nata88get(hash_int, key, NULL) == NULL) { \
		std::cerr << "error\n"; \
		exit(1); \
	}
#define FIND_INT_MISSING(key) \
	if (nata88get(hash_int, key, NULL) != NULL) { \
		std::cerr << "error\n"; \
		exit(1); \
	}
#define FIND_INT_EXISTING_COUNT(key, count) \
	if (nata88get(hash_int, key, NULL) != NULL) { \
		count++; \
	}
#define CHECK_INT_ITERATOR_VALUE(iterator, value) \
	std::cerr << "iteration for nata88 is not implemented yet\n"; \
	exit(73);
#define ITERATE_INT(key)

#define LOAD_FACTOR_INT_HASH(hash) (0.0f)

#define CLEAR_INT

#include "template.cc"
