#include <inttypes.h>
#include <string>
#include <Judy.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))


#define HASH_TYPE_STR void *
#define CREATE_STR(str_hash) NULL
#define RESERVE_STR(str_hash, size)
#define INSERT_STR(str_hash, key, value) \
	*(Word_t *)JudyHSIns(&str_hash, __UNCONST(key.c_str()), key.size(), NULL) = value;
#define DELETE_STR(str_hash, key) \
	JudyHSDel(&str_hash, __UNCONST(key.c_str()), key.size(), NULL);
#define FIND_STR_EXISTING(str_hash, key) \
	if (JudyHSGet(str_hash, __UNCONST(key.c_str()), key.size()) == NULL) { \
		std::cerr << "error"; \
		exit(1); \
	}
#define FIND_STR_MISSING(str_hash, key) \
	if (JudyHSGet(str_hash, __UNCONST(key.c_str()), key.size()) != NULL) { \
		std::cerr << "error"; \
		exit(1); \
	}
#define FIND_STR_EXISTING_COUNT(str_hash, key, count) \
	if (JudyHSGet(str_hash, __UNCONST(key.c_str()), key.size()) != NULL) { \
		count++; \
	}
#define LOAD_FACTOR_STR_HASH(str_hash) (0.0f)
#define CLEAR_STR(str_hash)

#include "template.cc"
