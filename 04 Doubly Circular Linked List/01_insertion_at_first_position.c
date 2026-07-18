#include <stdio.h>
#include <stdlib.h>

/*
    Program: Circular Doubly Linked List
    Operations:
    1. Insertion at Front
    2. Display (Forward Traversal)
    3. Reverse Display (Backward Traversal)
    4. Memory Deallocation
*/

// Node structure for a Circular Doubly Linked List
struct node{
    int data;           // Stores the data/value of the node
    struct node *next;  // Points to the next node
    struct node *prev;  // Points to the previous node
};

// Global head pointer (NULL means the list is empty)
struct node *head = NULL;


// Inserts a new node at the front of the circular doubly linked list
void insert_F(int value){

    struct node *new_node, *temp;

    // Dynamically allocate memory for a new node
    new_node = (struct node *)malloc(sizeof(struct node));

    // Check whether memory allocation was successful
    if(new_node == NULL){
        printf("Memory allocation failed.\n");
        return;
    }

    // Store the given value in the new node
    new_node->data = value;

    // Case 1: The list is empty
    if(head == NULL){

        head = new_node;

        // The node points to itself because the list is circular
        new_node->next = head;
        new_node->prev = head;

        return;
    }

    // Case 2: The list is not empty
    temp = head;

    // The new node will point to the current head
    new_node->next = head;

    // Update the previous pointer of the old head
    head->prev = new_node;

    // Traverse to the last node
    while(temp->next != head){
        temp = temp->next;
    }

    // Connect the last node with the new node
    temp->next = new_node;

    // Set the previous pointer of the new node
    new_node->prev = temp;

    // Update head to the new node
    head = new_node;
}


// Displays the list in the forward direction
void display(){

    struct node *temp = head;

    // Check whether the list is empty
    if(head == NULL){
        printf("Linked List is Empty!\n");
        return;
    }

    // Traverse the circular list
    do{
        printf("%d -> ", temp->data);
        temp = temp->next;
    }while(temp != head);

    printf("(head)\n");
}


// Displays the list in reverse order using previous pointers
void reverse_D(){

    struct node *temp = head;

    // Check whether the list is empty
    if(temp == NULL){
        printf("Circular Doubly Linked List is Empty!\n");
        return;
    }

    printf("Reverse Linked List:\n");

    // Move to the last node
    temp = temp->prev;

    printf("(head) <- ");

    // Traverse backward until head is reached
    while(temp != head){
        printf("%d <- ", temp->data);
        temp = temp->prev;
    }

    // Print the head node at the end
    printf("%d\n", temp->data);
}


// Frees all dynamically allocated nodes in the list
void Free_n(){

    // If the list is empty, nothing needs to be freed
    if(head == NULL)
        return;

    // Start from the second node because head is freed last
    struct node *temp = head->next;
    struct node *next_node;

    // Free all nodes except the head node
    while(temp != head){

        // Save the address of the next node before freeing
        next_node = temp->next;

        free(temp);

        // Move to the next node
        temp = next_node;
    }

    // Finally free the head node
    free(head);

    // Avoid a dangling pointer
    head = NULL;
}


// Main function: Program execution starts here
int main(){

    int v, num;
    char extra;

    // Display menu options
    printf("Enter:\n");
    printf("0 -> Terminate Program\n1 -> Insert at Front\n2 -> Display\n3 -> Reverse Display\n");

    // Continue running until the user chooses to exit
    while(1){

        // Take a valid menu choice from the user
        while(1){

            printf("\nEnter Your Choice = ");

            // Accept only integer input
            if(scanf("%d%c", &num, &extra) == 2 && extra == '\n'){

                if(num >= 0 && num <= 3){
                    break;
                }
                else{
                    printf("Invalid range! Enter a number from 0 to 3.\n");
                }
            }
            else{

                printf("Invalid input! Enter only an integer.\n");

                // Clear the input buffer
                while(getchar() != '\n');
            }
        }

        // Perform the operation selected by the user
        switch(num){

        case 0:

            printf("Program terminated successfully.\n");

            // Free all dynamically allocated memory
            Free_n();

            return 0;

        case 1: {

            char v_extra;

            printf("Enter value = ");

            // Validate node data input
            while(scanf("%d%c", &v, &v_extra) != 2 || v_extra != '\n'){

                printf("Invalid input! Enter only an integer.\n");

                while(getchar() != '\n');

                printf("Enter value = ");
            }

            insert_F(v);

            break;
        }

        case 2:

            display();

            break;

        case 3:

            reverse_D();

            break;
        }
    }

    return 0;
}