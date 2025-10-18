#include <stdio.h>

struct DefaultStruct {
    char a;
    int b;
    double c;
};

#pragma pack(1)
struct Pack1Struct {
    char a;
    int b;
    double c;
};

#pragma pack(2)
struct Pack2Struct {
    char a;
    int b;
    double c;
};
#pragma pack()

#pragma pack(4)
struct Pack4Struct {
    char a;
    int b;
    double c;
};
#pragma pack()

int main() {
    struct DefaultStruct s_default;
    struct Pack1Struct s_pack1;
    struct Pack2Struct s_pack2;
    struct Pack4Struct s_pack4;

    printf("=== Default Alignment (no #pragma pack) ===\n");
    printf("Size: %zu bytes\n", sizeof(s_default));
    printf("Address of a (char):   %p\n", (void *)&s_default.a);
    printf("Address of b (int):    %p\n", (void *)&s_default.b);
    printf("Address of c (double): %p\n\n", (void *)&s_default.c);

    printf("=== #pragma pack(1) ===\n");
    printf("Size: %zu bytes\n", sizeof(s_pack1));
    printf("Address of a (char):   %p\n", (void *)&s_pack1.a);
    printf("Address of b (int):    %p\n", (void *)&s_pack1.b);
    printf("Address of c (double): %p\n\n", (void *)&s_pack1.c);

    printf("=== #pragma pack(2) ===\n");
    printf("Size: %zu bytes\n", sizeof(s_pack2));
    printf("Address of a (char):   %p\n", (void *)&s_pack2.a);
    printf("Address of b (int):    %p\n", (void *)&s_pack2.b);
    printf("Address of c (double): %p\n\n", (void *)&s_pack2.c);

    printf("=== #pragma pack(4) ===\n");
    printf("Size: %zu bytes\n", sizeof(s_pack4));
    printf("Address of a (char):   %p\n", (void *)&s_pack4.a);
    printf("Address of b (int):    %p\n", (void *)&s_pack4.b);
    printf("Address of c (double): %p\n", (void *)&s_pack4.c);

    return 0;
}
