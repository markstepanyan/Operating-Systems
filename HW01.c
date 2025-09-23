#include <stdio.h>


//  Basics of Pointers
void Assignment_1 () {
    int a = 7;
    int *p = &a;
    
    printf("This is the variable version (&a): %p\n", &a);
    printf("This is the pointer version (*p):   %p\n", p);

    *p = 77;
    
    printf("After modifying the value: %d\n", *p);
}


// Pointer Arithmetic
void Assignment_2 () {
    int array[5] = {1, 3, 5, 7, 9};
    int *p = array;

    printf("Initial Array: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", *(p + i));
    }

    for (int i = 0; i < 5; i++)
    {
        *(p + i) += 5;
    }
    printf("\n");
    
    printf("Modified with pointer: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(p + i));        // print using the pointer expression again
    }
    printf("\n");

    printf("Modified with array: ");
    for (int i = 0; i < 5; ++i) {
        printf("%d ", array[i]);          // print using array indexing
    }
    printf("\n");
}


// Swap function 
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


// Pointers to Pointers
void Assignment_4 () {
    int n = 25;
    int *p = &n;
    int **pp = &p;

    printf("Value with pointer: %d\n", *p);
    printf("Value with double-pointer: %d\n", **pp);

    **pp += 10;
    printf("After change through double-pointer: %d\n", n);
}


// Strings and Character Pointers
void Assignment_5 () {
    char str[] = "Hello";
    char *p = str;

    printf("String with pointer: ");
    while (*p) {
        putchar(*p);
        p++;
    }
    printf("\n");

    int length = (int)(p - str);
    printf("Length: %d\n", length);
}


int main () {
    printf("Assignment_1");
    printf("\n");
    Assignment_1();

    printf("Assignment_2");
    printf("\n");
    Assignment_2();


    printf("Assignment_3");
    printf("\n");

    int x = 10;
    int y = 42;

    printf("Before: x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("After:  x = %d, y = %d\n", x, y);


    printf("Assignment_4");
    printf("\n");
    Assignment_4();

    printf("Assignment_5");
    printf("\n");
    Assignment_5();

    return 0;
}
