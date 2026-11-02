#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fp;
    fp=fopen("Contacts.csv","w+");
    // if (fp == NULL) {
    //     printf("File doen't exists\n");
    //     return;
    // }

    for(int i=0;i<addressBook->contactCount;i++){
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(fp);
  
}

void loadContactsFromFile(AddressBook *addressBook) {
    int i=0;
    FILE *fp1;
    fp1=fopen("Contacts.csv","r");
    if(fp1==NULL){
        printf("File Doesn't Exists\n");
        return;
    }
    while((fscanf(fp1,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email))==3){
        i++;

    }
    addressBook->contactCount=i;
}
