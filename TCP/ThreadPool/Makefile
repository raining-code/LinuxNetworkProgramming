ALL:server client
server:TCPServer.cc ServerMain.cc
	g++ $^ -o $@ -static
client:TCPClient.cc ClientMain.cc
	g++ $^ -o $@ -static
.PHONY:clean
clean:
	rm -rf client server