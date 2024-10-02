#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop {
private:
    std::string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(std::string name, MetroLine* metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop* getNextStop() const;
    MetroStop* getPrevStop() const;
    MetroLine* getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop* next);
    void setPrevStop(MetroStop* prev);
};

MetroStop::MetroStop(std::string name, MetroLine* metroLine, int fare) {
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const {
    return stopName;
}

MetroStop* MetroStop::getNextStop() const {
    return nextStop;
}

MetroStop* MetroStop::getPrevStop() const {
    return prevStop;
}

MetroLine* MetroStop::getLine() const {
    return line;
}

int MetroStop::getFare() const {
    return fare;
}

void MetroStop::setNextStop(MetroStop* next) {
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop* prev) {
    prevStop = prev;
}

// MetroLine class
class MetroLine {
private:
    std::string lineName;
    MetroStop* node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop* getNode() const;

    // Setter methods
    void setNode(MetroStop* node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name) {
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const {
    return lineName;
}

MetroStop* MetroLine::getNode() const {
    return node;
}

void MetroLine::setNode(MetroStop* node) {
    this->node = node;
}

void MetroLine::printLine() const {
    MetroStop* stop = node;
    while (stop != nullptr) {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}
void MetroLine::populateLine(std::string filename) {
    // Read the file and populate the line
    ifstream in(filename);
    string line,word;
    while(getline(in,line)){
        
        stringstream ss(line);
        vector<string> v;
        while(getline(ss,word,' ')){
            if(word[word.size()-1]==','){
                word.erase(word.end()-1);
            }
            v.push_back(word);
        }
        v.erase(v.end()-1);
        string name="\0";
        for(int i=0;i<v.size();i++){
            name=name+" "+v[i];
        }
        name.erase(name.begin());
        MetroStop* obj=new MetroStop(name,this,stoi(word));
        if(!node){
            node=obj;
        }
        else{
            MetroStop* temp=node;
            while(temp->getNextStop()){
                temp=temp->getNextStop();
            }
            temp->setNextStop(obj);
            obj->setPrevStop(temp);

        }

    }
}

int MetroLine::getTotalStops() const {
    int counter=0;
    MetroStop* temp=node;
    while(temp){
        counter++;
        temp=temp->getNextStop();

    }
    return counter;

}

// AVLNode class
class AVLNode {
private:
    std::string stopName;
    std::vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop*>& getStops() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() const;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
};

AVLNode::AVLNode(std::string name) {
    stopName = name;
    left = nullptr;
    right = nullptr;
}

std::string AVLNode::getStopName() const {
    return stopName;
}

const std::vector<MetroStop*>& AVLNode::getStops() const {
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent() const {
    return parent;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree {
    // Define your AVLTree implementation here.
private:
    AVLNode* root;

public:
    // getter methods
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    void rotateLeft(AVLNode* node);
    void rotateRight(AVLNode* node);
    void balance(AVLNode* node);
    int stringCompare(string s1, string s2);
    void insert(AVLNode* node, MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchStop(string stopName);
};

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this->root = root;
}

int AVLTree::height(AVLNode* node) {
    if(!node){
        return 0;
    }
    return 1+max(height(node->getLeft()),height(node->getRight()));
}

int AVLTree::stringCompare(string s1, string s2) {
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode* node) {
    return height(node->getLeft())-height(node->getRight());
}

void AVLTree::rotateLeft(AVLNode* node) {
    AVLNode* node1=node->getRight();
    AVLNode* node2=node1->getLeft();
    
    if(!node->getParent()){
       // cout<<"ilo"<<endl;
        setRoot(node1);
    }
    else{
        if(node==node->getParent()->getLeft()){
            node->getParent()->setLeft(node1);
            
        }
        else{
            node->getParent()->setRight(node1);
        }
    }
    node1->setParent(node->getParent());
    node1->setLeft(node);
    node->setParent(node1);
    node->setRight(node2);
    if(node2){
    node2->setParent(node);
    }
}

void AVLTree::rotateRight(AVLNode* node) {
    AVLNode* node1=node->getLeft();
    AVLNode* node2=node1->getRight();
    
    if(!node->getParent()){
        setRoot(node1);
        
    }
    
    else{
    
        if(node==node->getParent()->getLeft()){
            
            node->getParent()->setLeft(node1);          
        }
        else{
            
            node->getParent()->setRight(node1);      
        }
    }
    
    node1->setParent(node->getParent());
    node1->setRight(node);
    node->setParent(node1);
    node->setLeft(node2);
    if(node2){
    node2->setParent(node);
    }
}

void AVLTree::balance(AVLNode* node) {
    int bal=balanceFactor(node);
    if(bal>1){
        
        if(balanceFactor(node->getLeft())>0){
            
            rotateRight(node);
            
        }
        else{
            rotateLeft(node->getLeft());
            rotateRight(node);
        }
    }
    else if(bal<-1){
        if(balanceFactor(node->getRight())>0){
            rotateRight(node->getRight());
            rotateLeft(node);
        }
        else{
          //  cout<<"uio"<<endl;
            rotateLeft(node);
           // cout<<"3333"<<endl;
        }
    } 
      
}

void AVLTree::insert(AVLNode* node, MetroStop* metroStop) {
    if(!getRoot()){
        setRoot(new AVLNode(metroStop->getStopName()));
        root->setParent(nullptr);
        //cout<<"error"<<endl;
        
        return;
    }
    
    else if(stringCompare(node->getStopName(),metroStop->getStopName())>0 && node->getLeft()){
        insert(node->getLeft(),metroStop);
       
        balance(node);
    }
    else if(stringCompare(node->getStopName(),metroStop->getStopName())>0 && !node->getLeft()){
       // cout<<"left"<<endl;
        AVLNode* temp=new AVLNode(metroStop->getStopName());
        temp->setParent(node);
        node->setLeft(temp);
        
        
        balance(node);

    }
    else if(stringCompare(metroStop->getStopName(),node->getStopName())>0 && node->getRight()){
      //  cout<<"before right"<<endl;
        insert(node->getRight(),metroStop);
       // cout<<"tut"<<endl;
        balance(node);
        //cout<<"lol"<<endl;
    }

    else if(stringCompare(metroStop->getStopName(),node->getStopName())>0 && !node->getRight()){
        //cout<<"right"<<endl;
        AVLNode* temp=new AVLNode(metroStop->getStopName());
        temp->setParent(node);
        node->setRight(temp);
        //cout<<"123"<<endl;
        balance(node);
       // cout<<"345"<<endl;
    }
   // cout<<"insertion done"<<endl;
    
}

AVLNode* AVLTree::searchStop(string stopName) {
   
    AVLNode* temp=root;
    while(temp && temp->getStopName()!=stopName){
        if(stringCompare(stopName,temp->getStopName())>0){
            temp=temp->getRight();
        }
        else{
            temp=temp->getLeft();
        }

    }
    return temp;

}

void AVLTree::populateTree(MetroLine* metroLine) {
    
    if(root){
        root->setParent(nullptr);
    }
    
    MetroStop* temp=metroLine->getNode();
    while(temp){
           
           if(!searchStop(temp->getStopName())){
           
           insert(root,temp);
          
           AVLNode* tem=searchStop(temp->getStopName());
           tem->addMetroStop(temp);
           
        }
        else{
           
            
            AVLNode* tem=searchStop(temp->getStopName());
                        tem->addMetroStop(temp);
            
        }            
          
        temp=temp->getNextStop(); 
    }
    
    
}

void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}



// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;
    

public:
    bool val;
    Trip(MetroStop* metroStop, Trip* previousTrip);

    // Getter methods
    MetroStop* getNode() const;
    Trip* getPrev() const;
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip) {
    node = metroStop;
    prev = previousTrip;
}

MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    std::queue<Trip*> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip*> getTrips() const;

    // Setter methods
    void enqueue(Trip* trip);
    Trip* dequeue();
    bool isEmpty() const;
};

Exploration::Exploration() {
}

std::queue<Trip*> Exploration::getTrips() const {
    return trips;
}

void Exploration::enqueue(Trip* trip) {
    trips.push(trip);
}

Trip* Exploration::dequeue() {
    if (trips.empty()) {
        return nullptr;
    }
    Trip* trip = trips.front();
    trips.pop();
   cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const {
    return trips.empty();
}

class Path {
private:
    std::vector<MetroStop*> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop*> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

std::vector<MetroStop*> Path::getStops() const {
    return stops;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {
    for (auto stop : stops) {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    std::vector<MetroLine*> lines;

public:
    PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines);
    void createAVLTree();
    Path* findPath(std::string origin, std::string destination);

    // Getter methods
    AVLTree* getTree() const;
    const std::vector<MetroLine*>& getLines() const;
};

PathFinder::PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines) {
    tree = avlTree;
    lines = metroLines;
}

AVLTree* PathFinder::getTree() const {
    return tree;
}

const std::vector<MetroLine*>& PathFinder::getLines() const {
    return lines;
}

void PathFinder::createAVLTree() {
    
    for(int i=0;i<lines.size();i++){
        tree->populateTree(lines[i]);
        
    }
    
}

int num_jn(AVLTree* tree,MetroStop* metrostop){
    AVLNode* temp=nullptr;
    temp=tree->searchStop(metrostop->getStopName());
    return temp->getStops().size();

}
vector<Trip*> vec;
bool check(string name){
    for(int i=0;i<vec.size();i++){
        if(vec[i]->getNode()->getStopName()==name){
            return true;
        }

    }
    return false;
}


Path* PathFinder::findPath(std::string origin, std::string destination) {
  //  cout<<"lop"<<endl;
    AVLNode* orig=nullptr;
    Path* path=nullptr;
    MetroStop* temp=nullptr;
    if(!tree->searchStop(origin)){
       // cout<<"iop"<<endl;
        return nullptr;
    }
    else{
        orig=tree->searchStop(origin);
    }
    if(!tree->searchStop(destination)){
        return nullptr;
    }
    //cout<<orig->getStopName()<<endl;
    temp=orig->getStops()[0];
   // cout<<temp->getStopName()<<endl;
    Exploration* exp=new Exploration();
    int vs=num_jn(tree,temp);
    //cout<<vs<<"lk"<<endl;
    int j=0;
    while(vs>0){
        
        Trip* forw=new Trip(temp,nullptr);
        forw->val=true;
        Trip* back=new Trip(temp,nullptr);
        back->val=false;
        vec.push_back(forw);
        vec.push_back(back);
        exp->enqueue(forw);
        exp->enqueue(back);
        j++; 
        temp=orig->getStops()[j];
        vs--;
    }
   // cout<<vs<<endl;
   
    Trip* tem=exp->dequeue();
    temp=tem->getNode();
   // cout<<temp->getStopName()<<" "<<temp->getLine()->getLineName()<<"ooo"<<endl;
    bool a=true;
    while(temp){
        
       
        while(temp){
            if(temp->getStopName()==destination){
                //cout<<"entered if"<<endl;
                path=new Path();
                while(tem){
                    path->setTotalFare(path->getTotalFare()+abs(temp->getFare()-tem->getNode()->getFare()));
                    while(temp!=tem->getNode()){
                        path->addStop(temp);
                        if(tem->val){
                            temp=temp->getPrevStop();
                        }
                        else{
                            temp=temp->getNextStop();
                        }
                       
                    }
                    tem=tem->getPrev();
                    if(tem){
                        AVLNode* node=tree->searchStop(temp->getStopName());
                        vector<MetroStop*> v=node->getStops();
                        for(int i=0;i<v.size();i++){
                            if(v[i]->getLine()==tem->getNode()->getLine()){
                                temp=v[i];
                                break;
                            }
                        }
                    }


                }
               path->addStop(temp); 
              // cout<<exp->getTrips().size()<<endl;

               return path;


            }
     else if(a){
           // cout<<"entered else if"<<endl;
            temp = temp -> getNextStop();
            
            if(!temp){
                a=false;
            }
            else{
          //  cout<<temp->getStopName()<<" "<<temp->getLine()->getLineName()<<endl;
            int b=num_jn(tree,temp);
           //cout<<b<<" "<<temp->getStopName()<<endl;
            if(b>1){
               // cout<<"seytyusfdyuewdfkfdkfewukwfdkuwfeud"<<endl;
                AVLNode* abc=nullptr;
                abc=tree->searchStop(temp->getStopName());
                for(int i=0;i<b;i++){
                if(abc->getStops()[i]!=temp && !check(temp->getStopName())){
                
                Trip* tem1=new Trip(abc->getStops()[i],tem);
                tem1->val=true;
                Trip* tem2=new Trip(abc->getStops()[i],tem);
                tem2->val=false;
                vec.push_back(tem1);
                vec.push_back(tem2);
                exp->enqueue(tem1);
                exp->enqueue(tem2);
                //cout<<"enque"<<" "<<temp->getStopName()<<endl;
                }
              }
    
            }
            }

        }
            else{
             
                temp=temp->getPrevStop();
                if(!temp){
                    a=true;
                }
                else{
                int b=num_jn(tree,temp);

            if(b>1){
                
                AVLNode* abc=tree->searchStop(temp->getStopName());
                for(int i=0;i<b;i++){
                if(abc->getStops()[i]!=temp && !check(temp->getStopName())){
                
                Trip* tem1=new Trip(abc->getStops()[i],tem);
                tem1->val=true;
                Trip* tem2=new Trip(abc->getStops()[i],tem);
                tem2->val=false;
                vec.push_back(tem1);
                vec.push_back(tem2);
                exp->enqueue(tem1);
                exp->enqueue(tem2);
                }
            }
                
            }
            }

            }
        }
       // cout<<a<<endl;
        
        tem=exp->dequeue();
        
        
        if(tem){
        temp=tem->getNode();  
       // cout<<temp->getStopName()<<" "<<temp->getLine()->getLineName()<<endl;
          
        }
        else{
            temp=nullptr;
        }

    }
    //cout<<"i am here"<<endl;
    return path;
}

vector <MetroLine*> lines;
