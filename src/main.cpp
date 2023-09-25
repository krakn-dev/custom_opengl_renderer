#define GLFW_INCLUDE_NONE
#include "../lib/GLAD/glad.h"
#include "../lib/GLFW/glfw3.h"
#include "../lib/GLM/glm.hpp"
#include "../lib/GLM/gtc/matrix_transform.hpp"
#include "../lib/GLM/gtc/type_ptr.hpp"
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

  glm::vec3 translation = glm::vec3(0.0f, 0.0f, 3.0f);
  float rotation = 0.0f;
  glm::vec3 rotationAxis = glm::vec3(1.0f, 1.0f, 1.0f);

  CameraObject camera = CameraObject();
  camera.setModelMatrixTransform(&translation);
  camera.setModelMatrixRotation(&rotation, &rotationAxis);
  graphicEngine.addCamera(&camera);

  // INIT SHAPE
  glm::mat4 modelMatrix = glm::mat4(1);

  std::vector<glm::vec4> triangle = {
      glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
      glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
      glm::vec4(0.0f, 0.5f, 0.0f, 1.0f),
  };

  glm::vec3 color = glm::vec3(1);

  auto translate = glm::vec3(0.0f, 0.0f, 0.0f);
  ShapeObject shapeObject = ShapeObject(&modelMatrix, triangle, &color);
  shapeObject.setModelMatrixTransform(&translate);

  graphicEngine.addObject(&shapeObject);

  while (!glfwWindowShouldClose(window)) {
    rotation = glfwGetTime() * 10;
    camera.setModelMatrixRotation(&rotation, &rotationAxis);
    graphicEngine.render();
  }
  glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
