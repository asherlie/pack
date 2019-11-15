#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <string.h>
#include "shared.h"

#include <stdio.h>

_Bool verify_header(char* buf){
      for(int i = 0; i < 8; ++i)
            if(buf[i] != header[i])return 0;
      return 1;
}

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

            if(verify_header(buf)){

                  printf("\n------------------------------\n%i bytes recvd\n",
                        len-8);
                  for(int i = 8; i < len; ++i){
                        if(i%8 ==  0)putchar('\n');
                        printf((buf[i] < 0) ? "%.3i " : "%.4i ", buf[i]);
                  }

            }
            /*printf("%i\n", len);*/
      }
      return 0;
}
