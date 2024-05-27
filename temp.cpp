#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc,char *argv[]){
    if(argc<=2){
        printf("usage:%s ip port",argv[0]);
    }
    const char *ip=argv[1];
    int port=atoi(argv[2]);

    int listenfd=socket(PF_INET,SOCK_STREAM,0);
    assert(listenfd>=1);

    struct sockaddr_in address;
    memset(&address,0,sizeof(address));
    address.sin_family=AF_INET;
    address.sin_port=htons(port);
    inet_pton(AF_INET,ip,&address.sin_addr);
    
    int ret=0;
    ret=bind(listenfd,(struct sockaddr*)&address,sizeof(address));
    assert(ret!=-1);

    ret=listen(listenfd,5);

    struct sockaddr_in client;
    memset(&client,0,sizeof(client));
    socklen_t client_length;

    int sockfd=accept(listenfd,(struct sockaddr*)&client,&client_length);

    char buf[1024];
    int recv_size=0;
    recv_size=recv(sockfd,buf,sizeof(buf),0);
    printf("recv=%s\n",buf);
    int send_size=0;
    send_size=send(sockfd,buf,sizeof(buf),0);
    printf("send=%s\n",buf);
}