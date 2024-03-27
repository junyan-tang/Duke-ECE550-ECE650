TARGETS=ringmaster player

all: $(TARGETS)
clean:
	rm -f $(TARGETS)

ringmaster: ringmaster.cpp
	g++ -g -Werror -Wall -o $@ $<

player: player.cpp
	g++ -g -Werror -Wall -o $@ $<

