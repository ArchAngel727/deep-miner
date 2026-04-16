#include "../headers/game_manager.hpp"
#include "../headers/world.hpp"
#include <algorithm>
#include <iostream>
#include <string>

GameManager::GameManager()
    : running(true), world(5, 5, 10), render_engine(&world) {

  auto buf = this->render_engine.render_to_buffer();

  std::cout << buf;
}

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

  if (cmds[0] == "q" || cmds[0] == "quit" || cmds[0] == "exit") {
    this->running = false;
  }

  if (cmds[0] == "mv") {
    if (cmds.size() == 1) {
      return;
    }

    if (cmds[1] == "up") {
      return;
    }

    if (cmds[1] == "down") {
      return;
    }

    if (cmds[1] == "left") {
      return;
    }

    if (cmds[1] == "right") {
      return;
    }
  }
}

void GameManager::loop() {
  std::string cmd;

  while (this->running) {
    std::cin >> cmd;

    this->cmd_tree(cmd);
  }
}
