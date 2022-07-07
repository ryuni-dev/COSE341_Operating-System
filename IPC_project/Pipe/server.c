#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 100
#define NP_SEND "./server_to_client"
#define NP_RECEIVE "./client_to_server"

int main(void) {
	char receive_msg[BUFFER_SIZE], send_msg[BUFFER_SIZE];
	int receive_fd, send_fd;
	int value;

	/*---------------------------------------*/
	/* TODO 3 : make pipes and init fds      */
	/* (1) make NP_RECEIVE pipe              */
	/* (2) make NP_SEND pipe                 */
	/* (3) init receive_fd and send_fd       */
	
	if(access(NP_RECEIVE, F_OK) == 0){
		unlink(NP_RECEIVE);
	}
	if(mkfifo(NP_RECEIVE, 0666) == -1){
		printf("mkfifo of NP_RECEIVE error\n");
		return -1;
	}

	if(access(NP_SEND, F_OK) == 0){
		unlink(NP_SEND);
	}
	if(mkfifo(NP_SEND, 0666) == -1){
		printf("mkfifo of NP_SEND error\n");
		return -1;
	}
	
	if((receive_fd=open(NP_RECEIVE, O_RDWR)) == -1){
		printf("receive_fd open error!\n");
		return -1;
	}
	if((send_fd=open(NP_SEND, O_WRONLY)) == -1){
		printf("send_fd open error!\n");
		return -1;
	}

	/* TODO 3 : END                          */
	/*---------------------------------------*/

	while (1) {
		/*---------------------------------------*/
		/* TODO 4 : read msg                     */
		
		if(read(receive_fd, receive_msg, sizeof(receive_msg)) == -1){
			printf("receive from client : error!\n");
			return -1;
		}
		//if(!strcmp(receive_msg, "quit")) return 0;

		/* TODO 4 : END                          */
		/*---------------------------------------*/

		printf("server : receive %s\n", receive_msg);

		value = atoi(receive_msg);

		sprintf(send_msg, "%d", value*value);
		printf("server : send %s\n", send_msg);

		/*---------------------------------------*/
		/* TODO 5 : write msg                    */

		if(write(send_fd, send_msg, sizeof(send_msg)) == -1){
			printf("write server to client : error!\n");
			return -1;
		}

		/* TODO 5 : END                          */
		/*---------------------------------------*/
	}
	return 0;
}
