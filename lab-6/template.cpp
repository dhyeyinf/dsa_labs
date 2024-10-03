#include <iostream>
#include <vector>
#include<fstream>
#include<sstream>
using namespace std;

 

class HybridNode {
public:
    string key;  
    string element;  
    HybridNode* parent;
    HybridNode* left_child;
    HybridNode* right_child;
    HybridNode* next_node;
    char colour;

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) ,colour('R'){}
};

HybridNode* search(HybridNode* root, string key){
   HybridNode* temp=root;
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

HybridNode* rotateLeft(HybridNode* node) {
        HybridNode* x = node->right_child;
        HybridNode* y = x->left_child;
        x->left_child = node;
        node->right_child = y;
        node->parent = x;
        if (y != nullptr)
            y->parent = node;
        return x;
    }
 
    
HybridNode* rotateRight(HybridNode* node) {
        HybridNode* x = node->left_child;
        HybridNode* y = x->right_child;
        x->right_child = node;
        node->left_child = y;
        node->parent = x;
        if (y != nullptr)
            y->parent = node;
        return x;
    }

bool ll=false; 
    bool rr=false; 
    bool lr=false;
    bool rl=false;

class RedBlackTree {
private:
    HybridNode* root;
    

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode* getRoot() {
        return root;
    }

    void setRoot(HybridNode* node) {
        root = node;
    }

    HybridNode* insertHelp(HybridNode* root, string key, string element ) {
        bool f = false; // Flag to check RED-RED conflict
 
        if (root == nullptr){
            //cout<<"rrrrrrrrrrrrrr"<<endl;
            return new HybridNode(key,element);
            
            

        }

        else if (key < root->key) {
            //cout<<"entered left"<<endl;
            root->left_child = insertHelp(root->left_child, key,element);
           // cout<<"doneeee"<<endl;
            //cout<<root->key<<endl;
            root->left_child->parent = root;
            if (root != this->root) {
                if (root->colour == 'R' && root->left_child->colour == 'R')
                    f = true;
            }
           // cout<<"abc"<<endl;
        } else {
           // cout<<"entered right"<<endl;
            root->right_child = insertHelp(root->right_child, key,element);
            //cout<<"done"<<endl;
           //  cout<<root->key<<endl;
             //cout<<root->right_child->key<<endl;
            root->right_child->parent = root;
            if (root != this->root) {
                if (root->colour == 'R' && root->right_child->colour == 'R')
                    f = true;
            }
            // cout<<f<<endl;
            // cout<<ll<<lr<<rl<<rr<<endl;
        }
 
        // Perform rotations
        if (ll) {
            root = rotateLeft(root);
            root->colour = 'B';
            root->left_child->colour = 'R';
            ll = false;
        } else if (rr) {
            root = rotateRight(root);
            root->colour = 'B';
            root->right_child->colour = 'R';
            rr = false;
        } else if (rl) {
            root->right_child = rotateRight(root->right_child);
            root->right_child->parent = root;
            root = rotateLeft(root);
            root->colour = 'B';
            root->left_child->colour = 'R';
            rl = false;
        } else if (lr) {
            root->left_child = rotateLeft(root->left_child);
            root->left_child->parent = root;
            root = rotateRight(root);
            root->colour = 'B';
            root->right_child->colour = 'R';
            lr = false;
        }
 
        // Handle RED-RED conflicts
        if (f) {
           // cout<<"entered"<<endl;
            if (root->parent->right_child == root) {
                if (root->parent->left_child == nullptr || root->parent->left_child->colour == 'B') {
                    if (root->left_child != nullptr && root->left_child->colour == 'R')
                        rl = true;
                    else if (root->right_child != nullptr && root->right_child->colour == 'R')
                        ll = true;
                } else {
                    root->parent->left_child->colour = 'B';
                    root->colour = 'B';
                    if (root->parent != this->root)
                        root->parent->colour = 'R';
                }
            } else {
                if (root->parent->right_child == nullptr || root->parent->right_child->colour == 'B') {
                    if (root->left_child != nullptr && root->left_child->colour == 'R')
                        rr = true;
                    else if (root->right_child != nullptr && root->right_child->colour == 'R')
                        lr = true;
                } else {
                    root->parent->right_child->colour = 'B';
                    root->colour = 'B';
                    if (root->parent != this->root)
                        root->parent->colour = 'R';
                }
            }
            f = false;
        }
       // cout<<root->key<<" "<<root->colour<<" "<<"ggggggg"<<endl;
        return root;
    }

    
 
    HybridNode* insert(string key, string element) {
        // Implement Red-Black Tree insertion
       // cout<<key<<endl;
        if(!root){
            //cout<<"hereeeeeee"<<endl;
            root=new HybridNode(key,element);
            root->colour='B';
            return root;
        }
       // cout<<root->key<<" "<<root->colour<<endl;
        root=insertHelp(root,key,element);
        cout<<"root is"<<" "<<root->key<<" "<<root->colour<<endl;
        //cout<<key<<"done"<<endl;
        return root;
        

    }

    bool deleteNode(string key) {
        // Implement Red-Black Tree deletion
    }

    void traverseUp(HybridNode* node) {
        // Traverse up the tree from the given node to the root
    }

    void traverseDown(HybridNode* node, string bit_sequence) {
        // Traverse down the tree based on the bit sequence
    }

    vector<string> preOrderTraversal(HybridNode* node, int depth) {
        // Perform in-order traversal staying within specified depth
    }
    HybridNode* search(string key) {
        // Implement Red-Black Tree search
         HybridNode* temp=root;
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
    }
};

class IndexEntry {
private:
    string word;
    vector<pair<string, int>> chapter_word_counts;  // List of (chapter, word_count) tuples

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val) {
        word = word_val;
    }

    string getWord() {
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val) {
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts() {
        return chapter_word_counts;
    }

    void addOccurrence(string chapter, int word_count) {
        // Add a chapter's word count for this word
    }

    string toString() {
        // Return a string representation of the IndexEntry
        // Modify the implementation as needed for specific use cases
        return "";
    }
};
int c=0;



class Lexicon {
private:
    RedBlackTree red_black_tree;

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree) {
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree() {
        return red_black_tree;
    }

    void readChapter(string chapter_name, vector<string> words) {
        // Process words from a chapter and update the Red-Black Tree
        ifstream in(chapter_name);
        string chapter;
        if(!in.is_open()){
            return;
        }
        while(getline(in,chapter)){
          
            for(int i=0;i<chapter.size();i++){
                string word;
                while(chapter[i]>=65 && chapter[i]<=90 || chapter[i]>=97 && chapter[i]<=122 || chapter[i]==39){
                    word+=chapter[i];
                    i++;
                }
                words.push_back(word);
                //cout<<word<<endl;
              
               
            }
       

            
        }
        for(auto it:words){
            
            if(!red_black_tree.search(it)){
                c++;
                red_black_tree.insert(it,chapter_name);
                

            }
            else{
                HybridNode* temp=red_black_tree.search(it);


            }

        }
        cout<<c<<endl;

        
        

        
    }

    void pruneRedBlackTree() {
        // Prune the Red-Black Tree by deleting common words
    }

    vector<IndexEntry> buildIndex() {
        // Build the index using the remaining words in the Red-Black Tree
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

extern Lexicon lexicon;

int main(){
    cout<<"abc"<<endl;
    Lexicon obj;
    vector<string> words;
    obj.readChapter("Chapter_1.txt",words); 
    preorder(obj.getRedBlackTree().getRoot()); 
    return 0;

}
