#include "buf.h"

#test test_capacity_and_size_init
	float *a = 0;
	ck_assert_msg(buf_capacity(a) == 0, "test_capacity_init");
	ck_assert_msg(buf_size(a) == 0, "test_size_init");

#test test_size_1_and_value
	float *a = 0;
	buf_push(a, 1.3f);
	ck_assert_msg(buf_size(a) == 1, "test_size_1");
	ck_assert_msg(a[0] == (float)1.3f, "test_value");
	buf_free(a);

#test test_clear_and_clear_not_free
	float *a = 0;
	buf_push(a, 1.3f);
	buf_clear(a);
	ck_assert_msg(buf_size(a) == 0, "test_clear");
	ck_assert_msg(a != 0, "test_clear_not_free");
	buf_free(a);

#test test_free
	float *a = 0;
	buf_push(a, 1.3f);
	buf_free(a);
	ck_assert_msg(a == 0, test_free);

#test test_clear_empty_and_clear_no_op
	float *a = 0;
	buf_push(a, 1.3f);
	buf_free(a);
	buf_clear(a);
	ck_assert_msg(buf_size(a) == 0, "test_clear_empty");
	ck_assert_msg(a == 0, "test_clear_no_op");

#test test_size_and_match
	long *ai = 0;
	for (int i = 0; i < 10000; i++)
		buf_push(ai, i);
	ck_assert_msg(buf_size(ai) == 10000, "test_size_10000");
	int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
	ck_assert_msg(match == 10000, "test_match_10000");
	buf_free(ai);

#test test_grow_and_trunc
	long *ai = 0;
	buf_grow(ai, 1000);
	ck_assert_msg(buf_capacity(ai) == 1000, "test_row_1000");
	ck_assert_msg(buf_size(ai) == 0, "test_size_0_grow");
	buf_trunc(ai, 100);
	ck_assert_msg(buf_capacity(ai) == 100, "test_trunc_100");
	buf_free(ai);

#test test_pop_and_trunc
	float *a = 0;
	buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
	ck_assert_msg(buf_size(a) == 4, "test_size_4");
	ck_assert_msg(buf_pop(a) == (float)1.4f, "test_pop_3");
	buf_trunc(a, 3);
	ck_assert_msg(buf_size(a) == 3, "test_size_3");
	ck_assert_msg(buf_pop(a) == (float)1.3f, "test_pop_2");
	ck_assert_msg(buf_pop(a) == (float)1.2f, "test_pop_1");
	ck_assert_msg(buf_pop(a) == (float)1.1f, "test_pop_1");
	ck_assert_msg(buf_size(a) == 0, "test_size_0_pop");
	buf_free(a);
