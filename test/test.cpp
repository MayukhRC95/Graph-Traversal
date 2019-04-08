/* Test continue function in loop*/
#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{
	int in,n,c=0,*a,cont;
	cout<<"enter size"<<endl;
	cin>>n;
	a=new int[n];
	while(c<n)
	{
		cont=0;
		cout<<"enter input"<<endl;
		cin>>in;
		for(int i=0;i<=c;i++)
		{
			if(in==a[i])
			{
				cont=1;
			}
		}
		if(cont==1)
		{
			cout<<"enter different number"<<endl;
			continue;
		}
		else
		{
			a[c]=in;
		}
		c++;
	}
	for(int i=0;i<n;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}