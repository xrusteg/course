#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

struct frame {
	short send_port;
	short rcv_port;
	short length;
	short check_sum;
};

int main() {
	char msg1[] = "MESSAGE1";
	char buf[1024];
	int sock;
	struct sockaddr_in addr;
	struct frame frame1;
	
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if (sock < 0) {
		perror("socket");
		return 1;
	}
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	frame1.rcv_port = htons(3425);
	frame1.check_sum = 0;
	frame1.length = htons(sizeof(frame1) + sizeof(msg1));
	memcpy((void *)buf, (void *)&frame1, sizeof(frame1));
    	memcpy((void *)(buf + sizeof(frame1)), (void *) msg1, sizeof(msg1));
	sendto(sock, buf, sizeof(msg1) + sizeof(frame1), 0, (struct sockaddr *)&addr, sizeof(addr));

	close(sock);
	return 0;
}
