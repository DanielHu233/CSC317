// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction( vec3 seed)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  vec2 sd = random2(seed);                   //random theta and phi
  //spherical coordinate
  vec3 direction_vec = vec3(
    sin(M_PI * sd.x) * cos(2 * M_PI * sd.y), //x
    sin(M_PI * sd.x) * sin(2 * M_PI * sd.y), //y
    cos(M_PI * sd.x)                         //z
  );
  //unit
  return normalize(direction_vec);
  /////////////////////////////////////////////////////////////////////////////
}
