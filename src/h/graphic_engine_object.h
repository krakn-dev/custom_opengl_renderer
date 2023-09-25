#pragma once

#ifndef GRAPHIC_ENGINE_OBJECT_H_
#define GRAPHIC_ENGINE_OBJECT_H_

#include "../../lib/GLM/glm.hpp"

class GraphicEngineObject {
public:
  glm::mat4 *modelMatrix;
  GraphicEngineObject(glm::mat4 *modelMatrix = nullptr);
  ~GraphicEngineObject();
};

#endif // GRAPHIC_ENGINE_OBJECT_H_
