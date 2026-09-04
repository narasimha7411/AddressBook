# AddressBook

A simple console-based contact management system written in **C**. It allows you to create, search, edit, delete, and list contacts, with data persisted to a CSV file.

## Features

* **Create Contact** — Add a new contact with name, phone, and email
* **Search Contact** — Find contacts by name, phone, or email using substring matching
* **Edit Contact** — Update an existing contact's details
* **Delete Contact** — Remove a contact from the address book
* **List All Contacts** — View all saved contacts
* **Save and Exit** — Save all contacts to `contact.csv` before quitting
* **Quick Sort** — Contacts are efficiently sorted using the Quick Sort algorithm

## Project Structure

```text
AddressBook/
├── main.c              # Program entry point and menu loop
├── contact.c/.h        # Contact structure and address book operations
├── file.c/.h           # File I/O for loading and saving contacts
├── function.c/.h       # Supporting utility functions and sorting
└── contact.csv         # Persisted contact data
```

## Requirements

* GCC or another C compiler
* Linux, macOS, or Windows with a C development environment

## Build & Run

Clone the repository and navigate to the project directory:

```bash
git clone <your-repository-url>
cd AddressBook
```

Compile the program:

```bash
gcc main.c contact.c file.c function.c -o addressbook
```

Run the program:

```bash
./addressbook
```

## Usage

When the program starts, you will see the following menu:

```text
***************************************
|           ADDRESS BOOK MENU         |
---------------------------------------
|   1   |   CREATE CONTACT            |
|   2   |   SEARCH CONTACT            |
|   3   |   EDIT CONTACT              |
|   4   |   DELETE CONTACT            |
|   5   |   LIST ALL CONTACTS         |
|   6   |   SAVE AND EXIT             |
|   7   |   EXIT                      |
---------------------------------------
Choose your Option:
```

Enter the number corresponding to the action you want to perform.

## Data Storage

Contact information is stored in `contact.csv`. The program loads existing contacts from the CSV file and saves changes when **Save and Exit** is selected.

## Author

**Narasimha S**
