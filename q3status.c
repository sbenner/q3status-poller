#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <asm/poll.h>
#include <unistd.h>
#include <fcntl.h>
#include "q3status.h"


extern int save_status(q3stats_t *q3stats,PGconn * conn);
extern PGconn * pg_connect();


int main(int argc, char *argv[])
{
	int sockfd;
	int broadcast=1;
	struct sockaddr_in sendaddr;
	struct sockaddr_in recvaddr;
	int numbytes;

	struct pollfd pfd;
	if((sockfd = socket(PF_INET,SOCK_DGRAM,0)) == -1 )
	{
		perror("sockfd");
		exit(1);
	}
	if (fcntl(sockfd, F_SETFL, O_NONBLOCK) == -1) {
		printf("fcntl failed to O_NONBLOCK: %d", errno);
		return 0;
	}

	if((setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,
			&broadcast,sizeof broadcast)) == -1)
	{
		perror("setsockopt - SO_SOCKET ");
		exit(1);
	}

	if((setsockopt(sockfd,SOL_SOCKET,SO_DONTROUTE,
			&broadcast,sizeof broadcast)) == 32)
	{
		perror("setsockopt - SO_DONTROUTE");
		exit(1);
	}

	sendaddr.sin_family = AF_INET;
	sendaddr.sin_port = htons(10000);
	sendaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(sendaddr.sin_zero,'\0',sizeof sendaddr.sin_zero);

	if(bind(sockfd, (struct sockaddr*) &sendaddr, sizeof sendaddr) == -1)
	{
		perror("bind");
		exit(1);
	}

	recvaddr.sin_family = AF_INET;
	recvaddr.sin_port = htons(DEST_PORT);
	recvaddr.sin_addr.s_addr = inet_addr(DEST_ADDR);
	memset(recvaddr.sin_zero,'\0',sizeof recvaddr.sin_zero);

	char* woof;
	char buf[2048];
	woof= (char*)calloc(1,25);


	woof[0]='\xff';
	woof[1]='\xff';
	woof[2]='\xff';
	woof[3]='\xff';

	//strncat(woof,"rcon status",19);
	strncat(woof,"getstatus",14);
	size_t recvMsgSize=0;
	u_int snd = sizeof sendaddr;

	PGconn * conn = pg_connect();

	while((numbytes = sendto(sockfd, woof, 14 , 0,
			(struct sockaddr *)&recvaddr, sizeof recvaddr)) != -1)
	{
		bzero((void*)buf,2048);
		// printf("%d \n",numbytes);
		printf("###############################################\n");

		pfd.fd = sockfd;
		pfd.events = 0;
		pfd.events = pfd.events | POLLIN;
		pfd.events = pfd.events | POLLRDNORM;
		pfd.events = pfd.events | POLLRDBAND;
		pfd.events = pfd.events | POLLPRI;
		pfd.events = pfd.events | POLLERR;
		if (poll(&pfd, 1, 2000) < 0) // Blocks until VMQ event occurs. Use select() with other platforms.
		{
			printf("\n Poll failed");
			exit(1);
		}
		if ((pfd.revents & POLLERR) != 1){


			if ((recvMsgSize = recvfrom(sockfd, buf, 2048, 0,(struct sockaddr *)&sendaddr,&snd)) <= 0) {
				perror("recv() failed");
			}

			printf("%s \n", inet_ntoa(sendaddr.sin_addr));
			// printf("%s\n",buf);
			q3stats_t *q3 = showinfo(buf);


			save_status(q3,conn);

			printf("###############################################\n");

			sleep(2);
		}
	}
	perror("sendto");
	close(sockfd);

	return 0;
}
