//強い連結成分分解(Strongly Connected Component
//二度のdfsで実装
//強連結成分を一つの点に潰すと、DAG(閉路を持たない有向グラフ)

//関係ないメモ：
/*グローバル変数に頼りすぎると、「機能単位の独立したモジュール化」という関数本来の目的が失われることになるわけです。
従って、基本的には「できる限りローカル変数を用いて、関数とは引数と返却値でやり取りする」という習慣をつけた方がよいでしょう。
*/
/////////
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<cstring>


#define MAX_V 4 

using namespace std;
int V = 4;

vector<int> G[MAX_V]; //グラフの隣接リストを表現
vector<int> rG[MAX_V]; //辺の向きを逆にしたグラフ
vector<int> vs; //帰りがけ順の並び. backtrackするごとに入れる。
bool used[MAX_V]; //すでに調べたか
int cmp[MAX_V]; //属する強連結成分のトポロジカル順序

void add_edge(int from,int to);
void rdfs(int v, int k);
int scc();

int main(){
  add_edge(0,1);
  add_edge(1,0);
  add_edge(1,2);
  add_edge(2,3);
  add_edge(3,1);
  //実際のデータを入れる場合、ID?を標準入力させる？
  //IDの入力の場合どうするか？

  printf("scc = %d\n",scc());  
  
  //int j = vs.size();
  //printf("vs size %d\n",j);

}

//辺の向きを順方向と逆方向で入れる。
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
