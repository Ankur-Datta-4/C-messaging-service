# C-messaging-service
A DM service using C programming with mySQL as middleware.

### Working:
* A user logs as a new/existing user. user-Info is compared against the one in DB to authenticate.
* The user is presented with these options on successfull login,(else:error is reported):
    - Sending message.
    - Reading received messages.
    - Sign out
* sendMessage/viewMessages function, communicate with the mySQL server to send/retrieve messages.
* The afore options mentioned options are presented to the user, until they decide to logOut.
* No Encryption/Decryption as it is centralised.

![SS of exec](https://github.com/Ankur-Datta-4/C-messaging-service/blob/ef71147ec263213371e5189211a43c8e656e61cb/susess.png)

### Schema for Databases: 
create table users(
id INT auto_increment primary key,
name varchar(20) not null,
password varchar(20) not null);

create table messages(
id INT auto_increment primary key,
uid INT,
message varchar(255),
foreign key(uid) references users(id)
);

### Index for functions:

* finish_with_error(MYSQL *conn): reports the error-number(SQL) and exits, abruptly.(dev-only)
* setState(char *name,int isActive):updates the currentUser structure.
* createUser(MYSQL *conn, char *name, char *password):adds a new record to the users-table.
* loginUser(MYSQL *conn, char *name, char *password): checks if the user-input name and password matches with that in DB.
* sendMessage(MYSQL *conn): inserts a message record to the messages table with the user-input-content.
* viewMessages(MYSQL *conn): reads messages from the message-table, of the current-user.
* printOptions(): prints the options: send, view, and sign-out for receiving user input. 
* onLogin(): contains the calls to sendMessage() and viewMessage.
