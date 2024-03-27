#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "potato.hpp" 

using namespace std;

class Player{
private:
  int id;
  int playerNum;
  int with_master_fd;
  int with_left_fd;
  int with_right_fd;
  int socket_listen_fd;
  char hostname[100];
  NetInfo net;
  NetInfo toNet;
public:
  Player(char *hostname, char *port){
    with_master_fd = createClientSocket(hostname, port);
    recv(with_master_fd, &id, sizeof(id), MSG_WAITALL);
    recv(with_master_fd, &playerNum, sizeof(playerNum), MSG_WAITALL);
    socket_listen_fd = createServerSocket(NULL, "");
  }
  ~Player() {
    close(with_master_fd);
    close(with_left_fd);
    close(with_right_fd);
    close(socket_listen_fd);
  }
  void listenInfo(){
    Potato curr_p;
    int fd[] = {with_master_fd, with_left_fd, with_right_fd};
    fd_set all_fd;
    
    int max_fd = (with_master_fd > with_left_fd)? with_master_fd:with_left_fd;
    max_fd = (max_fd > with_right_fd)? max_fd:with_right_fd;
    srand((unsigned int)time(NULL) + id);
    while(true){
      FD_ZERO(&all_fd);
      for(int i = 0; i < 3; i++){
        FD_SET(fd[i], &all_fd);
      }
      int status = select(max_fd + 1, &all_fd, NULL, NULL, NULL);
      if(status == -1 || status == 0){
        cerr << "Select() failed!" << endl;
      }
      for(int i = 0; i < 3; i++){
        if(FD_ISSET(fd[i], &all_fd)){
          recv(fd[i], &curr_p, sizeof(curr_p), MSG_WAITALL);
          break;
        }
      }
      if(curr_p.hops > 0){
        curr_p.addToTrace(id);
        curr_p.hops--;
        
        int random = rand() % 2;
        int next_id;
        if(random == 0){
          next_id = (id - 1 + playerNum) % playerNum;
          send(with_left_fd, &curr_p, sizeof(curr_p), 0);
        }
        else{
          next_id = (id + 1 + playerNum) % playerNum; 
          send(with_right_fd, &curr_p, sizeof(curr_p), 0);
        }
        cout << "Sending potato to " << next_id << endl;
      }
      else if(curr_p.hops == 0){
        curr_p.addToTrace(id);
        send(with_master_fd, &curr_p, sizeof(curr_p), 0);
        cout << "I'm it" << endl;
      }
      else{
        break;
      }
    } 
  }

  void sendInfoToMaster(){
    gethostname(hostname, 100);
    strcpy(net.ip_addr, hostname);
    net.port = getCurrentPort(socket_listen_fd);
    send(with_master_fd, &net, sizeof(net),0);
  }
  void connectToNeighbour(){
    recv(with_master_fd, &toNet, sizeof(toNet), MSG_WAITALL);
    char port[20];
    sprintf(port, "%u", toNet.port);
    with_left_fd = createClientSocket(toNet.ip_addr, port);
    with_right_fd = creatServerConnection(socket_listen_fd);
  }

  void startPlay(){
    cout << "Connected as player " << id 
        << " out of " << playerNum << " total players" << endl;
    sendInfoToMaster();
    connectToNeighbour();
    listenInfo();
  }
};

int main(int argc, char *argv[])
{ 
  //check and parse input
  if (argc != 3) {
      cout << "Syntax: <machine_name> <port_num>\n" << endl;
      return 1;
  }
  char *mastername = argv[1];
  char *port = argv[2];

  Player * player = new Player(mastername, port);
  
  player->startPlay();
  delete(player);
  return 0;
}
