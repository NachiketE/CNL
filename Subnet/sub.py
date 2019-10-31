import sys

#take the address and cidr
(addrString,cidrString)=sys.argv[1].split('/')

#conver addrString to a list and cidrString to integer
addr=addrString.split('.')
cidr=int(cidrString)

firstoctet=int(addr[0])

if firstoctet>=0 and firstoctet<=127:
	print("Class: A ,  Default subnet: 255.0.0.0")

if firstoctet>=128 and firstoctet<=191:
	print("Class: B,  Default subnet: 255.255.0.0")
	
if firstoctet>=192 and firstoctet<=223:
	print("Class: C,  Default subnet: 255.255.255.0")
	
if firstoctet>=224 and firstoctet<=239:
	print("Class: D")
	
if firstoctet>=240 and firstoctet<=255:
	print("Class: E")
	
#calculate the subnet mask
mask=[0,0,0,0]
for i in range(cidr):
	mask[int(i/8)]= mask[int(i/8)]+ (1<<(7-i%8))
	
print("Subnet mask: ", ".".join(map(str,mask)))

#calculate the network address
net=[]
for i in range(4):
	net.append(int(addr[i]) &mask[i])
	
print("Network address: ", ".".join(map(str,net)))

#calculating the subnets
if firstoctet>=0 and firstoctet<=127:
	max_host=pow(2,int(32-cidr))
	print("Host/subnet: ", max_host)
	ones=cidr-8
	subnets=pow(2,ones)
	print("Number of subnets :", subnets)

if firstoctet>=128 and firstoctet<=191:
	max_host=pow(2,int(32-cidr))
	print("Host/subnet: ", max_host)
	ones=cidr-16
	subnets=pow(2,ones)
	print("Number of subnets :", subnets)
	
if firstoctet>=192 and firstoctet<=223:
	max_host=pow(2,int(32-cidr))
	print("Host/subnet: ", max_host)
	ones=cidr-24
	subnets=pow(2,ones)
	print("Number of subnets :", subnets)
	
	lb=[]
	ub=[]
	for i in range(3):
		lb.append(0)
		ub.append(0)
	for i in range(3):
		lb[i]=int(addr[i])
		ub[i]=int(addr[i])
	
	ll=[]
	ul=[]
	for i in range(subnets):
		ll.append(0)
		ul.append(0)
	
	max1=max_host
	print(max1)
	for i in range(subnets):
		while max1<=256:
			ll[i]=max1-max_host
			ul[i]=max1-1
			print("Subnet",i,":",". ".join(map(str,lb)),".",ll[i],"  -->  ",". ".join(map(str,ub)),".",ul[i])
			max1=max1+max_host
	
		
