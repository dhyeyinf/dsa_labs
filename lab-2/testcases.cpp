#include<bits/stdc++.h>
#include "interface_template.cpp"

int failed_tests = 0;

void test1() {
    std::string entity_name = "CSE";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    StudentRecord* student;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == "JohnDoe") {
            student = ite->get_element();
            break;
        }
        ite = ite->get_next();
    }
    assert(student->get_studentName() == "JohnDoe" && "Student JohnDoe is not present in the CSE Entity");
}

void test2() {
    std::string entity_name = "EE";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    StudentRecord* student;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == "SanyaSharma") {
            student = ite->get_element();
            break;
        }
        ite = ite->get_next();
    }
    assert(student->get_studentName() == "SanyaSharma"&& "Student SanyaSharma is not present in the EE Entity");
}

void test3() {
    std::string entity_name = "DSA";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    int size = 0;
    while (ite != nullptr) {
        size += 1;
        ite = ite->get_next();
    }
    assert(size == 20 && "Incorrect count of records in DSA course");
}

void test4() {
    std::string entity_name = "Programming";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    int size = 0;
    while (ite != nullptr) {
        size += 1;
        ite = ite->get_next();
    }
    assert(size == 20 && "Incorrect count of records in Programming Club");
}

void test5() {
    std::string entity_name = "Toastmasters";
    LinkedList entity;
    std::string studentname = "RaviKumar";

    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }

    entity.delete_student(studentname);
    Node* ite = entity.get_iterator();

    int if_exists = 0;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == studentname) {
            if_exists = 1;
            break;
        }
        ite = ite->get_next();
    }

    assert(if_exists == 0 && "Record still exists, Delete function not working!");
}

void test6() {
    std::string entity_name = "Maths";
    LinkedList entity;
    std::string studentname = "UzumakiNaruto";
    std::string studentroll = "B20CS011";
    StudentRecord student;
    student.set_studentName(studentname) ;
    student.set_rollNumber(studentroll) ;

    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }

    entity.add_student(student);
    Node* ite = entity.get_iterator();

    int if_exists = 0;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == studentname) {
            if_exists = 1;
            break;
        }
        ite = ite->get_next();
    }

    assert(if_exists == 1 && "Record is not added, Add Student Record function not working!");
}

void test7() {
    std::string entity_name = "PRML";
    LinkedList entity;
    std::string studentname = "HimashuGupta";

    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }

    entity.delete_student(studentname);
    Node* ite = entity.get_iterator();

    int if_exists = 0;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == studentname) {
            if_exists = 1;
            break;
        }
        ite = ite->get_next();
    }

    assert(if_exists == 0 && "Record still exists, Delete function not working!");
}

void test8() {
    std::string entity_name = "G5";
    LinkedList entity;
    std::string studentname = "UchihaSasuke";
    std::string studentroll = "B20ES011";
    StudentRecord student;
    student.set_studentName(studentname) ;
    student.set_rollNumber(studentroll) ;

    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }

    entity.add_student(student);
    Node* ite = entity.get_iterator();

    int if_exists = 0;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == studentname) {
            if_exists = 1;
            break;
        }
        ite = ite->get_next();
    }

    assert(if_exists == 1 && "Record is not added, Add Student Record function not working!");
}

int main() {
    int failed_tests = 0;
    //cout << "i am good" << endl;
    std::vector<void (*)()> unit_tests_list = {
        test1, test2, test3, test4, test5, test6, test7, test8
    };
    int total = unit_tests_list.size();

    try {
        read_input_file("Details.txt");
    } catch (const std::exception& e) {
        std::cout << "Could not read Sample Input File! Ensure that the file 'Details.txt' is in the folder and try again!" << std::endl;
        return 1;
    }

    for (int i = 0; i < total; ++i) {
        try {
            unit_tests_list[i]();
        } catch (const std::exception& e) {
            failed_tests++;
            std::cout << "Unit test #" << i+1 << " failure: " << e.what() << std::endl;
        }
    }

    if (failed_tests == 0) {
        std::cout << "All tests have passed successfully!" << std::endl;
    } else {
        std::cout << failed_tests << " tests failed!" << std::endl;
    }

    cout << "Number of failed test cases are: " << failed_tests<< endl;
    return 0;
}
