#include <stdio.h>
#include <stdlib.h>
//take user input and check if it is correct

int main(){
printf("\t\t\tHello user\n");
printf("\nEnter Username: ");
char userName[10];
char password[10];
scanf("%[^\n]s",userName);
fflush(stdin);
printf("\nEnter Password: ");
scanf("%[^\n]s",password);
fflush(stdin);
printf("reading..");
FILE *p;
p=fopen("C:\\Users\\ankur\\Desktop\\class\\project_test\\users.txt","r");
printf("\nPointer received");
char nameFromFile[20], passFromFile[20];
printf("\n");
fscanf(p,"%[^\n]s",nameFromFile);
fscanf(p,"%s",passFromFile);
fclose(p);
printf("File closed..\n");
printf("%s",nameFromFile);
printf("\n%s",passFromFile);


}