#include <stdio.h>
#include <stdlib.h>

// Structure of a node in Circular Doubly Linked List
struct node {
    int data;               // Stores the data of the node
    struct node *next;      // Points to the next node
    struct node *prev;      // Points to the previous node
};

// Head pointer of the circular doubly linked list
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

        // Make the new node the head of the list
        head = new_node;

        // Since there is only one node, it points to itself
        new_node->next = head;
        new_node->prev = head;

        return;
    }

    // Case 2: The list is not empty

    // Get the last node using the previous pointer of head
    last = head->prev;

    // Connect the new node with the current head and last node
    new_node->next = head;
    new_node->prev = last;

    // Update the links of the existing nodes
    last->next = new_node;
    head->prev = new_node;

    // Make the new node the new head
    head = new_node;
}

// Returns the number of nodes currently in the list
int count_nodes() {

    if (head == NULL)
        return 0;

    int count = 1;
    struct node *temp = head->next;

    while (temp != head) {
        count++;
        temp = temp->next;
    }

    return count;
}

// Deletes the node at the given position (1-based, counted from head)
void Delete_Pos(int pos) {

    // Check whether the list is empty
    if (head == NULL) {
        printf("Doubly Linked List is Empty!\n");
        return;
    }

    int total = count_nodes();

    // Validate the requested position
    if (pos < 1 || pos > total) {
        printf("Invalid position! The list has only %d node(s).\n", total);
        return;
    }

    struct node *temp = head;

    // Walk forward (pos - 1) times to reach the target node
    for (int i = 1; i < pos; i++) {
        temp = temp->next;
    }

    // Case 1: Only one node exists in the list
    if (temp->next == temp) {

        printf("%d deleted successfully.\n", temp->data);

        head = NULL;

        free(temp);

        return;
    }

    // Case 2: More than one node exists

    // Save the neighbouring nodes before unlinking temp
    struct node *prev_node = temp->prev;
    struct node *next_node = temp->next;

    // Bypass temp by connecting its neighbours directly
    prev_node->next = next_node;
    next_node->prev = prev_node;

    // If the deleted node was the head, move head to the next node
    if (temp == head) {
        head = next_node;
    }

    printf("%d deleted successfully.\n", temp->data);

    // Free the deleted node
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

    // Traverse and print the list until we reach the head again
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("(head)\n");
}

// Frees all dynamically allocated memory
void Free_n() {

    // If the list is empty, nothing needs to be freed
    if (head == NULL)
        return;

    // Start from the second node
    struct node *temp = head->next;
    struct node *next_node;

    // Free all nodes except the head node
    while (temp != head) {

        // Save the next node before freeing
        next_node = temp->next;

        // Free the current node
        free(temp);

        // Move to the next node
        temp = next_node;
    }

    // Free the head node
    free(head);

    // Avoid a dangling pointer
    head = NULL;
}

// Main function
int main() {

    int v, num, pos;
    char extra;

    // Display the menu
    printf("Enter:\n 0 -> Terminate Program\n1 -> Insert at Front\n2 -> Delete at Specific Position\n3 -> Display\n");

    // Run until the user chooses to exit
    while (1) {

        // Take a valid menu choice
        while (1) {

            printf("\nEnter Your Choice = ");

            // Accept only integer input
            if (scanf("%d%c", &num, &extra) == 2 && extra == '\n') {

                if (num >= 0 && num <= 3)
                    break;

                printf("Invalid range! Enter a number from 0 to 3.\n");
            }
            else {

                printf("Invalid input! Enter only an integer.\n");

                // Clear the input buffer
                while (getchar() != '\n');
            }
        }

        // Perform the selected operation
        switch (num) {

        case 0:

            printf("Program terminated successfully.\n");

            // Free all dynamically allocated memory
            Free_n();

            return 0;

        case 1: {

            char v_extra;

            printf("Enter value = ");

            // Validate node data input
            while (scanf("%d%c", &v, &v_extra) != 2 || v_extra != '\n') {

                printf("Invalid input! Enter only an integer.\n");

                while (getchar() != '\n');

                printf("Enter value = ");
            }

            // Insert the new node at the front
            insert_F(v);

            break;
        }

        case 2: {

            char pos_extra;

            printf("Enter position to delete = ");

            // Validate position input
            while (scanf("%d%c", &pos, &pos_extra) != 2 || pos_extra != '\n') {

                printf("Invalid input! Enter only an integer.\n");

                while (getchar() != '\n');

                printf("Enter position to delete = ");
            }

            // Delete the node at the given position
            Delete_Pos(pos);

            break;
        }

        case 3:

            // Display the list
            display();

            break;
        }
    }

    return 0;
}