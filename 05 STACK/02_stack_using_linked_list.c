#include <stdio.h>
#include <stdlib.h>

// Structure for stack node
struct stack {
    int data;              // Stores data
    struct stack *next;    // Points to next node
};

// Pointer to the top of the stack
struct stack *top = NULL;


//PUSH 
// Insert a new element at the top of the stack
void push(int value) {

    // Create a new node
    struct stack *new_node;

    // Allocate memory
    new_node = (struct stack *)malloc(sizeof(struct stack));

    // Check if memory allocation failed
    if (new_node == NULL) {
        printf("Stack Overflow!\n");
        return;
    }

    // Store value
    new_node->data = value;

    // Link new node with current top
    new_node->next = top;

    // Make new node the top
    top = new_node;

    printf("%d pushed into stack.\n", value);
}


// POP 
// Remove the top element
void pop() {

    // Check if stack is empty
    if (top == NULL) {
        printf("Stack Underflow!\n");
        return;
    }

    // Temporary pointer to top node
    struct stack *temp = top;

    // Move top to next node
    top = top->next;

    // Print deleted value
    printf("%d popped from stack.\n", temp->data);

    // Free memory
    free(temp);
}


// PEEK 
// Display the top element
void peek() {

    if (top == NULL) {
        printf("Stack is Empty!\n");
        return;
    }

    printf("Top element = %d\n", top->data);
}


// DISPLAY 
// Display all stack elements
void display() {

    // Check if stack is empty
    if (top == NULL) {
        printf("Stack is Empty!\n");
        return;
    }

    struct stack *temp = top;

    printf("Stack elements are:\n");

    // Traverse from top to bottom
    while (temp != NULL) {

        printf("%d\n", temp->data);

        // Move to next node
        temp = temp->next;
    }
}


//  MAIN FUNCTION 
int main() {

    int value,num;      // Value to push  and Menu choice num
    char extra;    // Used for input validation

    // Display menu
   printf("Enter:\n 0 -> Exit program\n 1 -> Push\n 2-> Pop\n 3 -> Peek\n 4 -> display \n");

    while (1) {

        // Input validation
        while (1) {

            printf("\nEnter Your Choice = ");

            // Accept only integer input
            if (scanf("%d%c", &num, &extra) == 2 && extra == '\n') {

                if (num >= 0 && num <= 4)
                    break;

                printf("Invalid range! Enter any number from 0 to 4.\n");
            }
            else {

                printf("Invalid input! Enter only an integer.\n");

                // Clear input buffer
                while (getchar() != '\n');
            }
        }

        // Perform operation
        switch (num) {

            case 0:
                printf("Program terminated.\n");
                return 0;

            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                push(value);
                break;

            case 2:
                pop();
                break;

            case 3:
                peek();
                break;

            case 4:
                display();
                break;
        }
    }

    return 0;
}