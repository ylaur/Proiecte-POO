#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Magazin.h"

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
        Magazine[X] = m;
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
