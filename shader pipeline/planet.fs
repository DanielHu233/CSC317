// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
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
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  vec3 ka = vec3(0.04,0.04,0.04);
  vec3 ks = vec3(1,1,1);
  vec3 kd;
  float p = 500;
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
    ks = vec3(0.3, 0.3, 0.3);
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }else{
    //add the effect of sea
    if(bump_height(is_moon, sphere_fs_in) > 0){
      float randomLand = abs(normalize(sphere_fs_in).x/1.5 + normalize(sphere_fs_in).y/2 + normalize(sphere_fs_in).z/2.5);
      kd = vec3(0.62 * randomLand, 0.55, 0.15);
      ks = vec3(0.1, 0.1, 0.1);
      //add north, south poles
      if(sphere_fs_in.y > 0.85 || sphere_fs_in.y < -0.76){
        kd = vec3(1, 1, 1);
      }
    }else{
      //polluted sea
      float randomSea = abs(normalize(sphere_fs_in).x/3 + normalize(sphere_fs_in).y/4 + normalize(sphere_fs_in).z/5);
      ks = vec3(0.7, 0.7, 0.7);
      kd = vec3(0.01, 0.013, 0.9 * randomSea);
    }

    //create wind effect on whole globe
    float wind = improved_perlin_noise((rotate_about_y(animation_seconds * M_PI) * vec4(sphere_fs_in, 1)).xyz);
    kd += wind * 2.7;
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
  /////////////////////////////////////////////////////////////////////////////
}
