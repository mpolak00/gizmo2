#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 11

struct cities;
typedef struct cities* Tree;
typedef struct cities {
    char name[50];
    Tree R;
    Tree L;
    int residents;
} Cities;

struct countries;
typedef struct countries* Position;
typedef struct countries {
    char name[50];
    Tree city;
    Position next;
} Countries;

typedef struct {
    Position table[TABLE_SIZE];
} HashTable;

unsigned int hash(char* key);
void initializeTable(HashTable* table);
int AddCountry(HashTable* table, char* NameOfCountry, char* file);
int AddCity(char* file, Tree S);
Tree EnterCity(char* name, int residents, Tree S);
int PrintCountries(HashTable* table);
int PrintCities(Tree S);
Position SearchCountry(HashTable* table, char* name);
int SearchCity(Tree S, int searched_number);

int main()
{
    HashTable table;
    initializeTable(&table);

    char NameOfCountry[50];
    char NameOfFile[50];
    int residents = 0;

    FILE* f = fopen("drzave.txt", "r");
    if (f == NULL)
    {
        printf("ERROR: File cannot be opened.\n");
        return -1;
    }

    while (!feof(f))
    {
        fscanf(f, "%s %s", NameOfCountry, NameOfFile);
        AddCountry(&table, NameOfCountry, NameOfFile);
    }
    fclose(f);

    PrintCountries(&table);

    printf("\nEnter the name of the wanted country: ");
    scanf("%s", NameOfCountry);

    Position P = SearchCountry(&table, NameOfCountry);
    if (P == NULL)
    {
        printf("This country doesn't exist in the current file, please try again.\n");
        return 0;
    }

    printf("Minimum population: ");
    scanf(" %d", &residents);

    printf("\nCities of %s with more than %d inhabitants:\n", P->name, residents);
    SearchCity(P->city, residents);

    return 0;
}

unsigned int hash(char* key) {
    unsigned int sum = 0;
    for (int i = 0; i < 5 && key[i] != '\0'; ++i) {
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}

void initializeTable(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table->table[i] = NULL;
    }
}

int AddCountry(HashTable* table, char* NameOfCountry, char* file) {
    unsigned int index = hash(NameOfCountry);

    Position q = (Position)malloc(sizeof(Countries));
    if (q == NULL)
    {
        printf("Memory allocation unsuccessful.\n");
        return -1;
    }

    strcpy(q->name, NameOfCountry);
    q->city = NULL;
    q->next = table->table[index];
    table->table[index] = q;

    q->city = (Tree)malloc(sizeof(Cities));
    if (q->city == NULL)
    {
        printf("Memory allocation unsuccessful.\n");
        return -1;
    }

    strcpy(q->city->name, "");
    q->city->residents = 0;
    q->city->R = NULL;
    q->city->L = NULL;

    AddCity(file, q->city);

    return 0;
}

int AddCity(char* file, Tree S)
{
    FILE* f = fopen(file, "r");
    if (f == NULL)
    {
        printf("ERROR: File cannot be opened.\n");
        return -1;
    }

    char name[50];
    int residents = 0;

    while (!feof(f))
    {
        fscanf(f, "%s %d", name, &residents);
        S = EnterCity(name, residents, S);
    }

    fclose(f);
    return 0;
}

Tree EnterCity(char* name, int residents, Tree S)
{
    Tree q = NULL;
    if (S == NULL)
    {
        q = (Tree)malloc(sizeof(Cities));
        if (q == NULL)
        {
            printf("Memory allocation unsuccessful.\n");
            return NULL;
        }
        strcpy(q->name, name);
        q->residents = residents;
        q->R = NULL;
        q->L = NULL;
        return q;
    }

    if (S->residents < residents)
        S->R = EnterCity(name, residents, S->R);
    else if (S->residents > residents)
        S->L = EnterCity(name, residents, S->L);
    else if (residents == S->residents)
    {
        if (strcmp(name, S->name) >= 0)
            S->R = EnterCity(name, residents, S->R);
        else
            S->L = EnterCity(name, residents, S->L);
    }

    return S;
}

int PrintCountries(HashTable* table)
{
    printf("COUNTRIES:\n");
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        Position P = table->table[i];
        while (P != NULL)
        {
            printf("\n%s:\n", P->name);
            PrintCities(P->city->R);
            P = P->next;
        }
    }
    return 0;
}

int PrintCities(Tree S)
{
    if (S == NULL)
        return 0;
    PrintCities(S->L);
    printf("%s \t", S->name);
    printf("%d\n", S->residents);
    PrintCities(S->R);
    return 0;
}

Position SearchCountry(HashTable* table, char* name)
{
    unsigned int index = hash(name);

    Position P = table->table[index];
    while (P != NULL)
    {
        if (strcmp(P->name, name) == 0)
        {
            return P;
        }
        P = P->next;
    }

    return P;
}

int SearchCity(Tree S, int searched_number)
{
    if (S == NULL)
    {
        return 0;
    }
    SearchCity(S->R, searched_number);
    if (S->residents > searched_number) {
        printf("%s %d\n", S->name, S->residents);
    }

    SearchCity(S->L, searched_number);

    return 0;
}
