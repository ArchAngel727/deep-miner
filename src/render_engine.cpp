#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>
#ifdef _WIN32
#include <windows.h>

struct winsize {
  int width;
  int height;
}

winsize
get_window_size() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int columns, rows;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
#else
#include <sys/ioctl.h>
#include <unistd.h>
winsize get_window_size() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w;
}
#endif

#include "../headers/render_engine.hpp"
#include "../headers/world.hpp"

void clear() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

RenderEngine::RenderEngine(World *world, PlayerBot *player)
    : world(world), player(player) {}

RenderEngine::~RenderEngine() {}

void bar(std::string &str, size_t size) {
  str.resize(size);
  std::fill(str.begin(), str.end(), '#');
}

bool is_buffer_empty(std::vector<std::string> &buffer) {
  bool is_empty = true;

  for (const auto &str : buffer) {
    for (auto &c : str) {
      if (c != ' ' && c != '#') {
        is_empty = false;
      }
    }
  }

  return is_empty;
}

void RenderEngine::render_block_buffer(std::vector<std::string> &buffer,
                                       size_t width, size_t height,
                                       size_t zero_flag, size_t depth = 0,
                                       bool max_flag = false) const {
  size_t val = depth;

  bar(buffer[0], width + 2);
  bar(buffer[buffer.size() - 1], width + 2);

  for (size_t j = 0; j < height; j++) {
    buffer[j + 1][0] = '#';

    for (size_t i = 0; i < width; i++) {
      Vector3 vec;

      switch (zero_flag) {
      case 0:
        if (max_flag) {
          val = this->world->get_size().get_x() - 1 - depth;
        }

        vec = Vector3(val, i, j);
        break;
      case 1:
        if (max_flag) {
          val = this->world->get_size().get_y() - 1 - depth;
        }

        vec = Vector3(i, val, j);
        break;
      case 2:
        if (max_flag) {
          val = this->world->get_size().get_z() - 1 - depth;
        }

        vec = Vector3(i, j, val);
        break;
      }

      if (this->player->get_position() == vec) {
        buffer[j + 1][i + 1] = 'X';
        continue;
      }

      auto block = world->get_block_at(vec);

      if (block.has_value()) {
        buffer[j + 1][i + 1] = '*';
      } else {
        buffer[j + 1][i + 1] = ' ';
      }
    }

    buffer[j + 1][width + 1] = '#';
  }

  if (is_buffer_empty(buffer)) {
    render_block_buffer(buffer, width, height, zero_flag, depth + 1);
  }
}

void RenderEngine::render_block(VIEW_AXIS axis,
                                std::vector<std::string> &buffer) const {
  std::vector<std::string> block_buffer;
  std::string str;
  size_t size_x, size_y, size_z;
  size_t start;

  this->world->get_size().export_to(size_x, size_y, size_z);

  switch (axis) {
  case X_POSITIVE:
    start = 0;

    str.resize(size_y + 2);
    block_buffer.assign(size_z + 2, str);

    this->render_block_buffer(block_buffer, size_y, size_z, 0);
    break;
  case Y_POSITIVE:
    start = size_y + 3;

    str.resize(size_x + 2);
    block_buffer.assign(size_z + 2, str);

    this->render_block_buffer(block_buffer, size_x, size_z, 1);
    break;
  case Z_POSITIVE:
    start = size_x + size_y + 6;

    str.resize(size_x + 2);
    block_buffer.assign(size_y + 2, str);

    this->render_block_buffer(block_buffer, size_x, size_y, 2);
    break;
  case X_NEGATIVE:
    start = 2 * size_x + size_y + 9;

    str.resize(size_y + 2);
    block_buffer.assign(size_z + 2, str);

    this->render_block_buffer(block_buffer, size_y, size_z, 0, true);
    break;
  case Y_NEGATIVE:
    start = 2 * size_x + 2 * size_y + 12;

    str.resize(size_y + 2);
    block_buffer.assign(size_z + 2, str);

    this->render_block_buffer(block_buffer, size_x, size_z, 1, true);
    break;
    break;
  case Z_NEGATIVE:
    break;
  }

  for (size_t i = 0; i < block_buffer.size(); i++) {
    if (start + block_buffer.at(i).size() <= buffer.at(i).size()) {
      buffer.at(i).replace(start, block_buffer.at(i).size(),
                           block_buffer.at(i));
    }
  }
}

const std::string RenderEngine::render_to_buffer() const {
  std::vector<std::string> buffer;
  size_t size_x, size_y, size_z;
  this->world->get_size().export_to(size_x, size_y, size_z);

  buffer.resize(std::max(std::max(size_x, size_y), size_z) + 2);

  for (auto &str : buffer) {
    str.resize(2 * size_x + 2 * size_y + size_x + 14, ' ');
  }

  this->render_block(VIEW_AXIS::X_POSITIVE, buffer);
  this->render_block(VIEW_AXIS::Y_POSITIVE, buffer);
  this->render_block(VIEW_AXIS::Z_POSITIVE, buffer);
  this->render_block(VIEW_AXIS::X_NEGATIVE, buffer);
  this->render_block(VIEW_AXIS::Y_NEGATIVE, buffer);

  std::string str_buf;

  for (auto &str : buffer) {
    str_buf.append(str);
    str_buf.push_back('\n');
  }

  return str_buf;
}
