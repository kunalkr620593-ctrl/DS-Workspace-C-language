#include <stdio.h>
#include <stdlib.h>

// Node structure
struct node{
    int data;              // Data part
    struct node *next;     // Pointer to next node
};

// Head pointer (starting node of list)
struct node *head = NULL;


// Function to count total nodes in circular linked list
int countNodes(){

    // If list is empty
    if (head == NULL)
        return 0;

    int count = 1;

    // Start from second node
    struct node *temp = head->next;

    // Traverse until we reach head again
    while (temp != head){
        count++;
        temp = temp->next;
    }

    return count;
}


// Function for taking valid integer input
int position(char *msg){

    int num;
    char extra;

    while (1){

        printf("%s", msg);

        // Check if user entered only integer
        if (scanf("%d%c", &num, &extra) == 2 && extra == '\n'){
            return num;
        }
        else{
            printf("Invalid input!\n");

            // Clear input buffer
            while (getchar() != '\n');
        }
    }
}


// Insert node at beginning
void insert_F(int value){

    struct node *new_node, *temp;

    // Create new node
    new_node = (struct node *)malloc(sizeof(struct node));

    // Check memory allocation
    if (new_node == NULL){
        printf("Memory allocation failed!\n");
        return;
    }

    new_node->data = value;

    // If list is empty
    if (head == NULL){

        head = new_node;

        // Point node to itself
        new_node->next = head;
        return;
    }

    temp = head;

    // Reach last node
    while (temp->next != head){
        temp = temp->next;
    }

    // Insert at first
    new_node->next = head;
    temp->next = new_node;
    head = new_node;
}


// Insert node at end
void insertion_E(int value){

    struct node *new_node, *temp;

    new_node = (struct node *)malloc(sizeof(struct node));

    if (new_node == NULL){
        printf("Memory allocation Failed!\n");
        return;
    }

    new_node->data = value;

    // If list is empty
    if (head == NULL){

        head = new_node;
        new_node->next = head;
    }
    else{

        temp = head;

        // Reach last node
        while (temp->next != head){
            temp = temp->next;
        }

        // Insert at end
        temp->next = new_node;
        new_node->next = head;
    }
}


// Insert node at specific position
void insertion_P(int pos){

    int value;
    int count = countNodes();

    struct node *new_node, *temp;

    // Position validation
    if (pos < 1 || pos > count + 1){
        printf("Invalid position!\n");
        return;
    }

    value = position("Enter value= ");

    // Create new node
    new_node = malloc(sizeof(struct node));

    if (new_node == NULL){
        printf("Memory Allocation Failed!\n");
        return;
    }

    new_node->data = value;

    // Insert at first position
    if (pos == 1){

        if (head == NULL){

            head = new_node;
            new_node->next = head;
        }
        else{

            temp = head;

            // Reach last node
            while (temp->next != head){
                temp = temp->next;
            }

            new_node->next = head;
            temp->next = new_node;
            head = new_node;
        }
    }
    else{

        temp = head;

        // Move to (position-1)th node
        for (int i = 1; i < pos - 1; i++){
            temp = temp->next;
        }

        // Insert node
        new_node->next = temp->next;
        temp->next = new_node;
    }

    printf("Node Inserted Successfully!\n");
}


// Delete first node
void deletion_F(){

    struct node *ptr, *temp = head;

    // Empty list
    if (head == NULL){
        printf("Linked List is empty!\n");
        return;
    }

    // Only one node
    if (head->next == head){

        free(head);
        head = NULL;
        return;
    }

    // Reach last node
    do{
        temp = temp->next;
    } while (temp->next != head);

    // Delete first node
    temp->next = head->next;

    ptr = head;
    head = head->next;

    free(ptr);
}


// Delete last node
void deletion_E(){

    struct node *temp = head;

    if (head == NULL){
        printf("Linked List is Empty!\n");
        return;
    }

    // Only one node
    if (head == head->next){

        free(head);
        head = NULL;
        return;
    }
    else{

        // Reach second last node
        do{
            temp = temp->next;
        } while (temp->next->next != head);

        // Delete last node
        free(temp->next);

        temp->next = head;
    }
}


// Delete node from specific position
void deletion_P(int pos){

    int count = countNodes();

    struct node *temp, *ptr;

    if (head == NULL){
        printf("Linked List is Empty!\n");
        return;
    }

    // Position validation
    if (pos < 1 || pos > count){
        printf("Invalid position!\n");
        return;
    }

    // Delete first node
    if (pos == 1){

        if (head->next == head){

            free(head);
            head = NULL;
        }
        else{

            temp = head;

            // Reach last node
            while (temp->next != head){
                temp = temp->next;
            }

            ptr = head;

            head = head->next;

            temp->next = head;

            free(ptr);
        }
    }
    else{

        temp = head;

        // Reach previous node
        for (int i = 1; i < pos - 1; i++){
            temp = temp->next;
        }

        ptr = temp->next;

        temp->next = ptr->next;

        free(ptr);
    }

    printf("Node Deleted Successfully!\n");
}


// Display circular linked list
void display(){

    struct node *temp = head;

    if (head == NULL){
        printf("Linked List is Empty!\n");
        return;
    }

    // Traverse until head comes again
    do{
        printf("%d->", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("(head)\n");
}


// Helper function for reverseDisplay()
// Prints nodes AFTER coming back from recursion, so last node prints first
void reverseDisplayUtil(struct node *temp){

    // Base case: reached the last node (its next points back to head)
    if (temp->next == head){
        printf("%d->", temp->data);
        return;
    }

    // Go deeper into the list first (towards the last node)
    reverseDisplayUtil(temp->next);

    // Print current node AFTER the recursive call returns
    // this is what makes it print in reverse order
    printf("%d->", temp->data);
}


// Display circular linked list in reverse order
// Note: singly linked list has no "prev" pointer, so we can't walk
// backwards directly. Recursion is used instead: go all the way to
// the last node first, then print while coming back (unwinding).
void reverseDisplay(){

    if (head == NULL){
        printf("Linked List is Empty!\n");
        return;
    }

    reverseDisplayUtil(head);
    printf("(head)\n");
}


// Main function: shows menu and calls the right function based on user's choice
int main(){

    int v, num;
    char extra;

    // Print menu only once
    printf("Enter: \n0 -> terminate program \n1 -> insertion at first \n2 -> Insertion at End Position \n3 -> Insertion at specific position\n");
    printf("4 -> Deletion From First Positin \n5 -> Deletion From End Position \n6 -> Deletion From Specific Position");
    printf("\n7 -> Count Nodes \n8 -> display \n9 -> Reverse Display \n");

    // Keep running until user chooses 0 (terminate)
    while (1){

        // Inner loop: keep asking until a valid choice (0-8) is entered
        while (1){

            printf("\nEnter Your choice= ");

            // Check if user entered only a valid integer
            if (scanf("%d%c", &num, &extra) == 2 && extra == '\n'){

                if (num >= 0 && num <= 9){
                    break;   // valid choice, exit inner loop
                }
                else{
                    printf("Invalid range! Enter any number from 0 to 9.\n");
                }
            }
            else{
                printf("Invalid input! Enter only an integer.\n");

                // Clear input buffer
                while (getchar() != '\n');
            }
        }

        // Call function based on user's choice
        switch (num){

        case 0:
            printf("Program terminate Successfully ");
            return 0;

        case 1:
            v = position("Enter value= ");
            insert_F(v);
            break;

        case 2:
            v = position("Enter value= ");
            insertion_E(v);
            break;

        case 3:
            v = position("Enter position= ");
            insertion_P(v);
            break;

        case 4:
            deletion_F();
            break;

        case 5:
            deletion_E();
            break;

        case 6:
            v = position("Enter position= ");
            deletion_P(v);
            break;

        case 7:
            v = countNodes();
            printf("Total Number of Nodes = %d", v);
            break;

        case 8:
            display();
            break;

        case 9:
            reverseDisplay();
            break;
        }
    }

    return 0;
}