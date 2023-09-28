#include "h/action_behavior.h"
#include "h/utilities.h"
#include <chrono>
#include <functional>

ActionBehavior::ActionBehavior(
    std::function<void(CallbackArguments)> callback) {
  this->callback = callback;
  ID = std::chrono::system_clock::now().time_since_epoch().count();
}
