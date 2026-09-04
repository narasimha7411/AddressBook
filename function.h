#ifndef FUNCTION_H //#ifndef is used to prevent multiple inclusions of the same header file, which can cause compilation errors.
#define FUNCTION_H

// Return nonzero if the character is alphanumeric.
char isalpnum(char c);

void display(Contact *contacts,short index);

int validName(char *name);
void inputName(char *name);

int validPhone(char *phone,AddressBook *addressBook);
void inputPhone(char *phone,AddressBook *addressBook);

int  validemail(char *email,AddressBook *addressBook);
void  inputemail(char *email,AddressBook *addressBook);
  
void swap(Contact *contacts1,Contact *contacts2);
int partition(Contact contacts[],int start,int end);
void quicksort(Contact *conacts,int start,int end);

short search_by_name(AddressBook *addressBook);
short search_by_phone(AddressBook *addressBook);
short search_by_email(AddressBook *addressBook);

void editname(AddressBook *addressBook,short index);
void editphone(AddressBook *addressBook,short index);
void editemail(AddressBook* addressBook,short index);

#endif