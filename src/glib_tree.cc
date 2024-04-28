#include <glib.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

static gint intcmp(gconstpointer a, gconstpointer b)
{
	return (a < b) ? -1 : ((a > b) ? 1 : 0);
}

static gint gstrcmp(gconstpointer a, gconstpointer b)
{
	return strcmp((char*) a, (char*) b);
}

static gboolean gtraversefunc(gpointer key, gpointer value, gpointer data)
{
//	printf("%p %p\n", key, *(int64_t*)value);
	return 0;
}

#define HASH_TYPE_INT GTree *
#define CREATE_INT(int_hash) g_tree_new(&intcmp)
#define RESERVE_INT(int_hash, size)
#define INSERT_INT(int_hash, key, value) \
	g_tree_insert(int_hash, GINT_TO_POINTER(key), __UNCONST(&value))
#define FIND_INT_EXISTING(int_hash, key) \
	if (g_tree_lookup(int_hash, GINT_TO_POINTER(key)) == NULL) { \
		std::cerr << "error\n"; \
		exit(1); \
	}
#define FIND_INT_MISSING(int_hash, key) \
	if (g_tree_lookup(int_hash, GINT_TO_POINTER(key)) != NULL) { \
		std::cerr << "error\n";								 \
		exit(1);											 \
	}
#define FIND_INT_EXISTING_COUNT(int_hash, key, count) \
	if (g_tree_lookup(int_hash, GINT_TO_POINTER(key)) != NULL) { \
		count++; \
	}
#define DELETE_INT(int_hash, key) \
	g_tree_remove(int_hash, GINT_TO_POINTER(key))
#define CHECK_INT_ITERATOR_VALUE(int_hash, iterator, value)
#define ITERATE_INT(int_hash, it)					\
	g_tree_foreach(int_hash, gtraversefunc, NULL);
#define LOAD_FACTOR_INT_HASH(int_hash) (0.0f)
#define CLEAR_INT(int_hash)

#define HASH_TYPE_STR GTree *
#define CREATE_STR(str_hash) g_tree_new(&gstrcmp)
#define RESERVE_STR(str_hash, size)
#define SHUFFLE_STR_ARRAY(keys)
#define INSERT_STR(str_hash, key, value) \
	g_tree_insert(str_hash, __UNCONST(key.c_str()), (char*)0 + value)
#define FIND_STR_EXISTING(str_hash, key)						   \
	if (g_tree_lookup(str_hash, __UNCONST(key.c_str())) == NULL) { \
		std::cerr << "error\n";								   \
		exit(1);												   \
	}
#define FIND_STR_MISSING(str_hash, key)						   \
	if (g_tree_lookup(str_hash, __UNCONST(key.c_str())) != NULL) { \
		std::cerr << "error\n";								   \
		exit(1);												   \
	}
#define FIND_STR_EXISTING_COUNT(str_hash, key, count) \
	if (g_tree_lookup(str_hash, __UNCONST(key.c_str())) != NULL) { \
		count++; \
	}
#define DELETE_STR(str_hash, key) \
	g_tree_remove(str_hash, __UNCONST(key.c_str()));
#define LOAD_FACTOR_STR_HASH(str_hash) (0.0f)
#define CLEAR_STR(str_hash)

#include "template.cc"
