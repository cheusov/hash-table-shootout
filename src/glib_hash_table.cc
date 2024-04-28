#include <glib.h>

#define __UNCONST(p) ((void *)((char*)NULL+((char*)p-(char*)NULL)))

static void ghrfunc(gpointer key, gpointer value, gpointer user_data)
{
//	printf("%p %p\n", key, *(int64_t*)value);
}

#define SETUP_INT(int_hash) GHashTable* int_hash = g_hash_table_new(g_direct_hash, g_direct_equal);
#define RESERVE_INT(int_hash, size)
#define INSERT_INT(int_hash, key, value) \
	g_hash_table_insert(int_hash, GINT_TO_POINTER(key), __UNCONST(&value))
#define FIND_INT_EXISTING(int_hash, key) \
	if (g_hash_table_lookup(int_hash, GINT_TO_POINTER(key)) == NULL) { \
		std::cerr << "error\n";									   \
		exit(1); \
	}
#define FIND_INT_MISSING(int_hash, key) \
	if (g_hash_table_lookup(int_hash, GINT_TO_POINTER(key)) != NULL) { \
		std::cerr << "error\n";									   \
		exit(1);												   \
	}
#define FIND_INT_EXISTING_COUNT(int_hash, key, count) \
	if (g_hash_table_lookup(int_hash, GINT_TO_POINTER(key)) != NULL) { \
		count++; \
	}
#define DELETE_INT(int_hash, key) \
	g_hash_table_remove(int_hash, GINT_TO_POINTER(key))
#define CHECK_INT_ITERATOR_VALUE(int_hash, iterator, value)
#define ITERATE_INT(int_hash, it)					\
	g_hash_table_foreach(int_hash, ghrfunc, NULL);
#define LOAD_FACTOR_INT_HASH(int_hash) (0.0f)
#define CLEAR_INT(int_hash)

#define SETUP_STR(str_hash) GHashTable* str_hash = g_hash_table_new(g_str_hash, g_str_equal);
#define RESERVE_STR(str_hash, size)
#define SHUFFLE_STR_ARRAY(keys)
#define INSERT_STR(str_hash, key, value)								\
	{																	\
		char *key_copy = strdup(key.c_str());							\
		if (!g_hash_table_insert(str_hash, key_copy, (char*)0 + value)){ \
			free(key_copy);											\
		}																\
	}
#define FIND_STR_EXISTING(str_hash, key)								\
	if (g_hash_table_lookup(str_hash, __UNCONST(key.c_str())) == NULL) { \
		std::cerr << "error\n";										\
		exit(1);														\
	}
#define FIND_STR_MISSING(str_hash, key) \
	if (g_hash_table_lookup(str_hash, __UNCONST(key.c_str())) != NULL) { \
		std::cerr << "error\n";											\
		exit(1); \
	}
#define FIND_STR_EXISTING_COUNT(str_hash, key, count) \
	if (g_hash_table_lookup(str_hash, __UNCONST(key.c_str())) != NULL) { \
		count++; \
	}
#define DELETE_STR(str_hash, key) \
	g_hash_table_remove(str_hash, __UNCONST(key.c_str()));
#define LOAD_FACTOR_STR_HASH(str_hash) (0.0f)
#define CLEAR_STR(str_hash)

#include "template.cc"
