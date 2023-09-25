#include "h/shape_object.h"
#include "../lib/GLM/gtc/matrix_transform.hpp"
#include "h/camera_object.h"
#include <iostream>
#include <vector>
#include "../lib/GLM/gtx/string_cast.hpp"

ShapeObject::ShapeObject(glm::mat4 *modelMatrix, std::vector<glm::vec4> shape,
                         glm::vec3 *color)
    : GraphicEngineObject(modelMatrix) {
  if (shape.size() == 0) {
    std::cout << "no shape?\n";
  }
  this->shape = shape;
  this->color = color;
}
void ShapeObject::setModelMatrixRotation(float *rotationDegrees,
                                         glm::vec3 *rotationAxis) {
  *GraphicEngineObject::modelMatrix =
      glm::rotate(*GraphicEngineObject::modelMatrix,
                  glm::radians(*rotationDegrees), *rotationAxis);
}
void ShapeObject::setModelMatrixTransform(glm::vec3 *translation) {
  *GraphicEngineObject::modelMatrix =
      glm::translate(*GraphicEngineObject::modelMatrix, *translation);
}

void ShapeObject::applyModel() {
  for (int i = 0; i < shape.size(); i++) {
    std::cout << glm::to_string(shape[i])<< std::endl;

    std::cout << "________________--"<< std::endl;
    shape[i] = *modelMatrix * shape[i];
    std::cout << glm::to_string(shape[i])<< std::endl;
  }
}
