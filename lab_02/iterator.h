#ifndef ITERATOR_H
#define ITERATOR_H

#include "list.h"

struct Iterator {
    Node* current;
};

Iterator begin(const List& list);
Iterator end(const List& list);
int next(Iterator& it);
int isSet(const Iterator& it);


#endif // ITERATOR_H
