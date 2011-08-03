#include <stddef.h>
#include "swap.h"

#define SWAP(a, b, c)           swap(a, b, c)
#define COMPARE(s, a, b)        (*(s)->compare)(a, b)

typedef struct sort_t {
    char* head;
    size_t size;
    size_t count;
    int (*compare)(const void*, const void*);
} sort_t;

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

            if (COMPARE(s, item1, item2) > 0)
            {
                int index = index1;
                char* item = item1;
                index1 = index2;
                index2 = index;
                item1 = item2;
                item2 = item;
            }

            if (COMPARE(s, item0, item1) > 0)
            {
                SWAP(item0, item1, s->size);
                i = index1;
                continue;
            }
            else if (COMPARE(s, item0, item2) > 0)
            {
                SWAP(item0, item2, s->size);
                i = index2;
                continue;
            }
        }
        else if (index1 < s->count)
        {
            char* item0 = s->head + i * s->size;
            char* item1 = s->head + index1 * s->size;
            if (COMPARE(s, item0, item1) > 0)
            {
                SWAP(item0, item1, s->size);
            }
        }

        break;
    }
}

    void
heap_sort(
        void* base,
        size_t size,
        size_t count,
        int (*compare)(const void*, const void*))
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
