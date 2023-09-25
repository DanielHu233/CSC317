// Given a 3d position as a seed, compute an even smoother procedural noise
// value. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   st  3D seed
// Values between  -½ and ½ ?
//
// expects: random_direction, improved_smooth_step
float improved_perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  //consulted https://en.wikipedia.org/wiki/Perlin_noise
  int x0 = int(floor(st.x));
  int x1 = x0 + 1;
  int y0 = int(floor(st.y));
  int y1 = y0 + 1;
  int z0 = int(floor(st.z));
  int z1 = z0 + 1;

  //seeds
  vec3 v1 = vec3(x0, y0, z0);
  vec3 v2 = vec3(x1, y0, z0);
  vec3 v3 = vec3(x0, y1, z0);
  vec3 v5 = vec3(x0, y0, z1);
  vec3 v4 = vec3(x1, y1, z0);
  vec3 v6 = vec3(x1, y0, z1);
  vec3 v7 = vec3(x0, y1, z1);
  vec3 v8 = vec3(x1, y1, z1);

  //gradient vectors using seeds
  vec3 g1 = random_direction(v1);
  vec3 g2 = random_direction(v2);
  vec3 g3 = random_direction(v3);
  vec3 g4 = random_direction(v4);
  vec3 g5 = random_direction(v5);
  vec3 g6 = random_direction(v6);
  vec3 g7 = random_direction(v7);
  vec3 g8 = random_direction(v8);

  //secondly, computing the dot product between the gradient vectors and their offsets
  //offset being difference between the gradient vector and the seed
  float n1 = dot(g1, st - v1); 
  float n2 = dot(g2, st - v2);
  float n3 = dot(g3, st - v3);
  float n4 = dot(g4, st - v4);
  float n5 = dot(g5, st - v5);
  float n6 = dot(g6, st - v6);
  float n7 = dot(g7, st - v7);
  float n8 = dot(g8, st - v8);

  //finally, interpolation between these value 
  //f(x) = a0 + smoothstep(x) * (a1-a0)
  float fx1 = n1 + improved_smooth_step(st.x - float(x0)) * (n2 - n1);
  float fx2 = n3 + improved_smooth_step(st.x - float(x0)) * (n4 - n3);
  float fx3 = n5 + improved_smooth_step(st.x - float(x0)) * (n6 - n5);
  float fx4 = n7 + improved_smooth_step(st.x - float(x0)) * (n8 - n7);
  float fy1 = fx1 + improved_smooth_step(st.y - float(y0)) * (fx2 - fx1);
  float fy2 = fx3 + improved_smooth_step(st.y - float(y0)) * (fx4 - fx3);
  float fz = fy1 + improved_smooth_step(st.z - float(z0)) * (fy2 - fy1);
  return fz/6; //between -0.5 and 0.5
  /////////////////////////////////////////////////////////////////////////////
}

