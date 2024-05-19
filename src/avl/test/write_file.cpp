#include "persona.hpp"

std::vector<Persona> personas{
    Persona(77766655,"Andrea", "Coa", "Ciencia de Datos", 19, 999888777, 1.62, 40.1),
    Persona(12345678,"Maria", "Lopez", "Ing. Civil", 21, 123457, 1.60, 60.5),
    Persona(19284783,"Pedro", "Gomez", "Ing. Industrial", 22, 123458, 1.80, 80.5),
    Persona(12346952,"Ana", "Torres", "Ing. Electrica", 23, 123459, 1.75, 75.5),
    Persona(19852348,"Luis", "Garcia", "Ing. Mecanica", 24, 123460, 1.65, 65.5),
    Persona(19721834,"Sofia", "Martinez", "Ing. Quimica", 25, 123461, 1.85, 85.5),
    Persona(12111118,"Carlos", "Hernandez", "Ing. Civil", 26, 123462, 1.75, 75.5),
    Persona(12350008,"Fernanda", "Diaz", "Ing. Electrica", 27, 123463, 1.70, 70.5),
    Persona(99932399,"Ricardo", "Vargas", "Ing. Mecanica", 28, 123464, 1.80, 80.5),
    Persona(83253429,"Diana", "Paz", "Ing. Quimica", 29, 123465, 1.60, 60.5)
};


void insert(){
    std::ofstream file("personas.dat", std::ios::out);
    for(auto& persona : personas){
        file.write((char*)&persona, sizeof(Persona));
    }
    file.close();
}


int main(){
    insert();
    return 0;
}
