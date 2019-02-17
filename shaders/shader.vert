#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Color;

out vec3 color;

uniform vec2 PositionOffset;

void main() {
	 gl_Position = vec4(Position.xy + PositionOffset, Position.z, 1.0f);
	 color = Color;
}
