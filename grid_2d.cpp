#include "grid_2d.h"

Grid2D::Grid2D(int n, double L)
  : n_(n), dx_(L / (n - 1)), u_(static_cast<size_t>(n) * static_cast<size_t>(n), 0.0)
{
}
