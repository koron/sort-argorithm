#include <stdint.h>
#include <stdio.h>

typedef (*cmpfunc_t)(const void*, const void*);

typedef struct sort_t {
    char* head;
    size_t size;
    size_t count;
    cmpfunc_t compare;
} sort_t;

static int count_compare = 0;
static int count_swap = 0;

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
    ++count_swap;
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
insert_heap(
        const sort_t* s,
        int index)
{
    int i;

    for (i = index; i < s->count; )
    {
        int index1 = i * 2 + 1;
        int index2 = index1 + 1;

        if (index2 < s->count)
        {
            char* item0 = s->head + i * s->size;
            char* item1 = s->head + index1 * s->size;
            char* item2 = item1 + s->size;

            if ((*s->compare)(item1, item2) > 0)
            {
                int index = index1;
                char* item = item1;
                index1 = index2;
                index2 = index;
                item1 = item2;
                item2 = item;
            }

            if ((*s->compare)(item0, item1) > 0)
            {
                swap(item0, item1, s->size);
                i = index1;
                continue;
            }
            else if ((*s->compare)(item0, item2) > 0)
            {
                swap(item0, item2, s->size);
                i = index2;
                continue;
            }
        }
        else if (index1 < s->count)
        {
            char* item0 = s->head + i * s->size;
            char* item1 = s->head + index1 * s->size;
            if ((*s->compare)(item0, item1) > 0)
            {
                swap(item0, item1, s->size);
            }
        }

        break;
    }
}

    void
heap_sort1(
        void* base,
        size_t size,
        size_t count,
        cmpfunc_t compare)
{
    sort_t s;
    char* tail;

    s.head = (char*)base;
    s.size = size;
    s.count = count;
    s.compare = compare;

    for (tail = s.head + size * (count - 1); s.head < tail; tail -= s.size)
    {
        make_heap(&s, 0);
        swap(s.head, tail, s.size);
        s.count -= 1;
    }
}

    void
heap_sort2(
        void* base,
        size_t size,
        size_t count,
        cmpfunc_t compare)
{
    sort_t s;
    char* tail;

    s.head = (char*)base;
    s.size = size;
    s.count = count;
    s.compare = compare;

    /* Make heap. */
    {
        int i;
        for (i = count - 1; i >= 0; --i) {
            insert_heap(&s, i);
        }
    }

    for (tail = s.head + size * (count - 1); s.head < tail; tail -= s.size)
    {
        swap(s.head, tail, s.size);
        s.count -= 1;
        insert_heap(&s, 0);
    }
}


    static int
cmp_int_asc(const int* a, const int* b)
{
    ++count_compare;
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

    heap_sort2(array, sizeof(array[0]), 13, (cmpfunc_t)cmp_int_asc);

    dump_array("sorted", array, 13);
    printf("compare=%d swap=%d\n", count_compare, count_swap);

    return 0;
}
