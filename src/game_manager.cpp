#include "../headers/game_manager.hpp"
#include "../headers/bot_1.hpp"
#include "../headers/bot_2.hpp"
#include "../headers/world.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>

GameManager::GameManager()
    : running(true), world(5, 5, 10), player(&this->world, 0, 0),
      render_engine(&world, &player, enemies) {

  this->enemies.push_back(new Bot1(&this->world, 4, 4));
  this->enemies.push_back(new Bot2(&this->world, 0, 4));
}

GameManager::~GameManager() {
  for (auto enemie : enemies) {
    delete enemie;
  }

  this->enemies.clear();
}

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

    if (cmds[1] == "up" || cmds[1] == "w") {
      this->player.move(Vector3(0, -1, 0));
      return;
    }

    if (cmds[1] == "down" || cmds[1] == "s") {
      this->player.move(Vector3(0, 1, 0));
      return;
    }

    if (cmds[1] == "left" || cmds[1] == "a") {
      this->player.move(Vector3(-1, 0, 0));
      return;
    }

    if (cmds[1] == "right" || cmds[1] == "d") {
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
    unsigned int point_sum = 0;
    point_sum += this->player.get_points();

    if (!std::getline(std::cin, cmd)) {
      break;
    }

    if (cmd.empty()) {
      continue;
    }

    this->player.mine(this->player.get_position());

    for (auto &bot : this->enemies) {
      int x, y;
      point_sum += bot->get_points();

      if (rand() % 100 > 50) {
        x = 1;
      } else {
        x = -1;
      }

      if (rand() % 100 > 50) {
        y = 1;
      } else {
        y = -1;
      }

      bot->mine(bot->get_position());
      bot->move(Vector3(x, y, 0));
    }

    this->world.update_world(point_sum);
    this->cmd_tree(cmd);
  }
}
