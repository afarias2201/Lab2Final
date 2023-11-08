#include "VehiculoArchivo.h"
#include <cstdio>
#include <cstring>

VehiculoArchivo::VehiculoArchivo(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}

bool VehiculoArchivo::Guardar(Vehiculo reg){
    bool pudoEscribir;
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if(p == nullptr){
        return false;
    }
    pudoEscribir = fwrite(&reg, sizeof(Vehiculo), 1, p);
    fclose(p);
    return pudoEscribir;
}

bool VehiculoArchivo::Guardar(Vehiculo reg, int nroRegistro){
    bool pudoEscribir;
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if(p == nullptr){
        return false;
    }
    fseek(p, nroRegistro * sizeof(Vehiculo), SEEK_SET);
    pudoEscribir = fwrite(&reg, sizeof(Vehiculo), 1, p);
    fclose(p);
    return pudoEscribir;
}

bool VehiculoArchivo::Guardar(Vehiculo* vRegistros, int cantidadRegistros){
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if( p == nullptr){
        return false;
    }

    int cantidadRegistrosEscritos = fwrite(vRegistros, sizeof(Vehiculo), cantidadRegistros, p);
    fclose(p);
    return cantidadRegistrosEscritos == cantidadRegistros;
}

int VehiculoArchivo::contarRegistros(){
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr){
    return 0;
    }
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Vehiculo);
}

Vehiculo VehiculoArchivo::Leer(int nroRegistro){
    Vehiculo reg;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr){
    return reg;
    }
    fseek(p, nroRegistro * sizeof(Vehiculo), SEEK_SET);
    fread(&reg, sizeof(Vehiculo), 1, p);
    fclose(p);
    return reg;
}

void VehiculoArchivo::Leer(Vehiculo* vRegistros, int cantidadRegistros){
	FILE *p = fopen(_nombreArchivo.c_str(), "rb");
	if (p == NULL)
	{
		return ;
	}

	fread(vRegistros, sizeof(Vehiculo), cantidadRegistros, p);
	fclose(p);
}

int VehiculoArchivo::Buscar(std::string nroPatente){
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr){
    return -1;
    }
    int i = 0;
    Vehiculo reg;
    while(fread(&reg, sizeof(Vehiculo), 1, p)){
    if(reg.getPatente() == nroPatente){
        fclose(p);
        return i;
    }
    i++;
    }
    fclose(p);
    return -1;
}

void VehiculoArchivo::Vaciar(){
	FILE *p = fopen(_nombreArchivo.c_str(), "wb");
	if (p == NULL)
	{
		return;
	}
	fclose(p);
}
