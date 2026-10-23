# Address Book Management System

A console-based **Address Book Management System built using C**.

This project was developed to practice fundamental C programming concepts by implementing a practical contact management application.

## Features

- Create new contacts
- Search contacts by:
  - Name
  - Phone number
  - Email
- Edit existing contacts
- Delete contacts
- List all contacts
- Handle duplicate names
- Validate contact information
- Check phone number uniqueness
- Check email uniqueness
- Store contact information using file handling

## Concepts Used

- Structures
- Arrays of structures
- Functions
- Pointers
- String handling
- Loops
- Conditional statements
- Input validation
- File handling
- Searching and updating records

## Contact Structure

Each contact contains:

```c
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;
```

The address book stores multiple `Contact` structures using an array.

## Menu

```text
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
```

## Search

Contacts can be searched using:

- Name
- Phone number
- Email

If multiple contacts have the same name, all matching contacts are displayed so that the user can select the required contact.

## Validation

The project includes validation for:

- Names containing alphabets and spaces
- Phone numbers containing exactly 10 digits
- Email format
- Duplicate phone numbers
- Duplicate email addresses

## File Handling

The project uses file handling to save and load address book data so that contact information can be retained between program executions.

## How to Compile

```bash
gcc main.c contact.c populate.c -o addressbook
```

## How to Run

```bash
./addressbook
```

## Project Structure

```text
Address_Book_project/
│
├── main.c
├── contact.c
├── contact.h
├── populate.c
├── populate.h
└── contacts.dat
```

## Learning Outcome

This project helped me gain practical experience in combining multiple C programming concepts into a single application.

It also improved my understanding of how data can be created, searched, updated, deleted, validated, and stored in a program.

## Future Improvements

Possible future improvements include:

- Better email validation
- Improved user input handling
- Sorting contacts
- More advanced search options
- Improved file/database management
- A graphical user interface

---

**Language:** C  
**Project Type:** Console Application  
**Focus:** C Programming Fundamentals & Problem Solving
