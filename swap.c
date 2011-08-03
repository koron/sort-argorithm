#include <stddef.h>

    void
swap(char* a, char* b, size_t size)
{
    char* e;
    for (e = a + size; a < e; ++a, ++b)
    {
        char tmp = *b;
        *b = *a;
        *a = tmp;
    }
}
