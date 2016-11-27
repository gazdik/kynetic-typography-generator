#version 330 core

in vec3 position;

uniform mat4 transform;
uniform mat4 size;
uniform vec3 color;
uniform float alpha;

out vec4 c;

void main()
{
  gl_Position = transform * size * vec4(position, 1.0f);
  c = vec4(color, alpha);
}
