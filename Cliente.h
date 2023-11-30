#ifndef CLIENTE_H
#define CLIENTE_H
#include <string>


class Cliente
{
    public:
        Cliente();
        int getID() const;
        std::string getDNI() const;
        std::string getNombres() const;
        std::string getApellidos() const;
        std::string getDomicilio() const;
        std::string getTelefono() const;
        std::string getEmail() const;
        bool getEstado() const;

        void setID(int id);
        void setDNI(std::string dni);
        void setNombres(std::string nombres);
        void setApellidos(std::string apellidos);
        void setDomicilio(std::string domicilio);
        void setTelefono(std::string telefono);
        void setEmail(std::string email);
        void setEstado(bool estado);

    private:
        int _id;
        char _dni[10];
        char _nombres[50];
        char _apellidos[50];
        char _domicilio[50];
        char _telefono[15];
        char _email[50];
        bool _estado;
};

#endif // CLIENTE_H
