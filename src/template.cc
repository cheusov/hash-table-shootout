#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <sys/resource.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <iostream>
#include <array>
#include <iomanip>
#include <cassert>
#include <getopt.h>

// TODO When generating random values to insert in the map there is no check
// to see if duplicate random values are generated. Could improve that (but the probability is so so
// low and the impact nearly null that it's not really worth it).

static const std::array<char, 62> ALPHANUMERIC_CHARS = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

/**
 * SMALL_STRING_SIZE should be small enough so that there is no heap allocation when a std::string is created.
 */
static const std::size_t TINY_STRING_MIN_SIZE = 2;
static const std::size_t TINY_STRING_MAX_SIZE = 10;
static const std::size_t SMALL_STRING_MIN_SIZE = 11;
static const std::size_t SMALL_STRING_MAX_SIZE = 20;
static const std::size_t STRING_MIN_SIZE = 21;
static const std::size_t STRING_MAX_SIZE = 100;
static const std::size_t HUGE_STRING_MIN_SIZE = 101;
static const std::size_t HUGE_STRING_MAX_SIZE = 200;

static const std::int64_t SEED = 0;
static std::mt19937_64 generator(SEED);

#ifndef ITERATE_INT
#define ITERATE_INT(int_hash, it) for (const auto& it : int_hash)
#endif

#ifndef SHUFFLE_STR_ARRAY
#define SHUFFLE_STR_ARRAY(keys) std::shuffle(keys.begin(), keys.end(), generator)
#endif

static std::size_t tests_count;
static std::size_t num_keys;

static std::size_t get_memory_usage_bytes(void)
{
	struct rusage r_usage;
	int ret = getrusage(RUSAGE_SELF, &r_usage);
	if (ret) {
		perror("getrusage(2) failed");
		exit(1);
	}
#ifdef __APPLE__
	return r_usage.ru_maxrss;
#else
	return r_usage.ru_maxrss * 1024;
#endif
}

// user time in microseconds
static uint64_t get_user_time(void)
{
	struct rusage r_usage;
	int ret = getrusage(RUSAGE_SELF, &r_usage);
	if (ret) {
		perror("getrusage(2) failed");
		exit(1);
	}
	return (r_usage.ru_utime.tv_sec * 1000000uL + r_usage.ru_utime.tv_usec) * 1000uL;
}

std::string get_random_alphanum_string(
	std::size_t min_size, std::size_t max_size)
{
	std::uniform_int_distribution<std::size_t> rd_uniform_size(min_size, max_size);
	size_t size = rd_uniform_size(generator);

	std::uniform_int_distribution<std::size_t> rd_uniform(0, ALPHANUMERIC_CHARS.size() - 1);

	std::string str(size, '\0');
	for (std::size_t i = 0; i < size; i++) {
		str[i] = ALPHANUMERIC_CHARS[rd_uniform(generator)];
	}

	return str;
}

/**
 * Generate a vector [0, nb_ints) and shuffle it
 */
static std::vector<std::int64_t> get_random_range_ints(std::size_t nb_ints) {
	std::vector<std::int64_t> random_shuffle_ints(nb_ints);
	std::iota(random_shuffle_ints.begin(), random_shuffle_ints.end(), 0);
	std::shuffle(random_shuffle_ints.begin(), random_shuffle_ints.end(), generator);

	return random_shuffle_ints;
}

/**
 * Generate random vector of random ints between min and max.
 */
static std::vector<std::int64_t> get_random_full_ints(
	std::size_t nb_ints,
	std::int64_t min = 0,
	std::int64_t max = std::numeric_limits<std::int64_t>::max())
{
	std::uniform_int_distribution<std::int64_t> rd_uniform(min, max);

	std::vector<std::int64_t> random_ints(nb_ints);
	for (std::size_t i = 0; i < random_ints.size(); i++) {
		random_ints[i] = rd_uniform(generator);
	}

	return random_ints;
}

static std::vector<std::string> get_random_alphanum_strings(
	std::size_t nb_strings, std::size_t min_size, std::size_t max_size)
{
	std::vector<std::string> random_strings(nb_strings);
	for (std::size_t i = 0; i < random_strings.size(); i++) {
		random_strings[i] = get_random_alphanum_string(min_size, max_size);
	}

	return random_strings;
}

class measurements {
 public:
 measurements(): m_memory_usage_bytes_start(get_memory_usage_bytes()),
		m_chrono_start(get_user_time())
	{
	}

	void set_chrono_start()
	{
		m_chrono_start = get_user_time();
	}

	~measurements() {
		const auto chrono_end = get_user_time();
		const std::size_t memory_usage_bytes_end = get_memory_usage_bytes();

		const float nb_seconds = (chrono_end - m_chrono_start);
		// On reads or delete the used bytes could be less than initially.
		const std::size_t used_memory_bytes = (memory_usage_bytes_end > m_memory_usage_bytes_start)?
			memory_usage_bytes_end - m_memory_usage_bytes_start:0;

		std::cout << nb_seconds / num_keys / tests_count << " " <<
			std::fixed << std::setprecision(2) <<
			(float)used_memory_bytes / num_keys / tests_count << " ";
	}

private:
	std::size_t m_memory_usage_bytes_start;
	std::uint64_t m_chrono_start = get_user_time();
};

static std::string test_type;
static std::int64_t value;

static std::vector<std::int64_t> generate_integer_keys()
{
	if (test_type == "insert_random_range" ||
		test_type == "reinsert_random_range" ||
		test_type == "read_random_range" ||
		test_type == "read_miss_random_range" ||
		test_type == "insert_random_range_reserve" ||
		test_type == "read_random_range_after_delete" ||
		test_type == "iteration_random_range" ||
		test_type == "delete_random_range")
	{
		return get_random_range_ints(num_keys);
	} else if (test_type == "insert_random_full" ||
			  test_type == "reinsert_random_full" ||
			  test_type == "read_random_full" ||
			  test_type == "read_miss_random_full" ||
			  test_type == "insert_random_full_reserve" ||
			  test_type == "read_random_full_after_delete" ||
			  test_type == "iteration_random_full" ||
			  test_type == "delete_random_full")
	{
		return get_random_full_ints(num_keys);
	} else {
		return std::vector<std::int64_t>();
	}
}

static bool process_integers()
{
	bool ret = true;

#ifdef HASH_TYPE_INT
	std::vector<HASH_TYPE_INT> int_hashes { tests_count, CREATE_INT };

#ifdef PREPARE_INT
	for (auto& int_hash: int_hashes) {
		PREPARE_INT(int_hash);
	}
#endif

	std::vector<std::int64_t> keys = generate_integer_keys();
	if (keys.empty())
		ret = true;

	if (test_type == "insert_random_range" ||
		test_type == "insert_random_full")
	{
		measurements m;
		for (auto& hash_int: int_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_INT(hash_int, keys[i], value);
			}
		}
	}

	else if (test_type == "insert_random_range_reserve" ||
			 test_type == "insert_random_full_reserve")
	{
		measurements m;
		for (auto& hash_int: int_hashes) {
			RESERVE_INT(hash_int, num_keys);
		}
		for (auto& hash_int: int_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_INT(hash_int, keys[i], value);
			}
		}
	}

	else if (test_type == "reinsert_random_range" ||
			 test_type == "reinsert_random_full")
	{
		measurements m;
		for (auto& hash_int: int_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_INT(hash_int, keys[i], value);
			}
		}
		std::shuffle(keys.begin(), keys.end(), generator);

		m.set_chrono_start();
		for (auto& hash_int: int_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_INT(hash_int, keys[i], value);
			}
		}
	}

	else if (test_type == "read_random_range" ||
			 test_type == "read_random_full")
	{
		measurements m;
		for (auto& hash_int: int_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_INT(hash_int, keys[i], value);
			}
		}

		std::shuffle(keys.begin(), keys.end(), generator);

		m.set_chrono_start();
		std::int64_t i64_val; // for cuckoohash_map
		for (auto& hash_int: int_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				FIND_INT_EXISTING(hash_int, keys[i]);
			}
		}
	}

	else if (test_type == "read_miss_random_range" ||
			 test_type == "read_miss_random_full")
	{
		std::vector<std::int64_t> keys_read;
		if (test_type == "read_miss_random_range"){
			keys_read =
				get_random_full_ints(num_keys, std::numeric_limits<std::int64_t>::min(), -3);
		}else if (test_type == "read_miss_random_full"){
			keys_read =
				get_random_full_ints(num_keys, std::numeric_limits<std::int64_t>::min(), -3);
		}

		measurements m;
		for (auto& hash_int: int_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_INT(hash_int, keys[i], value);
			}
		}


		m.set_chrono_start();
		std::int64_t i64_val; // for cuckoohash_map
		for (auto& hash_int: int_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				FIND_INT_MISSING(hash_int, keys_read[i]);
			}
		}
	}

	else if (test_type == "read_random_range_after_delete" ||
			 test_type == "read_random_full_after_delete")
	{
		measurements m;
		for (auto& hash_int: int_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_INT(hash_int, keys[i], value);
			}
		}

		std::shuffle(keys.begin(), keys.end(), generator);
		for (auto& hash_int: int_hashes) {
			for (std::int64_t i = 0; i < (num_keys + 1) / 2; i++) {
				DELETE_INT(hash_int, keys[i]);
			}
		}

		std::shuffle(keys.begin(), keys.end(), generator);


		std::int64_t nb_found = 0;
		m.set_chrono_start();
		std::string s_val; // for kyotocabinet_stash
		std::int64_t i64_val; // for cuckoohash_map
		for (auto& hash_int: int_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				FIND_INT_EXISTING_COUNT(hash_int, keys[i], nb_found);
			}
		}
	}

	else if (test_type == "iteration_random_range" ||
			 test_type == "iteration_random_full")
	{
		measurements m;
		for (auto& hash_int: int_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_INT(hash_int, keys[i], value);
			}
		}


		m.set_chrono_start();
		for (auto& hash_int: int_hashes) {
			ITERATE_INT(hash_int, it) {
				CHECK_INT_ITERATOR_VALUE(hash_int, it, value);
			}
		}
	}

	else if (test_type == "delete_random_range" ||
			 test_type == "delete_random_full")
	{
		measurements m;
		for (auto& hash_int: int_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_INT(hash_int, keys[i], value);
			}
		}

		std::shuffle(keys.begin(), keys.end(), generator);


		m.set_chrono_start();
		for (auto& hash_int: int_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				DELETE_INT(hash_int, keys[i]);
			}
		}
	}

	else {
		ret = false;
	}

	if (ret) {
		float load_factor_int = 0;
		load_factor_int = LOAD_FACTOR_INT_HASH(int_hashes[0]);
		std::cout << load_factor_int << std::endl;
	}

	for (auto& hash_int: int_hashes) {
		CLEAR_INT(hash_int);
	}
#else
	ret = false;
#endif

	return ret;
}

static std::vector<std::string> generate_string_keys()
{
	if (test_type == "insert_tiny_string" ||
		test_type == "reinsert_tiny_string" ||
		test_type == "insert_tiny_string_reserve" ||
		test_type == "read_tiny_string" ||
		test_type == "read_miss_tiny_string" ||
		test_type == "read_tiny_string_after_delete" ||
		test_type == "delete_tiny_string")
	{
		return get_random_alphanum_strings(
			num_keys, TINY_STRING_MIN_SIZE, TINY_STRING_MAX_SIZE);
	} else if (test_type == "insert_small_string" ||
		test_type == "reinsert_small_string" ||
		test_type == "insert_small_string_reserve" ||
		test_type == "read_small_string" ||
		test_type == "read_miss_small_string" ||
		test_type == "read_small_string_after_delete" ||
		test_type == "delete_small_string")
	{
		return get_random_alphanum_strings(
			num_keys, SMALL_STRING_MIN_SIZE, SMALL_STRING_MAX_SIZE);
	} else if (test_type == "insert_string" ||
			  test_type == "reinsert_string" ||
			  test_type == "insert_string_reserve" ||
			  test_type == "read_string" ||
			  test_type == "read_miss_string" ||
			  test_type == "read_string_after_delete" ||
			  test_type == "delete_string")
	{
		return get_random_alphanum_strings(
			num_keys, STRING_MIN_SIZE, STRING_MAX_SIZE);
	} else if (test_type == "insert_huge_string" ||
		test_type == "reinsert_huge_string" ||
		test_type == "insert_huge_string_reserve" ||
		test_type == "read_huge_string" ||
		test_type == "read_miss_huge_string" ||
		test_type == "read_huge_string_after_delete" ||
		test_type == "delete_huge_string")
	{
		return get_random_alphanum_strings(
			num_keys, HUGE_STRING_MIN_SIZE, HUGE_STRING_MAX_SIZE);
	} else {
		return std::vector<std::string>();
	}
}

static bool process_strings()
{
	bool ret = true;

#ifdef HASH_TYPE_STR
	std::vector<HASH_TYPE_STR> str_hashes { tests_count, CREATE_STR };

#ifdef PREPARE_STR
	for (auto& str_hash: str_hashes) {
		PREPARE_STR(str_hash);
	}
#endif

	std::vector<std::string> keys = generate_string_keys();
	if (keys.empty())
		ret = true;

	if (test_type == "read_miss_tiny_string" ||
		test_type == "read_miss_small_string" ||
		test_type == "read_miss_string" ||
		test_type == "read_miss_huge_string")
	{
		for (auto& str_hash: str_hashes) {
			RESERVE_STR(str_hash, num_keys);
		}
	}

	if (test_type == "insert_tiny_string" ||
		test_type == "insert_small_string" ||
		test_type == "insert_string" ||
		test_type == "insert_huge_string" ||
		test_type == "insert_tiny_string_reserve" ||
		test_type == "insert_small_string_reserve" ||
		test_type == "insert_string_reserve" ||
		test_type == "insert_huge_string_reserve")
	{
		measurements m;
		for (auto& str_hash: str_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_STR(str_hash, keys[i], value);
			}
		}
	}

	else if (test_type == "reinsert_tiny_string" ||
			 test_type == "reinsert_small_string" ||
			 test_type == "reinsert_string" ||
			 test_type == "reinsert_huge_string")
	{
		measurements m;
		for (auto& str_hash: str_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_STR(str_hash, keys[i], value);
			}
		}
		SHUFFLE_STR_ARRAY(keys);


		m.set_chrono_start();
		for (auto& str_hash: str_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_STR(str_hash, keys[i], value);
			}
		}
	}

	else if (test_type == "read_tiny_string" ||
			 test_type == "read_small_string" ||
			 test_type == "read_string" ||
			 test_type == "read_huge_string")
	{
		measurements m;
		for (auto& str_hash: str_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_STR(str_hash, keys[i], 1);
			}
		}

		SHUFFLE_STR_ARRAY(keys);

		std::string s_val; // for leveldb
		std::int64_t i64_val; // for cuckoohash_map
		m.set_chrono_start();
		for (auto& str_hash: str_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				FIND_STR_EXISTING(str_hash, keys[i]);
			}
		}
	}

	else if (test_type == "read_miss_tiny_string" ||
			 test_type == "read_miss_small_string" ||
			 test_type == "read_miss_string" ||
			 test_type == "read_miss_huge_string")
	{
		std::vector<std::string> keys_read;
		keys_read = get_random_alphanum_strings(
				num_keys, STRING_MIN_SIZE, STRING_MAX_SIZE);

		measurements m;
		for (auto& str_hash: str_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_STR(str_hash, keys[i], value);
			}
		}


		std::string s_val; // for kyotocabinet_stash
		std::int64_t i64_val; // for cuckoohash_map
		m.set_chrono_start();
		for (auto& str_hash: str_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				FIND_STR_MISSING(str_hash, keys_read[i]);
			}
		}
	}

	else if (test_type == "read_tiny_string_after_delete" ||
			 test_type == "read_small_string_after_delete" ||
			 test_type == "read_string_after_delete" ||
			 test_type == "read_huge_string_after_delete")
	{
		measurements m;
		for (auto& str_hash: str_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_STR(str_hash, keys[i], value);
			}
		}

		SHUFFLE_STR_ARRAY(keys);
		for (auto& str_hash: str_hashes) {
			for (std::int64_t i = 0; i < num_keys / 2; i++) {
				DELETE_STR(str_hash, keys[i]);
			}
		}
		SHUFFLE_STR_ARRAY(keys);


		std::int64_t nb_found = 0;
		std::string s_val; // for kyotocabinet_stash
		std::int64_t i64_val; // for cuckoohash_map
		m.set_chrono_start();
		for (auto& str_hash: str_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				FIND_STR_EXISTING_COUNT(str_hash, keys[i], nb_found);
			}
		}
	}

	else if (test_type == "delete_tiny_string" ||
			 test_type == "delete_small_string" ||
			 test_type == "delete_string" ||
			 test_type == "delete_huge_string")
	{
		measurements m;
		for (auto& str_hash: str_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				INSERT_STR(str_hash, keys[i], value);
			}
		}

		SHUFFLE_STR_ARRAY(keys);

		m.set_chrono_start();
		for (auto& str_hash: str_hashes) {
			for (std::int64_t i = 0; i < num_keys; i++) {
				DELETE_STR(str_hash, keys[i]);
			}
		}
	}

	else {
		ret = false;
	}

	if (ret) {
		assert(str_hashes.size() > 0);
		std::cout << LOAD_FACTOR_STR_HASH(str_hashes[0]) << std::endl;
	}

	for (auto& str_hash: str_hashes)
		CLEAR_STR(str_hash);
#else
	ret = false;
#endif

	return ret;
}

static void usage(void)
{
	std::cerr << "\
usage: progname [OPTIONS] number_of_keys OPERATION\n\
\n\
where OPERATION is either of the following:\n\
\n\
  insert_random_{range,full}\n\
  reinsert_random_{range,full}\n\
  read_random_{range,full}\n\
  read_miss_random_{range,full}\n\
  insert_random_{range,full}_reserve\n\
  read_random_{range,full}_after_delete\n\
  iteration_random_{range,full}\n\
  delete_random_{range,full}\n\
\n\
  insert_{tiny,small,,huge}_string\n\
  reinsert_{tiny,small,,huge}_string\n\
  insert_{tiny,small,,huge}_string_reserve\n\
  read_{tiny,small,,huge}_string\n\
  read_miss_{tiny,small,,huge}_string\n\
  delete_{tiny,small,,huge}_string\n\
  read_{tiny,small,,huge}_string_after_delete\n\
";
}

int main(int argc, char ** argv)
{
	int opt;
	while ((opt = getopt(argc, argv, "h")) != -1) {
		switch (opt) {
			case 'h':
				usage();
				return 0;
			default:
				usage();
				return EXIT_FAILURE;
		}
	}

	argc -= optind;
	argv += optind;

	if (argc != 2) {
		usage();
		return EXIT_FAILURE;
	}

	num_keys = std::stoll(argv[0]);
	tests_count = std::max(1uL, 1000000uL / num_keys);
	test_type = argv[1];
	value = 1;

	if (!process_integers() && !process_strings()){
		std::cerr << "Unknown test type: " << test_type << ".\n";
		// Do not change the exit status 71! It is used by bench.py
		std::exit(71);
	}
}
