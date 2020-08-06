
#include <windows.h>

#include <ctime>
#include <iostream>
#include <string>

#include "FGFDMPacket.hpp"

SOCKET sendSocket = -1;
struct sockaddr_in sendAddr;

// IP and port where FG is listening
const std::string fg_ip{"127.0.0.1"};
const int fg_port{5500};

// period to update fg (in milliseconds)
const int update_period{50};

void run();

int main(int argc, char** argv) {
   WSAData wd;
   if (WSAStartup(MAKEWORD(2,0),&wd) == 0) {
      memset(&sendAddr,0,sizeof(sendAddr));
      sendAddr.sin_family = AF_INET;
      sendAddr.sin_port = htons(fg_port);
      sendAddr.sin_addr.S_un.S_addr = inet_addr(fg_ip.c_str());
      sendSocket = socket(AF_INET,SOCK_DGRAM,0);
      if (sendSocket != INVALID_SOCKET) {
         run();
      } else {
         std::cout << "socket() failed" << std::endl;
      }
   } else {
      std::cout << "WSAStartup() failed" << std::endl;
   }
   return 0;
}

#define D2R (3.14159 / 180.0)            // degrees to radians

void run() {
   const double latitude{45.59823};      // degs
   const double longitude{-120.69202};   // degs
   const double altitude{150.0};         // meters above sea level
 
   float roll{};    // degs
   float pitch{};   // degs
   float yaw{};     // degs

   const float visibility{5000.0}; // meters

   while (true) {
      Sleep(update_period);

      // create packet to send to FlightGear, zero initial values
      FGFDMPacket fdm;

      fdm.version = FGFDMPacket_Version;

      fdm.latitude  = latitude * D2R;
      fdm.longitude = longitude * D2R;
      fdm.altitude  = altitude;

      fdm.phi   = static_cast<float>(roll * D2R);
      fdm.theta = static_cast<float>(pitch * D2R);
      fdm.psi   = static_cast<float>(yaw * D2R);
      fdm.num_engines = 1;

      fdm.num_tanks = 1;
      fdm.fuel_quantity[0] = 100.0;

      fdm.num_wheels = 3;

      fdm.cur_time = static_cast<std::uint32_t>(std::time(nullptr));
      fdm.warp = 1;

      fdm.visibility = visibility;

      if (!is_big_endian()) {
         swapBytes(&fdm);
      }

      sendto(sendSocket, reinterpret_cast<char*>(&fdm), sizeof(fdm), 0,
             reinterpret_cast<struct sockaddr*>(&sendAddr), sizeof(sendAddr));

      roll += 5.0;      // increase roll in 5 degree increments
      if (roll > 20.0) {
         roll = 0.0;
      }
      std::cout << "Roll: " << roll << std::endl;
   }
}
