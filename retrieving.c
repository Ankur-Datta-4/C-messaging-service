#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <mysql/mysql.h>
#include <stdio_ext.h>

static char* host = "localhost";
static char* user ="xenon";
static char* pass="xenon";
static char* dbname="testdb";

unsigned int port = 3306;

static char *unix_socket=NULL;
unsigned int flag=0;


void finish_with_error(MYSQL *conn){
  fprintf(stderr, "%s\n", mysql_error(conn));
  mysql_close(conn);
  exit(1);
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
char queryString[600];
sprintf(queryString,"INSERT INTO messages(uid,message) VALUES((select id from users where name=\'%s\'),\'%s\')",recipientName,messageString);
if (mysql_query(conn, queryString)){
      finish_with_error(conn);
  }
else{
    return 1;
}
}

int viewMessage(MYSQL *conn){
    return 0;
}

int main(){
    MYSQL *conn;

    conn=mysql_init(NULL);

    if(!(mysql_real_connect(conn, host, user, pass,dbname, port,unix_socket, flag))){
        fprintf(stderr, "\nError %s [%d]\n",mysql_error(conn),mysql_errno(conn));
        exit(1);
    }

printf("Connected\n\n");

printf("\tPress S to send message\n\tPress V to View messages\n");
char c=0;
fflush(stdin);
while(!(c=getchar()));
if(tolower(c)=='s'){
    if(sendMessage(conn)){
        printf("\nMessage Sent!");
    }
}else if(tolower(c)=='v'){
    if(!viewMessage(conn)){
        printf("\nUggh!One more error!");
    }
}else{
    printf("Invalid Input");
}


mysql_close(conn);
return EXIT_SUCCESS;

}