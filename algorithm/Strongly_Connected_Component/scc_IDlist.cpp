#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<cstring>
#include<fstream>
#include<map>
#include<string>

#define MAX_V 10000 

using namespace std;
int V;

vector<int> G[MAX_V]; //グラフの隣接リストを表現
vector<int> rG[MAX_V]; //辺の向きを逆にしたグラフ
vector<int> vs; //帰りがけ順の並び. backtrackするごとに入れる。
bool used[MAX_V]; //すでに調べたか
int cmp[MAX_V]; //属する強連結成分のトポロジカル順序


void add_edge(int from,int to);
void rdfs(int v, int k);
int scc();

int main(){
  int a,b;
  int max = 0;

  string rtext,ltext;
  map<string,int> mp;
  map<string,int> flag;
  string str;
  int valu = 0;

  //ifstream ifs("listdat.txt");
  

  string reading_line_buffer;

  ifstream reading_file;
  reading_file.open("IDedgelist.dat");
  

  if(reading_file.fail()){
    cerr<<"File do not exist\n";
    exit(0);
  }
  
  //cout << mp["abd"]; //keyを入れていないものに対しては、0出力する。

  
  //trueはひたすらファイルを読みこむことになる
  while(true){ 
    //sscanf(str.data(),"%s %s",rtext.c_str(),ltext.c_str());
    reading_file >> rtext >> ltext;
    if(reading_file.eof()) break;
    
    if(flag[ltext]!=1) {mp[ltext] = valu; flag[ltext]=1;valu++;}
    if(flag[rtext]!=1) {mp[rtext] = valu; flag[rtext]=1;valu++;}
    
    add_edge(mp[ltext],mp[rtext]);
      
    if(mp[rtext]>mp[ltext] && mp[rtext] > max){
      max = mp[rtext];
    }else if(mp[ltext] >= mp[rtext] && mp[ltext] > max){
      max = mp[ltext];
    }
    //cout << valu << endl;
  }
  
   cout << "C" << mp["C"] << endl;
   
   V = max + 1;
   printf("largest node number = %d\n",max);
   printf("num_of_sccs = %d\n",scc());  
}

void add_edge(int from,int to){
  G[from].push_back(to);
  rG[to].push_back(from);
}

void dfs(int v){
  used[v] = true;
  for(int i = 0;i < G[v].size(); i++){
    if(!used[G[v][i]]) dfs(G[v][i]);

  }
  vs.push_back(v);
}

void rdfs(int v, int k){
  used[v] = true;
  cmp[v] = k;
  for(int i=0;i<rG[v].size(); i++){
    if(!used[rG[v][i]]) rdfs(rG[v][i],k);
  }
}

int scc(){
  memset(used,0,sizeof(used));
  vs.clear();
  for(int v=0;v<V;v++){
    if(!used[v]) dfs(v);
  } 
  memset(used,0,sizeof(used));
  int k = 0;

  int j;
  for(int i=vs.size()-1; i >= 0; i--){
    if(!used[vs[i]]) rdfs(vs[i],k++);
  }
  return k; //number of scc's
  //to print specific scc. specify topological order.  
}
