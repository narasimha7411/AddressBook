#include<stdio.h>
#include<string.h>
#include "contact.h"
#include "function.h"
#include "file.h"

// Return true if character is a letter or digit.
char isalpnum(char c){

    if((c>='A' && c <= 'Z')|| (c >='a' && c<= 'z') || (c>='0' && c<='9')){
        return 1;;
    }
    return 0;
}

// Print the selected contact's details in a formatted block.
void display(Contact *contacts,short index){

    printf("****************************************\n");    
    printf("|           CONTACT DETAILS            |\n");
    printf("----------------------------------------\n");
    printf("| NAME    | %-25s |\n",contacts[index].name);
    printf("| PHONE   | %-25s |\n",contacts[index].phone);
    printf("| EMAIL   | %-25s |\n",contacts[index].email);
    printf("----------------------------------------\n\n"); 

    return;
}
// Validate that the name contains only letters, spaces, or periods.
int validName(char *name){

    for(int i=0;name[i];i++){

        if(!((name[i]>='A' && name[i]<='Z')||(name[i]>='a' && name[i]<='z')||(name[i]==' ')||(name[i]=='.'))){

            return 0;
        }
    }
    return 1;
}

// Loop until the user enters a valid name.
void inputName(char *name){

    while(1){

        printf("Enter the Name: ");
        scanf(" %[^\n]",name);

        if(validName(name)){
            break;
        }
        else{
            printf("Inavlid Name\n");
        }
    }
}

// Validate the phone number format, length, and check for duplicates.
int validPhone(char *phone,AddressBook *addressBook){

    if(strlen(phone)!=10){
        return 0;
    }

    for(int i=0;phone[i];i++){

        if(!(phone[i] >= '0' && phone[i]<= '9')){
            return 0;
        }
    }
    for(int i=0;i<addressBook->contactCount;i++){

        if(strcmp(phone,addressBook->contacts[i].phone)==0){ 
            return -1;
        }
    }
    return 1;

}
// Loop until the user enters a valid and unique phone number.
void inputPhone(char *phone,AddressBook *addressBook){

    while(1){
        printf("Enter the Phone N.O: ");
        scanf(" %[^\n]",phone);
        
        int ret = validPhone(phone,addressBook);

        if(ret == 1){
            break;
        }
        else if(ret == -1){
             printf("Duplicate Phone No!\n");  
        }
        else{
            printf("Inavlid Phone N.O\n");
        }
    }
}



// Validate the email address format and check for duplicates.
int  validemail(char *email,AddressBook *addressBook){

    int at_count=0,atpos=-1,dot_count=0,dotpos=-1;
    int len = strlen(email);

    if(len<5){  // Minimum length for a valid email is 5 characters (e.g., a@b.c).
        return 0;  
    }

    for(int i=0;email[i];i++){

        if(email[i]=='@'){
            atpos=i;
            at_count++;
        }
    }

    if((atpos <= 0) || (at_count != 1)  ){  
        // '@' should not be the first character and there should be exactly one '@'.
        return 0;
    }

    for(int i=atpos;email[i];i++){

        if(email[i]=='.'){
            dotpos=i;
            dot_count++;
        }
        else if(!(isalpnum(email[i]) || (email[i] == '_') || (email[i]=='-')|| (email[i] == '.')||(email[i] == '@') )){ 
            // Only letters, digits, '_', '-', '.', and '@' are allowed in the email.
            return 0;
        }
    }

    if(( dotpos == -1) || (dotpos == len-1) ||(dot_count != 1) || (dotpos == atpos+1)  ){
         // '.' should not be the last character, there should be exactly one '.', and it should not immediately follow '@'.
        return 0;
    }
    for(int i=0;i<addressBook->contactCount;i++){
        // Check for duplicate email addresses in the address book.
        if(strcmp(email,addressBook->contacts[i].email)==0){ 
            return -1;
        }
    }

    return 1;
}

// Loop until the user enters a valid and unique email address.
void  inputemail(char *email,AddressBook *addressBook){

    while(1){
        printf("Enter the Email: ");
        scanf(" %[^\n]",email);
        int ret = validemail(email,addressBook);
        if(ret == 1){
            break;
        }
        else if(ret == -1){
             printf("Email already exists!.\n");  
        }
        else{
            printf("Invalid Email\n");
        }
    }
    return ;
}
// Swap two contact records in the contacts array.
void swap(Contact *contacts1,Contact *contacts2){

    Contact temp = *contacts1;
    *contacts1 = *contacts2;
    *contacts2 = temp;

    return ;
}

// Partition helper for quicksort using the last element as pivot.
int partition(Contact contacts[],int start,int end){

    char *pivot = contacts[end].name; // Pivot is the last element's name.

    int i=start-1; // Index of the smaller element.

    for(int j=start;j<end;j++){

        if(strcmp(contacts[j].name,pivot)<=0){  // If current element is smaller than or equal to pivot, swap it to the left side.
            i++;                                // Increment index of smaller element.
            swap(&contacts[i],&contacts[j]);
        }
    }

    swap(&contacts[i+1],&contacts[end]);
    return i+1;
}

// Sort contacts alphabetically by name using quicksort.
void quicksort(Contact *contacts,int start,int end){

    
    if(start<end){

        int ret = partition(contacts,start,end); // Partition the array and get the pivot index.

        quicksort(contacts,start,ret-1);// Recursively sort the left subarray.

        quicksort(contacts,ret+1,end);// Recursively sort the right subarray.
    }

    return ;
}

// Search contacts by name substring and allow selection if many match.
short search_by_name(AddressBook *addressBook){

    char name[30];
    inputName(name);
    printf("\n");
    int count=0;
    int index;
    int duplicate[MAX_CONTACTS];    // Array to store indices of matching contacts for later selection.
    for(int i=0;i< (addressBook->contactCount);i++){

        if(strstr(addressBook->contacts[i].name,name) != NULL){ //strstr checks if the name is a substring of the contact's name.
            duplicate[count]=i; // Store the index of matching contacts for later selection.
            index=i;
            count++;

        }

    }   
    
    if(count==0){
        printf("No Matching Contact Found..!\n");
        return -1;
    }
    else if(count == 1){
        printf("One matching contact found with the given name.!\n");
        display(addressBook->contacts,index);
        return index;
    }
    else if(count>1){
        
        printf("Multiple Contacts Found..!\n");
        for(int i=0;i<count;i++){
            index=duplicate[i];        // Display all matching contacts with serial numbers for selection.
            printf("%-3d. ",i+1);
            display(addressBook->contacts,index);
        }

        while (1)
        {
            short choise;
            printf("\nEnter your choise: ");
            scanf("%hd",&choise);

            if(choise >=1 && choise<= count){
                // Get the index of the selected contact based on user input and (choice-1) tells us the index of the selected contact in the duplicate array.
                int serial_num = duplicate[choise-1]; 
                display(addressBook->contacts,serial_num);
                return serial_num;
            }
            printf("Invalid Input..\n");
        }
    }

    printf("Invalid Input..\n");
    return -1;
}
// Search contacts by phone number and return the index of the matching contact.
short search_by_phone(AddressBook *addressBook){

    char phone[11];
    printf("Enter Phone N.O: ");
    scanf(" %[^\n]",phone);
    printf("\n");

    AddressBook *ad=addressBook;

    for(short i=0;i< ad->contactCount;i++){

        if(strcmp(phone,ad->contacts[i].phone)==0){
            display(ad->contacts,i);
            return i;
        }
    }
    printf("Invalid Input..\n");
    return -1;
}

// Search contacts by partial email match and allow selection when multiple matches exist.
short search_by_email(AddressBook *addressBook){

    char email[30];
    printf("Enter Email ID: ");
    scanf("%s",email);
    printf("\n");

    int count=0;
    int index;
    int duplicate[MAX_CONTACTS];
    for(int i=0;i< (addressBook->contactCount);i++){

        if(strstr(addressBook->contacts[i].email,email) != NULL){ //strstr checks if the email is a substring of the contact's email.
            duplicate[count]=i;
            index=i;
            count++;

        }

    }   
    
    if(count==0){
        printf("No Matching Contact Found..!\n");
        return -1;
    }
    else if(count == 1){
        printf("One matching contact found with the given email_id.!\n");
        display(addressBook->contacts,index);
        return index;
    }
    else if(count>1){
        
        printf("Multiple Contacts Found..!\n");
        for(int i=0;i<count;i++){
            index=duplicate[i];
            printf("%-3d. ",i+1);
            display(addressBook->contacts,index);
        }
        short choise;
        while (1)
        {
            
            printf("\nEnter your choice: ");
            scanf("%hd",&choise);

            if(choise >=1 && choise<= count){
                // Get the index of the selected contact based on user input .
                int serial_num = duplicate[choise-1];
                display(addressBook->contacts,serial_num);
                return serial_num;
            }
            printf("Invalid Input..\n");
        }
    }
    printf("Invalid Input..\n");
    return -1;
}

// Update the stored name for the selected contact.
void editname(AddressBook *addressBook,short index){

    char name[20];
    inputName(name);
    strcpy(addressBook->contacts[index].name,name);

    return ;
}

// Update the stored phone number for the selected contact.
void editphone(AddressBook *addressBook,short index){
    char phone[11];
    inputPhone(phone,addressBook);
    strcpy(addressBook->contacts[index].phone,phone);

    return ;
}

// Update the stored email for the selected contact.
void editemail(AddressBook* addressBook,short index){
    char email[30];
    inputemail(email,addressBook);
    strcpy(addressBook->contacts[index].email,email);

    return ;
}
