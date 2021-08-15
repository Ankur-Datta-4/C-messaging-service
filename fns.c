
#include <stdio.h>
#include <stdlib.h>
#include "headerh.h"
#include <string.h>
#include <ctype.h>

int setState(char* userName, int isActive){
    if(isActive==1){
        currentUser.name=userName;
        currentUser.isLoggedIn=1;
    }else{
        currentUser.name=NULL;
        currentUser.isLoggedIn=0;
    }
}
int createUser(FILE *conn, char* name, char* pass){


printf("\t\t--WELCOME NEW USER--\n");

int res=fprintf(conn,"\n%s %s",name,pass);

 if(res<0){
     return(0);
 }
 else{
     return 1;
 }

}


int loginUser(FILE *conn, char* name, char* pass){
    
    
    rewind(conn);
    struct userInfo iter;
    char nameBuff[100],passBuff[100];
    while(fscanf(conn,"%s %s",iter.name,iter.pass) != EOF){
        if(strcmp(iter.name,name)==0){
            if(strcmp(iter.pass,pass)!=0){
                fprintf(stderr,"Invalid user credentials");
                return 0;
            }
            return 1;
        }
    }
    fprintf(stderr,"User doesn't exist!");
    return 0;
  
  }


int sendMessage(){

    char recipientName[50];
    fflush(stdin);
    printf("\nWhom do you want to send the message to..? ");
    scanf("%[a-z]s",recipientName);
    fflush(stdin);
    sprintf(recipientName,".txt");
    FILE *conn = fopen(recipientName,"a+");
    char messageString[100];
    printf("\nMessage: ");
    scanf("%[^\n]s",messageString);

    char messageStringWithName[120];
    sprintf(messageStringWithName,"%s: %s\n",currentUser.name,messageString);

//fseek(conn,0,SEEK_END);
int res=fprintf(conn,"%s",messageStringWithName);
if (res<=0){
      return 0;
  }
else{
    return 1;
}
fclose(conn);
}

int viewMessages(FILE *conn){
    char recString[600];
    while(fgets(recString,100,conn) != NULL){
        fputs(recString,conn);
    }
    return 1;

}


void printOptions(){
    printf("\n\tPress S to send message\n\tPress V to View messages\n\tPress Q to Sign out\n");
}

int onLogin(){
char c=0;
fflush(stdin);
char uFile[70];
sprintf(uFile,"%s.txt",currentUser.name);
FILE* conn=fopen(uFile,"w+");
while(currentUser.isLoggedIn){
    printOptions();
    while(!(c=getchar()));
    fflush(stdin);
    if(tolower(c)=='s'){
        if(sendMessage()){
           printf("\nMessage Sent!");
           fflush(stdin);
    }
    }else if(tolower(c)=='v'){
        if(!viewMessages(conn)){
            printf("\n Error in viewing message! \n"); 
        }

    }else if(tolower(c)=='q'){
        currentUser.isLoggedIn=0;
    }
    else{
    printf("Invalid Input");
}
c=0;
}
fclose(conn);
printf("Logged out!\n");
exit(1);

}