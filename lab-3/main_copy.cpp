#include<bits/stdc++.h>
using namespace std;
#define modm 1000000007

 

long long mod_pow(long long x, long long i, long long m) {
    long long result = 1;
    x %= m; // Take x modulo m initially to avoid overflow

    while (i > 0) {
        // If i is odd, multiply x with result
        if (i % 2 == 1) {
            result = (result * x) % m;
        }

        // Square x and reduce it modulo m
        x = (x * x) % m;

        // Divide i by 2
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

    void addContact( PhoneRecord* record) {
        string name = record -> getName();
        string organisation = record -> getOrganisation();
        vector<string> phoneNumbers = record -> getPhoneNumbers();
        string word = "";
        name = name + " ";
        for(int i  = 0;i<name.size();i++){
            if(name[i] == ' ')
             {
                int KEY = computeHash(word);
                HashTableRecord *node = new HashTableRecord(KEY,record);
                if(hashTable[KEY] == nullptr){
                    hashTable[KEY] = node;
                }
                else{
                    HashTableRecord *ite = hashTable[KEY];
                    while(ite -> getNext() != nullptr){
                        ite = ite -> getNext();
                    }
                    ite -> setNext(node);
                }
                word  = "";
             }
             else{
                word = word + name[i];
             }
        }
        
    }

    bool deleteContact( string* searchName) {
        string name  = *searchName + " ";
        vector<PhoneRecord*> contact = fetchContacts(&name);
        if(contact.empty())
         return false;
        else{
        PhoneRecord *ob = contact[0];
        string word = "";
        for(int i  = 0;i<name.size();i++){
            if(name[i] == ' ')
             {
                cout << "apple" << endl;
                int KEY = computeHash(word);
                cout << "ball" << endl;
                HashTableRecord *current = hashTable[KEY];
                cout << "cat" << endl;
                
                 cout << "happy" << KEY  << endl;
                //cout << current -> getKey() << " " << KEY << endl;
                
               if (current && (current -> getRecord() -> getName()) == ob -> getName()) {
                   cout << "o am here" << endl;
                   HashTableRecord *node = current;
                   current = current -> getNext();
                   hashTable[KEY] = current;
                   delete node;
                   cout << "o am here1" << endl;
                   word  = "";
                   continue;
                   
               }
               cout << "i am here2" << endl;
               HashTableRecord* prev = nullptr;
               
               while (current && (current->getRecord() -> getName()) != ob -> getName()) {
                cout << "i am here3" << endl;
                   prev = current;
                   
                   current = current->getNext();
               }
               if (current == nullptr) {
                   return false;
               }
               //cout << current -> getRecord() -> getName() << " ";
               prev->setNext(current -> getNext());
               //cout << prev -> getNext() -> getRecord() -> getName();

               delete current;
             //deletion complete
                word  = "";
                cout << "i am here1" << endl;

             }

             else{
                word = word + name[i];
             }
        }

      return true;

        }

        
    }

    vector<PhoneRecord*> fetchContacts( string* query) {
        // Implement fetching contacts based on the query
        // You may need to split the query into words and hash them separately
        // Then, retrieve and merge the records from the appropriate hash table slots
        // Sort and return the merged records
        vector<PhoneRecord*> result;
        map<PhoneRecord*,int> mp;
        string name = *query + ' ';
        string word = "";
        for(int i  = 0;i<name.size();i++){
            if(name[i] == ' ')
             {
                int KEY = computeHash(word);
                
                if(hashTable[KEY] == nullptr){
                    return result;
                }
                else{
                    HashTableRecord *node = hashTable[KEY];
                    while(node != nullptr){
                        mp[node -> getRecord()]++;
                        node = node -> getNext();
                    }
                }
                word  = "";
             }
             else{
                word = word + name[i];
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
            
    }

    // Add your own implementation for reading records from a file
    void readRecordsFromFile(){
          ifstream inputFile("Details.txt");
    
         if (!inputFile.is_open()) {
        cerr << "Failed to open file." << endl;
        return;
        }

        string line;
        //vector<string> tokens;
    
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
            PhoneRecord *ob = new PhoneRecord(row[0],row[row.size() - 1],numbers);
            addContact(ob);
        }

        // <---------- Addition of People -------------->

        
        // for(auto it : tokens){
        //     cout << it << endl;
        // }
        // string name = "Akash Reddy";
        //    int val = computeHash(name);
        //    HashTableRecord *obj = hashTable[val];
        //    string n = obj -> getRecord() -> getOrganisation();
        //    cout << n << endl;
        //    if(obj != nullptr)
        //     cout << "hurry" << endl
        //  string n = "Aarti";
        //  int v = computeHash(n);
        //  cout << v << endl;
        //  HashTableRecord *ob = hashTable[134];
        //  cout << ob -> getRecord() -> getName() << endl;
        //  vector<PhoneRecord*> cont = fetchContacts(&name);
        //  cout << cont.size() << endl;
        //  cout << cont[1] -> getName() << endl;;
        // bool ans = deleteContact(&name);
        // cout << ans << endl;
        // vector<PhoneRecord*> cont1 = fetchContacts(&name);
        // cout << cont1.size() << endl;

        // cout << "-----------------------" << endl;
        // for(int i  = 0;i<263;i++){
        //     HashTableRecord *node = hashTable[i];
        //     while(node != nullptr){
        //         cout << node -> getRecord() -> getName() << " ";
        //         node = node -> getNext();
        //     }
        //     cout << endl;
        // }
        //  vector<PhoneRecord*> cont1 = fetchContacts(&name);
        //  cout << cont1.size() << endl;
        // cout << ans;

    }

   

    // Destructor
    //~PhoneBook();
};

int main(){
   PhoneBook ob;
   ob.readRecordsFromFile();
  
//    HashTableRecord *obj = ob.hashTable[val];

   return 0;
}
