#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Uniforms for light properties
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;
uniform float hp;
// Output value to fragment shader
out vec3 color;

void main()
{
    // Compute world space vectors
    vec3 world_position = (Model * vec4(v_position, 1)).xyz;

    float maxHP = 5;
    float maxDeformation = 0.5;  // Example: Limiting deformation to 50%
    float deformationFactor = min(1.0, maxDeformation * (1.0 - smoothstep(0.0, 1.0, hp / maxHP)));

    // Apply displacement to the world position
    vec3 displaced_world_position = world_position + v_normal * deformationFactor;

    // Compute world normal
    vec3 world_normal = normalize(mat3(Model) * normalize(v_normal));

    // Compute lighting vectors
    vec3 L = normalize(light_position - displaced_world_position);
    vec3 V = normalize(eye_position - displaced_world_position);
    vec3 H = normalize(L + V);

    // Define ambient light component
    float ambient_light = 0.75;

    // Compute diffuse light component
    float diffuse_light = material_kd * max(dot(world_normal, L), 0);

    // Compute specular light component
    float specular_light = 0;

    if (diffuse_light > 0) {
        specular_light = material_ks * pow(max(dot(world_normal, H), 0), material_shininess);
    }

    // Compute light
    float d = distance(light_position, v_position);
    float attenuation_factor = 1 / (1 + 0.14 * d + 0.07 * d * d);
    float light = ambient_light + attenuation_factor * (diffuse_light + specular_light);

    // Apply the color modification based on health points
    vec3 final_object_color = object_color;

    if (hp < 5) {
        vec3 original_color = object_color;
        vec3 dark_color = vec3(0.1, 0.1, 0.1);
        float lerp_factor = (maxHP - hp) / (maxHP - 1.0);
        final_object_color = mix(original_color, dark_color, lerp_factor);

        if (hp < 1) {
            final_object_color = dark_color;
        }
    }

    // Send color light output to fragment shader
    color = final_object_color * light;

    // Apply displacement to the vertex position
    vec3 displaced_position = v_position + v_normal * deformationFactor;

    // Apply the transformation matrices
    gl_Position = Projection * View * Model * vec4(displaced_position, 1.0);
}
