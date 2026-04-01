#include <iostream>
#include "Produs.h"
#include "Punct2D.h"
#include "Angajat.h"
#include "Magazin.h"
#include "ReteaMagazine.h"

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
    Angajat sef1("Popescu", "Ion", 5050814401233, "0712345678", "Manager General");
    Angajat echipa1[] = {
        Angajat("Ionescu", "Maria", 2901225224566, "0722334455", "Casier"),
        Angajat("Vasile", "Andrei", 5050814401233, "0799887766", "Lucrator Comercial")
    };

    Angajat sef2("Marin", "George", 5050814401233, "0744556677", "Director Vanzari");
    Angajat sef3("Dumitru", "Elena", 2901225224566, "0733112233", "Sef Magazin");

    Angajat echipa3[] = {
        Angajat("Stan", "Mihai", 5050814401233, "0766112233", "Asistent Vanzari")
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

    Angajat sefNou("Mihailescu", "Gelu", 5050814401233, "0788998899", "Boss Suprem");
    Angajat paznic("Tudor", "Cristi", 5050814401233, "0711112222", "Agent Securitate");

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
    Angajat sefPatiserie("Zaharia", "Ioana", 2901225224566ULL, "0777888999", "Patiser Sef");

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

    return 0;
}
