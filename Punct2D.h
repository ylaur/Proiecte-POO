#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>

class Punct2D { // Clasa Punct2D
    unsigned int X, Y; // 2 Date Membre

public:
    Punct2D() : X(0), Y(0) {}; // Constructor fara parametrii
    Punct2D(const unsigned int x, const unsigned int y) : X(x), Y(y) {}; // Constructor cu 2 Parametrii
    Punct2D(const Punct2D &p) { X = p.X; Y = p.Y; }; // Constructor de Copiere

    // GETTERI
    unsigned int getX() const { return this->X; } // Getter pentru X
    unsigned int getY() const { return this->Y; } // Getter pentru Y

    // SETTERI
    void setX(const unsigned int x) { this->X = x; }; // Setter pentru X
    void setY(const unsigned int y) { this->Y = y; }; // Setter pentru Y

    double distanta(const Punct2D &p) const {                    // Metoda ce calculeaza distanta dintre 2 Obiecte de tip Punct2D 
        const long long x = (long long)this->X - (long long)p.X; // Exemplu apelare: locatie1.distanta(locatie2)
        const long long y = (long long)this->Y - (long long)p.Y;
        return std::sqrt(x * x + y * y);
    }

    friend std::ostream& operator<<(std::ostream &out, const Punct2D &p) { // Operator Overloading pentru afisare (<<)
        out << std::setprecision(2) << std::fixed << "(" << p.X << ", " << p.Y << ")";
        return out;
    }

    ~Punct2D() {}; // Destructor
};
