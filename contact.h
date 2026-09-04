#ifndef CONTACT_H  //ifndef is used to prevent multiple inclusions of the same header file, which can cause compilation errors.
#define CONTACT_H

#define MAX_CONTACTS 100

// A single contact entry with name, phone number, and email.
typedef struct{
    char name[30];
    char phone[12];
    char email[50];
} Contact;

// The address book container holding up to MAX_CONTACTS entries.
typedef struct 
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;

}AddressBook;

void createContact(AddressBook *addressBook);
short searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContact(AddressBook *addressBook);
void saveContact(AddressBook *addressBook);

// Initialize the address book and load any saved contacts.
void initialize(AddressBook *addressBook);

#endif // end of CONTACT_H