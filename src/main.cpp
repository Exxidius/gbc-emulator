#include "../include/emulator.h"
#include <iostream>

int main() {
  Emulator e;
  try {
    e.run();
  } catch (const std::exception &ex) {
    std::cerr << ex.what() << "\n";
    return 1;
  }
  return 0;
}
