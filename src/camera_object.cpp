#include "h/camera_object.h"
#include "../lib/GLFW/glfw3.h"
#include "../lib/GLM/gtc/matrix_transform.hpp"
#include "../lib/GLM/gtx/string_cast.hpp"
#include "h/input_manager.h"
#include "h/utilities.h"
#include <iostream>

CameraObject::CameraObject() {
  projectionMatrix = glm::mat4(1.0f);
  projectionMatrix = glm::perspective(
      glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f,
      100.0f);
}

void CameraObject::setProjectionMatrix(float fov, float windowWidth,
                                       float windowHeight, float near,
                                       float far) {
  projectionMatrix = glm::perspective(glm::radians(fov),
                                      windowWidth / windowHeight, near, far);
}

void CameraObject::syncMatrix() {

  glm::mat4 lookAtMatrix =
      glm::lookAt(GraphicEngineObject::position,
                  GraphicEngineObject::rotation + GraphicEngineObject::position,
                  glm::vec3(0.0f, 1.0f, 0.0f));

  modelMatrix = projectionMatrix * lookAtMatrix;
  std::cout << glm::to_string(position) << std::endl;
  // std::cout << glm::to_string(GraphicEngineObject::modelMatrix) << std::endl;
}

void CameraObject::onMovement(CallbackArguments arg) {
  auto *direction = std::get_if<glm::vec2>(&arg);
  if (direction == nullptr) {
    std::cout << "what the fuck" << std::endl;
    return;
  }
  std::cout << glm::to_string(*direction) << std::endl;
}

MovementAction::MovementAction(std::function<void(CallbackArguments)> callback)
    : ActionBehavior(callback) {

  std::vector<GLFW_KEY> forwardKeys = {
      GLFW_KEY_W,
      GLFW_KEY_K,
      GLFW_KEY_UP,
  };
  std::vector<GLFW_KEY> backwardsKeys = {
      GLFW_KEY_S,
      GLFW_KEY_J,
      GLFW_KEY_DOWN,
  };
  std::vector<GLFW_KEY> leftKeys = {
      GLFW_KEY_A,
      GLFW_KEY_H,
      GLFW_KEY_LEFT,
  };
  std::vector<GLFW_KEY> rightKeys = {
      GLFW_KEY_D,
      GLFW_KEY_L,
      GLFW_KEY_RIGHT,
  };

  glm::vec2 forwardDirection = glm::vec2(0.0f, 1.0f);
  glm::vec2 backwardsDirection = glm::vec2(0.0f, -1.0f);
  glm::vec2 leftDirection = glm::vec2(-1.0f, 0.0f);
  glm::vec2 rightDirection = glm::vec2(1.0f, 0.0f);

  ActionBehavior::triggerInputs.assign(
      {forwardKeys, backwardsKeys, rightKeys, leftKeys});
  ActionBehavior::triggerOutputs.assign(
      {forwardDirection, backwardsDirection, rightDirection, leftDirection});
}
