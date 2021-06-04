#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <ctype.h>

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

int createUser(MYSQL *conn, char* name, char* pass){


printf("\t\t--WELCOME NEW USER--\n");

char querystring[500];

sprintf(querystring,"INSERT INTO users(name,password) VALUES(\'%s\',\'%s\') ",name,pass);

printf("\n%s\n",querystring);

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
    printf("\n%s\n",querystring);


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
      if(strcmp(name,row[0])==0 && strcmp(pass,row[1])){
          printf("\nUser successfully logged in!");
      }else{
          printf("\nInvalid user input!");
      }
  }

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
    printf("\nUser created!");
}else{
    printf("\nAn error occurred");
}
}

else if(tolower(ansChar)=='n'){
if(loginUser(conn,name,passw)){
    printf("\nUser created!");
}else{
    printf("\nAn error occurred");
}
}


else{
    fprintf(stderr,"Invalid INput");
    exit(1);
}


 
mysql_close(conn);
return EXIT_SUCCESS;

}

