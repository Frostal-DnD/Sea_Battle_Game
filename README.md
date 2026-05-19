Sea Battle

Un joc de Bătălie Navală bazat pe consolă, scris în C++ pentru Windows. Jucătorul se confruntă cu un adversar controlat de calculator (AI), care folosește o strategie inteligentă de vânătoare și distrugere a navelor.

---
Funcționalități
1. Plasarea manuală a navelor — tu decizi unde îți poziționezi flota înainte de start
2. Interfață colorată în consolă — navele, loviturile și ratările sunt afișate în culori diferite prin Windows Console API
3. Afișaj dual — flota ta și grila inamicului sunt afișate simultan, una lângă alta
4. Adversar AI inteligent — logică de atac în trei faze (aleator → căutare → distrugere)
5. Actualizare în timp real — ultima mutare și rezultatul (lovit / scufundat / ratat) sunt afișate pentru ambii jucători
---
Cerințe
1. Sistem de operare: Windows (utilizează `<Windows.h>` și `<conio.h>`)
2. Compilator: MSVC (Visual Studio 2019/2022 recomandat) sau MinGW cu headere Windows
2. Standard: C++11 sau mai nou
> Proiectul a fost dezvoltat și testat cu Visual Studio — fișierele `.vcxproj` incluse sunt gata de deschis și compilat.
---
Cum să începi

1. Cu Visual Studio
Clonează repository-ul:
```
   git clone https://github.com/username-tau/Sea\_Battle\_Game.git
   ```
Deschide `Sea_Battle_Game.vcxproj` în Visual Studio.
Setează configurația la `x64 / Debug` sau `x64 / Release`.
Apasă F5 pentru a compila și rula.

2. Cu executabilul pre-compilat
Un executabil compilat se găsește la `x64/Debug/Sea_Battle_Game.exe`. Poate fi rulat direct din linia de comandă sau prin dublu-click.

3. Cu shortcut prestabilit
Un executabil compilat se găsește la mapa de bază `Sea_Battle_Game.lnk`. Poate fi rulat prin dublu-click.

---
Cum se joacă 
Video

<video width="700" controls>
  <source src="gameplay.mp4" type="video/mp4">
</video>

Plasarea navelor
La pornire ești rugat să plasezi 10 nave una câte una. Introdu fiecare navă în formatul:
```
<rând> <coloană> <lungime> <orientare>
```

|   Parametru   |   Valori   |   Exemplu   |
|---------------|------------|-------------|
|      Rând     |	  numere   |   `10` `3`  |
|---------------|------------|-------------|
|   Coloană     |  caractere |   `J` `E`   |
|---------------|------------|-------------|
|   Lungime     |   numere   |   `4` `3`   |
|---------------|------------|-------------|
|   Orientare	 |  caracter  |   `v` `o`   |



###Exemplu de introducere:
```
3 E 3 v
```
- Plasează o navă de 3 celule vertical, începând din rândul 3, coloana E.
Harta este afișată după fiecare plasare. Navele nu pot fi suprapuse și nici plasate adiacent una față de cealaltă.
Atacul
- La fiecare tur vei fi întrebat:
```
Unde doriti sa atacati ?
```
- Introdu coordonatele în același format `rând coloană`:
```
5 G
```
- După mutarea ta, AI-ul atacă automat. Afișajul se actualizează arătând ambele hărți cu rezultatele la zi.
Semnificația simbolurilor


|Simbol |	Culoare   |	  Semnificație   |
|-------|-----------|------------------|
|  `*`  |  Verde    | Nava ta (intactă)|
|-------|-----------|------------------|
|  `h`  |  Galben   |      Lovit       |
|-------|-----------|------------------|
|  `k`  |  Roșu     |     Scufundat    |
|-------|-----------|------------------|
|  `-`  |  Default  |      Ratat       |
|-------|-----------|------------------|

---
- Componența flotei
Ambii jucători folosesc aceeași flotă standard (10 nave în total):


| Lungimea navei	|   Cantitate      |
|-----------------|------------------|
| 4 celule	      |      1           |
|-----------------|------------------|
| 3 celule        |      2           |
|-----------------|------------------|
| 2 celule	      |      3           |
|-----------------|------------------|
| 1 celulă	      |      4           |
|-----------------|------------------|

Flota AI-ului este plasată aleatoriu la începutul fiecărei partide.
---
Comportamentul AI

AI-ul folosește o strategie în trei faze:

1. Modul aleator — alege coordonate aleatorii până când nimerește o navă.
2. Modul de căutare — după o lovitură, verifică cei patru vecini cardinali ai celulei lovite pentru a determina orientarea navei.
3. Modul de distrugere — odată ce orientarea este determinată, trage de-a lungul axei (înainte/înapoi) până când nava este scufundată, apoi revine la modul aleator.
4. Dacă AI-ul rămâne fără mutări valide în modul de căutare sau distrugere, revine automat la modul aleator.
---
Observații
1. Interfața jocului este în română (mesaje, erori, prompturi).
2. Necesită o consolă Windows cu suport pentru culori (standard `cmd.exe` sau Windows Terminal).
---
Licență
Acest proiect este distribuit în scop educațional. Ești liber să îl forkuiești și să îl îmbunătățești.
