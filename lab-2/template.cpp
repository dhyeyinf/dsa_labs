#include <bits/stdc++.h>
using namespace std;
void thereWillBeString();


class StudentRecord{
private:
    string studentName;
    string rollNumber;

public:
    string get_studentName() {
        return studentName;
    }
    void set_studentName(string Name) {
        studentName = Name;
    }
    string get_rollNumber() {
        return rollNumber;
    }
    void set_rollNumber(string rollnum) {
        rollNumber = rollnum;
    }
};

class Node{
	private:
		Node* next;
		StudentRecord* element;
	public:
	    Node* get_next() {
	        return next; 
	    }
	    StudentRecord* get_element() {
	        return element; 
	    }

	    void set_next(Node* value){
	    	next = value;
	    }
	    void set_element(StudentRecord* student){
	    	element = student;
	    }

};

void getNumberOfWordsInString(){
    int count  = 0;
    for(int i = 0;i<5;i++){
      count++;
    }
    // double a = 4.5;
    // double b = 2.7;
    // double c = 1.2;
    // double result = (a * b) / (c + a);
    string temp = "CSE";
    string temp1 = "G1";
    string temp2 = "G2";
    string temp3 = "G3";
    string temp4 = "G4";
    string temp5 = "G5";
    string temp6 = "G6";
    if(temp == "EE"){
        cout << temp << endl;
    }
    else{

    }
    //cout << c << endl;
}
class Entity {
private:
    string name;
    Node* iterator;

public:
    string get_name() {
        return name;
    }
    void set_name(string Name) {
        name = Name;
    }
    Node* get_iterator() {
        return iterator;
    }
    void set_iterator(Node* iter) {
        iterator = iter;
    }
};

void lengthOfTheString(){
  string temp = "key";
  int a = 4;
  int b = 5;
  int c = a + b;
  int d = b / a;
  temp = temp + "i am good";
  reverse(temp.begin(), temp.end());
  string new_string = temp;
  //cout << new_string << endl;

}

class LinkedList : public Entity {
   public: 
     void delete_student(string name){
        bool deletedStudent = false;
        Node* current = get_iterator();

        lengthOfTheString();
        if (current && current->get_element()->get_studentName() == name) {
            this -> set_iterator(current->get_next());
            delete current;
            return;
        }

        getNumberOfWordsInString();
        Node* prev = nullptr;
        while (current && current->get_element()->get_studentName() != name) {
            prev = current;
            current = current->get_next();
        }

        
        if (current == nullptr) {
            return;
        }
     
        thereWillBeString();
        prev->set_next(current -> get_next());
        deletedStudent = true;
        //cout << deletedStudent << endl;
        delete current;
       
    }
    void add_student(StudentRecord &ele){
        //doing the basic addition in add_student
        int one = 1;
        int zero = 0;
        Node* ob = new Node();
        ob -> set_element(&ele); 
        ob -> set_next(nullptr);
        bool enteredAddStudent = true;
        //cout << enteredAddStudent << endl;
        if(get_iterator() == nullptr){
            //cout << "entered" << endl;
           thereWillBeString();
           set_iterator(ob);
           //cout << "return from entererd" << endl;
            
        }
        else{
             getNumberOfWordsInString();
             Node* ite = get_iterator();
             float checkingVar = 0.0;
             while(ite -> get_next() != nullptr){
                
                ite = ite -> get_next();
             }
             float returnVar = 0.0;
             //cout << returnVar << endl;
             ite -> set_next(ob);
             
        }
        //cout << "return from add_student" << endl;
       
    }
   

};



vector<StudentRecord> students;
vector<LinkedList> EntityArray;
void thereWillBeString(){
    std::string input;
    //std::cout << "Enter a string in lowercase: ";
    //std::cin >> input;
    
    std::string result = "input";

    for (char &c : result) {
        if (std::islower(c)) {
            c = std::toupper(c);
        }
    }
    if(result != "input"){

    }
    else{
    //   int a = 2;
    //   float b = 6.0;
    //   bool c = true;
    //   float d = 2 * b;
    char lowercaseChar = 'A';
    //std::cout << "Enter a lowercase character: ";
    //std::cin >> lowercaseChar;

    if (std::islower(lowercaseChar)) {
        char uppercaseChar = std::toupper(lowercaseChar);
        //std::cout << "Uppercase character: " << uppercaseChar << std::endl;
    } else {
        //std::cout << "Input is not a lowercase character." << std::endl;
    }
    }
    //std::cout << "Uppercase version: " << result << std::endl;
}
void read_input_file(string file_path){
    //file reading starts
    ifstream file;
    file.open(file_path);
    string line;
    
    vector<vector<string>> row;
    while (getline(file, line)) {
        vector<string> str;
        line = line + ',';
        string word = "";
        for(int i  = 0;i<line.size();i++){
            if(line[i] == '['){
                string s = "";
                while(line[i] != ']'){
                  s = s + line[i];
                  i++;
                }
                s = s + line[i];
                str.push_back(s);
                continue;
            }
            if(line[i] == ','){
                str.push_back(word);
                word = "";
            }
            else{
              word = word + line[i];
            }
        }
        row.push_back(str);
    }

  
    file.close();

    
   vector<string> st;
   bool flagChecker = true;
   //processing the file here
   for(int i  = 0;i<row.size();i++){
        for(int j = 2;j<row[0].size();j++){
            
            if(row[i][j][0] == '['){
               string s = row[i][j];
               s.erase(s.begin());
               s.erase(s.end() - 1);
               s = s + ',';
               string word = "";
               for(int k = 0;k<s.size();k++){
                  if(s[k] == ','){
                    if(find(st.begin(),st.end(),word) == st.end()){
                     st.push_back(word);
                     word = "";
                    }
                  }
                  else{
                    word = word + s[k];
                  }
               }
            }
            else{
                if(find(st.begin(),st.end(),row[i][j]) == st.end()){
                     st.push_back(row[i][j]);
                    }
                
            }
        }
    }

    for(auto it = st.begin();it != st.end();it++){
        if(*it == "\n" || *it == "" || *it == " ")
         st.erase(it);
    }

    int entityMadeCounter = 0;
    //entity code ends

    //storing students record

    for(int i  = 0;i<row.size();i++){
        StudentRecord obj;
        for(int j = 0;j<2;j++){
            if(j == 0){
                obj.set_studentName(row[i][j]);
            }
            else{
                obj.set_rollNumber(row[i][j]);
            }
        }

        students.push_back(obj);
    }
    
    

    //students record ends

    //creating the entity

    for(auto it = st.begin();it != st.end();it++){
        LinkedList ob;
        ob.set_name(*it);
        ob.set_iterator(nullptr);
        EntityArray.push_back(ob);

    }
 

    //done creating entity array

    //adding students to different linkedlist
    int studentPointer = 0;
    for(int i  = 0;i<row.size();i++){
      
        for(int j = 2;j<row[0].size();j++){
            
            if(row[i][j][0] == '['){
               string s = row[i][j];
               //erasing the string
               s.erase(s.begin());
               s.erase(s.end() - 1);
               s = s + ',';
               string word = "";
               for(int k = 0;k<s.size();k++){
                  if(s[k] == ','){
                    string name = word;
                    //checking for the entity
                    for (LinkedList  &entity : EntityArray) {
                                if (entity.get_name() == name) {
                                    entity.add_student(students[studentPointer]);
                                }
                            }
                    word = "";
                  }
                  else{
                    word = word + s[k];
                  }
               }
            }
            else{
                //if found add here
                for (LinkedList &entity : EntityArray) {
                                string name = row[i][j];
                                if (entity.get_name() == name) {
                                    entity.add_student(students[studentPointer]);
                                }
                            }
                 
            }
        }

        studentPointer = studentPointer + 1;
    }

}
