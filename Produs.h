#pragma once
#include <iostream>
#include <cstring>

class Produs { // Clasa Produs
    char *Nume;  // 2 Date Membre
    double Pret;

public:
    Produs() : Nume(NULL), Pret(0) {}; // Constructor fara Parametrii
    Produs(const char *nume, const double pret) : Pret(pret) { // Constructor cu 2 Parametrii
        if (nume != NULL) {
            Nume = new char[std::strlen(nume) + 1]; // Alocam memorie dinamic
            std::strcpy(Nume, nume);
        }
        else {
            Nume = NULL;
        }
    }
    Produs(const Produs &p) : Pret(p.Pret) { // Constructor de Copiere
        if (p.Nume != NULL) {
            Nume = new char[std::strlen(p.Nume) + 1]; // Alocam memorie dinamic
            std::strcpy(Nume, p.Nume);
        }
        else {
            Nume = NULL;
        }
    }

    Produs& operator=(const Produs &p) { // Operator Overloading pentru atribuire (=)
        if (&p == this) {
            return *this;
        }
        delete [] Nume;
        if (p.Nume != NULL) {
            Nume = new char[std::strlen(p.Nume) + 1];
            std::strcpy(Nume, p.Nume);
        }
        else {
            Nume = NULL;
        }
        Pret = p.Pret;
        return *this;
    }

    // GETTERI
    const char* getNume() const { return Nume; } // Getter pentru Nume
    double getPret() const { return Pret; }      // Getter pentru Pret

    // SETTERI
    void setNume(const char *nume) { // Setter pentru Nume
        delete [] Nume;
        if (nume != NULL) {
            Nume = new char[std::strlen(nume) + 1];
            std::strcpy(Nume, nume);
        }
        else {
            Nume = NULL;
        }
    }
    void setPret(double pret) { Pret = pret; } // Setter pentru Pret

    friend std::ostream& operator<<(std::ostream &out, const Produs &p) { // Operator Overloading pentru afisare (<<)
        out << "Numele produsului -> " << (p.Nume == NULL || p.Nume[0] == '\0' ? "NULL" : p.Nume) << std::endl << "Pretul produsului -> "
        << p.Pret << std::endl;
        return out;
    }

    ~Produs() { // Destructor (stergem memoria alocata dinamic)
        if (Nume != NULL) {
            delete[] Nume;
        }
    }
};
