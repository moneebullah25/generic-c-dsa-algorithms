#include <criterion/criterion.h>
#include "../includes/c_map.h"
#include "../includes/c_helper.h"

Test(map_test, test_map_int) {
    MapInt *m = malloc(sizeof(MapInt));
    MapNew(m, HashFunctionInt, LinearProbing, DataCompare, FreeData, FreeData);

    MapSet(m, 0, 21);
    MapSet(m, 2, 15);
    MapSet(m, 3, 15);
    MapSet(m, 4, 15);

    int *val = MapGet(m, 2);
    cr_assert_eq(*val, 15);

    MapSet(m, 5, 43);
    val = MapGet(m, 5);
    cr_assert_eq(*val, 43);

    val = MapGet(m, 2);
    *val = 16;
    val = MapGet(m, 2);
    cr_assert_eq(*val, 16);

    MapDelete(m);
}

Test(map_test, test_map_double) {
    MapDouble *m = malloc(sizeof(MapDouble));
    MapNew(m, HashFunctionInt, LinearProbing, DataCompare, FreeData, FreeData);

    MapSet(m, 1.0, 21.25);
    MapSet(m, 2.0, 15.25);
    MapSet(m, 3.0, 15.25);
    MapSet(m, 4.0, 15.25);

    double *val = MapGet(m, 2.0);
    cr_assert_float_eq(*val, 15.25, 0.01);

    MapSet(m, 5.0, 43.0);
    val = MapGet(m, 5.0);
    cr_assert_float_eq(*val, 43.0, 0.01);

    val = MapGet(m, 2.0);
    *val = 16.0;
    val = MapGet(m, 2.0);
    cr_assert_float_eq(*val, 16.0, 0.01);

    MapDelete(m);
}

Test(map_test, test_map_string) {
	MapStringInt *m = malloc(sizeof(Map));
	MapNew(m, HashFunctionStr, LinearProbing, StringCompare, FreeString, FreeData);
	MapSet(m, "Muneeb\0", 21);
	MapSet(m, "Moiz\0", 15);
	MapSet(m, "Moaaz\0", 45);
	MapSet(m, "Arif\0", 75);

	MapIter *iter = MapIterator(m);
	int sum = 0;
	while (MapNext(m, iter)) {
		sum += *(int *)iter->node.value;
	}
	cr_assert_eq(sum, 156);

	MapSet(m, "Kashif\0", 43);
	iter = MapIterator(m);
	sum = 0;
	while (MapNext(m, iter)) {
		sum += *(int *)iter->node.value;
	}
	cr_assert_eq(sum, 199);

	void *age = MapGet(m, "Moiz\0");
	*(int *)age = 16;

	iter = MapIterator(m);
	sum = 0;
	while (MapNext(m, iter)) {
		sum += *(int *)iter->node.value;
	}
	cr_assert_eq(sum, 200);

	MapDelete(m);
}