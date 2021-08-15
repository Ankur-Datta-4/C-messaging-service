
struct userInfo{
    char* name;
    char* pass;
    int isLoggedIn;
}currentUser;



int setState(char* userName, int isActive);
int createUser(FILE *conn, char* name, char* pass);
int loginUser(FILE *conn, char* name, char* pass);
void printOptions();
int onLogin();