#include <inttypes.h>
#include <string>
#include <nata.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

#define HASH_TYPE_STR void *
#define CREATE_STR(str_hash) NULL
#define RESERVE_STR(str_hash, size)
#define INSERT_STR(str_hash, key, value) \
	*nataF8ins(&str_hash, key.c_str(), key.size(), NULL) = value;
#define DELETE_STR(str_hash, key) \
	nataF8del(&str_hash, key.c_str(), key.size(), NULL);
#define FIND_STR_EXISTING(str_hash, key) \
	if (nataF8get(str_hash, key.c_str(), key.size()) == NULL) { \
		std::cerr << "error\n"; \
		exit(1); \
	}
#define FIND_STR_MISSING(str_hash, key) \
	if (nataF8get(str_hash, key.c_str(), key.size()) != NULL) { \
		std::cerr << "error\n"; \
		exit(1); \
	}
#define FIND_STR_EXISTING_COUNT(str_hash, key, count) \
	if (nataF8get(str_hash, key.c_str(), key.size()) != NULL) { \
		count++; \
	}
#define LOAD_FACTOR_STR_HASH(str_hash) (0.0f)
#define CLEAR_STR(str_hash)

#include "template.cc"
