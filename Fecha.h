#ifndef FECHA_H
#define FECHA_H
#include <string>


class Fecha
{
   private:
   int _dia, _mes, _anio;
   void establecerFechaPorDefecto();
   bool esBisiesto();
   void agregarDia();

   public:
      Fecha();
      Fecha(int dia, int mes, int anio);

      int getDia();
      int getMes();
      int getAnio();
      void agregarDias(int cantidadDias);
      std::string toString();

      bool operator == (Fecha f);
      bool operator > (Fecha f);
      bool operator < (Fecha f);
};

#endif // FECHA_H
