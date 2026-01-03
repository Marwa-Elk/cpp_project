#include "material.h"

void get_all_materials(Material out[4])
{
  out[0] = {"cuivre",      389.0, 8940.0,  380.0};
  out[1] = {"fer",          80.2, 7874.0,  440.0};
  out[2] = {"verre",         1.2, 2530.0,  840.0};
  out[3] = {"polystyrene",   0.1, 1040.0, 1200.0};
}
