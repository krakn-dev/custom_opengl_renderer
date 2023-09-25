#include "h/camera_object.h"
#include "../lib/GLM/gtc/matrix_transform.hpp"
#include "h/utilities.h"

CameraObject::CameraObject() {
  projectionMatrix = glm::mat4(1.0f);
  projectionMatrix = glm::perspective(
      glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f,
      100.0f);
}

void CameraObject::setProjectionMatrix(float *fov, float windowWidth,
                                       float windowHeight, float *near,
                                       float *far) {
  projectionMatrix = glm::perspective(glm::radians(*fov),
                                      windowWidth / windowHeight, *near, *far);
}
void CameraObject::setModelMatrixRotation(float *rotationDegrees,
                                          glm::vec3 *rotationAxis) {
  *GraphicEngineObject::modelMatrix =
      glm::rotate(*GraphicEngineObject::modelMatrix,
                  glm::radians(-(*rotationDegrees)), *rotationAxis);
}
void CameraObject::setModelMatrixTransform(glm::vec3 *translation) {
  *GraphicEngineObject::modelMatrix =
      glm::translate(*GraphicEngineObject::modelMatrix, -(*translation));
}
