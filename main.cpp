#include "constants.h"
#include "material.h"
#include "grid_1d.h"
#include "grid_2d.h"
#include "solver_1d.h"
#include "solver_2d.h"
#include "sdl_view.h"
#include <iostream>
#include <algorithm>

static void minmax_1d(const Grid1D &g, double &mn, double &mx)
{
  mn = g.at(0); mx = g.at(0);
  for (int i = 1; i < g.n(); i++)
  {
    mn = std::min(mn, g.at(i));
    mx = std::max(mx, g.at(i));
  }
}

static void minmax_2d(const Grid2D &g, double &mn, double &mx)
{
  mn = g.at(0,0); mx = g.at(0,0);
  for (int j = 0; j < g.n(); j++)
    for (int i = 0; i < g.n(); i++)
    {
      mn = std::min(mn, g.at(i,j));
      mx = std::max(mx, g.at(i,j));
    }
}

static void run_bar_1d(const Material &m)
{
  Grid1D g(Cst::N, Cst::L);
  for (int i = 0; i < g.n(); i++) g.at(i) = Cst::u0_K();

  const double dt = Cst::tmax / (Cst::Nt - 1);
  SdlView view("Chaleur 1D - " + m.name, 900, 300);

  for (int frame = 0; frame < Cst::Nframes; frame++)
  {
    const int n_target = frame * (Cst::Nt - 1) / (Cst::Nframes - 1);

    for (int n = 0; n < n_target; n++)
      step_implicit_1d(g, m, dt, n * dt, Cst::L, Cst::tmax, Cst::f_K());

    double mn, mx;
    minmax_1d(g, mn, mx);

    if (!view.process_events()) return;
    view.clear();
    view.draw_curve_1d(g.data(), mn, mx);
    view.present();
    SDL_Delay(20);
  }
}

static void run_plate_2d(const Material &m)
{
  Grid2D g(Cst::N, Cst::L);
  for (int j = 0; j < g.n(); j++)
    for (int i = 0; i < g.n(); i++)
      g.at(i,j) = Cst::u0_K();

  const double dt = Cst::tmax / (Cst::Nt - 1);
  SdlView view("Chaleur 2D - " + m.name, 600, 600);

  const int max_iter = 30;      // à ajuster selon machine
  const double eps = 1e-3;      // à ajuster (K)

  for (int frame = 0; frame < Cst::Nframes; frame++)
  {
    const int n_target = frame * (Cst::Nt - 1) / (Cst::Nframes - 1);

    for (int n = 0; n < n_target; n++)
      step_implicit_2d(g, m, dt, n * dt, Cst::L, Cst::tmax, Cst::f_K(), max_iter, eps);

    double mn, mx;
    minmax_2d(g, mn, mx);

    if (!view.process_events()) return;
    view.clear();
    view.draw_heatmap_2d(g.data(), g.n(), mn, mx);
    view.present();
    SDL_Delay(20);
  }
}

int main(int argc, char **argv)
{
  Material mats[4];
  get_all_materials(mats);

  for (int k = 0; k < 4; k++)
  {
    std::cout << "Materiau: " << mats[k].name << std::endl;

    // Partie 1 : barre
    run_bar_1d(mats[k]);

    // Partie 2 : plaque
    run_plate_2d(mats[k]);
  }

  (void)argc;
  (void)argv;
  return 0;
}
