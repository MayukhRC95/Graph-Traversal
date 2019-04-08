/* 
*/
#include <cstdlib> 
#include <iostream>
using namespace std;
int *H;
void fixheap(int a, int pos, int end)
{
	int temp,check=-1;
	if(a>H[pos/2-1] && pos!=1){
		temp=H[pos/2-1];
		H[pos/2-1]=a;
		H[pos-1]=temp;
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
		fixheap(a,pos,end);
	}
}
void insert(int a, int pos)
{
	H[pos]=a;
	// cout<<"Inside Insert"<<H[pos+1]<<endl;
	fixheap(a,pos+1,pos+1);
}
int max()
{
	return H[0];
}
void Delete(int del, int pos)
{
	H[del-1]=H[pos-1];
	fixheap(H[del-1],del,pos-1);
}
int main()
{
	int n,pos=0;
	cout<<"Enter the no of elements:"<<endl;
	cin>>n;
	H= new int[n];
	for(int i=0;i<n-3;i++)
	{
		int a= rand()%10;
		cout<<i<<"th"<<a<<endl;
		insert(a,pos);
		pos+=1;
	}
	int m= max();
	cout<<"Maximum "<<m<<endl;
	for(int i=1;i<=pos;i++)
	{
		cout<<H[i-1];
	}
	cout<<endl;
	int del=2;
	cout<<"Delete "<<del<<" position"<<endl;
	if(del<pos){
		Delete(del,pos);
	  pos-=1;
	  for(int i=1;i<=pos;i++)
		{
			cout<<H[i-1];
		}
		cout<<endl;
	}
	else{
		cout<<"empty heap"<<endl;
	}
	return 0;
}