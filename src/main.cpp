#define GLFW_INCLUDE_NONE
#include "../lib/GLAD/glad.h"
#include "../lib/GLFW/glfw3.h"
#include "../lib/GLM/glm.hpp"
#include "../lib/GLM/gtc/matrix_transform.hpp"
#include "../lib/GLM/gtc/type_ptr.hpp"
#include "../lib/GLM/gtx/string_cast.hpp"
#include "h/camera_object.h"
#include "h/graphic_engine.h"
#include "h/shader.h"
#include "h/shape_object.h"
#include "h/utilities.h"

#include <iostream>
#include <vector>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

std::vector<std::function<void(GLFWwindow *, int, int)>>
    InputManager::mouseCallbacks;
int main() {
  GraphicEngine graphicEngine = GraphicEngine();
  InputManager inputManager = InputManager();
  GLFWwindow *window = graphicEngine.window;
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
  CameraObject camera = CameraObject();

  InputManager::mouseCallbacks.push_back(
      std::bind(&CameraObject::onLookAround, &camera, std::placeholders::_1,
                std::placeholders::_2, std::placeholders::_3));

  glfwSetCursorPosCallback(window, &InputManager::onMouseEvent);
  camera.position = cameraPosition;

  graphicEngine.addCamera(&camera);

  // INIT SHAPE

  std::vector<glm::vec4> triangle = {
      glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
      glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
      glm::vec4(0.0f, 0.5f, 0.0f, 1.0f),
  };
  glm::vec3 color = glm::vec3(1);
  ShapeObject shapeObject = ShapeObject(triangle, color);
  graphicEngine.addObject(&shapeObject);

  auto fnFunc = &CameraObject::onMovement;
  auto movementAction = MovementAction(
      std::bind(&CameraObject::onMovement, &camera, std::placeholders::_1));
  auto id = inputManager.addAction(movementAction);

  inputManager.window = window;
  while (!glfwWindowShouldClose(window)) {
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
      camera.rotation += 1;
    }
    inputManager.run();
    graphicEngine.render();
  }
  glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
