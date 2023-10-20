#include "Fecha.h"
#include <ctime>
#include <iostream>

void Fecha::establecerFechaPorDefecto(){
    time_t t = time(NULL);
    struct tm *f = localtime(&t);
    _dia = (*f).tm_mday; // Indirecciona f y accede a tm_mday
    _mes = f->tm_mon + 1; // Indirecciona f y accede a tm_mon
    _anio = f->tm_year + 1900;
}

bool Fecha::esBisiesto(){
    if ((_anio % 4 == 0 && _anio % 100 != 0) || _anio % 400 == 0){
      return true;
    }
    return false;
}

void Fecha::agregarDia(){
   int dias[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if (esBisiesto()){
      dias[1]++;
   }

   _dia++;
   if (_dia > dias[_mes-1]){
      _dia = 1;
      _mes++;
      if (_mes > 12){
         _mes = 1;
         _anio++;
      }
   }
}

void Fecha::agregarDias(int cantidadDias){

   if (cantidadDias > 0){
      for(int i=0; i<cantidadDias; i++){
         agregarDia();
      }
   }

}

Fecha::Fecha(){
   establecerFechaPorDefecto();
}

Fecha::Fecha(int dia, int mes, int anio){
   _dia = dia;
   _mes = mes;
   _anio = anio;

   if (_dia <= 0 || _mes <= 0 || _anio <= 0 || _mes > 12){
      establecerFechaPorDefecto();
   }
   else{
      int dias[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
      if (esBisiesto()){
         dias[1]++;
      }

      if (_dia > dias[_mes-1]){
         establecerFechaPorDefecto();
      }
   }
}

int Fecha::getDia(){
   return _dia;
}
int Fecha::getMes(){
   return _mes;
}
int Fecha::getAnio(){
   return _anio;
}

std::string Fecha::toString(){
    std::string valorADevolver;
    valorADevolver = std::to_string(_dia) + "/" + std::to_string(_mes) + "/" + std::to_string(_anio);
    return valorADevolver;
}

bool Fecha::operator==(Fecha f){
    if(_dia == f.getDia() && _mes == f.getMes() && _anio == f.getAnio()){
        return true;
    }
    else{
        return false;
    }
}

bool Fecha::operator > (Fecha f){
    if (_anio > f.getAnio()){
        return true;
    }
    else if (_anio == f.getAnio() && _mes > f.getMes()){
        return true;
    }
    else if (_anio == f.getAnio() && _mes == f.getMes() && _dia > f.getDia()){
        return true;
    }
    else{
        return false;
    }
}

bool Fecha::operator < (Fecha f){
    if (_anio < f.getAnio()){
        return true;
    }
    else if (_anio == f.getAnio() && _mes < f.getMes()){
        return true;
    }
    else if (_anio == f.getAnio() && _mes == f.getMes() && _dia < f.getDia()){
        return true;
    }
    else{
        return false;
    }
}
