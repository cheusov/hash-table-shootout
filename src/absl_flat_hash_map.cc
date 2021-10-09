#include <inttypes.h>
#include <string>
#include <memory>
#include "absl/container/flat_hash_map.h"

typedef absl::flat_hash_map<int64_t, int64_t, std::hash<int64_t>> hash_t;
typedef absl::flat_hash_map<std::string,int64_t, std::hash<std::string>> str_hash_t;

#include "hash_map_int_base.h"
#include "hash_map_str_base.h"

#include "template.cc"
