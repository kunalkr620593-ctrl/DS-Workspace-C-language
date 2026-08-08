#include <stdio.h>

// Maximum size of stack
#define MAX 5

// Array to store stack elements
int stack[MAX];

// 'top' keeps track of the top element
// Initially stack is empty, so top = -1
int top = -1;


// Adds a new element to the top of the stack
void push(int value) {

    // Check if stack is full
    if (top == MAX - 1) {
        printf("Stack Overflow!\n");
        return;
    }

    // Move top to next position
    top++;

    // Insert the new value
    stack[top] = value;

    printf("%d pushed into stack.\n", value);
}

// Removes the top element from the stack
void pop() {

    // Check if stack is empty
    if (top == -1) {
        printf("Stack Underflow!\n");
        return;
    }

    // Print the element being removed
    printf("%d popped from stack.\n", stack[top]);

    // Move top one position down
    top--;
}

// Displays the top element without removing it
void peek() {

    // Check if stack is empty
    if (top == -1) {
        printf("Stack is empty.\n");
        return;
    }

    // Display top element
    printf("Top element = %d\n", stack[top]);
}

// Prints all elements from top to bottom
void display() {

    // Check if stack is empty
    if (top == -1) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack elements are:\n");

    // Traverse from top to bottom
    for (int i = top; i >= 0; i--) {
        printf("%d\n", stack[i]);
    }
}


// MAIN FUNCTION 
int main() {

    int value;   // Stores value to be pushed
    int num;     // Stores user's menu choice
    char extra;  // Used to validate input

    // Display menu
    printf("Enter:\n 0 -> Exit program\n 1 -> Push\n 2-> Pop\n 3 -> Peek\n 4 -> display \n");

    // Infinite loop for menu
    while (1) {

        // Input validation loop
        while (1) {

            printf("\nEnter Your Choice = ");

            // Read integer and check if extra character exists
            if (scanf("%d%c", &num, &extra) == 2 && extra == '\n') {

                // Check if choice is within valid range
                if (num >= 0 && num <= 4) {
                    break;
                } else {
                    printf("Invalid range! Enter any number from 0 to 4.\n");
                }

            } else {

                // Invalid input (like 2a, abc, etc.)
                printf("Invalid input! Enter only an integer.\n");

                // Clear input buffer
                while (getchar() != '\n');
            }
        }

        // Perform operation based on user's choice
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