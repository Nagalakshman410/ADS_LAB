#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* xor_ptr; // XOR of previous and next node addresses
} Node;

// Function to perform XOR operation on pointers
Node* xor(Node* a, Node* b) {
    return (Node*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

// Function to insert a node at the beginning of the list
void insert(Node** head_ref, int data) {
    // Create a new node
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;

    // Set XOR of new node's address and next node's address
    new_node->xor_ptr = *head_ref;

    // If list is not empty, then update the previous node's XOR
    if (*head_ref != NULL) {
        // XOR of new node's address and next node's XOR
        (*head_ref)->xor_ptr = xor(new_node, (*head_ref)->xor_ptr);
    }

    // Change head
    *head_ref = new_node;
}

// Function to print the XOR linked list
void printList(Node* head) {
    Node *prev = NULL, *curr = head, *next;

    printf("XOR Linked List: ");
    while (curr != NULL) {
        printf("%d ", curr->data);
        // Get next node
        next = xor(prev, curr->xor_ptr);
        prev = curr;
        curr = next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    int data, count;

    printf("Enter the number of elements: ");
    scanf("%d", &count);

    printf("Enter %d elements:\n", count);
    for (int i = 0; i < count; i++) {
        scanf("%d", &data);
        insert(&head, data);
    }

    // Print the XOR linked list
    printList(head);

    return 0;
}