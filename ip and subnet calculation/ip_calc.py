#!/usr/bin/env python
import ipaddress
import sys

for arg in sys.argv[1:]:
    print(arg)    
    addr = ipaddress.ip_interface(arg)  
    print("IP address =", addr.ip)
    print("Netmask =", addr.netmask)
    print("Network Address =", addr.network.network_address)
    print("Broadcast Address=", addr.network.broadcast_address)
    start_ip = addr.network.network_address + 1
    end_ip = addr.network.broadcast_address - 1
    print("Range:",start_ip,"to",end_ip)
    print("Max Nodes:",addr.network.num_addresses-2)
    print()
