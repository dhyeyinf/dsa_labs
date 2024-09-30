#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <csignal>
#include <thread>
#include <mutex>
#include <atomic>
#include <functional>
#include<bits/stdc++.h>

// Import your PhoneBook and PhoneRecord classes here
#include "phonebook.cpp"

using namespace std;

  void test_add_and_delete_contact() {
        // Test adding a new contact and then deleting it
        cout << "|" << endl;
        PhoneBook* phone_book;
        cout << "kabadi" << endl;
        phone_book -> readRecordsFromFile("Details_new.txt");
        cout << "apple" << endl;
        vector<string> phoneNumbers1 = {"7889234231"};
        PhoneRecord record1("Adhir Ranjan", "Novotel", phoneNumbers1);
        phone_book->addContact(&record1);


        if (phone_book->deleteContact(new std::string("Adhir Ranjan"))) {
            vector<PhoneRecord*> contacts = phone_book->fetchContacts(new std::string("Adhir Ranjan"));    
        

        if (contacts.empty()) {

               cout << "success" << endl;
            } else {
                cout << "failure" << endl;
            }

    }


    else {
        cout << "Failure" << endl;
    }
    
    }


    int main(){
        test_add_and_delete_contact();
    }
