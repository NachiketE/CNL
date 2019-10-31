#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 8649
using namespace std;
void calculator(int sd)
{
	char ch[2],choice;
	char a[5],re[9];
	cout<<"Enter angle in degrees"<<endl;
	cin>>a;
	send(sd,(char*)&a,sizeof(a),0);
	cout<<"Enter choice:"<<endl;
	cout<<"1.Sine\t2.Cos\t3.tan\t4.cot\t5.sec\t6.cosec"<<endl;
	cin>>ch;
	choice=ch[0];
	//sending the choice of operation
	send(sd,(char*)&choice,sizeof(choice),0);
	//recieving the result
	memset(&re,'\0',10);
	recv(sd,(char*)&re,sizeof(re),0);
	cout<<"result:\t"<<re;
}

int main()
{
	int sd,newsd;
	sockaddr_in server,client;
	socklen_t lens;
	//creation of the socket
	sd=socket(AF_INET,SOCK_STREAM,0);
	if(sd==-1)
	{
		cout<<"socket not created"<<endl;
		cout<<strerror(errno)<<endl;
		exit(0);
	}
	else
	{
		cout<<"Socket created"<<endl;
	}
	//configure the server 
	bzero(&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(PORT);
	memset((&server.sin_zero),'\0',8);
	//connect to the server
	lens=sizeof(server);
	if(connect(sd,(struct sockaddr*)&server,lens)<0)
	{
		cout<<"Error in connection with server"<<endl;
		cout<<strerror(errno)<<endl;
		exit(0);		
	}
	else
	{
		cout<<"Connected with the server"<<endl;
	}
	char ch[2],choice;
	do
	{
		cout<<"Enter choice:"<<endl;
		cout<<"1. Trigonometric calculator\t 2.exit"<<endl;
		cin>>ch;
		choice=ch[0];
		send(sd,(char*)&choice,sizeof(choice),0);
		switch(choice)
		{
			case '1': //calculator
					calculator(sd);
					break;
			case '2': break;
		}
	}while(choice!='2');
close(sd);
	
}














