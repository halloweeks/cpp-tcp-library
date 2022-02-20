# Client code
```
#include "socket.hpp"

int main(){
   // send message string and receive message string
   std::string msg, buffer;
   
   // The connect function return Boolean
   if (!csock->Connect("0.0.0.0", 8888)) {
      std::cout << "[ERROR] Can't connect to the server" << std::endl;
      return -1;
   }
   
   while (true) {
      std::cout << "[msg]> ";
      // Get input from the client
      getline(std::cin, msg);
      // if user input is blank to set default message
      if(!msg.compare("")) {
         msg = "default message";
      } else if (!msg.compare("exit")) { // if user input is exit
         std::cout << "Bye!" << std::endl;
         break;
      }
      
      // send message to connected server
      if (csock->Send(msg)) {
         std::cout << "[SEND] " << msg << std::endl;
      } else {
         std::cout << "[ERROR] Unable to send" << std::endl;
      }
         
      // receive message from connected server
      if (csock->Receive(buffer) > 0) {
         std::cout << "[RECEIVE] " << buffer << std::endl;
      } else {
         std::cout << "[ERROR] Unable to receive" << std::endl;
      }
   }
   
   // Close the connection
   csock->Close();
   
   return 0;
}
```

# Server

```
#include "socket.hpp"

int main(){
   // Connection Id and receive size 
   int conn_id, read_size;
   // Store receive message to the buffer
   std::string buffer;
   
   if (ssock->Open(8888)) {
      std::cout << "[INFO] STARTING UP THE SERVER" << std::endl;
   } else {
      std::cout << ssock->Error() << std::endl;
      return -1;
   }
   
   while ((conn_id = ssock->Accept())) {
      if (conn_id > 0) {
         std::cout << "[INFO] CONNECTION ACCEPTED CONN ID " << conn_id << std::endl;
      } else {
         std::cout << "[WARNING] CONNECTION ACCEPTING FAILED" << std::endl;
      }
      while((read_size = ssock->Receive(conn_id, buffer))>0){
         if(ssock->Send(conn_id, buffer) == -1) {
            std::cout << "[WARNING] CAN'T SEND PACKET TO CONNECTION ID " << conn_id << std::endl;
         } else {
            std::cout << "[SEND] " << buffer << std::endl;
         }
         std::cout << "[RECEIVE] " << buffer << std::endl;
      }
      if (read_size == 0) {
         std::cout << "[NOTE] CONNECTION ID " << conn_id << " DISCONNECTED " << std::endl;
      } else if(read_size == -1) {
         std::cout << "[WARNING] FAILED TO RECEIVE PACKETS" << std::endl;
      }
   }
   
   return 0;
}
```
