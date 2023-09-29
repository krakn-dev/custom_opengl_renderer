#include "h/camera_object.h"
#include "../lib/GLFW/glfw3.h"
#include "../lib/GLM/gtc/matrix_transform.hpp"
#include "../lib/GLM/gtx/string_cast.hpp"
#include "h/input_manager.h"
#include "h/utilities.h"
#include <iostream>

CameraObject::CameraObject() {

  speed = 0.05f;
  rotation = glm::vec3(0.0f, -90.0f, 0.0f);
  cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  firstMouse = true;

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

// TODO update rotation when changed
void CameraObject::onLookAround(GLFWwindow *window, double xPosition,
                                double yPosition) {

  if (firstMouse) {
    lastXPosition = xPosition;
    lastYPosition = yPosition;
    firstMouse = false;
  }

  float *pitch = &GraphicEngineObject::rotation.x;
  float *yaw = &GraphicEngineObject::rotation.y;

  float xoffset = xPosition - lastXPosition;
  float yoffset = lastYPosition - yPosition;
  lastXPosition = xPosition;
  lastYPosition = yPosition;

  float sensitivity = 0.1f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  *yaw += xoffset;
  *pitch += yoffset;

  if (*pitch > 89.0f)
    *pitch = 89.0f;
  if (*pitch < -89.0f)
    *pitch = -89.0f;

  glm::vec3 direction;
  direction.x = cos(glm::radians(*yaw)) * cos(glm::radians(*pitch));
  direction.y = sin(glm::radians(*pitch));
  direction.z = sin(glm::radians(*yaw)) * cos(glm::radians(*pitch));

  cameraFront = glm::normalize(direction);
}
void CameraObject::syncMatrix() {

  glm::mat4 lookAtMatrix = glm::lookAt(
      GraphicEngineObject::position,
      cameraFront + GraphicEngineObject::position, glm::vec3(0.0f, 1.0f, 0.0f));

  modelMatrix = projectionMatrix * lookAtMatrix;
}

void CameraObject::onMovement(CallbackArguments arg) {

  auto *direction = std::get_if<glm::vec2>(&arg);
  if (direction == nullptr) {
    std::cout << "what the fuck" << std::endl;
    return;
  }

  auto cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

  auto realDirection = glm::vec3(0);
  if (direction->y == 1.0f) {
    realDirection += cameraFront;
  }
  if (direction->y == -1.0f) {
    realDirection -= cameraFront;
  }
  if (direction->x == 1.0f) {
    realDirection += glm::normalize(glm::cross(cameraFront, cameraUp));
  }
  if (direction->x == -1.0f) {
    realDirection -= glm::normalize(glm::cross(cameraFront, cameraUp));
  }

  position += glm::normalize(realDirection) * speed;
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

  sumOutputVectors = true;
}
