// Set the pixel color using Blinn-Phong shading (e.g., with constant blue and
// gray material color) with a bumpy texture.
// 
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
//                     linearly interpolated from tessellation evaluation shader
//                     output
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
//               rgb color of this pixel
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  vec3 ka = vec3(0.04,0.04,0.04);
  vec3 ks = vec3(1,1,1);
  vec3 kd;
  float p = 1000;
  //surface normal
  //first get tangent and bi-tangent
  vec3 T, B;
  tangent(normalize(sphere_fs_in), T, B);
  //epsilon taking 0.0001
  float epsilon = 0.0001;
  vec3 n = normalize(cross((bump_position(is_moon, sphere_fs_in + T * epsilon) - bump_position(is_moon, sphere_fs_in))/epsilon, 
                    (bump_position(is_moon, sphere_fs_in + B * epsilon) - bump_position(is_moon, sphere_fs_in))/epsilon)
           );
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
