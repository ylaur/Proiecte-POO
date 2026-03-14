#pragma once
#include <iostream>
#include <cstring>

class Produs { // Un obiect de tip "Produs" are 2 date membre: Numele produsului si Pretul sau.
    char *Nume;
    double Pret;

public:
    Produs() : Nume(NULL), Pret(0) {}; // Constructor fara parametrii
    Produs(const char *nume, const double pret) : Pret(pret) { // Constructor cu 2 parametrii
        if (nume != NULL) {
            Nume = new char[std::strlen(nume) + 1];
            std::strcpy(Nume, nume);
        }
        else {
            Nume = NULL;
        }
    }
    Produs(const Produs &p) : Pret(p.Pret) { // Constructor de copiere
        if (p.Nume != NULL) {
            Nume = new char[std::strlen(p.Nume) + 1];
            std::strcpy(Nume, p.Nume);
        }
        else {
            Nume = NULL;
        }
    }

    Produs& operator=(const Produs &p) { // Operator Overloading pentru "="
        if (&p == this) return *this;
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

    char* getNume() const { return Nume; } // GETTERI
    double getPret() const { return Pret; }

    void setNume(const char *nume) { // SETTERI
        delete [] Nume;
        if (nume != NULL) {
            Nume = new char[std::strlen(nume) + 1];
            std::strcpy(Nume, nume);
        }
        else {
            Nume = NULL;
        }
    }
    void setPret(double pret) { Pret = pret; }

    friend std::ostream& operator<<(std::ostream &out, const Produs &p) { // Afisare specifica obiectelor clasei "Produs"
        out << "Numele produsului -> " << (p.Nume == NULL || p.Nume[0] == '\0' ? "NULL" : p.Nume) << std::endl << "Pretul produsului -> "
        << p.Pret << std::endl;
        return out;
    }

    ~Produs() { // Destructor
        if (Nume != NULL) {
            delete[] Nume;
        }
    }
};
