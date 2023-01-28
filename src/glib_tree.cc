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

#define SETUP_INT GTree * int_hash = g_tree_new(&intcmp);
#define RESERVE_INT(size)
#define INSERT_INT(key, value) \
	g_tree_insert(int_hash, GINT_TO_POINTER(key), __UNCONST(&value))
#define FIND_INT_EXISTING(key) \
	if (g_tree_lookup(int_hash, GINT_TO_POINTER(key)) == NULL) { \
		std::cerr << "error\n"; \
		exit(1); \
	}
#define FIND_INT_MISSING(key) \
	if (g_tree_lookup(int_hash, GINT_TO_POINTER(key)) != NULL) { \
		std::cerr << "error\n";								 \
		exit(1);											 \
	}
#define FIND_INT_EXISTING_COUNT(key, count) \
	if (g_tree_lookup(int_hash, GINT_TO_POINTER(key)) != NULL) { \
		count++; \
	}
#define DELETE_INT(key) \
	g_tree_remove(int_hash, GINT_TO_POINTER(key))
#define CHECK_INT_ITERATOR_VALUE(iterator, value)
#define ITERATE_INT(key) \
	g_tree_foreach(int_hash, gtraversefunc, NULL);
#define LOAD_FACTOR_INT_HASH(int_hash) (0.0f)
#define CLEAR_INT

#define SETUP_STR GTree* str_hash = g_tree_new(&gstrcmp);
#define RESERVE_STR(size)
#define SHUFFLE_STR_ARRAY(keys)
#define INSERT_STR(key, value) \
	g_tree_insert(str_hash, __UNCONST(key.c_str()), (char*)0 + value)
#define FIND_STR_EXISTING(key)									   \
	if (g_tree_lookup(str_hash, __UNCONST(key.c_str())) == NULL) { \
		std::cerr << "error\n";									   \
		exit(1);												   \
	}
#define FIND_STR_MISSING(key)									   \
	if (g_tree_lookup(str_hash, __UNCONST(key.c_str())) != NULL) { \
		std::cerr << "error\n";									   \
		exit(1);												   \
	}
#define FIND_STR_EXISTING_COUNT(key, count) \
	if (g_tree_lookup(str_hash, __UNCONST(key.c_str())) != NULL) { \
		count++; \
	}
#define DELETE_STR(key) \
	g_tree_remove(str_hash, __UNCONST(key.c_str()));
#define LOAD_FACTOR_STR_HASH(int_hash) (0.0f)
#define CLEAR_STR

#include "template.cc"
