#include <stdio.h>
#include "phonebook.h"



int main() {
    PhoneBook *pb = createPhoneBook();
    PhoneEntry *e;
    
    addPhoneNumber("Duc", 12345, pb);
    //rintf("%ld", ((pb->entries)+1)->number);
    addPhoneNumber("Minh", 54321, pb);
    addPhoneNumber("Huong", 88888, pb); 

     if ((e = getPhoneNumber("Huong", pb)) != NULL)
        printf("Phone number of Huong is:%ld\n", e->number);
    else
        printf("Can\'t find phone number of Huong\n"); 
    
  return 0;  
}