 
//compile using g++ -std=c++11 

#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
int main()
{
    int nf,N;
    int no_tr=0;
    srand(time(NULL));
    cout<<"Enter the number of frames : ";
    cin>>nf;  //frame size
    cout<<"Enter the Window Size : ";
    cin>>N;  //window size
    int i=1;
    while(i<=nf) 
    {
        int x=0;

        //sending frame
        //server
        for(int j=i;j<i+N && j<=nf;j++) //sending frame of size of window
        {
            cout<<"Sent Frame "<<j<<endl;
            no_tr++; //incrementing the number of transmitted frame
        }
        //client side
        //receiving frame
        for(int j=i;j<i+N && j<=nf;j++)  //receving frame of size of window one by one
        {  
            int flag = rand()%2;  //rand() function is from cstdlib which generates random number btw 0 and RAND_MAX = 2147483647
            //The flag is used to simulate whether the packet is received sender side or not
            if(!flag)
                {
                    cout<<"Acknowledgment for Frame "<<j<<endl;
                    x++;
                }
            else
                {   cout<<"Frame "<<j<<" Not Received"<<endl;
                    cout<<"Retransmitting Window"<<endl;
                    break;
                }
        }
        cout<<endl;
        i+=x;
    }
    cout<<"Total number of transmissions : "<<no_tr<<endl;
    return 0;
}
