#pragma once
#include <iostream>
#include <cstring>

class Angajat { // Clasa Anagajat
    char *Nume;             //  6 Date Membre
    char *Prenume;
    unsigned long long CNP;
    unsigned long long Salariu;
    char *NumarTelefon;
    char *Functie;

static bool validNrTel(const char *numarTelefon) {                 // Metoda Privata
    if (numarTelefon == NULL || std::strlen(numarTelefon) != 10) { // Rol: valideaza un Numar de Telefon
        return 0;
    }

    if (numarTelefon[0] - '0' != 0 || numarTelefon[1] - '0' != 7) {
        return 0;
    }

    for (int i = 2; i < 10; ++i) {
        if (numarTelefon[i] - '0' < 0 || numarTelefon[i] - '0' > 9) {
            return 0;
        }
    }

    return 1;
}

static bool validCNP(unsigned long long cnp) { // Metoda Privata
    // Format CNP: SAALLZZJJNNNC - 13 cifre    // Rol: Valideaza un CNP, mai multe detalii la: https://ro.wikipedia.org/wiki/Cod_numeric_personal_(Rom%C3%A2nia)
    unsigned long long copieCNP = cnp / 10;

    if (cnp < 1000000000000ULL || cnp >= 10000000000000ULL) { // Contine DOAR 13 Cifre
        return 0;
    }

    unsigned short int CifraControl = cnp % 10; // Salvam C intr-o variabila pentru a fi ulterior verificat
    cnp /= 10;

    if (cnp % 1000 == 0) return 0;
    cnp /= 1000; // Taiem NNN (NNN apartine intervalului [1, 999])

    unsigned short int JJ = cnp % 100; // Salvam JJ = Cod Judet
    if (JJ != 51 && JJ != 52 && JJ != 70 && (JJ < 1 || JJ > 48)) {
        return 0;
    }
    cnp /= 100;

    if (cnp % 100 < 1 || cnp % 100 > 31) return 0; // Validam Luna
    cnp /= 100;

    unsigned short int LL = cnp % 100; // Salvam LL = Luna
    if (LL < 1 || LL > 12) return 0;
    cnp /= 100;

    unsigned short int AA = cnp % 100; // Salvam AA = An
    cnp /= 100;

    unsigned short int S = cnp % 100; // Salvam S

    // Caz particular: Sectorul 7 si 8 desfiintate in August 1979
    if ((JJ == 47 || JJ == 48) && LL >= 8 && AA >= 79) return 0;

    if (S != 1 && S != 2 && S != 5 && S != 6) return 0; // Validam S
    if ((S == 5 || S == 6) && AA > 26) return 0; // Cineva nascut dupa 2000 nu poate avea ult. 2 cif. din an > 26

    unsigned long long validC = 0; // Validam C
    unsigned long long CONST = 279146358279ULL;
    while (copieCNP) {
            validC += (copieCNP % 10) * (CONST % 10);
        CONST /= 10;
        copieCNP /= 10;
    }
    validC %= 11;
    if (validC < 10 && CifraControl != validC) return 0;
    if (validC == 10 && CifraControl != validC - 9) return 0;

    return 1; // Daca am ajuns aici, CNP-ul este VALID
}

public:
    Angajat() : Nume(NULL), Prenume(NULL), NumarTelefon(NULL), Functie(NULL), CNP(0), Salariu(0) {}; // Constructor fara Parametrii
    Angajat(const char *nume, const char *prenume, unsigned long long cnp, const char *numarTelefon, const char *functie, unsigned long long salariu) { // Constructor cu Parametrii
        if (nume != NULL) {
            Nume = new char[std::strlen(nume) + 1]; // Alocare dinamica a memoriei
            std::strcpy(Nume, nume);
        }
        else {
            Nume = NULL;
        }

        if (prenume != NULL) {
            Prenume = new char[std::strlen(prenume) + 1];
            std::strcpy(Prenume, prenume);
        }
        else {
            Prenume = NULL;
        }

        if (validNrTel(numarTelefon)) { // Va verifica oricum daca numarTelefon este sau nu NULL
            NumarTelefon = new char[std::strlen(numarTelefon) + 1];
            std::strcpy(NumarTelefon, numarTelefon);
        }
        else {
            NumarTelefon = NULL;
        }

        if (functie != NULL) {
            Functie = new char[std::strlen(functie) + 1];
            std::strcpy(Functie, functie);
        }
        else {
            Functie = NULL;
        }

        CNP = (validCNP(cnp) ? cnp : 0); // Daca CNP-ul NU este Valid, i se va asigna valoarea 0
        Salariu = salariu;
    }
    Angajat(const Angajat &a) { // Constructor de Copiere
        if (a.Nume != NULL) {
            Nume = new char[std::strlen(a.Nume) + 1];
            std::strcpy(Nume, a.Nume);
        }
        else {
            Nume = NULL;
        }

        if (a.Prenume != NULL) {
            Prenume = new char[std::strlen(a.Prenume) + 1];
            std::strcpy(Prenume, a.Prenume);
        }
        else {
            Prenume = NULL;
        }

        if (a.NumarTelefon != NULL) {
            NumarTelefon = new char[std::strlen(a.NumarTelefon) + 1];
            std::strcpy(NumarTelefon, a.NumarTelefon);
        }
        else {
            NumarTelefon = NULL;
        }

        if (a.Functie != NULL) {
            Functie = new char[std::strlen(a.Functie) + 1];
            std::strcpy(Functie, a.Functie);
        }
        else {
            Functie = NULL;
        }

        CNP = a.CNP;
        Salariu = a.Salariu;
    }

    Angajat& operator=(const Angajat &a) { // Operator Overloading pentru asignare (=)
        if (&a == this) {
            return *this;
        }

        delete[] Nume;
        delete[] Prenume;
        delete[] NumarTelefon;
        delete[] Functie;

        if (a.Nume != NULL) {
            Nume = new char[std::strlen(a.Nume) + 1];
            std::strcpy(Nume, a.Nume);
        }
        else {
            Nume = NULL;
        }

        if (a.Prenume != NULL) {
            Prenume = new char[std::strlen(a.Prenume) + 1];
            std::strcpy(Prenume, a.Prenume);
        }
        else {
            Prenume = NULL;
        }

        if (a.NumarTelefon != NULL) {
            NumarTelefon = new char[std::strlen(a.NumarTelefon) + 1];
            std::strcpy(NumarTelefon, a.NumarTelefon);
        }
        else {
            NumarTelefon = NULL;
        }

        if (a.Functie != NULL) {
            Functie = new char[std::strlen(a.Functie) + 1];
            std::strcpy(Functie, a.Functie);
        }
        else {
            Functie = NULL;
        }

        CNP = a.CNP;
        Salariu = a.Salariu;
        
        return *this;
    }

    // GETTERI
    const char* getNume () const { return Nume; }                // Getter pentru Nume
    const char* getPrenume() const { return Prenume; }           // Getter pentru Prenume
    const char* getNumarTelefon() const { return NumarTelefon; } // Getter pentru NumarTelefon
    const char* getFunctie() const { return Functie; }           // Getter pentru Functie
    unsigned long long getCNP() const { return CNP; }            // Getter pentru CNP
    unsigned long long getSalariu() const { return Salariu; }    // Getter pentru Salariu

    // SETTERI
    void setNume(const char *nume) { // Setter pentru Nume
        delete [] Nume; // Dezalocarea memoriei alocate dinamic
        Nume = NULL; // In cazul in care variabila data ca parametru (nume) are valori eronate, Nume = NULL
        if (nume != NULL) {
            Nume = new char[std::strlen(nume) + 1];
            std::strcpy(Nume, nume);
        }
    }
    void setPrenume(const char *prenume) { // Setter pentru Prenume
        delete [] Prenume;
        Prenume = NULL;
        if (prenume != NULL) {
            Prenume = new char[std::strlen(prenume) + 1];
            std::strcpy(Prenume, prenume);
        }
    }
    void setNumarTelefon(const char *numarTelefon) { // Setter pentru NumarTelefon
        delete [] NumarTelefon;
        NumarTelefon = NULL;

        if (validNrTel(numarTelefon)) { // Validam corectitudinea variabilei date ca parametru (numarTelefon)
            NumarTelefon = new char[std::strlen(numarTelefon) + 1];
            std::strcpy(NumarTelefon, numarTelefon);
        }
    }
    void setFunctie(const char *functie) { // Setter pentru Functie
        delete [] Functie;
        Functie = NULL;

        if (functie != NULL) {
            Functie = new char[std::strlen(functie) + 1];
            std::strcpy(Functie, functie);
        }
    }
    void setCNP(unsigned long long cnp) { // Setter pentru CNP
        CNP = 0; 
        if (validCNP(cnp)) // Validam corectitudinea variabilei data ca parametru (cnp). In cazul in care nu este Valida, CNP = 0
            CNP = cnp;
    }
    void setSalariu(unsigned long long salariu) { Salariu = salariu; } // Setter pentru Salariu

    friend std::ostream& operator<<(std::ostream &out, const Angajat &a) { // Operator Overloading pentru afisare (<<)
        out << "Detalii angajat: \n";
        out << "Nume: " << (a.Nume == NULL ? "NULL" : a.Nume) << "\nPrenume: " << (a.Prenume == NULL ? "NULL" : a.Prenume) <<
               "\nFunctie: " << (a.Functie == NULL ? "NULL" : a.Functie) <<
               "\nContact: " << (a.NumarTelefon  == NULL ? "NULL" : a.NumarTelefon)<< "\n";
        return out;
    }

    ~Angajat() { // Destructor (dezalocam memoria alocata dinamic)
        delete[] Nume;
        delete[] Prenume;
        delete[] NumarTelefon;
        delete[] Functie;
    }
};
