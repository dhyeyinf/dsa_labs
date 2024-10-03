#include <bits/stdc++.h>
using namespace std;

vector<string> common_words;
vector<string> chapters;
int c = 0;


class HybridNode {
public:
    string key;     // Word
    string element;    // Chapter
    HybridNode* parent;   // Parent node
    HybridNode* left_child;  // Left child node
    HybridNode* right_child;  // Right child node
    HybridNode* next_node;  // Next node in the linked list
    string color = "black";    // Color of the node
    int ch1 = 0;
    int ch2 = 0;
    int ch3 = 0;

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}

    bool isOnLeft() { 
        return this == parent->left_child; 
    }

    HybridNode *sibling() {
    // sibling null if no parent
        if (parent == NULL)
        return NULL;

        if (isOnLeft())
        return parent->right_child;

        return parent->left_child;
    }

    void moveDown(HybridNode *nParent) {
        // cout << "hi ji" << endl;
        // if(parent == nullptr){
        // cout << "hello" << endl;
        // }
        if (parent != nullptr) {
            if (isOnLeft()) {
                parent->left_child = nParent;
            } 
            else {
                parent->right_child = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }

    bool hasRedChild() {
        return (left_child != nullptr and left_child->color == "red") or
            (right_child != nullptr and right_child->color == "red");
    }
};

    int ll = 0 ; // Left-Left Rotation flag
    int rr = 0 ; // Right-Right Rotation flag
    int lr = 0 ; // Left-Right Rotation flag
    int rl = 0 ; // Right-Left Rotation flag
    // HybridNode* temp = root;

void Preordercount(HybridNode* node)
{
    if (node == nullptr)
    return;

    // Deal with the node
    
    // cout << node->key << " ";
    c++;
    // cout << node->color << endl;

    // Recur on left subtree
    Preordercount(node->left_child);


    // Recur on right subtree
    Preordercount(node->right_child);
}

void printPreorder(HybridNode* node)
{
    if (node == nullptr)
    return;

    // Deal with the node
    
    cout << node->key << " ";
    // c++;
    cout << node->color << endl;

    // Recur on left subtree
    printPreorder(node->left_child);


    // Recur on right subtree
    printPreorder(node->right_child);
}





void pretrav_common(HybridNode* node){
    if (node == nullptr)
    return;

    // Deal with the node
    
    if(node->ch1>0 && node->ch2>0 && node->ch3>0){
        common_words.push_back(node->key);
    }
    // cout << node->key << " ";
    // cout << node->color << endl;

    // Recur on left subtree
    pretrav_common(node->left_child);


    // Recur on right subtree
    pretrav_common(node->right_child);
}



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

    void right_Rotate(HybridNode *x) {
        // new parent will be node's left child
        // cout << "doing RR" << endl;
        HybridNode *nParent = x->left_child;

        // update root if current node is root
        if (x == root){
        root = nParent;
        // cout << "HE" << endl;
        // cout << root->key << endl;

        }

        x->moveDown(nParent);

        // connect x with new parent's right element
        x->left_child = nParent->right_child;
        // connect new parent's right element with node
        // if it is not null
        if (nParent->right_child != nullptr)
        nParent->right_child->parent = x;

        // connect new parent with x
        nParent->right_child = x;
    }

    void left_Rotate(HybridNode *x) {
        // new parent will be node's right child
        // cout << x->key << endl;
        // cout << "doing LR" << endl;
        HybridNode *nParent = x->right_child;
        // cout << nParent->parent->key << endl;
        // update root if current node is root
        if (x == root){
            // cout << "hi ji" << endl;
            root = nParent;
            
        // cout << "HE" << endl;

        }

        x->moveDown(nParent);

        // connect x with new parent's left element
        x->right_child = nParent->left_child;
        // connect new parent's left element with node
        // if it is not null
        if (nParent->left_child != nullptr)
        nParent->left_child->parent = x;

        // connect new parent with x
        nParent->left_child = x;
        // cout << "r is == " << root->key << endl;
    }

    HybridNode* rotateLeft(HybridNode* node) {
        // cout << "rotating left" << endl;
        HybridNode* x = node->right_child;
        HybridNode* y = x->left_child;
        x->left_child = node;
        node->right_child = y;
        node->parent = x;
        if (y != nullptr)
            y->parent = node;
        return x;
    }

    // Function to perform Right Rotation
    HybridNode* rotateRight(HybridNode* node) {
        // cout << "rotating right" << endl;
        HybridNode* x = node->left_child;
        HybridNode* y = x->right_child;
        x->right_child = node;
        node->left_child = y;
        node->parent = x;
        if (y != nullptr)
            y->parent = node;
        return x;
    }

    HybridNode* insertinTree(HybridNode* root, string k1 , string e1){
        int f = 0; // Flag to check RED-RED conflict
        if (root == nullptr){
            HybridNode* temp = new HybridNode(k1,e1);
            temp->color = "red";
            // c++;
            if(e1 == "Chapter1.txt"){
                temp->ch1++;
            }
            else if(e1 == "Chapter2.txt"){
                temp->ch2++;
            }
            else if(e1 == "Chapter3.txt"){
                temp->ch1++;
            }
            return temp;
        }
        else if (k1.compare(root->key) < 0) {
            // cout << "Go to left child" << endl;
            root->left_child = insertinTree(root->left_child, k1, e1);
            root->left_child->parent = root;
            if (root != this->root) {
                if (root->color == "red" && root->left_child->color == "red"){
                // cout << "hi" << endl;
                    f = 1;
                }
            }
        }
        else if(k1.compare(root->key) > 0){
            // cout << "Go to right child" << endl;
            // cout << "R is -- " << root->key << endl;
            root->right_child = insertinTree(root->right_child, k1, e1);
            // cout << "R is -- " << root->key << endl;
            // cout << "R R is -- " << root->right_child->key << endl;
            root->right_child->parent = root;
            if (root != this->root) {
                if (root->color == "red" && root->right_child->color == "red"){
                // cout << "hi" << endl;
                    f = 1;
                }
            }
        }
        else {
            if(e1 == "Chapter1.txt"){
                root->ch1++;
            }
            else if(e1 == "Chapter2.txt"){
                root->ch2++;
            }
            else if(e1 == "Chapter3.txt"){
                root->ch3++;
            }
        }
        // Perform rotations
        if (ll) {
            // cout << "left ll" << endl;
            root = rotateLeft(root);
            root->color = "black";
            root->left_child->color = "red";
            ll = false;
        } else if (rr) {
            // cout << "right right rr" << endl;
            root = rotateRight(root);
            root->color = "black";
            root->right_child->color = "red";
            rr = false;
        } else if (rl) {
            // cout << "right left rl" << endl;
            root->right_child = rotateRight(root->right_child);
            root->right_child->parent = root;
            root = rotateLeft(root);
            root->color = "black";
            root->left_child->color = "red";
            rl = false;
        } else if (lr) {
            // cout << "left right lr" << endl;
            root->left_child = rotateLeft(root->left_child);
            root->left_child->parent = root;
            root = rotateRight(root);
            root->color = "black";
            root->right_child->color = "red";
            lr = false;
        }
        // if (f == true){
        //     cout << "f is true" << endl;
        // }
        // Handle RED-RED conflicts
            // cout << "R is -- " << root->key << endl;
        if (f == 1) {
            // cout << "f is true" << endl;
            if (root->parent->right_child == root) {
                if (root->parent->left_child == nullptr || root->parent->left_child->color == "black") {
                    if (root->left_child != nullptr && root->left_child->color == "red")
                        rl = true;
                    else if (root->right_child != nullptr && root->right_child->color == "red")
                        ll = true;
                } else {
                    root->parent->left_child->color = "black";
                    root->color = "black";
                    if (root->parent != this->root)
                        root->parent->color = "red";
                }
            } else {
                if (root->parent->right_child == nullptr || root->parent->right_child->color == "black") {
                    if (root->left_child != nullptr && root->left_child->color == "red")
                        rr = true;
                    else if (root->right_child != nullptr && root->right_child->color == "red")
                        lr = true;
                } else {
                    root->parent->right_child->color = "black";
                    root->color = "black";
                    if (root->parent != this->root)
                        root->parent->color = "red";
                }
            }
            f = false;
        }
        // cout << "Here root is -- " << root->key << endl;
        return root;
}

    HybridNode* insert(string key, string element) {
        // Implement Red-Black Tree insertion
        if (root == nullptr) {
            root = new HybridNode(key,element);
            root->color = "black";
            root -> ch1++;
        } else{
            // cout << "in else case" << endl;
            cout << "root is -- " << root->key << endl; 
            root = insertinTree(root, key, element);
            root->parent = nullptr;
        }
        // setRoot(insertinTree(root, key , element));
        // cout << "root is -- " << getRoot()->key << endl;
        // cout << "root color is -- " << getRoot()->color << endl;
        return root;
    }

    HybridNode *search(string k) {
        HybridNode *temp = root;
        while (temp != nullptr) {
            if (k.compare(temp->key) < 0) {
                if (temp->left_child == nullptr)
                break;
                else
                temp = temp->left_child;
            }
            else if (k.compare(temp->key) == 0) {
                break;
            } 
            else {
                if (temp->right_child == nullptr)
                break;
                else
                temp = temp->right_child;
            }
        }
        return temp;
    }

    void fixDoubleBlack(HybridNode *x) {
        if (x == root)
        // Reached root
        return;

        HybridNode *sibling = x->sibling(), *parent = x->parent;
        if (sibling == nullptr) {
            // No sibling, double black pushed up
            fixDoubleBlack(parent);
        } 
        else {
            if (sibling->color == "red") {
            // Sibling red
                parent->color = "red";
                sibling->color = "black";
                if (sibling->isOnLeft()) {
                    // left case
                    right_Rotate(parent);
                } 
                else {
                    // right case
                    // cout << "hi" << endl;
                    cout << "root 1 --" << parent->key << endl;
                    left_Rotate(parent);
                }
                fixDoubleBlack(x);
            } 
            else {
                // Sibling black
                if (sibling->hasRedChild()) {
                    // cout << "hi ji" << endl;
                    // at least 1 red children
                    if (sibling->left_child != nullptr and sibling->left_child->color == "red") {
                        if (sibling->isOnLeft()) {
                        // cout << "hi2" << endl;
                            // left left
                            sibling->left_child->color = sibling->color;
                            sibling->color = parent->color;
                            right_Rotate(parent);
                        }
                        else {
                            // right left
                        // cout << "hi3" << endl;
                            sibling->left_child->color = parent->color;
                            right_Rotate(sibling);
                            left_Rotate(parent);
                        }
                    } 
                    else {
                        if (sibling->isOnLeft()) {
                        // left right
                        // cout << "hi4" << endl;
                            sibling->right_child->color = parent->color;
                            left_Rotate(sibling);
                            right_Rotate(parent);
                        }
                        else {
                        // cout << "hi ji" << endl;
                            // right right
                        // cout << "hi5" << endl;
                            sibling->right_child->color = sibling->color;
                            sibling->color = parent->color;
                            left_Rotate(parent);
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
                    sibling->color = "red";
                    if (parent->color == "black")
                    fixDoubleBlack(parent);
                    else
                    parent->color = "black";
                }
            }
        }
        // cout << "r is == " << root->key << endl;
    }

    HybridNode *successor(HybridNode *x) {
        HybridNode *temp = x;
        while (temp->left_child != NULL)
            temp = temp->left_child;
        return temp;
    }

    void swapValues(HybridNode *u,HybridNode *v) {
        string temp;
        temp = u->key;
        u->key = v->key;
        v->key = temp;
    }

    HybridNode *BSTreplace(HybridNode *x) {
        // when node have 2 children
        if (x->left_child != nullptr and x->right_child != nullptr)
        return successor(x->right_child);

        // when leaf
        if (x->left_child == nullptr and x->right_child == nullptr)
        return nullptr;

        // when single child
        if (x->left_child != nullptr)
        return x->left_child;
        else
        return x->right_child;
    }

    void deletion(HybridNode *v) {
        HybridNode *u = BSTreplace(v);

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
                    fixDoubleBlack(v);
                    // cout << "r is == " << root->key << endl;
                } 
                else {
          // u or v is red
                    if (v->sibling() != nullptr)
            // sibling is not null, make it red"
                    v->sibling()->color = "red";
                }
        // delete v from the tree
                if (v->isOnLeft()) {
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
                if (v->isOnLeft()) {
                    parent->left_child = u;
                } 
                else {
                    parent->right_child = u;
                }
                delete v;
                u->parent = parent;
                if (uvBlack) {
                    // u and v both black, fix double black at u
                    fixDoubleBlack(u);
                } 
                else {
                    // u or v red, color u black
                    u->color = "black";
                }
            }
            return;
        }
        // v has 2 children, swap values with successor and recurse
        swapValues(u, v);
        deletion(u);
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
        deletion(v);
        // cout << "r is == " << root->key << endl;
        // cout << root << endl;
        return true;
    }

    vector<HybridNode*> traverseUp(HybridNode* node) {
        // Traverse up the tree from the given node to the root
        // Return the vector of nodes in the path
    }

    vector<HybridNode*> traverseDown(HybridNode* node, string bit_sequence) {
        // Traverse down the tree based on the bit sequence
        // Return the vector of nodes in the path
    }

    vector<HybridNode*> preOrderTraversal(HybridNode* node, int depth) {
        // Perform pre-order traversal staying within specified depth
    }
    // HybridNode* search(string key) {
    //     // Implement Red-Black Tree search
    // }
    
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

vector<IndexEntry> intrav_indexentry(HybridNode* root, vector<IndexEntry> &temp){
    if (root == nullptr)
    return temp;

    // Deal with the node
    
    // cout << node->key << " ";
    // // c++;
    // cout << node->color << endl;

    // Recur on left subtree
    intrav_indexentry(root->left_child, temp);

    // cout << "word entering index -- " << root->key << endl;
    IndexEntry identry(root->key);
    vector<pair<string,int>> chap_freq_count;
    if(root->ch1 > 0){
        chap_freq_count.push_back({"Chapter1.txt" , root->ch1});
    }
    if(root->ch2 > 0){
        chap_freq_count.push_back({"Chapter2.txt" , root->ch2});
    }
    if(root->ch3 > 0){
        chap_freq_count.push_back({"Chapter3.txt" , root->ch3});
    }
    identry.setChapterWordCounts(chap_freq_count);
    temp.push_back(identry);
    // cout << temp[0].getWord() << endl;

    // Recur on right subtree
    intrav_indexentry(root->right_child, temp);
    return temp;
}

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

    void readChapters(vector<string> chapter_names) {  
        // Process words from a chapter and update the Red-Black Tree
        // chapter_names is a vector of chapter names
        // cout << chapter_names.size() << endl;
        for(int j = 0 ; j<chapter_names.size() ; j++){
            ifstream chap(chapter_names[j]);
            string ss;
            string word = "";
            getline(chap,ss);
            for(int i = 0 ; i<ss.size() ; i++){
                if (ss[i] > 90 && ss[i] < 97 || ss[i] < 64 || ss[i] > 122 ){
                    if(ss[i] != 39 && ss[i] != 45){
                        ss[i] = ' ';
                    } 
                }
            }
            // cout << "string size is " << ss.size() << endl;
            for(int i = 0 ; i<ss.size() ; i++){
                if(ss[i] != ' ' ){
                    if(ss[i] >= 65 && ss[i] <=90){
                        ss[i] = ss[i] + 32;
                    }
                    word = word + ss[i];
                    if(i == ss.size()-1){
                        cout << "word is -- " <<  word <<  endl;
                        red_black_tree.insert(word, chapter_names[j]);
                    }
                }
                else{
                    cout << "word is -- " <<  word <<  endl;
                    red_black_tree.insert(word, chapter_names[j]);
                    // cout << "Here also" << endl;
                    word = "" ;
                }
            }
            // cout << endl << "Preorder trav" << endl;
            // printPreorder(red_black_tree.getRoot());
            // cout << endl << "Deleting " << endl;
            // red_black_tree.deleteNode("a");
            // cout << endl << "Preorder trav after deletion" << endl;
            // printPreorder(red_black_tree.getRoot());
            
            // cout << "root now -- " << lx.getRedBlackTree().getRoot() << endl;
            // cout << endl << c << endl;
        }
    }

    vector<IndexEntry> buildIndex() {
        // Build the index using the remaining words in the Red-Black Tree4
        vector<IndexEntry> result;
        result = intrav_indexentry(red_black_tree.getRoot(), result);
        // cout << result.size() << endl;
        // cout << "word is == " << result[0].getWord() << endl;
        // cout << result[0].getChapterWordCounts()[0].first << endl;
        // cout << result[0].getChapterWordCounts()[0].second << endl;

        // for(int i = 0 ; i<result.size() ; i++){
        //     cout << result[i].getWord() << " ";
        //     for(int j = 0 ; j<result[i].getChapterWordCounts().size() ; j++){
        //         cout << result[i].getChapterWordCounts()[i].first << " " ;
        //         cout << result[i].getChapterWordCounts()[i].second << " " << endl;
        //     }
        // }
        for(auto it:result){
            cout<<it.getWord()<<" ";
            vector<pair<string,int>> v=it.getChapterWordCounts();
            for(auto abc:v){
                cout<<abc.first<<" "<<abc.second<<" ";
            }
            cout<<endl;
        }
        return result;
    }
};

int main(){
    // cout << "Hi" << endl;
    Lexicon lx;
    chapters.push_back("Chapter1.txt");
    chapters.push_back("Chapter2.txt");
    chapters.push_back("Chapter3.txt");
    lx.readChapters(chapters);
    // cout << "printing pretrav of tree before pruning" << endl;
    // cout << endl;
    // cout << endl << "root in the end is -- " << lx.getRedBlackTree().getRoot()->key << endl;
    pretrav_common(lx.getRedBlackTree().getRoot());
    cout << "common words are -- " << common_words.size() << endl;
    
    cout << "printing common words " << endl;

    for(int i = 0 ; i<common_words.size() ; i++){
        cout << common_words[i] << " " ;
    }
    cout << endl;

    Preordercount(lx.getRedBlackTree().getRoot());
    cout << "No of node before pruning -- " << c << endl;
    c = 0;
    for(int i = 0 ; i<common_words.size() ; i++){
        lx.getRedBlackTree().deleteNode(common_words[i]);
    }
    Preordercount(lx.getRedBlackTree().getRoot());
    cout << "No of nodes after pruning -- " << c << endl;

    // printPreorder(lx.getRedBlackTree().getRoot());
    lx.buildIndex();

    // printPreorder(lx.getRedBlackTree().getRoot());
    // cout << lx.getRedBlackTree().getRoot()->left_child->key << endl;
    // cout << lx.getRedBlackTree().getRoot()->right_child->color << endl;
    // cout << lx.getRedBlackTree().getRoot()->parent->key << endl;
    // cout << endl << (lx.getRedBlackTree().getRoot()->parent == nullptr) << endl;
    // cout << endl << "Deleting " << endl;
    // lx.getRedBlackTree().deleteNode("a");
    // cout << endl << "Preorder trav after deletion" << endl;
    // printPreorder(lx.getRedBlackTree().getRoot());
    // cout << (lx.getRedBlackTree().getRoot()->right_child->right_child->parent->key) << endl;
    
    // cout << endl;
    // printPreorder(lx.getRedBlackTree().getRoot());
    // cout << "Hello" << endl;
    return 0;
}
