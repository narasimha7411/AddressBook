#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<strings.h>
#include "contact.h"
#include "function.h"
#include "file.h"

// Initialize the address book structure and load saved data from disk.
void initialize(AddressBook *addressBook){
    addressBook->contactCount=0;
    loadContactFromFile(addressBook);
}

// Prompt the user for name, phone, and email, validate the input,
// and add the new contact to the address book.
void createContact(AddressBook *addressBook){

    char name[30];
    char phone[12];
    char email[50];

    
    inputName(name);
    inputPhone(phone,addressBook);
    inputemail(email,addressBook);    

    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);

    addressBook->contactCount++;

}

// Display search options and also used to select a contact for editing or deletion.
// Returns the index of the selected contact or -1 when not found.
short searchContact(AddressBook *addressBook){

    short sortChoice;
    while(1){
        
        printf("***************************************\n");    
        printf("|     Select the Sorting Criteria     |\n");
        printf("---------------------------------------\n");
        printf("|   1   |   %-25s |\n","SEARCH BY NAME ");
        printf("|   2   |   %-25s |\n","SEARCH BY PHONE");
        printf("|   3   |   %-25s |\n","SEARCH BY EMAIL");
        printf("---------------------------------------\n"); 
        printf("Enter your choice: ");
        
        if (scanf("%hd", &sortChoice) != 1) {
            int _ch;
            while ((_ch = getchar()) != '\n' && _ch != EOF);
            printf("Invalid Input..\n");
            continue;
        }

        if(sortChoice>= 1 && sortChoice<= 3){
            break;
        }
        printf("Invalid Input..");
    }
    short index;
    switch(sortChoice){

        case 1:
            index = search_by_name(addressBook);
            break;
        case 2:
            index = search_by_phone(addressBook);
            break;
        case 3:
            index = search_by_email(addressBook);
            break;
        default:
            printf("Inavlid Input\n");
    }
    
    return index;
}

// Allow the user to choose a field to update for the selected contact.
void editContact(AddressBook *addressBook){
    
    short index = searchContact(addressBook);
    if(index<0){
        return ;
    }

    short choice;
    while(1){
        printf("Edit Options: \n");
        printf("1.Edit Name \n");
        printf("2.Edit Phone N.O \n");
        printf("3.Edit Email ID \n");

        printf("***************************************\n");    
        printf("|            Edit Options             |\n");
        printf("---------------------------------------\n");
        printf("|   1   |   %-25s |\n","EDIT NAME ");
        printf("|   2   |   %-25s |\n","EDIT PHONE N.O ");
        printf("|   3   |   %-25s |\n","Edit Email ID ");
        printf("---------------------------------------\n"); 
        printf("Enter your choice: ");
        if (scanf("%hd", &choice) != 1) {
            int _ch;
            while ((_ch = getchar()) != '\n' && _ch != EOF);
            printf("Invalid Input..\n");
            continue;
        }

        if(choice>= 1 && choice<= 3){
            break;
        }
        printf("Invalid Input..");
    } 

    switch(choice){

        case 1: 
            editname(addressBook,index);
            break;
        case 2:
            editphone(addressBook,index);
            break;
        case 3:
            editemail(addressBook,index);
            break;
        default :
            printf("Invalid Input..\n");
    }

    printf("Edited Successfully..\n");
    display(addressBook->contacts,index);
    return ;
}

// Remove the selected contact by shifting later entries left.
void deleteContact(AddressBook *addressBook){

    short index = searchContact(addressBook);

    if(index<0){
        return ;
    }
    char ch[4];
    printf("Do you to delet(yes/no): ");
    scanf(" %[^\n]",ch);
    if(strcasecmp(ch,"yes")!=0){
        printf("Deletion Cancelled..\n");
        return ;
    }
    for(short i=index;i< (addressBook->contactCount)-1;i++){

        addressBook->contacts[i] = addressBook->contacts[i+1];
    }

    addressBook->contactCount --;

    printf("Contact Deleted Successfully..\n");
    return ;
}

// Sort and display all contacts in the address book.
void listContact(AddressBook *addressBook){

    if(addressBook->contactCount == 0){
        printf("AddressBook is Empty\n");
        return ;
    }

    if(addressBook->contactCount > 1){
        int start=0;
        int end = (addressBook->contactCount)-1;

        quicksort(addressBook->contacts,start,end); // Sort contacts by name using quicksort(most efficient).
    }
    // AddressBook *ad = addressBook;
    // for(short i = 0; i < ad->contactCount-1; i++){           // Bubble sort to sort contacts by name(more time consuming).
    // for(short j = 0; j < ad->contactCount-i-1; j++){
    //     if(strcmp(ad->contacts[j].name, ad->contacts[j+1].name) > 0){
    //         //swap contacts
    //         Contact temp = ad->contacts[j];
    //         ad->contacts[j] = ad->contacts[j+1];
    //         ad->contacts[j+1] = temp;
    //     }
    // }
    // }
    

    printf("---------------------------------------------------------------------------------\n");
    printf("|                               ADDRESS BOOK                                     |\n");
    printf("*********************************************************************************\n");
    printf("| %-3s | %-25s | %-10s | %-30s |\n","S.No", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------------------\n");

    for(short i = 0; i < addressBook->contactCount; i++)
    {
        printf("|  %-3d | %-25s | %-10s | %-30s |\n", 
            i+1, 
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    printf("----------------------------------------------------------------------------------\n");

    return;
}

// Save the current contacts to disk and terminate the program.
void saveContact(AddressBook *addressBook){
    saveContactToFile(addressBook);
    printf("Saving  and Exiting..\n");
    exit(0);
}
