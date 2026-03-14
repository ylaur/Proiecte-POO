#pragma once
#include <iostream>
#include <cstring>
#include "Produs.h"
#include "Punct2D.h"

class Magazin { // Un obiect de tip "Magazin" are 6 date membre: Numele, Sloganul, Forma Juridica, Numarul de produse si Locatia obiectului.
    char *Nume;
    char *Slogan;
    char *FormaJuridica;
    unsigned int NumarProduse;
    Produs *Produse;
    Punct2D Locatie;

public:
    Magazin() : Nume(NULL), Slogan(NULL), FormaJuridica(NULL), NumarProduse(0), Produse(NULL), Locatie({0, 0}) {}; // Constructor fara parametrii
    Magazin(const char *_nume, const char *_slogan, const char *_formaJuridica, 
            const unsigned int _numarProduse, const Produs _produse[], const Punct2D& _locatie)
            : NumarProduse(_numarProduse), Locatie(_locatie) { //  Constructor cu 6 parametrii (toate datele membre)
        if (_nume != NULL) {
            Nume = new char[std::strlen(_nume) + 1];
            std::strcpy(Nume, _nume);
        }
        else Nume = NULL;

        if (_slogan !=NULL) {
            Slogan = new char[std::strlen(_slogan) + 1];
            std::strcpy(Slogan, _slogan);
        }
        else Slogan = NULL;

        if (_formaJuridica != NULL && (std::strcmp(_formaJuridica, "PFA") == 0 || std::strcmp(_formaJuridica, "SRL") == 0 ||
            std::strcmp(_formaJuridica, "SA") == 0)) {
            FormaJuridica = new char[std::strlen(_formaJuridica) + 1];
            std::strcpy(FormaJuridica, _formaJuridica);
        }
        else FormaJuridica = NULL;

        if (NumarProduse > 0) {
            Produse = new Produs[NumarProduse];
            for (unsigned int i = 0; i < _numarProduse; i++) {
                Produse[i] = _produse[i];
            }
        }
        else {
            NumarProduse = 0;
            Produse = NULL;
        }
    }
    Magazin(const Magazin &m) : NumarProduse(m.NumarProduse), Locatie(m.Locatie) { // Constructor de copiere
        if (m.Nume != NULL) {
            Nume = new char[std::strlen(m.Nume) + 1];
            std::strcpy(Nume, m.Nume);
        } else Nume = NULL;

        if (m.Slogan != NULL) {
            Slogan = new char[std::strlen(m.Slogan) + 1];
            std::strcpy(Slogan, m.Slogan);
        } else Slogan = NULL;

        if (m.FormaJuridica != NULL) {
            FormaJuridica = new char[std::strlen(m.FormaJuridica) + 1];
            std::strcpy(FormaJuridica, m.FormaJuridica);
        } else FormaJuridica = NULL;

        if (NumarProduse > 0) {
            Produse = new Produs[NumarProduse];
            for (unsigned int i = 0; i < NumarProduse; i++) {
                Produse[i] = m.Produse[i];
            }
        } else {
            NumarProduse = 0;
            Produse = NULL;
        }
    }

    Magazin& operator=(const Magazin &m) { // Operator Overloading pentru "="
        if (&m == this) return *this;

        delete [] Nume;
        delete [] Slogan;
        delete [] FormaJuridica;
        delete [] Produse;

        if (m.Nume != NULL) {
            Nume = new char[std::strlen(m.Nume) + 1];
            std::strcpy(Nume, m.Nume);
        } else Nume = NULL;

        if (m.Slogan != NULL) {
            Slogan = new char[std::strlen(m.Slogan) + 1];
            std::strcpy(Slogan, m.Slogan);
        } else Slogan = NULL;

        if (m.FormaJuridica != NULL) {
            FormaJuridica = new char[std::strlen(m.FormaJuridica) + 1];
            std::strcpy(FormaJuridica, m.FormaJuridica);
        } else FormaJuridica = NULL;

        NumarProduse = m.NumarProduse;
        if (NumarProduse > 0) {
            Produse = new Produs[NumarProduse];
            for (unsigned int i = 0; i < NumarProduse; i++) {
                Produse[i] = m.Produse[i];
            }
        } else {
            NumarProduse = 0;
            Produse = NULL;
        }

        Locatie = m.Locatie;
        return *this;
    }

    char* getNume() const { return Nume; } //  GETTERI
    char* getSlogan() const { return Slogan; }
    char* getFormatJuridica() const { return FormaJuridica; }
    unsigned int getNumarProduse() const { return NumarProduse; }
    Produs* getProduse() const { return Produse; }
    Punct2D getLocatie() const { return Locatie; }

    void setNume(const char *_nume) { // SETTERI
        delete [] Nume;
        if (_nume != NULL) {
            Nume = new char[std::strlen(_nume) + 1];
            std::strcpy(Nume, _nume);
        } else Nume = NULL;
    }
    void setSlogan(const char *_slogan) {
        delete [] Slogan;
        if (_slogan != NULL) {
            Slogan = new char[std::strlen(_slogan) + 1];
            std::strcpy(Slogan, _slogan);
        } else Slogan = NULL;
    }
    void setFormaJuridica(const char *_FormaJuridica) { // Forma Juridica poate fi doar: "PFA", "SRL" si "SA". Orice altceva este respins.
        delete [] FormaJuridica;
        if (_FormaJuridica != NULL && (std::strcmp(_FormaJuridica, "PFA") == 0 || std::strcmp(_FormaJuridica, "SRL") == 0 ||
            std::strcmp(_FormaJuridica, "SA") == 0)) {
            FormaJuridica = new char[std::strlen(_FormaJuridica) + 1];
            std::strcpy(FormaJuridica, _FormaJuridica);
        } else FormaJuridica = NULL;
    }
    void setProduse(const unsigned int _numarProduse, const Produs _produse[]) { // Din motive de bune practici, se accepta adaugare produselor impreuna cu numarul lor,
        delete[] Produse;                                                        // nu doar una (sau niciuna) dintre cele doua.
        if (_numarProduse == 0) {
            NumarProduse = 0;
            Produse = NULL;
        } else {
            NumarProduse = _numarProduse;
            Produse = new Produs[NumarProduse];
            for (unsigned int i = 0; i < NumarProduse; i++) {
                Produse[i] = _produse[i];
            }
        }
    }
    void setLocatie(const Punct2D _locatie) { Locatie = _locatie; }

    void stergeProdus(unsigned int pozitie) { // Metoda pentru stergerea unui produs. Produsul de pe pozitia (0, ..., NumarProduse - 1) va fi sters.
        if (NumarProduse == 0) return;        // In cazul in care pozitia >= NumarProduse, se va sterge ultimul produs.
        if (NumarProduse == 1) {
            delete[] Produse;
            Produse = NULL;
            NumarProduse = 0;
            return;
        }
        if (pozitie >= NumarProduse) pozitie = NumarProduse - 1;

        Produs *auxProduse = new Produs[NumarProduse - 1];
        for (unsigned int i = 0; i < pozitie; ++i) auxProduse[i] = Produse[i];
        for (unsigned int i = pozitie + 1; i < NumarProduse; ++i) auxProduse[i - 1] = Produse[i];

        --NumarProduse;
        delete [] Produse;
        Produse = auxProduse;
    }

    void insereazaProdus(unsigned int pozitie, const Produs &p) { // Metoda pentru inserarea unui produs la o pozitie (0, ..., NumarProduse) specificata.
        if (pozitie > NumarProduse) pozitie = NumarProduse;       // In cazul in care pozitia > NumarProduse, se va insera la final.

        Produs *auxProduse = new Produs[NumarProduse + 1];
        for (unsigned int i = 0; i < pozitie; ++i) auxProduse[i] = Produse[i];
        auxProduse[pozitie] = p;
        for (unsigned int i = pozitie; i < NumarProduse; ++i) auxProduse[i + 1] = Produse[i];
        ++NumarProduse;

        delete[] Produse;
        Produse = auxProduse;
    }

    friend std::ostream& operator<<(std::ostream &out, const Magazin &m) { //  Afisare specifica obiectelor de tip "Magazin"
        out << "===== " << (m.Nume == NULL || m.Nume[0] == '\0' ? "NULL" : m.Nume) << " =====" << std::endl;
        out << "# Slogan: " << (m.Slogan == NULL || m.Slogan[0] == '\0' ? "NULL" : m.Slogan) << std::endl;

        if (m.NumarProduse == 0) {
            out << "Magazinul NU contine produse!" << std::endl;
        } else {
            out << "# Stocul nostru:" << std::endl << "----------" << std::endl;
            for (unsigned int i = 0; i < m.NumarProduse; i++) {
                out << "Produsul " << i + 1 << ": \n" << m.Produse[i];
                out << "----------" << std::endl;
            }
        }

        out << "# Adresa: " << m.Locatie << std::endl;
        return out;
    }

    ~Magazin() { // Destructor
        delete[] Nume;
        delete[] Slogan;
        delete[] FormaJuridica;
        delete[] Produse;
    }
};
