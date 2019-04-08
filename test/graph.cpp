/* This creates a graph(may be connected or not connected). This graph has 3 as an average degree of every vertex. This rule is followed strictly.  Some helpful checking code while printing: 
   while(1)
   {
      cout<<"display a vertex?"<<endl;
      cin>>dis;
      if(dis==-1)
         break;
      else if(dis>=n){
         cout<<"Out of vertices"<<endl;
      }
      else
         display(dis);
   }

   The goal is to make a graph which is connected which is made possible in the next attempt. The key is to first make a cycle between all the vertices and then randomly join the other vertices.
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
int *attached,*connect,n_v=0,max_degree=0;
void insert(int new_weight,int new_vertex, int u) { 
   struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
   new_node->weight = new_weight;
    new_node->vertex = new_vertex;
   new_node->next = graph[u]; 
   graph[u] = new_node; 
   //cout<<new_vertex<<" inserted in "<<u<<endl;
} 
void display(int u) { 
   struct Node* ptr;
   int connected_to=0;
   ptr = graph[u];
   while (ptr != NULL) { 
      cout<<"Connected to Vertex: "<< ptr->vertex <<" with Weight: "<<ptr->weight<<endl; 
      ptr = ptr->next;
      connected_to++;
   }
   if(connected_to==1000){
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

   int n,c=0,v,wt,full,n_vertices=0;
   int dis;
   cout<< "number of vertices"<<endl;
   cin>>n;
   graph= new Node* [n];
   /*for(int i=0;i<n;i++){
      graph[i]=NULL;
   }*/
   attached= new int [n];
   connect=new int [n];
   //cout<<"before attached"<<endl;
   for(int j=0;j<n;j++){ // can remove this later after checking.
         //cout<<"A ";
         attached[j]=0;
      }                  // till here pending removal.
      cout<<endl;
   //cout<<"Outside for"<<endl;
   for(int i=0;i<n;i++)
   {
      n_vertices=0;
      //cout<<"Inside For for "<<i<<" ";
      //cout<<"c before "<<c<<endl;
      c=attached_vertices(i);
      //cout<<"C is "<<c<<endl;
      while(c<1000)
      {
         v=rand()%n;
         full=count_connected(v);
         if(i==v){
            continue;
         }
         else if(attached[v]==1){ // checks whether the vertex is already attached(degree already reached ).
            continue;
         }
         else if(full==1000){
            //cout<<full<<endl;
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
            //cout<<v<<" ";
            //cout<<full<<" ";
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
  return 0;
}