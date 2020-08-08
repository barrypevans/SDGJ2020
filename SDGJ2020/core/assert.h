#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(val, msg, ...) if(!(val)){printf(msg, __VA_ARGS__); exit(1);};