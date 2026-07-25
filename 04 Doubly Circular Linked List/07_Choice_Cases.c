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

    new_node = (struct node *)malloc(sizeof(struct node));

    if(new_node == NULL){
        printf("Memory allocation failed.\n");
        return;
    }

    new_node->data = value;

    if(head == NULL){
        head = new_node;
        new_node->next = head;
        new_node->prev = head;
        return;
    }

    temp = head;
    new_node->next = head;
    head->prev = new_node;

    while(temp->next != head){
        temp = temp->next;
    }

    temp->next = new_node;
    new_node->prev = temp;
    head = new_node;
}

void Insert_E(int value){

    struct node *new_node, *temp;

    new_node = (struct node *)malloc(sizeof(struct node));

    if(new_node == NULL){
        printf("Memory allocation failed.\n");
        return;
    }

    new_node->data = value;

    if(head == NULL){
        head = new_node;
        new_node->next = head;
        new_node->prev = head;
        return;
    }

    temp = head;
    new_node->next = head;
    head->prev = new_node;

    while(temp->next != head){
        temp = temp->next;
    }

    new_node->prev = temp;
    temp->next = new_node;
}

void Insert_P(int pos, int value){

    int count = 0;
    struct node *temp = head;
    struct node *new_node;

    if(head != NULL){
        do{
            count++;
            temp = temp->next;
        }while(temp != head);
    }

    if(pos < 1 || pos > count + 1){
        printf("Invalid Position!\n");
        return;
    }

    new_node = (struct node *)malloc(sizeof(struct node));

    if(new_node == NULL){
        printf("Memory allocation failed.\n");
        return;
    }

    new_node->data = value;

    if(head == NULL){
        head = new_node;
        new_node->next = head;
        new_node->prev = head;
        printf("Node inserted successfully.\n");
        return;
    }

    if(pos == 1){
        temp = head->prev;
        new_node->next = head;
        new_node->prev = temp;
        temp->next = new_node;
        head->prev = new_node;
        head = new_node;
        printf("Node inserted successfully.\n");
        return;
    }

    if(pos == count + 1){
        temp = head->prev;
        new_node->next = head;
        new_node->prev = temp;
        temp->next = new_node;
        head->prev = new_node;
        printf("Node inserted successfully.\n");
        return;
    }

    temp = head;
    for(int i = 1; i < pos - 1; i++){
        temp = temp->next;
    }

    new_node->next = temp->next;
    new_node->prev = temp;
    temp->next->prev = new_node;
    temp->next = new_node;

    printf("Node inserted successfully.\n");
}

void Delete_F() {

    if (head == NULL) {
        printf("Doubly Linked List is Empty!\n");
        return;
    }

    struct node *temp = head, *last;

    if (temp->next == head) {
        head = NULL;
        printf("%d deleted successfully.\n", temp->data);
        free(temp);
        return;
    }

    last = temp->prev;
    head = temp->next;
    last->next = head;
    head->prev = last;

    printf("%d deleted successfully.\n", temp->data);
    free(temp);
}

void Delete_E() {

    if (head == NULL) {
        printf("Doubly Linked List is Empty!\n");
        return;
    }

    struct node *last = head->prev, *new_last;

    if (last == head) {
        printf("%d deleted successfully.\n", last->data);
        head = NULL;
        free(last);
        return;
    }

    new_last = last->prev;
    new_last->next = head;
    head->prev = new_last;

    printf("%d deleted successfully.\n", last->data);
    free(last);
}

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

void Delete_P(int pos) {

    if (head == NULL) {
        printf("Doubly Linked List is Empty!\n");
        return;
    }

    int total = count_nodes();

    if (pos < 1 || pos > total) {
        printf("Invalid position! The list has only %d node(s).\n", total);
        return;
    }

    struct node *temp = head;

    for (int i = 1; i < pos; i++) {
        temp = temp->next;
    }

    if (temp->next == temp) {
        printf("%d deleted successfully.\n", temp->data);
        head = NULL;
        free(temp);
        return;
    }

    struct node *prev_node = temp->prev;
    struct node *next_node = temp->next;

    prev_node->next = next_node;
    next_node->prev = prev_node;

    if (temp == head) {
        head = next_node;
    }

    printf("%d deleted successfully.\n", temp->data);
    free(temp);
}

void display(){

    struct node *temp = head;

    if(head == NULL){
        printf("Linked List is Empty!\n");
        return;
    }

    do{
        printf("%d -> ", temp->data);
        temp = temp->next;
    }while(temp != head);

    printf("(head)\n");
}

void reverse_D(){

    struct node *temp = head;

    if(temp == NULL){
        printf("Circular Doubly Linked List is Empty!\n");
        return;
    }

    printf("Reverse Linked List:\n");

    temp = temp->prev;

    printf("(head) <- ");

    while(temp != head){
        printf("%d <- ", temp->data);
        temp = temp->prev;
    }

    printf("%d\n", temp->data);
}

void Free_n(){

    if(head == NULL)
        return;

    struct node *temp = head->next;
    struct node *next_node;

    while(temp != head){
        next_node = temp->next;
        free(temp);
        temp = next_node;
    }

    free(head);
    head = NULL;
}

int main(){

    int v, num, pos, value;
    char extra;

    printf("Enter:\n");
    printf("0 -> Terminate Program\n1 -> Insertion at First\n2 -> Insertion at End\n3 -> Insertion at Specific Position\n4 -> Deletion From First\n5 -> Deletion From End\n6 -> Deletion From Specific Position\n7 -> Count Node\n8 -> Display\n9 -> Reverse Display\n");

    while(1){

        while(1){

            printf("\nEnter Your Choice = ");

            if(scanf("%d%c", &num, &extra) == 2 && extra == '\n'){

                if(num >= 0 && num <= 9){
                    break;
                }
                else{
                    printf("Invalid range! Enter a number from 0 to 9.\n");
                }
            }
            else{
                printf("Invalid input! Enter only an integer.\n");
                while(getchar() != '\n');
            }
        }

        switch(num){

        case 0:
            printf("Program terminated successfully.\n");
            Free_n();
            return 0;

        case 1: {

            char v_extra;

            printf("Enter value = ");

            while(scanf("%d%c", &v, &v_extra) != 2 || v_extra != '\n'){
                printf("Invalid input! Enter only an integer.\n");
                while(getchar() != '\n');
                printf("Enter value = ");
            }

            Insert_F(v);
            break;
        }

        case 2:{

            char v_extra;

            printf("Enter value = ");

            while(scanf("%d%c", &v, &v_extra) != 2 || v_extra != '\n'){
                printf("Invalid input! Enter only an integer.\n");
                while(getchar() != '\n');
                printf("Enter value = ");
            }

            Insert_E(v);
            break;
        }

        case 3:{

            char p_extra, v_extra;

            printf("Enter Position = ");

            while(scanf("%d%c", &pos, &p_extra) != 2 || p_extra != '\n'){
                printf("Invalid input! Enter only an integer.\n");
                while(getchar() != '\n');
                printf("Enter Position = ");
            }

            printf("Enter Value = ");

            while(scanf("%d%c", &value, &v_extra) != 2 || v_extra != '\n'){
                printf("Invalid input! Enter only an integer.\n");
                while(getchar() != '\n');
                printf("Enter Value = ");
            }

            Insert_P(pos, value);
            break;
        }

        case 4:
            Delete_F();
            break;

        case 5:
            Delete_E();
            break;

        case 6: {

            char pos_extra;

            printf("Enter position to delete = ");

            while (scanf("%d%c", &pos, &pos_extra) != 2 || pos_extra != '\n') {
                printf("Invalid input! Enter only an integer.\n");
                while (getchar() != '\n');
                printf("Enter position to delete = ");
            }

            Delete_P(pos);
            break;
        }

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