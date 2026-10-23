#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"


/* =========================================================
   VALIDATE NAME
   ========================================================= */

int isValidName(const char *name)
{
    int i;

    if (name[0] == '\0')
    {
        return 0;
    }

    for (i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha((unsigned char)name[i]) && name[i] != ' ')
        {
            return 0;
        }
    }

    return 1;
}

// int isNameUnique(AddressBook *addressBook, const char *name)
// {
//     int i;

//     for (i = 0; i < addressBook->contactCount; i++)
//     {
//         if (strcmp(addressBook->contacts[i].name, name) == 0)
//         {
//             return 0;
//         }
//     }

//     return 1;
// }


/* =========================================================
   VALIDATE PHONE
   ========================================================= */

int isValidPhone(const char *phone)
{
    int i;

    if (strlen(phone) != 10)
    {
        return 0;
    }

    for (i = 0; phone[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)phone[i]))
        {
            return 0;
        }

    }

    return 1;
}


/* =========================================================
   CHECK PHONE UNIQUE
   ========================================================= */

int isPhoneUnique(AddressBook *addressBook, const char *phone)
{
    int i;

    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            return 0;
        }
    }

    return 1;
}


/* =========================================================
   VALIDATE EMAIL
   ========================================================= */

int isValidEmail(const char *email)
{
    int i;
    int atPosition = -1;
    int dotComPosition = -1;


    /* Find @ */
    for (i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            /* More than one @ */
            if (atPosition != -1)
            {
                return 0;
            }

            atPosition = i;
        }
    }


    /* @ must exist and cannot be first */
    if (atPosition <= 0)
    {
        return 0;
    }


    /* Find .com after @ */
    for (i = atPosition + 1; email[i] != '\0'; i++)
    {
        if (email[i] == '.' &&
            email[i + 1] == 'c' &&
            email[i + 2] == 'o' &&
            email[i + 3] == 'm' &&
            email[i + 4] == '\0')
        {
            dotComPosition = i;
            break;
        }
    }


    /* .com must exist */
    if (dotComPosition == -1)
    {
        return 0;
    }


    /* Check characters between @ and .com
       Only alphabets allowed */
    for (i = atPosition + 1; i < dotComPosition; i++)
    {
        if (!isalpha((unsigned char)email[i]))
        {
            return 0;
        }
    }


    /* @ and .com cannot be next to each other */
    if (dotComPosition == atPosition + 1)
    {
        return 0;
    }


    return 1;
}


/* =========================================================
   CHECK EMAIL UNIQUE
   ========================================================= */

int isEmailUnique(AddressBook *addressBook, const char *email)
{
    int i;

    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            return 0;
        }
    }

    return 1;
}


/* =========================================================
   CREATE CONTACT
   ========================================================= */

void createContact(AddressBook *addressBook)
{
    Contact newContact;


    /* Check address book capacity */
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address Book is full. Cannot add more contacts.\n");
        return;
    }


    /* ---------------- NAME ---------------- */

    while (1)
    {
        printf("Enter name: ");
        scanf(" %[^\n]", newContact.name);

        if (isValidName(newContact.name))
        {
            break;
        }

        printf("Error: Invalid name. Name should contain only alphabets and spaces.\n");
    }


    /* ---------------- PHONE ---------------- */

    while (1)
    {
        printf("Enter phone number: ");
        scanf("%19s", newContact.phone);

        if (!isValidPhone(newContact.phone))
        {
            printf("Error: Invalid phone number. Phone number must contain exactly 10 digits.\n");
            continue;
        }

        if (!isPhoneUnique(addressBook, newContact.phone))
        {
            printf("Error: Phone number already exists.\n");
            continue;
        }

        break;
    }


    /* ---------------- EMAIL ---------------- */

    while (1)
    {
        printf("Enter email: ");
        scanf("%49s", newContact.email);

        if (!isValidEmail(newContact.email))
        {
            printf("Error: Invalid email.\n");
            continue;
        }

        if (!isEmailUnique(addressBook, newContact.email))
        {
            printf("Error: Email already exists.\n");
            continue;
        }

        break;
    }


    /* Store contact */
    addressBook->contacts[addressBook->contactCount] = newContact;
    addressBook->contactCount++;


    /* Permanently save */
    saveContactsToFile(addressBook);


    printf("Contact created successfully!\n");
}


/* =========================================================
   SEARCH CONTACT
   ========================================================= */

void searchContact(AddressBook *addressBook)
{
    int choice;

    char name[50];
    char phone[20];
    char email[50];


    printf("\nSearch Contact By:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);
    getchar();


    /* =====================================================
       SEARCH BY NAME
       ===================================================== */

    switch (choice)
    {
        case 1:
        {
            while (1)
            {
                int found = 0;

                printf("Enter name: ");
                scanf(" %[^\n]", name);


                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].name, name) == 0)
                    {
                        printf("\nContact Found:\n");

                        printf("Name : %s\n",
                               addressBook->contacts[i].name);

                        printf("Phone : %s\n",
                               addressBook->contacts[i].phone);

                        printf("Email : %s\n",
                               addressBook->contacts[i].email);

                        found = 1;
                    }
                }


                if (found)
                {
                    break;
                }


                printf("Contact not found. Please enter the name again.\n");
            }

            break;
        }


        /* =================================================
           SEARCH BY PHONE
           ================================================= */

        case 2:
        {
            while (1)
            {
                int found = 0;

                printf("Enter phone number: ");
                scanf("%19s", phone);


                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                    {
                        printf("\nContact Found:\n");

                        printf("Name : %s\n",
                               addressBook->contacts[i].name);

                        printf("Phone : %s\n",
                               addressBook->contacts[i].phone);

                        printf("Email : %s\n",
                               addressBook->contacts[i].email);

                        found = 1;

                        break;
                    }
                }


                if (found)
                {
                    break;
                }


                printf("Contact not found. Please enter the phone number again.\n");
            }

            break;
        }


        /* =================================================
           SEARCH BY EMAIL
           ================================================= */

        case 3:
        {
            while (1)
            {
                int found = 0;

                printf("Enter email: ");
                scanf("%49s", email);


                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].email, email) == 0)
                    {
                        printf("\nContact Found:\n");

                        printf("Name : %s\n",
                               addressBook->contacts[i].name);

                        printf("Phone : %s\n",
                               addressBook->contacts[i].phone);

                        printf("Email : %s\n",
                               addressBook->contacts[i].email);

                        found = 1;

                        break;
                    }
                }


                if (found)
                {
                    break;
                }


                printf("Contact not found. Please enter the email again.\n");
            }

            break;
        }


        default:
        {
            printf("Invalid choice.\n");
            break;
        }
    }
}


/* =========================================================
   EDIT CONTACT
   ========================================================= */

void editContact(AddressBook *addressBook)
{
    int searchChoice;
    int editChoice;

    int foundCount = 0;
    int contactIndex = -1;

    char name[50];
    char phone[20];
    char email[50];


    /* =====================================================
       SELECT SEARCH METHOD
       ===================================================== */

    printf("\nEdit Contact By:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");

    scanf("%d", &searchChoice);
    getchar();


    /* =====================================================
       SEARCH BY NAME
       ===================================================== */

    if (searchChoice == 1)
    {
        while (1)
        {
            foundCount = 0;

            printf("Enter name: ");
            scanf(" %[^\n]", name);


            /* Find all matching names */

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].name, name) == 0)
                {
                    foundCount++;

                    printf("\nContact %d:\n", foundCount);

                    printf("Name : %s\n",
                           addressBook->contacts[i].name);

                    printf("Phone : %s\n",
                           addressBook->contacts[i].phone);

                    printf("Email : %s\n",
                           addressBook->contacts[i].email);
                }
            }


            /* No contact */

            if (foundCount == 0)
            {
                printf("Contact not found. Please enter the name again.\n");
                continue;
            }


            /* Multiple contacts */

            if (foundCount > 1)
            {
                int selectedContact;
                int count = 0;


                printf("\nMultiple contacts found.\n");

                printf("Enter contact number to edit: ");
                scanf("%d", &selectedContact);


                if (selectedContact < 1 ||
                    selectedContact > foundCount)
                {
                    printf("Invalid contact number.\n");
                    continue;
                }


                /* Find actual array index */

                for (int i = 0;
                     i < addressBook->contactCount;
                     i++)
                {
                    if (strcmp(addressBook->contacts[i].name, name) == 0)
                    {
                        count++;

                        if (count == selectedContact)
                        {
                            contactIndex = i;
                            break;
                        }
                    }
                }
            }


            /* Only one contact */

            else
            {
                for (int i = 0;
                     i < addressBook->contactCount;
                     i++)
                {
                    if (strcmp(addressBook->contacts[i].name, name) == 0)
                    {
                        contactIndex = i;
                        break;
                    }
                }
            }


            break;
        }
    }


    /* =====================================================
       SEARCH BY PHONE
       ===================================================== */

    else if (searchChoice == 2)
    {
        while (1)
        {
            foundCount = 0;

            printf("Enter phone number: ");
            scanf("%19s", phone);


            for (int i = 0;
                 i < addressBook->contactCount;
                 i++)
            {
                if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    contactIndex = i;
                    foundCount = 1;

                    printf("\nContact Found:\n");

                    printf("Name : %s\n",
                           addressBook->contacts[i].name);

                    printf("Phone : %s\n",
                           addressBook->contacts[i].phone);

                    printf("Email : %s\n",
                           addressBook->contacts[i].email);

                    break;
                }
            }


            if (foundCount == 1)
            {
                break;
            }


            printf("Contact not found. Please enter the phone number again.\n");
        }
    }


    /* =====================================================
       SEARCH BY EMAIL
       ===================================================== */

    else if (searchChoice == 3)
    {
        while (1)
        {
            foundCount = 0;

            printf("Enter email: ");
            scanf("%49s", email);


            for (int i = 0;
                 i < addressBook->contactCount;
                 i++)
            {
                if (strcmp(addressBook->contacts[i].email, email) == 0)
                {
                    contactIndex = i;
                    foundCount = 1;

                    printf("\nContact Found:\n");

                    printf("Name : %s\n",
                           addressBook->contacts[i].name);

                    printf("Phone : %s\n",
                           addressBook->contacts[i].phone);

                    printf("Email : %s\n",
                           addressBook->contacts[i].email);

                    break;
                }
            }


            if (foundCount == 1)
            {
                break;
            }


            printf("Contact not found. Please enter the email again.\n");
        }
    }


    else
    {
        printf("Invalid choice.\n");
        return;
    }


    /* =====================================================
       SELECT WHAT TO EDIT
       ===================================================== */

    printf("\nWhat do you want to edit?\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");

    scanf("%d", &editChoice);
    getchar();


    /* =====================================================
       EDIT NAME
       ===================================================== */

    if (editChoice == 1)
    {
        while (1)
        {
            printf("Enter new name: ");
            scanf(" %[^\n]", name);


            if (isValidName(name))
            {
                strcpy(addressBook->contacts[contactIndex].name,
                       name);

                break;
            }


            printf("Error: Invalid name. Name should contain only alphabets and spaces.\n");
        }
    }


    /* =====================================================
       EDIT PHONE
       ===================================================== */

    else if (editChoice == 2)
    {
        while (1)
        {
            printf("Enter new phone number: ");
            scanf("%19s", phone);


            if (!isValidPhone(phone))
            {
                printf("Error: Invalid phone number. Phone number must contain exactly 10 digits.\n");
                continue;
            }


            /* Check duplicate phone */

            if (strcmp(addressBook->contacts[contactIndex].phone,
                       phone) != 0 &&
                !isPhoneUnique(addressBook, phone))
            {
                printf("Error: Phone number already exists.\n");
                continue;
            }


            strcpy(addressBook->contacts[contactIndex].phone,
                   phone);

            break;
        }
    }


    /* =====================================================
       EDIT EMAIL
       ===================================================== */

    else if (editChoice == 3)
    {
        while (1)
        {
            printf("Enter new email: ");
            scanf("%49s", email);


            if (!isValidEmail(email))
            {
                printf("Error: Invalid email.\n");
                continue;
            }


            /* Check duplicate email */

            if (strcmp(addressBook->contacts[contactIndex].email,
                       email) != 0 &&
                !isEmailUnique(addressBook, email))
            {
                printf("Error: Email already exists.\n");
                continue;
            }


            strcpy(addressBook->contacts[contactIndex].email,
                   email);

            break;
        }
    }


    else
    {
        printf("Invalid choice.\n");
        return;
    }


    /* Permanently save edited contact */

    saveContactsToFile(addressBook);


    printf("Contact updated successfully!\n");
}


/* =========================================================
   DELETE CONTACT
   ========================================================= */

void deleteContact(AddressBook *addressBook)
{
    int searchChoice;
    int foundCount = 0;
    int contactIndex = -1;

    char name[50];
    char phone[20];
    char email[50];


    printf("\nDelete Contact By:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");

    scanf("%d", &searchChoice);
    getchar();


    /* =====================================================
        SEARCH CONTACT BY NAME
       ===================================================== */

    if (searchChoice == 1)
    {
        while (1)
        {
            foundCount = 0;

            printf("Enter name: ");
            scanf(" %[^\n]", name);


            /* Display all matching contacts */

            for (int i = 0;
                 i < addressBook->contactCount;
                 i++)
            {
                if (strcmp(addressBook->contacts[i].name, name) == 0)
                {
                    foundCount++;

                    printf("\nContact %d:\n",
                           foundCount);

                    printf("Name : %s\n",
                           addressBook->contacts[i].name);

                    printf("Phone : %s\n",
                           addressBook->contacts[i].phone);

                    printf("Email : %s\n",
                           addressBook->contacts[i].email);
                }
            }


            if (foundCount == 0)
            {
                printf("Contact not found. Please enter the name again.\n");
                continue;
            }


            /* Multiple contacts */

            if (foundCount > 1)
            {
                int selectedContact;
                int count = 0;


                printf("\nMultiple contacts found.\n");
                printf("Enter contact number to delete: ");

                scanf("%d", &selectedContact);


                if (selectedContact < 1 ||
                    selectedContact > foundCount)
                {
                    printf("Invalid contact number.\n");
                    continue;
                }


                for (int i = 0;
                     i < addressBook->contactCount;
                     i++)
                {
                    if (strcmp(addressBook->contacts[i].name,
                               name) == 0)
                    {
                        count++;

                        if (count == selectedContact)
                        {
                            contactIndex = i;
                            break;
                        }
                    }
                }
            }


            /* Only one contact */

            else
            {
                for (int i = 0;
                     i < addressBook->contactCount;
                     i++)
                {
                    if (strcmp(addressBook->contacts[i].name,
                               name) == 0)
                    {
                        contactIndex = i;
                        break;
                    }
                }
            }


            break;
        }
    }


    /* =====================================================
        SEARCH CONTACT BY PHONE
       ===================================================== */

    else if (searchChoice == 2)
    {
        while (1)
        {
            foundCount = 0;

            printf("Enter phone number: ");
            scanf("%19s", phone);


            for (int i = 0;
                 i < addressBook->contactCount;
                 i++)
            {
                if (strcmp(addressBook->contacts[i].phone,
                           phone) == 0)
                {
                    contactIndex = i;
                    foundCount = 1;

                    printf("\nContact Found:\n");

                    printf("Name : %s\n",
                           addressBook->contacts[i].name);

                    printf("Phone : %s\n",
                           addressBook->contacts[i].phone);

                    printf("Email : %s\n",
                           addressBook->contacts[i].email);

                    break;
                }
            }


            if (foundCount == 1)
            {
                break;
            }


            printf("Contact not found. Please enter the phone number again.\n");
        }
    }


    /* =====================================================
      SEARCH CONTACT BY EMAIL
       ===================================================== */

    else if (searchChoice == 3)
    {
        while (1)
        {
            foundCount = 0;

            printf("Enter email: ");
            scanf("%49s", email);


            for (int i = 0;
                 i < addressBook->contactCount;
                 i++)
            {
                if (strcmp(addressBook->contacts[i].email,
                           email) == 0)
                {
                    contactIndex = i;
                    foundCount = 1;

                    printf("\nContact Found:\n");

                    printf("Name : %s\n",
                           addressBook->contacts[i].name);

                    printf("Phone : %s\n",
                           addressBook->contacts[i].phone);

                    printf("Email : %s\n",
                           addressBook->contacts[i].email);

                    break;
                }
            }


            if (foundCount == 1)
            {
                break;
            }


            printf("Contact not found. Please enter the email again.\n");
        }
    }


    else
    {
        printf("Invalid choice.\n");
        return;
    }


    /* =====================================================
       DELETE CONTACT FROM ARRAY
       ===================================================== */

    for (int i = contactIndex;
         i < addressBook->contactCount - 1;
         i++)
    {
        addressBook->contacts[i] =
            addressBook->contacts[i + 1];
    }


    addressBook->contactCount--;


    /* Permanently save after delete */

    saveContactsToFile(addressBook);


    printf("Contact deleted successfully!\n");
}


/* =========================================================
   LIST ALL CONTACTS
   ========================================================= */

void listContacts(AddressBook *addressBook)
{
    printf("---------------------------------------------\n");
    printf("Name\t\tPhone\t\tEmail\n");
    printf("---------------------------------------------\n");


    if (addressBook->contactCount == 0)
    {
        printf("Address Book is empty.\n");
        return;
    }


    for (int i = 0;
         i < addressBook->contactCount;
         i++)
    {
        printf("%s\t\t%s\t\t%s\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}


/* =========================================================
   SAVE CONTACTS TO FILE
   ========================================================= */

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *file;


    file = fopen("contacts.dat", "wb");


    if (file == NULL)
    {
        printf("Error: Unable to save contacts.\n");
        return;
    }


    fwrite(addressBook,
           sizeof(AddressBook),
           1,
           file);


    fclose(file);
}


/* =========================================================
   LOAD CONTACTS FROM FILE
   ========================================================= */

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *file;


    file = fopen("contacts.dat", "rb");


    /* File does not exist */
    if (file == NULL)
    {
        addressBook->contactCount = 0;
        return;
    }


    fread(addressBook,
          sizeof(AddressBook),
          1,
          file);


    fclose(file);
}