#shader vertex
#version 330 core
//#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 v_normal;
out vec2 v_texCoord;
out vec3 v_world_pos;


uniform mat4 u_MVP;

void main()
{
	v_world_pos = position;
	gl_Position = u_MVP * vec4(position,1);
	v_texCoord 	= texCoord;
	v_normal 	= -normal;
};



//--------------------------------------------------------------------
#shader fragment 
#version 330 core

#define MAX_DIRECTR_LIGHT_COUNT 4
struct DirLght
{
	vec4 direction;
	vec4 color;
	vec4 specular;
	float intensity;
};

in vec3 v_normal;
in vec2 v_texCoord;
in vec4 v_color;
in vec3 v_world_pos;

uniform vec3 u_ambient;
layout(std140) uniform DirectLight
{
	uint  	DirectLightCount;	
	DirLght DL[MAX_DIRECTR_LIGHT_COUNT];
};


out vec4 color;

//uniform sampler2D u_Texture;


void main()
{
	vec3 dir_color = vec3(0.0);
	for (uint i = 0u; i < DirectLightCount; ++i)
	{
		dir_color += DL[i].color.xyz * clamp(dot(v_normal,DL[i].direction.xyz),0,1) * DL[i].intensity;
	}
	color = vec4(dir_color + u_ambient,1);
	//color = vec4(v_texCoord,1,1);
};
