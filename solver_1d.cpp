#include "solver_1d.h"
#include "heat_source.h"
#include "constants.h"
#include <vector>

static void solve_tridiagonal(std::vector<double> &a,
                              std::vector<double> &b,
                              std::vector<double> &c,
                              std::vector<double> &d)
{
  const int n = static_cast<int>(d.size());

  for (int i = 1; i < n; i++)
  {
    const double w = a[i] / b[i - 1];
    b[i] -= w * c[i - 1];
    d[i] -= w * d[i - 1];
  }

  d[n - 1] /= b[n - 1];
  for (int i = n - 2; i >= 0; i--)
    d[i] = (d[i] - c[i] * d[i + 1]) / b[i];
}

void step_implicit_1d(Grid1D & g, const Material & m,
                      double dt, double /*t*/, double L, double tmax, double fK)
{
  const int N = g.n();
  const double dx = g.dx();
  const double r = m.alpha() * dt / (dx * dx);

  std::vector<double> a(N, 0.0), b(N, 0.0), c(N, 0.0), d(N, 0.0);

  // Conditions:
  // Neumann en x=0 : du/dx=0 -> u0 - u1 = 0
  b[0] = 1.0; c[0] = -1.0; d[0] = 0.0;

  // Intérieur
  for (int i = 1; i < N - 1; i++)
  {
    a[i] = -r;
    b[i] = 1.0 + 2.0 * r;
    c[i] = -r;

    const double x = g.x(i);
    const double Fi = F1D(x, L, tmax, fK);
    d[i] = g.at(i) + dt * (Fi / (m.rho * m.c));
  }

  // Dirichlet en x=L : u = u0
  a[N - 1] = 0.0; b[N - 1] = 1.0; c[N - 1] = 0.0;
  d[N - 1] = Cst::u0_K();

  solve_tridiagonal(a, b, c, d);

  for (int i = 0; i < N; i++)
    g.at(i) = d[i];
}
