#include "h/input_manager.h"
#include "../lib/GLFW/glfw3.h"
#include "../lib/GLM/glm.hpp"
#include "h/utilities.h"
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

void InputManager::removeAction(int id) {
  for (int iAc = 0; iAc < actions.size(); iAc++) {
    if (actions[iAc].ID == id) {
      actions.erase(actions.begin() + iAc);
      break;
    }
  }
}
int InputManager::addAction(ActionBehavior newAction) {
  actions.push_back(newAction);
  return newAction.ID;
}
void InputManager::run(GLFWwindow *window) {
  if (actions.size() == 0) {
    return;
  }
  auto sumVector = glm::vec2(0);
  bool alreadyCalledCallback = false;
  for (int iAc = 0; iAc < actions.size(); iAc++) {
    // for every action
    for (int iIn = 0; iIn < actions[iAc].triggerInputs.size(); iIn++) {
      // for every input
      for (int iKe = 0; iKe < actions[iAc].triggerInputs[iIn].size(); iKe++) {
        // for every key in input
        if (glfwGetKey(window, actions[iAc].triggerInputs[iIn][iKe]) ==
            GLFW_PRESS) {
          // On Key Pressed
          if (!actions[iAc].sumOutputVectors) {
            // if don't sum outputs call callback
            // and proceed to next action.
            actions[iAc].callback(actions[iAc].triggerOutputs[iIn]);
            alreadyCalledCallback = true;
            break;
          }
          sumVector += actions[iAc].triggerOutputs[iIn];
        }
      }
      if (alreadyCalledCallback) {
        alreadyCalledCallback = false;
        break;
      }
    }
    if (actions[iAc].sumOutputVectors && sumVector != glm::vec2(0)) {
      actions[iAc].callback(sumVector);
      sumVector = glm::vec2(0);
    }
  }
}
