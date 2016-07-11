#include <stdio.h>

#define offsetof(type, member) ((size_t) &((type *)0)->member)

#define ListEntry(ptr, type, member) ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define ListNew(head) ((head)->next=NULL)

#define ListAdd(head, node) { (node)->next=(head)->next; (head)->next = (node); }

#define ListEach(head, pos) for (pos = (head)->next; pos != NULL; pos = pos->next)

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
    ListEach(head, ptr) {

        Person* person = ListEntry (ptr, Person, node);
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
    ListNew(&head);
    ListAdd(&head, &john.node);
    ListAdd(&head, &mary.node);
    ListAdd(&head, &george.node);
    PersonListPrint(&head);
    return 0;
}


