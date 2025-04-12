#ifndef LIST_H
#define LIST_H

#include <string>

template<typename T>
class List
{
private:

    template<typename>  //Т - не надо объявлять, т.к. переменная объявлена ранее
    class Node
    {
    public:
      Node* next;
      T data;

      Node(T data = T(), Node* next = nullptr) {
          this->data = data;
          this->next = next;
      }
    };

    Node<T>* head;
    int size;

public:
    List();
    ~List();

    void pushBack(T data);
    int getSize();

};

#endif // LIST_H
