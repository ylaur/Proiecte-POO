#pragma once
#include <iostream>
#include <cstring>
#include "Produs.h"
#include "Punct2D.h"
#include "Angajat.h"

class Magazin {
    char *Nume;
    char *Slogan;
    char *FormaJuridica;
    unsigned int NumarProduse;
    unsigned int NumarAngajati;
    Produs *Produse;
    Angajat Sef;
    Angajat *Angajati;
    Punct2D Locatie;

public:
    Magazin() : Nume(NULL), Slogan(NULL), FormaJuridica(NULL), NumarProduse(0), Produse(NULL),
                NumarAngajati(0), Sef(Angajat()), Angajati(NULL),Locatie({0, 0})  {};
    Magazin(const char *_nume, const char *_slogan, const char *_formaJuridica,
            const unsigned int _numarProduse, const Produs _produse[], const Punct2D &_locatie,
            const unsigned int _nrAngajati, const Angajat &_sef, const Angajat _angajati[])
            : NumarProduse(_numarProduse), NumarAngajati(_nrAngajati), Locatie(_locatie), Sef(_sef) {
        if (_nume != NULL) {
            Nume = new char[std::strlen(_nume) + 1];
            std::strcpy(Nume, _nume);
        }
        else {
            Nume = NULL;
        }

        if (_slogan !=NULL) {
            Slogan = new char[std::strlen(_slogan) + 1];
            std::strcpy(Slogan, _slogan);
        }
        else {
            Slogan = NULL;
        }

        if (_formaJuridica != NULL && (std::strcmp(_formaJuridica, "PFA") == 0 || std::strcmp(_formaJuridica, "SRL") == 0 ||
            std::strcmp(_formaJuridica, "SA") == 0)) {
            FormaJuridica = new char[std::strlen(_formaJuridica) + 1];
            std::strcpy(FormaJuridica, _formaJuridica);
        }
        else {
            FormaJuridica = NULL;
        }

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

        if (NumarAngajati > 0) {
            Angajati = new Angajat[NumarAngajati];
            for (unsigned int i = 0; i < NumarAngajati; i++) {
                Angajati[i] = _angajati[i];
            }
        }
        else {
            NumarAngajati = 0;
            Angajati = NULL;
        }
    }
    Magazin(const Magazin &m) : NumarProduse(m.NumarProduse), NumarAngajati(m.NumarAngajati), Locatie(m.Locatie), Sef(m.Sef) {
        if (m.Nume != NULL) {
            Nume = new char[std::strlen(m.Nume) + 1];
            std::strcpy(Nume, m.Nume);
        }
        else {
            Nume = NULL;
        }

        if (m.Slogan != NULL) {
            Slogan = new char[std::strlen(m.Slogan) + 1];
            std::strcpy(Slogan, m.Slogan);
        }
        else {
            Slogan = NULL;
        }

        if (m.FormaJuridica != NULL) {
            FormaJuridica = new char[std::strlen(m.FormaJuridica) + 1];
            std::strcpy(FormaJuridica, m.FormaJuridica);
        }
        else {
            FormaJuridica = NULL;
        }

        if (NumarProduse > 0) {
            Produse = new Produs[NumarProduse];
            for (unsigned int i = 0; i < NumarProduse; i++) {
                Produse[i] = m.Produse[i];
            }
        }
        else {
            NumarProduse = 0;
            Produse = NULL;
        }

        if (NumarAngajati > 0) {
            Angajati = new Angajat[NumarAngajati];
            for (unsigned int i = 0; i < NumarAngajati; i++) {
                Angajati[i] = m.Angajati[i];
            }
        }
        else {
            NumarAngajati = 0;
            Angajati = NULL;
        }
    }

    Magazin& operator=(const Magazin &m) {
        if (&m == this) {
            return *this;
        }

        delete [] Nume;
        delete [] Slogan;
        delete [] FormaJuridica;
        delete [] Produse;
        delete [] Angajati;

        if (m.Nume != NULL) {
            Nume = new char[std::strlen(m.Nume) + 1];
            std::strcpy(Nume, m.Nume);
        }
        else {
            Nume = NULL;
        }

        if (m.Slogan != NULL) {
            Slogan = new char[std::strlen(m.Slogan) + 1];
            std::strcpy(Slogan, m.Slogan);
        }
        else {
            Slogan = NULL;
        }

        if (m.FormaJuridica != NULL) {
            FormaJuridica = new char[std::strlen(m.FormaJuridica) + 1];
            std::strcpy(FormaJuridica, m.FormaJuridica);
        }
        else {
            FormaJuridica = NULL;
        }

        NumarProduse = m.NumarProduse;
        if (NumarProduse > 0) {
            Produse = new Produs[NumarProduse];
            for (unsigned int i = 0; i < NumarProduse; i++) {
                Produse[i] = m.Produse[i];
            }
        }
        else {
            NumarProduse = 0;
            Produse = NULL;
        }

        NumarAngajati = m.NumarAngajati;
        if (NumarAngajati > 0) {
            Angajati = new Angajat[NumarAngajati];
            for (unsigned int i = 0; i < NumarAngajati; i++) {
                Angajati[i] = m.Angajati[i];
            }
        }
        else {
            NumarAngajati = 0;
            Angajati = NULL;
        }

        Sef = m.Sef;
        Locatie = m.Locatie;

        return *this;
    }

    const char* getNume() const { return Nume; }
    const char* getSlogan() const { return Slogan; }
    const char* getFormatJuridica() const { return FormaJuridica; }
    unsigned int getNumarProduse() const { return NumarProduse; }
    unsigned int getNumarAngajati() const { return NumarAngajati; }
    const Produs* getProduse() const { return Produse; }
    const Angajat* getAngajati() const { return Angajati; }
    Produs getProdusX(unsigned int X) const { return (X >= NumarProduse ? Produs() : Produse[X]); }
    Angajat getAngajatX(unsigned int X) const { return (X >= NumarAngajati ? Angajat() : Angajati[X]); }
    Angajat getSef() const { return Sef; }
    Punct2D getLocatie() const { return Locatie; }

    void setNume(const char *_nume) {
        delete [] Nume;
        if (_nume != NULL) {
            Nume = new char[std::strlen(_nume) + 1];
            std::strcpy(Nume, _nume);
        }
        else {
            Nume = NULL;
        }
    }
    void setSlogan(const char *_slogan) {
        delete [] Slogan;
        if (_slogan != NULL) {
            Slogan = new char[std::strlen(_slogan) + 1];
            std::strcpy(Slogan, _slogan);
        }
        else {
            Slogan = NULL;
        }
    }
    void setFormaJuridica(const char *_FormaJuridica) {
        delete [] FormaJuridica;
        if (_FormaJuridica != NULL && (std::strcmp(_FormaJuridica, "PFA") == 0 || std::strcmp(_FormaJuridica, "SRL") == 0 ||
            std::strcmp(_FormaJuridica, "SA") == 0)) {
            FormaJuridica = new char[std::strlen(_FormaJuridica) + 1];
            std::strcpy(FormaJuridica, _FormaJuridica);
        }
        else {
            FormaJuridica = NULL;
        }
    }
    void setProduse(const unsigned int _numarProduse, const Produs _produse[]) {
        delete[] Produse;
        if (_numarProduse == 0) {
            NumarProduse = 0;
            Produse = NULL;
        }
        else {
            NumarProduse = _numarProduse;
            Produse = new Produs[NumarProduse];
            for (unsigned int i = 0; i < NumarProduse; i++) {
                Produse[i] = _produse[i];
            }
        }
    }
    void setProdusX(const Produs &produs, unsigned int X) {
        if (X >= NumarProduse) {
            return;
        }
        Produse[X] = produs;
    }
    void setAngajati(const unsigned int _numarAngajati, const Angajat _angajati[]) {
        delete[] Angajati;
        if (_numarAngajati == 0) {
            NumarAngajati = 0;
            Angajati = NULL;
        }
        else {
            NumarAngajati = _numarAngajati;
            Angajati = new Angajat[NumarAngajati];
            for (unsigned int i = 0; i < NumarAngajati; i++) {
                Angajati[i] = _angajati[i];
            }
        }
    }
    void setAngajatX(const Angajat &angajat, unsigned int X) {
        if (X >= NumarAngajati) {
            return;
        }
        Angajati[X] = angajat;
    }
    void setSef(const Angajat &sef) { Sef = sef; }
    void setLocatie(const Punct2D _locatie) { Locatie = _locatie; }

    void stergeProdus(unsigned int pozitie) {
        if (NumarProduse == 0) return;

        if (NumarProduse == 1) {
            delete[] Produse;
            Produse = NULL;
            NumarProduse = 0;
            return;
        }

        if (pozitie >= NumarProduse) {
            pozitie = NumarProduse - 1;
        }

        Produs *auxProduse = new Produs[NumarProduse - 1];
        for (unsigned int i = 0; i < pozitie; ++i) {
            auxProduse[i] = Produse[i];
        }
        for (unsigned int i = pozitie + 1; i < NumarProduse; ++i) {
            auxProduse[i - 1] = Produse[i];
        }

        --NumarProduse;
        delete [] Produse;
        Produse = auxProduse;
    }
    void stergeAngajat(unsigned int pozitie) {
        if (NumarAngajati == 0) return;

        if (NumarAngajati == 1) {
            delete[] Angajati;
            Angajati = NULL;
            NumarAngajati = 0;
            return;
        }

        if (pozitie >= NumarAngajati) {
            pozitie = NumarAngajati - 1;
        }

        Angajat *auxAngajati = new Angajat[NumarAngajati - 1];
        for (unsigned int i = 0; i < pozitie; ++i) {
            auxAngajati[i] = Angajati[i];
        }
        for (unsigned int i = pozitie + 1; i < NumarAngajati; ++i) {
            auxAngajati[i - 1] = Angajati[i];
        }

        --NumarAngajati;
        delete [] Angajati;
        Angajati = auxAngajati;
    }


    void insereazaProdus(unsigned int pozitie, const Produs &p) {
        if (pozitie > NumarProduse) {
            pozitie = NumarProduse;
        }

        Produs *auxProduse = new Produs[NumarProduse + 1];
        for (unsigned int i = 0; i < pozitie; ++i) {
            auxProduse[i] = Produse[i];
        }
        auxProduse[pozitie] = p;
        for (unsigned int i = pozitie; i < NumarProduse; ++i) {
            auxProduse[i + 1] = Produse[i];
        }
        ++NumarProduse;

        delete[] Produse;
        Produse = auxProduse;
    }
    void insereazaAngajat(unsigned int pozitie, const Angajat &a) {
        if (pozitie > NumarAngajati) {
            pozitie = NumarAngajati;
        }

        Angajat *auxAngajati = new Angajat[NumarAngajati + 1];
        for (unsigned int i = 0; i < pozitie; ++i) {
            auxAngajati[i] = Angajati[i];
        }
        auxAngajati[pozitie] = a;
        for (unsigned int i = pozitie; i < NumarAngajati; ++i) {
            auxAngajati[i + 1] = Angajati[i];
        }
        ++NumarAngajati;

        delete[] Angajati;
        Angajati = auxAngajati;
    }

    friend std::ostream& operator<<(std::ostream &out, const Magazin &m) {
        out << "===== " << (m.Nume == NULL || m.Nume[0] == '\0' ? "NULL" : m.Nume) << " =====" << std::endl;
        out << "# Slogan: " << (m.Slogan == NULL || m.Slogan[0] == '\0' ? "NULL" : m.Slogan) << std::endl;

        if (m.NumarProduse == 0) {
            out << "Magazinul NU contine produse!" << std::endl;
        }
        else {
            out << "# Stocul nostru:" << std::endl << "----------" << std::endl;
            for (unsigned int i = 0; i < m.NumarProduse; i++) {
                out << "Produsul " << i + 1 << ": \n" << m.Produse[i];
                out << "----------" << std::endl;
            }
        }

        out << "# Adresa: " << m.Locatie << std::endl;
        return out;
    }

    ~Magazin() {
        delete[] Nume;
        delete[] Slogan;
        delete[] FormaJuridica;
        delete[] Produse;
        delete[] Angajati;
    }
};
