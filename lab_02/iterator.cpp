#include "iterator.h"

Iterator begin(const List& list) {
    Iterator iterator = { .current = list.head };
    return iterator;
}

Iterator end(const List& list) {
    Iterator iterator = { list.tail };
    return iterator;
}

int next(Iterator& it) {
    return it.current ? (it.current = it.current->next, 1) : 0;
}

int set(Iterator& it, List* list) {
    if (!it.current)
        return 0;

    it.current->data = list->head->data;
    return 1;
}
