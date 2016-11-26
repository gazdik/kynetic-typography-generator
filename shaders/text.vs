#version 330 core

in vec3 position;
in vec3 normal;

uniform mat4 transform;
uniform vec3 pen;

uniform mat4 scale;
uniform vec3 color;
uniform float alpha;

out vec4 c;

void main()
{
  gl_Position = transform * scale * (vec4(position, 1.0f) + vec4(pen, 1.0));
  c = vec4(color + normal * 0.1, alpha);
}
