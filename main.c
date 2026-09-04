/*
 * Name: Narasimha S
 * Duration: 30/07/2026 - 6/08/2026(1 week).
 * Project: Address Book Management System
 * Description: A simple console-based contact manager that lets the user
 *              create, search, edit, delete, list, and save contacts.
 * Highlights: Using quick sort for efficent sorting,
 *             searching by name, phone, or email with substring matching.
 */


#include<stdio.h>
#include<stdlib.h>
#include "contact.h"

// Main entry point for the address book program.
// Initializes the address book and runs the menu loop.
int main(){
    int choice;
    AddressBook addressBook;
    char line[32];

    // Initialize the address book and load contacts from file.
    initialize(&addressBook);

    do{
        printf("\n\n***************************************\n");    
        printf("|           ADDRESS BOOK MENU         |\n");
        printf("---------------------------------------\n");
        printf("|   1   |   %-25s |\n","CREATE CONTACT");
        printf("|   2   |   %-25s |\n","SEARCH CONTACT");
        printf("|   3   |   %-25s |\n","EDIT CONTACT");
        printf("|   4   |   %-25s |\n","DELETE CONTACT");
        printf("|   5   |   %-25s |\n","LIST ALL CONTACTS");
        printf("|   6   |   %-25s |\n","SAVE AND EXIT");
        printf("|   7   |   %-25s |\n","EXIT");
        printf("---------------------------------------\n"); 

        printf("Choose your Option: ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break; // handle EOF gracefully
        }

        if (sscanf(line, "%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch(choice){

            case 1:
                // Create a new contact and add it to the address book.
                createContact(&addressBook);
                break;
            case 2:
                // Search contacts by name, phone, or email.
                searchContact(&addressBook);
                break; 
            case 3:
                // Edit an existing contact.
                editContact(&addressBook);
                break;
            case 4:
                // Delete a contact from the address book.
                deleteContact(&addressBook);
                break;
            case 5:
                // Display all saved contacts.
                listContact(&addressBook);
                break;
            case 6:
                // Save contacts to file and exit the program.
                saveContact(&addressBook);
                break;
            case 7:
                // Exit without saving changes.
                printf("Exited Successfully..\n");
                return 1;
            default :
                // Handle invalid menu option.
                printf("Invalid Choice. Please try again..\n");
        }
    }while(choice != 6);

    return 0;
}