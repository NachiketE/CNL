//SERVER
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
using namespace std;

#define PORT 3206
#define buflen 1000;


int main() 
{

	struct sockaddr_in server_addr,client_addr;
	cout<<"\nUDP Server\nNote:-For receiving data, First Select Receive Option And then Select Send Option";

	//step 1: Creating Socket
	int sock;
	if((sock=socket(AF_INET,SOCK_DGRAM,0))==-1) //SOCK_DGRAM= SOCKET Type is datagram, AF_INET= Domain, Adress family
		//if the protocol is unspecified (a value of 0), the system selects a protocol that supports the requested socket type.
	{											//0=PACKET TYPE USUALLY 0 or (IPPROTo_UDP)
		cout<<"SOCKET CREATE ERROR";
	}
	//specify server address type, port as 8999 and address
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT); 
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY); //INADDR_ANY takes current IP Address of PC
	//htons() converts the unsigned short i	nteger hostshort from host byte order to network byte order.

	//BINDING socket to port
	if(bind(sock,(struct sockaddr *)&server_addr,sizeof(server_addr))==-1)   //sock= socket(socket descriptor)
		cout<<"BINDIND ERROR";
	else
		cout<<"\nUDP SERVER STARTED.";

	int client_len=sizeof(client_addr);
	// socklen_t is a type definition for length and size values used by socket related parameters, return values and structure 		members. Such definitions are used to allow platform independant source files. The header file where it is defined (sys/socket.h) 		may use different definitions according to the target platform (e.g. for 16, 32, and 64 bit CPUs).

	socklen_t cli=sizeof(client_addr);
	int choice,msg_len;
	char buffer[1000];
	bzero((char *)buffer,sizeof(buffer));	
	//ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
               //struct sockaddr *src_addr, socklen_t *addrlen)
	msg_len=recvfrom(sock,buffer,1000,0,(struct sockaddr *)&client_addr,&cli);

	if(msg_len>0)
	{
		cout<<"Client :- "<<buffer<<endl;
		bzero((char *)buffer,sizeof(buffer));

	}
	do
	{
		cout<<"\nMENU\n1. CHAT \n2.SEND FILE\n3.Receive File\n0.EXIT\nEnter your choice:";

		cin>>choice;
		switch(choice)
		{
		case 1:
			int n;
			while(1)
			{
				bzero((char *)buffer,sizeof(buffer));
				msg_len=recvfrom(sock,buffer,1000,0,(struct sockaddr *)&client_addr,&cli);

				if(msg_len>0)
				{
					cout<<"Client :- "<<buffer<<endl;
					bzero((char *)buffer,sizeof(buffer));

				}
				cout<<"\nEnter Reply:";
				cin.getline(buffer,sizeof(buffer));
				msg_len=sendto(sock,buffer,strlen(buffer),0,(struct sockaddr *)&client_addr,client_len);
				if(msg_len<0)
				{
					cout<<"Sending error"<<endl;
				}
				if(strcmp(buffer,"bye")==0)
					break;
				bzero((char *)buffer,sizeof(buffer));
			}
			break;

		case 2:
		{
			cout<<"\nEnter Filename:";
			char filename[100];
			cin>>filename;
			fstream fout;
			fout.open(filename,ios::in|ios::out|ios::binary);
			fout.seekg(0,ios::end);
			int filesize=fout.tellg(); //get file size
			char *filebuff=new char[filesize];
			fout.seekg(0,ios::beg);
			fout.read(filebuff,filesize); //reading file content

			msg_len=sendto(sock,filename,strlen(filename),0,(struct sockaddr *)&client_addr,client_len); //send filename
						if(msg_len==-1)
							cout<<"Filename error";

			msg_len=sendto(sock,(void *)&filesize,sizeof(filesize),0,(struct sockaddr *)&client_addr,client_len); //send filesize
			if(msg_len==-1)
				cout<<"Filesize error";



			msg_len=sendto(sock,filebuff,filesize,0,(struct sockaddr *)&client_addr,client_len); //send file conetents
			if(msg_len==-1)
				cout<<"File transmission error";
			else
				cout<<"Transmission Successful";
			fout.close();
		}
		break;
		case 3:
		{
			char filename[100];
			bzero((char *)filename,sizeof(filename));
			msg_len=recvfrom(sock,filename,99,0,(struct sockaddr*)&client_addr,&cli);
			if(msg_len==-1)
				cout<<"Filename error";
			cout<<"\nFilename:"<<filename;

			int filesize;
			msg_len=recvfrom(sock,(void *)&filesize,sizeof(filesize),0,(struct sockaddr*)&client_addr,&cli);
			cout<<"\nFileSize:"<<filesize;
			char *filebuff=new char[filesize];


			bzero((char *)filebuff,sizeof(filebuff));
			msg_len=recvfrom(sock,filebuff,filesize,0,(struct sockaddr*)&client_addr,&cli);
			ofstream fout1;
			fout1.open(filename,ios::out|ios::binary);
			if(!fout1)
			cout<<"CANNOT CREATE FILE";
			else
			{
				fout1.write(filebuff,filesize);
				fout1.close();
				cout<<"File received";
			}
		}
	    break;
		}
	}while(choice!=0);
close(sock);
	return 0;
}


