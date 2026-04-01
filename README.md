# Sistem de Gestiune a unei Retele de Magazine (Proiect POO)

Acest proiect este un sistem orientat pe obiecte (C++) pentru gestionarea unei retele de magazine. Abordarea este una tehnica, bazata pe managementul manual al memoriei. Nu s-au folosit containere standard (STL) precum `std::string` sau `std::vector`, preferandu-se alocarea dinamica si operatiile pe pointeri.

---

## Arhitectura Claselor

Proiectul contine 5 clase principale, structurate ierarhic:

### 1. Clasa `Punct2D`
Gestioneaza coordonatele spatiale (X, Y) pe o harta carteziana.
- **Metode principale:** `Punct2D()`, `Punct2D(x, y)`, `Punct2D(const Punct2D&)`, getteri, setteri, `distanta()`, `operator<<`.
- **Functionalitate:** Stocheaza coordonatele si calculeaza distanta euclidiana dintre doua puncte, aplicand cast-uri pentru a preveni erorile de tip underflow.

### 2. Clasa `Produs`
Modeleaza un produs cu Nume (alocat dinamic) si Pret.
- **Metode principale:** Constructori, Destructor, `operator=`, getteri, setteri, `operator<<`.
- **Functionalitate:** Gestioneaza in siguranta memoria pentru sirurile de caractere si previne afisarea pointerilor nuli.

### 3. Clasa `Angajat`
Stocheaza datele personalului (Nume, Prenume, NumarTelefon, Functie - alocate dinamic) si CNP.
- **Metode principale:** Constructori, Destructor, `operator=`, getteri, setteri, `validNrTel()`, `validCNP()`, `operator<<`.
- **Functionalitate:** Implementeaza validari stricte. Metoda `validCNP` verifica formatul standard al unui CNP romanesc (an, luna, zi, judet, cifra de control), iar `validNrTel` asigura formatul de 10 cifre.

### 4. Clasa `Magazin`
Reprezinta un nod din retea. Contine un array dinamic de `Produs`, un `Angajat` static (Seful) si un array dinamic de `Angajat` (Echipa).
- **Metode principale:** Constructori, Destructor, `operator=`, getteri, setteri, `insereazaProdus()`, `stergeProdus()`, `insereazaAngajat()`, `stergeAngajat()`, `operator<<`.
- **Functionalitate:** Foloseste compozitia pentru a reuni clasele anterioare. Metodele de inserare/stergere redimensioneaza dinamic array-urile si muta elementele la indexul specificat.

### 5. Clasa `ReteaMagazine`
Gestioneaza un array de magazine si relatiile logistice dintre ele pe baza distantelor.
- **Metode principale:** Constructori, Destructor, `operator=`, `initializare()`, `animatie_consola()`, `CelMaiIndepartatMagazin()`, `CelMaiApropiatMagazin()`, `ReconstruiesteDrum()`, `MagazineRaza()`, `distributie()`, `insereazaMagazin()`, `stergeMagazin()`.
- **Functionalitate:** Creeaza o matrice de adiacenta (graf neorientat complet) pe baza distantelor fizice si a unor obstacole generate aleatoriu. Evita recalcularea grafului printr-un sistem intern de validare a starii (caching).

**Detalii despre metoda `distributie`:**
Aceasta metoda aplica algoritmul lui Dijkstra pe graful retelei pentru a gasi rutele minime de la un magazin sursa spre restul retelei. Are 4 optiuni de output:
- **Optiunea 1:** Returneaza traseul complet (secventa de magazine) de la sursa catre un magazin destinatie specificat (pe pozitia 0 se pastreaza numarul magazinelor).
- **Optiunea 2:** Returneaza toate magazinele care se afla intr-o raza maxima de distanta data (pe pozitia 0 se pastreaza numarul magazinelor).
- **Optiunea 3:** Returneaza indexul celui mai indepartat magazin fata de sursa.
- **Optiunea 4:** Returneaza indexul celui mai apropiat magazin fata de sursa.

---

## Managementul Memoriei

Fiecare clasa care contine pointeri implementeaza **Regula celor 3** pentru a preveni memory leaks si double frees:
1. **Destructor (`~NumeClasa`)**: Elibereaza toata memoria alocata cu `new` sau `new[]`.
2. **Constructor de Copiere**: Realizeaza un *deep copy* al datelor pentru a evita partajarea acelorasi adrese de memorie intre obiecte diferite.
3. **Operatorul de atribuire (`operator=`)**: Curata memoria curenta a obiectului inainte de a aloca si copia continutul obiectului primit, continand si verificari impotriva auto-atribuirii (`if (this == &obj)`).
