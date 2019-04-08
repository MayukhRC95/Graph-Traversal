/* HeapSort
*/
#include<iostream>
#include<cstlib>
using namespace std;
int *H;
void fixheap(int a, int pos, int end)
{
	int check,temp;
	while(pos!=1)
	{
		check=-1;
		if(a>H[pos/2-1])
		{
			temp=H[pos/2-1];
			H[pos/2-1]=a;
			H[pos-1]=temp;
			check=1;
		}
		if(check==-1)
		{
			break;
		}
		pos=pos/2;
	}
		while(pos!=end)
		{
			check=-1;
			if(a<H[2*pos-1] || a<H[2*pos])
			{
				temp=H[pos-1];
				if(H[2*pos-1]>H[2*pos])
				{
					H[pos-1]=H[2*pos-1];
					pos=2*pos-1;
				}
				else
				{
					H[pos-1]=H[2*pos];
					pos=2*pos;
				}
				check=1;
			}
			if(check==-1)
			{
				break;
			}
		}
	}
void insert(int a, int pos)
{
	H[pos]=a;
	// cout<<"Inside Insert"<<H[pos+1]<<endl;
	fixheap(a,pos+1,pos+1);
}
int main()
{
	int n,pos=0;
	cout<<"Enter the no of elements:"<<endl;
	cin>>n;
	H= new int[n];
	cout<<"Original array"<<endl;
	for(int i=0;i<n;i++)
	{
		int a= rand()%10;
		cout<<a<<" ";
		insert(a,pos);
		pos+=1;
	}
	cout<<endl
	//pos-=1;
	for(int i=0;i<n;i++){
		int temp=H[0];
		H[0]=H[pos-1];
		H[pos-1]=temp;
		pos-=1;
		fixheap(H[0],1,pos+1);
	}
	for(int i=0;i<n;i++){
		cout<<H[i]<<" ";
	}
}