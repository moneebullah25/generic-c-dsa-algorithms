#include <criterion/criterion.h>
#include "../includes/c_map.h"

Test(MapInt, test_map_int) {
    MapInt *m = malloc(sizeof(MapInt));
    MapNew(m, HashFunctionInt, LinearProbing, DataCompare, FreeData, FreeData);

    MapSet(m, 0, 21);
    MapSet(m, 2, 15);
    MapSet(m, 3, 15);
    MapSet(m, 4, 15);

    int *val = MapGet(m, 2);
    assert_int_equal(*val, 15);

    MapSet(m, 5, 43);
    val = MapGet(m, 5);
    assert_int_equal(*val, 43);

    val = MapGet(m, 2);
    *val = 16;
    val = MapGet(m, 2);
    assert_int_equal(*val, 16);

    MapDelete(m);
}

Test(MapDouble, test_map_double) {
    MapDouble *m = malloc(sizeof(MapDouble));
    MapNew(m, HashFunctionInt, LinearProbing, DataCompare, FreeData, FreeData);

    MapSet(m, 1.0, 21.25);
    MapSet(m, 2.0, 15.25);
    MapSet(m, 3.0, 15.25);
    MapSet(m, 4.0, 15.25);

    double *val = MapGet(m, 2.0);
    assert_double_equal(*val, 15.25, 0.01);

    MapSet(m, 5.0, 43.0);
    val = MapGet(m, 5.0);
    assert_double_equal(*val, 43.0, 0.01);

    val = MapGet(m, 2.0);
    *val = 16.0;
    val = MapGet(m, 2.0);
    assert_double_equal(*val, 16.0, 0.01);

    MapDelete(m);
}
