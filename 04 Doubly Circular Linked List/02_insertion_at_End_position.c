#include <stdio.h>
#include <stdlib.h>

// Structure of a node in Circular Doubly Linked List
struct node{
    int data;           // Stores the value of the node
    struct node *next;  // Points to the next node
    struct node *prev;  // Points to the previous node
};

// Head pointer stores the address of the first node
struct node *head = NULL;


// Function to insert a node at the end of the list
void insert_E(int value){

    struct node *new_node, *temp;

    // Dynamically allocate memory for new node
    new_node = (struct node *)malloc(sizeof(struct node));

    // Check memory allocation
    if(new_node == NULL){
        printf("Memory allocation failed.\n");
        return;
    }

    // Store data in the new node
    new_node->data = value;

    // If the list is empty
    if(head == NULL){

        head = new_node;

        // New node points to itself
        new_node->next = head;
        new_node->prev = head;

        return;
    }

    temp = head;

    // New node will point to head because list is circular
    new_node->next = head;

    // Update previous pointer of head
    head->prev = new_node;

    // Traverse to the last node
    while(temp->next != head){
        temp = temp->next;
    }

    // Connect new node with last node
    new_node->prev = temp;
    temp->next = new_node;
}


// Function to display the list in forward direction
void display(){

    struct node *temp = head;

    // Check whether list is empty
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


// Function to display the list in reverse direction
void reverse_D(){

    struct node *temp = head;

    // Check whether list is empty
    if(temp == NULL){
        printf("Circular Doubly Linked List is Empty!\n");
        return;
    }

    printf("Reverse Linked List:\n");

    // Move to last node
    temp = temp->prev;

    printf("(head) <- ");

    // Traverse backward using prev pointers
    while(temp != head){
        printf("%d <- ", temp->data);
        temp = temp->prev;
    }

    // Print head node
    printf("%d\n", temp->data);
}


// Function to free all dynamically allocated nodes
void Free_n(){

    // If list is empty
    if(head == NULL)
        return;

    // Start from second node
    struct node *temp = head->next;
    struct node *next_node;

    // Free all nodes except head
    while(temp != head){

        // Save next node before freeing current node
        next_node = temp->next;

        free(temp);

        temp = next_node;
    }

    // Finally free head node
    free(head);

    // Avoid dangling pointer
    head = NULL;
}


// Main function: Program execution starts here
int main(){

    int v, num;
    char extra;

    // Display menu
    printf("Enter:\n");
    printf("0 -> Terminate Program\n1 -> Insert at End\n2 -> Display\n3 -> Reverse Display\n");

    // Run continuously until user exits
    while(1){

        // Take valid menu choice
        while(1){

            printf("\nEnter Your Choice = ");

            // Validate integer input
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

                // Clear input buffer
                while(getchar() != '\n');
            }
        }

        // Perform operation according to user choice
        switch(num){

        case 0:

            printf("Program terminated successfully.\n");

            // Free allocated memory
            Free_n();

            return 0;

        case 1:{

            char v_extra;

            printf("Enter value = ");

            // Validate node value input
            while(scanf("%d%c", &v, &v_extra) != 2 || v_extra != '\n'){

                printf("Invalid input! Enter only an integer.\n");

                while(getchar() != '\n');

                printf("Enter value = ");
            }

            insert_E(v);

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