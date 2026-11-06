#include "platform.hpp"
#include "game.hpp"

int main()
{
  game game1 = game();

  platform::graphics_begin();

  game1.initialise();

  // Main loop
  while (game1.is_running())
  {
    // update platform code
    if (platform::main_loop() != 0)
    {
      // tell game to stop if the platform says so
      game1.stop();
    }

    // run game code
    game1.main_loop();
    game1.draw();

    // platform drawing
    platform::draw();
  }

  game1.cleanup();
  platform::cleanup();
  platform::graphics_end();

  return 0;
}
