from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from utils import *
from exerciser import *

engine = create_engine('postgresql://postgres:passw0rd@localhost:5432/ACC_BBALL', echo=False)

Session = sessionmaker(bind=engine)
session = Session()

create_tables(engine)
init_color(session)
init_state(session)
init_team(session)
init_player(session)

exercise(session)

session.close()