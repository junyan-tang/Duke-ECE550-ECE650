#include "query_funcs.h"
#include <iomanip>

void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{
    work W(*C);
    string stmt = "INSERT INTO PLAYER (team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg) VALUES (" 
                + to_string(team_id) + "," + to_string(jersey_num) + "," + W.quote(first_name) + ","
                + W.quote(last_name) + "," + to_string(mpg) + "," + to_string(ppg) + "," + to_string(rpg) + "," 
                + to_string(apg) + "," + to_string(spg) + "," + to_string(bpg) + ");";
    W.exec(stmt);
    W.commit();
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
    work W(*C);
    string stmt = "INSERT INTO TEAM (name, state_id, color_id, wins, losses) VALUES (" + W.quote(name) + "," 
                + to_string(state_id) + "," + to_string(color_id) + ","
                + to_string(wins) + "," + to_string(losses) + ");";
    W.exec(stmt);
    W.commit();
}


void add_state(connection *C, string name)
{
    work W(*C);
    string stmt = "INSERT INTO STATE(name) VALUES (" + W.quote(name) + ");";
    W.exec(stmt);
    W.commit();
}


void add_color(connection *C, string name)
{
    work W(*C);
    string stmt = "INSERT INTO COLOR(name) VALUES (" + W.quote(name) + ");";
    W.exec(stmt);
    W.commit();
}

/*
 * All use_ params are used as flags for corresponding attributes
 * a 1 for a use_ param means this attribute is enabled (i.e. a WHERE clause is needed)
 * a 0 for a use_ param means this attribute is disabled
 */
void query1(connection *C,
	        int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{   bool flag = false;
    string stmt = "SELECT * FROM PLAYER";
    if (use_mpg) {
        if (flag){
            stmt += " AND ";
        }
        else{
            stmt += " WHERE ";
            flag = true;
        }
        stmt += "MPG >= " + to_string(min_mpg) + " AND MPG <= " + to_string(max_mpg);
    }
    if (use_ppg) {
        if (flag){
            stmt += " AND ";
        }
        else{
            stmt += " WHERE ";
            flag = true;
        }
        stmt += "PPG >= " + to_string(min_ppg) + " AND PPG <= " + to_string(max_ppg);
    }
    if (use_rpg) {
        if (flag){
            stmt += " AND ";
        }
        else{
            stmt += " WHERE ";
            flag = true;
        }
        stmt += "RPG >= " + to_string(min_rpg) + " AND RPG <= " + to_string(max_rpg);
    }
    if (use_apg) {
        if (flag){
            stmt += " AND ";
        }
        else{
            stmt += " WHERE ";
            flag = true;
        }
        stmt += "APG >= " + to_string(min_apg) + " AND APG <= " + to_string(max_apg);
    }
    if (use_spg) {
        if (flag){
            stmt += " AND ";
        }
        else{
            stmt += " WHERE ";
            flag = true;
        }
        stmt += "SPG >= " + to_string(min_spg) + " AND SPG <= " + to_string(max_spg);
    }
    if (use_bpg) {
        if (flag){
            stmt += " AND ";
        }
        else{
            stmt += " WHERE ";
            flag = true;
        }
        stmt += "BPG >= " + to_string(min_bpg) + " AND BPG <= " + to_string(max_bpg);
    }
    stmt += ";";

    nontransaction N(*C);
    result R(N.exec(stmt));

    cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" << endl;
    for(result::iterator i = R.begin(); i != R.end(); ++i) {
        cout << i[0].as<int>() << " " << i[1].as<int>() << " " << i[2].as<int>() 
        << " " << i[3].as<string>() << " " << i[4].as<string>() << " " << i[5].as<int>() 
        << " " << i[6].as<int>() << " " << i[7].as<int>() << " " << i[8].as<int>() << " " 
        << fixed << std::setprecision(1) << i[9].as<double>() << " " << i[10].as<double>() << endl;
    }
}


void query2(connection *C, string team_color)
{
    string stmt = "SELECT TEAM.NAME FROM TEAM, COLOR WHERE TEAM.COLOR_ID = COLOR.COLOR_ID AND COLOR.NAME = '" + team_color + "';";
    nontransaction N(*C);
    result R(N.exec(stmt));

    cout << "NAME" << endl;
    for(result::iterator i = R.begin(); i != R.end(); ++i) {
        cout << i[0].as<string>() << endl;
    }
}


void query3(connection *C, string team_name)
{
    string stmt = "SELECT FIRST_NAME, LAST_NAME FROM PLAYER WHERE TEAM_ID = (SELECT TEAM_ID FROM TEAM WHERE NAME = '" 
    + team_name +"') ORDER BY PPG DESC;";
    nontransaction N(*C);
    result R(N.exec(stmt));
    cout << "FIRST_NAME LAST_NAME" << endl;
    for(result::iterator i = R.begin(); i!= R.end(); i++) {
        cout << i[0].as<string>() << " " << i[1].as<string>() << endl;
    }
}


void query4(connection *C, string team_state, string team_color)
{   
    string stmt = "SELECT UNIFORM_NUM, FIRST_NAME, LAST_NAME FROM PLAYER, TEAM, COLOR, STATE " 
    "WHERE PLAYER.TEAM_ID = TEAM.TEAM_ID AND TEAM.STATE_ID = STATE.STATE_ID AND STATE.NAME = '" 
    + team_state + "' AND TEAM.COLOR_ID = COLOR.COLOR_ID AND COLOR.NAME = '" + team_color + "';";
    nontransaction N(*C);
    result R(N.exec(stmt));
    cout << "UNIFORM_NUM FIRST_NAME LAST_NAME" << endl;
    for(result::iterator i = R.begin(); i!= R.end(); i++) {
        cout << i[0].as<int>() << " " << i[1].as<string>() << " " << i[2].as<string>() << endl;
    }
}


void query5(connection *C, int num_wins)
{
    string stmt = "SELECT FIRST_NAME, LAST_NAME, NAME, WINS FROM PLAYER, TEAM WHERE PLAYER.TEAM_ID = TEAM.TEAM_ID AND WINS > " + to_string(num_wins) + ";";
    nontransaction N(*C);
    result R(N.exec(stmt));
    cout << "FIRST_NAME LAST_NAME NAME WINS" << endl;
    for(result::iterator i = R.begin(); i!= R.end(); i++) {
        cout << i[0].as<string>() << " " << i[1].as<string>() << " " << i[2].as<string>() << " " << i[3].as<int>() << endl;
    }
}
