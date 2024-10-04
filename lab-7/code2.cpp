#include <bits/stdc++.h>
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
bool comparator(Parcel* &a, Parcel* &b){
    if(a < b)
     return true;
     return false;
}
class MaxHeap {
public:
    MaxHeap() = default;
    std::vector<Parcel*> heap;
    int size = 0;
public:    
    int parent(int i) {
        // fill in this function
        return i / 2;
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
        return heap[0];
    }
    Parcel* extract_max() {
        // function that returns the max element and removes it from the heap
        Parcel *parcel = heap[0];
        // cout << "I am in EXTRACT MAX : ";
        // cout << parcel -> parcel_id << endl;
        heap.erase(heap.begin(), heap.begin() + 1);
        sort(heap.begin(), heap.end(), comparator);
        return parcel;
    }
    
    // void deleteNode(int curr){
    //     int index = size;
    //     //int t = heap[curr];
    //     heap[curr] = heap[index];
    //     heap.pop_back();
    //     size = size - 1;
    //     while(2 * curr <= size){
    //         int l = 2 * curr;
    //         int r = 2 * curr + 1;
    //         if(max(heap[l] -> priority,heap[r] -> priority) > heap[curr] -> priority){
    //             int ind = (max(heap[l] -> priority,heap[r] -> priority) == heap[l] -> priority) ? l : r;
    //             swap(heap[curr],heap[ind]);
    //             curr = (max(heap[l] -> priority,heap[r] -> priority) == heap[l] -> priority) ? l : r;
    //         }
    //         else
    //          return;
    //     }

    // }
    // void heapify(int n,int i){
    //     int largest = i;
    //     int l = left(i);
    //     int r = right(i);

    //     if(l <= n && heap[largest] -> priority < heap[l] -> priority)
    //      largest = l;
    //     if(r <= n && heap[largest] -> priority < heap[r] -> priority)
    //      largest = r;

    //     if(largest != i)
    //     {
    //         swap(heap[largest],heap[i]);
    //         heapify(n,largest);
    //     }  

    // }
    // void max_heapify(int i) {
    //     // function that maintains the max heap property
    //     int n = size;
    //     for(int i = n / 2;i>0;i--){
    //         heapify(n,i);
    //     }

    // }

    void insert(Parcel *item) {
        // function that inserts item into the heap
        //cout << "coming in insert" << endl;
        
        //size = size + 1;
        //int index = size;
        //cout << "size of heap in insert : " << heap.size() << endl;
        //heap[index] = item;
        heap.push_back(item);
        // while(index > 1){
        //     int parent_index = parent(index);
        //     if(heap[index] -> priority > heap[parent_index] -> priority){
        //         swap(heap[index],heap[parent_index]);
        //         index = parent_index;
        //     }
        //     else 
        //      return;
        // }
        sort(heap.begin(),heap.end(), comparator);
        // if(size == 0)
        //  {
        //     heap.insert(heap.begin(), nullptr);
        //     size = size + 1;
        //     extract_max();
        //  }

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

    FreightCar(int max_parcel_capacity) {
        this->max_parcel_capacity = max_parcel_capacity;
        // instantiate parcels vector as empty initially
        this->parcels = {};
        this->destination_city = "";
        this->next_link = "";
        this->current_location = "";
        this->sealed = false;
    }

    void load_parcel(Parcel *parcel) {
        // load parcel
        parcels.push_back(parcel);
    }

    bool can_move() {
        // if length of parcels is equal to max_parcel_capacity return true else return false
        if(parcels.size() == max_parcel_capacity)
         return true;
        return false; 
    }

    void move(std::string destination) {
        // function that moves freight car to destination (link)
        current_location = destination;
    }
};

class Vertex {
public:
    std::string name;
    int size_of_heap = 0;
    std::vector<FreightCar*> freight_cars;
    std::vector<Vertex*> neighbors;
    // trains_to_move is dict of destination and freight cars 
    std::map<std::string, std::vector<FreightCar*>> trains_to_move;
    int min_freight_cars_to_move;
    int max_parcel_capacity;
    std::unordered_map<std::string, MaxHeap> parcel_destination_heaps;
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
    string get_name(){
        return this -> name;
    }
    void add_neighbor(Vertex* neighbor) {
        // add neighbor to neighbors vector
        //cout << "have entered add_neighbour" << endl;
        //cout << "neighbour name" << endl;
        //cout << neighbor -> name << " " << (neighbor -> name).size() << endl;
        (this -> neighbors).push_back(neighbor);
        vector<Vertex*> n = this -> get_neighbors();
        //cout << "Printing in add_neighbour : " << n[0] -> name << endl;
    }

    // add get neighbors function
    std::vector<Vertex*> get_neighbors() {
        //cout << "Neighbours are :" << neighbors.size() << endl;
        //cout << "Printing in get_neighbours : " <<  neighbors[0] -> name << endl;
        // for(auto it : neighbors){
        //     cout << it -> name << endl;
        // }
        return neighbors;
    }

    std::vector<Parcel*> get_all_current_parcels() {
        // get all parcels from all destination heaps
        vector<Parcel*> parcels;
        for(auto it : parcel_destination_heaps){
            for(auto i : it.second.heap){
                parcels.push_back(i);
            }
        }
        return parcels;
    }

    void clean_unmoved_freight_cars() {
        // after time tick t, freight cars with parcels < min parcels should be deleted and parcels are to be added to heap
    }

    void loadParcel(Parcel *parcel) {
        // load parcel into heap
        //cout << "inside load parcel" << endl;
        //cout << parcel -> time_tick << " " << parcel -> parcel_id << endl;
        
        parcel_destination_heaps[parcel -> destination].insert(parcel);
        // cout << "Size of heap : " << parcel_destination_heaps[parcel -> destination].heap.size() << endl;
        // cout << "Max priioirty element : " << parcel_destination_heaps[parcel -> destination].get_max() -> parcel_id << parcel_destination_heaps[parcel -> destination].get_max() -> priority << endl;
        // for(auto it : parcel_destination_heaps[parcel -> destination].heap){
            
        //      cout << it -> parcel_id << " " << endl;
        // }
        //cout << "inserted in heap" << endl;
        all_parcels.push_back(parcel);
        //cout << "successfull inserted" << endl;
        //loadFreightCars();
        // for(auto it : parcel_destination_heaps){
        //     if(it.second.heap.size() == 5){
                
        //         loadFreightCars();
        //     }
        // }

    }

    void loadFreightCars() {
        // load parcels into freight cars (making sure that each freight car has parcels from only one destination, and # parcels == min_parcel_capacity)
        //cout << "Size of PARCEL DEST HEAPs" << parcel_destination_heaps.size() << endl;
        for(auto &it : parcel_destination_heaps){
            //cout << "i am ready to go" << endl;
            //cout << "Heap"
            //cout << "Size of PARCEL HEAPSSSS : " << it.second.heap.size() << endl;
            while(it.second.heap.size() >= max_parcel_capacity){
            //if(it.second.heap.size() >= 5){
                //cout << "i am good now" << endl;
                FreightCar *car  = new FreightCar(max_parcel_capacity);
                car -> destination_city = it.first;
                car -> current_location = name;
                for(int i = 1;i<=max_parcel_capacity;i++){
                    //cout << "EXTRACTED PARCEL : " << it.second.get_max() -> parcel_id << endl;
                    car -> load_parcel((it.second.extract_max()));
                }
                car -> sealed = true;
                car -> visited[car -> current_location] = 1;//changed
                sealed_freight_cars.push_back(car);
                // for(auto it : car -> parcels){
                //     cout << it -> parcel_id << " " << endl;
                // }
                //cout << it.second.heap.size() << endl;
                freight_cars.push_back(car);
            //}
            }
            //cout << "Size of PARCEL HEAPSSSS AFTER EXTRACTION : " << it.second.heap.size() << endl;


        }
        
        // for(auto it : parcel_destination_heaps){
        //     cout << "Parcel destination : " << it.first << endl;
        //     for(auto k : it.second.heap){
        //         cout << k -> parcel_id << " ";
        //     }
        // }
       
       
        
    }

    void print_parcels_in_freight_cars() {
        for (auto it : this -> parcel_destination_heaps) {
            for (auto& parcel : it.second.heap) {
                std::cout << "Parcel ID: " << parcel -> parcel_id << ", Parcel origin: " << parcel -> origin << ", Parcel destination: " << parcel -> destination << ", Parcel priority: " << parcel -> priority << std::endl;
            }
        }
    }
};





class Graph {

public:
    std::list<Vertex*> vertices;
    std::vector<std::pair<Vertex*, Vertex*>> edges;
    bool findPlace(string place){
        int n = vertices.size();
        //auto start = vertices.begin();
        int i = 0;
        for(auto it : vertices){
            if(it -> name == place)
             return true;
        }
        return false;
    }

    void add_edge(std::string source, std::string destination, int min_freight_cars_to_move, int max_parcel_capacity) {

        // check if source and destination vertices exist
        // if they do not exist, create them
        // add edges accordingly
        //cout << "in add_edge" << endl;
        bool index1 = findPlace(source);
        bool index2 = findPlace(destination);
        //cout << index1 << " " << index2 << endl;
        Vertex *source_vertex;
        Vertex *destination_vertex;
        if(index1 == true && index2 == true){
            
            for(auto it : vertices){
                if(it -> name == source)
                 source_vertex = it;
                if(it -> name == destination)
                 destination_vertex = it; 
                
            }

        }

        else if(index1 == true && index2 == false){
            
            
            destination_vertex = new Vertex(destination,min_freight_cars_to_move,max_parcel_capacity);
            for(auto it : this -> vertices){
                if(it -> name == source){
                  source_vertex = it;
                  break;
                }
                 //source_vertex = it;
            }

            
            

        }

        else if(index1 == false && index2 == true){
            
            source_vertex = new Vertex(source,min_freight_cars_to_move,max_parcel_capacity);
            for(auto it : this -> vertices){
                if(it -> name == destination){
                   destination_vertex = it;
                   break;
                }
                 //destination_vertex = it;
            }
            
            
        }

        else{
            source_vertex = new Vertex(source,min_freight_cars_to_move,max_parcel_capacity);
            destination_vertex = new Vertex(destination,min_freight_cars_to_move,max_parcel_capacity);
            
            // destination_vertex.add_neighbor(&source_vertex);
            // source_vertex.add_neighbor(&destination_vertex);
            // this -> vertices.push_back(source_vertex);
            // this -> vertices.push_back(destination_vertex);
            // cout << "hello man" << endl;
            // vector<Vertex*> n = source_vertex.get_neighbors();
            // cout << "ready" << endl;
            // cout << n[0] -> name << " "<< (n[0] -> name).size() << endl;
            // cout << "leaving from here" << endl;
        }

        source_vertex->add_neighbor(destination_vertex);
        destination_vertex->add_neighbor(source_vertex);
        if(index1 == false)
         this -> vertices.push_back(source_vertex);
        if(index2 == false)
         this -> vertices.push_back(destination_vertex); 

        edges.push_back({source_vertex, destination_vertex});  
        

    }

    void print_graph() {
        std::cout << "Printing graph, vertices: " << vertices.size() << std::endl;
        for (auto& vertex : this->vertices) {
            std::cout << "Vertex: " << vertex -> name << std::endl;
            std::cout << "Neighbors: ";
            for (auto& neighbor : vertex -> neighbors) {
                std::cout << neighbor->name << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::string> bfs(std::string source, std::string destination) {
        // function to return path from source to destination using bfs
        
         std::unordered_set<std::string> visited;
         std::queue<std::vector<std::string>> q;
         q.push({source});
     
         while (!q.empty()) {
             std::vector<std::string> path = q.front();
             q.pop();
             std::string current = path.back();
     
             if (current == destination) {
                 // Return the path if the destination is reached
                 return path;
             }
     
             if (visited.find(current) == visited.end()) {
                 visited.insert(current);
     
                 // Find the vertex corresponding to the current name
                 int index = findPlace(current);
                 Vertex* currentVertex;
                    for(auto it : vertices){
                        if(it -> name == current){
                           currentVertex = it;
                        }
                    }
                     
                     // Iterate through neighbors and enqueue the ones not visited
                     for (Vertex* adjacent : currentVertex -> get_neighbors()) {
                         if (visited.find(adjacent->name) == visited.end()) {
                             std::vector<std::string> new_path = path;
                             new_path.push_back(adjacent->name);
                             q.push(new_path);
                         }
                     }
                 }
             }
             // Return an empty vector if no path is found
             //return {};
            //cout << "apple" << endl;
            // for(auto it : this -> vertices){
            //     vector<Vertex*> neigh = it -> get_neighbors();
            //     cout << "Vertex is : " << it -> name << endl;
            //     cout << "Printing Size : " << neigh.size() << endl;
            // }

            
      
             return {};
         }
       
       string getBfsLink(string origin, string destination){
          if(origin == destination)
           return "";
          vector<string> path = bfs(origin, destination);
          if(path.size() > 1)
           return path[1];
          return ""; 
       }
         
     int dfsPath(string node,map<string,int> &visited,vector<string> path,vector<string> &ans, string destination){
        visited[node] =  1;
        path.push_back(node);
        Vertex *currentVertex;
        for(auto it : vertices){
            if(it -> name == node){
                currentVertex = it;
                break;
            }
        }
        vector<Vertex*> neighbours = currentVertex -> get_neighbors();
        for(Vertex* adjacent : neighbours){
            //cout << "i am inside" << endl;
            if(destination == adjacent -> name){
                //cout << "i am inside 2" << endl;
                //cout << "FOUND DESTINATION" << endl;
                path.push_back(adjacent -> name);
                //cout << "Path is : ";
                // for(auto i : path){
                //     cout << i << " ";
                // }
                //cout << endl;
                ans = path;
                //cout << "PATH IS : " << endl;
                // for(auto it : ans){
                //     cout << it << " ";
                // }
                return 1;
            }
            else if(visited[adjacent -> name] == 0){
                //path.push_back(adjac)
                //cout << "i am inside 3" << endl;
                if(dfsPath(adjacent -> name, visited,path,ans,destination) == 1) return 1;
                
            }
            
        }
        path.pop_back();
        return 0;

    }

    std::vector<std::string> dfs(std::string source, std::string destination) {
       // function to return path from source to destination using dfs
       Vertex* source_vertex;
       for(auto it : vertices){
        if(it -> name == source){
           source_vertex = it;
           break;
        }
       }
       map<string,int> visited;
       vector<string> path;
       vector<string> ans;
       dfsPath(source,visited,path,ans,destination);
    //    for(auto it : ans){
    //     cout << it << " ";
    //    }
       //cout << ans.size() << endl;
       return ans;


    }
    bool checkTwoPath(vector<string> path1,vector<string> path2){
        if(path1.size() != path2.size())
         return false;
        else{
           for(int i = 0;i<path1.size();i++){
               if(path1[i] != path2[i])
                return false;
           }
        }
        //cout << "leaving checkTwoPath" << endl;
        return true;
        
    }
    string getDfsLink(string origin, string destination, FreightCar* car){
        vector<string> path = dfs(origin, destination);
        path.erase(path.begin());
        //cout << "in getDfsLink" << endl;
        // vector<string> bfsPath = bfs(origin, destination);
        // cout << "in getDfsLink1" << endl;
        // string next_link;
        // cout << "in getDfsLink2" << endl;
        // cout << path.size() << endl;
        // cout << bfsPath.size() << " " << path[0].size() << endl;

        // if(checkTwoPath(bfsPath,path[0]) == true){
        //     if(path.size() > 1)
        //      next_link = path[1][1];
        //     else
        //     {

        //     }
              
        // }
        // else 
        //  next_link = path[0][1]; 
        // cout << "in getDfsLink3" << endl; 
        // vector<string> newpath;
        // string next_link = path[1][1];
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

    bool carPresent(vector<FreightCar*> cars, FreightCar* temp){
        //vector<FreightCar*> cars = vertex -> freight_cars;
        int count = 0;
        for(auto car1 : cars){
          int flag = 0;
          for(int i = 0;i<car1 -> max_parcel_capacity;i++){
             if(car1 -> parcels[i] -> parcel_id != temp -> parcels[i] -> parcel_id){
              //return false;
              flag = 1;
              count++;
              break;
             }
          }


        }
        if(count == cars.size())
        return false;
        return true;


    }
    void groupFreightCars() {
        // for every vertex, group freight cars by links
        cout << "entered freight cars" << endl;
        
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
                  //if(link != "")
                   bfs_bound[getBfsLink(car -> current_location, car -> destination_city)].push_back(car);
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
        cout << "INSIDE MOVE TRAINS ------------------ " << endl;
        for(auto &it : this -> vertices ){
            cout << "VERTEX IS : " << it -> name;
            cout << "Size of Freight Cars : " << it -> freight_cars.size() << endl;
            int flag_for_trains = 0;
            for(auto &i : it -> trains_to_move){
                flag_for_trains = 1;
                cout << "MADRARA UCHIHCA ----------------------------------- " << it -> trains_to_move.size() << endl;
                for(auto &j : i.second){
                   j -> current_location = i.first;
                   j -> visited[i.first] = 1;
                   for(auto &vertex : this -> vertices){
                    //count++;
                    
                       if(vertex -> name == i.first){
                        //cout << "PUSHING IN OHTER VERTEX ----------------------- " << endl;
                        vertex -> freight_cars.push_back(j);
                        break;
                       }
                   }
                //cout << "ITACHI UCHIHA " << endl;
                   for(auto f_car = it -> freight_cars.begin();f_car != it -> freight_cars.end();f_car++){
                    if(*f_car == j){
                        //cout << "I AM ENTERING THIS" << endl;
                        it -> freight_cars.erase(f_car);
                        break;
                    }
                   }

                   cout << "ITACHI UCHIHA " << endl;
                   //add freight car to next vertex
                   //j -> sealed = false;
                   j -> next_link = "";
                   if(j -> current_location == j -> destination_city){
                    //cout << "DESTINATION CITY : " << j -> current_location << endl;
                     for(auto &parcel : j -> parcels){
                        parcel -> delivered = true;
                        parcel -> current_location = parcel -> destination;
                        //cout << "Parcel Destination : " << parcel -> current_location << endl;
                     }
                     //deleting that car
                     
                     
                   }
                   else{
                    //cout << "ENTERED IN THIS GROUP ------------------ " << endl;
                    for(auto &parcel : j -> parcels){
                        parcel -> current_location = j -> current_location;
                    }
                   }


                }
            }

            if(flag_for_trains){
             cout << "Got in FLAG FOR TRAINS" << endl;
             it -> trains_to_move.clear();
            }
            cout << "AFTER MOVING : " << endl;
            cout << "VERTEX IS : " << it -> name << " ";
            cout << "Size of Freight Cars : " << it -> freight_cars.size() << endl;
        }
    }

   


};

class PRC {
public:
    Graph graph;
    std::vector<FreightCar*> freight_cars;
    string graph_file_name;
    string bookings_file_name;
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
        std::ifstream inputFile(graph_file_name);
        this -> graph_file_name = graph_file_name;

    
        if (!inputFile.is_open()) {
            std::cerr << "Error opening the file!" << std::endl;
            return; 
        }
        //Graph mygraph = this -> graph;
        //cout << &mygraph << endl;
        std::string line;
        while (std::getline(inputFile, line)) {
            //cout << "appple" << endl;
            //cout << line.size() << endl;
            istringstream iss(line);
            string word;
            vector<string> words;
            while(iss >> word){
              words.push_back(word);
            }
            //cout << words.size() << endl;
            if(words.size() != 0){
            this -> graph.add_edge(words[0], words[1], this -> min_freight_cars_to_move, this -> max_parcel_capacity);
            }
            //cout << "got out" << endl;
            
        }
        //cout << &mygraph << endl;
        // cout << "reached here" << endl;
        //cout << "i am here" << endl;
        // vector<string> bfs = mygraph.bfs("a","e");
        // vector<vector<string>> dfs = graph.dfs("a","g");
        // for(auto it : dfs){
        //     //cout << it.size() << " i am here" << endl;
        //     for(auto i : it){
        //         cout << i << " ";
        //     }
        //     cout << endl;
        // }
        // cout << "got bfs" << endl;
        // cout << bfs.size() << endl;
        // for(auto it : bfs){
        //     cout << it << " ";
        // }
        // inputFile.close();

    }

    int returnIndexOfSpace(string str){
        for(int i = 0;i<str.size();i++){
            if(str[i] == ' ')
             return i;
        }
        return -1;
    }
    void process_parcels(std::string parcels_file_name){
        // read parcels.txt file and create parcels 
        //cout << "i am here" << endl;
        std::ifstream inputFile(parcels_file_name);

        this -> bookings_file_name = parcels_file_name;

    
        if (!inputFile.is_open()) {
            std::cerr << "Error opening the file!" << std::endl;
            return; 
        }
    
        std::string line;
        vector<string> rows;
        while (std::getline(inputFile, line)) {
            rows.push_back(line);
        }
    
        int size_of_rows = rows.size();
        //cout << "Total Size : " << size_of_rows << endl;
        int j = 0;
        int k = 1;
        while(j < size_of_rows){
           int i;
           for( i = j;i<size_of_rows;i++){
             string str = rows[i];
             int index_space = returnIndexOfSpace(str);
             int tick_time = stoi(str.substr(0,index_space));
             if(tick_time != k){
                k++;
                j = i--;
                break;
             }
             else{

                //main code goes here for the time tick
                      istringstream iss(str);
                      string word;
                      vector<string> words;
                      while(iss >> word){
                       words.push_back(word);
                      }
      
                      Parcel *parcel = new Parcel(tick_time,words[1],words[2],words[3],stoi(words[4]));
                      //cout << tick_time << " " << words[1] << " " << words[2] << " " << words[3] << " " << stoi(words[4]) << endl;
                      parcels_with_time_tick[tick_time].push_back(parcel);
                      this -> parcels[words[1]] = (parcel);
                    //   for(auto it : this -> graph.vertices){
                    //     if(it -> name == words[2]){
                    //         it -> loadParcel(&parcel);
                    //     }
                    //   }
                      
             }
                    // for(auto it : this -> graph.vertices){
                    //     it -> loadFreightCars();
                    // }

                    // this -> graph.groupFreightCars();
                    // this -> graph.moveTrains();




           }
           if(i == size_of_rows)
            break;

           //j++;
        }
        inputFile.close();
        // map<int, std::vector<Parcel*>> parcels = this -> parcels_with_time_tick;
        // int count = 0;
        // for(auto it : parcels){
        //     cout << "Time Tick 1 : " << endl;
        //     for(auto i : it.second){
        //         cout << i -> parcel_id << endl;
        //         count++;
        //     }
        // }
        // cout << "Size is : " << count;
        
        
    }

    // function to return bookings at a particular time tick at a particular vertex
    std::vector<Parcel> get_bookings(int time_tick, std::string vertex) {
          vector<Parcel> ans;
          for(auto it : this -> parcels_with_time_tick){
            if(it.first == time_tick){
                for(auto i : it.second){
                    if(i -> origin == vertex){
                        ans.push_back(*i);
                    }
                }
            }
          }

          return ans;
    }

    std::map<std::string, std::string> get_state() {
        std::map<std::string, std::string> state;
        // from this.parcels
        // should return the dict of parcel_id and current_location
        map<string, Parcel*> parcels = this -> parcels;
        for(auto it : parcels){

            state[it.second -> parcel_id] = it.second -> current_location;
        }
        return state;

    }

    // run simulation function, takes run_till_time_tick as argument
    // if run_till_time_tick is not provided then run simulation till max_time_tick

    void run_simulation(int run_till_time_tick = -1) {
        // function to run simulation
        cout << "present in simulation" << endl;
        map<int, std::vector<Parcel*>> parcels = this -> parcels_with_time_tick;

        // for(auto it : parcels){
        //     cout << "Time Tick : " << it.first << endl;
        //     for(auto i : it.second){
        //         cout << i -> parcel_id << endl;
        //     }
        // }
        // cout << "Parcles ka size" << parcels.size() << endl;
        //cout << "present in simulation1" << endl;
        for(auto it : parcels){
            //cout << "simulation loop" << endl;
            if(it.first > run_till_time_tick){
                break;
            }
            else{
                //cout << "getting inside this" << endl;
                cout << "############### TIME TICK : " << it.first << " ############### ";
                for(auto parcel : it.second){
                    cout << "Parcel Id " << parcel -> parcel_id << endl;
                    //cout << "loading parcel" << endl;
                      for(auto i : this -> graph.vertices){
                        if(i -> name == parcel -> origin){
                            //cout << "loading parcel 2" << endl;
                            i -> loadParcel(parcel);
                            break;
                        }
                      }
                }
                //cout << "i am here" << endl;
                for(auto it : this -> graph.vertices){
                        it -> loadFreightCars();
                }
                //cout << "group freight cars" << endl;
                this -> graph.groupFreightCars();
                //cout << "cars grouped" << endl;
                this -> graph.moveTrains();
  
                
            }




        }

    }

    bool convergence_check(){
        // function to check convergence between old_state and new_state
    }

    bool all_parcels_delivered() {
        for (auto& parcel_pair : this->parcels) {
            Parcel *parcel = parcel_pair.second;
            if (!parcel -> delivered) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> get_stranded_parcels() {
        // return parcel_ids of stranded parcels
        vector<string> stranded_parcels;
        for(auto it : this -> parcels){
           if(it.second->current_location != it.second -> destination){
            stranded_parcels.push_back(it.first);
           }
        }

        return stranded_parcels;
    }

    std::vector<std::string> get_delivered_parcels() {
        // return parcel_ids of delivered parcels
        vector<string> stranded_parcels;
        for(auto it : this -> parcels){
           if(it.second->current_location == it.second -> destination){
            stranded_parcels.push_back(it.first);
           }
        }

        return stranded_parcels;
    }

    // get status of all parcels at time tick t (status = id, current location, delivered/not delivered)
    std::vector<std::string> get_status_of_all_parcels(int t) {
        //  std::string status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered) + "\n" ;
        // return the status of all parcels at time tick t as a vector of strings (each string formatted as above)
        //run_simulation(t);
        PRC myprc(this -> max_parcel_capacity, this -> min_freight_cars_to_move);
        myprc.create_graph(this -> graph_file_name);
        myprc.process_parcels(this -> bookings_file_name);
        myprc.run_simulation(t);
       
        map<string, Parcel*> all_parcels = myprc.parcels;
        cout << "Parcel Size : " << all_parcels.size() << endl;
        vector<string> ans;
        for(auto parcel : all_parcels){
            std::string status = parcel.second -> parcel_id + " " + parcel.second -> current_location + " " + std::to_string(parcel.second -> delivered);
            ans.push_back(status);
        }

        return ans;

    }

    // get status of parcel_id at time tick t (status = id, current location, delivered/not delivered)
    std::string get_status_of_parcel(std::string parcel_id, int t) {
        // status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered);
        // return status of one parcel at time tick t as a string (formatted as above)
        //run_simulation(t);
        PRC myprc(this -> max_parcel_capacity, this -> min_freight_cars_to_move);
        myprc.create_graph(this -> graph_file_name);
        myprc.process_parcels(this -> bookings_file_name);
        myprc.run_simulation(t);

        map<string, Parcel*> all_parcels = myprc.parcels;
        //map<string, Parcel*> all_parcels = this -> parcels;
        vector<string> ans;
        string status;
        for(auto parcel : all_parcels){
            if(parcel.second -> parcel_id == parcel_id)
             status = parcel.second -> parcel_id + " " + parcel.second -> current_location + " " + std::to_string(parcel.second -> delivered);
        }

        return status;

    }

    // get parcels delivered up to time tick t
    std::vector<std::string> get_parcels_delivered_up_to_time_tick(int t) {
        // return list of parcel_ids of parcels delivered up to time tick t
        //run_simulation(t);
        //run_simulation(t);
        PRC myprc(this -> max_parcel_capacity, this -> min_freight_cars_to_move);
        myprc.create_graph(this -> graph_file_name);
        myprc.process_parcels(this -> bookings_file_name);
        myprc.run_simulation(t);

        map<string, Parcel*> all_parcels = myprc.parcels;
        //map<string, Parcel*> all_parcels = this -> parcels;
        vector<string> ans;
        for(auto parcel : all_parcels){
            if(parcel.second -> delivered == true)
             ans.push_back(parcel.second -> parcel_id);
        }

        return ans;
    }

};

void test_case_1() {
    // create a PRC object
    PRC prc(2, 2);
    // create a graph
    prc.create_graph("samples/2/graph.txt");
    prc.process_parcels("samples/2/bookings.txt");
    prc.run_simulation(3);
    assert(prc.all_parcels_delivered() == false);
    //assert(prc.get_stranded_parcels().find("P2Ludhiana4") != std::string::npos);
    
    prc.run_simulation(4);
    std::vector<std::string> stranded_parcels = prc.get_stranded_parcels();
    for(auto it : stranded_parcels){
        cout << it << endl;
    }
    assert(std::find(stranded_parcels.begin(), stranded_parcels.end(), "P2Ludhiana4") != stranded_parcels.end());
    // delete the prc object
    //prc.~PRC();
}

void test_case_2() {
    // create a PRC object
    PRC prc(5, 5);
    // create a graph
    prc.create_graph("samples/5/graph.txt");
    prc.process_parcels("samples/5/bookings.txt");
    prc.run_simulation(4);
    assert(prc.all_parcels_delivered() == false);
    std::vector<std::string> delivered_parcels = prc.get_delivered_parcels();
    assert(std::find(delivered_parcels.begin(), delivered_parcels.end(), "P31") == delivered_parcels.end());
    assert(prc.get_parcels_delivered_up_to_time_tick(3).size() == 25);

    // vector<string> delivered = prc.get_parcels_delivered_up_to_time_tick(3);
    // cout << "DELIVERED PARCELS : " << endl;
    // for( auto it : delivered){
    //     cout << it << endl;
    // }
    cout << "------------------ STATUS OF PARCELS : -------------------" << endl;
    vector<string> status = prc.get_status_of_all_parcels(2);
    for(auto it : status){
        cout << it << endl;
    }

    cout << "--------------- STATUS OF P10 : ------------------------------------- " << endl;
    //string path = prc.get_status_of_parcel("P10",2);
    //cout << "COUNT IS : " << count << endl;;
    //cout << path << endl;
}






int main() {

    PRC prc = PRC(2, 2);
    cout << "i am here" << endl;
    prc.create_graph("graph.txt");
    cout << "i am in main" << endl;
    prc.graph.print_graph();
    prc.process_parcels("bookings.txt");
    vector<int> v(5,0);
    //prc.graph.randi(v);
    cout << "i am good" << endl;
    prc.run_simulation(3);
    cout << "running test case" << endl;
    test_case_1();
    cout << "got here" << endl;

    return 0;
}
