#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    printf("--------------------------------------------------------:::Contacts:::--------------------------------------------------------------------\n");
    printf("============================================================================================================================================\n");
    printf("Name                                     Phone Number               Email id                                     \n");
    printf("============================================================================================================================================\n");
    switch(sortCriteria){
        case 1:
            for(char ch='A';ch<='Z';ch++){
                for(int i=0;i<addressBook->contactCount;i++){
                    if(addressBook->contacts[i].name[0]==ch || addressBook->contacts[i].name[0]==ch+32){
                        printf("%-40s %-20s %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    }
                }
            }
            break;
        case 2:
            for(char ch='0';ch<='9';ch++){
                for(int i=0;i<addressBook->contactCount;i++){
                    if(addressBook->contacts[i].phone[0]==ch){
                        printf("%-40s %-20s %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    }
                }
            }
            break;
        case 3:
            for(char ch='A';ch<='Z';ch++){
                for(int i=0;i<addressBook->contactCount;i++){
                    if(addressBook->contacts[i].email[0]==ch || addressBook->contacts[i].email[0]==ch+32){
                        printf("%-40s %-20s %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    }
                }
            }
            break;
    }
    printf("----------------------------------------------:::Contact Saved Succussfully:::--------------------------------------------------------------\n");
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    int count = 0;
    do{
        printf("Enter the name: ");
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);
        if(validateName(addressBook->contacts[addressBook->contactCount].name)){
            break;
        }else{
            count++;
            printf("%d Limits Available\n",3-count);
        }
    }while(count < 3);
    if(count == 3){
        printf("Maximum attempts exceeded.\n");
        return;
    }
    count = 0;
    do{
        printf("Enter the Phone Number: ");
        scanf("%s", addressBook->contacts[addressBook->contactCount].phone);
        if(validatePhone(addressBook->contacts[addressBook->contactCount].phone,addressBook,-1)){
            break;
        }else{
            count++;
            printf("%d Limits Available\n",3-count);
        }
    }while(count < 3);
    if(count == 3){
        printf("Maximum attempts exceeded.\n");
        return;
    }
    count = 0;
    do{
        printf("Enter the Email Id: ");
        scanf("%s", addressBook->contacts[addressBook->contactCount].email);
        if(validateEmail(addressBook->contacts[addressBook->contactCount].email,addressBook,-1)){
            break;
        }else{
            count++;
            printf("\n%d Limits Available\n",3-count);
        }
    }while(count < 3);
    if(count == 3){
        printf("Maximum attempts exceeded.\n");
        return;
    }
    addressBook->contactCount++;
    printf("Contact created successfully.\n");
}
    
/* To Validate the Name*/
int validateName(char name[]){
    int flag=0;
    do{
        
        int j=0;
        while(name[j]!='\0'){
            j++;
        }
        int len=j;
        // if(len<3){
        //     printf("Enter the valid name\n");
        //     return 0;
        // }
        int i=0,space=0,alpha=0;
        while(name[i]!='\0'){
            if(isalpha(name[i])){
                alpha++;
                i++;
            }else if(isspace(name[i])){
                i++;
                space++;
            }else if(isdigit(name[i])){
                printf("Digits are not allowed in the name\n");
                return 0;
            }else{
                printf("Special characters are not allowed in the name\n");
                return 0;
            }
        }
        if(i==j && space<3 && alpha>=3){
            flag=1;
        }else{
            printf("Invalid name\n");
            return 0;
        }
    }while(flag==0);
    return 1;
}

/* To Validate the Phone Number*/
int validatePhone(char phone[],AddressBook *addressBook,int index){
    int flag=0;
    do{
        int i=0,digit=0;
        while(phone[i]!='\0'){
            if(isdigit(phone[i])){
                if(i==0){
                    if(phone[i]>='6' && phone[i]<='9'){
                        i++;
                        continue;
                    }
                    else{
                        printf("Enter first digit b/w 6 to 9 in number\n");
                        return 0;
                    }
                }
                i++;
            }else{
                printf("Enter the digits only in the number\n");
                return 0;
            }
        }
        if(i==10){
            flag++;
        }
        else{
            printf("Enter the valid number with 10 digits\n");
            return 0;
        }
        for(int i=0;i<addressBook->contactCount;i++){
            if(i==index){
                continue;
            }
            if(strcmp(addressBook->contacts[i].phone,phone)==0){
                printf("Phone Number is already present in the Contact List\n");
                return 0;
            }
        }
    }while(flag==0);
    return 1;
}


/* To Validate the Emial*/

int validateEmail(char email[],AddressBook *addressBook,int index){
    int i=0,dot_count=0,at_count=0,repeat=0,alpha=0,result=0,flag=1;
    while(email[i]!='\0'){
        if(isalnum(email[i]) || email[i]=='@' || email[i]=='.'){
            if(email[i]=='@'){
                at_count++;
            }
            else if(email[i]=='.'){
                dot_count++;
            }
        }else{
            printf("The email not contains any special characters except '@' and '.'\n");
            flag=0;
            break;
        }
        i++;
    }
    if(flag){
        if(at_count!=1 || dot_count<=0){
            printf("The email should contain only one '@' and atleast one '.'\n");
            return 0;
        }
        char *at_add=strchr(email,'@');
        char *dot_add=strrchr(email,'.');
        if(at_add==NULL || dot_add==NULL || at_add>dot_add){
            printf("Invalid email format there is no .com present at the end\n");
            return 0;
        }
        int len=strlen(email);
        if(strcmp(email+len-4,".com")==0){
            result++;
        }else{
            printf("'.com' is not present at the end\n");
            return 0;
        }
        for(char *i=at_add+1;i<dot_add;i++){
            if(isalpha(*i)){
                alpha++;
            }
        }
        if(alpha<=0){
            printf("Enter aleast one character b/w @ and .com\n");
            return 0;
        }
        else{
            result++;
        }
    }
    for (int i=0;i<addressBook->contactCount;i++){
        if(i==index){
            continue;
        }
        if (strcmp(addressBook->contacts[i].email,email)==0){
            printf("Email is already present in the Contact List\n");
            return 0;
        }
    }
    if(result==2){
        return 1;
    }
    return 0;
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int op,flag=1;
    while(flag){
        printf("1.Search by Name\n2.Search by Phone Number\n3.Search by Email Id\n4.Exit\n");
        if (scanf("%d", &op) != 1){
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n');
        return;
    }
        switch(op){
            case 1:
                Search_by_name(addressBook);
                break;
            case 2:
                Search_by_Phonenumber(addressBook);
                break;
            case 3:
                Search_by_Emailid(addressBook);
                break;
            case 4:
                flag=0;
                break;
        }
        printf("DO you want to continue YES-->1 (or) NO--> 0\n");
        scanf("%d",&flag);
    }
}

int Search_by_name(AddressBook *addressBook){
    char s_name[20];
    int found=0;
    int index=-1;
    printf("Enter the Name: ");
    scanf(" %[^\n]",s_name);
    for(int i=0;i<addressBook->contactCount;i++){
        char* name=strcasestr(addressBook->contacts[i].name,s_name);
        if(name!=NULL){
            found=1;
            index=i;
            printf("Index: %-5d Name: %-20s Phone Number: %-15s Email Id: %s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
    }
    if(found==0){
        printf("Name is not present in the contacts\n");
    }
    return index;
}
int Search_by_Phonenumber(AddressBook* addressBook){
    char p_no[20];
    int found=0,index=-1;
    printf("Enter the Phone Number: ");
    scanf(" %[^\n]",p_no);
    for(int i=0;i<addressBook->contactCount;i++){
        char* number=strstr(addressBook->contacts[i].phone,p_no);
        if(number!=NULL){
            found=1;
            index=i;
            printf("Index: %-5d Name: %-20s Phone Number: %-15s Email Id: %s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
    }
    if(found==0){
        printf("Phone Number is not present in the contacts\n");
    }
    return index;
}

int Search_by_Emailid(AddressBook* addressBook){
    char e_id[20];
    int found=0;
    int index=-1;
    printf("Enter the Email Id: ");
    scanf(" %[^\n]",e_id);
    for(int i=0;i<addressBook->contactCount;i++){
        char* email=strstr(addressBook->contacts[i].email,e_id);
        if(email!=NULL){
            found=1;
            index=i;
            printf("Index: %-5d Name: %-20s Phone Number: %-15s Email Id: %s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
    }
    if(found==0){
        printf("Email Id is not present in the contacts\n");
    }
    return index;
}


void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int op,index=-1,count=0;
    printf("1.Edit the Name\n2.Edit the Phone Number\n3.Edit the Email Id\n");
    if (scanf("%d", &op) != 1){
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n');
        return;
    }
    switch(op){
        case 1:
            printf("Check name is present in the contact list to modifiy: \n");
            index=Search_by_name(addressBook);
            if(index>=0){
                do{
                    printf("Choice the index to modify: ");
                    scanf("%d",&index);
                    printf("Enter the name to modify: ");
                    scanf(" %[^\n]", addressBook->contacts[index].name);
                    if(validateName(addressBook->contacts[index].name)){
                        printf("Name is Edited Succussfully\n");
                        break;
                    }else{
                        count++;
                    }
                }while(count < 3);
                if(count == 3){
                    printf("Maximum attempts exceeded.\n");
                    return;
                }
            }else{
                printf("The contact is not founnd\n");
            }
            break;
        case 2:
            printf("Check phone number is present in the contact list to modifiy: \n");
            index=Search_by_Phonenumber(addressBook);
            if(index>=0){
                count = 0;
                do{
                    printf("Choice the index to modify: ");
                    scanf("%d",&index);
                    printf("Enter the Phone Number to modify: ");
                    scanf("%s", addressBook->contacts[index].phone);
                    if(validatePhone(addressBook->contacts[index].phone,addressBook,index)){
                        printf("Phone Number is Edited Succussfully\n");
                        break;
                    }else{
                        count++;
                    }
                }while(count < 3);
                if(count == 3){
                    printf("Maximum attempts exceeded.\n");
                    return;
                }
            }else{
                printf("Entered Phone number is not present in the contact list\n");
            }
            break;
        case 3:
            printf("Check emial id is present in the contact list to modifiy: \n");
            index=Search_by_Emailid(addressBook);
            if(index>=0){
                count = 0;
                do{
                    printf("Choice the index to modify: ");
                    scanf("%d",&index);
                    printf("Enter the Email Id to modify: ");
                    scanf("%s", addressBook->contacts[index].email);
                    if(validateEmail(addressBook->contacts[index].email,addressBook,index)){
                        printf("Email is Edited Succussfully\n");
                        break;
                    }else{
                        count++;
                    }
                }while(count < 3);
                if(count == 3){
                    printf("Maximum attempts exceeded.\n");
                    return;
                }
            }else{
                printf("The mail is not present in the contact List\n");
            }
            break;
        default:
            printf("Invalid Option\n");
    }
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int op,index;
    printf("1.Delete by Name\n2.Delete by Phone Number\n3.Delete by Email Id\n");
    if (scanf("%d", &op) != 1){
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n');
        return;
    }
    if(op>=1 && op<=3){
        switch(op){
            case 1:
                index=Search_by_name(addressBook);
                if(index>=0){
                    printf("Select the index value to delete the contact: ");
                    scanf("%d",&index);
                    for(int i=index;i<addressBook->contactCount;i++){
                        strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
                        strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
                        strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
                    }
                    addressBook->contactCount--;
                }
                printf("Contact Deleted Successfully\n");
                break;
            case 2:
                index=Search_by_Phonenumber(addressBook);
                if(index>=0){
                    printf("Select the index value to delete the contact: ");
                    scanf("%d",&index);
                    for(int i=index;i<addressBook->contactCount;i++){
                        strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
                        strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
                        strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
                    }
                    addressBook->contactCount--;
                }
                printf("Contact Deleted Successfully\n");
                break;
            case 3:
                index=Search_by_Emailid(addressBook);
                if(index>=0){
                    printf("Select the index value to delete the contact: ");
                    scanf("%d",&index);
                    for(int i=index;i<addressBook->contactCount;i++){
                        strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
                        strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
                        strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
                    }
                    addressBook->contactCount--;
                }
                printf("Contact Deleted Successfully\n");
                break;
            default:
                printf("Invalid Option\n");
                return;
        }
    }
}
