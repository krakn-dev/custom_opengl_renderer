#pragma once

#ifndef GRAPHIC_ENGINE_H_
#define GRAPHIC_ENGINE_H_

#include "../../lib/GLAD/glad.h"
#include "../../lib/GLFW/glfw3.h"
#include "../../lib/GLM/glm.hpp"
#include "../../lib/GLM/gtc/matrix_transform.hpp"
#include "../../lib/GLM/gtc/type_ptr.hpp"
#include "camera_object.h"
#include "shader.h"
#include "shape_object.h"
#include <vector>

class GraphicEngine {
public:
  GLFWwindow *window;
  CameraObject *camera;

  GraphicEngine();
  void render();
  void addObject(ShapeObject *newObject);
  void addCamera(CameraObject *newCamera);

private:
  std::vector<ShapeObject *> objects;
  Shader *shader;

  bool objectsNeedUpdate;
  void updateCameraUniform();
  void setupVBOandVAO();
  void compileShader();
  void initOpenGL();
};
#endif // GRAPHIC_ENGINE_H_
