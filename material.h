#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

/// @brief Propriétés physiques d'un matériau : lambda, rho, c.
struct Material
{
  std::string name;
  double lambda; ///< conductivité thermique (W/(m.K))
  double rho;    ///< masse volumique (kg/m^3)
  double c;      ///< chaleur massique (J/(kg.K))

  double alpha() const { return lambda / (rho * c); } ///< lambda/(rho*c)
};

/// @brief Renvoie les 4 matériaux du tableau.
void get_all_materials(Material out[4]);

#endif
