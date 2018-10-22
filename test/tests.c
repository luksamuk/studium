#include <check.h>
#include <unistd.h>

#include "studium/core.h"
#include "studium/macros.h"
#include "studium/display.h"
#include "studium/render.h"
#include "studium/stmath.h"

// Documentation for testing:
// https://libcheck.github.io/check/doc/doxygen/html/check_8h.html
// https://libcheck.github.io/check/doc/check_html/check_3.html
// https://cmake.org/cmake/help/v3.0/command/add_test.html


/* ===========================================================================*/
/*                           Window and Renderer                              */
/* ===========================================================================*/

START_TEST(test_st_window)
{
    ck_assert_int_eq(st_init(), 0);

    st_window window;
    window = st_create_window(500, 500, "test_st_window");

    ck_assert_ptr_nonnull(window.hnd);
    ck_assert_int_eq(window.height, 500);
    ck_assert_int_eq(window.width,  500);

    ck_assert_int_eq(st_cleanup(), 0);
}
END_TEST

START_TEST(test_st_context)
{
    st_init();

    st_window window = st_create_window(500, 500, "test_st_context");
    st_window_init_renderer(&window);

    // Alloc/dealloc test texture
    st_texture img;
    img = st_texture_load("res/box.png");
    ck_assert_int_ne(img.id, 0);
    
    st_texture_unload(&img);
    ck_assert_int_eq(img.id, 0);
    
    st_cleanup();
}
END_TEST


Suite*
window_renderer_suite(void)
{
    Suite* s = suite_create("Window and Renderer");

    TCase* tc1 = tcase_create("Window Creation");
    tcase_add_test(tc1, test_st_window);

    TCase* tc2 = tcase_create("Renderer Manipulation");
    tcase_add_test(tc2, test_st_context);
    
    suite_add_tcase(s, tc1);
    suite_add_tcase(s, tc2);
    return s;
}

/* ===========================================================================*/
/*                           Matrix and Vector Test                           */
/* ===========================================================================*/

// Helper function
static int
compare_array(const float* array, const float* expected, size_t size)
{
    size_t i;
    for(i = 0; i < size; i++)
	if(array[i] != expected[i])
	    return 1;
    return 0;
}

// Helper macro
#define assert_array_ok(arr1, expect, sz)		\
    ck_assert_int_eq(compare_array((float*)&arr1,	\
				   expect,		\
				   sz),			\
		     0)

START_TEST(test_st_2dvectors)
{
    st_vec2 v2d_1 = st_vec2_zero();
    st_vec2 v2d_2 = st_vec2_one();
    st_vec2 v2d_3 = st_vec2_new((float[2]) {8.0f, 6.0f});

    // Test 2D vector creation
    {
	const float* expect_1 = (float[2]){0.0f, 0.0f};
	const float* expect_2 = (float[2]){1.0f, 1.0f};
	const float* expect_3 = (float[2]){8.0f, 6.0f};
    
	assert_array_ok(v2d_1, expect_1, 2);
	assert_array_ok(v2d_2, expect_2, 2);
	assert_array_ok(v2d_3, expect_3, 2);
    }

    // Test 2D vector arithmetic

    // Sum
    {
	st_vec2 sum = st_vec2_sum(v2d_2, v2d_3);
	const float* expect = (float[2]){9.0f, 7.0f};
	assert_array_ok(sum, expect, 2);
    }

    // Subtract
    {
	st_vec2 sub = st_vec2_sub(v2d_2, v2d_3);
	const float* expect = (float[2]){-7.0f, -5.0f};
	assert_array_ok(sub, expect, 2);
    }

    // Negate

    // Scalar multiplication

    // Cross multiplication
    // Algorithm applies to all kinds of matrices
    {
	st_mat2 mat1, mat2;
	
	// Copy these values to the matrices
	{
	    const float* buf = (float[4]){ 1.0f, 4.0f,
					   3.0f, 3.0f  };
	    size_t i;
	    for(i = 0; i < 4; i++) {
		mat1.A[i] = mat2.A[i] = buf[i];
	    }
	}

	const float* expect = (float[4]){ 13.0f, 16.0f,
					  12.0f, 21.0f  };
	st_mat2 result = st_mat2_mult(&mat1, &mat2);
	assert_array_ok(result.A, expect, 4);
    }

    // TODO: more tests
    
}
END_TEST

Suite*
vector_matrix_suite(void)
{
    Suite* s = suite_create("Vectors and Matrices");

    TCase* tc_vectors = tcase_create("Vector Operations");
    tcase_add_test(tc_vectors, test_st_2dvectors);

    suite_add_tcase(s, tc_vectors);
    return s;
}


/* ===========================================================================*/
/*                                  Test Runner                               */
/* ===========================================================================*/

int
main(void)
{
    int failed;
    SRunner* sr;
    
    sr = srunner_create(window_renderer_suite());
    srunner_add_suite(sr, vector_matrix_suite());
    srunner_run_all(sr, CK_VERBOSE);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return failed;
}
