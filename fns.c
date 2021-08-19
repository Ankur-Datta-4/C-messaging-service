
#include <stdio.h>
#include <stdlib.h>
#include "headerh.h"
#include <string.h>
#include <ctype.h>
#include <time.h>

int setState(char* userName, int isActive){
    if(isActive==1){
        strcpy(currentUser.name,userName);
        currentUser.isLoggedIn=1;
    }else{
        *(currentUser.name)=NULL;
        currentUser.isLoggedIn=0;
    }
}

int checkChar(char c){
    int status=0;
    char temp=tolower(c);
    if(temp=='y' || temp=='n')
        status=1;
    return status;
}

int createUser(char* name, char* pass){

FILE *conn=fopen("users.txt","a+");


int res=fprintf(conn,"\n%s %s",name,pass);

fclose(conn);
 if(res<0){
     
     return 0;
 }
 else{

     return 1;
 }




}


int loginUser(char* name, char* pass){
  
    FILE* conn=fopen("users.txt","r");
    
   
    char nameBuff[100],passBuff[100];
   
    while(fscanf(conn,"%s %s\n",nameBuff,passBuff) != EOF){
        
        if(strcmp(nameBuff,name)==0){
            if(strcmp(passBuff,pass)!=0){
                fprintf(stderr,"\nInvalid user credentials");
                return 0;
            }
           
            return 1;
        }
    }
    fclose(conn);
    fprintf(stderr,"\nUser doesn't exist!");
    return 0;
  
  }


int sendMessage(){
    FILE *conn=fopen("msgs.txt","a+");
    time_t t;
    time(&t);
     struct userInfo iter;
    printf("\nWhom do you want to send the message to..? ");
    scanf("%s",iter.msg.recipientName);
   fflush(stdin);
    char c=0;
    printf("\nMessage: ");
    scanf("%[^\n]s",iter.msg.messageText);
    printf("\nDo you want to attach anything..?");
    fflush(stdin);
    scanf("%c",&c);
    if(checkChar(c)==1 && tolower(c)=='y'){
        fflush(stdin);
        printf("\nEnter the link: ");
        scanf("%[^\n]s",iter.msg.links);
        printf("\n%s",iter.msg.links);
    }
    fseek(conn,0,SEEK_END);
    strcpy(iter.msg.sendTime,ctime(&t));
    strcpy(iter.msg.senderName,currentUser.name);
    
    int res=fwrite(&(iter.msg),sizeof(struct messageInfo),1,conn);
    fclose(conn);
if (res<1){
      return 0;
  }
else{
    return 1;
}
}

int viewMessages(){
    int res=0;
    struct userInfo iter;
    FILE* conn= fopen("msgs.txt","r+");
    rewind(conn);
   
    while((res=fread(&(iter.msg),sizeof(struct messageInfo),1,conn))){
       
        //  printf("\nCC%s: %s \n\t\t%s",currentUser.msg.senderName,currentUser.msg.messageText,currentUser.msg.sendTime);
        if(strcmp(iter.msg.recipientName,currentUser.name)==0){
            char time[20];
            strncpy(time,iter.msg.sendTime,19);
            printf("\n%s: %s\nLinks: %s\n\t\t\t%s",iter.msg.senderName,iter.msg.messageText,iter.msg.links,time);
            
        }
    }
    
    return 1;

}


void printOptions(){
    printf("\n\tPress S to send message\n\tPress V to View messages\n\tPress Q to Sign out\n");
}

int onLogin(){

char c=0;
fflush(stdin);

while(currentUser.isLoggedIn){
    printOptions();
    while(!(c=getchar()));
    fflush(stdin);
    if(tolower(c)=='s'){
        if(sendMessage()){
           printf("\nMessage Sent!");
           fflush(stdin);
    }else{
        printf("\nError sending message..");
    }
    }else if(tolower(c)=='v'){
        if(!viewMessages()){
            printf("\n Error in viewing message! \n"); 
        }

    }
    else if(tolower(c)=='q'){
        currentUser.isLoggedIn=0;
    }
    else{
    printf("Invalid Input");
}
c=0;
}

printf("Logged out!\n");
exit(1);

}