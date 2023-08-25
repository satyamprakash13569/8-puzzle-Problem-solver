#include<bits/stdc++.h>
using namespace std;
int step=0;
int dx[]={0,-1,0,1};
int dy[]={1,0,-1,0};
class state{
    public:
    state * parent;
    vector<vector<int>> arr;
    int hval;
    state(){
    arr.resize(3,vector<int>(3));
    }
};
void printv(vector<vector<int>> vv){
    cout<<step<<"th step"<<endl;step++;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<vv[i][j]<<" ";
        }cout<<endl;
    }cout<<endl;
}
void getpath(state * &s){
    if(s->parent==NULL){
        printv(s->arr);
        return;
    }
    getpath(s->parent);
    printv(s->arr);
}
bool isvalid(int x,int y){
    if(x<0 || x>2 || y<0 || y>2){
        return false;
    }
    return true;
}
int hvalue(vector<vector<int>> vv,vector<vector<int>> final){
    int h=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(vv[i][j]!=final[i][j] && vv[i][j]!=0){
                h++;
            }
        }
    }
    return h;
}
void h_methode(state * &s,vector<vector<int>> final,map<vector<vector<int>>,bool> &visited){
    pair<int,int> coordinate;
    priority_queue<pair<int,state*>,vector<pair<int,state*>>,greater<pair<int,state*>>>q;
    q.push(make_pair(s->hval,s));
    int x,y;
    while(!q.empty()){
    state * ss=q.top().second;
    q.pop();
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(ss->arr[i][j]==0){
                coordinate.first=i;
                coordinate.second=j;
                break;
            }
        }
    }
    for(int i=0;i<4;i++){
    x=coordinate.first+dx[i];y=coordinate.second+dy[i];
    if(isvalid(x,y)){
        vector<vector<int>> vv(3,vector<int>(3));
        vv=ss->arr;
        swap(vv[coordinate.first][coordinate.second],vv[x][y]);
        printv(vv);
        int h_value=hvalue(vv,final);
        if(visited[vv]==false){
            visited[vv]=true;
            state * temp=new state();
            temp->arr=vv;
            temp->parent=ss;
            temp->hval=h_value;
            q.push(make_pair(temp->hval,temp));
            if(h_value==0){
                cout<<"Relavant states:"<<endl;
                step=0;
                getpath(temp);
                return;
            }
        }
    }
    }
    }
}
int main(){
    vector<vector<int>>initial(3,vector<int>(3));
    cout<<"Enter initial state:"<<endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cin>>initial[i][j];
        }
    }
    vector<vector<int>>final(3,vector<int>(3));
    cout<<"Enter final state:"<<endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cin>>final[i][j];
        }
    }
    state * s=new state();
    s->arr=initial;
    s->parent=NULL;
    s->hval=hvalue(s->arr,final);
    map<vector<vector<int>>,bool> visited;
    visited[s->arr]=true;
    if(s->hval==0){
    getpath(s);
    }
    else{
    h_methode(s,final,visited); 
    }
    return 0;
}
