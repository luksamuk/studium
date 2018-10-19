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
/*                                  Test Runner                               */
/* ===========================================================================*/

int
main(void)
{
    int failed;

    Suite* s;
    SRunner* sr;

    // Window and renderer test suite
    s  = window_renderer_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    // Math test suite
    
    return failed;
}
