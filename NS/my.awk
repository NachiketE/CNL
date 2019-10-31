BEGIN{
pktdrop=0;
k=0;
total=0;
}
{
event =$1;
e=$5;
total++;
if(event=="d")
{
if(e=="cbr" ||e=="tcp" ||e="tcp1"||e=="udp"||e=="ftp1")
k++;
pktdrop++;
}
}
END{
printf("no of packets dropped is %d\n",pktdrop);
printf("no of UDP packets dropped is %d\n",k);
printf("no of TCP packets dropped is %d\n",pktdrop-k);
printf("Total packets are %d\n",total);
printf("Throughput is %d\n",(total-pktdrop)/total);
}
