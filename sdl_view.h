#ifndef SDL_VIEW_H
#define SDL_VIEW_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

/// @brief Wrapper SDL minimal pour afficher 1D (courbe) et 2D (heatmap).
class SdlView
{
public:
  SdlView(const std::string &title, int w, int h);
  ~SdlView();

  bool process_events();
  void clear();

  void present();

  void draw_curve_1d(const std::vector<double> &u, double umin, double umax);
  void draw_heatmap_2d(const std::vector<double> &u, int n, double umin, double umax);

private:
  SDL_Window *win_;
  SDL_Renderer *ren_;
  int w_;
  int h_;

  Uint8 clamp_u8(int v) const;
  Uint8 map_to_gray(double x, double a, double b) const;
};

#endif
