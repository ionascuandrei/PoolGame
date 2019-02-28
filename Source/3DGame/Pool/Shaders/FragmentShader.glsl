#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform float cut_off;
uniform int isCue;

uniform vec3 object_color;

layout(location = 0) out vec4 out_color;

void main()
{

	vec3 world_norm = normalize(world_normal);
	vec3 world_pos = world_position;

	// TODO: define ambient light component
	float ambient_light = 0.40;

	// TODO: compute diffuse light component
	float diffuse_light = max(dot( normalize(light_position - world_pos) , world_norm), 0) * 1 * material_kd;

	// TODO: compute specular light component
	float specular_light = pow(max(dot( reflect(-normalize(light_position - world_pos), world_norm)  , normalize(eye_position - world_pos) ), 0), material_shininess) * 1 * material_ks;

	// TODO: compute light
	float I = ambient_light + (diffuse_light + specular_light) * (1 / pow(distance(world_pos, light_position), 2) );


	float spot_light = dot(-normalize(light_position - world_pos), light_direction);
	float spot_light_limit = cos(cut_off);
	float linear_att;
	float light_att_factor;

	linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
	light_att_factor = pow(linear_att, 2);
	
	if(cut_off == 30){
		if (spot_light > cos(cut_off)){
			// fragmentul este iluminat de spot, deci se calculeaza valoarea luminii conform  modelului Phong
			// se calculeaza atenuarea luminii
			out_color = (ambient_light + (diffuse_light + specular_light) * light_att_factor) * vec4(object_color, 1);
			
		} 
		else {
			out_color = ambient_light * vec4(object_color, 1);
		}
	} else {
		out_color = I * vec4(object_color, 1);
	}

	

	

}