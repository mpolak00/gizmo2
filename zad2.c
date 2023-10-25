#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_LENGTH (50)
#define SUCCESS (0)
#define FAILURE (-1)

typedef struct Person* Position;

typedef struct Person {
    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];
    int birthYear;
    Position next;
} Person;

int addToTheFrontOfTheList(Position p, int x, const char xname[MAX_LENGTH], const char xsurname[MAX_LENGTH]) {
    Position newPerson = (Position)malloc(sizeof(struct Person));

    if (newPerson == NULL) {
        printf("\nNeuspješna alokacija memorije\n");
        return FAILURE;
    }

    newPerson->birthYear = x;
    strncpy(newPerson->name, xname, MAX_LENGTH);
    strncpy(newPerson->surname, xsurname, MAX_LENGTH);

    newPerson->next = p->next;
    p->next = newPerson;

    return SUCCESS;
}

int Printing(Position p) {
    while (p != NULL) {
        printf("\n%s %s %d", p->name, p->surname, p->birthYear);
        p = p->next;
    }
    return SUCCESS;
}

int addToTheEnd(Position p, int x, const char xname[MAX_LENGTH], const char xsurname[MAX_LENGTH]) {
    Position lastPerson = (Position)malloc(sizeof(struct Person));

    if (lastPerson == NULL) {
        printf("\nGreška u alokaciji memorije\n");
        return FAILURE;
    }

    lastPerson->birthYear = x;
    strncpy(lastPerson->name, xname, MAX_LENGTH);
    strncpy(lastPerson->surname, xsurname, MAX_LENGTH);

    while (p->next != NULL) {
        p = p->next;
    }

    lastPerson->next = NULL;
    p->next = lastPerson;

    return SUCCESS;
}

Position Search(Position p, char x) {
    while (p != NULL && strcmp(p->surname, x) != 0) {
        p = p->next;
    }
    return p;
}

Position FindPrevious(Position p, char x) {
    while (p->next != NULL && strcmp(p->next->surname, x) != 0) {
        p = p->next;
    }
    return p;
}

int Delete(Position p, char x) {
    Position prev = FindPrevious(p, x);

    if (prev != NULL && prev->next != NULL) {
        Position temp = prev->next;
        prev->next = temp->next;
        free(temp);
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

int main() {
    Person head = { .next = NULL, .name = "", .surname = "", .birthYear = 0 };

    int choice;
    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];
    int birthYear;

    while (1) {
        printf("\n1. Add to the front of the list");
        printf("\n2. Add to the end of the list");
        printf("\n3. Search for a person");
        printf("\n4. Delete a person");
        printf("\n5. Print the list");
        printf("\n6. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter name, surname, and birth year: ");
                scanf(" %s %s %d", name, surname, &birthYear);
                addToTheFrontOfTheList(&head, birthYear, name, surname);
                break;

            case 2:
                printf("\nEnter name, surname, and birth year: ");
                scanf(" %s %s %d", name, surname, &birthYear);
                addToTheEnd(&head, birthYear, name, surname);
                break;

            case 3:
                printf("\nEnter the surname to search for: ");
                scanf(" %s", surname);
                Position result = Search(head.next, surname);
                if (result != NULL) {
                    printf("Found: %s %s %d\n", result->name, result->surname, result->birthYear);
                } else {
                    printf("Person not found.\n");
                }
                break;

            case 4:
                printf("\nEnter the surname to delete: ");
                scanf(" %s", surname);
                int deleteResult = Delete(&head, surname);
                if (deleteResult == SUCCESS) {
                    printf("Person deleted.\n");
                } else {
                    printf("Person not found or unable to delete.\n");
                }
                break;

            case 5:
                Printing(head.next);
                break;

            case 6:
                // Izlaz iz programa
                return SUCCESS;

            default:
                printf("\nInvalid choice. Please enter a valid choice.\n");
                break;
        }
    }

    return SUCCESS;
}
