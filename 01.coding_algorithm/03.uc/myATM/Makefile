
all: server client open

server:
	gcc server.c bank.c -o server
client:
	gcc client.c bank.c -o client
open:
	gcc open.c bank.c dao.c -o open

.phony: clean
clean:
	-rm -v server client open *.dat
