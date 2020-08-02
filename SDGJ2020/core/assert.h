#pragma once
#include <assert.h>
#define ASSERT(val, msg, ...) if(!(val)){printf(msg, __VA_ARGS__);} assert(val);