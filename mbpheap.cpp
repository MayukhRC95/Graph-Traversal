#include <iostream>
#include<cstdlib>
using namespace std;
struct Node { 
   int vertex;
   int weight; 
   struct Node *next; 
}; 
struct Node* *graph;
int *attached,*connect,n,*bw,*status,*dad,*H,*Hv,avg_deg=3,max_degree=0,n_edge=0,n_v=0;
void insert(int new_weight,int new_vertex, int u) { 
   struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
   new_node->weight = new_weight;
    new_node->vertex = new_vertex;
   new_node->next = graph[u]; 
   graph[u] = new_node;
   //cout<<"connecting "<<new_vertex<<" to "<<u<<endl;
} 
void display(int u) { 
   struct Node* ptr;
   ptr = graph[u];
   int connected_to=0;
   while (ptr != NULL) { 
      cout<<"Connected to Vertex: "<< ptr->vertex <<" with Weight: "<<ptr->weight<<endl; 
      ptr = ptr->next;
      connected_to++;
      n_edge++;
   }
   if(connected_to==avg_deg){
      n_v++;
   }
   if(connected_to>max_degree){
      max_degree=connected_to;
   }
   cout<<"connected to "<<connected_to<<" vertices"<<endl;
}
int attached_vertices(int u)
{
   int count=0,v;
   struct Node* ptr;
   ptr = graph[u];
   while (ptr != NULL) { 
      v=ptr->vertex;
      attached[v]=1;// checks to which vertices it is already connected to(fills up attached array for future referencing)
      ptr = ptr->next;
      count++;
   }
   return count;// counts number of edges already there(returns the number of vertices already connected to)(0 if that is starting to fill up)
}
int count_connected(int u)
{
   int count=0,v;
   struct Node* ptr;
   ptr = graph[u];
   while (ptr != NULL) { 
      v=ptr->vertex;
      connect[v]=1;// checks to which vertices it is already connected to(fills up attached array for future referencing)
      ptr = ptr->next;
      count++;
   }
   return count;// counts number of edges already there(returns the number of vertices already connected to)(0 if that is starting to fill up)
}
void fixheap(int a,int vertex,int pos, int end)
{
   int temp,temp2,check=-1;
   if(a>H[pos/2-1] && pos!=1){
      temp=H[pos/2-1];
      temp2=Hv[pos/2-1];
      H[pos/2-1]=a;
      H[pos-1]=temp;
      Hv[pos/2-1]=vertex;
      Hv[pos-1]=temp2;
      pos=pos/2;
      check=1;
   }
   else if(2*pos<=end || 2*pos+1<=end){
      if(2*pos+1<=end){
         if(a<H[2*pos-1] && H[2*pos-1]>H[2*pos]){
            temp=H[2*pos-1];
            H[2*pos-1]=a;
            H[pos-1]=temp;
            pos=2*pos;
            check=1;
         }
         else if(a<H[2*pos]){
            temp=H[2*pos];
            H[2*pos]=a;
            H[pos-1]=temp;
            pos=2*pos+1;
            check=1;
         }
      }
      else if(a<H[2*pos-1]){
         temp=H[2*pos-1];
         H[2*pos-1]=a;
         H[pos-1]=temp;
         pos=2*pos;
         check=1;
      }
   }
   if(check==1){
      fixheap(a,vertex,pos,end);
   }
}
int insert_heap(int a, int pos,int vertex)
{
   H[pos]=a;
   Hv[pos]=vertex;
   // cout<<"Inside Insert"<<H[pos+1]<<endl;
   fixheap(a,vertex,pos+1,pos+1);
   return pos+1;
}
int Delete(int del, int pos)
{
   H[del-1]=H[pos-1];
   Hv[del-1]=Hv[pos-1];
   fixheap(H[del-1],Hv[del-1],del,pos-1);
   return pos-1;
}
int min(int a,int b)
{
   if(a<b){
      return a;
   }
   else{
      return b;
   }
}
int set_fringe(int s)
{
   struct Node* ptr;
   ptr = graph[s];
   int pos=0;
   while (ptr != NULL){
      status[ptr->vertex]=1;
      dad[ptr->vertex]=s;
      bw[ptr->vertex]=ptr->weight;
      pos=insert_heap(ptr->weight,pos,ptr->vertex);
      ptr = ptr->next;
      //pos+=1;
   }
  return pos;
}
int check_v(int v,int pos)
{
   struct Node* ptr;
   int w,del;
   ptr = graph[v];
   while (ptr != NULL){
      w=ptr->vertex;
      if(status[w]==0){
         status[w]=1;
         dad[w]=v;
         bw[w]=min(bw[v],ptr->weight);
         pos=insert_heap(ptr->weight,pos,ptr->vertex);
      }
      else if(status[w]==1 && bw[w]<min(bw[v],ptr->weight)){
         for(int i=0;i<n;i++){
            if(w==Hv[i]){
               del=i+1;
            }
         }
         pos=Delete(del,pos);
         dad[w]=v;
         bw[w]=min(bw[v],ptr->weight);
         pos=insert_heap(bw[w],pos,w);
      }
      ptr = ptr->next;
   }
   return pos;
}
void max_bandwitdth_path(int s)
{
   int isfringe=0,maxbw=0,v,pos;
   for(int i=0;i<n;i++){
      status[i]=0;
   }
   status[s]=2; 
   bw[s]=101;
   pos=set_fringe(s);
   /*for(int i=0;i<n;i++){
      if(status[i]==1){
         isfringe=1;
      }
   } finding fringes are there */
   if(Hv[0]!=-1){
      isfringe=1;
   }
   while(isfringe>0){
      /*for(int i=0;i<n;i++){
         if(bw[i]>maxbw){
            maxbw=bw[i];
            v=i;
         }
      } find the vertex with maximum bw */
      v=Hv[0];
      pos=Delete(1,pos);
      status[v]=2;
      pos=check_v(v,pos);
      isfringe=0;
      /*for(int i=0;i<n;i++){
         if(status[i]==1){
            isfringe=1;
         }
      }*/
      /*if(H[0]!=-1 && pos!=0){
         isfringe=1;
      }*/
      for(int i=0;i<n;i++){
      if(status[i]==1){
        isfringe+=1;
      }
    }
   }
   cout<<"status array ";
  for(int i=0;i<n;i++){
    cout<<status[i]<<" ";
  }
  cout<<endl;
  cout<<"dad array ";
  for(int i=0;i<n;i++){
    cout<<dad[i]<<" ";
  }
  cout<<endl;
  cout<<"Bandwidth array ";
  for(int i=0;i<n;i++){
    cout<<bw[i]<<" ";
  } 
  cout<<endl;
}
int main() { 

   int n,c,v,wt,full,s,t,n_vertices=0;
   int dis;
   cout<< "number of vertices"<<endl;
   cin>>n;
   graph= new Node* [n];
   attached= new int [n];
   connect=new int [n];
   status=new int [n];
   dad=new int [n];
   bw=new int [n];
   H=new int[n];
   Hv=new int[n];
   for(int i=0;i<n;i++){
      H[i]=-1;
      Hv[i]=-1;
   }
   for(int i=0; i<n;i++){
      if(i==n-1){
         wt=rand()%100+1;
         insert(wt,0,i);
         insert(wt,i,0);
      }
      else{
         wt=rand()%100+1;
         insert(wt,i+1,i);
         insert(wt,i,i+1);
      }
   }   // check this part of the code
   for(int j=0;j<n;j++){ // can remove this later after checking.
         attached[j]=0;
      }                  // till here pending removal.
   for(int i=0;i<n;i++)
   {
      c=attached_vertices(i);
      while(c<avg_deg)
      {
         v=rand()%n;
         full=count_connected(v);
         if(i==v){
            continue;
         }
         else if(attached[v]==1){ // checks whether the vertex is already attached(degree already reached ).
            continue;
         }
         else if(full==avg_deg){
            n_vertices+=1;
            if(n_vertices<n-1){
               continue;
            }
            else{
               wt=rand()%100 + 1;
               insert(wt,v,i);
               insert(wt,i,v);
               n_vertices=0;
               c++;
            }   // checks whether the vertex to be connected to is full or not
         }
         else
         {
            attached[v]=1;
            wt=rand()%100 + 1;
            insert(wt,v,i);
            insert(wt,i,v);
            c++;
         }
      }
      for(int j=0;j<n;j++){
         attached[j]=0; // preparing the attached array for the next vertex.
      }
   }
   for(int i=0;i<n;i++)
   {
      cout<<"Displaying "<<i<<"th vertex connections"<<endl;
      display(i);
   }
   cout<<"no of vertices having degree "<<avg_deg<<"  = "<<n_v<<endl;
   cout<<"Maximum degree :"<<max_degree<<endl;
   cout<<"Number of edges :"<<n_edge/2<<endl;
   cout<<"MBP starting vertex: "<<endl;
   cin>>s;
   max_bandwitdth_path(s);
   cout<<"Target vertex: "<<endl;
   cin>>t;
   while(t!=s){
      cout<<t<<" ";
      t=dad[t];
   }
   cout<<s<<endl;
  return 0;
}