# C-messaging-service
A DM service using C programming

First: Login system created, accepts both new and existing users. App exits when the credentials do no match, for existing users.

--->
    DataBASE Schema yet to posted.
    current plan: user table, messages table: id is the foreign key. 
        --> to figure, how to store a stack of messages
 
 ----> Messaging isn't validated yet. No plans also.
 
 This is part A.
 4 parts, yet to come.


PART B:

Able to send messages to other people.
MEssage retrival function yet to be made.
Login System is independent.

**NOTE**:: Both the files have seperate int mains, cos, it helps in easy development and testing.
**NOTE**:The following is the schema for the two tables used inside testdb:(you can paste them on the terminal of mysql)

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
