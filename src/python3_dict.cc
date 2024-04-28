#include <Python.h>

typedef PyObject * hash_t;

#define HASH_TYPE_INT hash_t
#define CREATE_INT(int_hash)
#define PREPARE_INT(int_hash)						\
	Py_Initialize();								\
	int_hash = PyDict_New();						\
	PyObject * py_int_value = PyLong_FromLong(0)
#define RESERVE_INT(int_hash, size)
#define INSERT_INT(int_hash, key, value)			\
	PyObject * py_int_key = PyLong_FromLong(key);	\
	PyDict_SetItem(int_hash, py_int_key, py_int_value); \
	Py_DECREF(py_int_key)
#define DELETE_INT(int_hash, key)					\
	PyObject * py_int_key = PyLong_FromLong(key);	\
	PyDict_DelItem(int_hash, py_int_key);			\
	Py_DECREF (py_int_key);
#define FIND_INT_EXISTING(int_hash, key)						\
	PyObject * py_int_key = PyLong_FromLong(key);				\
	volatile PyObject *v = PyDict_GetItem(int_hash, py_int_key);\
	Py_DECREF (py_int_key);									\
	if (v == NULL) {											\
		std::cerr << "error 1\n";								\
		exit(1);												\
	}
#define FIND_INT_MISSING(int_hash, key) \
	PyObject * py_int_key = PyLong_FromLong(key);				\
	volatile PyObject *v = PyDict_GetItem(int_hash, py_int_key);	\
	Py_DECREF (py_int_key);									\
	if (v != NULL) {											\
		std::cerr << "error 1\n";								\
		exit(1);												\
	}
#define FIND_INT_EXISTING_COUNT(int_hash, key, count)			\
	PyObject * py_int_key = PyLong_FromLong(key);				\
	volatile PyObject *v = PyDict_GetItem(int_hash, py_int_key);\
	Py_DECREF (py_int_key);									\
	if (v == NULL) {											\
		count++;												\
	}
#define CHECK_INT_ITERATOR_VALUE(int_hash, iterator, value)

#define ITERATE_INT(int_hash, it)						  \
	PyObject *key, *value;								  \
	Py_ssize_t it = 0;									  \
	while (PyDict_Next(int_hash, &it, &key, &value))

#define LOAD_FACTOR_INT_HASH(int_hash) (0.0f)

#define CLEAR_INT(int_hash)

////
#define HASH_TYPE_STR hash_t
#define CREATE_STR(str_hash)
#define PREPARE_STR(str_hash)						\
	Py_Initialize();								\
	str_hash = PyDict_New();						\
	PyObject * py_str_int_value = PyLong_FromLong(0)
#define RESERVE_STR(str_hash, size)
#define INSERT_STR(str_hash, key, value) \
	PyDict_SetItemString(str_hash, key.c_str(), py_str_int_value);
#define DELETE_STR(str_hash, key)	\
	PyDict_DelItemString(str_hash, key.c_str());
#define FIND_STR_EXISTING(str_hash, key) \
	volatile PyObject *v = PyDict_GetItemString(str_hash, key.c_str());	\
	if (v == NULL) {											\
		std::cerr << "error 1\n";								\
		exit(1);												\
	}
#define FIND_STR_MISSING(str_hash, key) \
	volatile PyObject *v = PyDict_GetItemString(str_hash, key.c_str());	\
	if (v != NULL) {											\
		std::cerr << "error 1\n";								\
		exit(1);												\
	}
#define FIND_STR_EXISTING_COUNT(str_hash, key, count)						\
	volatile PyObject *v = PyDict_GetItemString(str_hash, key.c_str());	\
	if (v == NULL) {											\
		count++;												\
	}
#define CHECK_STR_ITERATOR_VALUE(str_hash, iterator, value)

#define ITERATE_STR(str_hash, it)						\
	PyObject *key, *value;								\
	Py_ssize_t it = 0;									\
	while (PyDict_Next(str_hash, &it, &key, &value))

#define LOAD_FACTOR_STR_HASH(str_hash) (0.0f)

#define CLEAR_STR(str_hash)

#include "template.cc"
