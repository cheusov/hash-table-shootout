#include <inttypes.h>
#include <string>
#include <memory>
#include "folly/container/F14Map.h"

typedef folly::F14ValueMap<int64_t, int64_t, std::hash<int64_t>> hash_t;
typedef folly::F14ValueMap<std::string,int64_t, std::hash<std::string>> str_hash_t;

#include "hash_map_int_base.h"
#include "hash_map_str_base.h"

#include "template.cc"
