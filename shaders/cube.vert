#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 texCoords;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 normal;
out vec2 TexCoords;

void main() {
     TexCoords = texCoords;
	 normal = transpose(inverse(mat3(model))) * Normal;
	 FragPos = vec3(model * vec4(Position, 1.0f));
	 gl_Position = projection * view * model * vec4(Position, 1.0f);
}
