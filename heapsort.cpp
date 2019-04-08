/* HeapSort
*/
#include<iostream>
#include<cstdlib>
using namespace std;
int *H;
void fixheap(int a, int pos, int end)
{
	int temp=0;
	if(a>H[pos/2-1] && pos!=1){
		temp=H[pos/2-1];
		H[pos/2-1]=a;
		H[pos-1]=temp;
		pos=pos/2;
		temp=1;
	}
	else if(2*pos<=end || 2*pos+1<=end){
		if(2*pos+1<=end){
			if(a<H[2*pos-1] && H[2*pos-1]>H[2*pos]){
				temp=H[2*pos-1];
				H[2*pos-1]=a;
				H[pos-1]=temp;
				pos=2*pos;
				temp=1;
			}
			else if(a<H[2*pos]){
				temp=H[2*pos];
				H[2*pos]=a;
				H[pos-1]=temp;
				pos=2*pos+1;
				temp=1;
			}
		}
		else if(a<H[2*pos-1]){
			temp=H[2*pos-1];
			H[2*pos-1]=a;
			H[pos-1]=temp;
			pos=2*pos;
			temp=1;
		}
	}
	if(temp==1){
		fixheap(a,pos,end);
	}
}
void insert(int a, int pos)
{
	H[pos]=a;
	fixheap(a,pos+1,pos+1);
}
int main()
{
	int n,pos=0;
	cout<<"Enter the no of elements:"<<endl;
	cin>>n;
	H= new int[n];
	cout<<"Original array :";
	for(int i=0;i<n;i++)
	{
		int a= rand()%100;
		cout<<a<<" ";
		insert(a,pos);
		pos+=1;
	}
	cout<<endl;
	cout<<"Heap: ";
	for(int i=0;i<n;i++){
		cout<<H[i]<<" ";
	}
	cout<<endl;
	//pos-=1;
	for(int i=0;i<n-1;i++){
		int temp=H[0];
		//cout<<temp<<" "<<H[pos-1]<<" ";
		H[0]=H[pos-1];
		H[pos-1]=temp;
		//cout<<H[0]<<" "<<H[pos-1]<<" ";
		pos-=1;
		//cout<<"Heap: ";
	for(int i=0;i<n;i++){
		//cout<<H[i]<<" ";
	}
	//cout<<"Pos= "<<pos<<endl;
		fixheap(H[0],1,pos);
	}
	cout<<"Sorted Array: ";
	for(int i=0;i<n;i++){
		cout<<H[i]<<" ";
	}
	cout<<endl;
}