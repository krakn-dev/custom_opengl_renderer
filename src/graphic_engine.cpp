#include "h/graphic_engine.h"
#include "h/shader.h"
#include "h/utilities.h"
#include <vector>

#include "../lib/GLM/gtx/string_cast.hpp"

GraphicEngine::GraphicEngine() {
  initOpenGL();
  shader = new Shader("./src/shaders/vertex_shader.glsl",
                      "./src/shaders/fragment_shader.glsl");
  shader->use();
}

void GraphicEngine::addCamera(CameraObject *newCamera) { camera = newCamera; }

void GraphicEngine::render() {
  shader->use();

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glfwPollEvents();

  updateCameraUniform();

  if (!objectsNeedUpdate) {
    return;
  }
  objectsNeedUpdate = true;

  // Sync matrix with new position and rotation
  for (int iObj = 0; iObj < objects.size(); iObj++) {
    objects[iObj]->syncMatrix();
  }

  // Get number of vertices
  int numberOfVertices = 0;
  for (int iObj = 0; iObj < objects.size(); iObj++) { // for every object
    for (int iVex = 0;
         iVex < objects[iObj]->shape.size(); // for every shape vertex
         iVex++) {
      numberOfVertices++;
    }
  }

  // Get vertices and colors inside a vector [vertex, color, vertex...]
  std::vector<float> attributeVector = {};
  for (int iObj = 0; iObj < objects.size(); iObj++) { // for every object
    std::vector<glm::vec4> shape = objects[iObj]->getTransformedShape();

    for (int iVex = 0; iVex < shape.size(); // for every vertex in shape
         iVex++) {

      float *vertex = glm::value_ptr(shape[iVex]);
      for (int iVec = 0; iVec < 4; iVec++) { // for every vertex
        attributeVector.push_back(vertex[iVec]);
      }

      float *colors = glm::value_ptr(objects[iObj]->color);
      for (int iVec = 0; iVec < 3; iVec++) { // for every color
        attributeVector.push_back(colors[iVec]);
      }
    }
  }

  glBufferData(GL_ARRAY_BUFFER,
               attributeVector.size() * sizeof(attributeVector),
               attributeVector.data(), GL_STATIC_DRAW);

  // ENABLE VBO ATTRIBUTES
  // Vertices
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);

  // Colors
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                        (void *)(4 * sizeof(float)));

  glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
  glfwSwapBuffers(window);
}

void GraphicEngine::updateCameraUniform() {
  camera->syncMatrix();
  int cameraLoc = glGetUniformLocation(shader->ID, "camera");
  glUniformMatrix4fv(cameraLoc, 1, GL_FALSE,
                     glm::value_ptr(camera->modelMatrix));
}

void GraphicEngine::addObject(ShapeObject *newObject) {
  objects.push_back(newObject);
  objectsNeedUpdate = true;
}

void GraphicEngine::setupVBOandVAO() {
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO; // vertex buffer object
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBindVertexArray(VAO);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
}

void GraphicEngine::initOpenGL() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(
      (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }

  glViewport(0, 0, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);

  this->window = window;
  setupVBOandVAO();
}
