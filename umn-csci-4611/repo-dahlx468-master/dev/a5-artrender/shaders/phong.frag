#version 330
//Per-Pixel lighting - lighting is calculated once for each pixel

//position of light in eye space
in vec3 position_in_eye_space;

in vec3 normal_in_eye_space;

out vec4 color;

//Intensities
uniform vec3 light_in_eye_space;
uniform vec4 Ia, Id, Is;

//Material Parameters
uniform vec4 ka, kd, ks;
uniform float s;


void main() {
    //vec3 v = (model_view_matrix * vec4(vertex, 1)).xyz; dont need??
    //don't need v, use position in eye space
    //vec3 light = normalize(light_in_eye_space - v);
    //v = position in eye space
    //vec3 eyePoint = vec3(0, 0, 0) - v; or same as normalize(-v)
    
    vec3 normalEyeSpace = normalize(normal_in_eye_space);
    vec3 light = normalize(light_in_eye_space - position_in_eye_space);
    vec3 eyePoint = normalize(-position_in_eye_space);
    vec3 halfway = normalize(light + eyePoint);

    //Color = (Ka + Ia) + (Kd + Id * (n dot 1)) + (Ks * Is x (h dot n) to power s)
    color = (ka * Ia) + (kd * Id * dot(normalEyeSpace, light)) + (ks * Is * pow(dot(halfway, normalEyeSpace), s));
}
