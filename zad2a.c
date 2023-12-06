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

Position Search(Position p, const char* x) {
    while (p != NULL && strcmp(p->surname, x) != 0) {
        p = p->next;
    }

    if (p == NULL) {
        printf("\nNot in the list\n");
        return NULL;
    } else {
        return p;
    }
}

Position FindPrevious(Position p, const char* x) {
    while (p->next != NULL && strcmp(p->next->surname, x) != 0) {
        p = p->next;
    }
    return p;
}

int Delete(Position p, const char* x) {
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

int AddNext(Position p, const char* x, int birth, const char xname[MAX_LENGTH], const char xsurname[MAX_LENGTH]) {
    Position result = Search(p, x);
    if (result == NULL) {
        printf("\nNot found\n");
        return FAILURE;
    }

    Position newPerson = (Position)malloc(sizeof(struct Person));
    if (newPerson == NULL) {
        printf("\nMistake in allocation\n");
        return FAILURE;
    }
    newPerson->birthYear = birth;
    strncpy(newPerson->name, xname, MAX_LENGTH);
    strncpy(newPerson->surname, xsurname, MAX_LENGTH);
    newPerson->next = result->next;
    result->next = newPerson;
    return SUCCESS;
}

int AddBefore(Position p, const char* x, int birth, const char xname[MAX_LENGTH], const char xsurname[MAX_LENGTH]) {
    Position result = FindPrevious(p, x);
    if (result == NULL) {
        printf("\nMistake\n");
        return FAILURE;
    }
    Position newPerson = (Position)malloc(sizeof(struct Person));
    if (newPerson == NULL) {
        printf("\nMistake\n");
        return FAILURE;
    }
    newPerson->birthYear = birth;
    strncpy(newPerson->name, xname, MAX_LENGTH);
    strncpy(newPerson->surname, xsurname, MAX_LENGTH);
    newPerson->next = result->next;
    result->next = newPerson;
    return SUCCESS;
}

int sortEnternce(Position p, int birth, const char xname[MAX_LENGTH], const char xsurname[MAX_LENGTH]) {
    while (p->next != NULL && p->next->birthYear < birth) {
        p = p->next;
    }
    Position newPerson = (Position)malloc(sizeof(struct Person));
    if (newPerson == NULL) {
        printf("\nMistake\n");
        return FAILURE;
    }
    newPerson->birthYear = birth;
    strncpy(newPerson->name, xname, MAX_LENGTH);
    strncpy(newPerson->surname, xsurname, MAX_LENGTH);
    newPerson->next = p->next;
    p->next = newPerson;
    return SUCCESS;
}

int writeToFile(Position p, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("\nMistake\n");
        return FAILURE;
    }
    while (p != NULL) {
        fprintf(file, " %s %s %d\n", p->name, p->surname, p->birthYear);
        p = p->next;
    }
    fclose(file);
    return SUCCESS;
}

int readFromFile(Position p, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("\nMistake\n");
        return FAILURE;
    }
    while (1) {
        Position newPerson = (Position)malloc(sizeof(struct Person));
        if (newPerson == NULL) {
            printf("\nMistake\n");
            return FAILURE;
        }
        if (fscanf(file, " %s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear) != 3) {
            free(newPerson);
            break;
        }
        newPerson->next = p->next;
        p->next = newPerson;
        p = newPerson;
    }
    fclose(file);
    return SUCCESS;
}

int main() {
    Person head = { .next = NULL, .name = "", .surname = "", .birthYear = 0 };

    int choice;
    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];
    char Nextsurname[MAX_LENGTH];
    int birthYear;

    while (1) {
        printf("\n1. Add to the front of the list");
        printf("\n2. Add to the end of the list");
        printf("\n3. Search for a person");
        printf("\n4. Delete a person");
        printf("\n5. Print the list");
        printf("\n6. Add after a person");
        printf("\n7. Add before a person");
        printf("\n8. Sort by birth year");
        printf("\n9. Write to a file");
        printf("\n10. Read from a file");
        printf("\n11. Exit");
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
                printf("\Enter the surname to search for: ");
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
                printf("\nEnter the surname to add after: ");
                scanf(" %s", surname);
                printf("\nEnter the birth year: ");
                scanf("%d", &birthYear);
                printf("\nEnter the name: ");
                scanf(" %s", name);
                printf("\nEnter the surname: ");
                scanf(" %s", Nextsurname);

                int addNextResult = AddNext(&head, surname, birthYear, name, Nextsurname);
                if (addNextResult == SUCCESS) {
                    Printing(head.next);
                } else {
                    printf("\nMistake.\n");
                }
                break;

            case 7:
                printf("\nEnter the surname to add before: ");
                scanf(" %s", surname);
                printf("\nEnter the birth year: ");
                scanf("%d", &birthYear);
                printf("\nEnter the name: ");
                scanf(" %s", name);
                printf("\nEnter the surname: ");
                scanf(" %s", Nextsurname);

                int addBeforeResult = AddBefore(&head, surname, birthYear, name, Nextsurname);
                if (addBeforeResult == SUCCESS) {
                    Printing(head.next);
                } else {
                    printf("\nMistake.\n");
                }
                break;

            case 8:
                printf("\nEnter birth year, name, and surname: ");
                scanf("%d %s %s", &birthYear, name, surname);
                sortEnternce(&head, birthYear, name, surname);
                break;

            case 9:
                printf("\nEnter the filename to write to: ");
                char writeFilename[MAX_LENGTH];
                scanf(" %s", writeFilename);
                int writeResult = writeToFile(head.next, writeFilename);
                if (writeResult == SUCCESS) {
                    printf("Data written to file.\n");
                } else {
                    printf("File write error.\n");
                }
                break;

            case 10:
                printf("\nEnter the filename to read from: ");
                char readFilename[MAX_LENGTH];
                scanf(" %s", readFilename);
                int readResult = readFromFile(&head, readFilename);
                if (readResult == SUCCESS) {
                    printf("Data read from file.\n");
                } else {
                    printf("File read error.\n");
                }
                break;

            case 11:
                // Cleanup and exit
                while (head.next != NULL) {
                    Position temp = head.next;
                    head.next = temp->next;
                    free(temp);
                }
                return SUCCESS;

            default:
                printf("\nInvalid choice. Please enter a valid choice.\n");
                break;
        }
    }

    return SUCCESS;
}

       
