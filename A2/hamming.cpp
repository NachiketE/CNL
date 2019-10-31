#include<iostream>
#include<string>
#include<bits/stdc++.h>
using namespace std;

class hamming{
	string userdata,dataword,codeword;
	int rbits,nbits,total;
	char par;
	
	public:
	hamming()
	{
		cout<<"Enter the parity(o for even/e for odd)"<<endl;
		cin>>par;
		cout<<"Enter the data"<<endl;
		cin>>userdata;
		cout<<"User data in ascii value :";
		int len=userdata.size();
		for(int i=0;i<len;i++)
		{
			cout<<(int)userdata[i]<<"\t";
		}
		cout<<endl;
	}
	void binary_conversion()
	{
		int ascii;
		string temp="";
		for(int i=0;i<userdata.size();i++)
		{
			ascii=(int)userdata[i];
			while(ascii!=0)
			{
				if(ascii%2==0)
				{
					temp.push_back('0');
				}
				else
				{
					temp.push_back('1');
				}
				ascii=ascii/2;
			}
		}
		reverse(temp.begin(),temp.end());
		dataword=dataword+temp;
		cout<<"Binary value of userdata"<<endl;
		for(int i=0;i<dataword.size();i++)
		{
			cout<<dataword[i];
		}
		cout<<endl;
	}
	
	void codeword_generation()
	{
		int len=dataword.size();
		cout<<"Number of data bits are: "<<dataword.size()<<endl;
		//Calculating the number of redunduncy bits
		int r=0;
		while(pow(2,r)<=len+r+1)
		{
			r++;
		}
		rbits=r;
		cout<<"Number of redunduncy bits are: "<<rbits<<endl;
		total=len+rbits;
		cout<<"Total length of codeword is: "<<total<<endl;
		cout<<"Codeword without the parity bits is:"<<endl;
		int d=0;
		int d1=0;
		int a;
		cout<<setw(5);
		for(int i=1;i<=total;i++)
		{
			if(i==pow(2,d))
			{
				a=i-1;
				codeword[a]='-';
				cout<<"P"<<i<<setw(5);
				d++;
			}
			else
			{
				a=i-1;
				codeword[a]=dataword[d1];
				cout<<"D"<<i<<setw(5);
				d1++;
			}
		}
		cout<<endl;
		
		for(int k=0;k<total;k++)
		{
			cout<<codeword[k]<<setw(6);
		}
	//	cout<<"size of codeword: just after "<<codeword.size();
		cout<<endl;
		
		//Parity bits calculation
		d1=0;
		int min=0;
		int max=0;
		int s,j,parity;
		for(int i=1; i<=total; i=pow(2,d1))
		{
			++d1;
			parity=0;
			s=i;
			j=i;
			min=1;
			max=i;
			for(j; j<=total;)
			{
				for(s=j; max>=min && s<=total; ++min,++s)
				{
					int a=s-1;
					if(codeword[a]=='1')
						parity++;
				}
				j=s+i;
				min=1;
			}
			if(par=='e')	//Even parity
			{	
				if(parity%2==0)
				{
					int a=i-1;
					codeword[a]='0';
				}
				else
				{
					int a=i-1;
					codeword[a]='1';
				}
			}
			else	//Odd parity
			{
				if(parity%2==0)
				{
					int a=i-1;
					codeword[a]='1';
				}
				else
				{
					int a=i-1;
					codeword[a]='0';
				}
			}
	}
	cout<<"Codeword with parity buts is: "<<endl;
	display();
	}
	
	void display()
	{
		int d1=0;
		int d=0;
		cout<<setw(5);
		for(int i=1;i<=total;i++)
		{
			if(i==pow(2,d1))
			{
				cout<<"P"<<i<<setw(5);
				d1++;
			}
			else
			{
				cout<<"D"<<i<<setw(5);
				d++;
			}
		}
		cout<<endl;
		for(int i=0;i<total;i++)
		{
			cout<<codeword[i]<<setw(6);
		}
		cout<<endl;
	}
	void send_codeword()
	{
		int choice;
		cout<<"Send data with 1-bit error"<<endl;
		cout<<"Send error-free data"<<endl;
		cout<<"Enter your choice"<<endl;
		cin>>choice;
		if(choice==1)
		{
			int bit;
			cout<<"Enter the bit position to be altered: ";
			cin>>bit;
			if(codeword[bit-1]=='0')
				codeword[bit-1]='1';
			else
				codeword[bit-1]='0';
		
			cout<<endl;
			cout<<"Codeword after introducing error-bit: "<<endl;
			display();
			cout<<endl;
		}
		cout<<"Sending codeword...."<<endl;
		recieve_codeword();
	}
	void recieve_codeword()
	{
		cout<<"Recieving codeword....."<<endl;
		cout<<"The codeword revieved is: "<<endl;
		display();
		cout<<"Rechecking the parity..."<<endl;
		parity_calc();
		cout<<endl;
	}
	void parity_calc()
	{
		int d1=0;
		int min=0;
		int max=0;
		int s,j,parity;
		string q="";
		for(int i=1; i<=total; i=pow(2,d1))
		{
			++d1;
			parity=0;
			s=i;
			j=i;
			min=1;
			max=i;
			for(j; j<=total; )
			{
				for(s=j; max>=min && s<=total; ++min, ++s)
				{
					int a=s-1;
					if(codeword[a]=='1')
						parity++;
				}
				j= s+ i;
				min=1;
			}
			if(par=='e')	//even parity
			{
				if(parity%2==0)
				{
					cout<<"P"<<i<<"=0"<<endl;
					q.push_back('0');
				}
				else
				{
					cout<<"P"<<i<<"=1"<<endl;
					q.push_back('1');
				}	
			}
			else
			{
				if(parity%2==0)
				{
					cout<<"P"<<i<<"=1"<<endl;
					q.push_back('1');
				}
				else
				{
					cout<<"P"<<i<<"=0"<<endl;
					q.push_back('0');
				}	
			}
		}
			cout<<"Error position in binary: ";
			reverse(q.begin(),q.end());
			for(int i=0;i<rbits;i++)
			{
				cout<<q[i];
			}
			cout<<endl;
			reverse(q.begin(),q.end());
			//calculating the position
			int pos=0;
			for(int i=0;i<rbits;i++)
			{
				if(q[i]=='1')
				{
					pos=pos+pow(2,i);
				}
			}
			if(pos==0)
			{
				cout<<"No error in codeword recieved..."<<endl;
			}
			else
			{
				cout<<"Error detected at position: "<<pos<<endl;
				int a=pos-1;
				if(codeword[a]=='1')
					codeword[a]='0';
				else
					codeword[a]='1';
				cout<<"Codeword after corretion: "<<endl;
				display();
			}
		}
};
int main()
{
	hamming obj;
	obj.binary_conversion();
	obj.codeword_generation();
	obj.send_codeword();
return 0;
}
