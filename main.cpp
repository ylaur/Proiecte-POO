#include <iostream>
#include "Punct2D.h"
#include "Produs.h"
#include "Magazin.h"
#include "ReteaMagazine.h"

int main() {
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

    Magazin m1("Alimentara Central", "Proaspat in fiecare zi", "SRL", 3, alimente, Punct2D(10, 10));
    Magazin m2("Electro IT", "Tehnologia viitorului", "SA", 2, electronice, Punct2D(15, 20));
    Magazin m3("Fashion Hub", "Stilul te defineste", "SRL", 4, haine, Punct2D(100, 100));
    Magazin m4("Brico Universal", "Construim impreuna", "SA", 2, constructii, Punct2D(150, 30));
    Magazin m5("Fructe la Colt", "Vitamine pentru tine", "PFA", 3, fructe, Punct2D(5, 90));

    Magazin arrayMagazine[] = {m1, m2, m3, m4, m5};
    ReteaMagazine reteauaMea(5, arrayMagazine);

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

    return 0;
}
