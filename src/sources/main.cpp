#include <iostream>
#include <string>

#include "../../include/headers/Game.h"


int main() {
  std::string greeting = "\n\nWelcome to Chess!\n"
                         "Choose what to do:\n"
                         "- Start new game: enter \'start\'\n"
                         "- Exit Chess: enter \'exit\'\n";

  std::cout << greeting << std::endl;

  std::string command;
  std::getline(std::cin, command);

  while (command != "exit") {
    if (command == "start") {
      std::unique_ptr<Game> game(new Game);
      game->printTable();

      game->startGame();
    }
    std::cout << greeting << std::endl;
    std::getline(std::cin, command);
  }

  return 0;
}
