#include <bits/stdc++.h>
using namespace std;

class HybridNode {
public:
    string key;     // Word
    string element;    // Chapter
    HybridNode* parent;   // Parent node
    HybridNode* left_child;  // Left child node
    HybridNode* right_child;  // Right child node
    HybridNode* next_node;  // Next node in the linked list
    string color = "black";    // Color of the node

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}
    bool check_Red_Child() {
        return (left_child != nullptr and left_child->color == "red") or
            (right_child != nullptr and right_child->color == "red");
    }
    bool isLeft() { 
        bool a= this == parent->left_child; 
        return a;
    }
    void downward(HybridNode *nParent) {
        // cout << "hi ji" << endl;
        // if(parent == nullptr){
        // cout << "hello" << endl;
        // }
        if (parent != nullptr) {
            if (isLeft()) {
                parent->left_child = nParent;
            } 
            else {
                parent->right_child = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }

    HybridNode *sib() {
    // sibling null if no parent
        if (parent == NULL)
        return NULL;

        if (isLeft())
        return parent->right_child;

        return parent->left_child;
    }
    

    

   
};
vector<IndexEntry> index;


HybridNode* r_r(HybridNode* node) {
        HybridNode* x = node->left_child;
        HybridNode* y = x->right_child;
        x->right_child = node;
        node->left_child = y;
        node->parent = x;
        if (y != nullptr)
            y->parent = node;
        return x;
    }

HybridNode* r_l(HybridNode* node) {
        HybridNode* x = node->right_child;
        HybridNode* y = x->left_child;
        x->left_child = node;
        node->right_child = y;
        node->parent = x;
        if (y != nullptr)
            y->parent = node;
        return x;
    }
 
    


bool rr_case=false; 
bool lr_case=false;
bool ll_case=false; 
bool rl_case=false;
class RedBlackTree {
private:
    HybridNode* root;   // Root node

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode* getRoot() {
        return root;  // Return the root node
    }

    void setRoot(HybridNode* node) {
        root = node;  // Set the root node
    }
    void left_Rot(HybridNode *node) {
       
       
        HybridNode *nPar = node->right_child;
        
   
        if (node == root){
            // cout << "hi ji" << endl;
            root = nPar;
            
        // cout << "HE" << endl;

        }

        node->downward(nPar);

       
        node->right_child = nPar->left_child;
        
        if (nPar->left_child != nullptr)
        nPar->left_child->parent = node;

       
        nPar->left_child = node;
        // cout << "r is == " << root->key << endl;
    }
    void right_Rot(HybridNode *node) {
       
        HybridNode *nPar = node->left_child;

       
        if (node == root){
        root = nPar;
        

        }

        node->downward(nPar);

        
        node->left_child = nPar->right_child;
        
        if (nPar->right_child != nullptr)
        nPar->right_child->parent = node;

        
        nPar->right_child = node;
    }

    

    HybridNode* insertion(HybridNode* root, string k, string elem) {
        int checker = 0; 
        if (root == nullptr){
            //cout<<"rrrrrrrrrrrrrr"<<endl;
            HybridNode* temp=new  HybridNode(k,elem);
            temp->color="red";
            return temp;
            
            

        }

        else if (k < root->key) {
            
            root->left_child = insertion(root->left_child, k,elem);
           // cout<<"doneeee"<<endl;
            //cout<<root->key<<endl;
            root->left_child->parent = root;
            if (root != this->root) {
                if (root->color == "red" && root->left_child->color == "red")
                    checker = 1;
            }
           // cout<<"abc"<<endl;
        } else {
           // cout<<"entered right"<<endl;
            root->right_child = insertion(root->right_child, k,elem);
            //cout<<"done"<<endl;
           //  cout<<root->key<<endl;
             //cout<<root->right_child->key<<endl;
            root->right_child->parent = root;
            if (root != this->root) {
                if (root->color == "red" && root->right_child->color == "red")
                    checker = 1;
            }
            // cout<<f<<endl;
            // cout<<ll<<lr<<rl<<rr<<endl;
        }
 
       
        if (ll_case) {
            root = r_l(root);
            root->color = "black";
            root->left_child->color = "red";
            ll_case = false;
        } else if (rr_case) {
            root = r_r(root);
            root->color = "black";
            root->right_child->color = "red";
            rr_case= false;
        } else if (rl_case) {
            root->right_child = r_r(root->right_child);
            root->right_child->parent = root;
            root = r_l(root);
            root->color = "black";
            root->left_child->color = "red";
            rl_case = false;
        } else if (lr_case) {
            root->left_child = r_l(root->left_child);
            root->left_child->parent = root;
            root = r_r(root);
            root->color = "black";
            root->right_child->color = "red";
            lr_case = false;
        }
 
        // Handle RED-RED conflicts
        if (checker) {
           // cout<<"entered"<<endl;
            if (root->parent->right_child == root) {
                if (root->parent->left_child == nullptr || root->parent->left_child->color == "black") {
                    if (root->left_child != nullptr && root->left_child->color == "red")
                        rl_case = true;
                    else if (root->right_child != nullptr && root->right_child->color == "red")
                        ll_case = true;
                } else {
                    root->parent->left_child->color = "black";
                    root->color = "black";
                    if (root->parent != this->root)
                        root->parent->color = "red";
                }
            } else {
                if (root->parent->right_child == nullptr || root->parent->right_child->color == "black") {
                    if (root->left_child != nullptr && root->left_child->color == "red")
                        rr_case = true;
                    else if (root->right_child != nullptr && root->right_child->color == "red")
                        lr_case = true;
                } else {
                    root->parent->right_child->color = "black";
                    root->color = "black";
                    if (root->parent != this->root)
                        root->parent->color = "red";
                }
            }
            checker = 0;
        }
       // cout<<root->key<<" "<<root->colour<<" "<<"ggggggg"<<endl;
        return root;
    }
    

    HybridNode* insert(string key, string element) {
       
          if(!root){
            //cout<<"hereeeeeee"<<endl;
            root=new HybridNode(key,element);
            root->color="black";
            return root;
        }
       // cout<<root->key<<" "<<root->colour<<endl;
        root= insertion(root,key,element);
        root->parent=nullptr;
       // cout<<"root is"<<" "<<root->key<<" "<<root->color<<endl;
        //cout<<key<<"done"<<endl;
        return root;
        
    }

   void Fix_DB(HybridNode *x) {
        if (x == root)
       
        return;

        HybridNode *sib = x->sib(), *parent = x->parent;
        if (sib== nullptr) {
           
           Fix_DB(parent);
        } 
        else {
            if (sib->color == "red") {
          
                parent->color = "red";
                sib->color = "black";
                if (sib->isLeft()) {
                    
                    right_Rot(parent);
                } 
                else {
                    
                    // cout << "hi" << endl;
                    cout << "root 1 --" << parent->key << endl;
                    left_Rot(parent);
                }
               Fix_DB(x);
            } 
            else {
                // Sibling black
                if (sib->check_Red_Child()) {
                    // cout << "hi ji" << endl;
                    // at least 1 red children
                    if (sib->left_child != nullptr and sib->left_child->color == "red") {
                        if (sib->isLeft()) {
                        // cout << "hi2" << endl;
                            // left left
                            sib->left_child->color = sib->color;
                            sib->color = parent->color;
                            right_Rot(parent);
                        }
                        else {
                            // right left
                        // cout << "hi3" << endl;
                            sib->left_child->color = parent->color;
                            right_Rot(sib);
                            left_Rot(parent);
                        }
                    } 
                    else {
                        if (sib->isLeft()) {
                        // left right
                        // cout << "hi4" << endl;
                            sib->right_child->color = parent->color;
                            left_Rot(sib);
                            right_Rot(parent);
                        }
                        else {
                        // cout << "hi ji" << endl;
                            // right right
                        // cout << "hi5" << endl;
                            sib->right_child->color = sib->color;
                            sib->color = parent->color;
                            left_Rot(parent);
                            // cout << "r is == " << root->key << endl;
                            // cout << "parent is --" << parent->key << endl;
                            // cout << "root is --" << root->key << endl;
                            // cout << "root right is --" << root->right_child->key << endl;
                        }
                    }
                    parent->color = "black";
                }
                else {
                    // 2 black children
                    sib->color = "red";
                    if (parent->color == "black")
                    Fix_DB(parent);
                    else
                    parent->color = "black";
                }
            }
        }
        // cout << "r is == " << root->key << endl;
    }
    void swap(HybridNode *node1,HybridNode *node2) {
        string temp;
        temp = node1->key;
        node1->key = node2->key;
        node2->key = temp;
    }

    HybridNode *succ(HybridNode *node) {
        HybridNode *temp = node;
        while (temp->left_child != NULL)
            temp = temp->left_child;
        return temp;
    }

   

    HybridNode *repl(HybridNode *node) {
        // when node have 2 children
        if (node->left_child != nullptr and node->right_child != nullptr)
        return succ(node->right_child);

        // when leaf
        if (node->left_child == nullptr and node->right_child == nullptr)
        return nullptr;

        // when single child
        if (node->left_child != nullptr)
        return node->left_child;
        else
        return node->right_child;
    }

    void del(HybridNode *v) {
        HybridNode *u = repl(v);

    // True when u and v are both black
        bool uvBlack = ((u == nullptr or u->color == "black") and (v->color == "black"));
        // cout << uvBlack << endl;
        HybridNode *parent = v->parent;
        if (u == nullptr) {
            // cout << "true" << endl;
        // u is NULL therefore v is leaf
            if (v == root) {
                root = nullptr; // v is root, making root null
            } 
            else {
                if (uvBlack) {
                // u and v both black
                // v is leaf, fix double black at v
                // cout << "going to fix " << endl;
                    Fix_DB(v);
                    // cout << "r is == " << root->key << endl;
                } 
                else {
          // u or v is red
                    if (v->sib() != nullptr)
            // sibling is not null, make it red"
                    v->sib()->color = "red";
                }
        // delete v from the tree
                if (v->isLeft()) {
                    parent->left_child = nullptr;
                } 
                else {
                    parent->right_child = nullptr;
                }
            }
            // cout << "r is == " << root->key << endl;
            delete v;
            // cout << "r is == " << root->key << endl;
            return;
        }
        if (v->left_child == nullptr or v->right_child == nullptr) {
            // v has 1 child
            if (v == root) {
                // v is root, assign the value of u to v, and delete u
                v->key = u->key;
                v->left_child = v->right_child = nullptr;
                delete u;
            } 
            else {
                // Detach v from tree and move u up
                if (v->isLeft()) {
                    parent->left_child = u;
                } 
                else {
                    parent->right_child = u;
                }
                delete v;
                u->parent = parent;
                if (uvBlack) {
                    // u and v both black, fix double black at u
                    Fix_DB(u);
                } 
                else {
                    // u or v red, color u black
                    u->color = "black";
                }
            }
            return;
        }
        // v has 2 children, swap values with successor and recurse
        swap(u, v);
        del(u);
    }

    bool deleteNode(string key) {
        // Implement Red-Black Tree deletion
        if (root == nullptr)
        return false;
        
        HybridNode *v = search(key), *u;
        if (v == nullptr){
            return false;
        }
        if (v->key != key) {
            cout << "No node found to delete with value:" << key << endl;
            return false;
        }
        del(v);
        // cout << "r is == " << root->key << endl;
        // cout << root << endl;
        return true;
    }

    vector<HybridNode*> traverseUp(HybridNode* node) {
        // Traverse up the tree from the given node to the root
        // Return the vector of nodes in the path
        if(!node){
            return {};
        }
        vector<HybridNode*> result;
        HybridNode* temp=node;
        while(temp){
            result.push_back(temp);
            temp=temp->parent;
        }
        return result;
    }

    vector<HybridNode*> traverseDown(HybridNode* node, string bit_sequence) {
        // Traverse down the tree based on the bit sequence
        // Return the vector of nodes in the path
        HybridNode* temp=node;
        vector<HybridNode*> result;
        if(!temp){
            return {};
        }
        result.push_back(temp);
        for(auto it:bit_sequence){
            if(it=='0'){
                if(!temp->right_child){
                    return result;
                }
                temp=temp->right_child;
                result.push_back(temp);

            }
            else if(it=='1'){
                if(!temp->left_child){
                    return result;
                }
                temp=temp->left_child;
                result.push_back(temp);

            }
        }
        return result;
    }
    int calc_depth(HybridNode* node){
        if(!node){
            return 0;
        }
        int result=0;
        HybridNode* temp=root;
        while(temp->key!=node->key){
            if(temp->key>node->key){
                temp=temp->left_child;
                result++;
            }
            else{
                temp=temp->right_child;
                result++;
            }

        }
        return result;
    }

    void pror_trav(HybridNode* node,int d,vector<HybridNode*> &v){
        if(!node || calc_depth(node)>d){
            return;
        }
        v.push_back(node);
        pror_trav(node->left_child,d,v);
        pror_trav(node->right_child,d,v);

    }

    vector<HybridNode*> preOrderTraversal(HybridNode* node, int depth) {
        // Perform pre-order traversal staying within specified depth
        vector<HybridNode*> v;
        pror_trav(node,depth,v);
        return v;



    }
    HybridNode* search(string key) {
        // Implement Red-Black Tree search
        HybridNode* temp=this->root;
        while(temp && temp->key!=key){
            if(temp->key<key){
            temp=temp->right_child;
        }
            else{
            temp=temp->left_child;
        }
   }
   return temp;
        
    }
    
    int blackheight(HybridNode* node){
        // Implement blackheight
        HybridNode* temp=node;
        if(!temp){
            return 0;
        }
        int count=0;
        if(node->color=="black"){
            count=1;
        }
        return count+max(blackheight(node->left_child),blackheight(node->right_child));
    }
       
};

class IndexEntry {
private:
    string word;
    vector<pair<string, int>> chapter_word_counts;  // List of (chapter, word_count) tuples

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val) {  // Set the word
        word = word_val;
    }

    string getWord() {  // Get the word
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val) {  // Set the list of (chapter, word_count) tuples
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts() {  // Get the list of (chapter, word_count) tuples
        return chapter_word_counts;
    }
};

vector<string>chap_names;

int c=0;
vector<string> common;
class Lexicon {
private:
    RedBlackTree red_black_tree;  // Red-Black Tree

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree) {  // Set the Red-Black Tree
        red_black_tree = tree;
    }

    RedBlackTree &getRedBlackTree() {  // Get the Red-Black Tree
        return red_black_tree;
    }
    void process(vector<string> chapter_names){
     vector<string> words;
         int z=0;
        for(auto it:chapter_names){
        
        ifstream in(it);
        string chapter;
        if(!in.is_open()){
            return;
        }
        while(getline(in,chapter)){
          
            for(int i=0;i<chapter.size();i++){
                int d=0;
                string word;
                while(chapter[i]>=65 && chapter[i]<=90 || chapter[i]>=97 && chapter[i]<=122 || chapter[i]==39 || chapter[i]==45){
                    if(chapter[i]>=65 && chapter[i]<=90){
                        chapter[i]=chapter[i]+32;
                    }
                    word+=chapter[i];
                    i++;
                }
                for(auto io:words){
                    if(io==word){
                        d++;
                    }

                }
                if(d==z){
                words.push_back(word);
                }
                //cout<<word<<endl;
              
               
            }
       

            
        }
        z++;
       

        }
        
        for(int i=0;i<words.size();i++){
            int e=0;int f=0;
             for(auto it:common){
                    if(it==words[i]){
                        f++;
                    }
                }
            if(f==0){    
            for(int j=0;j<words.size();j++){
                
               
                if( words[i]==words[j]){
                    e++;
                    
                }
                
            }
            if(e==chapter_names.size()){
                common.push_back(words[i]);
            }
            }

        }

    }

    void readChapters(vector<string> chapter_names) {  
        // Process words from a chapter and update the Red-Black Tree
        // chapter_names is a vector of chapter names
        
        process(chapter_names);
        RedBlackTree tree;
        for(auto chapter_name:chapter_names){
        vector<string> words;
        ifstream in(chapter_name);
        string chapter_nam=chapter_name;
        chapter_nam.erase(chapter_nam.end()-4,chapter_nam.end());
        chap_names.push_back(chapter_nam);
        string chapter;
        if(!in.is_open()){
            return;
        }
        while(getline(in,chapter)){
            
            for(int i=0;i<chapter.size();i++){
                string word;
                while(chapter[i]>=65 && chapter[i]<=90 || chapter[i]>=97 && chapter[i]<=122 || chapter[i]==39 || chapter[i]==45){
                    if(chapter[i]>=65 && chapter[i]<=90){
                        chapter[i]=chapter[i]+32;
                    }
                    
                    word+=chapter[i];
                    i++;
                }
                //cout<<word<<endl;
                words.push_back(word);
                //cout<<word<<endl;
              
               
            }
       

            
        }
        for(auto it:words){
            int a=0;
            for(auto iq:common){
                if(iq==it){
                    a++;
                }
            }
            
            if(!tree.search(it) && a==0 ){
                c++;
                tree.insert(it,chapter_nam);
                IndexEntry* obj=new IndexEntry(it);
                vector<pair<string,int>> abc;
                pair<string,int> p={chapter_nam,1};
                //cout<<it<<" "<<chapter_nam<<" "<<"first time"<<endl;
                abc.push_back(p);
                obj->setChapterWordCounts(abc);
                index.push_back(*obj);

                

            }
            else {
                for(int j=0;j<index.size();j++){
                    int q=0;
                    if(index[j].getWord()==it){
                        vector<pair<string,int>> v=index[j].getChapterWordCounts();
                        for(int i=0;i<v.size();i++){
                           // cout<<it<<" "<<v[i].first<<" "<<v[i].second<<endl;
                            if(v[i].first==chapter_nam){
                                //cout<<"i am bitesh"<<endl;
                                q++;
                                v[i].second=v[i].second+1;
                                //cout<<v[i].second<<" "<<it<<" "<<chapter_nam<<endl;
                                index[j].setChapterWordCounts(v);


                            }
                        }
                        if(q==0){
                           // cout<<"mithundddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd"<<endl;
                            pair<string,int> pq={chapter_nam,1};
                            v.push_back(pq);
                           // cout<<it<<" "<<chapter_nam<<" "<<"1"<<endl; 
                            index[j].setChapterWordCounts(v);
                        }
                       
                    }
                    
                }
                


            }

        }
        //cout<<c<<endl;
        }

        this->setRedBlackTree(tree);

        
        
        
        
    }
    void simplify(vector<IndexEntry> &v){
        for(int i=0;i<v.size();i++){
            vector<pair<string,int>> vec = v[i].getChapterWordCounts();
          for(int k=0;k<chap_names.size();k++){
            int p=0;  
            for(int j=0;j<vec.size();j++){
                if(chap_names[k]==vec[j].first){
                    p++;
                }
             }
             if(p==0){
                vec.push_back({chap_names[k],0});
                v[i].setChapterWordCounts(vec);
             }
          }
        }





    }
    void arr(vector<pair<string,int>> &v){
        for(int i=0;i<v.size()-1;i++){
            for(int j=i+1;j<v.size();j++){
                if(v[i].first>v[j].first){
                    pair<string,int> pair=v[i];
                    v[i]=v[j];
                    v[j]=pair;
                }
            }
        }


    }
    void arrange(vector<IndexEntry> &v){
        for(int i=0;i<v.size()-1;i++){
            for(int j=i+1;j<v.size();j++){
                if(v[i].getWord()>v[j].getWord()){
                    IndexEntry t=v[i];
                    v[i]=v[j];
                    v[j]=t;

                }
            }
        }
        return;
        
    }
    
    bool check_arr(vector<int> a,vector<int> b){
        if(a.size()!=b.size()){
            return false;
        }
        int count =0;
        for(int i=0;i<a.size();i++){
            if(a[i]==b[i]){
                count++;
            }
        }
        if(count==a.size()){
            return true;
        }
        return false;

    }


    vector<IndexEntry> buildIndex() {
        // Build the index using the remaining words in the Red-Black Tree
        simplify(index);
        for(int i=0;i<index.size();i++){
            vector<pair<string,int>> vec= index[i].getChapterWordCounts();
            arr(vec);
            index[i].setChapterWordCounts(vec);
        }
        arrange(index);
        return index;

    }
};

void preorder(HybridNode* root){
        if(!root){
            return;
        }
        cout<<root->key<<" ";
        preorder(root->left_child);
        preorder(root->right_child);
    }

void inorder(HybridNode* root){
    if(!root){
        return;
    }
    inorder(root->left_child);
    cout<<root->key<<" ";
    inorder(root->right_child);
}

void postorder(HybridNode* root){
    if(!root){
        return;
    }
    postorder(root->left_child);
    postorder(root->right_child);
    cout<<root->key<<endl;
}

   




int main(){
    cout<<"abc"<<endl;
    vector<string> abc;
    abc.push_back("Chapter1.txt");
    abc.push_back("Chapter2.txt");
    abc.push_back("Chapter3.txt");
    Lexicon obj;
    vector<string> words;
    cout<<"here"<<endl;
    obj.readChapters(abc); 
    cout<<"here 00"<<endl;
    cout<<common.size();
    for(auto it:common){
        //cout<<"here 11"<<endl;
        cout<<it<<endl;
    }
    preorder(obj.getRedBlackTree().getRoot()); 
    cout<<endl;
     obj.getRedBlackTree().deleteNode("curious");
    vector<IndexEntry> v=obj.buildIndex();
    cout<<endl;
   
    preorder(obj.getRedBlackTree().getRoot());
    cout<<endl;

    // HybridNode* node=obj.getRedBlackTree().search("he");
    // if(!node){
    //     cout<<"yyyyyyyy"<<endl;
    // }
    // cout<<node->key<<endl;


    cout<<v.size()<<endl;
    for(auto it:v){
        cout<<it.getWord()<<" ";
        vector<pair<string ,int>> abc=it.getChapterWordCounts();
        for(auto ab:abc){
            //cout<<" i am bitesh"<<endl;
            cout<<ab.first<<" "<<ab.second<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;

    vector<HybridNode*> bs=obj.getRedBlackTree().traverseDown(obj.getRedBlackTree().search("wonder"),"1");
    for(auto it:bs){
        cout<<it->key<<endl;
    }
    return 0;


}
