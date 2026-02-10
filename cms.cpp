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
bool update_contact(Contact &contact, const string &new_phone);
bool update_contact(Contact &contact, const string &new_phone, const string &new_email);
int count_contacts_with_domain(Contact contacts[], int size, const string &domain, int index = 0);

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
    
    Contact new_contact;
    string name;

    cout << "Enter name: ";
    getline(cin, new_contact.name);

    
    cout << "Enter phone: ";
    getline(cin, new_contact.phone);

    cout << "Enter email: ";
    getline(cin, new_contact.email);


    Contact* existing = search_contact_by_name(contacts, current_size, new_contact.name);

    // new contact added
    if (existing == nullptr) {
        contacts[current_size] = new_contact;
        current_size++;
    }
    
    // contact already exists
    else {
        existing -> phone = new_contact.phone;
        existing -> email = new_contact.email;
    }

    return true;

}

/**
 * @brief Update a Contact's phone number
 * @param contact Contact to update
 * @param new_phone New phone number for the contact
 */
bool update_contact(Contact &contact, const string &new_phone) {
    if (contact.name  == "") {
        return false;
    }

    contact.phone = new_phone;
    return true;
}

/**
 * @brief Update a Contact's phone number and email
 * @param contact Contact to update
 * @param new_phone New phone number for the contact
 */
bool update_contact(Contact &contact, const string &new_phone, const string &new_email) {
    if (contact.name  == "") {
        return false;
    }

    contact.phone = new_phone;
    contact.email = new_email;
    return true;
}

/**
 * @brief Counts # of contacts with an email address from a specific domain (e.g., @gmail.com)
 * @param contacts Array of contacts
 * @param size Size of contacts array
 * @param domain Domain being searched for
 * @param index Index of last found contact with a given domain
 */
int count_contacts_with_domain(Contact contacts[], int size, const string &domain, int index) {
    // base case
    if (index >= size) {
        return 0;
    }
    
    int count = 0;

    // check if current contact contains domain
    if (((contacts + index) -> email).find(domain) != string::npos) {
        count = 1;
    }

    // rec call
    return count + count_contacts_with_domain(contacts, size, domain, index + 1); 
}


