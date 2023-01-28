#include <inttypes.h>

#include <bplus_tree.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)(p)-(char*)NULL)))

#define SETUP_INT \
	BplusTree * int_hash = bplus_tree_new();
#define RESERVE_INT(size)
#define INSERT_INT(key, value) \
	bplus_tree_insert(int_hash, key, (char*)0 + value)
#define FIND_INT_EXISTING(key) \
	if (bplus_tree_get(int_hash, key) == NULL){ \
		std::cerr << "error\n";				\
		exit(1); \
	}
#define FIND_INT_MISSING(key) \
	if (bplus_tree_get(int_hash, key) != NULL){ \
		std::cerr << "error\n";				\
		exit(1); \
	}
#define FIND_INT_EXISTING_COUNT(key, count) \
	if (bplus_tree_get(int_hash, key) == NULL){ \
		++count; \
	}
#define DELETE_INT(key) \
	bplus_tree_remove(int_hash, key)
#define TEARDOWN bplus_tree_destroy(int_hash);
#define LOAD_FACTOR_INT_HASH(int_hash) (0.0f)
#define ITERATE_INT(it)
#define CHECK_INT_ITERATOR_VALUE(it,value)
#define CLEAR_INT

#include "template.cc"
