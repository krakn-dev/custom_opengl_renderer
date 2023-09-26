#include "h/shape_object.h"
#include "../lib/GLM/gtc/matrix_transform.hpp"
#include "../lib/GLM/gtx/string_cast.hpp"
#include "h/camera_object.h"
#include <iostream>
#include <vector>

ShapeObject::ShapeObject(std::vector<glm::vec4> shape, glm::vec3 color) {
  if (shape.size() == 0) {
    std::cout << "no shape?\n";
  }
  this->shape = shape;
  this->color = color;
}

void ShapeObject::syncMatrix() {

  // TODO rotation
  //
  // *GraphicEngineObject::modelMatrix =
  // glm::rotate(*GraphicEngineObject::modelMatrix,
  // glm::radians(*GraphicEngineObject::rotation),
  //             *rotationAxis);
  GraphicEngineObject::modelMatrix = glm::translate(
      GraphicEngineObject::modelMatrix, GraphicEngineObject::position);
}

std::vector<glm::vec4> ShapeObject::getTransformedShape() {
  std::vector<glm::vec4> transformedShape = {};
  for (int i = 0; i < shape.size(); i++) {
    //    std::cout << glm::to_string(modelMatrix) << std::endl;
    transformedShape.push_back(GraphicEngineObject::modelMatrix * shape[i]);
  }
  return transformedShape;
}
