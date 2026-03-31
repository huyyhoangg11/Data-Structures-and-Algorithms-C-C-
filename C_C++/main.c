#include <stdio.h>
#include <arpa/inet.h>
int main() {
    printf("%X",htonl(0x1A2B3C4D));  // hton = host to network
    return 0;
}