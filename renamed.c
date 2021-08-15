#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerh.h"
#include <ctype.h>
#include <errno.h>

int main(){
    
    FILE* usersFl=fopen("users.txt","r");
    
    struct userInfo toUse;


if(usersFl !=NULL){

printf("Connected\n\n");

char ansChar;
printf("Are you a new user?(Y/N)");
fflush(stdin);
scanf("%c",&ansChar);

char name[50], passw[50];
printf("\nEnter user name: ");
scanf("%s",name);

printf("\nEnter password: ");
scanf("%s",passw);

if(tolower(ansChar)=='y'){
      if(createUser(usersFl,name,passw)){
         setState(name,1);
         printf("\nUser created!\n");
         onLogin();
    }else{
        printf("\nAn error occurred\n");
}
}

else if(tolower(ansChar)=='n'){
        if(loginUser(usersFl,name,passw)){
            setState(name,1);
            printf("\nUser logged in!\n");
            onLogin();
        }else{
            printf("\nInvalid Credentials!\n");
        }
}
else{
    fprintf(stderr,"Invalid INput\n");
    exit(1);
}

}
else{
printf("%d",errno);
exit(1);
}


}