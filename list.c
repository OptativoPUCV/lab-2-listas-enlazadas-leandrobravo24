#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List * list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

void * firstList(List * list) 
{
    if (list->head != NULL) {
        list->current = list->head;
        return list->current->data;
    }
    return NULL;
}

void * nextList(List * list) 
{
    if (list->current != NULL) {
        list->current = list->current->next;
        if (list->current != NULL) {
            return list->current->data;
        }
    }
    return NULL;
}

void * lastList(List * list) 
{
    if (list->tail != NULL) {
        list->current = list->tail;
        return list->current->data;
    }
    return NULL;
}

void * prevList(List * list) 
{
    if (list->current != NULL) {
        list->current = list->current->prev;
        if (list->current != NULL) {
            return list->current->data;
        }
    }
    return NULL;
}

void pushFront(List * list, void * data) 
{
    Node * nuevo = createNode(data);
    if (list->head == NULL) {
        list->head = nuevo;
        list->tail = nuevo;
    } else {
        nuevo->next = list->head;
        list->head->prev = nuevo;
        list->head = nuevo;
    }
    list->current = nuevo;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
    Node * nuevo = createNode(data);
    if (list->current == NULL) {
        list->head = nuevo;
        list->tail = nuevo;
    } else {

        nuevo->prev = list->current;
        nuevo->next = list->current->next;
        if (list->current->next != NULL) {
            list->current->next->prev = nuevo;
        } else {
            list->tail = nuevo;
        }
        list->current->next = nuevo;
    }
    list->current = nuevo;
}

void * popFront(List * list) 
{
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
    if (list->current != NULL) {
        Node * temp = list->current;
        void * data = temp->data;
        if (temp->prev != NULL) {
            temp->prev->next = temp->next;
        } else {
            list->head = temp->next;
        }
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        } else {
            list->tail = temp->prev;
        }
        list->current = temp->next;
        free(temp);
        return data;
    }
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}