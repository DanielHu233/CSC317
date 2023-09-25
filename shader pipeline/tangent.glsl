// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  T = normalize(vec3(cross(vec3(1, 1, 1), N)));
  B = normalize(vec3(cross(N, T)));
  /////////////////////////////////////////////////////////////////////////////
}
