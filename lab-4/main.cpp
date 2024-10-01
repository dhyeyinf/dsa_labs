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

    void addTrip(int key, Trip* trip)
    {BinaryTreeNode* temp=getBSTHead();
     BinaryTreeNode* parent=nullptr;
     while(temp){
       if(key>temp->getDepartureTime())
      { parent = 
      temp;
        temp = temp->getRightPtr();}
       else{
            parent=temp;
            temp=temp->getLeftPtr();
     }

     }
     
     temp=new BinaryTreeNode(key,trip,parent);
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
        for(int i=0;i<serviceptrs.size();i++){
            if(droplocation==serviceptrs[i]->getName()){
                return serviceptrs[i];
            }
        }
        return nullptr;
    }

    // Setter functions
    void setName(std::string location_name) {
        name = location_name;
    }

    TransportService* setServicePtr(std::string droplocation) {
        TransportService* obj=new TransportService(droplocation);
        serviceptrs.push_back(obj);
        return nullptr;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

    std::vector<TransportService*> trav(){
         return serviceptrs;
    }

    vector<Trip*> getTrip(){
        return trips;
    }

private:
    std::string name;
    std::vector<TransportService* >serviceptrs;
    std::vector<Trip*> trips;
};

class BinaryTree {
protected:
    BinaryTreeNode* root;

public:
    BinaryTree() : root(nullptr) {}

   
};

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree() {}

};

void inorder_trav(BinaryTreeNode* root,vector<BinaryTreeNode*> &result){
    
    if(!root){
        return;
    }
    inorder_trav(root->getLeftPtr(),result);
    result.push_back(root);
    inorder_trav(root->getRightPtr(),result);
    

}
int max(BinaryTreeNode* root){
    BinaryTreeNode* temp=root;
    while(temp->getRightPtr()){
        temp=temp->getRightPtr();
    }
    return temp->getDepartureTime();
}


BinaryTreeNode* deletedata(BinaryTreeNode* root,int d){
     if(!root){
        return NULL;
     }
     if(root->getDepartureTime()==d){
          //o child
          if(!root->getLeftPtr() && !root->getRightPtr()){
            delete root;
            return NULL;
          }

          //1 child
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

          //2 child
          if(root->getLeftPtr() && root->getRightPtr()){
            int n=max(root->getLeftPtr());
            root->setDepartureTime(n);
            root->setLeftPtr(deletedata(root->getLeftPtr(),n));

          }
        }
        else{
            if(root->getDepartureTime()>d){
                root->setLeftPtr(deletedata(root->getLeftPtr(),d));
            }
            else{
                root->setRightPtr(deletedata(root->getRightPtr(),d));
            }
        }
}

class TravelDesk {
public:
   Location* getLocation(std::string location){
        for(int i=0;i<locations.size();i++){
            if(locations[i]->getName()==location){
                return locations [i];
            }
        }
        return nullptr;
    }
    void add_trip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time) {
        // Implement this function to add a trip
         Vehicle* veh=nullptr;
        int c=0;
         for(int i=0;i<vehicles.size();i++){
            if(vehicle_number==vehicles[i]->getVehicleNumber()){
                veh=vehicles[i];
               c++;
               break;
            }
        }
       
        if(c==0){
               veh=new Vehicle(vehicle_number,seating_capacity);
                vehicles.push_back(veh);
        }
        Trip* trip=new Trip(veh,pick_up_location,drop_location,departure_time);
        veh->addTrip(trip);
        int j;
        c=0;
        for(j=0;j<locations.size();j++){
            if(locations[j]->getName()==pick_up_location){
                c++;
                break;

            }
        }
        if(c==0){
            Location* loc=new Location(pick_up_location);
            loc->setServicePtr(drop_location);
            loc->addTrip(trip);
            loc->getServicePtr(drop_location)->addTrip(departure_time,trip);
            locations.push_back(loc);
        }
        else{
            if(!locations[j]->getServicePtr(drop_location)){
                locations[j]->setServicePtr(drop_location);
                locations[j]->addTrip(trip);
                locations[j]->getServicePtr(drop_location)->addTrip(departure_time,trip);


            }
            else{
                locations[j]->getServicePtr(drop_location)->addTrip(departure_time,trip);
            }
        }
        
        cout<<veh->getVehicleNumber()<<endl<<getLocation(pick_up_location)->getServicePtr(drop_location)->getName()<<endl;
       

    }

    std::vector<Trip*> show_trips(std::string pick_up_location, int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range
        Location* obj=nullptr;
        vector<Trip*> result;
        vector<BinaryTreeNode*> flag;
        if(after_time>before_time){
            int t=after_time;
            after_time=before_time;
            before_time=t; 
        }
        cout<<"here0"<<endl;
        obj=getLocation(pick_up_location);
        
        if(obj!=nullptr){
          vector<TransportService*> serv=obj->trav();
          
            for(int i=0;i<serv.size();i++){
                inorder_trav(serv[i]->getBSTHead(),flag);

            }
         cout<<flag.size()<<endl;
         for(int i=0;i<flag.size();i++){
            if(flag[i]->getDepartureTime()>=after_time && flag[i]->getDepartureTime()<before_time){
                result.push_back(flag[i]->getTripNodePtr());
            }
        }
        }  
        cout<<"DEF"<<endl;
        cout<<result.size()<<endl;
        
        for(auto it:result){
            cout<<it->getDepartureTime()<<" ";
        }
        cout<<endl;
        

         return result;
    }
    std::vector<Trip*> showTripsbydestination(std::string pick_up_location, std::string destination,int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin
         Location* obj=nullptr;
        vector<Trip*> result={nullptr};
        vector<BinaryTreeNode*> flag;
        if(after_time>before_time){
            int t=after_time;
            after_time=before_time;
            before_time=t; 
        }
        
        for(int i=0;i<locations.size();i++){
            if(locations[i]->getName()==pick_up_location){
                obj=locations[i];
            }
        }
        if(obj!=nullptr){
             vector<TransportService*> serv=obj->trav();
             if(after_time<before_time){
             for(int i=0;i<serv.size();i++){
                if(serv[i]->getName()==destination){
                     inorder_trav(serv[i]->getBSTHead(),flag);
                } 

            }
        }
            for(int i=0;i<flag.size();i++){
               if(flag[i]->getDepartureTime()>=after_time && flag[i]->getDepartureTime()<before_time){
                   result.push_back(flag[i]->getTripNodePtr());
            }

        }
        }
        

         return result;

        // Placeholder
    }

    Trip* book_trip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time) {
        // Implement this function to book a trip
        Vehicle* obj=nullptr;
        Trip* trip=nullptr;
        for(int i=0;i<vehicles.size();i++){
            if(vehicles[i]->getVehicleNumber()==vehicle_number){
                obj=vehicles[i];
            }
        }
        vector<Trip*> v=obj->getTrips();
        for(int i=0;i<v.size();i++){
            if(v[i]->getPickUpLocation()==pick_up_location && v[i]->getDropLocation()==drop_location && v[i]->getDepartureTime()==departure_time){
                 trip=v[i];
                 break;
            }
        }

        if(trip->getBookedSeats()<obj->getSeatingCapacity()){
            trip->setBookedSeats(trip->getBookedSeats()+1);
            return trip;
        }

        if(trip->getBookedSeats()==obj->getSeatingCapacity()){
           Location* loc= getLocation(pick_up_location);
           TransportService* serv=loc->getServicePtr(drop_location);
           deletedata(serv->getBSTHead(),departure_time);
           
            for(int i=0;i<obj->getTrips().size();i++){
            if(obj->getTrips()[i]->getPickUpLocation()==pick_up_location && obj->getTrips()[i]->getDropLocation()==drop_location && obj->getTrips()[i]->getDepartureTime()==departure_time){
                 obj->getTrips().erase(obj->getTrips().begin()+i);
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
   

private:
    std::vector<Vehicle*> vehicles;
    std::vector<Location*> locations;
};

