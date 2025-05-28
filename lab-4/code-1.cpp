#include <iostream>
#include <vector>
#include <map>
#include<queue>

#include<utility>
using namespace std;
class Vehicle;
class BinaryTreeNode;
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
          BinaryTreeNode * temp= getBSTHead();
        BinaryTreeNode * parent=nullptr;
        while(temp!=nullptr)
        {

            if(key>temp->getDepartureTime())
            {
                parent=temp;
                 temp=temp->getRightPtr();
            }
            else{
                parent=temp;
                temp=temp->getLeftPtr();
            }
        }
        temp= new BinaryTreeNode(key,trip,parent);
        if(getBSTHead()==nullptr)
        setBSTHead(temp);
       
        if(parent!=nullptr){
        if(parent->getDepartureTime()>=temp->getDepartureTime())
        {
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


class Location {
public:
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    TransportService* getServicePtr(std::string droplocation) const {

        TransportService * temp=nullptr;
        for(int i=0;i<serviceptrs.size();i++)
        {
            if(serviceptrs[i]->getName()==droplocation)
            temp=serviceptrs[i];
        }

        return temp; 
    }

    // Setter functions
    void setName(std::string location_name) {
        name = location_name;
    }

    TransportService* setServicePtr(std::string droplocation) {
        return nullptr;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }
    void addService(TransportService* service)
    {
        serviceptrs.push_back(service);
    }
    vector<TransportService*> getvect(){
        return serviceptrs;
    }
    vector<Trip*> gettrips(){
        return trips;
    }

private:
    std::string name;
    std::vector<TransportService* >serviceptrs;
    std::vector<Trip*> trips;
};
int Get_Height(BinaryTreeNode* root)
{
    if(root==nullptr)
    return 0;
    else
    return 1+max(Get_Height(root->getLeftPtr()),Get_Height(root->getRightPtr()));
}
int Get_Number_Nodes(BinaryTreeNode* root)
{
    if(root==nullptr)
    return  0;
    else
    return 1+(Get_Number_Nodes(root->getLeftPtr()) + Get_Number_Nodes(root->getRightPtr()));
}

class BinaryTree {
protected:
    BinaryTreeNode* root;

public:
    BinaryTree() : root(nullptr) {}
    void setroot(BinaryTreeNode * root)
    {
        this->root=root;
    }
    BinaryTreeNode* getroot(){
        return this->root;
    }

    int getHeight() const {
        // Implement this function to return the height of the tree
        int k= Get_Height(this->root);
        
        return k; // Placeholder
    }

    int getNumberOfNodes() const {
        // Implement this function to return the number of nodes in the tree
        int k= Get_Number_Nodes(this->root);
        return k; // Placeholder
    }
};


class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree() {}
    BinaryTreeNode* getmin (BinaryTreeNode*temp) const
    {
        while(temp->getLeftPtr()!=nullptr)
        {
            temp=temp->getLeftPtr();
        }
        return temp; 
    }
    BinaryTreeNode* getmax (BinaryTreeNode*temp) const
    {
        while(temp->getRightPtr()!=nullptr)
        {
            temp=temp->getRightPtr();
        }
        return temp;
    }

    BinaryTreeNode* getElementWithMinimumKey() const {
        // Implement this function to return the element with the minimum key
      BinaryTreeNode* temp= this->root;
      temp=getmin(temp);
      return temp;
      
        
    }

    BinaryTreeNode* getElementWithMaximumKey() const {
        // Implement this function to return the element with the maximum key
         BinaryTreeNode* temp= this->root;
         temp=getmax(temp);
        
        return temp;
        //holder
    }
    BinaryTreeNode* GetSuc(BinaryTreeNode* root,int key) const{
    BinaryTreeNode* req=nullptr;
    while(root!=nullptr)
    if(root->getDepartureTime()==key)
    {   
            if(root->getRightPtr()){
            req=getmin(root->getRightPtr());
            break; 

            }
    }
    else if(key>root->getDepartureTime())
    {
        root=root->getRightPtr();
    }
    else{
            req=root;
            root=root->getLeftPtr();
    }
    return req;

}
BinaryTreeNode* GetPred(BinaryTreeNode* root,int key) const{
    BinaryTreeNode* req= nullptr;
    while(root!=nullptr)
    {
        if(root->getDepartureTime()==key)
        {
           if(root->getLeftPtr())
           {
            req = getmax(root->getLeftPtr());
            break;
           } 
        }
        else if(key<root->getDepartureTime())
        {
            root=root->getLeftPtr();
        }
        else{
            req=root;
            root=root->getRightPtr();
        }
    }
}

    BinaryTreeNode* searchNodeWithKey(int key) const {
        // Implement this function to search for a node with the given key or the next larger key
        BinaryTreeNode*temp=this->root;
        while(temp!=nullptr&&temp->getDepartureTime()!=key)
        {
                if(key>temp->getDepartureTime())
                {
                    temp=temp->getRightPtr();
                }
                else{
                    temp=temp->getLeftPtr();
                }
        }
        return temp; // Placeholder
    }

    BinaryTreeNode* getSuccessorNode(BinaryTreeNode*& node) const {
        // Implement this function to return the successor node of the given node
        BinaryTreeNode*ans= GetSuc(node,node->getDepartureTime()-1);
        return ans; // Placeholder
    }

    BinaryTreeNode* getSuccessorNodeByKey(int key) const {
        // Implement this function to return the successor node by key
        BinaryTreeNode*ans = GetSuc(this->root,key);
        return ans; 
         // Placeholder
    }


    BinaryTreeNode* getPredecessorNode(BinaryTreeNode* node) const {
        // Implement this function to return the predecessor node of the given node
        BinaryTreeNode*ans= GetPred(node,node->getDepartureTime());
        return ans; // Placeholder
    }

    BinaryTreeNode* getPredecessorNodeByKey(int key) const {
        // Implement this function to return the predecessor node by key
        BinaryTreeNode*ans = GetPred(this->root,key);
        return ans;  // Placeholder
    }
};
BinaryTreeNode * DeletFromBst(BinaryTreeNode* root,int d)
{
    if(root==nullptr)
    {
        return root;
    }
    if(root->getDepartureTime()==d)
    {
        // 0 child
        if(root->getRightPtr()==nullptr && root->getLeftPtr() == nullptr)
        {
                delete root;
                return nullptr;
        }
        else if(root->getLeftPtr()!=nullptr&& root ->getRightPtr()==nullptr)
        {
            BinaryTreeNode* temp= root->getLeftPtr();
            delete root;
            return temp;
        }
        else if(root->getLeftPtr()==nullptr&& root ->getRightPtr()!=nullptr)
        {
           BinaryTreeNode * temp= root->getRightPtr();
            delete root;
            return temp;
        }
        else{
            BinarySearchTree* tile;
            BinaryTreeNode* xet=root->getRightPtr();
            int val=(tile->getSuccessorNode(xet))->getDepartureTime();
            root->setDepartureTime(val);
            root->setRightPtr(DeletFromBst(root->getRightPtr(),val));
            return root;
        }
    }
    else if(root->getDepartureTime()>d)
    {
        root->setLeftPtr( DeletFromBst(root->getLeftPtr(),d));
    }
    else{
        root->setRightPtr( DeletFromBst(root->getRightPtr(),d));
    }
}

class TravelDesk {
public:
Vehicle* getVehicle(std::string vehicle){
        Vehicle * temp=nullptr;
        for(int i=0;i<vehicles.size();i++)
        {
            if(vehicles[i]->getVehicleNumber()==vehicle)
            temp=vehicles[i];
        }
        return temp;
    }

    void add_trip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time) {
        // Implement this function to add a trip
        
        int flag=0;
        Vehicle* vehicle=nullptr;
        Location * location=nullptr;
        for(int i=0;i<vehicles.size();i++)
        {
            
            if(vehicles[i]->getVehicleNumber()==vehicle_number)
            {
              vehicle =vehicles[i];
                flag=1;
                break;
            }
        }
        if(flag==0){
             vehicle = new Vehicle(vehicle_number,seating_capacity);
            vehicles.push_back(vehicle);
            
            
        }
        flag=0;
        for(int i=0;i<locations.size();i++)
        {
            if(locations[i]->getName()==pick_up_location)
            {
                 location=locations[i];
                flag=1;
                
                break;
            }
        }
        if(flag==0){
           
            location = new Location(pick_up_location);
            
            
            //service->setLocationPtr(location);
            locations.push_back(location);
            
        }
         TransportService* service = location->getServicePtr(drop_location);
             if(service==nullptr)
             {
                service=new TransportService(drop_location);
                location->addService(service);
             }
 
        Trip * trip = new Trip(vehicle,pick_up_location,drop_location,departure_time);
            vehicle->addTrip(trip);
            location->addTrip(trip); 
            location->getServicePtr(drop_location)->addTrip(departure_time,trip);
            
    }
    Location* getLocation(std::string location){
        Location * temp=nullptr;
        for(int i=0;i<locations.size();i++)
        {
            if(locations[i]->getName()==location)
            temp=locations[i];
        }
        return temp;
    }


    std::vector<Trip*> show_trips(std::string pick_up_location, int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range
        if(before_time<after_time)
        swap(before_time,after_time);
        vector <Trip*> result;
        Location * location = getLocation(pick_up_location);
        if(location==nullptr)
        return result;
        vector<TransportService*> v=location->getvect();
        for(int i=0;i<v.size();i++)
        {
            BinaryTreeNode* temp=v[i]->getBSTHead();
            BinarySearchTree ob;
            ob.setroot(v[i]->getBSTHead());
            int k=after_time-1;
            temp=ob.getSuccessorNodeByKey( k);
            while(temp){
                if(temp->getDepartureTime()<before_time)
                result.push_back(temp->getTripNodePtr());
                 k=temp->getDepartureTime()+1;
                                 

                temp=ob.getSuccessorNodeByKey( k);   

            }

        }
        return result;
        
         // Placeholder
    }
    
    std::vector<Trip*> showTripsbydestination(std::string pick_up_location, std::string destination,int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin
        if(before_time<after_time)
        swap(before_time,after_time);
        vector <Trip*> result;
        Location * location = getLocation(pick_up_location);
        TransportService*service= location->getServicePtr(destination);
       BinaryTreeNode* temp=service->getBSTHead();
         BinarySearchTree ob;
            ob.setroot(service->getBSTHead());
            int k=after_time-1;
            temp=ob.getSuccessorNodeByKey( k);
            while(temp){
                if(temp->getDepartureTime()<before_time)
                result.push_back(temp->getTripNodePtr());
                 k=temp->getDepartureTime()+1;
                                 

                temp=ob.getSuccessorNodeByKey( k);
                
                
                
               

            }
         
        return result; // Placeholder
    }

    Trip* book_trip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time) {
        // Implement this function to book a trip
        Vehicle* vehicle=getVehicle(vehicle_number);
        // if(vehicle==nullptr)
        // return;
        int index;
        Trip* temptrip=nullptr;
        vector<Trip*> v=vehicle->getTrips();
        for(int i=0;i<v.size();i++)
        {
            if(v[i]->getPickUpLocation()==pick_up_location&& v[i]->getDropLocation() == drop_location && v[i]->getDepartureTime()==departure_time )
           { temptrip=v[i];
           index=i;
                break;
           }
        }
        if(temptrip->getBookedSeats()<vehicle->getSeatingCapacity())
        {temptrip->setBookedSeats(temptrip->getBookedSeats()+1);
            return temptrip;
        }
       if(temptrip->getBookedSeats()==vehicle->getSeatingCapacity())
       {
         vehicle->getTrips().erase(vehicle->getTrips().begin()+index);
            Location* location=getLocation(pick_up_location);
            vector<Trip*> ob=location->gettrips();
            for(int i=0;i<ob.size();i++)
            {
            if(ob[i]->getPickUpLocation()==pick_up_location&& ob[i]->getDropLocation() == drop_location && ob[i]->getDepartureTime()==departure_time )
                    location->gettrips().erase(location->gettrips().begin()+i);
                    break;
            }
            TransportService*serv=location->getServicePtr(drop_location);
            BinaryTreeNode* root=serv->getBSTHead();
            root=DeletFromBst(root,departure_time);

            // if(serv==nullptr)
            // return;

       }

       // Placeholder
    }
    

private:
    std::vector<Vehicle*> vehicles;
    std::vector<Location*> locations;
};
