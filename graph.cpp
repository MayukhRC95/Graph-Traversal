/* This prog creates a definitive connected graph. this algo will work for a sparse graph and a dense graph if the vertex degree density is <=20%. This is verifed. For more tha 20% I am not sure. But that can be derivable.
*/
#include <iostream>
#include<cstdlib>
using namespace std;
struct Node { 
   int vertex;
   int weight; 
   struct Node *next; 
}; 
struct Node* *graph;
int *attached,*connect,n_v=0,max_degree=0,n_edge=0,avg_deg=6;
void insert(int new_weight,int new_vertex, int u) { 
   struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
   new_node->weight = new_weight;
    new_node->vertex = new_vertex;
   new_node->next = graph[u]; 
   graph[u] = new_node; 
   //cout<<"Added "<<new_vertex<<" to "<<u<<endl;
} 
void display(int u) { 
   struct Node* ptr;
   int connected_to=0;
   ptr = graph[u];
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
   cout<<"connected to "<<connected_to<<endl;
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
int main() { 

   int n,c,v,wt,full,n_vertices=0;
   int dis;
   cout<< "number of vertices"<<endl;
   cin>>n;
   graph= new Node* [n];
   attached= new int [n];
   connect=new int [n];
   //cout<<"before for"<<endl;
   for(int i=0; i<n;i++){  // makes a cycle first to ensure connectivity
      //cout<<"inside for ";
      if(i==n-1){
        // cout<<"1 for"<<i<<" "<<endl;
         wt=rand()%10;
         insert(wt,0,i);
         insert(wt,i,0);
      }
      else{
      //   cout<<"2 for"<<i<<endl;
         wt=rand()%10;
         insert(wt,i+1,i);
         insert(wt,i,i+1);
      }
   }
   for(int j=0;j<n;j++){ // can remove this later after checking.
         attached[j]=0;
      }                  // till here pending removal.
    //  cout<<"before for"<<endl;
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
               wt=rand()%100;
               insert(wt,v,i);
               insert(wt,i,v);
               n_vertices=0;
               c++;
            }   // checks whether the vertex to be connected to is full or not
         }
         else
         {
            attached[v]=1;
            wt=rand()%100;
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
   cout<<"no of vertices having degree 1000 = "<<n_v<<endl;
   cout<<"Maximum degree :"<<max_degree<<endl;
   cout<<"Number of edges :"<<n_edge/2<<endl;
  return 0;
}