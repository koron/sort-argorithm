#include <stdint.h>
#include <stdio.h>

typedef (*cmpfunc_t)(const void*, const void*);

typedef struct sort_t {
    char* head;
    size_t size;
    size_t count;
    cmpfunc_t compare;
    char* tail;
} sort_t;

    static void
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

    static void
make_heap(
        const sort_t* s,
        int index0)
{
    int index1 = index0 * 2 + 1;
    int index2 = index1 + 1;

    if (index2 < s->count)
    {
        char* item0 = s->head + index0 * s->size;
        char* item1 = s->head + index1 * s->size;
        char* item2 = item1 + s->size;

        make_heap(s, index1);
        make_heap(s, index2);

        if ((*s->compare)(item1, item2) > 0)
        {
            index1 = index2;
            item1 = item2;
        }

        if ((*s->compare)(item0, item1) > 0)
        {
            swap(item0, item1, s->size);
            make_heap(s, index1);
        }
    }
    else if (index1 < s->count)
    {
        char* item0 = s->head + index0 * s->size;
        char* item1 = s->head + index1 * s->size;
        if ((*s->compare)(item0, item1) > 0)
        {
            swap(item0, item1, s->size);
        }
    }
}

    void
heap_sort(
        void* base,
        size_t size,
        size_t count,
        cmpfunc_t compare)
{
    sort_t s;

    s.head = (char*)base;
    s.size = size;
    s.count = count;
    s.compare = compare;
    s.tail = s.head + size * (count - 1);

    for (; s.head < s.tail; s.tail -= s.size)
    {
        make_heap(&s, 0);
        swap(s.head, s.tail, s.size);
        s.count -= 1;
    }
}

    static int
cmp_int_asc(const int* a, const int* b)
{
    return *b - *a;
}

    int
main(int argc, char** argv)
{
    int i;
    int array[] = { 10, 4, 8, 5, 12, 2, 6, 11, 3, 9, 7, 1 };

    heap_sort(array, sizeof(array[0]), 12, (cmpfunc_t)cmp_int_asc);

    printf("array:");
    for (i = 0; i < 12; ++i)
    {
        printf(" %d", array[i]);
    }
    printf("\n");

    return 0;
}
