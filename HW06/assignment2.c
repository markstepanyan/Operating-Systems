#include <stdio.h>

struct struct1 {
    char a;
    int b;
    double c;
};

struct struct2 {
    int x;
    double y;
    char z;
};

int main() {
    struct struct1 a1;
    struct struct2 a2;

    printf("=== Structure Example 1 (char, int, double) ===\n");
    printf("Total size: %d bytes\n", (int)sizeof(a1));
    printf("Address of 'a' (char):   %p\n", (void *)&a1.a);
    printf("Address of 'b' (int):    %p\n", (void *)&a1.b);
    printf("Address of 'c' (double): %p\n", (void *)&a1.c);

    printf("\n=== Structure Example 2 (int, double, char) ===\n");
    printf("Total size: %d bytes\n", (int)sizeof(a2));
    printf("Address of 'x' (int):    %p\n", (void *)&a2.x);
    printf("Address of 'y' (double): %p\n", (void *)&a2.y);
    printf("Address of 'z' (char):   %p\n", (void *)&a2.z);

    return 0;
}
