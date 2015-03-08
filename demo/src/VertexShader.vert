#version 420

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;

out vec3 color;

uniform mat4 MVP;

void main () {
  color = vertex_color;
  vec4 pos = vec4(vertex_position, 1.0);
  gl_Position = MVP * pos;
}