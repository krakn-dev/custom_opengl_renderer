#pragma once

#ifndef CAMERA_OBJECT_H_
#define CAMERA_OBJECT_H_

#include "../../lib/GLM/glm.hpp"
#include "graphic_engine_object.h"
#include "input_manager.h"

class CameraObject : public GraphicEngineObject {
public:
  glm::vec3 cameraFront;
  bool firstMouse;
  glm::mat4 projectionMatrix;
  double lastXPosition;
  double lastYPosition;
  float speed;

  CameraObject();
  void setProjectionMatrix(float fov, float windowWidth, float windowHeight,
                           float near, float far);
  void syncMatrix();
  void onLookAround(GLFWwindow *window, double xPos, double yPos);
  void onMovement(CallbackArguments direction);
};

class MovementAction : public ActionBehavior {
public:
  MovementAction(std::function<void(CallbackArguments)> callback);
};

#endif // CAMERA_OBJECT_H_
