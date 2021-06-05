#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <ctype.h>
#include <stdio_ext.h>

static char* host = "localhost";
static char* user ="xenon";
static char* pass="xenon";
static char* dbname="testdb";

unsigned int port = 3306;

static char *unix_socket=NULL;
unsigned int flag=0;

struct userInfo{
    char* name;
    int isLoggedIn;
}currentUser;

void finish_with_error(MYSQL *conn){
  fprintf(stderr, "%s\n", mysql_error(conn));
  mysql_close(conn);
  exit(1);
}

int setState(char* userName, int isActive){
    if(isActive==1){
        currentUser.name=userName;
        currentUser.isLoggedIn=1;
    }else{
        currentUser.name=NULL;
        currentUser.isLoggedIn=0;
    }
}
int createUser(MYSQL *conn, char* name, char* pass){


printf("\t\t--WELCOME NEW USER--\n");

char querystring[500];

sprintf(querystring,"INSERT INTO users(name,password) VALUES(\'%s\',\'%s\') ",name,pass);


 if(mysql_query(conn, querystring)){
     return(0);
 }
 else{
     return 1;
 }

}


int loginUser(MYSQL *conn, char* name, char* pass){
    
    
    char querystring[500];
    //to be confirmed, last calculated
    sprintf(querystring,"SELECT name,password FROM users where name=\'%s\'",name);



    if (mysql_query(conn,querystring)) {
    fprintf(stderr,"Invalid user credentials");
      finish_with_error(conn);
  }else{
      MYSQL_RES *res=mysql_store_result(conn);
      if(res==NULL){
          finish_with_error(conn);
      }
      MYSQL_ROW row;
      row=mysql_fetch_row(res);
      if(strcmp(name,row[0])==0 && strcmp(pass,row[1])==0){
          return 1;
      }else{
          return 0;
      }
  }

}


int sendMessage(MYSQL *conn){

char recipientName[50];
__fpurge(stdin);
printf("\nWhom do you want to send the message to..? ");
scanf("%[a-z]s",recipientName);
__fpurge(stdin);
char messageString[100];
printf("\nMessage: ");
scanf("%[^\n]s",messageString);

char messageStringWithName[120];
sprintf(messageStringWithName,"%s: %s",currentUser.name,messageString);

char queryString[600];
sprintf(queryString,"INSERT INTO messages(uid,message) VALUES((select id from users where name=\'%s\'),\'%s\')",recipientName,messageStringWithName);
if (mysql_query(conn, queryString)){
      finish_with_error(conn);
  }
else{
    return 1;
}
}

int viewMessages(MYSQL *conn){
    char queryString[600];
    sprintf(queryString,"SELECT message from messages where uid=(select id from users where name=\'%s\')",currentUser.name);
    if(mysql_query(conn,queryString)){   
        finish_with_error(conn);
    }
    else{
       MYSQL_RES *result = mysql_store_result(conn);

        if (result == NULL){
            finish_with_error(conn);
        }

        MYSQL_ROW row;

        while ((row = mysql_fetch_row(result))!=NULL){
            printf("%s \n",row[0]);
        }
        return 1;

    }
}

void printOptions(){
    printf("\n\tPress S to send message\n\tPress V to View messages\n\tPress Q to Sign out\n");
}

int onLogin(MYSQL *conn){
char c=0;
__fpurge(stdin);

while(currentUser.isLoggedIn){
    printOptions();
    while(!(c=getchar()));
    __fpurge(stdin);
    if(tolower(c)=='s'){
        if(sendMessage(conn)){
           printf("\nMessage Sent!");
           __fpurge(stdin);
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
printf("Logged out!\n");
exit(1);

}


int main(){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW *row;

    conn=mysql_init(NULL);

if(!(mysql_real_connect(conn, host, user, pass,dbname, port,unix_socket, flag))){
        fprintf(stderr, "\nError %s [%d]\n",mysql_error(conn),mysql_errno(conn));
        exit(1);
    }

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
      if(createUser(conn,name,passw)){
         setState(name,1);
         printf("\nUser created!\n");
         onLogin(conn);
    }else{
        printf("\nAn error occurred\n");
}
}

else if(tolower(ansChar)=='n'){
        if(loginUser(conn,name,passw)){
            setState(name,1);
            printf("\nUser logged in!\n");
            onLogin(conn);
        }else{
            printf("\nInvalid Credentials!\n");
        }
}
else{
    fprintf(stderr,"Invalid INput\n");
    exit(1);
}



 
mysql_close(conn);
return EXIT_SUCCESS;

}

