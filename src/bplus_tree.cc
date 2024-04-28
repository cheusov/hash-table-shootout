#include <inttypes.h>

#include <bplus_tree.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)(p)-(char*)NULL)))

#define SETUP_INT(int_hash)					\
	BplusTree * int_hash = bplus_tree_new();
#define RESERVE_INT(int_hash, size)
#define INSERT_INT(int_hash, key, value)		\
	bplus_tree_insert(int_hash, key, (char*)0 + value)
#define FIND_INT_EXISTING(int_hash, key)		\
	if (bplus_tree_get(int_hash, key) == NULL){ \
		std::cerr << "error\n";				\
		exit(1); \
	}
#define FIND_INT_MISSING(int_hash, key)		\
	if (bplus_tree_get(int_hash, key) != NULL){ \
		std::cerr << "error\n";				\
		exit(1); \
	}
#define FIND_INT_EXISTING_COUNT(int_hash, key, count)	\
	if (bplus_tree_get(int_hash, key) == NULL){ \
		++count; \
	}
#define DELETE_INT(int_hash, key)	\
	bplus_tree_remove(int_hash, key)
#define TEARDOWN bplus_tree_destroy(int_hash);
#define LOAD_FACTOR_INT_HASH(int_hash) (0.0f)
#define ITERATE_INT(int_hash, it)
#define CHECK_INT_ITERATOR_VALUE(int_hash, it, value)
#define CLEAR_INT

#include "template.cc"
