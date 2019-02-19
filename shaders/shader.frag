#version 330 core

in vec2 TexCoords;
out vec4 color_out;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    vec4 tex1 = texture(texture1, TexCoords);
    vec4 tex2 = texture(texture2, TexCoords);
	color_out = mix(tex1, tex2, tex2.a);
}
