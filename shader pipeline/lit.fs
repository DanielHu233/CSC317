// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: PI, blinn_phong
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  vec3 ka = vec3(0.04,0.04,0.04);
  vec3 ks = vec3(1,1,1);
  vec3 kd;
  float p = 1000;
  //surface normal
  vec3 n = normalize(normal_fs_in);
  //point to eye
  vec3 v = -1 * normalize(view_pos_fs_in.xyz);
  //light direction
  float theta = M_PI * animation_seconds / 4;
  vec4 angle = view * vec4(4 * cos(theta), 2.7, 4 * sin(theta), 1); //define the incident angle
  vec3 l = normalize(angle.xyz - view_pos_fs_in.xyz);

  if(is_moon){
    kd = vec3(0.58, 0.5, 0.5);
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }else{
    kd = vec3(0.13, 0.2, 0.68);
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
  /////////////////////////////////////////////////////////////////////////////
}
