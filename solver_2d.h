#ifndef SOLVER2D_H
#define SOLVER2D_H

#include "grid_2d.h"
#include "material.h"

/// @brief Un pas de temps implicite 2D via Gauss-Seidel.
/// @param max_iter nb itérations GS
/// @param eps critère d'arrêt (diff max)
void step_implicit_2d(Grid2D & g, const Material & m,
                      double dt, double t, double L, double tmax, double fK,
                      int max_iter, double eps);

#endif
