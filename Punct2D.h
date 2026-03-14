#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>

class Punct2D { // Un obiect de tip "Punct2D" are 2 date membre: coordonata X si coordonata Y.
    unsigned int X, Y;

public:
    Punct2D() : X(0), Y(0) {}; // Constructor fara parametrii 
    Punct2D(const unsigned int x, const unsigned int y) : X(x), Y(y) {}; // Constructor cu 2 parametrii
    Punct2D(const Punct2D &p) { X = p.X; Y = p.Y; }; // Constructor de copiere

    unsigned int getX() const { return this->X; } // GETTERI
    unsigned int getY() const { return this->Y; }

    void setX(const unsigned int x) { this->X = x; }; // SETTERI
    void setY(const unsigned int y) { this->Y = y; };

    double distanta(const Punct2D &p) const { // Metoda care returneaza distanta dintre 2 obiecte de tip "Punct2D"
        const long long x = (long long)this->X - (long long)p.X;
        const long long y = (long long)this->Y - (long long)p.Y;
        return std::sqrt(x * x + y * y);
    }

    friend std::ostream& operator<<(std::ostream &out, const Punct2D &p) { // Afisare specifica obiectelor clasei "Punct2D"
        out << std::setprecision(2) << std::fixed << "(" << p.X << ", " << p.Y << ")";
        return out;
    }

    ~Punct2D() {}; // Destructor
};
