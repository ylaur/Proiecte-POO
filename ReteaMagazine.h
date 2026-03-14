#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Magazin.h"

class ReteaMagazine { //  Un obiect de tip "ReteaMagazine" are 2 date membre: NumarMagazine si Magazine.
    unsigned int NumarMagazine;
    Magazin *Magazine;

    double **Harta = NULL;   // Toate aceste "variabile" (Harta, ..., ULTIMUL_VIZITAT) sunt "variabile" pentru "Caching",
    double *Distante = NULL; // iar User-ul nu are acces la ele, nefiind necesare acestuia.
    bool *Vizitat = NULL;
    unsigned long long *Parinte = NULL;
    const double INF = INFINITY; 
    const unsigned int DEVIATIE_RELIEF = 110; // Ca si in viata reala, relieful nu este perfect.
    const unsigned int OFFSET = 20;           // Rolul acestor "variabile" este sa simuleze un scenariu real.
    bool MODIFICAT = 1;               // Rol de optimizare
    unsigned int ULTIMUL_VIZITAT = 0; // Rol de optimizare

    void animatie_consola() { // Metoda privata pentru animatia din consola. Este accesata doar daca alte metode (publice) ale obiectului sunt apelate
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

    void initializare(const unsigned int NumarOrdineMagazin) { // Metoda privata pentru intializare. Pentru algoritmul lui Dijkstra (aflat in alte metode ale obiectului)
        std::srand(std::time(0));                              // este necesara prelucrarea datelor User-ului.  

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
        for (unsigned int i = 0; i < NumarMagazine; ++i) Distante[i] = INF;
        Distante[NumarOrdineMagazin] = 0;

        Harta = new double*[NumarMagazine];                // Generarea hartii (grafului) asociata datelor User-ului. 
        for (unsigned int i = 0; i < NumarMagazine; ++i) {
            Harta[i] = new double[NumarMagazine]();
            for (unsigned int j = 0; j < NumarMagazine; ++j) {
                unsigned long long OBSTACOL = std::rand();
                Harta[i][j] = Magazine[i].getLocatie().distanta(Magazine[j].getLocatie()) + (i != j ? OBSTACOL % DEVIATIE_RELIEF + OFFSET: 0);
            }
        }
    }

    unsigned int* CelMaiIndepartatMagazin() const { // Metoda privata, apelata doar daca face parte din optiunile date de User.
        if (NumarMagazine < 2) return NULL;         // Returneaza Numarul De Ordine al Magazinului cel mai INDEPARTAT de un Magazin X (deja precalculat de alta metoda)

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

    unsigned int* CelMaiApropiatMagazin() const { // Metoda privata, apelata doar daca faca parte din optiunile date de User.
        if (NumarMagazine < 2) return NULL;       // Returneaza Numarul De Ordine al Magazinului cel mai APROPIAT de un Magazin X (deja precalculat de alta metoda)

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

    unsigned int* ReconstruiesteDrum(const unsigned int destinatie) const { // Metoda privata, apelata doar daca face parte din optiunile date de User.
        if (destinatie >= NumarMagazine || destinatie < 0 ) return NULL;    // Returneaza Cel mai Scurt DRUM pentru a distribui de la Magazinul X (deja precalculat de alta metoda),
                                                                            // catre Magazinul specificat de User.
        unsigned int numar_noduri = 1;
        unsigned int curent = destinatie;
        while (curent != ULTIMUL_VIZITAT) {
            numar_noduri++;
            curent = Parinte[curent];
        }

        unsigned int *drum = new unsigned int[numar_noduri + 1];
        drum[0] = numar_noduri; // Pentru ca User-ul sa parcurga DRUMUL furnizat, pe pozitia 0 se afla Numarul De Magazine aflate pe ruta de distributie.

        curent = destinatie;
        for (int i = numar_noduri; i >= 1; --i) {
            drum[i] = curent;
            curent = Parinte[curent];
        }

        return drum;
    }

    unsigned int* MagazineRaza(unsigned int raza) const { // Metoda privata, apelata doar daca face parte din opitunile date de User.
        if (NumarMagazine <= 1) return NULL;              // Returneaza TOATE Magazinele aflate in RAZA Magazinlui specificat de User in alta metoda.

        unsigned int counter = 0;
        for (unsigned int i = 0; i < NumarMagazine; ++i) {
            if (i != ULTIMUL_VIZITAT && Distante[i] <= raza) ++counter;
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
    ReteaMagazine() : NumarMagazine(0), Magazine(NULL) {} // Constructor fara parametrii
    ReteaMagazine(const unsigned int _nrMag, const Magazin *mag) : NumarMagazine(_nrMag) { // Constructor cu cele 2 date membre accesibile de User.
        if (NumarMagazine != 0) {
            Magazine = new Magazin[NumarMagazine];
            for (unsigned int i = 0; i < NumarMagazine; i++) Magazine[i] = mag[i];
        } else {
            Magazine = NULL;
        }
    }
    ReteaMagazine(const ReteaMagazine &m) { // Constructor de copiere
        NumarMagazine = m.NumarMagazine;
        if (NumarMagazine != 0) {
            Magazine = new Magazin[NumarMagazine];
            for (unsigned int i = 0; i < NumarMagazine; ++i) Magazine[i] = m.Magazine[i];
        } else {
            Magazine = NULL;
        }
        MODIFICAT = 1;
    }

    ReteaMagazine& operator=(const ReteaMagazine &m) { // Operator Overloading pentru "="
        if (&m == this) return *this;

        if (Harta != NULL) {
            for (unsigned int i = 0; i < NumarMagazine; ++i) delete[] Harta[i];
        }
        delete[] Harta; Harta = NULL;
        delete[] Distante; Distante = NULL;
        delete[] Vizitat; Vizitat = NULL;
        delete[] Magazine; Magazine = NULL;
        delete[] Parinte; Parinte = NULL;

        NumarMagazine = m.NumarMagazine;
        if (NumarMagazine != 0) {
            Magazine = new Magazin[NumarMagazine];
            for (unsigned int i = 0; i < NumarMagazine; ++i) Magazine[i] = m.Magazine[i];
        } else {
            Magazine = NULL;
        }

        MODIFICAT = 1;
        return *this;
    }

    unsigned int* distributie(unsigned int NumarOrdineMagazin, const unsigned int optiune = 1, const long long X = -1) { 
        if (NumarOrdineMagazin == 0 || NumarOrdineMagazin > NumarMagazine || NumarMagazine == 0)
            return NULL;        // Metoda ce returneaza Output specific dupa Input-ul introdus de User.
				                // User-ul introduce Numarul de Ordine al Magazinului de la care vrea sa primeasca date legate de distributie.
				                // Metoda are 4 optiuni (vezi mai jos). Unele optiuni necesita si alt argument la apel (X). 
                                // Aici se efectueaza calculul "variabilelor" de "Caching".
        --NumarOrdineMagazin;

        if (ULTIMUL_VIZITAT != NumarOrdineMagazin || MODIFICAT == 1) { // Determinarea eficientei de distributie pentru fiecare Magazin, 
            MODIFICAT = 0;
            ULTIMUL_VIZITAT = NumarOrdineMagazin;

            animatie_consola();
            initializare(NumarOrdineMagazin);

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

        switch (optiune) { // Sectiunea aceasta are rolul de a selecta optiunea pe baza argumentelor specificate de User la apelul metodei.
	    case 1: return (X != -1 ? ReconstruiesteDrum(X) : NULL);     // Op1: Primeste argumentul X (Magazin Destinatie). Descrierea optiunii este mai sus
	    case 2: return (X != -1 ? MagazineRaza(X) : NULL);           // Op2: Primeste argumentul X (RAZA). Descrierea optiunii este mai sus
	    case 3: return (X == -1 ? CelMaiIndepartatMagazin() : NULL); // Op3: NU primeste niciun argument. Descrierea optiunii este mai sus
	    case 4: return (X == -1 ? CelMaiApropiatMagazin() : NULL);   // Op4: NU primeste niciun argument. Descrierea optiunii este mai sus
	    default: return NULL;                                        // Op/: In cazul in care optiunea nu este valida, se returneaza NULL
        }
    }

    void stergeMagazin(unsigned int pozitie) { // Metoda pentru stergerea la o pozitie (0, ..., NumarMagazine - 1) corespunzatoare a unui Magazin.
        if (NumarMagazine == 0) return;        // Daca pozitia >= NumarMagazine, se va sterge ultimul Magazin.

        if (Harta != NULL) {
            for (unsigned int i = 0; i < NumarMagazine; ++i) delete[] Harta[i];
            delete[] Harta; Harta = NULL;
            delete[] Distante; Distante = NULL;
            delete[] Vizitat; Vizitat = NULL;
            delete[] Parinte; Parinte = NULL;
        }

        if (NumarMagazine == 1) {
            delete[] Magazine; Magazine = NULL;
            NumarMagazine = 0;
            MODIFICAT = 1;
            return;
        }

        if (pozitie >= NumarMagazine) pozitie = NumarMagazine - 1;

        Magazin *auxMagazine = new Magazin[NumarMagazine - 1];
        for (unsigned int i = 0; i < pozitie; ++i) auxMagazine[i] = Magazine[i]; 
        for (unsigned int i = pozitie + 1; i < NumarMagazine; ++i) auxMagazine[i - 1] = Magazine[i];

        --NumarMagazine;
        delete[] Magazine;
        Magazine = auxMagazine;
        MODIFICAT = 1;
    }

    void insereazaMagazin(unsigned int pozitie, const Magazin &m) { // Metoda pentru inserarea la o pozitie (0, NumarMagazine) corespunzatoare a unui Magazin.
        if (pozitie > NumarMagazine) pozitie = NumarMagazine;       // Daca pozitia > NumarMagazine, se va insera la final.

        if (Harta != NULL) {
            for (unsigned int i = 0; i < NumarMagazine; ++i) delete[] Harta[i];
            delete[] Harta; Harta = NULL;
            delete[] Distante; Distante = NULL;
            delete[] Vizitat; Vizitat = NULL;
            delete[] Parinte; Parinte = NULL;
        }

        if (NumarMagazine == 0) {
            NumarMagazine = 1;
            Magazine = new Magazin[1];
            *Magazine = m;
            MODIFICAT = 1;
            return;
        }

        Magazin *auxMagazine = new Magazin[NumarMagazine + 1];
        for (unsigned int i = 0; i < pozitie; ++i) auxMagazine[i] = Magazine[i];
        auxMagazine[pozitie] = m;
        for (unsigned int i = pozitie; i < NumarMagazine; ++i) auxMagazine[i + 1] = Magazine[i];

        ++NumarMagazine;
        delete[] Magazine;
        Magazine = auxMagazine;
        MODIFICAT = 1;
    }

    unsigned int getNumarMagazine() const { return NumarMagazine; } // GETTERI
    Magazin* getMagazine() const { return Magazine; }
    void setMagazine(const unsigned int _nrMag, const Magazin *magazine) { // SETTER (din motive de bune practici, se accepta Numarul Magazinelor, impreuna cu ele).
        if (Harta != NULL) {
            for (unsigned int i = 0; i < NumarMagazine; i++) delete[] Harta[i];
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
        for (unsigned int i = 0; i < NumarMagazine; i++) Magazine[i] = magazine[i];
        MODIFICAT = 1;
    }

    ~ReteaMagazine() { // Destructor
        delete[] Magazine;
        if (Harta != NULL) {
            for (unsigned int i = 0; i < NumarMagazine; i++) delete[] Harta[i];
        }
        delete[] Harta;
        delete[] Distante;
        delete[] Vizitat;
        delete[] Parinte;
    }
};
