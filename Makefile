build: heap_sort

tags:
	ctags *.c

clean:
	rm -f *.o a.out
	rm -f heap_sort

heap_sort: main.o swap.o heap_sort.o
