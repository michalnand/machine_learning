#version 330


uniform float timer;

layout(location = 0) in vec4 position;

void main()
{
    mat3 rotation = mat3(
        vec3( cos(timer),  sin(timer),  0.0),
        vec3(-sin(timer),  cos(timer),  0.0),
        vec3(        0.0,         0.0,  1.0)
    );
    gl_Position = vec4(rotation * position.xyz, 1.0);
}
