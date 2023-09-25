#pragma once

#ifndef shader_h
#define shader_h

#include "../../lib/GLAD/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
  Shader(const char *vertexPath, const char *fragmentPath);
  unsigned int ID;
  void use();
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;

private:
  void checkCompileErrors(unsigned int shader, std::string type);
};
#endif
