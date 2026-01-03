#include "heat_source.h"

static bool in_interval(double a, double b, double x)
{
  return (x >= a) && (x <= b);
}

double F1D(double x, double L, double tmax, double fK)
{
  const double A = tmax * fK / 2.0;

  if (in_interval(L/10.0, 2.0*L/10.0, x))
    return A;

  if (in_interval(5.0*L/10.0, 6.0*L/10.0, x))
    return 0.75 * A;

  return 0.0;
}

static bool in_square(double x, double y, double ax, double bx, double ay, double by)
{
  return in_interval(ax, bx, x) && in_interval(ay, by, y);
}

double F2D(double x, double y, double L, double tmax, double fK)
{
  const double A = tmax * fK / 2.0;

  const double a1 = L/6.0, b1 = 2.0*L/6.0;
  const double a2 = 4.0*L/6.0, b2 = 5.0*L/6.0;

  if (in_square(x,y, a1,b1, a1,b1)) return A;
  if (in_square(x,y, a2,b2, a1,b1)) return A;
  if (in_square(x,y, a1,b1, a2,b2)) return A;
  if (in_square(x,y, a2,b2, a2,b2)) return A;

  return 0.0;
}
