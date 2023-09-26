#pragma once

#ifndef SHAPE_OBJECT_H_
#define SHAPE_OBJECT_H_

#include "../../lib/GLM/glm.hpp"
#include "graphic_engine_object.h"
#include <vector>

class ShapeObject : public GraphicEngineObject {
public:
  glm::vec3 color;
  std::vector<glm::vec4> shape;

  ShapeObject(std::vector<glm::vec4> shape, glm::vec3 color);
  std::vector<glm::vec4> getTransformedShape();
  void syncMatrix();
};
#endif // SHAPE_OBJECT_H_
