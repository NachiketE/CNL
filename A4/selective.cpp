
//compile using g++ -std=c++11 if g++ doesn't work
/*
Author : Robert Langdon
Date : 22/10/19
Program for selective repeat
Logic behind the program is the receiver and the sender both have the same window_size.
Meaning the sender can send packets in the number of window_size and the receiver can receive the same
If a single frame is dropped only that frame with the remaining frame is send and not the whole window as in case of go-back-n
Steps:
1.Get the no.of frames from the user
2.Get the window_size from the user
3.initialize the frame_count to zero and also no_tr(no of transactions) to zero 
4.Sender sends the packets whose acknowledgement is not received in batch size of window_size to the receiver and initialize sent_count by 1
5.If the receiver receives the frame it sends the acknowledgment
6.The packets whose acknowledgement is not received by the sender will be send back again with the remaining
  in the size of window_size and frame_count would be increased by 1 for each packet received
7.If frame_count is not equal to  frame_size jump to step 4
8.Print the sent_count
*/

//I think this code would be easier with python..just a thought..using list

#include<iostream>
#include<ctime>
#include<cstdlib>
#include <bits/stdc++.h> 


using namespace std;

int main()
{
    int frame_size,window_size;
    srand(time(NULL));
    //Get the frame and window_size from user
    cout<<"Enter the number of frames : ";
    cin>>frame_size;  //frame size
    cout<<"Enter the Window Size : ";
    cin>>window_size;  //window size
    int dropped_packet[frame_size+1];  //packets which were dropped
    int ack_received = 0; // total no. of acknowlegdment received
    int no_tr = 0 ; // no.of transactions
    int i;
    int last_packet = 0;
    int last_packet_copy = last_packet;
    int insert_here = 1;
    for(int j = 0 ; j <=frame_size; j++){
        dropped_packet[j] = MAX_INPUT;
    }
    int count;
    while(ack_received != frame_size) {
            //sent those frame  whose acknoledgemnt is not received in order to user in size of window_size or less
            count = ack_received; 
            for(i = 1 ; i <= window_size && count!=frame_size; i++ ){
                if(dropped_packet[i] != MAX_INPUT){
                    cout << "Frame sent " << dropped_packet[i] << endl;
                    count++;
                }else{
                    if(last_packet +1 > frame_size)
                        break;
                    cout << "Frame sent " << last_packet + 1<< endl;
                    last_packet ++;
                }
                no_tr++;
            }
            cout << endl;


            //Receiving the packets and sending acknowledgement
            for(i = 1 ; i <= window_size && ack_received !=frame_size;i++){
                int flag = rand()%2;
                if(!flag){ // Frame received
                    if(dropped_packet[i] != MAX_INPUT){
                        cout << "Acknowledgement from frame " << dropped_packet[i]  << " Received"<<  endl;
                        dropped_packet[i] = MAX_INPUT;
                    }
                    else{
                        if(last_packet_copy +1 > frame_size)
                            break;
                        cout << "Acknowledgement from frame " << last_packet_copy + 1  << " Received"<< endl;
                        last_packet_copy++;
                    }
                    ack_received++;
                }else{ //frame dropped
                    if(dropped_packet[i] != MAX_INPUT){
                        cout << "Frame " << dropped_packet[i]  << " Dropped" << endl;
                    }
                    else{
                        if(last_packet_copy + 1 > frame_size)
                            break;
                        cout << "Frame " << last_packet_copy + 1 << " Dropped"  << endl;
                        dropped_packet[insert_here] = last_packet_copy +1;
                        insert_here++;
                        last_packet_copy++;
                    }
                }
            }
            
            int n = sizeof(dropped_packet)/sizeof(dropped_packet[0]); 
            sort(dropped_packet+1, dropped_packet+n); 
            last_packet_copy = last_packet;
            for(i = 1 ; i <=frame_size;i++){
                if(dropped_packet[i] == MAX_INPUT){
                    insert_here = i;
                    break;
                }
            }
            cout << endl;
    }
    cout<<"Total number of transmissions : "<<no_tr<<endl;
    return 0;
}
