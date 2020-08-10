#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
#define ASSERT(val, msg, ...) if(!(val)){printf(msg, __VA_ARGS__); exit(1);};
#else
#define ASSERT(val, msg, ...) if(!(val)){exit(1);}
#endif