#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "../../lib/GLFW/glfw3.h"
#include "../../lib/GLM/glm.hpp"
#include "./action_behavior.h"
#include "./utilities.h"
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <variant>
#include <vector>

class InputManager {
public:
  int addAction(ActionBehavior newAction); // return id
  void removeAction(int id);
  void run(GLFWwindow *window);

private:
  std::vector<ActionBehavior> actions;
};

#endif // INPUT_MANAGER_H_
