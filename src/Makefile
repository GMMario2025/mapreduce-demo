all: master worker main

master:
	g++ master.cc utils/string.cc utils/server.cc utils/client.cc -o ../bin/master

worker:
	g++ worker.cc utils/string.cc utils/server.cc utils/client.cc -o ../bin/worker

main:
	g++ main.cc utils/string.cc utils/client.cc -o ../bin/main
