#include <iostream>
#include <iomanip>

using namespace std;

struct Item {
    int idItem;
    string namaItem; 
    string tipeItem;
    int countItem;
    int valueItem;
};

struct Equipment{
    string codeEquipment;
    string namaEquipment;
    string scalingTipe;
    int countEquipment;
    int damageEquipment;
    string scaling;
};

struct Skill{
    string codeSkill;
    string namaSkill;
    string scalingTipe;
    int damageSkill;
    string scaling;
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
    //untuk mengecek player menggunakan weapon atau tidak
    bool usingWeapon = false;

    Item inv[50];
    Equipment equip[50];
    int inventoryCount;
    int equipmentCount;

    //untuk mengetahui weapon apa yang dipakai;
    Equipment curentWeapoon;

    int weaponDamage;
    int skillDamage;

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

Monster monsterList[5] = {
    {1, "goblin", 100, 20},
    {2, "skeleton", 80, 50},
    {3, "skeleton mage", 60, 100},
    {4, "orc", 150, 30},
    {5, "demon", 200, 80}
};

Item shopItems[5] = {
    {1, "Potion HP", "heal", 3, 50},
    {2, "Potion Mana", "mana", 2, 40}
};
// loop control
bool ulang = false;

// help function
void kembaliUtama();
void kembaliHalaman();
void invalidOption();

// feature function
void startGame();
void initPlayer(Player &plyr, string nama, int classInput);
void applyClass(Player &plyr, int classInput);
void recalcStat(Player &plyr);
void tampilStatus(Player &plyr);


void townMenu();




void enterDungeon();

// di menu enter dungeon
void aboutMonster();
void showInventori(Player &plyr);
void showEquipment(Player &plyr);



//sistem game
int weaponScaling(Equipment weapon, Player &plyr); //weapon scaling
int skillScaling(Skill Spell, Player &plyr); //skill scaling



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

void kembaliHalaman() {
	char kembali;

    cout << "\nKembali ke halaman sebelumnya(y/t)? ";
	cin >> kembali;
				
    if (kembali == 'y' || kembali == 'Y') {
		ulang = true;
		system("cls");
	} else {
		system("cls");
		cout << "\nKeluar dari program...\n" << endl;
		ulang = false;
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
    plyr.equipmentCount = 0;
    plyr.isAlive = true;

    applyClass(plyr, classInput);
    recalcStat(plyr);

    Item potionHp = {1, "Potion HP", "heal", 3, 500};
    Item potionMana = {2, "Potion Mana", "mana", 2, 1000};

    Equipment shortSword = {"1", "Short Sword", "dagger", 1, 20};

    plyr.inv[plyr.inventoryCount++] = potionHp;
    plyr.inv[plyr.inventoryCount++] = potionMana;

    plyr.equip[plyr.equipmentCount++] = shortSword;
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

//sistem scaling weapon
int weaponScaling(Equipment weapon, Player &plyr){  
    int statscaling = 0; 
    int multiplater = 0;
    
    
    if(weapon.scalingTipe == "strenght"){  
        statscaling = plyr.strength;
    } else if(weapon.scalingTipe == "dex"){  
       statscaling = plyr.dexterity;
    } else if(weapon.scalingTipe == "inteligence"){  
        statscaling = plyr.inteligence;
    } 
    
    switch(weapon.scaling[0]){
        case 'A': multiplater = 10; break;
        case 'B': multiplater = 8; break;
        case 'C': multiplater = 5; break;
        default : multiplater = 2; break;
    }
    return (statscaling*multiplater)/2;
}

//sistem skill damage scaling hanya bergantung pada intelengence saja
int skillScaling(Skill Spell, Player &plyr){  
    int statscaling = 0; 
    int multiplater = 0;
     
    switch(Spell.scaling[0]){
        case 'A': multiplater = 10; break;
        case 'B': multiplater = 8; break;
        case 'C': multiplater = 5; break;
        default : multiplater = 2; break;
    }
    return (statscaling*multiplater)/2;
}

void recalcStat(Player &plyr, Equipment weapon, Skill spell) {
    plyr.maxHp = 100 + (plyr.vigor * 10);
    plyr.maxMana = 50 + (plyr.mind * 8);

    plyr.hp = plyr.maxHp;
    plyr.mana = plyr.maxMana;
    
    plyr.baseDamage = 5 + ((plyr.strength * 2) + (plyr.dexterity * 1))/2;
    //skill damage
    plyr.skillDamage = skillScaling(spell, plyr);
    //menginisiate damage sentaja player
    if(plyr.usingWeapon = true){
        plyr.weaponDamage = weapon.damageEquipment + weaponScaling(weapon, plyr);
    } else {
        plyr.weaponDamage = plyr.baseDamage;
    }

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
        cout << "|   [1] Enter Dungeon                  |" << endl;
        cout << "|   [2] Shop                           |" << endl;
        cout << "|   [3] Inventory                      |" << endl;
        cout << "|   [4] Equipment                      |" << endl;
        cout << "|   [5] Blacksmith                     |" << endl;
        cout << "|   [6] Save Game                      |" << endl;
        cout << "|   [7] Quit Game                      |" << endl;
        cout << "========================================" << endl;
        cout << "Masukkan pilihan : ";
        cin >> opsiTown;
        
        cin.ignore();

        switch (opsiTown) {
            case 1:
                system("cls");
                enterDungeon();
                

                //

                break;
            case 2:
                system("cls");

                //
                
                break;
            case 3:
                //inventori
                system("cls");
                showInventori(plyr);
                kembaliHalaman();
                break;
            case 4:
                //equipment
                system("cls");
                showEquipment(plyr);
                kembaliHalaman();
                break;
            case 5:
                system("cls");

                //
                
                break;
            case 6:
                system("cls");

                //
                
                break;
            case 7:
                system("cls");
                

                //
                
                break;
            default:
				system("cls");
                invalidOption();
                break;
        }
    } while (ulang == true);
}

// hanya bisa kembali 1 halaman
void enterDungeon() {
    system("cls");

    int opsiDungeon;
    do{
        cout << "========================================" << endl;
        cout << "|        Welcome to the Dungeon        |" << endl;
        cout << "=======================================" << endl;
        cout << "|   [1] Enter Floor                    |" << endl;
        cout << "|   [2] About the monster              |" << endl;
        cout << "|   [3] Inventory                      |" << endl;
        cout << "|   [4] Equipment                      |" << endl;
        cout << "|   [5] level up                       |" << endl;
        cout << "|   [5] Save Game                      |" << endl;
        cout << "|   [6] return town                    |" << endl;
        cout << "========================================" << endl;
        cout << "Masukkan pilihan : ";
        cin >> opsiDungeon;

        switch (opsiDungeon)
        {
        case 1:
            system("cls");
        // Code for entering floor
            break;
        case 2:
            system("cls");
            aboutMonster();
            kembaliHalaman();
        // Code for about the monster
            break;
        case 3:
        // code fo inventori
            system("cls");
            showInventori(plyr);
            kembaliHalaman();
            break;
        case 4:
        // Code for equipment
            system("cls");
            showEquipment(plyr);
            kembaliHalaman();
            break;
        case 5:
            system("cls");
        // Code for save game
            break;
        case 6:
            system("cls");
        // Code for return dungeon
            break;
    
        default:
            invalidOption();
            break;
        }
    } while (ulang == true);
}

// list of monster in dungeon
void aboutMonster(){
        cout << "===============================================" << endl;  
        cout << "|              List of Monster                |" << endl;
        cout << "===============================================" << endl;
        for (int i = 0; i < 5; i++)
        {
            cout << "===============================================" << endl;
            cout << "Nama Monster : " << monsterList[i].monster_name << endl;
            cout << "HP Monster   : " << monsterList[i].monster_hp << endl;
            cout << "Mana Monster : " << monsterList[i].monster_mana << endl;
        }
}

// show inventory
void showInventori(Player &plyr){
    system("cls");
    cout << "=====================================" << endl;
    cout << "|            Inventori              |" << endl;
    cout << "=====================================" << endl;
    if (plyr.inventoryCount < 0){
        cout << "invntori kosong" << endl;
        return;
    }
    for(int i = 0;i < plyr.inventoryCount; i++){
        cout << i+1 <<". " << plyr.inv[i].namaItem << " X " << plyr.inv[i].countItem << endl;
    }
}

// show equipment
void showEquipment(Player &plyr){
    system("cls");
    cout << "=====================================" << endl;
    cout << "|            Equipment              |" << endl;
    cout << "=====================================" << endl;
    if (plyr.inventoryCount < 0){
        cout << "Equipment kosong" << endl;
        return;
    }
    for(int i = 0;i < plyr.equipmentCount; i++){
        cout << i+1 <<". " << plyr.equip[i].namaEquipment << " X " << plyr.equip[i].countEquipment << endl;
    }
}

// function untuk menambah item ke inventori
void addItem(Player &plyr, Item itemBaru){
    for(int i = 0; i < plyr.inventoryCount; i++){
        if(plyr.inv[i].idItem == itemBaru.idItem){
            plyr.inv[i].countItem += itemBaru.countItem;
            return;
        }
    }
    if(plyr.inventoryCount < 64){
        plyr.inv[plyr.inventoryCount] = itemBaru;
        plyr.inventoryCount++;
    }else {
        cout << "inventori sudah penuh " << endl;
        return;
    }
}

