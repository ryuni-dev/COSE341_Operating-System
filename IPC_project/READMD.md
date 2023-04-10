# 실습 2 : IPC
> **[Report](/IPC_project/report_of_IPC.pdf)**
## Assignment 1-1. 
### Shared memory
- init buffer
- attach buffer
- produce message
- consume message

## Assignment 1-2. 
### Semaphore
- init semaphore
- destroy semaphore
- use s_quit() and s_wait()

## Assignment 2. 
### Pipe
**client.c**
- init receive_fd and send_fd 
- send msg and receive msg
  
**server.c**
- make pipes and init fds 
- read msg
- write msg