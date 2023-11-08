#include "ClienteArchivo.h"
#include <iostream>

ClienteArchivo::ClienteArchivo(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}
bool ClienteArchivo::Guardar(Cliente reg){
    bool pudoEscribir;
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if(p == nullptr){
        return false;
    }
    pudoEscribir = fwrite(&reg, sizeof(Cliente), 1, p);
    fclose(p);
    return pudoEscribir;
}
bool ClienteArchivo::Guardar(Cliente reg, int nroRegistro){
    bool pudoEscribir;
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if(p == nullptr){
        return false;
    }
    fseek(p, nroRegistro * sizeof(Cliente), SEEK_SET);
    pudoEscribir = fwrite(&reg, sizeof(Cliente), 1, p);
    fclose(p);
    return pudoEscribir;
}

bool ClienteArchivo::Guardar(Cliente* clientes, int cantidadRegistros){
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if(p == nullptr){
        return false;
    }

    int cantidadRegistrosEscritos = fwrite(clientes, sizeof(Cliente), cantidadRegistros, p);
    fclose(p);
    return cantidadRegistrosEscritos == cantidadRegistros;
}

int ClienteArchivo::contarRegistros(){
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr){
    return 0;
    }
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Cliente);
}
Cliente ClienteArchivo::Leer(int nroRegistro){
    Cliente reg;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr){
    return reg;
    }
    fseek(p, nroRegistro * sizeof(Cliente), SEEK_SET);
    fread(&reg, sizeof(Cliente), 1, p);
    fclose(p);
    return reg;
}

void ClienteArchivo::Leer(Cliente* clientes, int cantidadRegistros){
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if(p == nullptr){
        return;
    }
    fread(clientes, sizeof(Cliente), cantidadRegistros, p);
    fclose(p);
}

int ClienteArchivo::Buscar(std::string dniCliente){
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr){
    return -1;
    }
    int i = 0;
    Cliente reg;
    while(fread(&reg, sizeof(Cliente), 1, p)){
    if(reg.getDNI() == dniCliente){
        fclose(p);
        return i;
    }
    i++;
    }
    fclose(p);
    return -1;
}

void ClienteArchivo::Vaciar(){
    FILE *p = fopen(_nombreArchivo.c_str(), "wb");
    if(p == nullptr){
        return;
    }
    fclose(p);
}
