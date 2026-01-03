#include "solver_2d.h"
#include "heat_source.h"
#include "constants.h"
#include <algorithm>
#include <cmath>

static double get_neumann_x0(const Grid2D &g, int i, int j)
{
  // x=0 : u(-1,j)=u(1,j) => pour i=0, voisin gauche = u(1,j)
  if (i == 0) return g.at(1, j);
  return g.at(i - 1, j);
}

static double get_neumann_y0(const Grid2D &g, int i, int j)
{
  // y=0 : u(i,-1)=u(i,1) => pour j=0, voisin bas = u(i,1)
  if (j == 0) return g.at(i, 1);
  return g.at(i, j - 1);
}

void step_implicit_2d(Grid2D & g, const Material & m,
                      double dt, double /*t*/, double L, double tmax, double fK,
                      int max_iter, double eps)
{
  const int N = g.n();
  const double dx = g.dx();
  const double r = m.alpha() * dt / (dx * dx);
  const double denom = 1.0 + 4.0 * r;

  // Pré-calcul rhs = u^n + dt * F/(rho*c)  (stocké dans u_old virtuel via lecture)
  // On ne copie pas tout (trop gros), on lit u^n via une seconde grille ? => non.
  // Ici, on fait une copie locale minimale: on copie la data (coûteux mais simple).
  // Si trop lent, réduire N / optimiser.
  Grid2D old = g;

  for (int iter = 0; iter < max_iter; iter++)
  {
    double max_diff = 0.0;

    for (int j = 0; j < N; j++)
    {
      for (int i = 0; i < N; i++)
      {
        // Dirichlet x=L ou y=L
        if (i == N - 1 || j == N - 1)
        {
          const double prev = g.at(i, j);
          g.at(i, j) = Cst::u0_K();
          max_diff = std::max(max_diff, std::abs(g.at(i, j) - prev));
          continue;
        }

        const double x = g.x(i);
        const double y = g.y(j);
        const double F = F2D(x, y, L, tmax, fK);
        const double rhs = old.at(i, j) + dt * (F / (m.rho * m.c));

        // Voisins avec Neumann sur x=0 et y=0
        const double uL = get_neumann_x0(g, i, j);
        const double uR = (i == N - 2) ? Cst::u0_K() : g.at(i + 1, j);
        const double uD = get_neumann_y0(g, i, j);
        const double uU = (j == N - 2) ? Cst::u0_K() : g.at(i, j + 1);

        const double new_u = (rhs + r * (uL + uR + uD + uU)) / denom;

        const double prev = g.at(i, j);
        g.at(i, j) = new_u;
        max_diff = std::max(max_diff, std::abs(new_u - prev));
      }
    }

    if (max_diff < eps)
      return;
  }
}
