#pragma once
#include <iostream>
#include <cstring>

class Angajat {
    char *Nume;
    char *Prenume;
    unsigned long long CNP;
    char *NumarTelefon;
    char *Functie;

bool validNrTel(const char *numarTelefon) {
    if (numarTelefon == NULL || std::strlen(numarTelefon) != 10) {
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

bool validCNP(unsigned long long cnp) {
    // Format CNP: SAALLZZJJNNNC - 13 cifre
    unsigned long long copieCNP = cnp / 10;

    if (cnp < 1000000000000ULL || cnp >= 10000000000000ULL) {
        return 0;
    }

    unsigned short int CifraControl = cnp % 10; // Salvam C intr-o variabila pentru a fi ulterior verificat
    cnp /= 10;

    if (cnp % 1000 == 0) return 0;
    cnp /= 1000; // Taiem NNN (NNN apartine intervalului [1, 999])

    unsigned short int JJ = cnp % 100;
    if (JJ != 51 && JJ != 52 && JJ != 70 && (JJ < 1 || JJ > 48)) {
        return 0;
    }
    cnp /= 100;

    if (cnp % 100 < 1 || cnp % 100 > 31) return 0;
    cnp /= 100;

    unsigned short int LL = cnp % 100;
    if (LL < 1 || LL > 12) return 0;
    cnp /= 100;

    unsigned short int AA = cnp % 100;
    cnp /= 100;

    unsigned short int S = cnp % 100;

    // Caz particular: Sectorul 7 si 8 desfiintate in August 1979
    if ((JJ == 47 || JJ == 48) && LL >= 8 && AA >= 79) return 0;

    if (S != 1 && S != 2 && S != 5 && S != 6) return 0;
    if ((S == 5 || S == 6) && AA > 26) return 0; // Cineva nascut dupa 2000 nu poate avea ult. 2 cif. din an > 26

    unsigned long long validC = 0;
    unsigned long long CONST = 279146358279ULL;
    while (copieCNP) {
            validC += (copieCNP % 10) * (CONST % 10);
        CONST /= 10;
        copieCNP /= 10;
    }
    validC %= 11;
    if (validC < 10 && CifraControl != validC) return 0;
    if (validC == 10 && CifraControl != validC - 9) return 0;

    return 1;
}

public:
    Angajat() : Nume(NULL), Prenume(NULL), NumarTelefon(NULL), Functie(NULL), CNP(0) {};
    Angajat(const char *nume, const char *prenume, unsigned long long cnp, const char *numarTelefon, const char *functie) {
        if (nume != NULL) {
            Nume = new char[std::strlen(nume) + 1];
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

        CNP = (validCNP(cnp) ? cnp : 0);
    }
    Angajat(const Angajat &a) {
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
    }

    Angajat& operator=(const Angajat &a) {
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

        return *this;
    }

    const char* getNume () const { return Nume; }
    const char* getPrenume() const { return Prenume; }
    const char* getNumarTelefon() const { return NumarTelefon; }
    const char* getFunctie() const { return Functie; }
    unsigned long long getCNP() const { return CNP; }

    void setNume(const char *nume) {
        delete [] Nume;
        Nume = NULL;
        if (nume != NULL) {
            Nume = new char[std::strlen(nume) + 1];
            std::strcpy(Nume, nume);
        }
    }
    void setPrenume(const char *prenume) {
        delete [] Prenume;
        Prenume = NULL;
        if (prenume != NULL) {
            Prenume = new char[std::strlen(prenume) + 1];
            std::strcpy(Prenume, prenume);
        }
    }
    void setNumarTelefon(const char *numarTelefon) {
        delete [] NumarTelefon;
        NumarTelefon = NULL;

        if (validNrTel(numarTelefon)) {
            NumarTelefon = new char[std::strlen(numarTelefon) + 1];
            std::strcpy(NumarTelefon, numarTelefon);
        }
    }
    void setFunctie(const char *functie) {
        delete [] Functie;
        Functie = NULL;

        if (functie != NULL) {
            Functie = new char[std::strlen(functie) + 1];
            std::strcpy(Functie, functie);
        }
    }
    void setCNP(unsigned long long cnp) {
        CNP = 0;
        if (validCNP(cnp))
            CNP = cnp;
    }

    friend std::ostream& operator<<(std::ostream &out, const Angajat &a) {
        out << "Detalii angajat: \n";
        out << "Nume: " << (a.Nume == NULL ? "NULL" : a.Nume) << "\nPrenume: " << (a.Prenume == NULL ? "NULL" : a.Prenume) <<
               "\nFunctie: " << (a.Functie == NULL ? "NULL" : a.Functie) <<
               "\nContact: " << (a.NumarTelefon  == NULL ? "NULL" : a.NumarTelefon)<< "\n";
        return out;
    }

    ~Angajat() {
        delete[] Nume;
        delete[] Prenume;
        delete[] NumarTelefon;
        delete[] Functie;
    }
};
