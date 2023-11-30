#include "Marca.h"
#include <cstring>

Marca::Marca(){
    _activo = true;
}
int Marca::getID() const{
    return _id;
}
std::string Marca::getNombre() const{
    return _nombre;
}
bool Marca::getActivo() const{
    return _activo;
}
void Marca::setID(int id){
    _id = id;
}
void Marca::setNombre(std::string nombre){
    strcpy(_nombre, nombre.c_str());
}
void Marca::setActivo(bool activo){
    _activo = activo;
}
