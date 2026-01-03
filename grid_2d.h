#ifndef GRID2D_H
#define GRID2D_H

#include <vector>

/// @brief Grille 2D : u(i,j) sur [0,L]^2 stockée en tableau 1D.
class Grid2D
{
public:
  Grid2D(int n, double L);

  int n() const { return n_; }
  double dx() const { return dx_; }
  double x(int i) const { return i * dx_; }
  double y(int j) const { return j * dx_; }

  double & at(int i, int j) { return u_[idx(i,j)]; }
  double at(int i, int j) const { return u_[idx(i,j)]; }

  const std::vector<double> & data() const { return u_; }

private:
  int n_;
  double dx_;
  std::vector<double> u_;

  int idx(int i, int j) const { return j * n_ + i; }
};

#endif
