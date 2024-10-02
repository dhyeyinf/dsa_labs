#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "student_solution.cpp"
using namespace std;


vector<string> getFileNames() {
    vector<string> filenames;
    filenames.push_back("blue.txt");
    filenames.push_back("green.txt");
    filenames.push_back("magenta.txt");
    filenames.push_back("orange.txt");
    filenames.push_back("red.txt");
    filenames.push_back("violet.txt");
    filenames.push_back("yellow.txt");
    return filenames;
}

void testPopulateLine() {
    cout<<"Testing populateLine()"<<endl;
    vector<string> filenames = getFileNames();
    int expectedTotalStops[] = {44, 21, 25, 6, 29,38, 62};
    for (int i = 0; i < filenames.size(); i++) {
        string lineName = filenames[i].substr(0, filenames[i].length() - 4);
        MetroLine* metroLine = new MetroLine(lineName);
        metroLine->populateLine(filenames[i]);
        lines.push_back(metroLine);
        cout << "Line name: " << metroLine->getLineName() << endl;
        cout << "Total stops: " << metroLine->getTotalStops() << endl;
        cout << endl;
        assert(metroLine->getTotalStops() == expectedTotalStops[i]);
        metroLine->printLine();
    }
}

void testPopulateTree() {
    cout<<"Testing populateTree()"<<endl;
    vector<string> filenames = getFileNames();
    AVLTree* tree = new AVLTree();
    tree->setRoot(nullptr);
    for (auto line : lines) {
        if (tree->getRoot() == nullptr) {
            tree->setRoot(new AVLNode(line->getNode()->getStopName()));
        }
        tree->populateTree(line);
    }
    cout << "Height of tree: " << tree->height(tree->getRoot()) << endl;
    cout << "Total nodes in tree: " << tree->getTotalNodes(tree->getRoot()) << endl;
    assert(tree->height(tree->getRoot()) == 9);
    assert(tree->getTotalNodes(tree->getRoot()) == 211);
}

vector<pair<string, string>> getExpectedPathPairs() {
    vector<pair<string, string>> expectedPathPairs;
    expectedPathPairs.push_back(make_pair("Pitampura", "Pul Bangash"));
    expectedPathPairs.push_back(make_pair("Brigadier Hoshiar Singh", "Inderlok"));

    return expectedPathPairs;
}

map<int, vector<string>> expectedPathMapping() {
    map<int, vector<string>> m;
    m[0] = vector<string> {"Pul Bangash", "Pratap Nagar", "Shastri Nagar", "Inder Lok", "Kanhaiya Nagar", "Keshav Puram", "Netaji Subhash Place", "Kohat Enclave", "Pitampura"};
    m[1] = vector<string> {"Inderlok", "Ashok Park Main", "Punjabi Bagh", "Shivaji Park", "Madi Pur", "Paschim Vihar East", "Paschim Vihar West", "Peera Garhi", "Udyog Nagar", "Surajmal Stadium", "Nangloi", "Nangloi Railway Station", "Rajdhani Park", "Mundka", "Mundka Industrial Area", "Ghevra Metro Station", "Tikri Kalan", "Tikri Border", "Pandit Shree Ram Sharma", "Bahadurgarh City", "Brigadier Hoshiar Singh"};

    return m;
}

void testFindPath() {
    PathFinder* pathFinder = new PathFinder(new AVLTree(), lines);
    pathFinder->createAVLTree();
    vector<pair<string, string>> expectedPathPairs = getExpectedPathPairs();
    for (int i = 0; i < expectedPathPairs.size(); i++) {
        Path* path = pathFinder->findPath(expectedPathPairs[i].first, expectedPathPairs[i].second);
        assert(path != nullptr);
        cout << "Total fare: " << path->getTotalFare() << endl;
        path->printPath();
        vector<string> expectedPath = expectedPathMapping()[i];
        for (int j = 0; j < expectedPath.size(); j++) {
            assert(path->getStops()[j]->getStopName() == expectedPath[j]);
        }
    }
}

int main() {
    vector<void(*)()> tests;
    tests.push_back(&testPopulateLine);
    tests.push_back(&testPopulateTree);
    tests.push_back(&testFindPath);

    for (auto test : tests) {
        test();
    }
    cout<<"test cases passed"<<endl;

    return 0;
}
