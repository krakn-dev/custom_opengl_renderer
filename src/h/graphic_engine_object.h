#pragma once

#ifndef GRAPHIC_ENGINE_OBJECT_H_
#define GRAPHIC_ENGINE_OBJECT_H_

#include "../../lib/GLM/glm.hpp"

class GraphicEngineObject {
public:
  glm::mat4 modelMatrix;
  glm::vec3 position;
  glm::vec3 rotation;

  GraphicEngineObject();
  ~GraphicEngineObject();
  void syncMatrix();
};

#endif // GRAPHIC_ENGINE_OBJECT_H_
