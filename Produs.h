#pragma once
#include <iostream>
#include <cstring>

class Produs {
    char *Nume;
    double Pret;

public:
    Produs() : Nume(NULL), Pret(0) {};
    Produs(const char *nume, const double pret) : Pret(pret) {
        if (nume != NULL) {
            Nume = new char[std::strlen(nume) + 1];
            std::strcpy(Nume, nume);
        }
        else {
            Nume = NULL;
        }
    }
    Produs(const Produs &p) : Pret(p.Pret) {
        if (p.Nume != NULL) {
            Nume = new char[std::strlen(p.Nume) + 1];
            std::strcpy(Nume, p.Nume);
        }
        else {
            Nume = NULL;
        }
    }

    Produs& operator=(const Produs &p) {
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

    const char* getNume() const { return Nume; }
    double getPret() const { return Pret; }

    void setNume(const char *nume) {
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

    friend std::ostream& operator<<(std::ostream &out, const Produs &p) {
        out << "Numele produsului -> " << (p.Nume == NULL || p.Nume[0] == '\0' ? "NULL" : p.Nume) << std::endl << "Pretul produsului -> "
        << p.Pret << std::endl;
        return out;
    }

    ~Produs() {
        if (Nume != NULL) {
            delete[] Nume;
        }
    }
};
