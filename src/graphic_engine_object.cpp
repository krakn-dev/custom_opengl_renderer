#include "h/graphic_engine_object.h"

GraphicEngineObject::GraphicEngineObject() {
  this->modelMatrix = glm::mat4(1.0f);
}
GraphicEngineObject::~GraphicEngineObject() {}
