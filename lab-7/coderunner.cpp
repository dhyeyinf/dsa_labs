#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cassert>
using namespace std;

class Parcel {
public:
    int time_tick;
    std::string parcel_id;
    std::string origin;
    std::string destination;
    int priority;
    bool delivered;
    std::string current_location;

    Parcel() = default;
    Parcel(int time_tick, std::string parcel_id, std::string origin, std::string destination, int priority) {
        this->time_tick = time_tick;
        this->parcel_id = parcel_id;
        this->origin = origin;
        this->destination = destination;
        this->priority = priority;
        this->delivered = false;
        this->current_location = origin;
    }
};

class MaxHeap {
public:
    std::vector<Parcel*> heap;

    MaxHeap(){
        heap.push_back(nullptr);
    }

    int parent(int i) {
        // fill in this function
        return i/2;
    }

    int left(int i) {
        // fill in this function
        return 2*i;
    }

    int right(int i) {
        // fill in this function
        return 2*i + 1;
    }

    Parcel* get_max() {
        // fill in this function
        return heap[1];
    }

    Parcel* extract_max() {
        // function that returns the max element and removes it from the heap
        Parcel* result=heap[1];
        swap(heap[1],heap[heap.size()-1]);
        heap.erase(heap.end()-1);
        max_heapify(1);
        return result;
        

    }

    void max_heapify(int i) {
        // function that maintains the max heap property
        int flag=i;

        if(left(i)<heap.size() && heap[left(i)]->priority>heap[flag]->priority){
            flag=left(i);
            
        }
        if(right(i)<heap.size() && heap[right(i)]->priority>heap[flag]->priority){
            flag=right(i);
            
        }
        if(flag!=i){
            swap(heap[i],heap[flag]);
            max_heapify(flag);
        }
        
    }

    void insert(Parcel* item) {
        // function that inserts item into the heap
       
        heap.push_back(item);
        
        int index=heap.size()-1;
        // for(int i=0;i<heap.size();i++){
        //     if(heap[i].parcel_id==item.parcel_id){
        //         index=i;
        //         break;
        //     }
        // }
        while(index>1){
            int parent=index/2;
            if(heap[parent]->priority<heap[index]->priority){
                swap(heap[parent],heap[index]);
            }
            index=parent;
        }
    }

    bool is_empty() {
        return heap.empty();
    }
};

class FreightCar {
public:
    int max_parcel_capacity;
    std::vector<Parcel*> parcels;
    std::string destination_city;
    std::string next_link;
    std::string current_location;
     std::map<string,int> visited;
    bool sealed;
    bool delivered=false;
    

    FreightCar(int max_parcel_capacity) {
        this->max_parcel_capacity = max_parcel_capacity;
        // instantiate parcels vector as empty initially
        this->parcels = {};
        this->destination_city = "";
        this->next_link = "";
        this->current_location = "";
        this->sealed = false;
    }

    void load_parcel(Parcel* parcel) {
        // load parcel
        parcels.push_back(parcel);
    }

    bool can_move() {
        // if length of parcels is equal to max_parcel_capacity return true else return false
        if(parcels.size()==max_parcel_capacity){
            return true;
        }
        return false;

    }

    void move(std::string destination) {
        // function that moves freight car to destination (link)
        current_location=destination;


    }
};

class Vertex {
public:
    std::string name;
    std::vector<FreightCar*> freight_cars;
    std::vector<Vertex*> neighbors;
    // trains_to_move is dict of destination and freight cars 
    std::map<std::string, std::vector<FreightCar*>> trains_to_move;
    int min_freight_cars_to_move;
    int max_parcel_capacity;
    std::unordered_map<std::string, MaxHeap*> parcel_destination_heaps;
    std::vector<FreightCar*> sealed_freight_cars;
    std::vector<Parcel*> all_parcels;
    Vertex() = default;
    Vertex(std::string name, int min_freight_cars_to_move, int max_parcel_capacity) {
        this->name = name;
        this->freight_cars = {};
        this->neighbors = {};
        this->trains_to_move = {};
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->max_parcel_capacity = max_parcel_capacity;
        this->parcel_destination_heaps = {};
        this->sealed_freight_cars = {};
        this->all_parcels = {};
    }

    void add_neighbor(Vertex* neighbor) {
        // add neighbor to neighbors vector
        neighbors.push_back(neighbor);
    }

    // add get neighbors function
    std::vector<Vertex*> get_neighbors() {
        return this->neighbors;
    }

    std::vector<Parcel*> get_all_current_parcels() {
        // get all parcels from all destination heaps
        return all_parcels;
    }

    void clean_unmoved_freight_cars() {
        // after time tick t, freight cars with parcels < min parcels should be deleted and parcels are to be added to heap
        // cout<<"fc size "<<freight_cars.size()<<endl;
        vector<FreightCar*> result;
        vector<Parcel*> unmoved_parcels;
        for(int i=0;i<freight_cars.size();i++){
            if(freight_cars[i]->parcels.size() < freight_cars[i]->max_parcel_capacity){
                // cout<<"rrrrrrrrr"<<endl;
                // cout<<max_parcel_capacity<<endl;
                // cout<<freight_cars[i]->parcels.size()<<endl;
                // cout<<freight_cars[i]->destination_city<<endl;
                    for(int j=0;j<freight_cars[i]->parcels.size();j++){
                        //cout<<it->parcel_id<<endl;
                        //cout<<"tttt"<<endl;
                        unmoved_parcels.push_back(freight_cars[i]->parcels[j]);
                         if(freight_cars[i]->parcels[j]==nullptr){
                            cout<<"null"<<endl;
                         }
                         //cout << "apple" << endl;
                        cout<<freight_cars[i]->parcels[j]->destination<<endl;
                        //cout << "kanjar" << endl;
                          if(parcel_destination_heaps[freight_cars[i]->parcels[j]->destination]==nullptr){
                            //cout<<"iiiiii"<<endl;
                                    parcel_destination_heaps[freight_cars[i]->parcels[j]->destination]=new MaxHeap();

                            }
                            //cout<<"uuuuuuu"<<endl;
                        parcel_destination_heaps[freight_cars[i]->parcels[j]->destination]->insert(freight_cars[i]->parcels[j]);
                        //cout<<"yyyyyyyy"<<endl;
                    }
                  // freight_cars.erase(freight_cars.begin()+i);
                 
            }
            else{
                result.push_back(freight_cars[i]);
            }

        }
        // cout << unmoved_parcels.size() << endl;
        this->freight_cars = result;
    }

    void loadParcel(Parcel *parcel) {
        // load parcel into heap
        string dest=parcel->destination;
       // cout<<"rr"<<endl;
        if(parcel_destination_heaps[dest]==nullptr){
            parcel_destination_heaps[dest]=new MaxHeap();

        }
        parcel_destination_heaps[dest]->insert(parcel);
       // cout<<"kkk"<<endl;
        all_parcels.push_back(parcel);

    }

    void loadFreightCars() {
        // load parcels into freight cars (making sure that each freight car has parcels from only one destination, and # parcels == min_parcel_capacity)
        for(auto it : parcel_destination_heaps){
          // cout<<it.second->heap.size()<<endl;
          // cout << "----------------------------------------------------------" << endl;
          

            while(it.second->heap.size()>1){
                
              int val=it.second->heap.size()-1;
              int max;
              if(val % max_parcel_capacity==0){
                max=val/max_parcel_capacity;
              }
              else{
                max=(val/max_parcel_capacity)+1;
              }
                 for(int i=0;i<max;i++){
                   FreightCar* obj= new FreightCar(max_parcel_capacity);
                   obj->current_location=this->name;
                   obj->destination_city=it.first;
                   
                   
                   while(obj->parcels.size()<obj->max_parcel_capacity && it.second->heap.size()>1){
                      // cout<<it.second->heap.size()<<"hhhe"<<endl;
                      // cout << "********************************************************" << endl;
                       obj->load_parcel(it.second->extract_max());
                       //cout<<"eeeeeee"<<endl;
                    //    for(auto par:obj->parcels){
                    //     cout<<par->parcel_id<<endl;
                    //    }
                        
                   }
                   
                   //cout<<obj->parcels.size()<<"iiiiiiiiiiiii"<<endl;
                   if(obj->parcels.size() == obj->max_parcel_capacity){
                      // cout<<"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"<<endl;
                       obj->sealed=true;
                       sealed_freight_cars.push_back(obj);
                   }
                   //cout << "#####################################################" << endl;
                   freight_cars.push_back(obj);
   
                 }


            }

        }


    }

//     void print_parcels_in_freight_cars() {
// //for (auto& [destination, heap] : this->parcel_destination_heaps) {
//             for (auto& parcel : heap.heap) {
//                 std::cout << "Parcel ID: " << parcel.parcel_id << ", Parcel origin: " << parcel.origin << ", Parcel destination: " << parcel.destination << ", Parcel priority: " << parcel.priority << std::endl;
//             }
//         }
    
};

class Graph {

public:
    std::list<Vertex*> vertices;
    std::vector<std::pair<Vertex*, Vertex*>> edges;

    void add_edge(std::string source, std::string destination, int min_freight_cars_to_move, int max_parcel_capacity) {

        // check if source and destination vertices exist
        // if they do not exist, create them
        // add edges accordingly
        Vertex* origin=nullptr;
        Vertex* dest=nullptr;
        for(auto it:vertices){
            if(it->name==source){
                origin=it;
            }
            if(it->name==destination){
                dest=it;
            }
        }
        if(!origin){
            origin=new Vertex(source,min_freight_cars_to_move,max_parcel_capacity);
            vertices.push_back(origin);
        }
        if(!dest){
            dest=new Vertex(destination,min_freight_cars_to_move,max_parcel_capacity);
            vertices.push_back(dest);
        }
        pair<Vertex*,Vertex*> p={origin,dest};
        origin->add_neighbor(dest);
        dest->add_neighbor(origin);
        edges.push_back(p);

        

    }

    void print_graph() {
        std::cout << "Printing graph, vertices: " << vertices.size() << std::endl;
        for (auto& vertex : this->vertices) {
            std::cout << "Vertex: " << vertex->name << std::endl;
            std::cout << "Neighbors: ";
            for (auto& neighbor : vertex->neighbors) {
                std::cout << neighbor->name << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::string> bfs(std::string source, std::string destination) {
        // function to return path from source to destination using bfs
        vector<string> visited;
        vector<string> result;
        Vertex* origin=nullptr;
        for(auto it:vertices){
            if(it->name==source){
                origin=it;
                
            }
        }
       // cout<<origin->name<<endl;
        if(!origin){
            return {};
        }
        visited.push_back(source);
        queue<Vertex*> q;
        q.push(origin);
        vector<pair<Vertex*,string>> path;
        path.push_back({nullptr,source});
        while(!q.empty()){
            Vertex* temp=q.front();
           // cout<<temp->name<<endl;
            vector<Vertex*> neigh=temp->get_neighbors();
            
            q.pop();
            for(auto it:neigh){
                int c=0;
               // cout<<it->name<<" ";
                for(auto a:visited){
                    if(a==it->name){
                        c=1;
                    }
                }
               // cout<<endl;
                if(c==0){
                    visited.push_back(it->name);
                    q.push(it);
                    path.push_back({temp,it->name});
                    if(it->name==destination){
                      result.push_back(it->name);
                     // cout<<it->name<<" "<<"done"<<endl;
                      pair<Vertex*,string> flag;
                      for(auto p:path){
                        if(p.second==it->name){
                            flag=p;
                        }
                      }
                     // cout<<flag.second<<" jj"<<endl;
                      Vertex* abc=flag.first;
                     // cout<<abc->name<<endl;
                      while(abc){
                        result.insert(result.begin(),abc->name);
                       // cout<<"yyyyy"<<endl;
                        for(auto b:path){
                            if(b.second==abc->name){
                               // cout<<"oooo"<<endl;
                                abc=b.first;
                                break;
                            }
                        }
                       // cout<<"uuuu"<<endl;
                      }
                      return result;
                    }
                }


            }
            


        }
       // cout<<"ended"<<endl;
        return {};
        


        }
    void dfs_help(Vertex* origin,Vertex* destination,vector<string>&result,vector<Vertex*>&visited,vector<string>&temp){
        temp.push_back(origin->name);
        if(origin==destination){
            result=temp;
            return;

        }
        vector<Vertex*> neighbour=origin->get_neighbors();

        for(auto it:neighbour){
            if(find(visited.begin(),visited.end(),it)==visited.end()){
                visited.push_back(it);
                dfs_help(it,destination,result,visited,temp);
                temp.erase(temp.end()-1);
                //visited.erase(visited.end()-1);
            }

        }
        



    }

    std::vector<std::string> dfs(std::string source, std::string destination) {
       // function to return path from source to destination using dfs
       vector<string> result;
       vector<Vertex*> visited;
       vector<string> temp;
       Vertex* origin=nullptr;
       Vertex* dest=nullptr;
       for(auto it:vertices){
        if(it->name==source){
            origin=it;
        }
        if(it->name==destination){
            dest=it;
        }
       }
       if(!origin || !dest){
        return{};
       }
       visited.push_back(origin);
       dfs_help(origin,dest,result,visited,temp);
       //cout<<origin->name<<endl;
       return result;
       
    
       }
  string getBfsLink(string origin, string destination){
          if(origin == destination)
           return "";
          vector<string> path = bfs(origin, destination);
          if(path.size() > 1)
           return path[1];
          return ""; 
       }

        string getDfsLink(string origin, string destination, FreightCar* car){
        if(origin == destination)
         return "";
        vector<string> path = dfs(origin, destination);
        path.erase(path.begin());
      
        int flag = 0;

        for(auto it : car -> visited){
            for(auto i : path){
                if(it.first == i){
                    flag = 1;
                    break;
                }
            }
            if(flag) break;
        }
        
        string next_link = "";
        if(!flag){
        if(path.size() >= 1)
          next_link = path[0];
        }
        return next_link;
    }
    void groupFreightCars() {
        // for every vertex, group freight cars by links
          for(auto &it : vertices){
            map<string,vector<FreightCar*>> bfs_bound;
            map<string,vector<FreightCar*>> dfs_bound;
            int parcel_capacity = it -> max_parcel_capacity;
            int car_capacity = it -> min_freight_cars_to_move;
            vector<FreightCar*> total_moved_cars;
            vector<FreightCar*> unmoved_cars;
            //cout << "inside group cars" << endl;
            cout << "Vertex is : " << it -> name << endl;
            cout << it-> freight_cars.size() << endl;
            //cout << "Parcels : " << endl;
            // for(auto k : it -> freight_cars){
            //     for(auto pa : k -> parcels){
            //         cout << pa -> parcel_id << " ";
            //     }
            //     cout << endl;
            // }
            //checking for the bfs
            cout << "before1" << endl;
            for(auto car : it -> freight_cars){
                 if(car -> can_move() == true){
                  string link = getBfsLink(car -> current_location, car -> destination_city);
                  if(link != ""){
                   bfs_bound[getBfsLink(car -> current_location, car -> destination_city)].push_back(car);
                  }
                  //car -> sealed = true;
                  //car -> next_link = getBfsLink(car -> current_location, car -> destination_city);
                 }
            }
            cout << "before2" << endl;
            for(auto bfs : bfs_bound){
                if(bfs.second.size() >= car_capacity){
                    for(auto push_vec : bfs.second){
                         push_vec -> next_link = bfs.first;
                         it -> trains_to_move[bfs.first].push_back(push_vec);
                         total_moved_cars.push_back(push_vec);
                    }
                    
                    // for(auto k : bfs.second){
                    //     k -> next_link = bfs.first;
                    // }
                }
                else{
                    for(auto stranded_car : bfs.second){
                        unmoved_cars.push_back(stranded_car);
                    }
                }
            }
            cout << "before3" << endl;
            //checking for the dfs
            for(auto k : unmoved_cars){
                cout << "after3" << endl;
                if(k -> can_move() == true){
                 cout << "after33" << endl;
                 string dfsLink = getDfsLink(k -> current_location, k -> destination_city, k);
                 //k -> sealed = true;
                 //k -> next_link = dfsLink;
                 if(dfsLink != ""){
                    dfs_bound[dfsLink].push_back(k);
                 }
                 cout << "crazy" << endl;
                 
                }
            }

            cout << "before4" << endl;
            vector<FreightCar*> finally_unmoved_cars;
            for(auto dfs: dfs_bound){
                if(dfs.second.size() >= car_capacity){
                    for(auto push_vec : dfs.second){
                         push_vec -> next_link = dfs.first;
                         it -> trains_to_move[dfs.first].push_back(push_vec);
                         total_moved_cars.push_back(push_vec);
                    }
                    // it -> trains_to_move[dfs.first] = dfs.second;
                    // for(auto k : dfs.second){
                    //     k -> next_link = dfs.first;
                    // }

                }
                else{
                    for(auto stranded_car : dfs.second){
                        finally_unmoved_cars.push_back(stranded_car);
                    }
                }
            }
            int i = 0;
            //edit for removing the cars which are going to move
            cout << "before5" << endl;
            cout << "Finally MOVED Cars : " << total_moved_cars.size() << endl;
            //if(finally_unmoved_cars.size() > 0){
            
            // for(auto car : it -> freight_cars){
            //     cout << "AFTER5" << endl;
            //     if(carPresent(total_moved_cars, car) == true)
            //      {
            //        cout << "GOING TO DELETE ----------------- " << endl;
                   
            //        it -> freight_cars.erase(it -> freight_cars.begin() + i);
            //      }
            //      cout << "SIZE OF FREIGHT CARS : " << it -> freight_cars.size() << endl;
            //      i++;
            // }
            //}

            // for (auto i = it->freight_cars.begin(); i != it->freight_cars.end();) {
            //    cout << "AFTER5" << endl;
            //    if (carPresent(total_moved_cars, *i)) {
            //        cout << "GOING TO DELETE ----------------- " << endl;
            //        i = it->freight_cars.erase(i);
            //                                      // erasing and updating the iterator
            //    } else {
            //        ++i; // move to the next element if not erased
            //    }
            //    cout << "SIZE OF FREIGHT CARS: " << it->freight_cars.size() << endl;
            // }


            cout << "i am leaving this" << endl;

           cout << "VERTEX IS " << it -> name << " " << "NO OF FREIGHT CARS TRAINS " << it -> freight_cars.size() << endl;

        }

        //moveTrains();

        cout << "$$$$$$$$$$$$$$$$$$$$ FINNALY LEFT GROUP F CARS ####################" << endl;


    }

    void moveTrains() {
        // for every vertex, move freight cars to next link
        vector<pair<FreightCar* ,string>> abc;
        for(auto it:vertices){
            //cout<<it->name<<endl;
            cout<<it->freight_cars.size()<<"rrrr"<<endl;
            for(auto mpp:it->trains_to_move){
               // cout<<"yes"<<endl;
               // cout<<it->freight_cars.size()<<endl;
                for( auto fc:mpp.second){
                    //cout<<fc->next_link<<endl;
                    
                    fc->move(fc->next_link);
                    fc->next_link="";
                    // vector<FreightCar*> temp;
                    // for(int i=0;i<it->freight_cars.size();i++){
                    //     if(it->freight_cars[i]!=fc){
                    //         //it->freight_cars.erase(it->freight_cars.begin()+i);
                    //         cout<<"aaa"<<endl;
                    //         temp.push_back(fc);
                    //     }
                    // }
                    if(find(it->freight_cars.begin(),it->freight_cars.end(),fc)!=it->freight_cars.end()){
                        it->freight_cars.erase(find(it->freight_cars.begin(),it->freight_cars.end(),fc));
                    }
                   
                    // it->freight_cars=temp;
                    //  cout<<it->freight_cars.size()<<"oooo"<<endl;
                    // vector<FreightCar*> temp1;
                    // for(int i=0;i<it->sealed_freight_cars.size();i++){
                    //     if(it->sealed_freight_cars[i]!=fc){
                    //         //it->sealed_freight_cars.erase(it->freight_cars.begin()+i);
                    //          temp1.push_back(fc);
                    //     }

                    // }
                    // it->sealed_freight_cars=temp1;
                      if(find(it->sealed_freight_cars.begin(),it->sealed_freight_cars.end(),fc)!=it->sealed_freight_cars.end()){
                        it->sealed_freight_cars.erase(find(it->sealed_freight_cars.begin(),it->sealed_freight_cars.end(),fc));
                    }
                    //cout<<"done"<<endl;
                   // cout<<fc->current_location<<endl;
                    if(fc->current_location==fc->destination_city){
                        fc->delivered=true;
                    }
                       // cout<<"uu"<<endl;
                    for(auto ver:vertices){
                        if(ver->name==mpp.first){
                            //cout<<ver->name<<endl;
                        ver->freight_cars.push_back(fc);
                        ver->sealed_freight_cars.push_back(fc);
                        }
                    }
                    
                    //cout<<"ppppppp"<<endl;
                    cout<<fc->parcels.size()<<endl;
                    //abc.push_back({fc,fc->current_location});

                    for(auto par:fc->parcels){
                    //     vector<Parcel*> abc;
                    //    // cout<<"lllllll"<<endl;
                    //     for(int i=0;i<it->all_parcels.size();i++){
                    //         if(it->all_parcels[i]!=par){
                    //            // it->all_parcels.erase(it->all_parcels.begin()+i);
                    //            abc.push_back(par);
                    //         }
                    //     }
                    //     it->all_parcels=abc;
                    if(find(it->all_parcels.begin(),it->all_parcels.end(),par)!=it->all_parcels.end()){
                        it->all_parcels.erase(find(it->all_parcels.begin(),it->all_parcels.end(),par));
                    }
                        par->current_location=mpp.first;
                       // cout<<par->current_location<<endl;
                        if(par->current_location==par->destination){
                            par->delivered=true;
                        }
                       
                        for(auto ver:vertices){
                        if(ver->name==mpp.first){
                        ver->all_parcels.push_back(par);
                        
                        }
                    }
                        }
                       // cout<<"kkk"<<endl;


                    


                }
            }
            it->trains_to_move.clear();
        }
        // for(auto it:abc){
        //     for(auto par:it.first->parcels){
        //         cout<<"aa"<<endl;
        //         cout<<par->parcel_id<<endl;

        //     }
        // }
        


    }



};
string g;
string p;

class PRC {
public:
    Graph graph;
    std::vector<FreightCar*> freight_cars;
    std::map<std::string, Parcel*> parcels;
    std::map<int, std::vector<Parcel*>> parcels_with_time_tick;
    int max_parcel_capacity;
    int min_freight_cars_to_move;
    int time_tick;
    std::map<std::string, std::string> old_state;
    std::map<std::string, std::string> new_state;
    int max_time_tick;

    PRC(int max_parcel_capacity, int min_freight_cars_to_move) {
        this->max_parcel_capacity = max_parcel_capacity;
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->time_tick = 1;
        this->max_time_tick = 100;
        this->freight_cars = {};
        this->parcels = {};
        this->parcels_with_time_tick = {};
        this->old_state = {};
        this->new_state = {};

    }

    void create_graph(std::string graph_file_name) {

        // read graph.txt file and create graph
        g=graph_file_name;
        ifstream in(graph_file_name);
        if(!in.is_open()){
            return;
        }
        string line;
        while(getline(in,line)){
            stringstream ss(line);
            string place1;
            string place2;
            getline(ss,place1,' ');
            getline(ss,place2,' ');
            graph.add_edge(place1,place2,min_freight_cars_to_move,max_parcel_capacity);


        }




    }

    void process_parcels(std::string parcels_file_name){
        // read parcels.txt file and create parcels 
        p=parcels_file_name;
        ifstream in(parcels_file_name);
        if(!in.is_open()){
            return;
        }
        string line;
        string word;
        int time;
        string id;
        string origin;
        string destination;
        int priority;
        while(getline(in,line)){
        stringstream ss(line);
        getline(ss,word,' ');
        time=stoi(word);

        getline(ss,id,' ');
        getline(ss,origin,' ');
        getline(ss,destination,' ');

        getline(ss,word,' ');
        priority=stoi(word);
        Parcel* obj=new Parcel(time,id,origin,destination,priority);
        obj->current_location=origin;
        parcels.insert({id,obj});
        parcels_with_time_tick[time].push_back(obj);

        

        }
       

        
    }

    // function to return bookings at a particular time tick at a particular vertex
    std::vector<Parcel*> get_bookings(int time_tick, std::string vertex) {
        Vertex* obj=nullptr;
        list<Vertex*> vertices=graph.vertices;
        for(auto it:vertices){
            if(it->name==vertex){
                obj=it;
            }
        }
        vector<Parcel*> abc=obj->all_parcels;
        vector<Parcel*> result;
        for(int i=0;i<abc.size();i++){
            if(abc[i]->time_tick==time_tick){
                result.push_back(abc[i]);
            }
        }
        return result;

    }

    std::map<std::string, std::string> get_state() {
        std::map<std::string, std::string> state;
        // from this.parcels
        // should return the dict of parcel_id and current_location
        for(auto it:parcels){
            state[it.second->parcel_id]=it.second->current_location;
        }

        return state;
    }

    // run simulation function, takes run_till_time_tick as argument
    // if run_till_time_tick is not provided then run simulation till max_time_tick

    void run_simulation(int run_till_time_tick = -1) {

        // function to run simulation 
        if(run_till_time_tick==-1 || run_till_time_tick>max_time_tick){
            run_till_time_tick=max_time_tick;
        }
        
        while(time_tick<run_till_time_tick){
          // cout<<tt<<tt<<tt<<tt<<tt<<tt<<tt<<tt<<tt<<tt<<tt<<tt<<endl;
            old_state=this->get_state();
            for(auto it:parcels_with_time_tick){
                
                //cout<<it.first<<endl;
                if(it.first==time_tick){
                  //  cout<<"here"<<endl;
                    for(auto parcel:it.second){
                       // cout<<parcel->parcel_id<<endl;
                        if(parcel->origin==parcel->current_location){
                           // cout<<"kkkkkkkkkkkkkkkkk"<<endl;
                            for(auto v:graph.vertices){
                               
                                if(v->name==parcel->origin){
                                  //  cout<<v->name<<endl;
                                    v->loadParcel(parcel);
                                   // cout<<"yyyyyyyyy"<<endl;
                                }
                            }
                        }
                    }
                   // cout<<"lll"<<endl;
                    break;

                }
            }
            for(auto it:graph.vertices){
              //  cout<<it->name<<endl;
              //cout<<it->name<<endl;
                it->loadFreightCars();
               // cout<<it->name<<" done"<<endl;
            }
            cout<<"yyyyyyy"<<endl;
            for(auto it:graph.vertices){
                                
               // cout<<it->name<<endl;
                it->clean_unmoved_freight_cars();
               // cout<<it->name<<" done"<<endl;

            }
            cout<<"ppp"<<endl;
            graph.groupFreightCars();
            cout<<"kkkkkkkkkkkkkkkkkkkk"<<endl;
            time_tick++;
            graph.moveTrains();
            
            new_state=this->get_state();
            cout<<"rrr"<<endl;
            if(this->convergence_check()==true){
                break;
            }

        }
        

    }

    bool convergence_check(){
        // function to check convergence between old_state and new_state
        for(auto it:parcels){
            if(old_state[it.second->parcel_id]!=new_state[it.second->parcel_id]){
                return false;
            }
        }
        return true;
    }

     bool all_parcels_delivered() {
        // function to check if all parcels are delivered
        // return true if all parcels are delivered else return false
        for(auto it:parcels){
            if(it.second->delivered==false){
                return false;
            }

        }
        return true;
    }

    std::vector<std::string> get_stranded_parcels() {
        // return parcel_ids of stranded parcels
        vector<string> result;
        for(auto it:parcels){
            if(it.second->delivered==false){
                result.push_back(it.second->parcel_id);
            }
        }
        return result;
    }

    std::vector<std::string> get_delivered_parcels() {
        // return parcel_ids of delivered parcels
          vector<string> result;
        for(auto it:parcels){
            if(it.second->delivered==true){
                result.push_back(it.second->parcel_id);
            }
        }
        return result;
    }

    // get status of all parcels at time tick t (status = id, current location, delivered/not delivered)
    std::vector<std::string> get_status_of_all_parcels(int t) {
        //  std::string status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered) + "\n" ;
        // return the status of all parcels at time tick t as a vector of strings (each string formatted as above)
       PRC obj(this->max_parcel_capacity,this->min_freight_cars_to_move);
       obj.create_graph(g);
       obj.process_parcels(p);
       obj.run_simulation(t);
       vector<string> result;
       for(auto par:obj.parcels){
        result.push_back(par.second->parcel_id+" "+par.second->current_location+" "+to_string(par.second->delivered));


       }
       return result;
    }

    // get status of parcel_id at time tick t (status = id, current location, delivered/not delivered)
    std::string get_status_of_parcel(std::string parcel_id, int t) {
        // status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered);
        // return status of one parcel at time tick t as a string (formatted as above)
           PRC obj(this->max_parcel_capacity,this->min_freight_cars_to_move);
       obj.create_graph(g);
       obj.process_parcels(p);
       obj.run_simulation(t);
       Parcel* par=obj.parcels[parcel_id];
       return  par->parcel_id+" "+par->current_location+" "+to_string(par->delivered);

    }

    // get parcels delivered up to time tick t
    std::vector<std::string> get_parcels_delivered_up_to_time_tick(int t) {
        // return list of parcel_ids of parcels delivered up to time tick t
         PRC obj(this->max_parcel_capacity,this->min_freight_cars_to_move);
       obj.create_graph(g);
       obj.process_parcels(p);
       obj.run_simulation(t);
       vector<string> result;
       for(auto par:obj.parcels){
        if(par.second->delivered==true){
        result.push_back(par.second->parcel_id);
        }

       }
       return result;
    }

};


// void test_case_1() {
//     // create a PRC object
//     PRC prc(2, 2);
//     // create a graph
//     prc.create_graph("samples/2/graph.txt");
//     prc.process_parcels("samples/2/bookings.txt");
//     prc.run_simulation(3);
//     assert(prc.all_parcels_delivered() == false);
//     assert(prc.get_stranded_parcels().find("P2Ludhiana4") != std::string::npos);

//     prc.run_simulation(4);
//     std::vector<std::string> stranded_parcels = prc.get_stranded_parcels();
//     assert(std::find(stranded_parcels.begin(), stranded_parcels.end(), "P2Ludhiana4") != stranded_parcels.end());
//     // delete the prc object
//     prc.~PRC();
// }

int main() {

    PRC prc = PRC(2, 2);
    prc.create_graph("graph.txt");
    //prc.graph.print_graph();
    cout<<"here"<<endl;
    vector<string> abc=prc.graph.dfs("Mumbai","Ahmedabad");
    vector<string> pqr=prc.graph.bfs("Mumbai","Ahmedabad");
    cout<<"ee"<<endl;
    cout<<abc.size()<<endl;
    for(auto it: abc){
      
        cout<<it<<" ";
       
      
    }
    cout<<endl;
    for(auto it:pqr){
        cout<<it<<" "<<endl;
    }
    cout<<endl;
    cout<<"ended"<<endl;
    cout<<prc.graph.edges.size()<<endl;
    // prc.process_parcels();
    // prc.run_simulation(3);
    prc.process_parcels("booking.txt");
    cout<<"process_parcels done"<<endl;
   // prc.run_simulation(3);
    prc.run_simulation(4);
    cout<<"running:"<<endl;
    cout<<prc.time_tick<<endl;
   vector<string> sp=prc.get_stranded_parcels();
    cout<<"here"<<endl;
    int c=0;
    
    for(auto it:prc.graph.vertices){
        //cout<<"lll"<<endl;
        cout<<it->name<<":"<<it->freight_cars.size()<<endl;
        if(it->name=="AHMEDABAD"){
            cout<<"aaa"<<endl;
            if(it->all_parcels.size()==0){
                cout<<"wrong"<<endl;
            }
            for(auto par:it->all_parcels){
                cout<<par->parcel_id<<endl;

            }
        }
    }
    for(auto it:prc.parcels){
        cout<<it.first<<" "<<it.second->delivered<<endl;
    }
    for(auto it:sp){
        c++;
        cout<<it<<" ";
    }
    cout<<c<<endl;
    cout<<prc.parcels.size()<<endl;

    return 0;
}
