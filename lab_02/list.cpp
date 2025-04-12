#include "list.h"

List* init(RegionData data) {
    Node* root = (Node*)malloc(sizeof(Node));
    root->data = data;
    root->next = NULL;

    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = root;

    return list;
}

int hasNext(List* list) {
    return list->head == NULL ? 0 : 1;
}

void next(List* list) {
    if (hasNext(list))
        list->head = list->head->next;
}

void pushBack(List* list, RegionData data) {
    Node* node = (Node*)malloc(sizeof(Node));   //сохранить в лист
    node->data = data;
    node->next = NULL;
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
     }
     else {
        list->tail->next = node;
        list->tail = node;
    }
}

List* filterList(List* list, char* regionName) {
    List* listLocale = (List*)malloc(sizeof(List));
    listLocale->head = list->head;
    List* listRegion;
    do {
        if (!strcmp(regionName, listLocale->head->data.region)) {
            listRegion = init(listLocale->head->data);      //передвигаем список на первую строку с указанным регионом
            next(list);
            break;
         }
        listLocale->head = listLocale->head->next;
    } while (hasNext(listLocale));

    while (hasNext(listLocale)) {
        if (!strcmp(regionName, listLocale->head->data.region)) {
            pushBack(listRegion, listLocale->head->data);
        }
        next(listLocale);
    }
    free(listLocale);
    return listRegion;
}

void clearList(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    next(list);

}

void deleteList(List* list) {
    if (list->head != NULL) {
        List* p = (List*)malloc(sizeof(List));
        p->head = list->head;
        while (p->head->next) {
            List* temp = (List*)malloc(sizeof(List));
            temp->head = p->head;
            next(p);
            free(temp);
        }
        free(p);
        free(list);
    }
}
