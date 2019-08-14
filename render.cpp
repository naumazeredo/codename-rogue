// @Todo use indexes
// @Todo multiple program_ids
// @Performance use GL_STREAM_DRAW and GL_DYNAMIC_DRAW instead of rebuilding the buffer

#include "render.h"

#include <vector>
#include <SDL.h>
#include "shaders.h"

GLuint vertex_array_id;
GLuint vertex_buffer_object;
GLuint color_buffer_object;
GLuint program_id;

std::vector<f32> vertex_buffer;
std::vector<f32> color_buffer;

//
// Test
//

extern f32 frequency;

GLuint frequency_uniform;
GLuint time_uniform;

//
// Test
//

void setup_rendering() {
  glGenVertexArrays(1, &vertex_array_id);

  glGenBuffers(1, &vertex_buffer_object);
  glGenBuffers(1, &color_buffer_object);
}

void cleanup_rendering() {
  glDeleteProgram(program_id);

  glDeleteBuffers(1, &vertex_buffer_object);
  glDeleteBuffers(1, &color_buffer_object);

  glDeleteVertexArrays(1, &vertex_array_id);
}

void load_shaders() {
  program_id = load_shaders("data/shaders/timedcolored.vertexshader", "data/shaders/colored.fragmentshader");

  time_uniform = glGetUniformLocation(program_id, "time");
  frequency_uniform = glGetUniformLocation(program_id, "frequency");
}

void add_to_render(f32 x, f32 y, f32 w, f32 h, f32 z) {
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

void bind_buffers() {
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(f32) * vertex_buffer.size(),
               &vertex_buffer[0],
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ARRAY_BUFFER, color_buffer_object);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(f32) * color_buffer.size(),
               &color_buffer[0],
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/*
internal
void update_buffers() {
  std::vector<f32> new_vertex_buffer = vertex_buffer;
  for (u32 i = 0; i < new_vertex_buffer.size(); i += 3) {
    new_vertex_buffer[i  ] += offset_x;
    new_vertex_buffer[i+1] += offset_y;
  }

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(f32) * new_vertex_buffer.size(), &new_vertex_buffer[0]);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
*/

void render() {
  glBindVertexArray(vertex_array_id);

  //update_buffers();

  glUseProgram(program_id);

  glUniform1f(time_uniform, SDL_GetTicks() / 1000.0f);
  glUniform1f(frequency_uniform, frequency);

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
