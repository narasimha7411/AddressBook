#include<stdio.h>
#include "file.h"

// Write all contacts to contact.csv in a simple comma-separated format(CSV).

void saveContactToFile(AddressBook *addressBook){
    
    FILE *fcontact = fopen("contact.csv","w");

    fprintf(fcontact,"#%d\n",addressBook->contactCount);
    // This line stores the contact count as #<count>. Ex: #3

    for(int i=0;i<addressBook->contactCount;i++){
        fprintf(fcontact, "%-20s,%-10s,%-30s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    
    fclose(fcontact);
}

// Read contacts from contact.csv if the file exists.
// Expects first line to be #<count> followed by name,phone,email lines.
void loadContactFromFile(AddressBook *addressBook){

    FILE *fcontact = fopen("contact.csv","r");
    if(ferror(fcontact)){
        printf("Error 1st time\n");
    }

    if(fcontact == NULL){
        fprintf(stderr,"can't accesse file contact.csv");
        return ;
    }

    // read the contact count from the first line and increment the contactCount in the address book.
    fscanf(fcontact,"#%d\n",&addressBook->contactCount); 
    
    for(int i=0;i<addressBook->contactCount;i++){
        fscanf(fcontact,"%[^,],%[^,],%[^\n]\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }
     if(ferror(fcontact)){
        printf("Error 2st time\n");
    }
    fclose(fcontact);
}
