#ifndef SOCKET_TCP
#define SOCKET_TCP

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

#define BUFFER_SIZE 4096

class client {
   private:
   int sock = 0, valread;
   struct sockaddr_in serv_addr;
   char buffer[BUFFER_SIZE] = {0};
   const char* Error_Msg;
   
   public:
   bool Connect(const char*, unsigned port);
   int Send(std::string);
   int Receive(std::string &buf);
   void Close();
   const char* Error();
};

class server {
   private:
   int socket_desc , client_sock, c;
   struct sockaddr_in server , client;
   char buffer[BUFFER_SIZE] = {0};
   const char* Error_Msg;
   public:
   bool Open(unsigned port);
   int Accept();
   int Send(int, std::string);
   int Receive(int, std::string &buf);
   void Close();
   const char* Error();
   void Disconnect(int);
};
/* client code */
bool client::Connect(const char* address = "127.0.0.1", unsigned port = 8888) {
   int status = 1;
   
   if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      Error_Msg ="socket creating failed";
      status = 0;
   }
   
   // assign IP, PORT
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(port);
   
   // Convert IPv4 and IPv6 addresses from text to binary form
   if(inet_pton(AF_INET, address, &serv_addr.sin_addr)<=0){
      Error_Msg = "invalid address/ address not supported";
      status = 0;
   }
   
   // connect the client socket to server socket
   if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
      Error_Msg = "Unable to connect the server";
      status = 0;
   }
   
   return status;
}

int client::Send(std::string packet) {
   return send(sock, packet.c_str(), strlen(packet.c_str()), 0);
}

int client::Receive(std::string &buf) {
   int status = 0;
   status = recv(sock, buffer, BUFFER_SIZE, 0);
   buf = buffer;
   memset(buffer, 0, BUFFER_SIZE);
   return status;
}


void client::Close() {
   close(sock);
}

const char* client::Error() {
   return Error_Msg;
}

/* client code end*/

bool server::Open(unsigned port = 8888) {
   int status = 1;
   // Create TCP socket
   socket_desc = socket(AF_INET, SOCK_STREAM, 0);
   // check socket creation
   if (socket_desc==-1) {
      Error_Msg = "could not create socket";
      status = 0;
   }
   
   // Prepare the sockaddr_in structure
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port = htons(port);
   
   // Bind the address and port
   if (bind(socket_desc,(struct sockaddr *)&server, sizeof(server))<0) {
      Error_Msg = "Binding failed";
      status = 0;
   }
   
   // Listen on the socket, with 40 max connection requests queued
   if (listen(socket_desc, 3) < 0) {
      Error_Msg = "failed to listening";
      status = 0;
   }
   return status;
}

int server::Accept() {
   c = sizeof(struct sockaddr_in);
   return accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
}

int server::Send(int sock, std::string packet) {
   return send(sock, packet.c_str(), strlen(packet.c_str()), 0);
}

int server::Receive(int sock, std::string &buf) {
   int status = 0;
   status = recv(sock, buffer, BUFFER_SIZE,0);
   buf = buffer;
   memset(buffer, 0, BUFFER_SIZE);
   return status;
}

void server::Close() {
   close(socket_desc);
}

const char* server::Error() {
   return Error_Msg;
}

void server::Disconnect(int sock) {
   close(sock);
}

client *csock = new client;
server *ssock = new server;
#endif