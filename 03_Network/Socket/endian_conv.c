#include <stdio.h>

int main(int argc, char **argv)
{
    short host_port_order = 0x1234;
    short net_port_order;

    long host_addr_order = 0x12345678;
    long net_addr_order;

    net_port_order = htons(host_port_order);
    net_addr_order = htonl(host_addr_order);

    printf("Host Order Port: %x \n", host_port_order);
    printf("Network Order Port: %x \n", net_port_order);

    printf("Host Order Address: %x \n", host_addr_order);
    printf("Network Order Address: %x \n", net_addr_order);

    return 0;
}