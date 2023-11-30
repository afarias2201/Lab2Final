#include "MarcaArchivo.h"

MarcaArchivo::MarcaArchivo(std::string nombreArchivo)
{
    _nombreArchivo = nombreArchivo;
}

bool MarcaArchivo::Guardar(Marca reg){
    bool pudoEscribir;
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if(p == nullptr){
        return false;
    }
    pudoEscribir = fwrite(&reg, sizeof(Marca), 1, p);
    fclose(p);
    return pudoEscribir;
}
bool MarcaArchivo::Guardar(Marca reg, int nroRegistro){
    bool pudoEscribir;
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if(p == nullptr){
        return false;
    }
    fseek(p, nroRegistro * sizeof(Marca), SEEK_SET);
    pudoEscribir = fwrite(&reg, sizeof(Marca), 1, p);
    fclose(p);
    return pudoEscribir;
}
bool MarcaArchivo::Guardar(Marca* marcas, int cantidadRegistros){
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if(p == nullptr){
        return false;
    }

    int cantidadRegistrosEscritos = fwrite(marcas, sizeof(Marca), cantidadRegistros, p);
    fclose(p);
    return cantidadRegistrosEscritos == cantidadRegistros;
}
int MarcaArchivo::contarRegistros(){
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr){
    return 0;
    }
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Marca);
}
Marca MarcaArchivo::Leer(int nroRegistro){
    Marca reg;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr){
    return reg;
    }
    fseek(p, nroRegistro * sizeof(Marca), SEEK_SET);
    fread(&reg, sizeof(Marca), 1, p);
    fclose(p);
    return reg;
}
void MarcaArchivo::Leer(Marca* marcas, int cantidadRegistros){
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if(p == nullptr){
        return;
    }
    fread(marcas, sizeof(Marca), cantidadRegistros, p);
    fclose(p);
}
int MarcaArchivo::Buscar(int idMarca){
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr){
    return -1;
    }
    int i = 0;
    Marca reg;
    while(fread(&reg, sizeof(Marca), 1, p)){
    if(reg.getID() == idMarca){
        fclose(p);
        return i;
    }
    i++;
    }
    fclose(p);
    return -1;
}

int MarcaArchivo::Buscar(std::string nombre){
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr){
    return -1;
    }
    int i = 0;
    Marca reg;
    while(fread(&reg, sizeof(Marca), 1, p)){
    if(reg.getNombre() == nombre){
        fclose(p);
        return i;
    }
    i++;
    }
    fclose(p);
    return -1;
}

void MarcaArchivo::Vaciar(){
    FILE *p = fopen(_nombreArchivo.c_str(), "wb");
    if(p == nullptr){
        return;
    }
    fclose(p);
}
