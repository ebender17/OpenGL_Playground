#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

uniform mat4 u_MVP;

out vec4 v_Color;

void main()
{
    v_Color = color;
    gl_Position = u_MVP * vec4(position.x, position.y, position.z, 1.0f);
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;

void main()
{
    color = v_Color;
};