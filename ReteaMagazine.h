#pragma once
#include <iostream>
#include <thread>    // 
#include <chrono>    // Introduse pentru "animatia" din consola
#include <cmath>
#include <cstdlib>   //
#include <ctime>     // Introduse pentru generarea corecta a unor Valori din Clasa
#include "Magazin.h" // Folosim Clasele definite anterior (ierarhic)

class ReteaMagazine { // Clasa ReteaMagazine
    unsigned int NumarMagazine; // 11 Date Membre (doar NumarMagazine si Magazine pot fi accesate de Utilizator)
    Magazin *Magazine;          

    // Acestea sunt calculate si folosite doar de Metodele Clasei, Utilizatorul nu ar trebui sa aiba acces la ele (considerate drept date de "Cache")
    double **Harta = NULL;                    // Genereaza Harta Retelei
    double *Distante = NULL;                  // Stocheaza Dinstatele dintre Magazine
    bool *Vizitat = NULL;                     // Folosit doar pentru Parcurgere (la momentul i, stocheaza i valori de 1, restul fiind 0)
    unsigned long long *Parinte = NULL;       // Array "vector" de tati
    const double INF = INFINITY;              // Compiler BUILT-IN (constanta double)
    const unsigned int DEVIATIE_RELIEF = 110; // Folosit la calculare
    const unsigned int OFFSET = 20;           // Folosit la calculare
    bool MODIFICAT = 1;                       // Verifica daca Metoda "distributie" a mai fost apelata inainte si NU s-au efectuat Modificari
    unsigned int ULTIMUL_VIZITAT = 0;         // Folosit la calculare

    void animatie_consola() { // Metoda Privata pentru Animatia din Consola
        const unsigned int TIMP = 325; // Delay-ul dintre cadre
        for (unsigned int i = 0; i < 3; ++i) {
            std::cout << "Incarcare   " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(TIMP));
            std::cout << "\rIncarcare.  " << std::flush; // Folosim \r pentru a merge la inceputul randului, dupa aceea stergem randul
            std::this_thread::sleep_for(std::chrono::milliseconds(TIMP));
            std::cout << "\rIncarcare.. " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(TIMP));
            std::cout << "\rIncarcare..." << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(TIMP));
            std::cout << '\r' << std::flush;
        }
        std::cout << "            \r" << std::flush;
    }

    void initializare(const unsigned int NumarOrdineMagazin) { // Metoda Privata folosita la initializarea
        std::srand(std::time(0));

        // In cazul in care s-a mai apelat metoda, dezalocam valorile vechi
        if (Harta != NULL) { 
            for (unsigned int i = 0; i < NumarMagazine; i++) {
                delete[] Harta[i];
            }
        }
        delete[] Harta;
        delete[] Distante;
        delete[] Vizitat;
        delete[] Parinte;

        Vizitat = new bool[NumarMagazine]();  // Initalizam totul cu 0
        Distante = new double[NumarMagazine];
        Parinte = new unsigned long long[NumarMagazine](); 
        for (unsigned int i = 0; i < NumarMagazine; ++i) {
            Distante[i] = INF; // Initializam Disntantele cu constanta INF
        }
        Distante[NumarOrdineMagazin] = 0; // Distanta de la Magazinul dat ca parametru si el insusi este intotdeauna 0

        Harta = new double*[NumarMagazine]; // Creem Harta si mapam distanele dintre Magazine
        for (unsigned int i = 0; i < NumarMagazine; ++i) {
            Harta[i] = new double[NumarMagazine]();
            for (unsigned int j = 0; j < NumarMagazine; ++j) {
                unsigned long long OBSTACOL = std::rand();
                // Incercam sa simulam mediul real: relieful nu este perfect si exista obstacole (i.e: statul la semafor, trafic)
                Harta[i][j] = Magazine[i].getLocatie().distanta(Magazine[j].getLocatie()) + (i != j ? OBSTACOL % DEVIATIE_RELIEF + OFFSET: 0); // i == j => Distanta = 0
            }
        }
    }

    unsigned int* CelMaiIndepartatMagazin() const { // Metoda Privata folosita pentru a determina Numarul de Ordine al celui mai Indepartat Magazin
        if (NumarMagazine < 2) { // Daca avem MAXIM 1 Magazin, nu exista un "cel mai indepartat magazin"
            return NULL;
        }

        double MAX_DIST = -1;
        unsigned int NR_ORD_MAG = 0;
        for (unsigned int i = 0; i < NumarMagazine; ++i) { // Determinam pozitia Magazinului
            if (ULTIMUL_VIZITAT != i && MAX_DIST < Distante[i]) {
                MAX_DIST = Distante[i];
                NR_ORD_MAG = i;
            }
        }

        unsigned int *MAG_ORD = new unsigned int[1];
        *MAG_ORD = NR_ORD_MAG;
        return MAG_ORD; // Returnam Pozitia
    }

    unsigned int* CelMaiApropiatMagazin() const { // Metoda Privata folosita pentru a determina Numarul de Ordine al celui mai Apropiat Magazin
        if (NumarMagazine < 2) { // Daca avem MAXIM 1 Magazin, nu exista un "cel mai apropiat magazin"
            return NULL;
        }

        double MIN_DIST = INF;
        unsigned int NR_ORD_MAG = 0;
        for (unsigned int i = 0; i < NumarMagazine; ++i) { // Determinam pozitia Magazinului
            if (ULTIMUL_VIZITAT != i && MIN_DIST > Distante[i]) {
                MIN_DIST = Distante[i];
                NR_ORD_MAG = i;
            }
        }

        unsigned int *MAG_ORD = new unsigned int[1];
        *MAG_ORD = NR_ORD_MAG;
        return MAG_ORD; // Returnam Pozitia
    }

    // Metoda Privata care determina drumul de distanta minima ditre Magazinul Initial si Magazinul Destinatie
    unsigned int* ReconstruiesteDrum(const unsigned int destinatie) const { 
        if (destinatie >= NumarMagazine) { // Tratam cazul in care Numarul de Oridne al Magazinului Destinatie este invalid             
            return NULL;
        }

        unsigned int numar_noduri = 1;
        unsigned int curent = destinatie;
        while (curent != ULTIMUL_VIZITAT) { // Determinam Numarul de Magazine prin care trebuie sa trecem
            numar_noduri++;
            curent = Parinte[curent];
        }

        unsigned int *drum = new unsigned int[numar_noduri + 1]; // Alocam memorie pentru a stoca Numerele de Ordine ale Magazinelor
        drum[0] = numar_noduri; // Pentru ca "drum" sa poata fi parcurs, pozitia 0 va contine valoarea cu Numarul de Magazine

        curent = destinatie;
        for (int i = numar_noduri; i >= 1; --i) { 
            drum[i] = curent;
            curent = Parinte[curent];
        }

        return drum; // Returnam Drumul
    }

    // Metoda Privata care determina Magazinele aflate in Raza specificata ca parametru
    unsigned int* MagazineRaza(unsigned int raza) const {
        if (NumarMagazine <= 1) { // Daca avem MAXIM 1 Magazin, nu exista alte magazine in proximitatea acestuia
            return NULL;
        }

        unsigned int counter = 0; // Determinam Numarul de Magazine aflate in Raza
        for (unsigned int i = 0; i < NumarMagazine; ++i) {
            if (i != ULTIMUL_VIZITAT && Distante[i] <= raza) {
                ++counter;
            }
        }

        unsigned int* magazine = new unsigned int[counter + 1]; // Alocam memorie pentru a stoca Numerele de Ordine ale acestora
        magazine[0] = counter; // Pentru ca "magazine" sa poata fi parcurs, pozitia 0 va contine valoarea cu Numarul de Magazine

        unsigned int index_curent = 1;
        for (unsigned int i = 0; i < NumarMagazine; ++i) {
            if (i != ULTIMUL_VIZITAT && Distante[i] <= raza) { // Determinam Magazinele care respecta conditia
                magazine[index_curent++] = i;
            }
        }

        return magazine; // Returnam Magazinele
    }

public:
    ReteaMagazine() : NumarMagazine(0), Magazine(NULL) {} // Constructor fara Parametrii
    ReteaMagazine(const unsigned int _nrMag, const Magazin *mag) : NumarMagazine(_nrMag) { // Constructor cu Parametrii
        if (NumarMagazine != 0) {
            Magazine = new Magazin[NumarMagazine]; // Alocam memorie dinamic
            for (unsigned int i = 0; i < NumarMagazine; i++) {
                Magazine[i] = mag[i];
            }
        }
        else {
            Magazine = NULL;
        }
    }
    ReteaMagazine(const ReteaMagazine &m) { // Consructor de Copiere
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
        // Nu se copiaza valorile de "Cache", nefiind necesare, deoarece acestea sunt folosite doar cand Utilizatorul apeleaza Metoda "distributie"
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

        // Nu se copiaza valorile de "Cache", nefiind necesare, deoarece acestea sunt folosite doar cand Utilizatorul apeleaza Metoda "distributie"
    }

    // Metoda Publica, ce poate returna diverse lucruri prin optiunile sale (descrise mai jos)
    // Se foloseste Algoritmul lui Dijkstra pentru determinarea unor proprietati dintre Magazinele din Retea
    // Metoda poate fi apelata fie cu 2, respectiv 3 parametrii (numarul fiind determinat de optiunea aleasa)
    unsigned int* distributie(unsigned int NumarOrdineMagazin, const unsigned int optiune = 1, const long long X = -1) {
        if (NumarOrdineMagazin >= NumarMagazine || NumarMagazine == 0) // Tratam cazul in care Numarul de Ordine al Magazinului primit ca parametru e invalid
            return NULL;                                               // sau NU exista Magazine in Retea

        if (ULTIMUL_VIZITAT != NumarOrdineMagazin || MODIFICAT == 1) { // Se evita calcularea redundanta a Alg. lui Dijkstra, tinand minte Ultimul Magazin Accesat
            MODIFICAT = 0;
            ULTIMUL_VIZITAT = NumarOrdineMagazin;

            initializare(NumarOrdineMagazin); // Initializam Harta
            animatie_consola();               // Apelam Metoda Privata pentru a simula incarcarea Metodei "distributie"

            for (unsigned int i = 0; i < NumarMagazine; i++) {
                long long MAGAZIN_CURENT = -1;
                double DISTANT_CURENTA = INF;

                for (unsigned int j = 0; j < NumarMagazine; j++) // Determinam Magazinul cu Distanta cea mai mica
                    if (!Vizitat[j] && DISTANT_CURENTA > Distante[j]) {
                        MAGAZIN_CURENT = j;
                        DISTANT_CURENTA = Distante[j];
                    }

                if (MAGAZIN_CURENT == -1) break;

                Vizitat[MAGAZIN_CURENT] = 1; // Vzitam Magazinul cu proprietatea mentionata in comentariul anterior
                for (unsigned int j = 0; j < NumarMagazine; j++)
                    if (!Vizitat[j] && Harta[MAGAZIN_CURENT][j] + Distante[MAGAZIN_CURENT] < Distante[j]) { // Actualizam Distantele
                        Distante[j] = Harta[MAGAZIN_CURENT][j] + Distante[MAGAZIN_CURENT];
                        Parinte[j] = MAGAZIN_CURENT;
                    }
            }
        }

        // Descrierea Metodelor a fost facuta mai sus
        switch (optiune) {
            case 1:
                return (X != -1 ? ReconstruiesteDrum(X) : NULL);     // Mod de apelare (exemplu): VAR.distributie(3, 1, 4)
            case 2:
                return (X != -1 ? MagazineRaza(X) : NULL);           // Mod de apelare (exemplu): VAR.distributie(9, 2, 150)
            case 3:
                return (X == -1 ? CelMaiIndepartatMagazin() : NULL); // Mod de apelare (exemplu): VAR.distribute(5, 3)
            case 4:
                return (X == -1 ? CelMaiApropiatMagazin() : NULL);   // Mod de apelare (exemplu): VAR.distributie(1, 4)
            default:
                return NULL;
        }
    }

    void stergeMagazin(unsigned int pozitie) { // Sterge Magazinul de la Pozitia X
        if (NumarMagazine == 0) return; // Tratam cazul in care nu exista Magazine

        if (Harta != NULL) { // Deoarece se Modifica Reteaua, Harta, impreuna cu celelalte date aflate in legatura, se sterg
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

        if (NumarMagazine == 1) { // Daca exista un singur Magazin, dezalocam Magazine
            delete[] Magazine;
            Magazine = NULL;
            NumarMagazine = 0;
            MODIFICAT = 1;
            return;
        }

        if (pozitie >= NumarMagazine) { // Daca pozitie >> NumarMagazine, se sterge Ultimul Magazin
            pozitie = NumarMagazine - 1;
        }

        Magazin *auxMagazine = new Magazin[NumarMagazine - 1]; // Alocam memorie pentru noul Array
        for (unsigned int i = 0; i < pozitie; ++i) {
            auxMagazine[i] = Magazine[i];
        }
        for (unsigned int i = pozitie + 1; i < NumarMagazine; ++i) {
            auxMagazine[i - 1] = Magazine[i];
        }

        --NumarMagazine;        // Decrementam NumarMagazine cu 1
        delete[] Magazine;      // Dezalocam Magazine
        Magazine = auxMagazine; // Magazine devine auxMagazine
        MODIFICAT = 1;          // Marcam ca Harta s-a Modificat
    }

    void insereazaMagazin(unsigned int pozitie, const Magazin &m) { // Insereaza Magazinul la Pozitia X
        if (pozitie > NumarMagazine) { // Daca Pozitie >> NumarMagazine, se insereaza la capatul Array-ului
            pozitie = NumarMagazine;
        }

        if (Harta != NULL) { // Harta se modifica, deci se sterge Harta veche, impreuna cu variabilele legate de aceasta
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

        if (NumarMagazine == 0) { // Daca nu exista Magazine in Retea, creem un nou Array cu un singur element
            NumarMagazine = 1;
            Magazine = new Magazin[1];
            *Magazine = m;
            MODIFICAT = 1;
            return;
        }

        Magazin *auxMagazine = new Magazin[NumarMagazine + 1]; // Creem un nou Array
        for (unsigned int i = 0; i < pozitie; ++i) {
            auxMagazine[i] = Magazine[i]; // Copiem Datele
        }
        auxMagazine[pozitie] = m; // Facem inserarea propiu-zisa
        for (unsigned int i = pozitie; i < NumarMagazine; ++i) {
            auxMagazine[i + 1] = Magazine[i];
        }

        ++NumarMagazine;        // Incrementam NumarMagazine cu 1
        delete[] Magazine;      // Dezalocam Magazine
        Magazine = auxMagazine; // Magazine devine auxMagazine
        MODIFICAT = 1;          // Marcam ca Harta s-a modificat
    }

    // GETTERI
    unsigned int getNumarMagazine() const { return NumarMagazine; } // Getter pentru NumarMagazine
    const Magazin* getMagazine() const { return Magazine; }         // Getter pentru Magazine
    Magazin getMagazinX(unsigned int X) const { return (X >= NumarMagazine ? Magazin() : Magazine[X]); } // Getter pentru Magazinul de la Pozitia X

    // SETTERI
    void setMagazine(const unsigned int _nrMag, const Magazin *magazine) { // Setter pentru NumarMagazine si Magazine
        if (Harta != NULL) {
            for (unsigned int i = 0; i < NumarMagazine; i++) {
                delete[] Harta[i];
            }
        }
        delete[] Harta; Harta = NULL; // Stergem Harta si celelate date legate de aceasta
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
        MODIFICAT = 1; // Marcam ca Harta s-a modificat
    }
    void setMagazinX(const Magazin &m, unsigned int X) { // Setter pentru Magazinul de la Pozitia X
        if (X >= NumarMagazine) { 
            return;
        }
        
        if (Harta != NULL) {
            for (unsigned int i = 0; i < NumarMagazine; i++) {
                delete[] Harta[i];
            }
        }
        delete[] Harta; Harta = NULL; // Stergem Harta si celelate date legate de aceasta (deoarece noul Magazin poate avea alta Locatie)
        delete[] Distante; Distante = NULL;
        delete[] Vizitat; Vizitat = NULL;
        delete[] Parinte;
        
        Magazine[X] = m; // Actualizam Magazinul de la Pozitia X
        MODIFICAT = 1;   // Marcam ca Harta s-a modificat
    }

    ~ReteaMagazine() { // Destructor (dezalocam memoria alocata dinamic)
        delete[] Magazine;
        if (Harta != NULL) { // Fiind un Arrary de Pointeri, se dezaloca fiecare Pointer si abia dupa stergem Harta
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
