#ifndef HEAT_SOURCE_H
#define HEAT_SOURCE_H

/// @brief Source de chaleur 1D selon l'énoncé.
/// F(x) = tmax*f/2 sur [L/10,2L/10], 3/4*tmax*f/2 sur [5L/10,6L/10], 0 sinon.
double F1D(double x, double L, double tmax, double fK);

/// @brief Source de chaleur 2D selon l'énoncé : 4 carrés.
double F2D(double x, double y, double L, double tmax, double fK);

#endif
