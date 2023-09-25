#include "insert_box_into_box.h"

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  B.min_corner(0) = fmin(A.min_corner(0), B.min_corner(0));
  B.max_corner(0) = fmax(A.max_corner(0), B.max_corner(0));
  B.min_corner(1) = fmin(A.min_corner(1), B.min_corner(1));
  B.max_corner(1) = fmax(A.max_corner(1), B.max_corner(1));
  B.min_corner(2) = fmin(A.min_corner(2), B.min_corner(2));
  B.max_corner(2) = fmax(A.max_corner(2), B.max_corner(2));
  ////////////////////////////////////////////////////////////////////////////
}

