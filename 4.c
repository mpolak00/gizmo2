#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 128

struct Polinome;
typedef struct Polinome* Position;

typedef struct Polinome {

    int coef;
    int exp;
    Position  next;

} Poli;

int Read_file(Position P1, Position P2);
Position MakePol(int koef, int eks);
int ReadLine(Position head, char* buffer);
int ClearZero(Position head);
int InsertSorted(Position head, Position NewElement);
int InsertAfter(Position head, Position NewElement);
int Print(Position P);
int CleanUp(Position P);
int Multiply(Position P1, Position P2);
int Sum(Position P1, Position P2);



int main() {


    Poli head1 = { .coef = 0 , .exp = 0, .next = NULL };
    Poli head2 = { .coef = 0, .exp = 0, .next = NULL };

    Position P1 = &head1;
    Position P2 = &head2;

    int answer = 1;

    if (Read_file(P1, P2) != 0) {
        perror("List error");
        return -1;
    }

    while (answer != 0) {


        printf("\nOdaberite broj ovisno o zeljenoj vrsti racunanja: \n");
        printf("Ispis binoma (1)\n");
        printf("Umnozak: (2)\n");
        printf("Zbroj: (3)\n");
        printf("Izlaz (0)\n");
        printf("Unesite vas odabir:  ");
        scanf(" %d", &answer);



        switch (answer)
        {

        case 0:
            break;

        case 1:
            printf("\nPolinomi iz datoteke su :\n");
            printf("\n 1.red: \n");
            Print(P1);
            printf("\n 2.ref: \n");
            Print(P2);

            break;

        case 2:
            Multiply(P1, P2);

            break;
        case 3:
            Sum(P1, P2);

            break;

        default:
            printf("\nUnijeli ste broj koji nije poduden!\n\n");
            break;
        }
    }


    return 0;
}


int CleanUp(Position P) {

    Position temp = NULL;

    while (NULL != P->next) {
        temp = P->next;
        P->next = temp->next;
        free(temp);
    }

    return 0;
}

Position MakePol(int koef, int eks) {

    Position New = NULL;

    New = (Position)malloc(sizeof(Poli));

    New->coef = koef;
    New->exp = eks;
    New->next = NULL;

    return New;
}


int Read_file(Position P1, Position P2) {

    FILE* fp = NULL;
    char buffer[MAX_SIZE] = { 0 };

    fp = fopen("polinom.txt", "r");

    if (fp == NULL) {
        printf("File missing or unable to open.");
        return -1;
    }

    fgets(buffer, MAX_SIZE, fp);
    ReadLine(P1, buffer);
    ClearZero(P1);

    fgets(buffer, MAX_SIZE, fp);
    ReadLine(P2, buffer);
    ClearZero(P2);


    fclose(fp);

    return 0;
}

int ReadLine(Position head, char* buffer) {

    int coef, exp;
    int counter = 0;
    int read = 0;


    while (strlen(buffer) > 0) {
        read = sscanf(buffer, " %d  %d  %n ", &coef, &exp, &counter);

        if (read == 2 && coef != 0)
            InsertSorted(head, MakePol(coef, exp));

        buffer += counter;

    }

    return 0;
}

int InsertSorted(Position head, Position NewElement) {

    int n = 0;

    while (head->next != NULL && head->next->exp < NewElement->exp) {
        head = head->next;
    }

    if (head->next != NULL && head->next->exp == NewElement->exp) {
        head->next->coef += NewElement->coef;
        n = head->coef;

        if (n == 0)
            ClearZero(head);
    }

    else {
        MakePol(NewElement->coef, NewElement->exp);
        InsertAfter(head, NewElement);
    }

    return 0;
}


int ClearZero(Position head) {
    Position temp = head;
    Position temp1 = NULL;

    while (temp->next != NULL) {

        if (temp->next->coef == 0)
        {
            temp1 = temp->next;
            temp->next = temp1->next;
            free(temp1);
        }

        else {
            temp = temp->next; 
        }

    }
    return 0;
}

int InsertAfter(Position head, Position NewElement) {

    NewElement->next = head->next;
    head->next = NewElement;

    return 0;
}

int Print(Position P) {
    Position temp = P->next;

    while (temp) {
        printf(" %dx^%d  \n", temp->coef, temp->exp);
        temp = temp->next;
    }

    return 0;
}
int Sum(Position p1, Position p2) {
    p1 = p1->next;
    p2 = p2->next;
    Position temp = NULL;
    int coef_sum = 0;

    printf("zbroj je: \t\n");
    while (p1 != NULL && p2 != NULL) {
        if (p1->exp == p2->exp) {
            coef_sum = p1->coef + p2->coef;
            printf("\t%dx^%d\n", coef_sum, p1->exp);
            p1 = p1->next;
            p2 = p2->next;


        }
        else if (p1->exp > p2->exp) {
            printf("\t%dx^%d\n", p2->coef, p2->exp);
            p2 = p2->next;

        }
        else {
            printf("\t%dx^%d\n", p1->coef, p1->exp);
            p1 = p1->next;
        }
    }
    if (p1 == NULL)temp = p2;
    else if (p2 == NULL) { temp = p1; }
    while (temp != NULL) {
        printf(" ovaj:\t%dx^%d", temp->coef, temp->exp);
        temp = temp->next;
    }
    return 0;

}

int Multiply(Position p1, Position p2) {
    int coef_mult = 1, exp_sum = 0;
    p1 = p1->next;
    p2 = p2->next;
    if (p1 == NULL || p2== NULL) { printf("ONE OR BOTH POLINOMES ARE EMPTY"); }
    while (p1 != NULL) {
        coef_mult = coef_mult * p1->coef;
        exp_sum = exp_sum + p1->exp;
        printf("trenutno stanje : %dx^%d\n", coef_mult, exp_sum);
        p1 = p1->next;

    }
    while (p2 != NULL) {
        coef_mult = coef_mult * p2->coef;
        exp_sum = exp_sum + p2->exp;
        printf("trenutno stanje : %dx^%d\n", coef_mult, exp_sum);
        p2 = p2->next;
    }
    printf("Rjesenje je : %dx^%d", coef_mult, exp_sum);
    return 0;
}
