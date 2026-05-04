#include <iostream>
#include <iomanip>

using namespace std;

struct Item {
    string codeItem;
    string namaItem; 
    string tipeItem;
    int countItem;
};

struct Player {
    string nama;
    string classType;

    int exp;
    int lvl;
    int gold;

    int hp; 
    int maxHp;

    int mana;
    int maxMana;
    
    int baseDamage;
    
    bool isAlive = true;
    // bool weapon = true;

    Item inv[50];
    int inventoryCount;

    int def;
    int vigor; 
    int mind;
    int dexterity;
    int strength; 
    int inteligence;
};

struct Monster{
    int id_monster; 
    string monster_name;
    int monster_hp;
    int monster_mana;
};

// loop control
bool ulang = false;

// help function
void kembaliUtama();
void invalidOption();

// feature function
void startGame();
void initPlayer(Player &plyr, string nama, int classInput);
void applyClass(Player &plyr, int classInput);
void recalcStat(Player &plyr);
void tampilStatus(Player &plyr);

void townMenu();

// struct
Player plyr;

int main() {
    int opsiMenu;

    do {
        cout << "===================================" << endl;
        cout << "|       DUNGEON CRAWLER            |" << endl;
        cout << "===================================" << endl;
        cout << "|   [1] Mulai Game                 |" << endl;
        cout << "|   [2] Load Game                  |" << endl;
        cout << "|   [3] Keluar Game                |" << endl;
        cout << "===================================" << endl;
		cout << "Masukkan pilihan : ";
		cin >> opsiMenu;    

        cin.ignore();

        switch (opsiMenu) {
            case 1:
                system("cls");
                
                startGame();

                break;
            case 2:
                system("cls");

                //
                
                break;
            case 3:
                ulang = false;
				system("cls");
				cout << "\nKeluar dari program...\n" << endl;
				exit(0);
                break;
            default:
				system("cls");
                invalidOption();
                
                kembaliUtama();
                break;
        }

    } while (ulang == true);
}

void kembaliUtama() {
	char kembali;

    cout << "\nKembali ke Menu Utama(y/t)? ";
	cin >> kembali;
				
    if (kembali == 'y' || kembali == 'Y') {
		ulang = true;
		system("cls");
	} else {
		system("cls");
		cout << "\nKeluar dari program...\n" << endl;
		exit(0);
	}
}

void invalidOption() {
    cout << "========================================" << endl;
    cout << "|    Input menu tidak valid            |" << endl;
    cout << "|    Silakan pilih menu yang benar     |" << endl;
    cout << "========================================" << endl;
}

void startGame() {
    string namaInput;
    int classInput;

    cout << "========================================" << endl;
    cout << "|            Buat karakter             |" << endl;
    cout << "========================================" << endl;
    cout << "Masukkan nama karakter : ";
    getline(cin, namaInput);

    do {
        system("cls");
        cout << "========================================" << endl;
        cout << "|            Pilih class               |" << endl;
        cout << "========================================" << endl; 
        cout << "|   [1] Knight    - Def & Vit tinggi   |" << endl;
        cout << "|   [2] Ranger    - Dex tinggi         |" << endl;
        cout << "|   [3] Mage      - Int & Mind tinggi  |" << endl;
        cout << "|   [4] Warrior   - Str tinggi         |" << endl;
        cout << "|   [5] Assassin  - Dex & Str          |" << endl;
        cout << "========================================" << endl;
        cout << "Pilih class (1 - 5): ";
        cin >> classInput;
    } while (classInput < 1 || classInput > 5);

    initPlayer(plyr, namaInput, classInput);

    system("cls");

    cout << "========================================" << endl;
    cout << "|            Karakter dibuat           |" << endl;
    cout << "========================================" << endl; 
    tampilStatus(plyr);
    cout << "========================================" << endl; 

    cout << "\nTekan enter untuk melanjutkan :" << endl;
    system("pause");

    townMenu();
}

void initPlayer(Player &plyr, string nama, int classInput) {
    plyr.nama = nama;
    plyr.lvl = 1;
    plyr.exp = 0;
    plyr.gold = 100;

    plyr.inventoryCount = 0;
    plyr.isAlive = true;

    applyClass(plyr, classInput);
    recalcStat(plyr);

    Item potionHp = {"pthp", "Potion HP", "heal", 3};
    Item potionMana = {"ptmn", "Potion Mana", "mana", 2};

    plyr.inv[plyr.inventoryCount++] = potionHp;
    plyr.inv[plyr.inventoryCount++] = potionMana;
}

void applyClass(Player &plyr, int classInput) {
    switch(classInput) {
        case 1:
            plyr.classType = "Knight";
            plyr.vigor = 8;
            plyr.strength = 6;
            plyr.def = 7;
            plyr.dexterity = 3;
            plyr.inteligence = 2;
            plyr.mind = 3;
            break;
        case 2:
            plyr.classType = "Ranger";
            plyr.vigor = 5;
            plyr.strength = 5;
            plyr.def = 4;
            plyr.dexterity = 8;
            plyr.inteligence = 3;
            plyr.mind = 3;
            break;
        case 3: 
            plyr.classType = "Mage";
            plyr.vigor = 4;
            plyr.strength = 2;
            plyr.def = 3;
            plyr.dexterity = 3;
            plyr.inteligence = 9;
            plyr.mind = 8;
            break;
        case 4: 
            plyr.classType = "Warrior";
            plyr.vigor = 7;
            plyr.strength = 9;
            plyr.def = 5;
            plyr.dexterity = 4;
            plyr.inteligence = 2;
            plyr.mind = 2;
            break;
        case 5:
            plyr.classType = "Assassin";
            plyr.vigor = 5;
            plyr.strength = 7;
            plyr.def = 3;
            plyr.dexterity = 9;
            plyr.inteligence = 3;
            plyr.mind = 3;
            break;
    }
}

void recalcStat(Player &plyr) {
    plyr.maxHp = 100 + (plyr.vigor * 10);
    plyr.maxMana = 50 + (plyr.mind * 8);

    plyr.hp = plyr.maxHp;
    plyr.mana = plyr.maxMana;

    plyr.baseDamage = 5 + (plyr.strength * 2);
}

void tampilStatus(Player &plyr) {
    cout << "Nama  : " << plyr.nama << endl;
    cout << "Class : " << plyr.classType << endl;
    cout << "Level : " << plyr.lvl << " | EXP: " << plyr.exp << endl;
    cout << "Gold  : " << plyr.gold << endl;
    cout << "========================================" << endl;
    cout << "HP    : " << plyr.hp << "/" << plyr.maxHp << endl;
    cout << "Mana  : " << plyr.mana << "/" << plyr.maxMana << endl;
    cout << "Damage: " << plyr.baseDamage << endl;
    cout << "Def   : " << plyr.def << endl;
    cout << "========================================" << endl;
    cout << "Strength : " << plyr.strength  << " | Dexterity : " << plyr.dexterity << endl;
    cout << "Inteligence : " << plyr.inteligence << " | Vigor : " << plyr.vigor << " | Mind : " << plyr.mind << endl;

    cout << "========================================" << endl;
    cout << "|              Inventory               |" << endl;
    cout << "========================================" << endl; 
    if (plyr.inventoryCount == 0) {
        cout << "Inventory anda kosong" << endl;
        return;
    }

    for (int i = 0; i < plyr.inventoryCount; i++) {
        cout << i+1 << ". " << plyr.inv[i].namaItem << " x" << plyr.inv[i].countItem << endl;
    }
}

void townMenu() {
    system("cls");

    int opsiTown;

    do {
        cout << "========================================" << endl;
        cout << "|            Bagelen City              |" << endl;
        cout << "========================================" << endl; 
        cout << "|   [1] Masuk Dungeon                  |" << endl;
        cout << "|   [2] Shop                           |" << endl;
        cout << "|   [3] Inventory                      |" << endl;
        cout << "|   [4] Equipment                      |" << endl;
        cout << "|   [5] Barak                          |" << endl;
        cout << "|   [6] Save Game                      |" << endl;
        cout << "|   [7] Keluar Game                    |" << endl;
        cout << "========================================" << endl;
        cout << "Masukkan pilihan : ";
        cin >> opsiTown;
        
        cin.ignore();

        switch (opsiTown) {
            case 1:
                system("cls");

                //

                break;
            case 2:
                system("cls");

                //
                
                break;
            default:
				system("cls");
                invalidOption();
                break;
        }
    } while (opsiTown < 1 || opsiTown > 7);
}

// void pop() {

// }