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

