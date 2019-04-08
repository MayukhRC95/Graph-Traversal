#include <iostream>
#include<cstdlib>
using namespace std;
struct Node { 
   int data; 
   struct Node *next; 
}; 
struct Node* *table;
void insert(int new_data, int i) { 
   struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
   new_node->data = new_data; 
   new_node->next = table[i]; 
   table[i] = new_node; 
} 
void display(int i) { 
   struct Node* ptr;
   ptr = table[i];
   while (ptr != NULL) { 
      cout<< ptr->data <<" "; 
      ptr = ptr->next; 
   } 
}
int main() { 

   int n,c,data,l;
   cout<< "list size"<<endl;
   cin>>n;
   table= new Node* [n];
   for(int i=0;i<n;i++)
   {
      c=1;
      cout<<i+1<<"th List"<<endl;
      table[i]=NULL;
      while(c==1)
      {
         cout<<"insert element"<<endl;
         cin>>data;
         insert(data,i);
         cout<<"want to continue"<<endl;
         cin>>c;
      }
   }
   c=1;
   while(c==1){
      cout<<"Display which list?"<<endl;
      cin>>l;
      display(l-1);
      cout<<"want to continue?"<<endl;
      cin>>c;
   }

   return 0;
}