#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAXNAME 128
#define MAXRED 1024
#define MAXPOINT 50
#define EXIT_SUCESS 0
#define EXIT_UNSUCESS -1
#define MAXLINE 120

typedef struct studenti{
char name[MAXNAME];
char surname[MAXNAME];
int points[MAXPOINT];
}Student;


int ReadNoRowsInFile(char NameData[MAXNAME]){
  int counter=0;
  FILE *filePointer=fopen(NameData,"r"); 
  // mora ovako jer Varijabla NameData je deklarirana kao FILE * i postavljena na NULL. Međutim, NameData bi trebala biti putanja do datoteke, a ne pokazivač na FILE.
  char buffer[MAXLINE]={0};

  if (!filePointer){
    printf("\nFile is not opened\n");
    return EXIT_UNSUCESS;
    else {
    printf("\n uspjelo je \n");
    }
  while(fgets(buffer,MAXLINE,filePointer)){ 
    // sa fgets odvojeno i !feof(filePointer) se cita jedna dodatna linija
    if(strcmp("\n",buffer)!=0){
      counter++;
    }
  }
  fclose(filePointer);
  return counter;
  }
}


  void printingStunet(Student *stud , int numStud){
    double average=0;
    int i=0;
    for(i=0;i<numStud;i++){
      average=(double)(stud+i)->points /MAXPOINT;
      Printf("\n Student %s %s imao je %s bodova, odnosno %s prosjek",(stud+i)->name, (stud+i)->surname, (stud+i)->points, average*100);
    }
  }

 void readingStudent(Student *stud, int noRows, char NameData[MAXNAME]){
   FILE *fp=fopen(NameData,"r");
   int i=0;
   if(fp==NULL){
     printf("\n data error \n");
   }
   else{
     printf("\n sucessful \n");
   }
   for(i=0;i<noRows;i++){
     fscnaf(fp,"%s %s %d",(stud+i)->name, (stud+i)->surname, &(stud+i)->points);
     
   }
   fclose(fp);
 }




int main() {
  int noRows=0;
  char NameData[MAXNAME];
    printf("\n Upisite ime datoteke");
    scanf("%s",NameData);

  //datoteka se otvara u funkcijama ne u mainu nema potrebe
  
  noRows= ReadNoRowsInFile(NameData);
  printf("%d",noRows);
  Student *stud=(Student*)malloc(noRows*sizeof(Student));
readingStudent(stud,noRows,NameData);
  printingStudent(stud, noRows);
  
 
  free(stud);
      return EXIT_SUCESS;
  }
 
  