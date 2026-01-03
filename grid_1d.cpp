#include "grid_1d.h"

Grid1D::Grid1D(int n, double L)
  : n_(n), dx_(L / (n - 1)), u_(static_cast<size_t>(n), 0.0)
{
}
