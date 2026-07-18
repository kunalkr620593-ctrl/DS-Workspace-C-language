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


// Function to insert a node at a specific position
void insert_P(int pos, int value){

    int count = 0;
    struct node *temp = head;
    struct node *new_node;

    // Count total number of nodes
    if(head != NULL){
        do{
            count++;
            temp = temp->next;
        }while(temp != head);
    }

    // Check whether the position is valid
    if(pos < 1 || pos > count + 1){
        printf("Invalid Position!\n");
        return;
    }

    // Allocate memory for the new node
    new_node = (struct node *)malloc(sizeof(struct node));

    // Check memory allocation
    if(new_node == NULL){
        printf("Memory allocation failed.\n");
        return;
    }

    // Store data in the new node
    new_node->data = value;

    // Case 1: List is empty
    if(head == NULL){

        head = new_node;

        // Since the list is circular, the node points to itself
        new_node->next = head;
        new_node->prev = head;

        printf("Node inserted successfully.\n");
        return;
    }

    // Case 2: Insert at the first position
    if(pos == 1){

        // Last node can be accessed directly using head->prev
        temp = head->prev;

        new_node->next = head;
        new_node->prev = temp;

        temp->next = new_node;
        head->prev = new_node;

        // Update head pointer
        head = new_node;

        printf("Node inserted successfully.\n");
        return;
    }

    // Case 3: Insert at the last position
    if(pos == count + 1){

        temp = head->prev;

        new_node->next = head;
        new_node->prev = temp;

        temp->next = new_node;
        head->prev = new_node;

        printf("Node inserted successfully.\n");
        return;
    }

    // Case 4: Insert at a middle position
    temp = head;

    // Reach the (position-1)th node
    for(int i = 1; i < pos - 1; i++){
        temp = temp->next;
    }

    new_node->next = temp->next;
    new_node->prev = temp;

    temp->next->prev = new_node;
    temp->next = new_node;

    printf("Node inserted successfully.\n");
}


// Function to display the list in forward direction
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


// Function to display the list in reverse direction
void reverse_D(){

    struct node *temp = head;

    // Check whether the list is empty
    if(temp == NULL){
        printf("Circular Doubly Linked List is Empty!\n");
        return;
    }

    printf("Reverse Linked List:\n");

    // Move to the last node
    temp = head->prev;

    printf("(head) <- ");

    // Traverse backward
    do{
        printf("%d <- ", temp->data);
        temp = temp->prev;
    }while(temp != head->prev);

    printf("(head)\n");
}


// Function to free all dynamically allocated nodes
void Free_n(){

    // If the list is empty
    if(head == NULL)
        return;

    // Start from the second node
    struct node *temp = head->next;
    struct node *next_node;

    // Free all nodes except the head node
    while(temp != head){

        // Save the next node before freeing
        next_node = temp->next;

        free(temp);

        temp = next_node;
    }

    // Finally free the head node
    free(head);

    // Avoid dangling pointer
    head = NULL;
}


// Main function: Program execution starts here
int main(){

    int choice, value, pos;
    char extra;

    // Display menu
    printf("Enter:\n");
    printf("0 -> Terminate Program\n1 -> Insert at Specific Position\n2 -> Display\n3 -> Reverse Display\n");

    // Keep running until the user chooses to exit
    while(1){

        // Take a valid menu choice
        while(1){

            printf("\nEnter Your Choice = ");

            // Accept only integer input
            if(scanf("%d%c", &choice, &extra) == 2 &&
               extra == '\n'){

                // Check valid range
                if(choice >= 0 && choice <= 3)
                    break;

                printf("Invalid range! Enter a number from 0 to 3.\n");
            }
            else{

                printf("Invalid input! Enter only an integer.\n");

                // Clear the input buffer
                while(getchar() != '\n');
            }
        }

        // Perform operation according to user's choice
        switch(choice){

        case 0:

            // Free all dynamically allocated memory
            Free_n();

            printf("Program terminated successfully.\n");

            return 0;

        case 1:{

            char p_extra, v_extra;

            // Take position input
            printf("Enter Position = ");

            while(scanf("%d%c", &pos, &p_extra) != 2 || p_extra != '\n'){

                printf("Invalid input! Enter only an integer.\n");

                while(getchar() != '\n');

                printf("Enter Position = ");
            }

            // Take value input
            printf("Enter Value = ");

            while(scanf("%d%c", &value, &v_extra) != 2 || v_extra != '\n'){

                printf("Invalid input! Enter only an integer.\n");

                while(getchar() != '\n');

                printf("Enter Value = ");
            }

            // Insert node at the given position
            insert_P(pos, value);

            break;
        }

        case 2:

            // Display the list in forward direction
            display();

            break;

        case 3:

            // Display the list in reverse direction
            reverse_D();

            break;
        }
    }

    return 0;
}