#include <iostream>
#include <cstring>
#include <vector>

#include "potato.hpp"

using namespace std;

class Ringmaster{
private:
  int curr_player;
  int player_num;
  int hops_num;
  int socket_listen_fd;
  int max_fd;
  vector<int> all_players_fd;
  vector<NetInfo> players_net;
  fd_set players_fd;
  Potato potato;
public:
  Ringmaster(char * port, int players, int hops):player_num(players), hops_num(hops){
    socket_listen_fd = createServerSocket(NULL, port);
    all_players_fd.resize(player_num);
    players_net.resize(player_num);
    max_fd = 0;
    potato.hops = hops;
    potato.trace_len = hops;
  }
  ~Ringmaster(){
    for(int i = 0; i < player_num; i++){
      close(all_players_fd[i]);
    }
  }
  void connectPlayers(){
    while(curr_player != player_num){
      int player_fd = creatServerConnection(socket_listen_fd);
      all_players_fd[curr_player] = player_fd;
      send(player_fd, &curr_player, sizeof(curr_player), 0);
      send(player_fd, &player_num, sizeof(player_num), 0);
      recv(player_fd, &players_net[curr_player], sizeof(players_net[curr_player]), MSG_WAITALL);
      curr_player += 1;
    }
    close(socket_listen_fd);
  }
  void sendRingInfo(){
    for(int i = 0; i < player_num; i++){
      int index = (i + player_num - 1) % player_num;
      send(all_players_fd[i], &players_net[index], sizeof(players_net[index]), 0);
      cout << "Player " << i << " is ready to play" << endl;
    }
  }
  void sendPotato(){
    srand((unsigned int)time(NULL) + player_num);
    int random = rand() % player_num;
    cout << "Ready to start the game, sending potato to player " << random << endl;
    potato.hops--;
    send(all_players_fd[random], &potato, sizeof(potato), 0);
    
  }
  void receivePotato(){
    FD_ZERO(&players_fd);
    for(int i = 0; i < player_num; i++){
      FD_SET(all_players_fd[i], &players_fd);
    }
    findMaxID();
    int status = select(max_fd + 1, &players_fd, NULL, NULL, NULL);
    if(status == -1 || status == 0){
      cerr << "Select() failed!" << endl;
    }
    for(int i = 0; i < player_num; i++){
      if (FD_ISSET(all_players_fd[i], &players_fd)){
        recv(all_players_fd[i], &potato, sizeof(potato), MSG_WAITALL);
      }
    }
  }

  void closeGame(){
    potato.hops = -1;
    for(int i = 0; i < player_num; i++){
      send(all_players_fd[i], &potato, sizeof(potato), 0);
    }
  }
  void startGame(){
    printInitInfo();
    connectPlayers();
    sendRingInfo();
    if(potato.hops == 0){
      srand((unsigned int)time(NULL) + player_num);
      int random = rand() % player_num;
      cout << "Ready to start the game, sending potato to player " << random << endl;
      closeGame();
      potato.printTrace();
    }
    else if(potato.hops != 0){
      sendPotato();
      receivePotato();
      closeGame();
      potato.printTrace();
    }
  }

  void findMaxID(){
    for(int i = 0; i < player_num; i++){
      if(all_players_fd[i] > max_fd){
        max_fd = all_players_fd[i];
      }
    }
  }

  void printInitInfo(){
    cout << "Potato Ringmaster" << endl;
    cout << "Players = " << player_num << endl;
    cout << "Hops = " << hops_num << endl;
  }

};

int main(int argc, char *argv[])
{ //check input format
  if (argc != 4) {
      cout << "Syntax: <port_num> <num_players> <num_hops>\n" << endl;
      return 1;
  }
  //parse input
  char *port = argv[1];
  int player_num = stoi(argv[2]);
  int hops_num = stoi(argv[3]);
  if(player_num <= 1 || hops_num < 0 || hops_num > 512){
    cout << "Argument Error: num_players must be greater than 1" << endl;
    cout << "num_hops must be greater than or equal to zero and less than or equal to 512" << endl;
    return 1;
  }
  Ringmaster * master = new Ringmaster(port, player_num, hops_num);
  master->startGame();
  delete(master);
  return 0;
}
