import sys

(addrString, cidrString) = sys.argv[1].split('/')
addr = addrString.split('.')
cidr = int(cidrString)

# Initialize the netmask and calculate based on CIDR mask
mask = [0, 0, 0, 0]
for i in range(cidr):
	mask[int(i/8)] = mask[int(i/8)] + (1 << (7 - i % 8))

# Initialize net and binary and netmask with addr to get network
net = []
for i in range(4):
	net.append(int(addr[i]) & mask[i])

# Duplicate net into broad array, gather host bits, and generate broadcast
broad = list(net)
brange = 32 - cidr
for i in range(brange):
	broad[3 - i//8] = broad[3 - i//8] + (1 << (i % 8))

#Finding out subnets
net_3 = net[3]
broad_3 = broad[3]
diff = broad_3 - net_3
num_subnets = (1<<(cidr - 24))
max = int((diff + 1) / num_subnets)

print(bin(net[3]).replace("0b",""))

#calculating subnet range, upper and lower bound
ll = []               #lower bound
ul = []		      #upper bound
for i in range(num_subnets):    #for-loop since we dont know how many subnets are there
	ll.append(0)	
	ul.append(0)

n_max = 0
max1 = int(max)
for i in range(num_subnets):
	n_max = n_max + max
	ll[i] = net[3] + n_max - max1		
	ul[i] = net[3] + n_max - 1 

#duplicating lb and ub list with broad for the first three values of the address
lb = []			
ub = []
for i in range(3):              #initializing
	lb.append(0)
	ub.append(0)

for i in range(3):
	lb[i] = broad[i]
	ub[i] = broad[i]	


# Print information, mapping integer lists to strings for easy printing
print ("Address:   " , addrString)
print ("Netmask:   " , ".".join(map(str, mask)))
print ("Network:   " , ".".join(map(str, net)))
print ("Broadcast: " , ".".join(map(str, broad)))
print ("SUBNETS: ")
for i in range(num_subnets):
	print("Subnet",i,":",". ".join(map(str,lb)),".",ll[i],"  -->  ",". ".join(map(str,ub)),".",ul[i])

