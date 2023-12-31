// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  if(is_moon){
  	float noise = improved_perlin_noise(3 * s);
  	return 0.07 * max(smooth_heaviside(noise, 8), -0.02);
  }else{
  	float noise = improved_perlin_noise(2.6 * s);
  	return 0.1 * max(smooth_heaviside(noise, 45), 0);
  }
  /////////////////////////////////////////////////////////////////////////////
}
