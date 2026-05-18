#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <string.h>
using namespace std;
char PlayerOne[12][12][3];
char PlayerTwo[12][12][3];
int IdNaveOne[12][12];
int IdNaveTwo[12][12];
int x, y, l, idShip = 1, idCount, idNow, win = 0, liveOne, liveTwo, idShipAI = 1, countlanave = 0, Target, Targetqueue, Ymin, Xmin, Ymax, Xmax, direction, aiX, aiY, LastStatusPlayer = 0, LastStatusAI = 0, lastxPl = 0, lastyPl = 0, lastxAI = 0, lastyAI = 0, killID;
int nave[4] = { 0 }, nave2[4] = { 0 };
char s, ychar, lastyAIchar = '-', lastyPlchar = '-';
int dirX[4] = { -1, 1, 0, 0 };
int dirY[4] = { 0, 0, -1, 1 };
// plasarea Navelor
void punemNavaPlayerOne() {
ErrorImput:
    if (!(cin >> x >> ychar >> l >> s)) {
        cout << "Input invalid.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        goto ErrorImput;
    }
    // regulile de plasare a flotei
    switch (ychar) {
    case 'A':
    case 'a':
        y = 1;
        break;
    case 'B':
    case 'b':
        y = 2;
        break;
    case 'C':
    case 'c':
        y = 3;
        break;
    case 'D':
    case 'd':
        y = 4;
        break;
    case 'E':
    case 'e':
        y = 5;
        break;
    case 'F':
    case 'f':
        y = 6;
        break;
    case 'G':
    case 'g':
        y = 7;
        break;
    case 'H':
    case 'h':
        y = 8;
        break;
    case 'I':
    case 'i':
        y = 9;
        break;
    case 'J':
    case 'j':
        y = 10;
        break;
    default:
        cout << "Nu puteti lovi acolo\n";
        goto ErrorImput;
    }
    if (x < 1 || x > 10) {
        cout << "X e introdus gresit.\n";
        goto ErrorImput;
    }
    if (l < 1 || l > 4) {
        cout << "lungimea navei e introdus gresit.\n";
        goto ErrorImput;
    }
    if (s != 'o' && s != 'v') {
        cout << "Starea navei e introdus gresit.\n";
        goto ErrorImput;
    }
    // Evidenta flotei
    if (l == 4 && nave[3] >= 1) {
        cout << "Limita navelor de aceasta lungine a fost atinsa\n";
        goto ErrorImput;
    }
    if (l == 3 && nave[2] >= 2) {
        cout << "Limita navelor de aceasta lungine a fost atinsa\n";
        goto ErrorImput;
    }
    if (l == 2 && nave[1] >= 3) {
        cout << "Limita navelor de aceasta lungine a fost atinsa\n";
        goto ErrorImput;
    }
    if (l == 1 && nave[0] >= 4) {
        cout << "Limita navelor de aceasta lungine a fost atinsa\n";
        goto ErrorImput;
    }
    if (s == 'v') {
        if (x + (l - 1) > 10) {
            cout << "Nava nu poate fi plasata aici.\n";
            goto ErrorImput;
        }
        if (PlayerOne[x][y][2] == '#') {
            cout << "Nava nu poate fi plasata aici.\n";
            goto ErrorImput;
        }
        if (PlayerOne[x + l - 1][y][2] == '#') {
            cout << "Nava nu poate fi plasata aici.\n";
            goto ErrorImput;
        }
        //plasarea navei
        for (int i = 0; i < l; i++) {
            PlayerOne[x + i][y][1] = '*';
        }
        for (int i = 0; i < l; i++) {
            IdNaveOne[x + i][y] = idShip;
        }
        idShip++;
        //actualizam "collision layer"
        for (int i = 0; i < (l + 2); i++) {
            PlayerOne[x - 1 + i][y - 1][2] = '#';
            PlayerOne[x - 1 + i][y][2] = '#';
            PlayerOne[x - 1 + i][y + 1][2] = '#';
        }
        // actualizam evidenta flotei
        if (l == 1) {
            nave[0]++;
        }
        if (l == 2) {
            nave[1]++;
        }
        if (l == 3) {
            nave[2]++;
        }
        if (l == 4) {
            nave[3]++;
        }
    }
    if (s == 'o') {
        if (y + (l - 1) > 10) {
            cout << "Nava nu poate fi plasata aici.\n";
            goto ErrorImput;
        }
        if (PlayerOne[x][y][2] == '#') {
            cout << "Nava nu poate fi plasata aici.\n";
            goto ErrorImput;
        }
        if (PlayerOne[x][y + l - 1][2] == '#') {
            cout << "Nava nu poate fi plasata aici.\n";
            goto ErrorImput;
        }
        //plasarea navei
        for (int i = 0; i < l; i++) {
            PlayerOne[x][y + i][1] = '*';
        }
        for (int i = 0; i < l; i++) {
            IdNaveOne[x][y + i] = idShip;
        }
        idShip++;
        //actualizam "collision layer"
        for (int i = 0; i < (l + 2); i++) {
            PlayerOne[x + 1][y - 1 + i][2] = '#';
            PlayerOne[x][y - 1 + i][2] = '#';
            PlayerOne[x - 1][y - 1 + i][2] = '#';
        }
        // actualizam evidenta flotei
        if (l == 1) {
            nave[0]++;
        }
        if (l == 2) {
            nave[1]++;
        }
        if (l == 3) {
            nave[2]++;
        }
        if (l == 4) {
            nave[3]++;
        }
    }
}
void punemNavaPlayerTwo() {
ErrorImput2:
    x = rand() % 10 + 1;
    y = rand() % 10 + 1;
    l = rand() % 4 + 1;
    s = (rand() % 2 == 0) ? 'v' : 'o';
    // Evidenta flotei
    if (l == 4 && nave2[3] >= 1) {
        goto ErrorImput2;
    }
    if (l == 3 && nave2[2] >= 2) {
        goto ErrorImput2;
    }
    if (l == 2 && nave2[1] >= 3) {
        goto ErrorImput2;
    }
    if (l == 1 && nave2[0] >= 4) {
        goto ErrorImput2;
    }
    if (s == 'v') {
        if (x + (l - 1) > 10) {
            goto ErrorImput2;
        }
        if (PlayerTwo[x][y][2] == '#') {
            goto ErrorImput2;
        }
        if (PlayerTwo[x + l - 1][y][2] == '#') {
            goto ErrorImput2;
        }
        //plasarea navei
        for (int i = 0; i < l; i++) {
            PlayerTwo[x + i][y][1] = '*';
        }
        for (int i = 0; i < l; i++) {
            IdNaveTwo[x + i][y] = idShipAI;
        }
        idShipAI++;
        countlanave++;
        //actualizam "collision layer"
        for (int i = 0; i < (l + 2); i++) {
            PlayerTwo[x - 1 + i][y - 1][2] = '#';
            PlayerTwo[x - 1 + i][y][2] = '#';
            PlayerTwo[x - 1 + i][y + 1][2] = '#';
        }
        // actualizam evidenta flotei
        if (l == 1) {
            nave2[0]++;
        }
        if (l == 2) {
            nave2[1]++;
        }
        if (l == 3) {
            nave2[2]++;
        }
        if (l == 4) {
            nave2[3]++;
        }
    }
    if (s == 'o') {
        if (y + (l - 1) > 10) {
            goto ErrorImput2;
        }
        if (PlayerTwo[x][y][2] == '#') {
            goto ErrorImput2;
        }
        if (PlayerTwo[x][y + l - 1][2] == '#') {
            goto ErrorImput2;
        }
        //plasarea navei
        for (int i = 0; i < l; i++) {
            PlayerTwo[x][y + i][1] = '*';
        }
        for (int i = 0; i < l; i++) {
            IdNaveTwo[x][y + i] = idShipAI;
        }
        idShipAI++;
        countlanave++;
        //actualizam "collision layer"
        for (int i = 0; i < (l + 2); i++) {
            PlayerTwo[x + 1][y - 1 + i][2] = '#';
            PlayerTwo[x][y - 1 + i][2] = '#';
            PlayerTwo[x - 1][y - 1 + i][2] = '#';
        }
        // actualizam evidenta flotei
        if (l == 1) {
            nave2[0]++;
        }
        if (l == 2) {
            nave2[1]++;
        }
        if (l == 3) {
            nave2[2]++;
        }
        if (l == 4) {
            nave2[3]++;
        }
    }
}
//Graphic Tools
void Col(int bg, int txt) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((bg << 4) | txt));
}
void setcur(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
}
void draw() {
    int setY = 0;
    int setX1 = 0;
    int setX2 = 40;
    // Header-ele
    setcur(setX1, setY);
    cout << "      FLOTA MEA";
    setcur(setX2, setY);
    cout << "      FLOTA AI";
    setY++;
    switch (lastyAI) {
    case 1:
        lastyAIchar = 'A';
        break;
    case 2:
        lastyAIchar = 'B';
        break;
    case 3:
        lastyAIchar = 'C';
        break;
    case 4:
        lastyAIchar = 'D';
        break;
    case 5:
        lastyAIchar = 'E';
        break;
    case 6:
        lastyAIchar = 'F';
        break;
    case 7:
        lastyAIchar = 'G';
        break;
    case 8:
        lastyAIchar = 'H';
        break;
    case 9:
        lastyAIchar = 'I';
        break;
    case 10:
        lastyAIchar = 'J';
        break;
    default:
        break;
    }
    switch (lastyPl) {
    case 1:
        lastyPlchar = 'A';
        break;
    case 2:
        lastyPlchar = 'B';
        break;
    case 3:
        lastyPlchar = 'C';
        break;
    case 4:
        lastyPlchar = 'D';
        break;
    case 5:
        lastyPlchar = 'E';
        break;
    case 6:
        lastyPlchar = 'F';
        break;
    case 7:
        lastyPlchar = 'G';
        break;
    case 8:
        lastyPlchar = 'H';
        break;
    case 9:
        lastyPlchar = 'I';
        break;
    case 10:
        lastyPlchar = 'J';
        break;
    default:
        break;
    }
    setcur(setX1, setY);
    cout << "AI last try:" << lastxAI << " " << lastyAIchar << endl;
    setcur(setX2, setY);
    cout << "My last try:" << lastxPl << " " << lastyPlchar << endl;
    setY++;
    setcur(setX1, setY);
    switch (LastStatusAI) {
    case 0:
        cout << "Status: ";
        break;
    case 1:
        cout << "Status: hit";
        break;
    case 2:
        cout << "Status: kill";
        break;
    case 3:
        cout << "Status: miss";
        break;
    }
    setcur(setX2, setY);
    switch (LastStatusPlayer) {
    case 0:
        cout << "Status: ";
        break;
    case 1:
        cout << "Status: hit";
        break;
    case 2:
        cout << "Status: kill";
        break;
    case 3:
        cout << "Status: miss";
        break;
    }
    setY++;
    // Numerele coloanelor
    setcur(setX1, setY);
    cout << "     A  B  C  D  E  F  G  H  I  J";
    setcur(setX2, setY);
    cout << "     A  B  C  D  E  F  G  H  I  J";
    setY++;
    // Randurile
    for (int i = 1; i < 11; i++) {
        //PlayerOne
        setcur(setX1, setY);
        cout << setw(3) << i << " ";
        for (int j = 1; j < 11; j++) {
            if (PlayerOne[i][j][1] == '*') {
                Col(7, 2);
                cout << " * ";
                Col(7, 1);
            }
            else if (PlayerOne[i][j][1] == 'h') {
                Col(7, 6);
                cout << " h ";
                Col(7, 1);
            }
            else if (PlayerOne[i][j][1] == 'k') {
                Col(7, 4);
                cout << " k ";
                Col(7, 1);
            }
            else {
                cout << " " << PlayerOne[i][j][1] << " ";
            }
        }
        //AI
        setcur(setX2, setY);
        cout << setw(3) << i << " ";
        for (int j = 1; j < 11; j++) {
            if (PlayerTwo[i][j][0] == 'h') {
                Col(7, 6);
                cout << " h ";
                Col(7, 1);
            }
            else if (PlayerTwo[i][j][0] == 'k') {
                Col(7, 4);
                cout << " k ";
                Col(7, 1);
            }
            else {
                cout << " " << PlayerTwo[i][j][0] << " ";
            }
        }
        setY++;
    }
    // Mutam cursorul sub ambele matrici
    setcur(0, setY + 1);
}
// verificam e hit sau kill
void verificareAI(int x, int y) {
    idNow = IdNaveOne[x][y];
    IdNaveOne[x][y] = IdNaveOne[x][y] * (-1);
    idCount = 0;
    for (int i = 1; i < 11; i++) {
        for (int j = 1; j < 11; j++) {
            if (IdNaveOne[i][j] == idNow) {
                idCount++;
            }
        }
    }
}
void verificarePlayer(int x, int y) {
    idNow = IdNaveTwo[x][y];
    IdNaveTwo[x][y] = IdNaveTwo[x][y] * (-1);
    idCount = 0;
    for (int i = 1; i < 11; i++) {
        for (int j = 1; j < 11; j++) {
            if (IdNaveTwo[i][j] == idNow) {
                idCount++;
            }
        }
    }
}
// Attack
void attackPlayerOne() {
RepeatAttack1:
    cout << "Unde doriti sa atacati ?\n";
    //cout << Xmax << " " << Xmin << " " << Ymax << " " << Ymin << " " << Target;
    if (!(cin >> x >> ychar)) {
        cout << "Input invalid.\n";
        cin.clear();              // scoate fail state
        cin.ignore(1000, '\n');   // sterge linia gresita
        goto RepeatAttack1;
    }
    if (x > 10 || x < 1) {
        cout << "Nu puteti pune acolo\n";
        goto RepeatAttack1;
    }
    switch (ychar) {
    case 'A':
    case 'a':
        y = 1;
        break;
    case 'B':
    case 'b':
        y = 2;
        break;
    case 'C':
    case 'c':
        y = 3;
        break;
    case 'D':
    case 'd':
        y = 4;
        break;
    case 'E':
    case 'e':
        y = 5;
        break;
    case 'F':
    case 'f':
        y = 6;
        break;
    case 'G':
    case 'g':
        y = 7;
        break;
    case 'H':
    case 'h':
        y = 8;
        break;
    case 'I':
    case 'i':
        y = 9;
        break;
    case 'J':
    case 'j':
        y = 10;
        break;
    default:
        cout << "Nu puteti lovi acolo\n";
        goto RepeatAttack1;
    }
    if (PlayerTwo[x][y][0] != '.') {
        cout << "Ati impuscat deja acolo anterior\n";
        goto RepeatAttack1;
    }
    if (PlayerTwo[x][y][1] == '*') {
        // verificam e hit sau kill
        verificarePlayer(x, y);
        if (idCount > 0) {
            PlayerTwo[x][y][0] = 'h';
            lastxPl = x;
            lastyPl = y;
            LastStatusPlayer = 1;
            --liveTwo;
        }
        else if (idCount <= 0) {
            PlayerTwo[x][y][0] = 'k';
            lastxPl = x;
            lastyPl = y;
            LastStatusPlayer = 2;
            --liveTwo;


            killID = IdNaveTwo[aiX][aiY];
            for (int i = 1; i < 11; i++) {
                for (int j = 1; j < 11; j++) {
                    if (IdNaveTwo[i][j] == killID) {
                        for (int a = 0; a < 3; a++) {
                            for (int b = 0; b < 3; b++) {
                                if (PlayerTwo[i + a - 1][j + b - 1][1] == '.') {
                                    PlayerTwo[i + a - 1][j + b - 1][1] = '-';
                                }
                                if (PlayerTwo[i + a][j + b][1] == 'h') {
                                    PlayerTwo[i + a][j + b][1] = 'k';
                                }
                            }
                        }
                    }
                }
            }

        }
    }
    else if (PlayerTwo[x][y][1] == '.') {
        PlayerTwo[x][y][0] = '-';
        lastxPl = x;
        lastyPl = y;
        LastStatusPlayer = 3;
    }
}
void attackAI() {
    // destroy mode
    if (Target == 2) {
        if (Xmax == Xmin) {
            aiX = Xmax;
            aiY = (direction == 0) ? Ymax + 1 : Ymin - 1;
        }
        else {
            aiX = (direction == 0) ? Xmax + 1 : Xmin - 1;
            aiY = Ymax;
        }
        if (aiX < 1 || aiX > 10 || aiY < 1 || aiY > 10 ||
            PlayerOne[aiX][aiY][1] == 'h' ||
            PlayerOne[aiX][aiY][1] == 'k' ||
            PlayerOne[aiX][aiY][1] == '-') {
            direction = 1 - direction;
            if (Xmax == Xmin) {
                aiX = Xmax;
                aiY = (direction == 0) ? Ymax + 1 : Ymin - 1;
            }
            else {
                aiX = (direction == 0) ? Xmax + 1 : Xmin - 1;
                aiY = Ymax;
            }
        }
        if (aiX < 1 || aiX > 10 || aiY < 1 || aiY > 10 ||
            PlayerOne[aiX][aiY][1] == 'h' ||
            PlayerOne[aiX][aiY][1] == 'k' ||
            PlayerOne[aiX][aiY][1] == '-') {
            Target = 0;
            Targetqueue = 0;
            direction = 0;
            goto RandomMode;
        }
        if (PlayerOne[aiX][aiY][1] == '*') {
            verificareAI(aiX, aiY);
            if (idCount > 0) {
                PlayerOne[aiX][aiY][1] = 'h';
                if (aiX > Xmax) Xmax = aiX;
                if (aiX < Xmin) Xmin = aiX;
                if (aiY > Ymax) Ymax = aiY;
                if (aiY < Ymin) Ymin = aiY;
                --liveOne;
                lastxAI = aiX; lastyAI = aiY;
                LastStatusAI = 1;
            }
            else {
                PlayerOne[aiX][aiY][1] = 'k';
                Target = 0; Targetqueue = 0; direction = 0;
                --liveOne;
                lastxAI = aiX; lastyAI = aiY;
                LastStatusAI = 2;

                killID = IdNaveOne[aiX][aiY];
                for (int i = 1; i < 11; i++) {
                    for (int j = 1; j < 11; j++) {
                        if (IdNaveOne[i][j] == killID) {
                            for (int a = 0; a < 3; a++) {
                                for (int b = 0; b < 3; b++) {
                                    if (PlayerOne[i + a - 1][j + b - 1][1] == '.') {
                                        PlayerOne[i + a - 1][j + b - 1][1] = '-';
                                    }
                                    if (PlayerOne[i + a][j + b][1] == 'h') {
                                        PlayerOne[i + a][j + b][1] = 'k';
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (PlayerOne[aiX][aiY][1] == '.') {
            PlayerOne[aiX][aiY][1] = '-';
            direction = 1 - direction;
            lastxAI = aiX; lastyAI = aiY;
            LastStatusAI = 3;
        }
    }
    // search mode
    else if (Target == 1) {
    SearchMode:
        if (Targetqueue >= 4) {
            Target = 0;
            Targetqueue = 0;
            direction = 0;
            goto RandomMode;
        }
        aiX = Xmin + dirX[Targetqueue];
        aiY = Ymin + dirY[Targetqueue];
        if (aiX < 1 || aiX > 10 || aiY < 1 || aiY > 10 ||
            PlayerOne[aiX][aiY][1] == 'h' ||
            PlayerOne[aiX][aiY][1] == 'k' ||
            PlayerOne[aiX][aiY][1] == '-') {
            Targetqueue++;
            goto SearchMode;
        }
        if (PlayerOne[aiX][aiY][1] == '*') {
            verificareAI(aiX, aiY);
            if (idCount > 0) {
                PlayerOne[aiX][aiY][1] = 'h';
                Target = 2;
                if (aiX > Xmin) { Xmax = aiX; Ymax = Ymin; direction = 0; }
                if (aiX < Xmin) { Xmax = aiX; Ymax = Ymin; direction = 1; }
                if (aiY > Ymin) { Xmax = Xmin; Ymax = aiY; direction = 0; }
                if (aiY < Ymin) { Xmax = Xmin; Ymax = aiY; direction = 1; }
                --liveOne;
                lastxAI = aiX; lastyAI = aiY;
                LastStatusAI = 1;
            }
            else {
                PlayerOne[aiX][aiY][1] = 'k';
                Target = 0; Targetqueue = 0; direction = 0;
                --liveOne;
                lastxAI = aiX; lastyAI = aiY;
                LastStatusAI = 2;
                killID = IdNaveOne[aiX][aiY];
                for (int i = 1; i < 11; i++) {
                    for (int j = 1; j < 11; j++) {
                        if (IdNaveOne[i][j] == killID) {
                            for (int a = 0; a < 3; a++) {
                                for (int b = 0; b < 3; b++) {
                                    if (PlayerOne[i + a - 1][j + b - 1][1] == '.') {
                                        PlayerOne[i + a - 1][j + b - 1][1] = '-';
                                    }
                                    if (PlayerOne[i + a][j + b][1] == 'h') {
                                        PlayerOne[i + a][j + b][1] = 'k';
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (PlayerOne[aiX][aiY][1] == '.') {
            PlayerOne[aiX][aiY][1] = '-';
            Targetqueue++;
            lastxAI = aiX; lastyAI = aiY;
            LastStatusAI = 3;
        }
    }
    // random mode
    else if (Target == 0) {
    RandomMode:
        for (int i = 0; i < 4; i++) {
            int r = rand() % 4;
            swap(dirX[i], dirX[r]);
            swap(dirY[i], dirY[r]);
        }
    RepeatRandom:
        aiX = rand() % 10 + 1;
        aiY = rand() % 10 + 1;
        if (PlayerOne[aiX][aiY][1] == 'h' ||
            PlayerOne[aiX][aiY][1] == 'k' ||
            PlayerOne[aiX][aiY][1] == '-') {
            goto RepeatRandom;
        }
        if (PlayerOne[aiX][aiY][1] == '*') {
            verificareAI(aiX, aiY);
            if (idCount > 0) {
                PlayerOne[aiX][aiY][1] = 'h';
                Target = 1;
                Xmin = aiX; Ymin = aiY;
                Xmax = aiX; Ymax = aiY;
                Targetqueue = 0;
                --liveOne;
                lastxAI = aiX; lastyAI = aiY;
                LastStatusAI = 1;
            }
            else {
                PlayerOne[aiX][aiY][1] = 'k';
                --liveOne;
                lastxAI = aiX; lastyAI = aiY;
                LastStatusAI = 2;
                killID = IdNaveOne[aiX][aiY];
                for (int i = 1; i < 11; i++) {
                    for (int j = 1; j < 11; j++) {
                        if (IdNaveOne[i][j] == killID) {
                            for (int a = 0; a < 3; a++) {
                                for (int b = 0; b < 3; b++) {
                                    if (PlayerOne[i + a - 1][j + b - 1][1] == '.') {
                                        PlayerOne[i + a - 1][j + b - 1][1] = '-';
                                    }
                                    if (PlayerOne[i + a][j + b][1] == 'h') {
                                        PlayerOne[i + a][j + b][1] = 'k';
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (PlayerOne[aiX][aiY][1] == '.') {
            PlayerOne[aiX][aiY][1] = '-';
            lastxAI = aiX; lastyAI = aiY;
            LastStatusAI = 3;
        }
    }
}
// main
int main() {
    srand(time(0));
    system("color 71");
    SetConsoleTitle(L"Sea_Battle");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //initializam matricile
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            for (int k = 0; k < 3; k++) {
                PlayerOne[i][j][k] = '.';
                PlayerTwo[i][j][k] = '.';
            }
            IdNaveOne[i][j] = 0;
            IdNaveTwo[i][j] = 0;
        }
    }
    for (int j = 0; j < 10; j++) {
        cout << "Introduceti coordonatele navei, lungimea ei si starea corabiei (v: verticala / o: orizontala), conform exemplului \n"
            "1 A 4 v \n\n";
        cout << "     A  B  C  D  E  F  G  H  I  J\n";
        for (int i = 1; i < 11; i++) {
            cout << setw(3) << i << " ";
            for (int j = 1; j < 11; j++) {
                cout << " " << PlayerOne[i][j][1] << " ";
            }
            cout << endl;
        }
        cout << endl;
        punemNavaPlayerOne();
        system("cls");
    }
    while (countlanave < 10) {
        punemNavaPlayerTwo();
    }
    for (int i = 1; i < 11; i++) {
        for (int j = 1; j < 11; j++) {
            if (PlayerOne[i][j][1] == '*') { liveOne++; }
        }
    }
    for (int i = 1; i < 11; i++) {
        for (int j = 1; j < 11; j++) {
            if (PlayerTwo[i][j][1] == '*') { liveTwo++; }
        }
    }
    while (win == 0) {

        draw();
        // Attack Player
        attackPlayerOne();
        // Attack AI
        attackAI();

        system("cls");
        if (liveOne <= 0) {
            win = 2;
        }
        if (liveTwo <= 0) {
            win = 1;
        }

    }
    if (win == 1) {
        cout << "\nYOU WIN\n";
    }
    else if (win == 2) {
        cout << "\nGAME OVER\n";
    }
    return 0;
