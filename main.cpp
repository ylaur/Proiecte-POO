#include <iostream>
#include "Punct2D.h"
#include "Produs.h"
#include "Magazin.h"
#include "ReteaMagazine.h"

int main() {
	Produs alimente[] = { // Cateva exemple care folosesc Clasele si Metodele aferente lor
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

	// Initializare Magazine
    Magazin m1("Alimentara Central", "Proaspat in fiecare zi", "SRL", 3, alimente, Punct2D(10, 10));
    Magazin m2("Electro IT", "Tehnologia viitorului", "SA", 2, electronice, Punct2D(15, 20));
    Magazin m3("Fashion Hub", "Stilul te defineste", "SRL", 4, haine, Punct2D(100, 100));
    Magazin m4("Brico Universal", "Construim impreuna", "SA", 2, constructii, Punct2D(150, 30));
    Magazin m5("Fructe la Colt", "Vitamine pentru tine", "PFA", 3, fructe, Punct2D(5, 90));

    Magazin arrayMagazine[] = {m1, m2, m3, m4, m5};
    ReteaMagazine reteauaMea(5, arrayMagazine);

	// Apelare Metode
    unsigned int* res3 = reteauaMea.distributie(1, 3);
    if (res3 != NULL) {
        std::cout << "Cel mai indepartat: " << reteauaMea.getMagazine()[res3[0]].getNume() << "\n\n";
        delete[] res3;
    }

    unsigned int* res4 = reteauaMea.distributie(1, 4);
    if (res4 != NULL) {
        std::cout << "Cel mai apropiat: " << reteauaMea.getMagazine()[res4[0]].getNume() << "\n\n";
        delete[] res4;
    }

    unsigned int* res2 = reteauaMea.distributie(1, 2, 150);
    if (res2 != NULL) {
        std::cout << "Magazine in raza de 150:\n";
        for (unsigned int i = 1; i <= res2[0]; ++i) {
            std::cout << "- " << reteauaMea.getMagazine()[res2[i]].getNume() << "\n";
        }
        std::cout << "\n";
        delete[] res2;
    }

    unsigned int* res1 = reteauaMea.distributie(1, 1, 3);
    if (res1 != NULL) {
        std::cout << "Traseu catre Brico Universal:\n";
        for (unsigned int i = 1; i <= res1[0]; ++i) {
            std::cout << reteauaMea.getMagazine()[res1[i]].getNume() << (i < res1[0] ? " -> " : "");
        }
        std::cout << "\n";
        delete[] res1;
    }

    // Apelare Metode Distributie (Algoritmul original)
    std::cout << "========= 1. ALGORITMI DE DISTRIBUTIE =========\n";

    res3 = reteauaMea.distributie(1, 3);
    if (res3 != NULL) {
        std::cout << "Cel mai indepartat: " << reteauaMea.getMagazine()[res3[0]].getNume() << "\n";
        delete[] res3;
    }

    res4 = reteauaMea.distributie(1, 4);
    if (res4 != NULL) {
        std::cout << "Cel mai apropiat: " << reteauaMea.getMagazine()[res4[0]].getNume() << "\n";
        delete[] res4;
    }

    res2 = reteauaMea.distributie(1, 2, 150);
    if (res2 != NULL) {
        std::cout << "Magazine in raza de 150:\n";
        for (unsigned int i = 1; i <= res2[0]; ++i) {
            std::cout << "- " << reteauaMea.getMagazine()[res2[i]].getNume() << "\n";
        }
        delete[] res2;
    }

    res1 = reteauaMea.distributie(1, 1, 3);
    if (res1 != NULL) {
        std::cout << "Traseu catre Brico Universal:\n";
        for (unsigned int i = 1; i <= res1[0]; ++i) {
            std::cout << reteauaMea.getMagazine()[res1[i]].getNume() << (i < res1[0] ? " -> " : "");
        }
        std::cout << "\n\n";
        delete[] res1;
    }

    // Testare functionala a claselor (Adaugat Nou)
    std::cout << "========= 2. TESTARE METODE CLASE =========\n";

    // Calculare distanta directa (Testare Punct2D)
    std::cout << "\n[ Testare distanta Punct2D ]\n";
    Punct2D loc1 = m1.getLocatie();
    Punct2D loc2 = m3.getLocatie();
    std::cout << "Distanta in linie dreapta intre " << m1.getNume() << " " << loc1
              << " si " << m3.getNume() << " " << loc2
              << " este: " << loc1.distanta(loc2) << "\n";

    // Manipulare Stoc (Testare insereaza/sterge Produs)
    std::cout << "\n[ Manipulare Stoc Magazin ]\n";
    std::cout << "Adaugam un produs nou in " << m5.getNume() << "...\n";
    Produs pNou("Kiwi", 9.5);
    m5.insereazaProdus(1, pNou); // Il inseram pe pozitia 1

    std::cout << "Stergem primul produs (pozitia 0)...\n";
    m5.stergeProdus(0); // Ar trebui sa stearga "Mere Ionatan"

    std::cout << "Noul inventar pentru magazinul 5:\n";
    std::cout << m5 << "\n"; // Aici testam operatorul << supraincarcat

    // Manipulare Retea (Testare insereaza/sterge Magazin)
    std::cout << "\n[ Manipulare Retea de Magazine ]\n";
    Produs patiserie[] = { Produs("Covrig", 2.0), Produs("Merdenea", 4.0) };
    Magazin m6("Patiseria de vis", "Cald si bun", "SRL", 2, patiserie, Punct2D(50, 50));

    std::cout << "Inseram un magazin nou la finalul retelei...\n";
    reteauaMea.insereazaMagazin(reteauaMea.getNumarMagazine(), m6);

    std::cout << "Stergem Electro IT (pozitia 1)...\n";
    reteauaMea.stergeMagazin(1);

    std::cout << "Lista actualizata a magazinelor din retea (" << reteauaMea.getNumarMagazine() << " magazine):\n";
    for(unsigned int i = 0; i < reteauaMea.getNumarMagazine(); ++i) {
        std::cout << i + 1 << ". " << reteauaMea.getMagazine()[i].getNume() << "\n";
    }

    // Test Deep Copy 
    std::cout << "\n[ Verificare Deep Copy (Regula celor 3) ]\n";
    Magazin clonaBrico = m4; // Apelam constructorul de copiere
    clonaBrico.setNume("Brico FALS");
    clonaBrico.getProduse()[0].setPret(999.99); // Modificam pretul unui produs in clona

    std::cout << "Pret ciment in original (" << m4.getNume() << "): " << m4.getProduse()[0].getPret() << " RON\n";
    std::cout << "Pret ciment in clona (" << clonaBrico.getNume() << "): " << clonaBrico.getProduse()[0].getPret() << " RON\n";
    std::cout << "(Daca preturile sunt diferite, copierea a fost facuta corect pe portiuni de memorie distincte!)\n\n";

    return 0;
}
