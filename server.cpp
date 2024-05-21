#include<iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include<unistd.h>
#include <arpa/inet.h>
using namespace std;
int main(int argc,char *argv[]){
    
    if(argc<=2){
        cout<<"usage:"<<argv[0]<<" ip_address portname"<<endl;
        return -1;
    }
    struct sockaddr_in server_addr;
    const char* ip=argv[1];
    int port=atoi(argv[2]);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    inet_pton(AF_INET,ip,&server_addr.sin_addr);

    int serverfd=socket(PF_INET,SOCK_STREAM,0);
    int ret=bind(serverfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(ret==-1){
        perror("bind");
    }

    ret=listen(serverfd,5);
    if(ret==-1){
        perror("listen");
    }

    struct sockaddr_in client_addr;
    socklen_t client_addr_len;
    int clientfd=accept(serverfd,(struct sockaddr*)&client_addr,&client_addr_len);
    if(clientfd<=0){
        perror("accept");
    }
    char buf[1024]="123";
    int send_size=send(clientfd,buf,sizeof(buf),0);
    cout<<buf<<endl;
    recv(clientfd,buf,send_size,0);
    sleep(1);
    cout<<buf<<endl;
    
    close(serverfd);
    close(clientfd);
}