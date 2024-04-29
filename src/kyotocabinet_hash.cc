#include <string>
#include <kchashdb.h>
#include <stdlib.h>

#include "kyotocabinet.h"

static const std::string kDBPathPrefix = "/tmp/kyotocabinet_hash.dat";

#define HASH_TYPE_STR str_hash_t<kyotocabinet::HashDB>

#define CREATE_STR

#define PREPARE_STR(str_hash) str_hash.initdb(kDBPathPrefix);

#include "template.cc"
