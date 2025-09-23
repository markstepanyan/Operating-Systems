#include <stdio.h>
#include <stdlib.h>

void function1() {
    printf("Function 1: \n");
}

void function2() {
    printf("Function 2: \n");
}

int main() {
    atexit(function1);
    atexit(function2);

    return 0;
}

