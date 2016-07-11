#include <stdio.h>

typedef struct listnode {
    struct listnode* next;
} ListNode;

typedef struct {
    char*       name;
    int         age;
    ListNode    node;
} Person;

void PersonListPrint(ListNode* head) {
    ListNode* ptr;

    for (ptr = (head)->next; ptr != ((void *)0) ; ptr = ptr->next) {
        Person* person = ((Person *)((char *)(ptr)-(unsigned long)(&((Person *)0)->node)));
        printf("%s is %d years old\n", person->name, person->age);
    }
}

int main() {

    ListNode head;

    Person john = {
        .name = "A",
        .age = 10,
    };

    Person mary = {
        .name = "B",
        .age = 20,
    };
    Person george = {
        .name = "C",
        .age = 30,
    };
    ((&head)->next= ((void *)0));
    { (&john.node)->next=(&head)->next; (&head)->next = (&john.node); };
    { (&mary.node)->next=(&head)->next; (&head)->next = (&mary.node); };
    { (&george.node)->next=(&head)->next; (&head)->next = (&george.node); };

    PersonListPrint(&head);
    return 0;
}

