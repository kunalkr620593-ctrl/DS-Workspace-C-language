#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct node *head = NULL;

int countNodes(){
    if (head == NULL){
        return 0;
    }
    int count = 1;
    struct node *temp = head->next;

    while (temp != head){
        count++;
        temp = temp->next;
    }
    return count;
}

int position(char *msg){
    int num;
    char extra;

    while (1){
        printf("%s", msg);
        if (scanf("%d%c", &num, &extra) == 2 && extra == '\n'){
            return num;
        }
        else{
            printf("Invalid input!\n");
            while (getchar() != '\n');
        }
    }
}

void insertion_P(int pos){
    int value;
    int count = countNodes();
    struct node *new_node, *temp;

    if (pos < 1 || pos > count + 1){
        printf("Invalid position!\n");
        return;
    }

    value = position("Enter value= ");

    new_node = malloc(sizeof(struct node));

    if (new_node == NULL){
        printf("Memory Allocation Failed!\n");
        return;
    }

    new_node->data = value;

    if (pos == 1){

        if (head == NULL){
            head = new_node;
            new_node->next = head;
        }
        else{
            temp = head;
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
        for (int i = 1; i < pos - 1; i++){
            temp = temp->next;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
    printf("Node Inserted Successfully!\n");
}

void deletion_P(int pos){
    int count = countNodes();
    struct node *temp, *ptr;
    if (head == NULL){
        printf("Linked List is Empty!\n");
        return;
    }

    if (pos < 1 || pos > count){
        printf("Invalid position!\n");
        return;
    }

    if (pos == 1){
        if (head->next == head){
            free(head);
            head = NULL;
        }
        else{
            temp = head;
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
        for (int i = 1; i < pos - 1; i++){
            temp = temp->next;
        }

        ptr = temp->next;
        temp->next = ptr->next;
        free(ptr);
    }

    printf("Node Deleted Successfully!\n");
}

void display(){
    if (head == NULL){
        printf("Singly Circular Linked List is Empty!\n");
        return;
    }
    struct node *temp = head;
    do{
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(head)\n");
}

int main(){
    int num, p;
    char extra;
    printf("Enter:\n");
    printf("0 -> Terminate Program \n1 -> Insertion at Specific Position \n2 -> Deletion at specific position \n3 -> Display\n");
    while (1){
        while (1){
            printf("Enter your choice= ");
            if (scanf("%d%c", &num, &extra) == 2 && extra == '\n'){

                if (num >= 0 && num <= 3){
                    break;
                }
                else{
                    printf("Invalid range!\n");
                }
            }
            else{
                printf("Invalid input!\n");
                while (getchar() != '\n');
            }
        }
        switch (num){

        case 0:
            printf("Program terminated successfully!\n");
            return 0;

        case 1:
            p = position("Enter position= ");
            insertion_P(p);
            break;

        case 2:
            p = position("Enter position= ");
            deletion_P(p);
            break;

        case 3:
            display();
            break;
        }
    }
    return 0;
}