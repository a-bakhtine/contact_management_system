#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// contact structure
struct Contact {
  string name;
  string phone;
  string email;
};

// function declarations
void display_contact(const Contact & contact);
void display_all_contacts(Contact contacts[], int size);
Contact* search_contact_by_name(Contact contacts[] , int size, const string &name);
bool add_contact(Contact contacts[], int &current_size, int max_size);


// main
int main() {
    return 0;
}

// functions

/**
 * @brief Displays all information of a Contact
 * @param contact Contact
 */
void display_contact(const Contact &contact) {
    cout << "Name: "  << contact.name << endl;
    cout << "Phone: " << contact.phone << endl;
    cout << "Email: " << contact.email << endl;
}

/**
 * @brief Displays all contacts in the array
 * @param contacts Array of Contact objects to display
 * @param size Number of contacts in the array
 */
void display_all_contacts(Contact contacts[], int size) {
    if (size == 0) {
        cout << "No contacts to display." << endl;
        return;
    }
    
    for (int i = 0; i < size; i++) {
        display_contact(*(contacts + i));
        cout << endl;
    }
}

/**
 * @brief Searches for a contact by name
 * @param contacts Array of Contacts
 * @param size Number of Contacts currently stored
 * @param name Name of contact being searched for
 */
Contact* search_contact_by_name(Contact contacts[] , int size, const string &name) {
    for (int i = 0; i < size; i++) {
        if (name == (contacts + i) -> name ) { 
            return contacts + i;
        }
    }
    return nullptr;
}

/**
 * @brief Adds a new contact to the array
 * @param contacts Array of Contact objects to add to
 * @param current_size Int indicating size of array
 * @param max_size Int indicating max allowed size of array
 */
bool add_contact(Contact contacts[], int &current_size, int max_size) {
    if (current_size >= max_size) {
        return false;
    }
    
    Contact newContact;
    string name;

    cout << "Enter name: ";
    getline(cin, newContact.name);

    
    cout << "Enter phone: ";
    getline(cin, newContact.phone);

    cout << "Enter email: ";
    getline(cin, newContact.email);


    Contact* existing = search_contact_by_name(contacts, current_size, newContact.name);

    // new contact added
    if (existing == nullptr) {
        contacts[current_size] = newContact;
        current_size++;
    }
    
    // contact already exists
    else {
        existing -> phone = newContact.phone;
        existing -> email = newContact.email;
    }

    return true;

}


