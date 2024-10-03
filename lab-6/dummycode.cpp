 #include<bits/stdc++.h>
 #include<fstream>
 #include<sstream>
  
  using namespace std;



  int main(){
 
 ifstream in("Chapter_1.txt");
        string chapter;
        if(!in.is_open()){
            return 0;
        }
        while(getline(in,chapter)){
          
            for(int i=0;i<chapter.size();i++){
                string word;
                while(chapter[i]>=65 && chapter[i]<=90 || chapter[i]>=97 && chapter[i]<=122 || chapter[i]==39){
                    word+=chapter[i];
                    i++;
                }
                //words.push_back(word);
                cout<<word<<endl;
            }

            
        }
  }
