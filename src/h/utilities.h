#pragma once

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "../../lib/GLM/glm.hpp"
#include <variant>
#include <vector>

extern int WINDOW_HEIGHT;
extern int WINDOW_WIDTH;

typedef int GLFW_KEY;

typedef std::variant<glm::vec2> CallbackArguments;

#endif // UTILITIES_H_
