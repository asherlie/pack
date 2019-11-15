#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if_packet.h>
#include <linux/if.h>
#include <string.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

#include "shared.h"

#include <errno.h>
#include <stdio.h>

int main(int a, char** b){
      if(a == 1)return 0;
      int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

      char buf[64+8] = {0};
      /*printf("%i\n", sizeof(header));*/
      memcpy(buf, header, 8);
      strcpy(buf+8, b[1]);

      struct sockaddr_ll dest;
      memset(&dest, 0, sizeof(struct sockaddr_ll));
      dest.sll_family = AF_PACKET;
      dest.sll_protocol = htons(ETH_P_ALL);
      /*dest.sll_protocol = AF_PACKET;*/

      
      /*
       * dest.sll_addr[0+2] = 0x74;
       * dest.sll_addr[1+2] = 0xe5;
       * dest.sll_addr[2+2] = 0x0b;
       * dest.sll_addr[3+2] = 0xb5;
       * dest.sll_addr[4+2] = 0x5b;
       * dest.sll_addr[5+2] = 0x08;
      */

/*74:e5:0b:b5:5b:08*/
       /* this one or nothing - zeros should be localhost */
        /*
         * dest.sll_addr[0] = 0x74;
         * dest.sll_addr[1] = 0xe5;
         * dest.sll_addr[2] = 0x0b;
         * dest.sll_addr[3] = 0xb5;
         * dest.sll_addr[4] = 0x5b;
         * dest.sll_addr[5] = 0x08;
        */

      /*
       *dest.sll_addr[0] = 0xf0;
       *dest.sll_addr[1] = 0xde;
       *dest.sll_addr[2] = 0xf1;
       *dest.sll_addr[3] = 0xc3;
       *dest.sll_addr[4] = 0x4d;
       *dest.sll_addr[5] = 0x92;
       */

      struct ifreq ifr = {0};
      strcpy(ifr.ifr_name, "lo");
      strcpy(ifr.ifr_name, "wlp3s0");

      if(ioctl(sock, SIOCGIFINDEX, &ifr) == -1)perror("ioctl");
      /*printf("indx: %i\n", ifr.ifr_ifindex);*/
      struct ifreq ifr_hw = {0};
      strcpy(ifr_hw.ifr_name, "wlp3s0");
      if(ioctl(sock, SIOCGIFHWADDR, &ifr_hw) == -1)perror("ioctl");
      for(int i = 0; i < 8; ++i){
            printf("%i ", ifr_hw.ifr_hwaddr.sa_data[i]);
      }
      puts("");
      /*printf("%i\n", ifr_hw.ifr_hwaddr.sa_family);*/
      /*ifr_hw.ifr_hwaddr;*/

      dest.sll_ifindex = ifr.ifr_ifindex;
      dest.sll_halen = ETH_ALEN;

      int x = sendto(sock, buf, 64+8, 0, (struct sockaddr*)&dest, sizeof(struct sockaddr_ll));
      if(x == -1)perror("sendto");
}
