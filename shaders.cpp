#include "shaders.h"

// @FixIt don't use iostream, stringstream or any of this crap
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

GLuint load_shader(const char* shader_code, GLenum shader_type) {
  GLuint shader_id = glCreateShader(shader_type);

  glShaderSource(shader_id, 1, &shader_code, NULL);
  glCompileShader(shader_id);

  GLint result = GL_FALSE;
  int info_log_length;

  // Check Vertex Shader
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
  glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

  if (info_log_length > 0) {
    std::vector<char> shader_error_message(info_log_length+1);
    glGetShaderInfoLog(shader_id, info_log_length, NULL, &shader_error_message[0]);

    // @FixIt should log
    printf("%s\n", &shader_error_message[0]);
  }

  return shader_id;
}

GLuint load_shaders(const char* vertex_file_path, const char* fragment_file_path){
  printf("Loading shaders\n");

  // Read the Vertex Shader code from the file
  std::string vertex_shader_code;
  std::ifstream vertex_shader_stream(vertex_file_path, std::ios::in);
  if (vertex_shader_stream.is_open()) {
    std::stringstream sstr;
    sstr << vertex_shader_stream.rdbuf();
    vertex_shader_code = sstr.str();
    vertex_shader_stream.close();
  } else {
    printf("Impossible to open %s.\n", vertex_file_path);
    return 0;
  }

  // Compile vertex shader
  printf("Compiling shader : %s\n", vertex_file_path);
  GLuint vertex_shader_id = load_shader(vertex_shader_code.c_str(), GL_VERTEX_SHADER);

  // Read the Fragment Shader code from the file
  std::string fragment_shader_code;
  std::ifstream fragment_shader_stream(fragment_file_path, std::ios::in);
  if (fragment_shader_stream.is_open()) {
    std::stringstream sstr;
    sstr << fragment_shader_stream.rdbuf();
    fragment_shader_code = sstr.str();
    fragment_shader_stream.close();
  }

  // Compile fragment shader
  printf("Compiling shader : %s\n", fragment_file_path);
  GLuint fragment_shader_id = load_shader(fragment_shader_code.c_str(), GL_FRAGMENT_SHADER);

  // Link the program
  printf("Linking program\n");
  GLuint program_id = glCreateProgram();
  glAttachShader(program_id, vertex_shader_id);
  glAttachShader(program_id, fragment_shader_id);
  glLinkProgram(program_id);

  // Check the program
  GLint result = GL_FALSE;
  int info_log_length;

  glGetProgramiv(program_id, GL_LINK_STATUS, &result);
  glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
  if (info_log_length > 0) {
    std::vector<char> program_error_message(info_log_length+1);
    glGetProgramInfoLog(program_id, info_log_length, NULL, &program_error_message[0]);

    // @FixIt logger
    printf("%s\n", &program_error_message[0]);
  }

  glDetachShader(program_id, vertex_shader_id);
  glDetachShader(program_id, fragment_shader_id);

  glDeleteShader(vertex_shader_id);
  glDeleteShader(fragment_shader_id);

  return program_id;
}
