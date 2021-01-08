#include "buf.h"

#test test_capacity_init
	float *a = 0;
	ck_assert(buf_capacity(a) == 0);
