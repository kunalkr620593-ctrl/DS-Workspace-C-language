#include <stdio.h>
#include <stdlib.h>

// Structure of a node in Circular Doubly Linked List
struct node {
    int data;
    struct node *next;
    struct node *prev;
};

struct node *head = NULL;

// Inserts a new node at the front of the circular doubly linked list
void insert_F(int value) {

    struct node *new_node, *last;

    // Dynamically allocate memory for a new node
    new_node = (struct node *)malloc(sizeof(struct node));

    // Check whether memory allocation was successful
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Store the given value in the new node
    new_node->data = value;

    // Case 1: The list is empty
    if (head == NULL) {

        head = new_node;

        // Since this is the first node, it points to itself
        new_node->next = head;
        new_node->prev = head;

        return;
    }

    // Case 2: The list is not empty

    // The last node is directly available using head->prev
    last = head->prev;

    // Connect the new node with the current head and last node
    new_node->next = head;
    new_node->prev = last;

    // Update the old links
    last->next = new_node;
    head->prev = new_node;

    // Make the new node the head of the list
    head = new_node;
}

// Deletes the node at the front of the circular doubly linked list
void Delete_F() {

    // Check whether the list is empty
    if (head == NULL) {
        printf("Doubly Linked List is Empty!\n");
        return;
    }

    struct node *temp = head, *last;

    // Case 1: Only one node exists
    if (temp->next == head) {
        head = NULL;
        printf("%d deleted successfully.\n", temp->data);
        free(temp);
        return;
    }

    // Case 2: More than one node exists

    // Store the last node
    last = temp->prev;

    // Move head to the second node
    head = temp->next;

    // Connect the last node with the new head
    last->next = head;
    head->prev = last;

    printf("%d deleted successfully.\n", temp->data);

    // Free memory of the deleted node
    free(temp);
}

// Displays the circular doubly linked list
void display() {

    struct node *temp = head;

    // Check whether the list is empty
    if (head == NULL) {
        printf("Linked List is Empty!\n");
        return;
    }

    // Traverse and print each node until we reach the head again
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("(head)\n");
}

// Frees all dynamically allocated memory
void Free_n() {

    // If the list is empty, nothing to free
    if (head == NULL)
        return;

    // Start from the second node
    struct node *temp = head->next;
    struct node *next_node;

    // Free all nodes except the head
    while (temp != head) {

        next_node = temp->next;

        free(temp);

        temp = next_node;
    }

    // Free the head node
    free(head);

    // Avoid dangling pointer
    head = NULL;
}

// Main function
int main() {

    int v, num;
    char extra;

    // Display menu
    printf("Enter:\n");
    printf("0 -> Terminate Program\n");
    printf("1 -> Insert at Front\n");
    printf("2 -> Delete from Front\n");
    printf("3 -> Display\n");

    while (1) {

        // Take a valid menu choice
        while (1) {

            printf("\nEnter Your Choice = ");

            if (scanf("%d%c", &num, &extra) == 2 && extra == '\n') {

                if (num >= 0 && num <= 3)
                    break;

                printf("Invalid range! Enter a number from 0 to 3.\n");
            }
            else {

                printf("Invalid input! Enter only an integer.\n");

                while (getchar() != '\n');
            }
        }

        switch (num) {

        case 0:

            printf("Program terminated successfully.\n");

            Free_n();

            return 0;

        case 1: {

            char v_extra;

            printf("Enter value = ");

            while (scanf("%d%c", &v, &v_extra) != 2 || v_extra != '\n') {

                printf("Invalid input! Enter only an integer.\n");

                while (getchar() != '\n');

                printf("Enter value = ");
            }

            insert_F(v);

            break;
        }

        case 2:

            Delete_F();

            break;

        case 3:

            display();

            break;
        }
    }

    return 0;
}