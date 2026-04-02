#pragma once
#include <iostream>
#include <cstring>
#include "Produs.h"  // Ne folosim de clasele definite anterior (ierarhic)
#include "Punct2D.h"
#include "Angajat.h"

class Magazin { // Clasa Magazin
    char *Nume;                  // 9 Date Membre
    char *Slogan;
    char *FormaJuridica;         // Poate fi DOAR una din urmatoarele: "SRL", "SA", "PFA"
    unsigned int NumarProduse;   // Contor pentru Produse (stocheaza numarul de Produse)
    unsigned int NumarAngajati;  // Contor pentru Angajati (stocheaza numarul de Angajati)
    Produs *Produse;             // Array alocat dinamic in care vom stoca Produsele
    Angajat Sef;                 
    Angajat *Angajati;           // Array alocat dinamic in care vom stoca Angajatii
    Punct2D Locatie;             // Stocheaza Locatia (i.e: (5, 25))

public:
    Magazin() : Nume(NULL), Slogan(NULL), FormaJuridica(NULL), NumarProduse(0), Produse(NULL), // Constructor fara Parametrii
                NumarAngajati(0), Sef(Angajat()), Angajati(NULL),Locatie({0, 0})  {}; 
    Magazin(const char *_nume, const char *_slogan, const char *_formaJuridica, // Constructor cu Parametrii
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

        if (_formaJuridica != NULL && (std::strcmp(_formaJuridica, "PFA") == 0 || std::strcmp(_formaJuridica, "SRL") == 0 || // Doar UNA din optiuni
            std::strcmp(_formaJuridica, "SA") == 0)) {
            FormaJuridica = new char[std::strlen(_formaJuridica) + 1];
            std::strcpy(FormaJuridica, _formaJuridica);
        }
        else {
            FormaJuridica = NULL;
        }

        if (NumarProduse > 0) {
            Produse = new Produs[NumarProduse]; // Alocam memorie dinamic
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
    Magazin(const Magazin &m) : NumarProduse(m.NumarProduse), NumarAngajati(m.NumarAngajati), Locatie(m.Locatie), Sef(m.Sef) { // Constructor de Copiere
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

    Magazin& operator=(const Magazin &m) { // Operator Overloading pentru asignare (=)
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

    // GETTERI
    const char* getNume() const { return Nume; }                    // Getter pentru Nume
    const char* getSlogan() const { return Slogan; }                // Getter pentru Slogan
    const char* getFormatJuridica() const { return FormaJuridica; } // Getter Forma Juridica
    unsigned int getNumarProduse() const { return NumarProduse; }   // Getter NumarProduse
    unsigned int getNumarAngajati() const { return NumarAngajati; } // Getter NumarAngajati
    const Produs* getProduse() const { return Produse; }            // Getter Produse
    const Angajat* getAngajati() const { return Angajati; }         // Getter Angajati
    Produs getProdusX(unsigned int X) const { return (X >= NumarProduse ? Produs() : Produse[X]); }      // Geter Produs de la pozitia X
    Angajat getAngajatX(unsigned int X) const { return (X >= NumarAngajati ? Angajat() : Angajati[X]); } // Getter Angajat de la pozitia X
    Angajat getSef() const { return Sef; }                          // Getter Sef
    Punct2D getLocatie() const { return Locatie; }                  // Getter Locatie 

    // SETTERi
    void setNume(const char *_nume) { // Setter Nume
        delete [] Nume;
        if (_nume != NULL) {
            Nume = new char[std::strlen(_nume) + 1];
            std::strcpy(Nume, _nume);
        }
        else {
            Nume = NULL;
        }
    }
    void setSlogan(const char *_slogan) { // Setter Slogan
        delete [] Slogan;
        if (_slogan != NULL) {
            Slogan = new char[std::strlen(_slogan) + 1];
            std::strcpy(Slogan, _slogan);
        }
        else {
            Slogan = NULL;
        }
    }
    void setFormaJuridica(const char *_FormaJuridica) { // Setter FormaJuridica
        delete [] FormaJuridica;
        if (_FormaJuridica != NULL && (std::strcmp(_FormaJuridica, "PFA") == 0 || std::strcmp(_FormaJuridica, "SRL") == 0 || // Doar UNA din optiuni
            std::strcmp(_FormaJuridica, "SA") == 0)) {
            FormaJuridica = new char[std::strlen(_FormaJuridica) + 1];
            std::strcpy(FormaJuridica, _FormaJuridica);
        }
        else {
            FormaJuridica = NULL;
        }
    }
    void setProduse(const unsigned int _numarProduse, const Produs _produse[]) { // Setter NumarProduse si Produse
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
    void setProdusX(const Produs &produs, unsigned int X) { // Setter Produs de la pozitia X
        if (X >= NumarProduse) {
            return;
        }
        Produse[X] = produs;
    }
    void setAngajati(const unsigned int _numarAngajati, const Angajat _angajati[]) { // Setter NumarAngajati si Angajati
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
    void setAngajatX(const Angajat &angajat, unsigned int X) { // Setter Angajat de la pozitia X
        if (X >= NumarAngajati) {
            return;
        }
        Angajati[X] = angajat;
    }
    void setSef(const Angajat &sef) { Sef = sef; }                  // Setter Sef
    void setLocatie(const Punct2D _locatie) { Locatie = _locatie; } // Setter Locatie

    void stergeProdus(unsigned int pozitie) { // Metoda pentru Stergerea unui Produs de la o Pozitie anume
        if (NumarProduse == 0) return; // NumarProduse = 0 => Nu efectuam nimic

        if (NumarProduse == 1) {       // NumarProduse = 1 => Dezalocam Produse
            delete[] Produse;
            Produse = NULL;
            NumarProduse = 0;
            return;
        }

        if (pozitie >= NumarProduse) { // Daca pozitia >> NumarProduse, se sterge Ultimul Produs
            pozitie = NumarProduse - 1;
        }

        Produs *auxProduse = new Produs[NumarProduse - 1]; // Alocam memorie pentru Array-ul nou
        for (unsigned int i = 0; i < pozitie; ++i) {
            auxProduse[i] = Produse[i];                    // Copiem datele in Array-ul nou
        }
        for (unsigned int i = pozitie + 1; i < NumarProduse; ++i) {
            auxProduse[i - 1] = Produse[i];
        }

        --NumarProduse;       // Decrementam NumarProduse cu 1
        delete[] Produse;     // Dezalocam Produse
        Produse = auxProduse; // Produse devine auxProduse
    }
    void stergeAngajat(unsigned int pozitie) { // Metoda pentru Stergerea unui Angajat
        if (NumarAngajati == 0) return; // Nu efectuam nimic

        if (NumarAngajati == 1) {       // NumarAngajati = 1 => Dezalocam Angajati
            delete[] Angajati;
            Angajati = NULL;
            NumarAngajati = 0;
            return;
        }

        if (pozitie >= NumarAngajati) { // Daca pozitie >> NumarAngajati, se elimina Ultimul Angajat
            pozitie = NumarAngajati - 1;
        }

        Angajat *auxAngajati = new Angajat[NumarAngajati - 1]; // Alocam memorie pentru Array-ul nou
        for (unsigned int i = 0; i < pozitie; ++i) {
            auxAngajati[i] = Angajati[i];                      // Copiem datele
        }
        for (unsigned int i = pozitie + 1; i < NumarAngajati; ++i) {
            auxAngajati[i - 1] = Angajati[i];
        }

        --NumarAngajati;        // Decrementam NumarAngajati cu 1
        delete[] Angajati;      // Dezalocam Angajati
        Angajati = auxAngajati; // Angajati devine auxAngajati
    }


    void insereazaProdus(unsigned int pozitie, const Produs &p) { // Metoda de Inserare a unui Produs la Pozitia specificata
        if (pozitie > NumarProduse) { // Daca pozitie >> NumarProduse, inserarea se va face la capatul Array-ului
            pozitie = NumarProduse;
        }

        Produs *auxProduse = new Produs[NumarProduse + 1]; // Alocam memorie pentru noul Array
        for (unsigned int i = 0; i < pozitie; ++i) {
            auxProduse[i] = Produse[i];                    // Copiem datele
        }
        auxProduse[pozitie] = p;                           // Facem inserarea propiu-zisa
        for (unsigned int i = pozitie; i < NumarProduse; ++i) {
            auxProduse[i + 1] = Produse[i];
        
        }
        ++NumarProduse;       // Incrementam NumarProduse cu 1
        delete[] Produse;     // Dezalocam Produse
        Produse = auxProduse; // Produse devine auxProduse
    }
    void insereazaAngajat(unsigned int pozitie, const Angajat &a) { // Metoda de Inserare a unui Angajat la Pozitia specificata
        if (pozitie > NumarAngajati) { // Daca pozitie >> NumarAngajati, inserarea se va face la capatul Array-ului
            pozitie = NumarAngajati;
        }

        Angajat *auxAngajati = new Angajat[NumarAngajati + 1]; // Alocam memorie pentru noul Array
        for (unsigned int i = 0; i < pozitie; ++i) {
            auxAngajati[i] = Angajati[i];                      // Copiem datele
        }
        auxAngajati[pozitie] = a;                              // Facem inserarea propiu-zisa
        for (unsigned int i = pozitie; i < NumarAngajati; ++i) {
            auxAngajati[i + 1] = Angajati[i];
        }
        
        ++NumarAngajati;        // Incrementam NumarProduse cu 1
        delete[] Angajati;      // Dezalocam Angajati
        Angajati = auxAngajati; // Angajati devine auxAngajati
    }

    friend std::ostream& operator<<(std::ostream &out, const Magazin &m) { // Operator Overloading pentru afisare (<<)
        out << "===== " << (m.Nume == NULL || m.Nume[0] == '\0' ? "NULL" : m.Nume) << " =====" << std::endl; // Daca, pentru o data membra, valoarea ei este NULL,
        out << "# Slogan: " << (m.Slogan == NULL || m.Slogan[0] == '\0' ? "NULL" : m.Slogan) << std::endl;   // se afiseaza deasemenea NULL

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

    ~Magazin() { // Destructor (dezalocam memoria alocata dinamic)
        delete[] Nume;
        delete[] Slogan;
        delete[] FormaJuridica;
        delete[] Produse;
        delete[] Angajati;
    }
};
