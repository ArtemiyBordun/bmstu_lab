#include "list.h"

template<typename T>
List<T>::List() {
    size = 0;
    head = nullptr;
}

template<typename T>
List<T>::~List() {
    delete List<T>();
}

template<typename T>
void List<T>::pushBack(T data) {
    if (head == nullptr)
        head = new Node<T>(data);
    else {
        Node<T>* current = this->head;

        while (current->next != nullptr)
            current = current->next;
        current->next = new Node<T>(data);
    }
    size++;
}

template<typename T>
int List<T>::getSize() {
    return size;
}
