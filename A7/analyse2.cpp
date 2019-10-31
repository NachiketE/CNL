#include <iostream>
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <net/ethernet.h>

using namespace std;

void packetHandler(u_char *user, const struct pcap_pkthdr *h,const u_char *packet);

int tcpcount = 0;
int udpcount = 0;
int ipcount = 0;
int ipv6count = 0;
int ethercount = 0;
int icmpcount = 0;
int arpcount = 0;

int main()
{
    pcap_t *fp;
    char errbuf[PCAP_ERRBUF_SIZE];

    fp = pcap_open_offline("CapturedPacketspcap.pcap", errbuf);
    pcap_loop(fp, 0, packetHandler, NULL);

    cout<<"tcpcount: "<<tcpcount<<endl;
    cout<<"udpcount: "<<udpcount<<endl;
    cout<<"ipv6count: "<<ipv6count<<endl;
        cout<<"ipcount: "<<ipcount<<endl;
    cout<<"ethercount: "<<ethercount<<endl;
    cout<<"arpcount: "<<arpcount<<endl;
}


void packetHandler(u_char *user, const struct pcap_pkthdr *h,const u_char *packet){
    const struct ether_header* etherHeader;
    const struct ip* ipheader;
    etherHeader=(struct ether_header *)packet;
    ethercount++;
    if(ntohs(etherHeader->ether_type)==ETHERTYPE_IP){
        ipcount++;
        ipheader = (struct ip*)(packet+ sizeof(ether_header));
        if(ipheader->ip_p==IPPROTO_UDP)
        udpcount++;
        if(ipheader->ip_p==IPPROTO_TCP)
        tcpcount++;
    }
    if(ntohs(etherHeader->ether_type)==ETHERTYPE_ARP){
    arpcount++;
    }
        if(ntohs(etherHeader->ether_type)==ETHERTYPE_IPV6){
            ipv6count++;
        }
        



}
