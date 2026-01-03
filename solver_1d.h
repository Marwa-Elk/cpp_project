#ifndef SOLVER1D_H
#define SOLVER1D_H

#include "grid_1d.h"
#include "material.h"

/// @brief Résout la barre 1D avec schéma implicite.
/// @param g grille (u est modifié in-place)
/// @param m matériau
/// @param dt pas de temps
/// @param t temps courant (pour F si besoin)
/// @param L longueur
/// @param tmax temps max
/// @param fK paramètre f en Kelvin (selon sujet)
void step_implicit_1d(Grid1D & g, const Material & m,
                      double dt, double t, double L, double tmax, double fK);

#endif
