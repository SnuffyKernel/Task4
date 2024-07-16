#include <stdio.h>
#include <stdlib.h>

#define MAX_PRIORITY 255

typedef struct Node {
    int data;
    int priority;
    struct Node* next;
} Node;

Node* newNode(int data, int priority) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->priority = priority;
    temp->next = NULL;
    return temp;
}

void push(Node** head, int data, int priority) {
    Node* start = (*head);
    Node* temp = newNode(data, priority);
    
    if ((*head)->priority > priority) {
        temp->next = *head;
        *head = temp;
    } else {
        while (start->next != NULL && start->next->priority <= priority) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
}

void pop(Node** head) {
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

void popByPriority(Node** head, int priority) {
    Node* temp = *head, *prev = NULL;
    
    if (temp != NULL && temp->priority == priority) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->priority != priority) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

void popByMinPriority(Node** head, int minPriority) {
    Node* temp = *head, *prev = NULL;

    while (temp != NULL && temp->priority < minPriority) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    if (prev != NULL) {
        prev->next = temp->next;
    } else {
        *head = temp->next;
    }
    free(temp);
}

int peek(Node** head) {
    return (*head)->data;
}

int isEmpty(Node** head) {
    return (*head) == NULL;
}

int main() {
    Node* pq = newNode(4, 1);
    push(&pq, 5, 2);
    push(&pq, 6, 3);
    push(&pq, 7, 0);

    printf("Top Element: %d\n", peek(&pq));
    pop(&pq);
    printf("Top Element: %d\n", peek(&pq));
    
    popByPriority(&pq, 2);
    printf("Top Element after removing priority 2: %d\n", peek(&pq));
    
    popByMinPriority(&pq, 3);
    if (!isEmpty(&pq)) {
        printf("Top Element after removing min priority 3: %d\n", peek(&pq));
    } else {
        printf("Queue is empty\n");
    }

    return 0;
}