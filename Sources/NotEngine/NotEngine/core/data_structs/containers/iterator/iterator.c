#include <stdlib.h>
#include "iterator.h"

Iterator iterator_next(Iterator it) {
    return it.next(it);
}

Iterator iterator_prev(Iterator it) {
    return it.prev(it);
}

bool iterator_equals(Iterator it1, Iterator it2) {
    return it1.ptr == it2.ptr && it1.container == it2.container;
}

Iterator iterator_advance(Iterator it, int n) {
    Iterator result = it;
    while (n > 0) {
        result = result.next(result);
        n--;
    }
    while (n < 0) {
        result = result.prev(result);
        n++;
    }
    return result;
}

ptrdiff_t iterator_distance(Iterator first, Iterator last) {
    ptrdiff_t n = 0;
    Iterator it = first;
    while (!iterator_equals(it, last)) {
        it = iterator_next(it);
        n++;
    }
    return n;
}

void iterator_get(Iterator it,void* dest) {
     it.get(it,dest);
}

void iterator_set(Iterator it, const void* value) {
    it.set(it, value);
}
