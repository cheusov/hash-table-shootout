#include <Python.h>

typedef PyObject * hash_t;

#define SETUP_INT									\
	Py_Initialize();								\
	hash_t int_hash = PyDict_New();				\
	PyObject * py_int_value = PyLong_FromLong(0);
#define RESERVE_INT(size)
#define INSERT_INT(key, value)						\
	PyObject * py_int_key = PyLong_FromLong(key);	\
	PyDict_SetItem(int_hash, py_int_key, py_int_value); \
	Py_DECREF(py_int_key)
#define DELETE_INT(key)							\
	PyObject * py_int_key = PyLong_FromLong(key);	\
	PyDict_DelItem(int_hash, py_int_key);			\
	Py_DECREF (py_int_key);
#define FIND_INT_EXISTING(key) \
	PyObject * py_int_key = PyLong_FromLong(key);				\
	volatile PyObject *v = PyDict_GetItem(int_hash, py_int_key);	\
	Py_DECREF (py_int_key);										\
	if (v == NULL) {											\
		std::cerr << "error 1\n";								\
		exit(1);												\
	}
#define FIND_INT_MISSING(key) \
	PyObject * py_int_key = PyLong_FromLong(key);				\
	volatile PyObject *v = PyDict_GetItem(int_hash, py_int_key);	\
	Py_DECREF (py_int_key);										\
	if (v != NULL) {											\
		std::cerr << "error 1\n";								\
		exit(1);												\
	}
#define FIND_INT_EXISTING_COUNT(key, count)						\
	PyObject * py_int_key = PyLong_FromLong(key);				\
	volatile PyObject *v = PyDict_GetItem(int_hash, py_int_key);	\
	Py_DECREF (py_int_key);										\
	if (v == NULL) {											\
		count++;												\
	}
#define CHECK_INT_ITERATOR_VALUE(iterator, value)

#define ITERATE_INT(it)									  \
	PyObject *key, *value;								  \
	Py_ssize_t it = 0;									  \
	while (PyDict_Next(int_hash, &it, &key, &value))

#define LOAD_FACTOR_INT_HASH(h) (0.0f)

#define CLEAR_INT

////

#define SETUP_STR									\
	Py_Initialize();								\
	hash_t str_hash = PyDict_New();					\
	PyObject * py_str_int_value = PyLong_FromLong(0);
#define RESERVE_STR(size)
#define INSERT_STR(key, value) \
	PyDict_SetItemString(str_hash, key.c_str(), py_str_int_value);
#define DELETE_STR(key)	\
	PyDict_DelItemString(str_hash, key.c_str());
#define FIND_STR_EXISTING(key) \
	volatile PyObject *v = PyDict_GetItemString(str_hash, key.c_str());	\
	if (v == NULL) {											\
		std::cerr << "error 1\n";								\
		exit(1);												\
	}
#define FIND_STR_MISSING(key) \
	volatile PyObject *v = PyDict_GetItemString(str_hash, key.c_str());	\
	if (v != NULL) {											\
		std::cerr << "error 1\n";								\
		exit(1);												\
	}
#define FIND_STR_EXISTING_COUNT(key, count)						\
	volatile PyObject *v = PyDict_GetItemString(str_hash, key.c_str());	\
	if (v == NULL) {											\
		count++;												\
	}
#define CHECK_STR_ITERATOR_VALUE(iterator, value)

#define ITERATE_STR(it)									  \
	PyObject *key, *value;								  \
	Py_ssize_t it = 0;									  \
	while (PyDict_Next(str_hash, &it, &key, &value))

#define LOAD_FACTOR_STR_HASH(str_hash) (0.0f)

#define CLEAR_STR

#include "template.cc"
