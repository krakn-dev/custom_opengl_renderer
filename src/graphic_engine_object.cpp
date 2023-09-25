#include "h/graphic_engine_object.h"

GraphicEngineObject::GraphicEngineObject(glm::mat4 *modelMatrix) {
  this->modelMatrix =
      modelMatrix != nullptr ? modelMatrix : new glm::mat4(1.0f);
}
GraphicEngineObject::~GraphicEngineObject() { delete modelMatrix; }
