#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct node *head = NULL;

void insert_F(int value){
    struct node *new_node, *temp;

    new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL){
        printf("Memory allocation failed!\n");
        return;
    }
    new_node->data = value;

    if (head == NULL){
        head = new_node;
        new_node->next = head;
        return;
    }
    temp = head;
    while (temp->next != head){
        temp = temp->next;
    }

    new_node->next = head;
    temp->next = new_node;
    head = new_node;
}

void countNodes(){
    if (head == NULL){
        printf("Linked List is Empty!\n");
        return;
    }
    int count = 1;
    struct node *temp = head->next;
    while (temp != head){
        count++;
        temp = temp->next;
    }
    printf("Total Number of Nodes = %d\n", count);
}

void display(){
    struct node *temp = head;
    if (head == NULL){
        printf("Linked List is Empty!\n");
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
    printf("Enter: \n0 -> terminate program\n1 -> insertion at first \n2 -> count nodes \n3 -> display \n");
    while (1){
        while (1){
            printf("\nEnter Your choice= ");
            if (scanf("%d%c", &num, &extra) == 2 && extra == '\n'){
                if (num >= 0 && num <= 3){
                    break;
                }
                else{
                    printf("Invalid range! Enter any number from 0 to 3.\n");
                }
            }
            else{
                printf("Invalid input! Enter only an integer.\n");
                while (getchar() != '\n');
            }
        }
        switch (num){

        case 0:
            printf("Program terminate Successfully ");
            return 0;

        case 1:
            printf("Enter value=");
            scanf("%d", &v);
            insert_F(v);
            break;

        case 2:
            countNodes();
            break;

        case 3:
            display();
            break;
        }
    }
    return 0;
}