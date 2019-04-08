#include<iostream>
#include<cstdlib>
using namespace std;
struct Node { 
   int vertex;
   int weight; 
   struct Node *next; 
}; 
struct Node* *graph;
int *attached,*connect,n,*Bw,*status,*dad,n_v=0,max_degree=0,avg_deg=3,n_edge=0;
void insert(int new_weight,int new_vertex, int u) { 
   struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
   new_node->weight = new_weight;
    new_node->vertex = new_vertex;
   new_node->next = graph[u]; 
   graph[u] = new_node; 
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
int min(int a,int b)
{
  //cout<<"min"<<endl;
	if(a<b){
		return a;
	}
	else{
		return b;
	}
}
void set_fringe(int s)
{
  cout<<"Inside set_fringe"<<endl;
	struct Node* ptr;
  ptr = graph[s];
  while (ptr != NULL){
  	status[ptr->vertex]=1;
  	dad[ptr->vertex]=s;
  	Bw[ptr->vertex]=ptr->weight;
  	ptr = ptr->next;
  }
}
void check_v(int v)
{
  cout<<"check_v"<<endl;
	struct Node* ptr;
	int w,fringe_added=0,fringe_changed=0;
  ptr = graph[v];
  //cout<<"From vertex"<<ptr->vertex<<endl;
  while (ptr != NULL){
  	//cout<<"Inside while"<<endl;
    w=ptr->vertex;
    //cout<<"At vertex "<<w<<"Status: "<<status[w]<<endl;
  	if(status[w]==0){
  		status[w]=1;
  		dad[w]=v;
      Bw[w]=min(Bw[v],ptr->weight);
      fringe_added++;
  	}
  	else if(status[w]==1 && Bw[w]<min(Bw[v],ptr->weight)){
  		dad[w]=v;
  		Bw[w]=min(Bw[v],ptr->weight);
      fringe_changed++;
  	}
    ptr=ptr->next;
  }
}
void max_bandwitdth_path(int s)
{
  cout<<"inside max_bandwitdth_path"<<endl;
	int isfringe=0,maxbw=0,v;
	for(int i=0;i<n;i++){
		//cout<<"Inside status for"<<endl;
    status[i]=0;
	}
	status[s]=2; 
  Bw[s]=101;
	set_fringe(s);
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
    cout<<Bw[i]<<" ";
  } 
  cout<<endl;
	for(int i=0;i<n;i++){
		if(status[i]==1){
			isfringe+=1;
		}
	}
	while(isfringe>0){
    cout<<"Fringes "<<isfringe<<endl;
		for(int i=0;i<n;i++){
			if(Bw[i]>maxbw && status[i]==1){
				maxbw=Bw[i];
				v=i;
			}
		}
    cout<<"Max bw: "<<maxbw<<" vertex "<<v<<endl;
    maxbw=0;
		status[v]=2;
    cout<<"status "<<status[v]<<endl;
		check_v(v);
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
    cout<<Bw[i]<<" ";
  }
  cout<<endl;
    isfringe=0;
    for(int i=0;i<n;i++){
      if(status[i]==1){
        isfringe+=1;
      }
    }
    cout<<"Fringes "<<isfringe<<endl;
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
    cout<<Bw[i]<<" ";
  } 
  cout<<endl;
}
int main() { 

   int c,v,wt,full,s,t,n_vertices=0;
   int dis;
   cout<< "number of vertices"<<endl;
   cin>>n;
   graph= new Node* [n];
   attached= new int [n];
   connect=new int [n];
   status=new int [n];
   dad=new int [n];
   Bw=new int [n];
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