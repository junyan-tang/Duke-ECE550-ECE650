#include <stdlib.h>
#include <sys/select.h>
#include <sys/types.h>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;
class Potato{
public:
    int hops;
    int trace[512] = {};
    int trace_len;
public:
    Potato(int h):hops(h), trace_len(h){}
    Potato():hops(5){}
    void printTrace(){
        cout << "Trace of potato:" << endl;
        const char *sep = "";
        for(int i = 0; i < trace_len; i++){
            cout << sep << trace[i];
            sep = ",";
        }
        cout << endl;
    }
    void addToTrace(int player_id){
        trace[trace_len - hops - 1] = player_id;
    }
};

class NetInfo{
public:
  char ip_addr[100];
  uint16_t port;
  
  NetInfo(char * addr, uint16_t p):port(p){
    strcpy(ip_addr, addr);
  }
  NetInfo():port(-1){}
};

//create socket
int createServerSocket(char * hostname, const char *port){
  int status;
  int socket_fd;
  struct addrinfo host_info;
  struct addrinfo *host_info_list;

  memset(&host_info, 0, sizeof(host_info));

  host_info.ai_family   = AF_UNSPEC;
  host_info.ai_socktype = SOCK_STREAM;
  host_info.ai_flags    = AI_PASSIVE;
  //get hostinfo
  status = getaddrinfo(hostname, port, &host_info, &host_info_list);
  if (status != 0) {
    cerr << "Error: cannot get address info for host" << endl;
    cerr << "  (" << hostname << "," << port << ")" << endl;
    exit(1);
  }
  //create socket
  socket_fd = socket(host_info_list->ai_family, host_info_list->ai_socktype, host_info_list->ai_protocol);
  if (socket_fd == -1) {
    cerr << "Error: cannot create socket" << endl;
    cerr << "  (" << hostname << "," << port << ")" << endl;
    exit(1);
  }
  //bind to the port and allow port reuse
  int yes = 1;
  status = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
  status = bind(socket_fd, host_info_list->ai_addr, host_info_list->ai_addrlen);
  if (status == -1) {
    cerr << "Error: cannot bind socket" << endl;
    cerr << "  (" << hostname << "," << port << ")" << endl;
    exit(1);
  } 
  //free address info
  freeaddrinfo(host_info_list);
  //start listening
  status = listen(socket_fd, 100);
  if (status == -1) {
    cerr << "Error: cannot listen on socket" << endl; 
    exit(1);
  }
  return socket_fd;
}

//server listen and accept
int creatServerConnection(int socket_fd){
  struct sockaddr_storage socket_addr;
  socklen_t socket_addr_len = sizeof(socket_addr);
  int player_connection_fd;
  player_connection_fd = accept(socket_fd, (struct sockaddr *)&socket_addr, &socket_addr_len);
  if (player_connection_fd == -1) {
    cerr << "Error: cannot accept connection on socket" << endl;
    exit(1);
  }
  return player_connection_fd;
}

//create client socket and connect to server
int createClientSocket(char *hostname, char *port){
  int status;
  int socket_fd;
  struct addrinfo host_info;
  struct addrinfo *host_info_list;

  memset(&host_info, 0, sizeof(host_info));
  host_info.ai_family   = AF_UNSPEC;
  host_info.ai_socktype = SOCK_STREAM;
  //get address info
  status = getaddrinfo(hostname, port, &host_info, &host_info_list);
  if (status != 0) {
    cerr << "Error: cannot get address info for host" << endl;
    cerr << "  (" << hostname << "," << port << ")" << endl;
    exit(1);
  }
  //create socket and connect with server
  socket_fd = socket(host_info_list->ai_family, host_info_list->ai_socktype, host_info_list->ai_protocol);
  if (socket_fd == -1) {
    cerr << "Error: cannot create socket" << endl;
    cerr << "  (" << hostname << "," << port << ")" << endl;
    exit(1);
  }
  status = connect(socket_fd, host_info_list->ai_addr, host_info_list->ai_addrlen);
  if (status == -1) {
    cerr << "Error: cannot connect to socket" << endl;
    cerr << "  (" << hostname << "," << port << ")" << endl;
    exit(1);
  }
  freeaddrinfo(host_info_list);
  return socket_fd;
}

//Get the current port in use
uint16_t getCurrentPort(int sockfd){
  struct sockaddr_in addr;
  socklen_t addr_len = sizeof(addr);

  if (getsockname(sockfd, (struct sockaddr *)&addr, &addr_len) == -1) {
      cerr << "Error: cannot get port number" << endl;
  }

  return ntohs(addr.sin_port);
}


