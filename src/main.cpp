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

int main() {
  GraphicEngine graphicEngine = GraphicEngine();
  GLFWwindow *window = graphicEngine.window;
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
  CameraObject camera = CameraObject();
  glm::vec3 cameraRotation = glm::vec3(0.0f, 0.0f, -3.0f);
  camera.rotation = cameraRotation;
  camera.position = cameraPosition;

  graphicEngine.addCamera(camera);

  // INIT SHAPE

  std::vector<glm::vec4> triangle = {
      glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
      glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
      glm::vec4(0.0f, 0.5f, 0.0f, 1.0f),
  };
  glm::vec3 color = glm::vec3(1);
  ShapeObject shapeObject = ShapeObject(triangle, color);
  graphicEngine.addObject(shapeObject);

  while (!glfwWindowShouldClose(window)) {

    cameraPosition = glm::vec3(0);
    const float movementSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      cameraPosition.z -= 1;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      cameraPosition.z += 1;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      cameraPosition.x -= 1;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      cameraPosition.x += 1;

    cameraRotation = glm::vec3(0);
    const float rotationSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
      cameraRotation.x -= 1;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
      cameraRotation.x += 1;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
      cameraRotation.y -= 1;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
      cameraRotation.y += 1;

    graphicEngine.camera.rotation += cameraRotation * rotationSpeed;
    graphicEngine.camera.position += cameraPosition * movementSpeed;
    graphicEngine.render();
  }
  glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {}
