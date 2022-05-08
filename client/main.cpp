#include "server.h"
#include <thread>
#include <chrono>

int main(){
  using namespace std::chrono_literals;
  Server server;
  while (true){
    std::this_thread::sleep_for(100ms);
    server.Next();
  }
}