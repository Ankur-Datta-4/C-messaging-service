
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerh.h"
#include <ctype.h>
#include <errno.h>
#include <conio.h>



int setState(char* userName, int isActive);
int createUser( char* name, char* pass);
int loginUser(char* name, char* pass);
void printOptions();
int onLogin();
int checkChar(char);

int main(){
    
    FILE* usersFl=fopen("users.txt","r");
    
    struct userInfo toUse;


if(usersFl !=NULL){

printf("Connected\n\n");
fclose(usersFl);


char ansChar;
printf("Are you a new user?(Y/N)");
fflush(stdin);
scanf("%c",&ansChar);
if(checkChar(ansChar)==0){
    printf("\nInvalid Input!\n");
    exit(EXIT_FAILURE);
    //EXIT_FAILURE====>1, SUCCESS==>0
    
}

char name[50], passw[50],c=0;
int i,flag=1;
printf("\nEnter user name: ");
scanf("%s",name);

printf("\nEnter password: ");
scanf("%s",passw);


if(tolower(ansChar)=='y'){
      if(createUser(name,passw)){
        printf("\n\n\t\tWelcome New User");
         setState(name,1);
         onLogin();
    }else{
        printf("\nAn error occurred");
}
}

else{
        if(loginUser(name,passw)){
            setState(name,1);
            printf("\nUser logged in!\n");
            onLogin();
        }else{
            printf("\nInvalid Credentials!\n");
        }
}


}
else{
printf("%s",strerror(errno));
exit(1);
}


}