#include <criterion/criterion.h>
#include "../includes/c_tree.h"
#include "../includes/c_helper.h"
#include <stdlib.h>

Test(tree_test, test_tree_int)
{
    TreeInt *tree = malloc(sizeof(TreeInt));
    TreeNew(tree, IntDataCompare, FreeData);
    cr_assert(TreeEmpty(tree), "Expected tree to be empty");

    TreeInsert(tree, 5);
    TreeInsert(tree, 4);
    TreeInsert(tree, 6);
    TreeInsert(tree, 2);
    TreeInsert(tree, 7);
    TreeInsert(tree, 3);
    TreeInsert(tree, 1);

    cr_assert_eq(TreeSize(tree), 7, "Expected tree size to be 7");

    cr_assert(TreeContains(tree, 5), "Expected tree to contain 5");
    cr_assert(TreeContains(tree, 7), "Expected tree to contain 7");
    cr_assert_not(TreeContains(tree, 9), "Expected tree not to contain 9");

    TreeRemove(tree, 2);
    TreeRemove(tree, 5);

    cr_assert_eq(TreeSize(tree), 5, "Expected tree size to be 5 after removing elements");

    cr_assert(TreeContains(tree, 6), "Expected tree to contain 6 after removing element");
    cr_assert_not(TreeContains(tree, 2), "Expected tree not to contain 2 after removing it");

    cr_assert_eq(*(int *)TreeMin(tree), 1, "Expected minimum element to be 1");
    cr_assert_eq(*(int *)TreeMax(tree), 7, "Expected maximum element to be 7");

    TreeClear(tree);

    cr_assert(TreeEmpty(tree), "Expected tree to be empty after clearing");

    TreeDelete(tree);
}

Test(tree_test, test_tree_double)
{
    TreeDouble *tree = malloc(sizeof(TreeDouble));
    TreeNew(tree, DoubleDataCompare, FreeData);
    cr_assert(TreeEmpty(tree), "Expected tree to be empty");

    TreeInsert(tree, 5.25);
    TreeInsert(tree, 4.25);
    TreeInsert(tree, 6.25);
    TreeInsert(tree, 2.25);
    TreeInsert(tree, 7.25);
    TreeInsert(tree, 3.25);
    TreeInsert(tree, 1.25);

    cr_assert_eq(TreeSize(tree), 7, "Expected tree size to be 7");

    cr_assert(TreeContains(tree, 5.25), "Expected tree to contain 5.25");
    cr_assert(TreeContains(tree, 7.25), "Expected tree to contain 7.25");
    cr_assert_not(TreeContains(tree, 9.25), "Expected tree not to contain 9.25");

    TreeRemove(tree, 2.25);
    TreeRemove(tree, 5.25);

    cr_assert_eq(TreeSize(tree), 5, "Expected tree size to be 5 after removing elements");

    cr_assert(TreeContains(tree, 6.25), "Expected tree to contain 6.25 after removing element");
    cr_assert_not(TreeContains(tree, 2.25), "Expected tree not to contain 2.25 after removing it");

    cr_assert_float_eq(*(double *)TreeMin(tree), 1.25, 0.01, "Expected minimum element to be 1.25");
    cr_assert_float_eq(*(double *)TreeMax(tree), 7.25, 0.01, "Expected maximum element to be 7.25");

    TreeClear(tree);

    cr_assert(TreeEmpty(tree), "Expected tree to be empty after clearing");

    TreeDelete(tree);
}

Test(tree_test, test_tree_string)
{
    TreeString *tree = malloc(sizeof(TreeString));
    TreeNew(tree, StringCompare, FreeString);
    cr_assert(TreeEmpty(tree), "Expected tree to be empty");

    TreeInsert(tree, "hello");
    TreeInsert(tree, "world");
    TreeInsert(tree, "this");
    TreeInsert(tree, "is");
    TreeInsert(tree, "a");
    TreeInsert(tree, "test");

    cr_assert_eq(TreeSize(tree), 6, "Expected tree size to be 6");

    cr_assert(TreeContains(tree, "hello"), "Expected tree to contain 'hello'");
    cr_assert(TreeContains(tree, "test"), "Expected tree to contain 'test'");
    cr_assert_not(TreeContains(tree, "notfound"), "Expected tree not to contain 'notfound'");

    TreeRemove(tree, "this");
    TreeRemove(tree, "test");

    cr_assert_eq(TreeSize(tree), 4, "Expected tree size to be 4 after removing elements");

    cr_assert(TreeContains(tree, "hello"), "Expected tree to contain 'hello' after removing elements");
    cr_assert_not(TreeContains(tree, "test"), "Expected tree not to contain 'test' after removing it");

    cr_assert_str_eq(*(char **)TreeMin(tree), "a", "Expected minimum element to be 'a'");
    cr_assert_str_eq(*(char **)TreeMax(tree), "world", "Expected maximum element to be 'world'");

    TreeClear(tree);

    cr_assert(TreeEmpty(tree), "Expected tree to be empty after clearing");

    TreeDelete(tree);
}
