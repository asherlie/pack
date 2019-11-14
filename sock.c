#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <string.h>

#include <stdio.h>

int main(){
      int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

      char buf[1000];
      struct sockaddr_ll from;
      socklen_t sz = sizeof(struct sockaddr_ll);

      while(1){
            memset(buf, 0, 1000);

            int len = recvfrom(sock, &buf, 1000, 0, (struct sockaddr*)&from, &sz);
            /*
             * printf("addr: ");
             * for(int i = 0; i < 8; ++i)printf("%i ", from.sll_addr[i]);
             * puts("");
            */

            if((from.sll_addr[0] == 0x98 ||
               from.sll_addr[0] == 0xdc ||
               from.sll_addr[0] == 0x0a ||
               *buf == 'f') &&
               len == 4){
                  puts("YA");

                  printf("%i: \"%s\"\n", len, buf);
            }
            /*printf("%i\n", len);*/
      }
      return 0;
}
