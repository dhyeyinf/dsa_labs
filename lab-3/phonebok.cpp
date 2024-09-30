#include<bits/stdc++.h>
using namespace std;
#define modm 1000000007

bool isStringPresent(const std::string& mainString, const std::string& subString) {
    return mainString.find(subString) != std::string::npos;
}

long long mod_pow(long long x, long long i, long long m) {
    long long result = 1;
    x %= m;
    // Take x modulo m initially to avoid overflow
    while (i > 0) {
        if (i % 2 == 1) {
            result = (result * x) % m;
        }
        x = (x * x) % m;
        i /= 2;
    }

    return result;
}
class PhoneRecord {
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    PhoneRecord(const string& n, const string& org, const vector<string>& numbers)
        {
           name = n;
           organisation = org;
           phoneNumbers = numbers;
        }

    // Getters and setters for name, organisation, and phoneNumbers

    string getName() const {
        return name;
    }

    string getOrganisation() const {
        return organisation;
    }

    vector<string> getPhoneNumbers() const {
        return phoneNumbers;
    }
};

class HashTableRecord {
private:
    int key;
    PhoneRecord* element;
    HashTableRecord* next;

public:
    HashTableRecord(int k,  PhoneRecord* rec)
        : key(k), element(rec), next(nullptr) {}

    // Getters and setters for key, record, and next

    int getKey() const {
        return key;
    }

    PhoneRecord* getRecord() const {
        return element;
    }

    HashTableRecord* getNext() const {
        return next;
    }

    void setNext(HashTableRecord* nxt) {
        next = nxt;
    }
};

bool cmp(pair<PhoneRecord*, int>& a,
        pair<PhoneRecord*, int>& b)
{
    return a.second > b.second;
}

class PhoneBook {
private:
    static const int HASH_TABLE_SIZE = 263; // Fixed size of the hash table
    HashTableRecord* hashTable[HASH_TABLE_SIZE];

public:
    PhoneBook() {
        // Initialize the hash table slots to nullptr
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }

    // Function to compute the hash value for a given string
    long long computeHash( string& str) {
        long long hashVal = 0ll;
        for(int i  = 0;i<str.length();i++){
              hashVal = hashVal  + ((long long)((int)str[i]) * mod_pow(263,i,modm));
        }
        hashVal = hashVal % HASH_TABLE_SIZE;
        return hashVal;
    }

    // Implement methods for adding, deleting, and fetching contacts

    void addContact(PhoneRecord* record) {
        //cout << "i am here" << endl;
        string word = "";
        stringstream name;
        name << (record) -> getName();
        while(getline(name,word,' ')){
            //cout << "i am ready" << endl;
                int KEY = computeHash(word);
                HashTableRecord *node = new HashTableRecord(KEY,record);
                
                if(hashTable[KEY] == nullptr){
                    hashTable[KEY] = node;
                    //cout << "1" << endl;
                }
                else{
                    //cout << "else" << endl;
                    
                   // cout << "singer" << endl;
                    //cout << 
                    //cout << ite -> getRecord() -> getName() << endl;
                    HashTableRecord *ite = hashTable[KEY];
                    while(ite -> getNext() != nullptr){
                        ite = ite -> getNext();
                    }
                    //cout << "kangaru" << endl;
                    ite -> setNext(node);
                    //cout << "suraj" << endl;
                }
             }
             //cout << "gubbal" << endl;  
        }
    bool deleteContact(const string* searchName) {
        string str  = *searchName;
        vector<PhoneRecord*> contact = fetchContacts(&str);
        if(contact.empty())
         return false;
        else{
        PhoneRecord *ob = contact[0];
        string word = "";
        stringstream name;
        name << contact[0] -> getName();
        while(getline(name,word,' ')){ 
                int KEY = computeHash(word);
                HashTableRecord *current = hashTable[KEY];
               if (current && (current -> getRecord() -> getName()) == ob -> getName()) {
                   
                   HashTableRecord *node = current;
                   current = current -> getNext();
                   hashTable[KEY] = current;
                   delete node;
                   word  = "";
                   continue; 
               }
               HashTableRecord* prev = nullptr;
               while (current && (current -> getRecord() -> getName()) != ob -> getName()) {
               
                   prev = current;
                   
                   current = current->getNext();
               }
               if (current == nullptr) {
                   return false;
               }
               prev -> setNext(current -> getNext());
               delete current;
             }
             return true;
        }
      return true;   
    }

    vector<PhoneRecord*> fetchContacts(string* query) {
        vector<PhoneRecord*> result;
        unordered_map<PhoneRecord*,int> mp;
        string strname = *query;
        string word = "";
        stringstream name;
        name << strname;
        while(getline(name,word,' ')){
                int KEY = computeHash(word);
                
                if(hashTable[KEY] == nullptr){
                    return result;
                }
                else{
                    HashTableRecord *node = hashTable[KEY];
                    string str = *query;
                    string w = "";
                    stringstream strword;
                    strword << str;
                    while(getline(strword,w,' ')){
                    while(node != nullptr){
                        if((isStringPresent(node -> getRecord() -> getName(),w)))
                         mp[node -> getRecord()]++;
                        node = node -> getNext();
                    }
                 }
                }
             }
        vector<pair<PhoneRecord*,int>> vec;
        for(auto it : mp){
            pair<PhoneRecord*,int> pr = make_pair(it.first,it.second);
            vec.push_back(pr);
        }
        sort(vec.begin(),vec.end(),cmp);
        for(auto it : vec){
            result.push_back(it.first);
        }
        return result;
    }

    int countRecordsPointingTo(PhoneRecord* record){
        stringstream name;
        name << record -> getName();
        int c  = 0;
        string word = "";
        while(getline(name,word,' ')){
           int KEY = computeHash(word);
           HashTableRecord* ob = hashTable[KEY];
           while(ob != nullptr){
            if(ob -> getRecord() == record) 
             c++;
            ob = ob -> getNext(); 
           }
        }
        return c;
    }

    void readRecordsFromFile(const string& filename ){
        //cout << "ball" << endl;
        ifstream inputFile(filename);
        if (!inputFile.is_open()) {
        cerr << "Failed to open file." << endl;
        return;
        }
        string line;
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string token;
            vector<string> row;
            while (getline(ss, token, ',')) {
                row.push_back(token);
            }
            vector<string> numbers;
            for(int i = 1;i<row.size() - 1;i++){
               numbers.push_back(row[i]);
            }
            //cout << "come here" << endl;
            PhoneRecord *ob = new PhoneRecord(row[0],row[row.size() - 1],numbers);
            //cout << "cat" << endl;
            addContact(ob);
            //cout << "dog" << endl;
        }
    }  
    //destructor 
    ~PhoneBook(){
        for(auto i:hashTable){
            HashTableRecord* tmp = i;
            while(tmp != nullptr){
                HashTableRecord* t1 = tmp;
                tmp = tmp -> getNext();
                delete t1;
            }
        }

    }
   
};


