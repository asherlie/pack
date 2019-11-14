#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if_packet.h>
#include <linux/if.h>
#include <string.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

#include <errno.h>

#include <stdio.h>

int main(){
      int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

      char buf[] = "msg0";

      struct sockaddr_ll dest;
      memset(&dest, 0, sizeof(struct sockaddr_ll));
      dest.sll_family = AF_PACKET;
      dest.sll_protocol = htons(ETH_P_ALL);
      /*dest.sll_protocol = AF_PACKET;*/
      /*
       *dest.sll_addr[0+2] = 0x74;
       *dest.sll_addr[1+2] = 0xe5;
       *dest.sll_addr[2+2] = 0x0b;
       *dest.sll_addr[3+2] = 0xb5;
       *dest.sll_addr[4+2] = 0x5b;
       *dest.sll_addr[5+2] = 0x08;
       */

      /*
       * this one
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

      struct ifreq ifr;
      strcpy(ifr.ifr_name, "lo");
      /*strcpy(ifr.ifr_name, "wlp3s0");*/

      if(ioctl(sock, SIOCGIFINDEX, &ifr) == -1)perror("ioctl");

      dest.sll_ifindex = ifr.ifr_ifindex;
      dest.sll_halen = 6;

      int x = sendto(sock, buf, 4, 0, (struct sockaddr*)&dest, sizeof(struct sockaddr_ll));
      if(x == -1)perror("sendto");
}
