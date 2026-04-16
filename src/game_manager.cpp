#include "../headers/game_manager.hpp"
#include "../headers/world.hpp"
#include <algorithm>
#include <iostream>
#include <string>

GameManager::GameManager()
    : running(true), world(5, 5, 10), render_engine(&world),
      player(&this->world, 0, 0) {}

GameManager::~GameManager() {}

// Source - https://stackoverflow.com/a/14266139
std::vector<std::string> split(std::string s, const std::string &delimiter) {
  std::vector<std::string> tokens;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    tokens.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  tokens.push_back(s);

  return tokens;
}

void GameManager::cmd_tree(std::string cmd) {
  auto cmds = split(cmd, " ");

  std::for_each(cmds.begin(), cmds.end(), [](std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::tolower(c); });
  });

  if (cmds.size() < 1) {
    return;
  }

  if (cmds[0] == "q" || cmds[0] == "quit" || cmds[0] == "exit") {
    this->running = false;
  }

  if (cmds[0] == "mv") {
    if (cmds.size() < 2) {
      return;
    }

    if (cmds[1] == "up") {
      this->player.move(Vector3(0, -1, 0));
      return;
    }

    if (cmds[1] == "down") {
      this->player.move(Vector3(0, 1, 0));
      return;
    }

    if (cmds[1] == "left") {
      this->player.move(Vector3(-1, 0, 0));
      return;
    }

    if (cmds[1] == "right") {
      this->player.move(Vector3(1, 0, 0));
      return;
    }
  }
}

void GameManager::loop() {
  std::string cmd;

  while (this->running) {
    std::cout << this->render_engine.render_to_buffer() << '\n';
    std::cout << this->player.get_position() << '\n';
    if (!std::getline(std::cin, cmd)) {
      break;
    }

    if (cmd.empty()) {
      continue;
    }

    this->cmd_tree(cmd);
    this->player.mine(this->player.get_position());
  }
}
