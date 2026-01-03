#include "sdl_view.h"
#include <cmath>

SdlView::SdlView(const std::string &title, int w, int h)
  : win_(nullptr), ren_(nullptr), w_(w), h_(h)
{
  SDL_Init(SDL_INIT_EVERYTHING);
  win_ = SDL_CreateWindow(title.c_str(),
                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                          w_, h_, SDL_WINDOW_OPENGL);
  ren_ = SDL_CreateRenderer(win_, -1, 0);
}

SdlView::~SdlView()
{
  SDL_DestroyRenderer(ren_);
  SDL_DestroyWindow(win_);
  SDL_Quit();
}

bool SdlView::process_events()
{
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT) return false;
    if (e.type == SDL_KEYDOWN)
    {
      if (e.key.keysym.sym == SDLK_ESCAPE) return false;
      if (e.key.keysym.sym == SDLK_q) return false;
    }
  }
  return true;
}

void SdlView::clear()
{
  SDL_SetRenderDrawColor(ren_, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(ren_);
}

void SdlView::present()
{
  SDL_RenderPresent(ren_);
}

Uint8 SdlView::clamp_u8(int v) const
{
  if (v < 0) return 0;
  if (v > 255) return 255;
  return static_cast<Uint8>(v);
}

Uint8 SdlView::map_to_gray(double x, double a, double b) const
{
  if (b <= a) return 0;
  const double t = (x - a) / (b - a);
  return clamp_u8(static_cast<int>(std::round(255.0 * t)));
}

void SdlView::draw_curve_1d(const std::vector<double> &u, double umin, double umax)
{
  const int n = static_cast<int>(u.size());
  SDL_SetRenderDrawColor(ren_, 255, 255, 255, SDL_ALPHA_OPAQUE);

  for (int i = 0; i < n - 1; i++)
  {
    const double g0 = map_to_gray(u[i],   umin, umax) / 255.0;
    const double g1 = map_to_gray(u[i+1], umin, umax) / 255.0;

    const int x0 = (w_ - 1) * i / (n - 1);
    const int x1 = (w_ - 1) * (i + 1) / (n - 1);

    const int y0 = static_cast<int>((1.0 - g0) * (h_ - 1));
    const int y1 = static_cast<int>((1.0 - g1) * (h_ - 1));

    SDL_RenderDrawLine(ren_, x0, y0, x1, y1);
  }
}

void SdlView::draw_heatmap_2d(const std::vector<double> &u, int n,
                              double umin, double umax)
{
  for (int j = 0; j < n; j++)
  {
    for (int i = 0; i < n; i++)
    {
      const double val = u[j * n + i];
      const Uint8 g = map_to_gray(val, umin, umax);
      SDL_SetRenderDrawColor(ren_, g, 0, static_cast<Uint8>(255 - g), SDL_ALPHA_OPAQUE);

      const int x = (w_ - 1) * i / (n - 1);
      const int y = (h_ - 1) * j / (n - 1);

      SDL_RenderDrawPoint(ren_, x, y);
    }
  }
}
