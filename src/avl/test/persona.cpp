#include "persona.hpp"

std::ostream& operator<<(std::ostream& os, const Persona& p){
    os << "DNI: " << p.dni << std::endl;
    os << "Nombre: " << p.nombre << std::endl;
    os << "Apellido: " << p.apellido << std::endl;
    os << "Carrera: " << p.carrera << std::endl;
    os << "Edad: " << p.edad << std::endl;
    os << "Numero: " << p.numero << std::endl;
    os << "Estatura: " << p.estatura << std::endl;
    os << "Peso: " << p.peso << std::endl;
    return os;
}

/*
struct Persona{
    int dni;
    char nombre[100];
    char apellido[100];
    char carrera[100];
    int edad;
    int numero;
    float estatura;
    float peso;
};
*/
