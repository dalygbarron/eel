#include "test/unit.h"
#include <stdio.h>

int unit_testsRun = 0;

static char *testAb() {
    unit_assert("1 should equal 2", 1 == 2);
    return 0;
}

char *allTests() {
    unit_runTest(testAb);
    return 0;
}

int main(int argc, char const **argv) {
    char *result = allTests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", unit_testsRun);
    return result != 0;
}
