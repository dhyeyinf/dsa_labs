#include <bits/stdc++.h>


using namespace std;

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

    void set_next(Node* value) {
        next = value;
    }

    void set_element(StudentRecord* student) {
        element = student;
    }

};

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

vector<StudentRecord> students;


class LinkedList : public Entity {
    // Implement LinkedList members here
public:
    void add_student(StudentRecord &student)
    {
        Node* temp= get_iterator();
        if(temp == nullptr)
         set_iterator(temp);
        else{ 
        while(temp->get_next()!=nullptr)
        {
            temp=temp->get_next();
        }
        
        
        Node* newnode = new Node();
        newnode->set_element(&student);
        newnode->set_next(nullptr);
        temp->set_next(newnode);
        }

       
    }
   void delete_student(string studentName)
{
    Node* temp = get_iterator();
    Node* prev = nullptr;  // Maintain a pointer to the previous node

    while (temp->get_next() != nullptr && temp->get_next()->get_element()->get_studentName() != studentName)
    {
        prev = temp;
        temp = temp->get_next();
    }

    if (temp->get_next() != nullptr) // Check if the student was found
    {
        Node* nodeToDelete = temp->get_next();

        if (prev) {
            prev->set_next(nodeToDelete->get_next());
        }
        else {
            // If the target node is the first node, update the head
            // You should have a head pointer for your linked list.
            // Assuming head is a pointer to the first node:
            set_iterator(nodeToDelete->get_next());
        }

        // Deallocate memory for the nodeToDelete if it's dynamically allocated
        delete nodeToDelete->get_element();
        delete nodeToDelete;
    }
}

};
vector<LinkedList> EntityArray;

void read_input_file(string file_path)
{
    string attribute;
    int attributeIndex=0;
    Entity* entity;
    ifstream fileinput (file_path);
    if (!fileinput.is_open())
    {
        cerr<<" Failed to open the file"<<endl;
        return;
    }
     
    string line, studentName, rollNumber;
    stringstream ss;
    while (getline(fileinput,line))
    {
                line.pop_back();

        stringstream ss (line);
        getline(ss, studentName, ',');
        getline(ss,rollNumber,',');
     //   cout<< studentName<< " "<<rollNumber<<endl;
        StudentRecord* student= new StudentRecord();
        student->set_studentName (studentName);
        student->set_rollNumber(rollNumber);
        students.push_back(*student);
     // cout<< line<< endl;

   
    while (getline ( ss, attribute, ','))
    {    // cout<<attribute<<endl;
          if (attribute[0]=='[')
          attribute.erase(0,1);
          
          if (attribute.back()==']')
          attribute.pop_back();
          
          
         // cout<<attribute<<endl;

          
       // if (attributeIndex>=2)
        //  {
            bool entityExists=false;
            for (auto entity : EntityArray)
            {
                 if (entity.get_name()==attribute)
                 {
                     entity.add_student(*student);
                     entityExists=true;
                     
                     break;
                 }

            }
          
 
          if (!entityExists) {
             
            LinkedList newentity;
            newentity.set_name(attribute);
            Node* newnode=new Node();
            newnode-> set_element(student);
            newnode-> set_next(nullptr);
            newentity.set_iterator(newnode);
            EntityArray.push_back(newentity);
      //      cout<<attribute<<endl;
         // }
    }
    attributeIndex++;
   }

}}
