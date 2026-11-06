#include "game.hpp"

int game::initialise()
{
  running = true;

  platform::log("Chlorodemic!");
  platform::log("Number: " + to_string(get_number()));

  return 0;
}

int game::main_loop()
{
  return 0;
}

int game::draw()
{
  return 0;
}

bool game::is_running()
{
  return running;
}

void game::cleanup()
{
  platform::log("Cleanup.");
}

void game::stop()
{
  platform::log("Stopping game...");
  running = false;
}
