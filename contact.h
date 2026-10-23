#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct
{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;


/* Create */
void createContact(AddressBook *addressBook);

/* Search */
void searchContact(AddressBook *addressBook);

/* Edit */
void editContact(AddressBook *addressBook);

/* Delete */
void deleteContact(AddressBook *addressBook);

/* List */
void listContacts(AddressBook *addressBook);

/* Initialize */
void initialize(AddressBook *addressBook);

/* File handling */
void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);


/* Validation functions */
int isValidName(const char *name);
int isValidPhone(const char *phone);
int isPhoneUnique(AddressBook *addressBook, const char *phone);
int isValidEmail(const char *email);
int isEmailUnique(AddressBook *addressBook, const char *email);

#endif


