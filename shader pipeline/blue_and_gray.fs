// Set the pixel color to blue or gray depending on is_moon.
//
// Uniforms:
uniform bool is_moon;
// Outputs:
out vec3 color;
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code:
  if(is_moon){
    color = vec3(0.58, 0.5, 0.5);//grey
  }else{
    color = vec3(0.13, 0.2, 0.68);//blue
  }
  /////////////////////////////////////////////////////////////////////////////
}
