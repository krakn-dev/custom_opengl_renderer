#pragma once

#ifndef SHAPE_OBJECT_H_
#define SHAPE_OBJECT_H_

#include "../../lib/GLM/glm.hpp"
#include "graphic_engine_object.h"
#include <vector>

class ShapeObject : public GraphicEngineObject {
public:
  glm::vec3 *color;
  std::vector<glm::vec4> shape;

  ShapeObject(glm::mat4 *modelMatrix, std::vector<glm::vec4> shape,
              glm::vec3 *color);
  void setModelMatrixRotation(float *rotationDegrees, glm::vec3 *rotationAxis);
  void setModelMatrixTransform(glm::vec3 *translation);
  void applyModel();
};
#endif // SHAPE_OBJECT_H_
