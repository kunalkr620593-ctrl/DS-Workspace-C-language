#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct node *head = NULL;

void insertion_E(int value){
    struct node *new_node, *temp;
    new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL){
        printf("Memory allocation Failed!\n");
        return;
    }
    new_node->data = value;
    if (head == NULL){
        head = new_node;
        new_node->next = head;
    }
    else{
        temp = head;
        while (temp->next != head){
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = head;
    }
}

void Deletion_E(){
    struct node *temp = head;
    if (head == NULL){
        printf("Linked List is Empty!\n");
        return;
    }
    if (head == head->next){
        free(head);
        head = NULL;
        return;
    }
    else{
        do{
            temp = temp->next;
        } while (temp->next->next != head);
        free(temp->next);
        temp->next = head;
    }
}

void display(){
    struct node *temp = head;
    if (head == NULL){
        printf("Singly Circular Linked List is Empty!\n");
        return;
    }
    do{
        printf("%d->", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("(head)\n");
}

int main(){
    int v, num;
    char extra;
    printf("Enter:\n0 -> Terminalte Program \n1 -> Insertion at End \n2 -> Deletion From End position \n3 -> Display\n");

    while (1){
        while (1){
            printf("\nEnter your choice= ");
            if (scanf("%d%c", &num, &extra) == 2 && extra == '\n'){
                if (num >= 0 && num <= 3){
                    break;
                }
                else{
                    printf("Invalid range!\n");
                }
            }
            else{
                printf("Invalid Input! please Enter only integer\n");
                while (getchar() != '\n');
            }
        }
        switch (num){
        case 0:
            printf("Program Terminate Successfully");
            return 0;
        case 1:
            printf("Enter value= ");
            scanf("%d", &v);
            insertion_E(v);
            break;

        case 2:
            Deletion_E();
            break;

        case 3:
            display();
            break;
        }
    }
}