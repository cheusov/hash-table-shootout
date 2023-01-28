#include <inttypes.h>
#include <string>
#include <Judy.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

#define SETUP_STR void *str_hash = NULL;
#define RESERVE_STR(size)
#define INSERT_STR(key, value) \
	*(Word_t *)JudyHSIns(&str_hash, __UNCONST(key.c_str()), key.size(), NULL) = value;
#define DELETE_STR(key) \
	JudyHSDel(&str_hash, __UNCONST(key.c_str()), key.size(), NULL);
#define FIND_STR_EXISTING(key) \
	if (JudyHSGet(str_hash, __UNCONST(key.c_str()), key.size()) == NULL) { \
		std::cerr << "error"; \
		exit(1); \
	}
#define FIND_STR_MISSING(key) \
	if (JudyHSGet(str_hash, __UNCONST(key.c_str()), key.size()) != NULL) { \
		std::cerr << "error"; \
		exit(1); \
	}
#define FIND_STR_EXISTING_COUNT(key, count) \
	if (JudyHSGet(str_hash, __UNCONST(key.c_str()), key.size()) != NULL) { \
		count++; \
	}
#define LOAD_FACTOR_STR_HASH(h) (0.0f)
#define CLEAR_STR

#include "template.cc"
