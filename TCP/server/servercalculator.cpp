#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<bits/stdc++.h>
#include<string.h>
#include<errno.h>
#include<stdbool.h>
#include<math.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 8649
using namespace std;
void calculator(int newsd)
{
	char ch[2],choice,a[5],re[9];
	
	//recieving the angle and choice of operation from client
	recv(newsd,(char*)&a,sizeof(a),0);
	cout<<"angle recieved:"<<a<<endl;
	recv(newsd,(char*)&ch,sizeof(ch),0);
	choice=ch[0];
	float angle=(float)atof(a);
	cout<<"angle(float)"<<angle<<endl;
	while(angle>360)
	{
		angle=angle-360;
	}
	angle=angle*(3.14/180);
	cout<<"angle(radian)"<<angle<<endl;
	float result=0;
	switch(choice)
	{
		case '1': result=sin(angle);
			break;
		case '2': result=cos(angle);
			break;
		case '3': result=tan(angle);
			break;
		case '4': result=1/(tan(angle));
			break;
		case '5': result=1/(cos(angle));
			break;
		case '6': result=1/(sin(angle));
			break;
	}
	cout<<"result:"<<result<<endl;
	memset(&re,'\0',9);
	gcvt(result,9,re);
	send(newsd,(char*)&re,sizeof(re),0);
	
}
int main()
{
	int sd,newsd;
	socklen_t lenc;
	sockaddr_in server,client;

	//create a socket
	sd=socket(AF_INET,SOCK_STREAM,0);
	if(sd==-1)
	{
		cout<<"Socket not created"<<endl;
		cout<<strerror(errno)<<endl;
		exit(0);
	}
	else
	{
		cout<<"Socket created!"<<endl;
	}
	//configure the sockadd_in
	bzero(&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(PORT);
	memset((&server.sin_zero),'\0',8);

	//now bind the server to the socket
	if(bind(sd,(struct sockaddr*)&server,sizeof(server))<0)
	{
		cout<<"Socket not binded"<<endl;
	}
	else
	{
		cout<<"Socket binded"<<endl;
	}
	listen(sd,5);
	//accepting the client socket
	lenc=sizeof(client);
	newsd=accept(sd,(struct sockaddr*)&client,&lenc);
	if(newsd<0)
	{
		cout<<"Error in connection with client"<<endl;
		cout<<strerror(errno)<<endl;
		exit(0);
	}
	else
	{
		cout<<"Connected to client."<<endl;
	}
	char ch[2],choice;
	do
	{
		recv(newsd,(char*)&ch,sizeof(ch),0);
		choice=ch[0];
		switch(choice)
		{
			case '1': //caculator
				calculator(newsd);
				break;
			case '2': break;
		}
	}while(choice!='2');
	close(sd);
	close(newsd);
return 0;
}
























