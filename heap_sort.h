#ifndef HEAP_SORT_H__
#define HEAP_SORT_H__

#ifdef __cplusplus
extern "C" {
#endif

void heap_sort(
        void* base,
        size_t size,
        size_t count,
        int (*compare)(const void*, const void*));

#ifdef __cplusplus
}
#endif

#endif/*HEAP_SORT_H__*/
