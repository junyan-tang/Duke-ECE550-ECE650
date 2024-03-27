from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, Double, String, ForeignKey, Sequence
from sqlalchemy.orm import relationship

Base = declarative_base()

class Color(Base):
    __tablename__ = 'color'
    color_id = Column(Integer, primary_key=True)
    name = Column(String)
    team = relationship("Team", backref="color")

class State(Base):
    __tablename__ = 'state'
    state_id = Column(Integer, primary_key=True)
    name = Column(String)
    team = relationship("Team", backref="state")

class Team(Base):
    __tablename__ = 'team'
    team_id = Column(Integer, primary_key=True)
    name = Column(String)
    state_id = Column(Integer, ForeignKey('state.state_id'))
    color_id = Column(Integer, ForeignKey('color.color_id'))
    wins = Column(Integer)
    losses = Column(Integer)

class Player(Base):
    __tablename__ = 'player'
    player_id = Column(Integer, primary_key=True)
    team_id = Column(Integer, ForeignKey('team.team_id'))
    uniform_num = Column(Integer)
    first_name = Column(String)
    last_name = Column(String)
    mpg = Column(Integer)
    ppg = Column(Integer)
    rpg = Column(Integer)
    apg = Column(Integer)
    spg = Column(Double)
    bpg = Column(Double)

