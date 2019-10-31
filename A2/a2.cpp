#include<iostream>
#include<string>
using namespace std;

class CRC{
	private:
	  string input;
	  string divisor;
	  int len_input;
	  int len_gen;
	  string dividend;
	  int r;
	  int len_dividend;
	  string result;
	  string received;
	public:

	  string fun_xor(string a,string b){
	    int len = len_gen;
	    string res="";
	    if(a[0]=='0'){
	      b="";
	      for(int i=0;i<len;i++){
		b = b + "0";
	      }
	    }
	    for(int i=0;i<len;i++){
	      res = res + (a[i]==b[i]?"0":"1");
	    }
	    return res.substr(1);
	  }

	  void getData(){
	    cout<<"Enter the input: ";
	    cin>>input;
	    cout<<"Enter the generator polynomial: ";
	    cin>>divisor;
	    len_input = input.length();
	    len_gen = divisor.length();
	    r = len_gen - 1;
	    dividend = input;
	    for(int i=0;i<r;i++){
	      dividend = dividend + "0";
	    }
	    len_dividend = dividend.length();
	    // cout<<input<<" "<<len_input<<" "<<divisor<<" "<<len_gen<<" "<<dividend<<" "<<len_dividend<<endl;
	    modulo_div();
	  }

	  void modulo_div(){

	    string temp = dividend.substr(0,len_gen);
	    int j = len_gen;
	    while(j<len_dividend){
	      temp = fun_xor(temp,divisor);
	      temp = temp + dividend[j];
	      j++;
	    }
	    temp = fun_xor(temp,divisor);
	    result = input + temp;
	  }

	  void display_sender(){
	    cout<<"Data word to be sent: "<<input<<endl;
	    cout<<"Generator Polynomial: "<<divisor<<endl;
	    cout<<"Dividend: "<<dividend<<endl;
	    cout<<"CRC Code word sent: "<<result<<endl;
	  }

	  void receiverSide(){
	    cout<<"Enter the data word received: ";
	    cin>>received;
	    string temp = received.substr(0,len_gen);
	    int j = len_gen;
	    while(j<len_dividend){
	      temp = fun_xor(temp,divisor);
	      temp = temp + received[j];
	      j++;
	    }
	    temp = fun_xor(temp,divisor);
	    cout<<"Remainder is: "<<temp<<endl;
	    bool zero = true;
	    for(int i=0;i<len_gen-1;i++){
	      if(temp[i]=='1'){
		zero = false;
		break;
	      }
	    }
	    if(zero){
	      cout<<"No error induced!";
	    }
	    else{
	      cout<<"Error is induced!"<<endl;
	    }
	  }

};

int main(){
  CRC crc;
  crc.getData();
  crc.display_sender();
  crc.receiverSide();
}
