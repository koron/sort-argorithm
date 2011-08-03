#include <stdint.h>
#include <stdio.h>

    static int
cmp_int_asc(const int* a, const int* b)
{
    return *b - *a;
}

    static void
dump_array(const char* label, int* array, int length)
{
    int i;

    printf("%s:", label);
    for (i = 0; i < length; ++i)
    {
        printf(" %d", array[i]);
    }
    printf("\n");
}

    int
main(int argc, char** argv)
{
    int array[] = { 10, 4, 8, 5, 12, 2, 6, 11, 3, 9, 7, 1, 13 };
    int len = 13;

    heap_sort(array, sizeof(array[0]), len,
            (int (*)(const void*, const void*))cmp_int_asc);

    dump_array("sorted", array, len);

    return 0;
}
