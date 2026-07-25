#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
    struct node *prev;
};

struct node *head=NULL;

void Insert_F(int value){

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

    // OPTIMIZATION: head->prev already points to the last node in a
    // circular doubly linked list, so there's no need to traverse —
    // this makes insertion O(1) instead of O(n)
    temp = head->prev;

    // The new node will point to the current head
    new_node->next = head;

    // Update the previous pointer of the old head
    head->prev = new_node;

    // Connect the last node with the new node
    temp->next = new_node;

    // Set the previous pointer of the new node
    new_node->prev = temp;

    // Update head to the new node
    head = new_node;
}

// Function to insert a node at the end of the list
void Insert_E(int value){

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

    // OPTIMIZATION: head->prev already points to the last node in a
    // circular doubly linked list, so there's no need to traverse —
    // this makes insertion O(1) instead of O(n)
    temp = head->prev;

    // New node will point to head because list is circular
    new_node->next = head;

    // Update previous pointer of head
    head->prev = new_node;

    // Connect new node with last node
    new_node->prev = temp;
    temp->next = new_node;
}

// Function to insert a node at a specific position
void Insert_P(int pos, int value){

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

// Deletes the node at the end (rear) of the circular doubly linked list
void Delete_E() {

    // Check whether the list is empty
    if (head == NULL) {
        printf("Doubly Linked List is Empty!\n");
        return;
    }

    // Get the last node using head->prev
    struct node *last = head->prev, *new_last;

    // Case 1: Only one node exists
    // (When there is only one node, head->prev points back to head itself)
    if (last == head) {

        printf("%d deleted successfully.\n", last->data);

        head = NULL;

        free(last);

        return;
    }

    // Case 2: More than one node exists

    // Get the node before the last node
    new_last = last->prev;

    // Connect the new last node with the head
    new_last->next = head;
    head->prev = new_last;

    printf("%d deleted successfully.\n", last->data);

    // Free the deleted node
    free(last);
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
void Delete_P(int pos) {

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

    // FIX: added pos and value here — the original code used them in
    // case 3 and case 6 below without ever declaring them (compile error)
    int v, num, pos, value;
    char extra;

    // Display menu options
    printf("Enter:\n");
    printf("0 -> Terminate Program\n1 -> Insertion at First\n2 -> Insertion at End\n3 -> Insertion at Specific Position\n4 -> Deletion From First\n5 -> Deletion From End\n6 -> Deletion From Specific Position\n7 -> Count Node\n8 -> Display\n9 -> Reverse Display\n");

    // Continue running until the user chooses to exit
    while(1){

        // Take a valid menu choice from the user
        while(1){

            printf("\nEnter Your Choice = ");

            // Accept only integer input
            if(scanf("%d%c", &num, &extra) == 2 && extra == '\n'){

                // FIX: was "num <= 3", which silently blocked every menu
                // option from 4 to 9 even though they're listed above
                if(num >= 0 && num <= 9){
                    break;
                }
                else{
                    printf("Invalid range! Enter a number from 0 to 9.\n");
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

            // FIX: was "insert_F" (lowercase i) — C is case-sensitive,
            // the function is defined as "Insert_F"
            Insert_F(v);

            break;
        }

        case 2:{

            char v_extra;

            printf("Enter value = ");

            // Validate node value input
            while(scanf("%d%c", &v, &v_extra) != 2 || v_extra != '\n'){

                printf("Invalid input! Enter only an integer.\n");

                while(getchar() != '\n');

                printf("Enter value = ");
            }

            // FIX: was "insert_E" (lowercase i) — should match "Insert_E"
            Insert_E(v);

            break;
        }

        case 3:{

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

            // FIX: was "insert_P" (lowercase i) — should match "Insert_P"
            Insert_P(pos, value);

            break;
        }

        case 4:

            Delete_F();

            break;

        case 5:

            // Delete the last node
            Delete_E();

            break;

        case 6: {

            char pos_extra;

            printf("Enter position to delete = ");

            // Validate position input
            while (scanf("%d%c", &pos, &pos_extra) != 2 || pos_extra != '\n') {

                printf("Invalid input! Enter only an integer.\n");

                while (getchar() != '\n');

                printf("Enter position to delete = ");
            }

            // FIX: was "Delete_Pos", a function that doesn't exist —
            // should call "Delete_P"
            Delete_P(pos);

            break;
        }

        // FIX: case 7 and case 8 were swapped relative to the menu text
        // above (menu says 7 = Count Node, 8 = Display). Case 8 also used
        // to call count_nodes() and throw away the return value, so
        // pressing 8 did nothing visible.
        case 7:

            printf("Number of nodes: %d\n", count_nodes());
            break;

        case 8:

            display();
            break;

        case 9:

            reverse_D();
            break;
        }
    }

    return 0;
}