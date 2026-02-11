#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
using namespace std;

// contact structure
struct Contact {
  string name;
  string phone;
  string email;
};

// function declarations
void display_menu();
int get_user_choice(int min_choice, int max_choice);
void display_contact(const Contact & contact);
void display_all_contacts(Contact contacts[], int size);
Contact* search_contact_by_name(Contact contacts[] , int size, const string &name);
bool add_contact(Contact contacts[], int &current_size, int max_size);
bool update_contact(Contact &contact, const string &new_phone);
bool update_contact(Contact &contact, const string &new_phone, const string &new_email);
int count_contacts_with_domain(Contact contacts[], int size, const string &domain, int index = 0);
int find_contact_index(Contact contacts[], int size, const string &name);
bool delete_contact(Contact contacts[], int &size, const string &name);
void get_contact_statistics(Contact contacts[], int size, int &total_contacts, int &contacts_with_email, int &contacts_with_phone);

// main
int main() {
    const int MAX_CONTACTS = 100;
    Contact contacts[MAX_CONTACTS];
    int current_size = 0;
    int choice;

    do {
        display_menu();
        choice = get_user_choice(1,8);

        switch (choice) {
            // add contacts
            case 1: {
                if (add_contact(contacts, current_size, MAX_CONTACTS)) {
                    cout << "Contact saved succesfully!" << endl;
                } else {
                    cout << "Failed to add contact." << endl;
                }
                break;
            }
        
            // display all contacts
            case 2: {
                display_all_contacts(contacts, current_size);
                break;
            }

            // search for a contact
            case 3: {
                string search_name;
                cout << "Enter a name to search: ";
                getline(cin, search_name);
                Contact* searched_contact = search_contact_by_name(contacts, current_size, search_name);
                if (searched_contact != nullptr) {
                    cout << "Contact found:" << endl;
                    display_contact(*searched_contact);
                } else {
                    cout << "Contact not found." << endl;
                }

                break;
            }

            // update a contact
            case 4: {
                string update_name;
                cout << "Enter the name of a contact to update: ";
                getline(cin, update_name);
                Contact* searched_contact = search_contact_by_name(contacts, current_size, update_name);
                
                // check if contact exists
                if (searched_contact != nullptr) {
                    cout << "Update:" << endl;
                    cout << "1. Phone only" << endl;
                    cout << "2. Phone and email" << endl;
                    int update_choice = get_user_choice(1,2);

                    if (update_choice == 1) {
                        string new_phone;
                        cout << "Enter new phone: ";
                        getline(cin, new_phone);

                        if (update_contact(*searched_contact, new_phone)) {
                            cout << "Contact updated succesfully!" << endl;
                        } else {
                            cout << "Contact update failed." << endl;
                        }

                    } else if (update_choice == 2) {
                        string new_phone;
                        string new_email;
                        cout << "Enter new phone: ";
                        getline(cin, new_phone);

                        cout << "Enter new email: ";
                        getline(cin, new_email);

                        if (update_contact(*searched_contact, new_phone, new_email)) {
                            cout << "Contact updated succesfully!" << endl;
                        } else {
                            cout << "Contact update failed." << endl;
                        }
                    
                    }
                } else {
                    cout << "Contact not found." << endl;
                }
                
                break;
            }

            // delete a contact
            case 5: {
                string delete_name;
                cout << "Enter the name of a contact to delete: ";
                getline(cin, delete_name);

                if (delete_contact(contacts, current_size, delete_name)) {
                    cout << "Contact deleted successfully!" << endl;
                } else {
                    cout << "Contact not found." << endl;
                }
                break;
            }
            
            // count contacts by email domain
            case 6: {
                string domain_name;
                cout << "Enter email domain to search (e.g. @gmail.com): ";
                getline(cin, domain_name);
                int count = count_contacts_with_domain(contacts, current_size, domain_name);
                cout << "Number of contacts with domain " << domain_name << ": " << count << endl;
                break;
            }

            // display contact statistics
            case 7: {
                int total, with_email, with_phone;
                get_contact_statistics(contacts, current_size, total, with_email, with_phone);
                break; 
            }

            // exit
            case 8: {
                cout << "Exiting... Goodbye! " << endl;
                break;
            }
        }

        if (choice != 8) {
            cout << "\nPress Enter to continue..." << endl;
            string filler;
            getline(cin, filler); // to eat whats typed + newline
        }

    } while (choice != 8);
    
    return 0;
}

// functions
/**
 * @brief Displays a menu of tasks that user can perform
 */
void display_menu() {
    cout << "1. Add a contact" << endl;
    cout << "2. Display all contacts" << endl;
    cout << "3. Search for a contact by name" << endl;
    cout << "4. Update a contact (phone only, or phone and email)" << endl;
    cout << "5. Delete a contact" << endl;
    cout << "6. Count contacts by email domain" << endl;
    cout << "7. Display contact statistics" << endl;
    cout << "8. Exit" << endl;
}

/**
 * @brief Get choice from user that is within provided int range
 * @param min_choice Minimum allowed integer choice
 * @param max_choice Maximum allowed integer choice
 * @return An int corresponding to a task 
 */
int get_user_choice(int min_choice, int max_choice) {
    string choice;

    while (true) {
        cout << "Enter your choice: ";
        getline(cin, choice); 

        if (choice.size() == 1 && choice[0] >= ('0' + min_choice) &&
            choice[0] <= ('0' + max_choice)) {
            return choice[0] - '0';
        }
        cout << "Invalid input! Please enter an integer from "
            << min_choice << "-" << max_choice << "." << endl;
    } 
}

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
 * @return a pointer to a contact with the given name (else nullptr)
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
 * @return True if Contact added / updated sucessfully (else false)
 */
bool add_contact(Contact contacts[], int &current_size, int max_size) {
    if (current_size >= max_size) {
        return false;
    }
    
    Contact new_contact;

    cout << "Enter name: ";
    getline(cin, new_contact.name);

    // check if name is empty / whitespace
    bool valid_name = false;
    for (char c : new_contact.name) {
        if (!isspace(c)) {
            valid_name = true;
            break;
        }
    }

    if (!valid_name) {
        return false;
    }
    
    cout << "Enter phone: ";
    getline(cin, new_contact.phone);

    cout << "Enter email: ";
    getline(cin, new_contact.email);


    Contact* existing = search_contact_by_name(contacts, current_size, new_contact.name);

    // new contact added
    if (existing == nullptr) {
        *(contacts + current_size) = new_contact;
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
 * @return True if contact updated successfully (else false)
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
 * @return True if Contact updated sucessfully (else false)
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
 * @param index Current array traversal index
 * @return The total count of contacts matching the domain
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

/**
 * @brief Returns the index of a contact by name or -1 if not found
 * @param contacts Array of contacts
 * @param size Size of contacts array
 * @param name Name of contact to find
 * @return Index of a contact based on the name (else return -1)
 */
int find_contact_index(Contact contacts[], int size, const string &name) {
    for (int i = 0; i < size; i++) {
        if ((contacts + i) -> name == name) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Removes a contact from the contacts array
 * @param contacts Array of contacts
 * @param size Size of contacts array
 * @param name Name of contact to delete
 * @return True if deletion successful (else false)
 */
bool delete_contact(Contact contacts[], int &size, const string &name) {
    int contact_index = find_contact_index(contacts, size, name);
    // no contact to delete
    if (contact_index == -1) {
        return false;
    }
    
    // shift contact array (performs the deletion)
    for (int i = contact_index; i < size - 1; i++) {
        *(contacts + i) = *(contacts + i + 1);
    }

    size--;

    return true;
}

/**
 * @brief Analyzes the contact list and provides statistics
 * @param contacts Array of contacts
 * @param size Size of contacts array
 * @param total_contacts Output param - total # contacts
 * @param contacts_with_email Output param - total # contacts with email
 * @param contacts_with_phone Output param - total # contacts with phone
 */
void get_contact_statistics(Contact contacts[], int size, int &total_contacts, int &contacts_with_email, int &contacts_with_phone) {
    total_contacts = 0;
    contacts_with_email = 0;
    contacts_with_phone = 0;

    // traverse array and do counts
    for (int i = 0; i < size; i++) {
        total_contacts++;
        
        if ((contacts + i) -> email != "") {
            contacts_with_email++;
        }

        if ((contacts + i) -> phone != "") {
            contacts_with_phone++;
        }
   } 

   cout << "Contact Statistics:" << endl;
   cout << "Total contacts: " << total_contacts << endl;
   cout << "Contacts with email: " << contacts_with_email << endl;
   cout << "Contacts with phone: " << contacts_with_phone << endl;
}
