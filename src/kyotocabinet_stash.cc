#include <string>
#include <kcstashdb.h>
#include <stdlib.h>

#include "kyotocabinet.h"

static const std::string kDBPathPrefix = "/tmp/kyotocabinet_stash.dat";

#define HASH_TYPE_STR str_hash_t<kyotocabinet::StashDB>

#define CREATE_STR

#define PREPARE_STR(str_hash) str_hash.initdb(kDBPathPrefix);

#include "template.cc"
