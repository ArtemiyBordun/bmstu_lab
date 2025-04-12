#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "regiondata.h"

struct Node {
    RegionData data;
    Node* next;
};

struct List {
    Node* head;
    Node* tail;
    unsigned size;
};

List* init(RegionData data);
void next(List* list);
int hasNext(List* list);
void pushBack(List* head, RegionData data);
List* filterList(List* list, char* regionName);

void clearList(List* list);
void deleteList(List* list);

#endif // LIST_H
