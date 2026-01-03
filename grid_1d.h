#ifndef GRID1D_H
#define GRID1D_H

#include <vector>

/// @brief Grille 1D : u[i] sur x in [0,L].
class Grid1D
{
public:
  Grid1D(int n, double L);

  int n() const { return n_; }
  double dx() const { return dx_; }
  double x(int i) const { return i * dx_; }

  double & at(int i) { return u_[i]; }
  double at(int i) const { return u_[i]; }

  const std::vector<double> & data() const { return u_; }

private:
  int n_;
  double dx_;
  std::vector<double> u_;
};

#endif
