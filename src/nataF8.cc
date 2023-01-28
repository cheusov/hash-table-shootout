#include <inttypes.h>
#include <string>
#include <nata.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

#define SETUP_STR void *str_hash = NULL;
#define RESERVE_STR(size)
#define INSERT_STR(key, value) \
	*nataF8ins(&str_hash, key.c_str(), key.size(), NULL) = value;
#define DELETE_STR(key) \
	nataF8del(&str_hash, key.c_str(), key.size(), NULL);
#define FIND_STR_EXISTING(key) \
	if (nataF8get(str_hash, key.c_str(), key.size()) == NULL) { \
		std::cerr << "error\n"; \
		exit(1); \
	}
#define FIND_STR_MISSING(key) \
	if (nataF8get(str_hash, key.c_str(), key.size()) != NULL) { \
		std::cerr << "error\n"; \
		exit(1); \
	}
#define FIND_STR_EXISTING_COUNT(key, count) \
	if (nataF8get(str_hash, key.c_str(), key.size()) != NULL) { \
		count++; \
	}
#define LOAD_FACTOR_STR_HASH(h) (0.0f)
#define CLEAR_STR

#include "template.cc"
