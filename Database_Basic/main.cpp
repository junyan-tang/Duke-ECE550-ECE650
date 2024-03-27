#include <iostream>
#include <fstream>
#include <pqxx/pqxx>

#include "exerciser.h"

using namespace std;
using namespace pqxx;

void create_table(connection *C){
  work W(*C);
  //drop all the tables
  W.exec("DROP TABLE IF EXISTS PLAYER");
  W.exec("DROP TABLE IF EXISTS TEAM");
  W.exec("DROP TABLE IF EXISTS STATE");
  W.exec("DROP TABLE IF EXISTS COLOR");
  
  //create the tables
  W.exec("CREATE TABLE STATE(STATE_ID SERIAL, NAME VARCHAR(100), PRIMARY KEY(STATE_ID))");
  W.exec("CREATE TABLE COLOR(COLOR_ID SERIAL, NAME VARCHAR(100), PRIMARY KEY(COLOR_ID))");
  W.exec("CREATE TABLE TEAM(TEAM_ID SERIAL, NAME VARCHAR(100), STATE_ID INT, COLOR_ID INT, WINS INT, LOSSES INT, PRIMARY KEY(TEAM_ID), FOREIGN KEY(STATE_ID) REFERENCES STATE(STATE_ID), FOREIGN KEY(COLOR_ID) REFERENCES COLOR(COLOR_ID))");
  W.exec("CREATE TABLE PLAYER(PLAYER_ID SERIAL, TEAM_ID INT, UNIFORM_NUM INT, FIRST_NAME VARCHAR(100), LAST_NAME VARCHAR(100), MPG INT, PPG INT, RPG INT, APG INT, SPG DOUBLE PRECISION, BPG DOUBLE PRECISION, PRIMARY KEY(PLAYER_ID), FOREIGN KEY(TEAM_ID) REFERENCES TEAM(TEAM_ID))");
  
  W.commit();
}

void init_player(connection *C, string file_name){
  ifstream players(file_name);
  string line;
  int player_id, team_id, jersey_num, mpg, ppg, rpg, apg;
  string first_name, last_name;
  double spg, bpg;

  while (getline(players, line)) {
    stringstream ss(line);
    ss >> player_id >> team_id >> jersey_num >> first_name >> last_name >> mpg >> ppg >> rpg >> apg >> spg >> bpg;
    add_player(C, team_id, jersey_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg);
  }
  players.close();
}

void init_team(connection *C, string file_name){
  ifstream teams(file_name);
  string line;
  int team_id, state_id, color_id, wins, losses;
  string name;

  while (getline(teams, line)) {
    stringstream ss(line);
    ss >> team_id >> name >> state_id >> color_id >> wins >> losses;
    add_team(C, name, state_id, color_id, wins, losses); 
  }
  teams.close();
}

void init_state(connection *C, string file_name){
  ifstream states(file_name);
  string line;
  int state_id;
  string name;
  while (getline(states, line)) {
    stringstream ss(line);
    ss >> state_id >> name;
    add_state(C, name);
  }
  states.close();
}

void init_color(connection *C, string file_name){
  ifstream colors(file_name);
  string line;
  int color_id;
  string name;
  while(getline(colors, line)){
    stringstream ss(line);
    ss >> color_id >> name;
    add_color(C, name);
  }
  colors.close();
}

int main (int argc, char *argv[]) 
{

  //Allocate & initialize a Postgres connection object
  connection *C;

  try{
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    if (C->is_open()) {
      cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }
  } catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }


  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files
  create_table(C);
  
  init_state(C, "state.txt");
  init_color(C, "color.txt");
  init_team(C, "team.txt");
  init_player(C, "player.txt");

  exercise(C);

  //Close database connection
  C->disconnect();

  return 0;
}


