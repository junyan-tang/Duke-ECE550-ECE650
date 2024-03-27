from sqlalchemy import inspect, desc

from schema import *

def create_tables(engine):
    inspector = inspect(engine)
    if inspector.has_table("player"):
        Player.__table__.drop(engine)
    if inspector.has_table("team"):
        Team.__table__.drop(engine)
    if inspector.has_table("color"):
        Color.__table__.drop(engine)
    if inspector.has_table("state"):
        State.__table__.drop(engine)
    Base.metadata.create_all(engine)

def add_color(session, name):
    new_color = Color(name=name)
    session.add(new_color)
    session.commit()

def init_color(session):
    f = open("color.txt", "r")
    line = f.readline()
    while line:
        line = line.strip()
        if line:
            color_id, name = line.split(" ")
            add_color(session, name)
        line = f.readline()
    f.close()

def add_state(session, name):
    new_state = State(name=name)
    session.add(new_state)
    session.commit()

def init_state(session):
    f = open("state.txt", "r")
    line = f.readline()
    while line:
        line = line.strip()
        if line:
            state_id, name = line.split(" ")
            add_state(session, name)
        line = f.readline()
    f.close()

def add_team(session, name, state_id, color_id, wins, losses): 
    new_team = Team(name=name, state_id=state_id, color_id=color_id, wins=wins, losses=losses)
    session.add(new_team)
    session.commit()

def init_team(session):
    f = open("team.txt", "r")
    line = f.readline()
    while line:
        line = line.strip()
        if line:
            team_id, name, state_id, color_id, wins, losses = line.split(" ")
            add_team(session, name, state_id, color_id, wins, losses)
        line = f.readline()
    f.close()

def add_player(session, team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg):
    new_player = Player(team_id=team_id, uniform_num=uniform_num, first_name=first_name, last_name=last_name, mpg=mpg, ppg=ppg, rpg=rpg, apg=apg, spg=spg, bpg=bpg)
    session.add(new_player)
    session.commit()

def init_player(session):
    f = open("player.txt", "r")
    line = f.readline()
    while line:
        line = line.strip()
        if line:
            player_id, team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg = line.split(" ")
            add_player(session, team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg)
        line = f.readline()
    f.close()

def query1(session, use_mpg, min_mpg, max_mpg, 
           use_ppg, min_ppg, max_ppg,
           use_rpg, min_rpg, max_rpg,
           use_apg, min_apg, max_apg,
           use_spg, min_spg, max_spg,
           use_bpg, min_bpg, max_bpg):
    players = session.query(Player)
    if use_mpg:
        players = players.filter(Player.mpg >= min_mpg, Player.mpg <= max_mpg)
    if use_ppg:
        players = players.filter(Player.ppg >= min_ppg, Player.ppg <= max_ppg)
    if use_rpg:
        players = players.filter(Player.rpg >= min_rpg, Player.rpg <= max_rpg)
    if use_apg:
        players = players.filter(Player.apg >= min_apg, Player.apg <= max_apg)
    if use_spg:
        players = players.filter(Player.spg >= min_spg, Player.spg <= max_spg)
    if use_bpg:
        players = players.filter(Player.bpg >= min_bpg, Player.bpg <= max_bpg)
    players = players.all()
    print("PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG")
    for player in players:
        print(f"{player.player_id} {player.team_id} {player.uniform_num} {player.first_name} {player.last_name} {player.mpg} {player.ppg} {player.rpg} {player.apg} {player.spg} {player.bpg}")

def query2(session, color_name):
    teams = session.query(Team, Color).filter(Team.color_id == Color.color_id, Color.name == color_name).all()
    print("NAME")
    for team in teams:
        print(team.Team.name)

def query3(session, team_name):
    players = session.query(Player, Team).filter(Player.team_id == Team.team_id, Team.name == team_name)
    players = players.order_by(desc(Player.ppg)).all()
    print("FIRST_NAME LAST_NAME")
    for player in players:
        print(f"{player.Player.first_name} {player.Player.last_name}")

def query4(session, state_name, color_name):
    players = session.query(Player, Team, State, Color).filter(Player.team_id == Team.team_id, Team.state_id == State.state_id, Team.color_id == Color.color_id, State.name == state_name, Color.name == color_name).all()
    print("UNIFORM_NUM FIRST_NAME LAST_NAME")
    for player in players:
        print(f"{player.Player.uniform_num} {player.Player.first_name} {player.Player.last_name}")

def query5(session, win_number):
    players = session.query(Player, Team).filter(Player.team_id == Team.team_id, Team.wins > win_number).all()
    print("FIRST_NAME LAST_NAME NAME WINS")
    for player in players:
        print(f"{player.Player.first_name} {player.Player.last_name} {player.Team.name} {player.Team.wins}")
    