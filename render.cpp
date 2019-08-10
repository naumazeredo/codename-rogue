// @Todo use indexes
// @Todo multiple program_ids

#include "render.h"

#include <vector>
#include "shaders.h"

GLuint vertex_array_id;
GLuint vertex_buffer_object;
GLuint color_buffer_object;
GLuint program_id;

std::vector<float> vertex_buffer;
std::vector<float> color_buffer;

void setup_rendering() {
  glGenVertexArrays(1, &vertex_array_id);

  glGenBuffers(1, &vertex_buffer_object);
  glGenBuffers(1, &color_buffer_object);

  program_id = load_shaders("data/shaders/colored.vertexshader", "data/shaders/colored.fragmentshader");
}

void cleanup_rendering() {
  glDeleteProgram(program_id);

  glDeleteBuffers(1, &vertex_buffer_object);
  glDeleteBuffers(1, &color_buffer_object);

  glDeleteVertexArrays(1, &vertex_array_id);
}

void add_to_render(float x, float y, float w, float h, float z) {
  // first triangle
  vertex_buffer.push_back(x);
  vertex_buffer.push_back(y);
  vertex_buffer.push_back(z);

  vertex_buffer.push_back(x+w);
  vertex_buffer.push_back(y);
  vertex_buffer.push_back(z);

  vertex_buffer.push_back(x+w);
  vertex_buffer.push_back(y+h);
  vertex_buffer.push_back(z);


  color_buffer.push_back(1.0f);
  color_buffer.push_back(0.0f);
  color_buffer.push_back(0.0f);

  color_buffer.push_back(0.0f);
  color_buffer.push_back(1.0f);
  color_buffer.push_back(0.0f);

  color_buffer.push_back(0.0f);
  color_buffer.push_back(0.0f);
  color_buffer.push_back(1.0f);

  // second triangle
  vertex_buffer.push_back(x+w);
  vertex_buffer.push_back(y+h);
  vertex_buffer.push_back(z);

  vertex_buffer.push_back(x);
  vertex_buffer.push_back(y+h);
  vertex_buffer.push_back(z);

  vertex_buffer.push_back(x);
  vertex_buffer.push_back(y);
  vertex_buffer.push_back(z);


  color_buffer.push_back(0.0f);
  color_buffer.push_back(0.0f);
  color_buffer.push_back(1.0f);

  color_buffer.push_back(0.0f);
  color_buffer.push_back(1.0f);
  color_buffer.push_back(0.0f);

  color_buffer.push_back(1.0f);
  color_buffer.push_back(0.0f);
  color_buffer.push_back(0.0f);
}

void render() {
  glBindVertexArray(vertex_array_id);

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(float) * vertex_buffer.size(),
               &vertex_buffer[0],
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ARRAY_BUFFER, color_buffer_object);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(float) * color_buffer.size(),
               &color_buffer[0],
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glUseProgram(program_id);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  // vertex position
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  // vertex colors
  glBindBuffer(GL_ARRAY_BUFFER, color_buffer_object);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glDrawArrays(GL_TRIANGLES, 0, vertex_buffer.size());

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
