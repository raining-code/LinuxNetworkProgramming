ALL:server client
server:ServerMain.cc Server.cc
	g++ $^ -o $@ -static
client:ClientMain.cc Client.cc
	g++ $^ -o $@ -static
.PHONY:clean
clean:
	rm -rf server client