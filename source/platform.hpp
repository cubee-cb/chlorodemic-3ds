#pragma once

#include <string>

namespace platform
{
  int graphics_begin();

  int graphics_end();

  int main_loop();
  int draw();

  void cleanup();

  void log(int input);
  void log(const char *input);
  void log(std::string input);

  int load_texture(); // todo: abstract asset loading
}
