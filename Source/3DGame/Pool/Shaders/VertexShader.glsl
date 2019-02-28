#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform int isCue;
uniform float ElapsedTime;
uniform vec3 ballPosition;

// Output values to fragment shader
out vec3 world_position;
out vec3 world_normal;

void main()
{
	// TODO: compute world space vertex position and normal
	world_position = (Model * vec4(v_position, 1.0)).xyz;
	world_normal = mat3(Model) * v_normal;

	vec3 auxPos;
	vec4 aux;
	if(isCue == 1){
		aux = Model * vec4(v_position, 1.0);
		vec4 forward = normalize(vec4(aux.x,aux.y - 0.4f,aux.z, 1.0f) - vec4(ballPosition, 1.0f));
		aux += (ElapsedTime /4.0f) * normalize(forward);
		auxPos = vec3(aux.x , aux.y , aux.z);
		gl_Position = Projection * View * vec4(auxPos, 1.0);
	} else {
		gl_Position = Projection * View * Model * vec4(v_position, 1.0);
	}
}
