#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <cmath>
#include <ctime>

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

class Punct2D {
    unsigned int X, Y;

public:
    Punct2D() : X(0), Y(0) {};
    Punct2D(const unsigned int x, const unsigned int y) : X(x), Y(y) {};
    Punct2D(const Punct2D &p) { X = p.X; Y = p.Y; };

    unsigned int getX() const { return this->X; }
    unsigned int getY() const { return this->Y; }

    void setX(const unsigned int x) { this->X = x; };
    void setY(const unsigned int y) { this->Y = y; };

    double distanta(const Punct2D &p) const {
        const long long x = (long long)this->X - (long long)p.X;
        const long long y = (long long)this->Y - (long long)p.Y;
        return std::sqrt(x * x + y * y);
    }

    friend std::ostream& operator<<(std::ostream &out, const Punct2D &p) {
        out << std::setprecision(2) << std::fixed << "(" << p.X << ", " << p.Y << ")";
        return out;
    }

    ~Punct2D() {};
};

class Angajat {
    char *Nume;
    char *Prenume;
    unsigned long long CNP;
    char *NumarTelefon;
    char *Functie;
    unsigned long long Salariu;

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
    Angajat() : Nume(NULL), Prenume(NULL), NumarTelefon(NULL), Functie(NULL), CNP(0), Salariu(0) {};
    Angajat(const char *nume, const char *prenume, unsigned long long cnp, const char *numarTelefon, const char *functie, unsigned long long salariu) {
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
        Salariu = salariu;
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
        Salariu = a.Salariu;
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
        Salariu = a.Salariu;

        return *this;
    }

    const char* getNume () const { return Nume; }
    const char* getPrenume() const { return Prenume; }
    const char* getNumarTelefon() const { return NumarTelefon; }
    const char* getFunctie() const { return Functie; }
    unsigned long long getCNP() const { return CNP; }
    unsigned long long getSalariu() const { return Salariu; }

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
    void setSalariu(unsigned long long salariu) { Salariu = salariu; }

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

class ReteaMagazine {
    unsigned int NumarMagazine;
    Magazin *Magazine;

    double **Harta = NULL;
    double *Distante = NULL;
    bool *Vizitat = NULL;
    unsigned long long *Parinte = NULL;
    const double INF = INFINITY;
    const unsigned int DEVIATIE_RELIEF = 110;
    const unsigned int OFFSET = 20;
    bool MODIFICAT = 1;
    unsigned int ULTIMUL_VIZITAT = 0;

    void animatie_consola() {
        const unsigned int TIMP = 325;
        for (unsigned int i = 0; i < 3; ++i) {
            std::cout << "Incarcare   " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(TIMP));
            std::cout << "\rIncarcare.  " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(TIMP));
            std::cout << "\rIncarcare.. " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(TIMP));
            std::cout << "\rIncarcare..." << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(TIMP));
            std::cout << '\r' << std::flush;
        }
        std::cout << "            \r" << std::flush;
    }

    void initializare(const unsigned int NumarOrdineMagazin) {
        std::srand(std::time(0));

        if (Harta != NULL) {
            for (unsigned int i = 0; i < NumarMagazine; i++) {
                delete[] Harta[i];
            }
        }
        delete[] Harta;
        delete[] Distante;
        delete[] Vizitat;
        delete[] Parinte;

        Vizitat = new bool[NumarMagazine]();
        Distante = new double[NumarMagazine];
        Parinte = new unsigned long long[NumarMagazine]();
        for (unsigned int i = 0; i < NumarMagazine; ++i) {
            Distante[i] = INF;
        }
        Distante[NumarOrdineMagazin] = 0;

        Harta = new double*[NumarMagazine];
        for (unsigned int i = 0; i < NumarMagazine; ++i) {
            Harta[i] = new double[NumarMagazine]();
            for (unsigned int j = 0; j < NumarMagazine; ++j) {
                unsigned long long OBSTACOL = std::rand();
                Harta[i][j] = Magazine[i].getLocatie().distanta(Magazine[j].getLocatie()) + (i != j ? OBSTACOL % DEVIATIE_RELIEF + OFFSET: 0);
            }
        }
    }

    unsigned int* CelMaiIndepartatMagazin() const {
        if (NumarMagazine < 2) {
            return NULL;
        }

        double MAX_DIST = -1;
        unsigned int NR_ORD_MAG = 0;
        for (unsigned int i = 0; i < NumarMagazine; ++i) {
            if (ULTIMUL_VIZITAT != i && MAX_DIST < Distante[i]) {
                MAX_DIST = Distante[i];
                NR_ORD_MAG = i;
            }
        }

        unsigned int *MAG_ORD = new unsigned int[1];
        *MAG_ORD = NR_ORD_MAG;
        return MAG_ORD;
    }

    unsigned int* CelMaiApropiatMagazin() const {
        if (NumarMagazine < 2) {
            return NULL;
        }

        double MIN_DIST = INF;
        unsigned int NR_ORD_MAG = 0;
        for (unsigned int i = 0; i < NumarMagazine; ++i) {
            if (ULTIMUL_VIZITAT != i && MIN_DIST > Distante[i]) {
                MIN_DIST = Distante[i];
                NR_ORD_MAG = i;
            }
        }

        unsigned int *MAG_ORD = new unsigned int[1];
        *MAG_ORD = NR_ORD_MAG;
        return MAG_ORD;
    }

    unsigned int* ReconstruiesteDrum(const unsigned int destinatie) const {
        if (destinatie >= NumarMagazine || destinatie < 0 ) {
            return NULL;
        }

        unsigned int numar_noduri = 1;
        unsigned int curent = destinatie;
        while (curent != ULTIMUL_VIZITAT) {
            numar_noduri++;
            curent = Parinte[curent];
        }

        unsigned int *drum = new unsigned int[numar_noduri + 1];
        drum[0] = numar_noduri;

        curent = destinatie;
        for (int i = numar_noduri; i >= 1; --i) {
            drum[i] = curent;
            curent = Parinte[curent];
        }

        return drum;
    }

    unsigned int* MagazineRaza(unsigned int raza) const {
        if (NumarMagazine <= 1) {
            return NULL;
        }

        unsigned int counter = 0;
        for (unsigned int i = 0; i < NumarMagazine; ++i) {
            if (i != ULTIMUL_VIZITAT && Distante[i] <= raza) {
                ++counter;
            }
        }

        unsigned int* magazine = new unsigned int[counter + 1];
        magazine[0] = counter;

        unsigned int index_curent = 1;
        for (unsigned int i = 0; i < NumarMagazine; ++i) {
            if (i != ULTIMUL_VIZITAT && Distante[i] <= raza) {
                magazine[index_curent++] = i;
            }
        }

        return magazine;
    }

public:
    ReteaMagazine() : NumarMagazine(0), Magazine(NULL) {}
    ReteaMagazine(const unsigned int _nrMag, const Magazin *mag) : NumarMagazine(_nrMag) {
        if (NumarMagazine != 0) {
            Magazine = new Magazin[NumarMagazine];
            for (unsigned int i = 0; i < NumarMagazine; i++) {
                Magazine[i] = mag[i];
            }
        }
        else {
            Magazine = NULL;
        }
    }
    ReteaMagazine(const ReteaMagazine &m) {
        NumarMagazine = m.NumarMagazine;
        if (NumarMagazine != 0) {
            Magazine = new Magazin[NumarMagazine];
            for (unsigned int i = 0; i < NumarMagazine; ++i) {
                Magazine[i] = m.Magazine[i];
            }
        }
        else {
            Magazine = NULL;
        }
        MODIFICAT = 1;
    }

    ReteaMagazine& operator=(const ReteaMagazine &m) {
        if (&m == this) {
            return *this;
        }

        if (Harta != NULL) {
            for (unsigned int i = 0; i < NumarMagazine; ++i) {
                delete[] Harta[i];
            }
        }
        delete[] Harta;
        Harta = NULL;
        delete[] Distante;
        Distante = NULL;
        delete[] Vizitat;
        Vizitat = NULL;
        delete[] Magazine;
        Magazine = NULL;
        delete[] Parinte;
        Parinte = NULL;

        NumarMagazine = m.NumarMagazine;
        if (NumarMagazine != 0) {
            Magazine = new Magazin[NumarMagazine];
            for (unsigned int i = 0; i < NumarMagazine; ++i) {
                Magazine[i] = m.Magazine[i];
            }
        }
        else {
            Magazine = NULL;
        }

        MODIFICAT = 1;
        return *this;
    }

    unsigned int* distributie(unsigned int NumarOrdineMagazin, const unsigned int optiune = 1, const long long X = -1) {
        if (NumarOrdineMagazin >= NumarMagazine || NumarMagazine == 0)
            return NULL;

        if (ULTIMUL_VIZITAT != NumarOrdineMagazin || MODIFICAT == 1) {
            MODIFICAT = 0;
            ULTIMUL_VIZITAT = NumarOrdineMagazin;

            initializare(NumarOrdineMagazin);
            animatie_consola();

            for (unsigned int i = 0; i < NumarMagazine; i++) {
                long long MAGAZIN_CURENT = -1;
                double DISTANT_CURENTA = INF;

                for (unsigned int j = 0; j < NumarMagazine; j++)
                    if (!Vizitat[j] && DISTANT_CURENTA > Distante[j]) {
                        MAGAZIN_CURENT = j;
                        DISTANT_CURENTA = Distante[j];
                    }

                if (MAGAZIN_CURENT == -1) break;

                Vizitat[MAGAZIN_CURENT] = 1;
                for (unsigned int j = 0; j < NumarMagazine; j++)
                    if (!Vizitat[j] && Harta[MAGAZIN_CURENT][j] + Distante[MAGAZIN_CURENT] < Distante[j]) {
                        Distante[j] = Harta[MAGAZIN_CURENT][j] + Distante[MAGAZIN_CURENT];
                        Parinte[j] = MAGAZIN_CURENT;
                    }
            }
        }

        switch (optiune) {
            case 1:
                return (X != -1 ? ReconstruiesteDrum(X) : NULL);
            case 2:
                return (X != -1 ? MagazineRaza(X) : NULL);
            case 3:
                return (X == -1 ? CelMaiIndepartatMagazin() : NULL);
            case 4:
                return (X == -1 ? CelMaiApropiatMagazin() : NULL);
            default:
                return NULL;
        }
    }

    void stergeMagazin(unsigned int pozitie) {
        if (NumarMagazine == 0) return;

        if (Harta != NULL) {
            for (unsigned int i = 0; i < NumarMagazine; ++i) {
                delete[] Harta[i];
            }
            delete[] Harta;
            Harta = NULL;
            delete[] Distante;
            Distante = NULL;
            delete[] Vizitat;
            Vizitat = NULL;
            delete[] Parinte;
            Parinte = NULL;
        }

        if (NumarMagazine == 1) {
            delete[] Magazine;
            Magazine = NULL;
            NumarMagazine = 0;
            MODIFICAT = 1;
            return;
        }

        if (pozitie >= NumarMagazine) {
            pozitie = NumarMagazine - 1;
        }

        Magazin *auxMagazine = new Magazin[NumarMagazine - 1];
        for (unsigned int i = 0; i < pozitie; ++i) {
            auxMagazine[i] = Magazine[i];
        }
        for (unsigned int i = pozitie + 1; i < NumarMagazine; ++i) {
            auxMagazine[i - 1] = Magazine[i];
        }

        --NumarMagazine;
        delete[] Magazine;
        Magazine = auxMagazine;
        MODIFICAT = 1;
    }

    void insereazaMagazin(unsigned int pozitie, const Magazin &m) {
        if (pozitie > NumarMagazine) {
            pozitie = NumarMagazine;
        }

        if (Harta != NULL) {
            for (unsigned int i = 0; i < NumarMagazine; ++i) {
                delete[] Harta[i];
            }
            delete[] Harta;
            Harta = NULL;
            delete[] Distante;
            Distante = NULL;
            delete[] Vizitat;
            Vizitat = NULL;
            delete[] Parinte;
            Parinte = NULL;
        }

        if (NumarMagazine == 0) {
            NumarMagazine = 1;
            Magazine = new Magazin[1];
            *Magazine = m;
            MODIFICAT = 1;
            return;
        }

        Magazin *auxMagazine = new Magazin[NumarMagazine + 1];
        for (unsigned int i = 0; i < pozitie; ++i) {
            auxMagazine[i] = Magazine[i];
        }
        auxMagazine[pozitie] = m;
        for (unsigned int i = pozitie; i < NumarMagazine; ++i) {
            auxMagazine[i + 1] = Magazine[i];
        }

        ++NumarMagazine;
        delete[] Magazine;
        Magazine = auxMagazine;
        MODIFICAT = 1;
    }

    unsigned int getNumarMagazine() const { return NumarMagazine; }
    const Magazin* getMagazine() const { return Magazine; }
    Magazin getMagazinX(unsigned int X) const { return (X >= NumarMagazine ? Magazin() : Magazine[X]); }

    void setMagazine(const unsigned int _nrMag, const Magazin *magazine) {
        if (Harta != NULL) {
            for (unsigned int i = 0; i < NumarMagazine; i++) {
                delete[] Harta[i];
            }
        }
        delete[] Harta; Harta = NULL;
        delete[] Distante; Distante = NULL;
        delete[] Vizitat; Vizitat = NULL;
        delete[] Magazine;
        delete[] Parinte;

        NumarMagazine = _nrMag;
        if (NumarMagazine == 0) {
            Magazine = NULL;
            MODIFICAT = 1;
            return;
        }
        Magazine = new Magazin[NumarMagazine];
        for (unsigned int i = 0; i < NumarMagazine; i++) {
            Magazine[i] = magazine[i];
        }
        MODIFICAT = 1;
    }
    void setMagazinX(const Magazin &m, unsigned int X) {
        if (X >= NumarMagazine) {
            return;
        }

        if (Harta != NULL) {
            for (unsigned int i = 0; i < NumarMagazine; i++) {
                delete[] Harta[i];
            }
        }
        delete[] Harta;
        delete[] Distante;
        delete[] Vizitat;
        delete[] Parinte;

        Magazine[X] = m;
        MODIFICAT = 1;
    }

    ~ReteaMagazine() {
        delete[] Magazine;
        if (Harta != NULL) {
            for (unsigned int i = 0; i < NumarMagazine; i++) {
                delete[] Harta[i];
            }
        }
        delete[] Harta;
        delete[] Distante;
        delete[] Vizitat;
        delete[] Parinte;
    }
};

int main() {
    // Proiect POO 1
    // Tema: Comert

    // Teste de creare a obiectelor si apelarea metodelor claselor

    // Creare obiecte de baza (Produse si Angajati)

    // Produse
    Produs alimente[] = {
        Produs("Paine Prahova", 2.5),
        Produs("Lapte 1L", 5.0),
        Produs("Oua 10 buc", 12.0)
    };
    Produs electronice[] = {
        Produs("Laptop Gaming", 4500.0),
        Produs("Mouse Wireless", 120.0)
    };
    Produs haine[] = {
        Produs("Tricou Bumbac", 35.0),
        Produs("Blugi Denim", 150.0),
        Produs("Jacheta Iarna", 300.0),
        Produs("Adidasi Alergare", 250.0)
    };
    Produs constructii[] = {
        Produs("Ciment 25kg", 25.0),
        Produs("Vopsea Lavabila", 80.0)
    };
    Produs fructe[] = {
        Produs("Mere Ionatan", 4.5),
        Produs("Banane", 7.0),
        Produs("Portocale", 6.5)
    };

    // Angajati
    Angajat sef1("Popescu", "Ion", 5050814401233, "0712345678", "Manager General", 8500); // Adaugat salariu
    Angajat echipa1[] = {
        Angajat("Ionescu", "Maria", 2901225224566, "0722334455", "Casier", 3500), // Adaugat salariu
        Angajat("Vasile", "Andrei", 5050814401233, "0799887766", "Lucrator Comercial", 3200) // Adaugat salariu
    };

    Angajat sef2("Marin", "George", 5050814401233, "0744556677", "Director Vanzari", 9000); // Adaugat salariu
    Angajat sef3("Dumitru", "Elena", 2901225224566, "0733112233", "Sef Magazin", 6000); // Adaugat salariu

    Angajat echipa3[] = {
        Angajat("Stan", "Mihai", 5050814401233, "0766112233", "Asistent Vanzari", 4000) // Adaugat salariu
    };

    // Initializare magazine (si crearea Retelei de Magazine)
    Magazin m1("Alimentara Central", "Proaspat in fiecare zi", "SRL", 3, alimente, Punct2D(10, 10), 2, sef1, echipa1);
    Magazin m2("Electro IT", "Tehnologia viitorului", "SA", 2, electronice, Punct2D(15, 20), 0, sef2, NULL);
    Magazin m3("Fashion Hub", "Stilul te defineste", "SRL", 4, haine, Punct2D(100, 100), 1, sef3, echipa3);
    Magazin m4("Brico Universal", "Construim impreuna", "SA", 2, constructii, Punct2D(150, 30), 2, sef1, echipa1);
    Magazin m5("Fructe la Colt", "Vitamine pentru tine", "PFA", 3, fructe, Punct2D(5, 90), 1, sef3, echipa3);

    Magazin arrayMagazine[] = {m1, m2, m3, m4, m5};
    ReteaMagazine reteauaMea(5, arrayMagazine);

    // Testarea Algoritmilor de Distributie (Dijkstra)
    unsigned int* res3 = reteauaMea.distributie(1, 3);
    std::cout << "1) ALGORITMI DE DISTRIBUTIE:\n";
    if (res3 != NULL) {
        std::cout << "Cel mai indepartat magazin: " << reteauaMea.getMagazine()[*res3].getNume() << "\n";
        delete[] res3;
    }

    unsigned int* res4 = reteauaMea.distributie(1, 4);
    if (res4 != NULL) {
        std::cout << "Cel mai apropiat magazin: " << reteauaMea.getMagazine()[*res4].getNume() << "\n";
        delete[] res4;
    }

    unsigned int* res2 = reteauaMea.distributie(1, 2, 150);
    if (res2 != NULL) {
        std::cout << "Magazine in raza de 150 unitati:\n";
        for (unsigned int i = 1; i <= res2[0]; ++i) {
            std::cout << "- " << reteauaMea.getMagazine()[res2[i]].getNume() << "\n";
        }
        delete[] res2;
    }

    unsigned int* res1 = reteauaMea.distributie(1, 1, 3);
    if (res1 != NULL) {
        std::cout << "Traseu catre Brico Universal:\n";
        for (unsigned int i = 1; i <= res1[0]; ++i) {
            std::cout << reteauaMea.getMagazine()[res1[i]].getNume() << (i < *res1 ? " -> " : "");
        }
        std::cout << "\n\n";
        delete[] res1;
    }

    // Testare Metode
    std::cout << "2) TESTARE METODE CLASE:\n";
    // Testare distanta Punct2D
    Punct2D loc1 = m1.getLocatie();
    Punct2D loc2 = m3.getLocatie();
    std::cout << "Distanta intre " << m1.getNume() << loc1 << " si " << m3.getNume() << loc2
              << " este: " << loc1.distanta(loc2) << "\n";

    Angajat sefNou("Mihailescu", "Gelu", 5050814401233, "0788998899", "Boss Suprem", 15000); // Adaugat salariu
    Angajat paznic("Tudor", "Cristi", 5050814401233, "0711112222", "Agent Securitate", 3000); // Adaugat salariu

    m1.setSef(sefNou); // Testam setSef
    m1.insereazaAngajat(m1.getNumarAngajati(), paznic); // Testam insereazaAngajat
    m1.stergeAngajat(0); // Stergem primul angajat

    // Testare metode Produse
    Produs pNou("Paine Neagra", 3.5);
    m1.insereazaProdus(1, pNou); // Inserare
    m1.stergeProdus(0); // Stergere

    std::cout << m1 << "\n"; // Aici testam afisarea completa (Angajati + Produse)

    // Manipulare Retea
    Produs patiserie[] = { Produs("Covrig", 2.0), Produs("Merdenea", 4.0) };
    Angajat sefPatiserie("Zaharia", "Ioana", 2901225224566ULL, "0777888999", "Patiser Sef", 5500); // Adaugat salariu

    Magazin m6("Patiseria de vis", "Cald si bun", "SRL", 2, patiserie, Punct2D(50, 50), 0, sefPatiserie, NULL);

    std::cout << "Inseram un magazin nou (Patiseria) la finalul retelei\n";
    reteauaMea.insereazaMagazin(reteauaMea.getNumarMagazine(), m6);

    reteauaMea.stergeMagazin(1); // Stergere magazin la pozitia 1

    std::cout << "Lista actualizata a magazinelor (" << reteauaMea.getNumarMagazine() << " magazine):\n";
    for(unsigned int i = 0; i < reteauaMea.getNumarMagazine(); ++i) {
        std::cout << i + 1 << ". " << reteauaMea.getMagazine()[i].getNume() << "\n";
    }

    // Testare Constructor de Copiere
    Magazin clonaBrico = m4;
    clonaBrico.setNume("Brico CLONAT");
    Produs fierBeton("Fier Beton", 15.0);
    clonaBrico.setProdusX(fierBeton, 0);

    std::cout << "\nOriginal (" << m4.getNume() << "): Primul produs este "
              << m4.getProdusX(0).getNume() << " - " << m4.getProdusX(0).getPret() << " RON\n";
    std::cout << "Clona (" << clonaBrico.getNume() << "): Primul produs este "
              << clonaBrico.getProdusX(0).getNume() << " - " << clonaBrico.getProdusX(0).getPret() << " RON\n";

    std::cout << "\nMeniu: \n";

    int alegere_meniu = -1;
    while (alegere_meniu != 0) {
        std::cout << "\n*****************************************\n";
        std::cout << "                  MENIU                  \n";
        std::cout << "*****************************************\n";
        std::cout << "1. Afiseaza magazinele din retea\n";
        std::cout << "2. Testeaza metoda 'distributie'\n";
        std::cout << "0. Iesire\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "Alege o optiune: ";

        std::cin >> alegere_meniu;

        switch (alegere_meniu) {
            case 1: {
                std::cout << "\n>>> AFISARE MAGAZINE <<<\n";
                for (unsigned int i = 0; i < reteauaMea.getNumarMagazine(); ++i) {
                     std::cout << reteauaMea.getMagazinX(i) << "\n";
                }
                break;
            }
            case 2: {
                std::cout << "\n>>> METODA DISTRIBUTIE <<<\n";
                unsigned int opt_distributie, sursa;

                std::cout << "Optiuni distributie:\n";
                std::cout << "  1 - Traseu complet catre destinatie\n";
                std::cout << "  2 - Toate magazinele dintr-o raza maxima\n";
                std::cout << "  3 - Cel mai indepartat magazin\n";
                std::cout << "  4 - Cel mai apropiat magazin\n";
                std::cout << "Alege optiunea (1-4): ";
                std::cin >> opt_distributie;

                if (opt_distributie >= 1 && opt_distributie <= 4) {
                    std::cout << "\nMagazine disponibile:\n";
                    for(unsigned int i = 0; i < reteauaMea.getNumarMagazine(); ++i) {
                         std::cout << i << ". " << reteauaMea.getMagazine()[i].getNume() << "\n";
                    }
                    std::cout << "Introdu indexul magazinului sursa (0 - " << reteauaMea.getNumarMagazine() - 1 << "): ";
                    std::cin >> sursa;

                    unsigned int* rezultat = NULL;

                    if (opt_distributie == 1) {
                        long long destinatie;
                        std::cout << "Introdu indexul magazinului destinatie: ";
                        std::cin >> destinatie;
                        rezultat = reteauaMea.distributie(sursa, opt_distributie, destinatie);

                        if (rezultat != NULL) {
                            unsigned int nr_magazine = rezultat[0];
                            std::cout << "\nTraseu gasit (" << nr_magazine << " magazine implicate):\n";
                            for (unsigned int i = 1; i <= nr_magazine; i++) {
                                std::cout << reteauaMea.getMagazine()[rezultat[i]].getNume() << (i < nr_magazine ? " -> " : "");
                            }
                            std::cout << "\n";
                        }
                    }
                    else if (opt_distributie == 2) {
                        long long raza;
                        std::cout << "Introdu raza maxima (distanta in care se cauta): ";
                        std::cin >> raza;
                        rezultat = reteauaMea.distributie(sursa, opt_distributie, raza);

                        if (rezultat != NULL) {
                            unsigned int nr_magazine = rezultat[0];
                            std::cout << "\nS-au gasit " << nr_magazine << " magazine in raza specificata:\n";
                            for (unsigned int i = 1; i <= nr_magazine; i++) {
                                std::cout << "- " << reteauaMea.getMagazine()[rezultat[i]].getNume() << "\n";
                            }
                        }
                    }
                    else if (opt_distributie == 3 || opt_distributie == 4) {
                        rezultat = reteauaMea.distributie(sursa, opt_distributie);

                        if (rezultat != NULL) {
                            std::cout << "\nMagazinul gasit este: " << reteauaMea.getMagazine()[*rezultat].getNume() << "\n";
                        }
                    }

                    if (rezultat != NULL) {
                        delete[] rezultat;
                    } else {
                        std::cout << "Eroare: Metoda a returnat NULL\n";
                    }
                } else {
                    std::cout << "Optiune invalida pentru distributie\n";
                }
                break;
            }
            case 0: {
                std::cout << "\nAi iesit din Meniu\n";
                break;
            }
            default: {
                std::cout << "\nOptiune invalida, mai incearca o data\n";
                break;
            }
        }
    }

    return 0;
}
