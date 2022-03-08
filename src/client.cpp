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