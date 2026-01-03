#ifndef CONSTANTS_H
#define CONSTANTS_H

/// @brief Constantes numériques du projet chaleur.
namespace Cst
{
  constexpr double L = 1.0;       ///< Longueur (m)
  constexpr double tmax = 16.0;   ///< Temps max (s)
  constexpr int N = 1001;         ///< Nb points espace (1D) et par axe (2D)
  constexpr int Nt = 1001;        ///< Nb points temps
  constexpr int Nframes = 100;    ///< Nb images à afficher
  constexpr double CelsiusToKelvin = 273.15;

  constexpr double u0_C = 13.0;   ///< Temp initiale en Celsius
  constexpr double f_C  = 80.0;   ///< "température" source en Celsius (selon énoncé)

  inline double u0_K() { return u0_C + CelsiusToKelvin; }
  inline double f_K()  { return f_C  + CelsiusToKelvin; }
}

#endif
