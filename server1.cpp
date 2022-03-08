#include "socket.hpp"
#include <pthread.h>

// Define connection handler function
void *connection_handler(void *);

int main(){
   int connection_id;
   
   std::cout << "[INFO] STARTING UP THE SERVER" << std::endl;
   std::cout << "[INFO] PORT NUMBER 8888" << std::endl;
   
   if (!ssock->Open(8888)){
      std::cout << ssock->Error() << std::endl;
      return -1;
   }
   
   std::cout << "[INFO] WAITING FOR UPCOMING CONNECTIONS" << std::endl;
   
   pthread_t thread_id;
   while ((connection_id = ssock->Accept())) {
      if (pthread_create(&thread_id, NULL,  connection_handler,(void*)&connection_id)<0) {
		 std::cout << "[WARNING] CONNECTION ACCEPTING FAILED" << std::endl;
      } else {
		 std::cout << "[INFO] CONNECTION ACCEPTED CONNECTION ID "<< connection_id << std::endl;
	  }
   }
   
   return 0;
}

// This will handle connection for each client
void *connection_handler(void *socket_desc){
  //Get the socket descriptor
  int sock = *(int*)socket_desc;
  int read_size;
  std::string RequestData, ResponseData = "Hello, client";

  // Receive message from client
  while((read_size = ssock->Receive(sock, RequestData))>0){
     // Print received message from client
     std::cout << "[RECEIVE] " << RequestData << std::endl;
     // Send response to client
     if(ssock->Send(sock, ResponseData) == -1) {
        std::cout << "[WARNING] CAN'T SEND PACKET TO CONNECTION ID " << sock << std::endl;
     } else {
	std::cout << "[SEND] " << ResponseData << std::endl;
     }
  }
  
  // check receive status
  if(read_size == 0) {
  	std::cout << "[NOTE] CONNECTION ID " << sock << " DISCONNECTED " << std::endl;
      fflush(stdout);
  } else if(read_size == -1) {
      std::cout << "[WARNING] FAILED TO RECEIVE PACKETS" << std::endl;
  }
  
  return 0;
}
