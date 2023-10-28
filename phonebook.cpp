/*Phonebook application
date-28/10/2023
*/  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char name[30];
    char country_code[4];
    long int mble_no;
    char sex[8];
    char mail[100];
    struct Person* next; // Pointer to the next contact (used in linked list)
};

typedef struct Person Person;

struct Node {
    Person data;
    struct Node *next;
};

typedef struct Node Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

typedef struct {
    Node *top;
} Stack;

Person phonebook[100]; // Array to store contacts
int contactCount = 0;  // Number of contacts stored in the array
Queue linkedListQueue = {NULL, NULL}; // Queue to manage additional contacts in linked list

void remove_all();
void print_menu();
void add_person();
void list_record();
void search_person();
void remove_person();
void update_person();
void take_input(Person* p);
void enqueue(Queue *q, Person data);
Person dequeue(Queue *q);
void push(Stack *s, Person data);
Person pop(Stack *s);

int main() {
    start();
    return 0;
}

void start() {
    int choice;
    while (1) {
        print_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                list_record();
                getchar();
                getchar();
                break;
            case 2:
                add_person();
                getchar();
                getchar();
                break;
            case 3:
                search_person();
                getchar();
                getchar();
                break;
            case 4:
                remove_person();
                getchar();
                getchar();
                break;
            case 5:
                update_person();
                getchar();
                getchar();
                break;
            case 6:
                remove_all();
                getchar();
                getchar();
                break;
            default:
                system("clear");
                printf("Thanks for using the phonebook. Visit again :)\n");
                getchar();
                getchar();
                exit(0);
        }
    }
}

void print_menu() {
    system("clear");
    printf("\t\t********\n");
    printf("\t\t*                  Welcome TO My phone book                    *\n");
    printf("\t\t********\n\n");
    printf("\t\t\t1) List record\n\n");
    printf("\t\t\t2) Add person\n\n");
    printf("\t\t\t3) Search person Details\n\n");
    printf("\t\t\t4) Remove person\n\n");
    printf("\t\t\t5) Update person\n\n");
    printf("\t\t\t6) Delete all contacts\n\n");
    printf("\t\t\t7) Exit Phonebook\n\n\n");

    printf("\t\t\tEnter your Choice: ");
}

void add_person() {
    system("clear");
    if (contactCount < 100) {
        Person p;
        take_input(&p);
        phonebook[contactCount++] = p;
    } else {
        Person p;
        take_input(&p);
        enqueue(&linkedListQueue, p);
    }

    system("clear");
    printf("Record added Successfully\n");
    printf("Press any key to continue....\n");
}

void take_input(Person* p) {
    system("clear");
    getchar();
    printf("Enter name: ");
    scanf("%[^\n]s", p->name);

    printf("Enter country code: ");
    scanf("%s", p->country_code);

    printf("Enter mobile no: ");
    scanf("%ld", &p->mble_no);

    printf("Enter sex: ");
    scanf("%s", p->sex);

    printf("Enter email: ");
    scanf("%s", p->mail);

    p->next = NULL; // Initialize the 'next' pointer
}

void list_record() {
    system("clear");
    printf("\n**********\n");
    printf("*                  Here is all records listed in phone book                   *\n");
    printf("**********\n\n");
    printf("  NAME\t\t\t\t   COUNTRY CODE\t\t    PHONE NO\t\t    SEX\t\t             EMAIL\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < contactCount; i++) {
        Person p = phonebook[i];
        int len1 = 40 - strlen(p.name);
        int len2 = 19 - strlen(p.country_code);
        int len3 = 15;
        int len4 = 21 - strlen(p.sex);

        printf("%s", p.name);
        for (int j = 0; j < len1; j++) printf(" ");

        printf("%s", p.country_code);
        for (int j = 0; j < len2; j++) printf(" ");

        printf("%ld", p.mble_no);
        for (int j = 0; j < len3; j++) printf(" ");

        printf("%s", p.sex);
        for (int j = 0; j < len4; j++) printf(" ");

        printf("%s", p.mail);
        printf("\n");
    }

    // Print additional contacts from the linked list
    Node* current = linkedListQueue.front;
    while (current != NULL) {
        Person p = current->data;
        int len1 = 40 - strlen(p.name);
        int len2 = 19 - strlen(p.country_code);
        int len3 = 15;
        int len4 = 21 - strlen(p.sex);

        printf("%s", p.name);
        for (int j = 0; j < len1; j++) printf(" ");

        printf("%s", p.country_code);
        for (int j = 0; j < len2; j++) printf(" ");

        printf("%ld", p.mble_no);
        for (int j = 0; j < len3; j++) printf(" ");

        printf("%s", p.sex);
        for (int j = 0; j < len4; j++) printf(" ");

        printf("%s", p.mail);
        printf("\n");

        current = current->next;
    }

    printf("\nPress any key to continue....\n");
}

void search_person() {
    system("clear");
    long int phone;
    printf("Enter Phone number of the person you want to search: ");
    scanf("%ld", &phone);

    int found = 0;

    for (int i = 0; i < contactCount; i++) {
        if (phonebook[i].mble_no == phone) {
            printf("\nName: %s\n", phonebook[i].name);
            printf("Country Code: %s\n", phonebook[i].country_code);
            printf("Phone Number: %ld\n", phonebook[i].mble_no);
            printf("Sex: %s\n", phonebook[i].sex);
            printf("Email: %s\n", phonebook[i].mail);
            found = 1;
            break;
        }
    }

    if (!found) {
        Node* current = linkedListQueue.front;
        while (current != NULL) {
            if (current->data.mble_no == phone) {
                printf("\nName: %s\n", current->data.name);
                printf("Country Code: %s\n", current->data.country_code);
                printf("Phone Number: %ld\n", current->data.mble_no);
                printf("Sex: %s\n", current->data.sex);
                printf("Email: %s\n", current->data.mail);
                found = 1;
                break;
            }
            current = current->next;
        }
    }

    if (!found) {
        printf("Person is not in the Phonebook\n");
    }

    printf("\nPress any key to continue....\n");
}

void enqueue(Queue *q, Person data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

Person dequeue(Queue *q) {
    if (q->front == NULL) {
        Person emptyContact = {"", "", 0, "", ""};
        return emptyContact;
    }
    Node *temp = q->front;
    Person data = temp->data;
    q->front = temp->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return data;
}

void push(Stack *s, Person data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
}

Person pop(Stack *s) {
    if (s->top == NULL) {
        Person emptyContact = {"", "", 0, "", ""};
        return emptyContact;
    }
    Node *temp = s->top;
    Person data = temp->data;
    s->top = temp->next;
    free(temp);
    return data;
}

void remove_person() {
    system("clear");
    long int phone;
    printf("Enter Phone number of the person you want to remove from phonebook: ");
    scanf("%ld", &phone);

    int found = 0;

    for (int i = 0; i < contactCount; i++) {
        if (phonebook[i].mble_no == phone) {
            found = 1;
            for (int j = i; j < contactCount - 1; j++) {
                phonebook[j] = phonebook[j + 1];
            }
            contactCount--;
            break;
        }
    }

    if (!found) {
        Node* prev = NULL;
        Node* current = linkedListQueue.front;

        while (current != NULL) {
            if (current->data.mble_no == phone) {
                found = 1;
                if (prev == NULL) {
                    linkedListQueue.front = current->next;
                    if (linkedListQueue.front == NULL) {
                        linkedListQueue.rear = NULL;
                    }
                } else {
                    prev->next = current->next;
                    if (prev->next == NULL) {
                        linkedListQueue.rear = prev;
                    }
                }
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
    }

    if (found) {
        printf("Person removed successfully\n");
    } else {
        printf("No record found for %ld number\n", phone);
    }

    printf("\nPress any key to continue....\n");
}

void update_person() {
    system("clear");
    long int phone;
    printf("Enter Phone number of the person you want to update details: ");
    scanf("%ld", &phone);

    int found = 0;

    for (int i = 0; i < contactCount; i++) {
        if (phonebook[i].mble_no == phone) {
            take_input(&phonebook[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        Node* current = linkedListQueue.front;
        while (current != NULL) {
            if (current->data.mble_no == phone) {
                take_input(&(current->data));
                found = 1;
                break;
            }
            current = current->next;
        }
    }

    if (found) {
        printf("Data updated successfully\n");
    } else {
        printf("No record found for %ld number\n", phone);
    }

    printf("\nPress any key to continue....\n");
}

void remove_all() {
    contactCount = 0;

    while (linkedListQueue.front != NULL) {
        Node* current = linkedListQueue.front;
        linkedListQueue.front = linkedListQueue.front->next;
        free(current);
    }

    linkedListQueue.rear = NULL;

    system("clear");
    printf("All data in the phonebook deleted successfully\n");
    printf("Press any key to continue....\n");
}
