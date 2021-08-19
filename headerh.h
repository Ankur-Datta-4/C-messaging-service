
struct userInfo{
    char name[100];
    
    
        int isLoggedIn;
        struct messageInfo{
        char senderName[100];
        char recipientName[100];
        char messageText[500];
        char sendTime[50];
        char links[100];
    
    }msg;
    
}currentUser;



int setState(char* userName, int isActive);
int createUser(char* name, char* pass);
int loginUser(char* name, char* pass);
void printOptions();
int onLogin();
int checkChar(char);