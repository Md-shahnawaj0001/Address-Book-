// #include "contact.h"

// // Dummy contact data
// static Contact dummyContacts[] = {
//     {"Prafulla", "1234567890", "john@example.com"},
//     {"Alice Smith", "0987654321", "alice@example.com"},
//     {"Bob Johnson", "1112223333", "bob@company.com"},
//     {"Carol White", "4445556666", "carol@company.com"},
//     {"David Brown", "7778889999", "david@example.com"},
//     {"Eve Davis", "6665554444", "eve@example.com"},
//     {"Frank Miller", "3334445555", "frank@example.com"},
//     {"Grace Wilson", "2223334444", "grace@example.com"},
//     {"Hannah Clark", "5556667777", "hannah@example.com"},
//     {"Ian Lewis", "8889990000", "ian@example.com"},
//     {"shahnawaj", "9304890415", "shahnawazinfo8@gmail.com"},
//     {"shahnawaj", "9576738688", "shahnawazkhan428@gmail.com"},
//     {"shahnawaj", "7004653169", "mbimdshahnawaz0786@gmail.com"}
// };

// void initialize(AddressBook* addressBook)
// {
//     addressBook->contactCount = 0;

//     int numDummyContacts = sizeof(dummyContacts) / sizeof(dummyContacts[0]);

//     for (int i = 0; i < numDummyContacts && addressBook->contactCount < 100; ++i)
//     {
//         addressBook->contacts[addressBook->contactCount++] = dummyContacts[i];
//     }
// }






#include "contact.h"

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}