#include <criterion/criterion.h>
#include "../includes/c_avltree.h"
#include "../includes/c_helper.h"
#include <stdlib.h>

Test(avltree_test, test_avltree_int)
{
    AvlTreeInt *avltree = malloc(sizeof(AvlTreeInt));
    AvlTreeNew(avltree, IntDataCompare, FreeData);
    cr_assert(AvlTreeEmpty(avltree), "Expected avltree to be empty");

    AvlTreeInsert(avltree, 5);
    AvlTreeInsert(avltree, 4);
    AvlTreeInsert(avltree, 6);
    AvlTreeInsert(avltree, 2);
    AvlTreeInsert(avltree, 7);
    AvlTreeInsert(avltree, 3);
    AvlTreeInsert(avltree, 1);

    cr_assert_eq(AvlTreeSize(avltree), 7, "Expected avltree size to be 7");

    cr_assert(AvlTreeContains(avltree, 5), "Expected avltree to contain 5");
    cr_assert(AvlTreeContains(avltree, 7), "Expected avltree to contain 7");
    cr_assert_not(AvlTreeContains(avltree, 9), "Expected avltree not to contain 9");

    AvlTreeRemove(avltree, 2);
    AvlTreeRemove(avltree, 5);

    cr_assert_eq(AvlTreeSize(avltree), 5, "Expected avltree size to be 5 after removing elements");

    cr_assert(AvlTreeContains(avltree, 6), "Expected avltree to contain 6 after removing element");
    cr_assert_not(AvlTreeContains(avltree, 2), "Expected avltree not to contain 2 after removing it");

    cr_assert_eq(*(int *)AvlTreeMin(avltree), 1, "Expected minimum element to be 1");
    cr_assert_eq(*(int *)AvlTreeMax(avltree), 7, "Expected maximum element to be 7");

    AvlTreeClear(avltree);

    cr_assert(AvlTreeEmpty(avltree), "Expected avltree to be empty after clearing");

    AvlTreeDelete(avltree);
}

Test(avltree_test, test_avltree_double)
{
    AvlTreeDouble *avltree = malloc(sizeof(AvlTreeDouble));
    AvlTreeNew(avltree, DoubleDataCompare, FreeData);
    cr_assert(AvlTreeEmpty(avltree), "Expected avltree to be empty");

    AvlTreeInsert(avltree, 5.25);
    AvlTreeInsert(avltree, 4.25);
    AvlTreeInsert(avltree, 6.25);
    AvlTreeInsert(avltree, 2.25);
    AvlTreeInsert(avltree, 7.25);
    AvlTreeInsert(avltree, 3.25);
    AvlTreeInsert(avltree, 1.25);

    cr_assert_eq(AvlTreeSize(avltree), 7, "Expected avltree size to be 7");

    cr_assert(AvlTreeContains(avltree, 5.25), "Expected avltree to contain 5.25");
    cr_assert(AvlTreeContains(avltree, 7.25), "Expected avltree to contain 7.25");
    cr_assert_not(AvlTreeContains(avltree, 9.25), "Expected avltree not to contain 9.25");

    AvlTreeRemove(avltree, 2.25);
    AvlTreeRemove(avltree, 5.25);

    cr_assert_eq(AvlTreeSize(avltree), 5, "Expected avltree size to be 5 after removing elements");

    cr_assert(AvlTreeContains(avltree, 6.25), "Expected avltree to contain 6.25 after removing element");
    cr_assert_not(AvlTreeContains(avltree, 2.25), "Expected avltree not to contain 2.25 after removing it");

    cr_assert_eq(*(double *)AvlTreeMin(avltree), 1.25, "Expected minimum element to be 1.25");
    cr_assert_eq(*(double *)AvlTreeMax(avltree), 7.25, "Expected maximum element to be 7.25");

    AvlTreeClear(avltree);

    cr_assert(AvlTreeEmpty(avltree), "Expected avltree to be empty after clearing");

    AvlTreeDelete(avltree);
}

Test(avltree_test, test_avltree_string)
{
    AvlTreeString *avltree = malloc(sizeof(AvlTreeString));
    AvlTreeNew(avltree, StringCompare, FreeString);
    cr_assert(AvlTreeEmpty(avltree), "Expected avltree to be empty");

    AvlTreeInsert(avltree, "hello");
    AvlTreeInsert(avltree, "world");
    AvlTreeInsert(avltree, "this");
    AvlTreeInsert(avltree, "is");
    AvlTreeInsert(avltree, "a");
    AvlTreeInsert(avltree, "test");

    cr_assert_eq(AvlTreeSize(avltree), 6, "Expected avltree size to be 6");

    cr_assert(AvlTreeContains(avltree, "hello"), "Expected avltree to contain 'hello'");
    cr_assert(AvlTreeContains(avltree, "test"), "Expected avltree to contain 'test'");
    cr_assert_not(AvlTreeContains(avltree, "notfound"), "Expected avltree not to contain 'notfound'");

    AvlTreeRemove(avltree, "this");
    AvlTreeRemove(avltree, "test");

    cr_assert_eq(AvlTreeSize(avltree), 4, "Expected avltree size to be 4 after removing elements");

    cr_assert(AvlTreeContains(avltree, "hello"), "Expected avltree to contain 'hello' after removing elements");
    cr_assert_not(AvlTreeContains(avltree, "test"), "Expected avltree not to contain 'test' after removing it");

    cr_assert_str_eq((char *)AvlTreeMin(avltree), "a", "Expected minimum element to be 'a'");
    cr_assert_str_eq((char *)AvlTreeMax(avltree), "world", "Expected maximum element to be 'world'");

    AvlTreeClear(avltree);

    cr_assert(AvlTreeEmpty(avltree), "Expected avltree to be empty after clearing");

    AvlTreeDelete(avltree);
}
