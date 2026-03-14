# 🛒 Sistem Gestiune Rețea de Magazine (Proiect POO)

Acest proiect a fost dezvoltat în C++ pentru cursul/laboratorul de **Programare Orientată pe Obiecte (POO)**. Aplicația simulează o rețea complexă de magazine, gestionând stocuri de produse, locații pe o hartă 2D și calculând distanțe și rute optime folosind algoritmi pe grafuri.

## 🚀 Funcționalități principale

* **Gestiunea Memoriei Dinamice:** Implementare completă a „Regulii celor 3” (Rule of Three) - constructori de copiere, destructori și supraîncărcarea operatorului `=` pentru pointeri (`char*`, array-uri dinamice).
* **Ierarhie de Clase Modulară:** Codul este împărțit curat folosind abordarea *header-only*.
* **Algoritm de Distribuție (Pathfinding):** Folosește un algoritm similar cu **Dijkstra** pe o hartă generată dinamic (cu obstacole și variații de relief) pentru a determina:
  * Traseul optim (cel mai scurt drum) către un anumit magazin.
  * Toate magazinele aflate într-o anumită rază de acțiune.
  * Cel mai apropiat și cel mai îndepărtat magazin din rețea.
* **Interfață de Consolă:** Suprapunerea operatorului `<<` pentru afișarea formatată a produselor, stocurilor și datelor magazinelor, inclusiv o animație de încărcare (folosind `<thread>` și `<chrono>`).

## 📁 Structura Proiectului

Proiectul este modularizat în următoarele fișiere:

* `Punct2D.h` - Gestionează coordonatele spațiale (X, Y) și calculează distanța euclidiană.
* `Produs.h` - Definește un produs cu nume (alocat dinamic) și preț.
* `Magazin.h` - Gestionează datele unui magazin (Nume, Slogan, Forma Juridică) și array-ul dinamic de produse (stocul).
* `ReteaMagazine.h` - Clasa "Core". Generează harta (matricea de adiacență), stochează vectorul de magazine și rulează algoritmii de calcul al drumurilor.
* `main.cpp` - Punctul de intrare în program, unde sunt populate datele de test și sunt apelați algoritmii.

## 🛠️ Tehnologii folosite
* **Limbaj:** C++ standard (C++11 sau mai nou)
* **Biblioteci standard:** `<iostream>`, `<iomanip>`, `<cstring>`, `<thread>`, `<chrono>`, `<cmath>`, `<cstdlib>`, `<ctime>`

## 💻 Cum se compilează și rulează

Dacă folosești **Linux** sau un terminal cu g++ instalat (ex: WSL, MinGW pe Windows), rulează următoarele comenzi în folderul proiectului:

```bash
# Compilarea proiectului
g++ main.cpp -o gestiune_magazine

# Rularea executabilului
./gestiune_magazine
