#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
/*
Name : Venkata Ravindra Nandhem
Batch Id : 26015b
Date : 29/8/2026
Project Title : Address Book

Description: 
Address Book is a menu-driven C application used to manage and organize contact information efficiently. 
It allows users to create, search, edit, delete, and display contacts containing details such as name, phone number, and email ID. 
The project uses structures, arrays, functions, strings, pointers, and file handling to store and manage contact data.

Main Features
Create Contact – Add a new contact with name, phone number, and email.
Search Contact – Search contacts using name, phone number, or email ID.
Edit Contact – Modify the details of an existing contact.
Delete Contact – Remove a selected contact from the address book.
Display Contacts – Display all stored contacts.
Save Contacts – Store contact information in a file.
Load Contacts – Retrieve previously saved contacts when the program starts.

*/
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int validateName(char name[]);
int validatePhone(char phone[],AddressBook *addressBook,int index);
int validateEmail(char email[],AddressBook *addressBook,int index);
void searchContact(AddressBook *addressBook);
int Search_by_name(AddressBook *addressBook);
int Search_by_Phonenumber(AddressBook* addressBook);
int Search_by_Emailid(AddressBook* addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);


#endif
