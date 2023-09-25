#include "h/input_handler.h"

class InputHandler {
  void mouseEventSubscribers(void (*callback)()) { callback(); }
};
