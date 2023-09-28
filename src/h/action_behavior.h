#ifndef ACTION_BEHAVIOR_H_
#define ACTION_BEHAVIOR_H_

#include "./utilities.h"
#include <chrono>
#include <functional>

class ActionBehavior {
public:
  int ID;
  bool sumOutputVectors;
  std::function<void(CallbackArguments)> callback;
  std::vector<std::vector<GLFW_KEY>> triggerInputs;
  std::vector<CallbackArguments> triggerOutputs;
  ActionBehavior(std::function<void(CallbackArguments)> callback);
};

#endif // ACTION_BEHAVIOR_H_
