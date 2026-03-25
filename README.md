# Sistem Gestiune Rețea de Magazine (Proiect POO)

Acest proiect a fost dezvoltat în C++ pentru cursul/laboratorul de **Programare Orientată pe Obiecte (POO)**. Aplicația simulează o rețea complexă de magazine, gestionând stocuri de produse, locații pe o hartă 2D și calculând distanțe și rute optime folosind algoritmi pe grafuri.

## Funcționalități principale

* **Gestiunea Memoriei Dinamice:** Implementare completă a „Regulii celor 3” (Rule of Three) - constructori de copiere, destructori și supraîncărcarea operatorului `=` pentru pointeri (`char*`, array-uri dinamice).
* **Ierarhie de Clase Modulară:** Codul este împărțit curat folosind abordarea *header-only*.
* **Algoritm de Distribuție (Pathfinding):** Folosește un algoritm similar cu **Dijkstra** pe o hartă generată dinamic (cu obstacole și variații de relief) pentru a determina:
  * Traseul optim (cel mai scurt drum) către un anumit magazin.
  * Toate magazinele aflate într-o anumită rază de acțiune.
  * Cel mai apropiat și cel mai îndepărtat magazin din rețea.

## Structura Proiectului

Proiectul este modularizat în următoarele fișiere:

* `Punct2D.h` - Gestionează coordonatele spațiale (X, Y) și calculează distanța euclidiană.
* `Produs.h` - Definește un produs cu nume (alocat dinamic) și preț.
* `Magazin.h` - Gestionează datele unui magazin (Nume, Slogan, Forma Juridică) și array-ul dinamic de produse (stocul).
* `ReteaMagazine.h` - Clasa "Core". Generează harta (matricea de adiacență), stochează vectorul de magazine și rulează algoritmii de calcul al drumurilor.
* `main.cpp` - Punctul de intrare în program, unde sunt populate datele de test și sunt apelați algoritmii.
