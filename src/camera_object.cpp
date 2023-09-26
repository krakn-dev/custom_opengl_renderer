#include "h/camera_object.h"
#include "../lib/GLM/gtc/matrix_transform.hpp"
#include "../lib/GLM/gtx/string_cast.hpp"
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
