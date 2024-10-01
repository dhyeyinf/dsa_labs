#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Vehicle;

class Trip {
public:
    Trip(Vehicle* vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle* getVehicle() const {
        return vehicle;
    }

    std::string getPickUpLocation() const {
        return pick_up_location;
    }

    std::string getDropLocation() const {
        return drop_location;
    }

    int getDepartureTime() const {
        return departure_time;
    }

    int getBookedSeats() const {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle* v) {
        vehicle = v;
    }

    void setPickUpLocation(std::string location) {
        pick_up_location = location;
    }

    void setDropLocation(std::string location) {
        drop_location = location;
    }

    void setDepartureTime(int time) {
        departure_time = time;
    }

    void setBookedSeats(int seats) {
        booked_seats = seats;
    }

private:
    Vehicle* vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};

class BinaryTreeNode;

// BinaryTreeNode* insertdata(BinaryTreeNode* root, int data, Trip* trip){
//     if(root == nullptr){
//         BinaryTreeNode* parent = nullptr;
//         BinaryTreeNode* r = new BinaryTreeNode(data,trip,parent);
//         r->setDepartureTime(data);
//         r->setTripNodePtr(trip);
//         return r;
//     }
//     // Node* tree = new Node;
//     if(data >root->getDepartureTime()){
//         root->setRightPtr(insertdata(root->getRightPtr(),data,trip));
//     }
//     else{
//         root->setLeftPtr(insertdata(root->getLeftPtr(),data,trip));
//     }
//     return root;
// }



class BinaryTreeNode {
public:
    BinaryTreeNode(int departuretime = 0, Trip* tripenodeptr = nullptr, BinaryTreeNode* parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode* getLeftPtr() const {
        return leftptr;
    }

    BinaryTreeNode* getRightPtr() const {
        return rightptr;
    }

    BinaryTreeNode* getParentPtr() const {
        return parentptr;
    }

    int getDepartureTime() const {
        return departuretime;
    }

    Trip* getTripNodePtr() const {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode* left) {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode* right) {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode* parent) {
        parentptr = parent;
    }

    void setDepartureTime(int time) {
        departuretime = time;
    }

    void setTripNodePtr(Trip* trip) {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode* leftptr;
    BinaryTreeNode* rightptr;
    BinaryTreeNode* parentptr;
    int departuretime;
    Trip* tripnodeptr;
};

int numb = 50;

class TransportService {
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    BinaryTreeNode* getBSTHead() const {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name) {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode* node) {
        BSThead = node;
    }

    void addTrip(int key, Trip* trip){
        // BSThead = insertdata(BSThead,key,trip);

        BinaryTreeNode* temp=getBSTHead();
        BinaryTreeNode* parent=nullptr;
        while(temp){
            if(key>temp->getDepartureTime()){
                parent =  temp;
                temp = temp->getRightPtr();
            }
            else{
                parent=temp;
                temp=temp->getLeftPtr();
            }
        }
        temp=new BinaryTreeNode(key,trip,parent);
        if(getBSTHead()==nullptr)  
            setBSTHead(temp);
            if(parent!=nullptr){
                if(parent->getDepartureTime()>=temp->getDepartureTime()){
                    parent->setLeftPtr(temp);
                }
                else{
                    parent->setRightPtr(temp);
                }
            }
    }

private:
    std::string name;
    BinaryTreeNode* BSThead;
};


class Vehicle {
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const {
        return vehicle_number;
    }

    int getSeatingCapacity() const {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(std::string number) {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity) {
        seating_capacity = capacity;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

    vector<Trip*> getTrips(){
        return trips;
    }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip*> trips;
};

int check_sptr(vector<TransportService*> serviceptrs, string dloc){
    for(int i = 0 ; i<serviceptrs.size() ; i++){
        if(serviceptrs[i]-> getName() == dloc){
            return i;
        }
    }
    return -1;
}

class Location {
public:
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    TransportService* getServicePtr(std::string droplocation) const {
        int l = check_sptr(serviceptrs, droplocation);
        if(l == -1){
            return nullptr;
        }
        else{
            return serviceptrs[l];
        }
    }

    // Setter functions
    void setName(std::string location_name) {
        name = location_name;
    }

    TransportService* setServicePtr(std::string droplocation) {
        TransportService* tserv = new TransportService(droplocation);
        serviceptrs.push_back(tserv);
        return nullptr;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }
    
    // vector<Trip*> travservice(){
    //     vector<Trip*> result;
    //     for(int i = 0 ; i<serviceptrs.size() ; i++){
    //         BinaryTreeNode* node = serviceptrs[i]-> getBSTHead();
    //         result = Inordertrav(node);
    //     }
    // }

    std::vector<TransportService*> sptrs(){
        return serviceptrs;
    }

    // BinaryTreeNode* getnode(){
    //     for(int i=0 ; i<serviceptrs.size() ; i++){
    //         if(serviceptrs[i] == destination)
    //         return serviceptrs[i]-> getBSTHead();
    //     }
    //     return nullptr;
    // }

    vector<Trip*> getTrip(){
        return trips;
    }

private:
    std::string name;
    std::vector<TransportService* >serviceptrs;
    std::vector<Trip*> trips;
};

int tree_height(BinaryTreeNode* node){
    if(node == nullptr){
        return 0;
    }
    return 1+max(tree_height(node->getLeftPtr()),tree_height(node->getRightPtr()));

}

int tree_nodes(BinaryTreeNode*root){
	static int count = 1;
    if(root == NULL)
		return 0;
	if(root-> getLeftPtr() != NULL){
		count = count+1;
		count = tree_nodes(root->getLeftPtr());
	}
	if(root-> getRightPtr() != NULL){
		count = count+1;
		count = tree_nodes(root->getRightPtr());
	}
	return count;
}

class BinaryTree {
protected:
    BinaryTreeNode* root;

public:
    BinaryTree() : root(nullptr) {}

    int getHeight() const {
        return tree_height(root);
         // Placeholder
    }

    int getNumberOfNodes() const {
        return tree_nodes(root);
        // Placeholder
    }

    void setRoot(BinaryTreeNode* node){
        root = node;
        return;
    }

    BinaryTreeNode*  getRoot(){
        return  root;
    }
};

BinaryTreeNode* getminnode(BinaryTreeNode* node) {
    while(node->getLeftPtr()){
        node = node->getLeftPtr();
    }
    return node;
}

BinaryTreeNode* getmaxnode(BinaryTreeNode* node) {
    while(node->getRightPtr()){
        node = node->getRightPtr();
    }
    return node;
}

BinaryTreeNode* getsucnode(BinaryTreeNode* root,int data){
    BinaryTreeNode* ans = nullptr;
    while(root != nullptr)
    if(root->getDepartureTime() == data){   
        if(root->getRightPtr()){
            ans = getminnode(root->getRightPtr());
            break; 
        }
    }
    else if(data < root->getDepartureTime()){   
        ans = root;
        root = root->getLeftPtr();
    }
    else{
        root = root->getRightPtr();
    }
    return ans;
}

BinaryTreeNode* getprenode(BinaryTreeNode* root,int data){
    BinaryTreeNode* ans = nullptr;
    while(root != nullptr){
        if(root->getDepartureTime() == data){
            if(root->getLeftPtr()){
                ans = getmaxnode(root->getLeftPtr());
                break;
            } 
        }
        else if(data > root->getDepartureTime()){
            ans = root;
            root = root->getRightPtr();
        }
        else{
            root = root->getLeftPtr();    
        }
    }
}

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree() {}

    BinaryTreeNode* getElementWithMinimumKey() const {
        // Implement this function to return the element with the minimum key
        BinaryTreeNode* ans = getminnode(root);
        return ans;
    }

    BinaryTreeNode* getElementWithMaximumKey() const {
        // Implement this function to return the element with the maximum key
        BinaryTreeNode* ans = getmaxnode(root);
        return ans;
    }

    BinaryTreeNode* searchNodeWithKey(int key) const {
        // Implement this function to search for a node with the given key or the next larger key
        BinaryTreeNode* ans = root;
        while(ans && ans->getDepartureTime() != key){
            if(ans->getDepartureTime() > key){
                ans = ans->getLeftPtr();
            }
            else{
                ans = ans->getRightPtr();
            }
        }
        return ans;
    }

    BinaryTreeNode* getSuccessorNode(BinaryTreeNode* node) const {
        // Implement this function to return the successor node of the given node
        BinaryTreeNode* ans = getsucnode(root,node->getDepartureTime());
        return ans;
    }

    BinaryTreeNode* getSuccessorNodeByKey(int key) const {
        // Implement this function to return the successor node by key
        BinaryTreeNode* result=getsucnode(root,key);
        return result;
    }

    BinaryTreeNode* getPredecessorNode(BinaryTreeNode* node) const {
        // Implement this function to return the predecessor node of the given node
        BinaryTreeNode* result=getprenode(root,node->getDepartureTime());
        return result;
    }

    BinaryTreeNode* getPredecessorNodeByKey(int key) const {
        // Implement this function to return the predecessor node by key
        BinaryTreeNode* result=getprenode(root,key);
        return result;
    }
};

int checki(int d){
    for(int i = 0 ; i<numb ; i++){
        d++;
    }
    return d;
}

int check_vehicle(vector<Vehicle*> vh ,string vhnum){
    for(int i=0 ; i<vh.size() ; i++){
        if(vhnum == vh[i]-> getVehicleNumber() ){
            return i;
        }
    }
    return -1;
}

int check_location(vector<Location*> lc ,string pickup){
    for(int i=0 ; i<lc.size() ; i++){
        if(lc[i]-> getName() == pickup){
            return i;
        }
    }
    return -1;
}


// Node* formtree(Node* tree){
//     int data;
//     cin >> data;
//     while(data != -1){
//         tree = insertdata(tree,data);
//         cin >> data;
//     }
//     return tree;
// }

// void add_deptime(Location* l, int dtime, string destination){
//     BinaryTreeNode* bst = l->getServicePtr(destination)->getBSTHead();
//     bst = insertdata(bst, dtime);
// }

void intrav(BinaryTreeNode* root , vector<BinaryTreeNode* > &dummy){
    int flag = 0;

    if(root == nullptr){
        return ;
    }
    intrav(root->getLeftPtr(), dummy);
    // if(root->getDepartureTime() >= atime && root->getDepartureTime() < btime){
    //     result.push_back(root->getTripNodePtr());
    // }
    // if(root->getDepartureTime() >= btime){
    //     return result;
    // }
    dummy.push_back(root);

    intrav(root->getRightPtr(), dummy);
}

int getmaximumtime(BinaryTreeNode* root){
    BinaryTreeNode* node=root;
    while(node->getRightPtr()){
        node=node->getRightPtr();
    }
    return node->getDepartureTime();
}

BinaryTreeNode* dataerase(BinaryTreeNode* root,int data){
    if(root == nullptr){
        return nullptr;
    }
    // cout << "here -- " << endl;

    if(root->getDepartureTime() == data){
        if(!root->getLeftPtr() && !root->getRightPtr()){
            delete root;
            return nullptr;
        }

        if(root->getLeftPtr() && !root->getRightPtr()){
            BinaryTreeNode* temp=root->getLeftPtr();
            delete root;
            return temp;
        }

        if(!root->getLeftPtr() && root->getRightPtr()){
            BinaryTreeNode* temp=root->getRightPtr();
            delete root;
            return temp;
        }

        if(root->getLeftPtr() && root->getRightPtr()){
            int var = getmaximumtime(root->getLeftPtr());
            root->setDepartureTime(var);
            root->setLeftPtr(dataerase(root->getLeftPtr(), var));
        }
    }
    // cout << "here -- " << endl;
    else{
        if(root->getDepartureTime()>data){
            root->setLeftPtr(dataerase(root->getLeftPtr() , data));
        }
        else{
            root->setRightPtr(dataerase(root->getRightPtr() , data));
        }
    }
    // cout << "here -- " << endl;
}

class TravelDesk {
public:
    
    

    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time) {
        // Implement this function to add a trip
        Vehicle* vchl = nullptr;
        int l = -1; 
        // cout << "vehicle no is -- " << vehicle_number << endl;
        l = check_vehicle(vehicles, vehicle_number);
        // cout << "value of l is -- " << l << endl;
        if(l == -1){
            vchl = new Vehicle(vehicle_number,seating_capacity);
            vehicles.push_back(vchl);
        }
        else{
            vchl = vehicles[l]; 
        }
        Trip* trp = new Trip(vchl, pick_up_location, drop_location, departure_time);
        l = check_location(locations, pick_up_location);
        // cout << "hi" << endl;
        // Location* loc = new Location(pick_up_location);
        if(l == -1){
            Location* loc = new Location(pick_up_location);
            loc->addTrip(trp);
            loc->setServicePtr(drop_location);
            loc->getServicePtr(drop_location)->addTrip(departure_time,trp);
            locations.push_back(loc);
            // locations.push_back(loc);
        }
        else{
            if(!locations[l]->getServicePtr(drop_location)){
                locations[l]->setServicePtr(drop_location);
                locations[l]->addTrip(trp);
                locations[l]->getServicePtr(drop_location)->addTrip(departure_time,trp);
            }
            else{
                locations[l]->getServicePtr(drop_location)->addTrip(departure_time,trp);
            }
        }
        // add_deptime(loc, departure_time, drop_location, );
        // loc->getServicePtr(drop_location)->addTrip(departure_time,trp);
        int var = 0;

        var = checki(var);

        vchl->addTrip(trp);
        // loc->addTrip(trp);
        
    }

    int check = 0;

    std::vector<Trip*> showTrips(std::string pick_up_location, int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range
        vector<Trip* > result;
        vector<BinaryTreeNode*> dummy;
        if(before_time < after_time){
            int temp;
            temp = after_time;
            after_time = before_time;
            before_time = temp;
        }
        Location* loc = nullptr;
        for(int i = 0 ; i<locations.size() ; i++){
            if(locations[i]-> getName() == pick_up_location){
                loc = locations[i];
                break;
            }
        }
        if(loc != nullptr){
            vector<TransportService*> serv=loc->sptrs();
            for(int i = 0 ; i<serv.size() ; i++){
                intrav(serv[i]->getBSTHead() , dummy);
            }
        }

        for(int i=0;i<dummy.size();i++){
            if(dummy[i]->getDepartureTime()>=after_time && dummy[i]->getDepartureTime()<before_time){
                result.push_back(dummy[i]->getTripNodePtr());
            }
        }

        return result; // Placeholder
    }
    std::vector<Trip*> showTripsbydestination(std::string pick_up_location, std::string destination,int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin
        vector<Trip* > result;
        vector<BinaryTreeNode*> dummy;
        if(before_time < after_time){
            int temp;
            temp = after_time;
            after_time = before_time;
            before_time = temp;
        }
        Location* loc = nullptr;
        BinaryTreeNode* root;
        for(int i = 0 ; i<locations.size() ; i++){
            if(locations[i]-> getName() == pick_up_location){
                loc = locations[i];
                break;
            }
        }
        if(loc != nullptr){
            vector<TransportService*> temp=loc->sptrs();
            for(int i = 0 ; i<temp.size() ; i++){
                if(temp[i]->getName() == destination){
                    intrav(temp[i]->getBSTHead(), dummy);
                }
            }
            for(int i=0;i<dummy.size();i++){
                if(dummy[i]->getDepartureTime()>=after_time && dummy[i]->getDepartureTime()<before_time){
                    result.push_back(dummy[i]->getTripNodePtr());
                }
            }
        }


        return result; // Placeholder
    }

    Trip* bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time) {
        // Implement this function to book a trip
        Vehicle* vchl = nullptr;
        Trip* trip = nullptr;

        int l;
        l = check_vehicle(vehicles, vehicle_number);

        vchl = vehicles[l];

        // for(int i=0;i<vehicles.size();i++){
        //     if(vehicles[i]->getVehicleNumber()==vehicle_number){
        //         obj=vehicles[i];
        //     }
        // }

        if(vchl == nullptr)
        return nullptr;

        int var;

        vector<Trip*> trips;

        trips = vchl->getTrips();

        for(int i = 0 ; i<trips.size() ; i++){
            if(trips[i] -> getPickUpLocation() == pick_up_location && trips[i] -> getDropLocation() == drop_location && trips[i] -> getDepartureTime() == departure_time){
                trip = trips[i];
                break;
            }
        }

        if(trip == nullptr)
        return nullptr;

        if(trip->getBookedSeats() < vchl->getSeatingCapacity()){
            trip->setBookedSeats( trip->getBookedSeats() + 1 );
            return trip;
        }

        if(trip->getBookedSeats() == vchl->getSeatingCapacity()){
            Location* loc = getLocation(pick_up_location);
            TransportService* service;
            service = loc->getServicePtr(drop_location);
            dataerase(service->getBSTHead() , departure_time);
            
            for(int i = 0 ; i<vchl->getTrips().size() ; i++){
                if(vchl->getTrips()[i]->getPickUpLocation() == pick_up_location && vchl->getTrips()[i]->getDropLocation() == drop_location && vchl->getTrips()[i]->getDepartureTime() == departure_time){
                    vchl->getTrips().erase(vchl->getTrips().begin()+i);
                    break;
                }
            }

            for(int i=0;i<loc->getTrip().size();i++){
                if(loc->getTrip()[i]->getPickUpLocation()==pick_up_location && loc->getTrip()[i]->getDropLocation()==drop_location && loc->getTrip()[i]->getDepartureTime()==departure_time){
                    loc->getTrip().erase(loc->getTrip().begin()+i);
                    break;
                }
            }
        }

        return nullptr; // Placeholder
    }

    Location* getLocation(std::string location){
        for(int i=0;i<locations.size();i++){
            if(locations[i]->getName() == location){
                return locations [i];
            }
        }
        return nullptr;
    }

private:
    std::vector<Vehicle*> vehicles;
    std::vector<Location*> locations;
};
