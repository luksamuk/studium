#include <check.h>
#include <unistd.h>

#include "studium/core.h"
#include "studium/macros.h"
#include "studium/display.h"
#include "studium/render.h"
#include <cglm/cglm.h>

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
/*                         Entity and Component System Test                   */
/* ===========================================================================*/

typedef struct {
    mat4 model;
} c_dummy_position;

typedef enum C_DUMMY_COMPONENTS {
    C_POSITION
} c_dummy_c_t;

START_TEST(test_st_entities)
{
    st_gamestate gs = st_gamestate_init();
    st_gamestate_register_component(&gs, C_POSITION, sizeof(c_dummy_position));

    st_entity e = st_entity_new(&gs);
    ck_assert_uint_ne(e, 0);

    // Entity has dummy position component?
    int has_component = st_entity_has_component(&gs, e, C_POSITION);
    ck_assert_int_eq(has_component, 0);

    // Add component, then do stuff to id
    st_entity_add_component(&gs, e, C_POSITION);
    has_component = st_entity_has_component(&gs, e, C_POSITION);
    ck_assert_int_ne(has_component, 0);
    
    st_gamestate_cleanup(&gs);
}
END_TEST

Suite*
entity_components_suite(void)
{
    Suite* s = suite_create("Entities and Components");
    TCase* tc_entities = tcase_create("Entity Creation");
    tcase_add_test(tc_entities, test_st_entities);
    suite_add_tcase(s, tc_entities);
    return s;
}


/* ===========================================================================*/
/*                                  Test Runner                               */
/* ===========================================================================*/

// TODO:
// - Finish porting all matrix tests
//   - Prepare for more when actual graphics stuff comes
// - Test growable array implementation
// - Test entity system implementation

int
main(void)
{
    int failed;
    SRunner* sr;
    
    sr = srunner_create(window_renderer_suite());
    srunner_add_suite(sr, entity_components_suite());
    
    srunner_run_all(sr, CK_VERBOSE);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return failed;
}
