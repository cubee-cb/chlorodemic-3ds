#pragma once

#include "platform.hpp"

#include <string>

#include "util.hpp"

using namespace std;

class game
{
private:
  bool running = false;

public:
  bool is_running();
  void stop();
  int initialise();
  int main_loop();
  int draw();
  void cleanup();
};
