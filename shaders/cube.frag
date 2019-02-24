#version 330 core

out vec4 color_out;

in vec3 FragPos;
in vec3 normal;
in vec2 TexCoords;


uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform sampler2D tex;

void main() {
    float ambient = 0.1;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diffuse = dot(norm, lightDir);
    diffuse = max(diffuse, 0);

    float spectularStrength = 0.5;

    vec3 reflectDir = reflect(-lightDir, norm);
    reflectDir = normalize(reflectDir);
    vec3 cameraDir = normalize(cameraPos - FragPos);
    float spectular = dot(reflectDir, cameraDir);
    spectular = max(spectular, 0) * spectularStrength;

    //texture

    vec4 col = texture(tex, TexCoords);

    vec3 result = (ambient + diffuse + spectular) * lightColor;
    color_out = vec4(result, 1.0f) * col;
}
