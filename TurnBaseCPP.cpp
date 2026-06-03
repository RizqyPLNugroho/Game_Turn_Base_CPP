#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

struct Item {
    string codeItem;
    string namaItem; 
    string tipeItem;
    int countItem;
    int valueItem;
};

struct Equipment {
    string codeEquipment;
    string namaEquipment;
    string scalingTipe;
    // int countEquipment;
    int damageEquipment;
    string scaling;
    int upgradeLevel;
    int price;
};

struct Skill {
    string codeSkill;
    string namaSkill;
    string scalingTipe;
    int damageSkill;
    string scaling;
    int manaCost;
    int price;
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
    int maxExp;
    int baseDamage;
    
    int poinLevelUp;

    bool isAlive = true;
    //untuk mengecek player menggunakan weapon atau tidak
    bool usingWeapon = false;
    bool isDefending = false;

    Item inv[50];
    int inventoryCount;

    Equipment equip[50];
    int equipmentCount;
    //untuk mengetahui weapon apa yang dipakai; // kuganti langsung menunjuk ke object diarray, supaya tdk desync 
    // Equipment curentWeapoon;
    int equippedWeaponIndex;

    Skill skill[10];
    int skillCount;
    
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
    string codeMonster; 
    string monsterName;
    int monsterHp;
    int maxHp;
    int monsterMana;
    int monsterExpDrop;
    int monsterGoldDrop;
    int monsterDamage;
    bool isDefending = false;
    bool isAlive = true;
};

Equipment weaponList[15]{
    {"str001", "Hammer", "strength", 100, "B", 0, 1500},
    {"str002", "Great Sword", "strength", 200, "A", 0, 3000},
    {"str003", "Claymore", "strength", 80, "C", 0, 1200},
    {"dex001", "Dagger", "dex", 100, "C", 0, 1400},
    {"dex002", "Claw", "dex", 120, "B", 0, 1800},
    {"dex003", "Katana", "dex", 90, "A", 0, 2500},
    {"int001", "Spell Book", "inteligence", 50, "B", 0, 1300},
    {"int002", "Wizard Wand", "inteligence", 60, "A", 0, 2000},
    {"int003", "Magic Wand", "inteligence", 40, "A", 0, 1700},

    {"str004", "Dragon Slayer", "strength", 250, "A", 0, 5000},
    {"dex004", "Twin Blade", "dex", 170, "A", 0, 4200},
    {"int004", "Ancient Staff", "inteligence", 150, "A", 0, 4500},
    {"mix001", "Blood Sword", "strength", 180, "B", 0, 3800},
    {"mix002", "Shadow Dagger", "dex", 160, "A", 0, 4000},
    {"mix003", "Dark Grimoire", "inteligence", 200, "S", 0, 6000}
};

Skill shopSkill[8] = {
    {"SK006", "Meteor Strike", "strength", 80, "A", 30, 2000},
    {"SK007", "Whirlwind", "strength", 60, "B", 20, 1500},
    {"SK008", "Rapid Shot", "dex", 70, "A", 25, 1800},
    {"SK009", "Poison Slash", "dex", 65, "B", 20, 1600},
    {"SK010", "Thunder Bolt", "inteligence", 90, "A", 35, 2500},
    {"SK011", "Ice Spear", "inteligence", 75, "B", 25, 1800},
    {"SK012", "Dark Explosion", "inteligence", 120, "S", 50, 4000},
    {"SK013", "Execution", "strength", 110, "S", 45, 3500}
};

Monster monsterList[5] = {
    {"gbl001", "Goblin", 100, 100, 20, 100, 100, 20},
    {"skl001", "Skeleton", 80, 80, 50, 120, 80, 10},
    {"skm001", "Skeleton Mage", 60, 60, 100, 150, 150 ,70},
    {"orc001", "Orc", 150, 150, 30, 200, 200, 50},
    {"dmn001", "Demon", 200, 200, 80, 300, 300, 80}
};

Item shopItem[3] = {
    {"hp001", "Potion HP", "heal", 1, 500},
    {"mp001", "Potion Mana", "mana", 1, 1000},
    {"up001", "Smiting Stone", "upgrade", 1, 2000}
};

Player plyr;

// loop control
bool ulangHome = false;
bool ulangChild = false;

// help function
void backMain();
bool backChildMenu();
void invalidOption();
string toLowerCase(string text);

// char feature function
void startGame();
void initPlayer(Player &plyr, string nama, int classInput);
void applyClass(Player &plyr, int classInput);
void addClassSkill(Player &plyr);
void recalcStat(Player &plyr);
void showStats(Player &plyr);

void townMenu();

void enterDungeon();

// di menu enter dungeon
void aboutMonster();
void showInventory(Player &plyr);

void equipmentMenu(Player &plyr);
void listWeapon(Player &plyr);
void equipWeapon(Player &plyr);
void unequipWeapon(Player &plyr);

void searchWeapon(Player &plyr);
void sortWeaponIndex(Player &plyr, int idx[], int opsiSort);
void showAllWeapon(Player &plyr);

// sistem game
int weaponScaling(Equipment weapon, Player &plyr); //weapon scaling
int skillScaling(Skill Spell, Player &plyr); //skill scaling
void skillList(Player &plyr, Monster &monster);

void shopMenu();
void buyItem(Player &plyr, int opsi);
void buyWeapon(Player &plyr);
void buySkill(Player &plyr);
void sellItem(Player &plyr);
void sellWeapon(Player &plyr);

void blacksmithMenu();
void upgradeWeapon(Player &plyr);

void enterFloor(Player &plyr);
void battleMonster(Player &plyr, Monster monster);
void monsterAction(Player &plyr, Monster &monster);


void useItem(Player &plyr);
void levelUp(Player &plyr);
void defeatHandling(Player &plyr);
void monsterDrop(Player &plyr, Monster monster);

bool saveSudahAda(string saveName);
void saveGame(Player &plyr);
void loadGame(Player &plyr);
bool showSaveFiles();

Monster randomMonster();

int main() {
    srand(time(0));

    int opsiMenu;

    do {
        cout << "========================================" << endl;
        cout << "|       DUNGEON CRAWLER                |" << endl;
        cout << "========================================" << endl;
        cout << "|       [1] Mulai Game                 |" << endl;
        cout << "|       [2] Load Game                  |" << endl;
        cout << "|       [3] Keluar Game                |" << endl;
        cout << "========================================" << endl;
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
                loadGame(plyr);
                ulangHome = true;
                break;
            case 3:
                ulangHome = false;
				system("cls");
				cout << "\nKeluar dari program...\n" << endl;
				exit(0);
                break;
            default:
				system("cls");
                invalidOption();
                
                backMain();
                break;
        }

    } while (ulangHome == true);
}

void backMain() {
	char kembaliHome;

    cout << "\nKembali ke menu utama (y/t)? ";
	cin >> kembaliHome;
				
    if (kembaliHome == 'y' || kembaliHome == 'Y') {
		ulangHome = true;
		system("cls");
	} else {
		system("cls");
		cout << "\nKeluar dari program...\n" << endl;
		exit(0);
	}
}

bool backChildMenu() {
	char kembaliChild;

    cout << "\nKembali ke halaman sebelumnya (y/t)? ";
	cin >> kembaliChild;
    system("cls");

    if (kembaliChild == 'y' || kembaliChild == 'Y') {
		return true;
	} else {
		return false;
	}
}

void invalidOption() {
    cout << "========================================" << endl;
    cout << "|    Pilihan anda tidak valid          |" << endl;
    cout << "|    Silakan pilih dengan benar        |" << endl;
    cout << "========================================" << endl;
}

string toLowerCase(string text){
    for(size_t i = 0; i < text.length(); i++){
        text[i] = tolower(text[i]);
    }
    return text;
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
    showStats(plyr);
    showInventory(plyr);
    equipmentMenu(plyr);
    cout << "========================================" << endl; 

    cout << "\nTekan enter untuk melanjutkan :" << endl;
    system("pause");

    townMenu();
}

void initPlayer(Player &plyr, string nama, int classInput) {
    plyr.nama = nama;
    plyr.lvl = 1;
    plyr.exp = 0;
    plyr.maxExp = 1000;
    plyr.gold = 1000;

    plyr.hp = 0;
    plyr.maxHp = 0;
    plyr.mana = 0;
    plyr.maxMana = 0;

    plyr.inventoryCount = 0;
    plyr.equipmentCount = 0;

    plyr.isAlive = true;

    plyr.weaponDamage = 0;
    plyr.skillDamage = 0;

    applyClass(plyr, classInput);
    addClassSkill(plyr);

    Item potionHp = shopItem[0];
    potionHp.countItem = 3;
    Item potionMana = shopItem[1];
    potionMana.countItem = 3;

    Equipment starterWeapon;

    switch(classInput) {
        case 1: starterWeapon = weaponList[0]; break;
        case 2: starterWeapon = weaponList[3]; break;
        case 3: starterWeapon = weaponList[6]; break;
        case 4: starterWeapon = weaponList[1]; break;
        case 5: starterWeapon = weaponList[5]; break;
    }

    plyr.equip[plyr.equipmentCount++] = starterWeapon;


    plyr.inv[plyr.inventoryCount++] = potionHp;
    plyr.inv[plyr.inventoryCount++] = potionMana;
    
    // equip weapon otomatis
    plyr.equippedWeaponIndex = 0;
    plyr.usingWeapon = true;

    recalcStat(plyr);
}

void applyClass(Player &plyr, int classInput) {
    switch(classInput) {
        case 1:
            plyr.classType = "Knight";
            plyr.vigor = 8;
            plyr.strength = 7;
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

void addClassSkill(Player &plyr) {
    plyr.skillCount = 0;
    if(plyr.classType == "Knight") {
        Skill shieldBash = {"SK001", "Shield Bash", "strength", 30, "C", 15, 0};

        plyr.skill[plyr.skillCount++] = shieldBash;
    } else if (plyr.classType == "Ranger") {
        Skill piercingArrow = {"SK002", "Piercing Arrow", "dex", 35, "B", 20, 0};

        plyr.skill[plyr.skillCount++] = piercingArrow;
    } else if (plyr.classType == "Mage") {
        Skill fireBall = {"SK003", "Fire Ball", "inteligence", 50, "A", 5, 0};

        plyr.skill[plyr.skillCount++] = fireBall;
    } else if (plyr.classType == "Warrior") {
        Skill berserkSlash = {"SK004", "Berserk Slash", "strength", 45, "B", 20, 0};

        plyr.skill[plyr.skillCount++] = berserkSlash;
    } else if (plyr.classType == "Assassin") {
        Skill shadowStrike = {"SK005", "Shadow Strike", "dex", 40, "B", 20, 0};

        plyr.skill[plyr.skillCount++] = shadowStrike;
    }
}

//sistem scaling weapon
int weaponScaling(Equipment weapon, Player &plyr){  
    int statScaling = 0; 
    int multiplier = 0;
    
    if (weapon.scalingTipe == "strength") {  
        statScaling = plyr.strength;
    } else if (weapon.scalingTipe == "dex") {  
       statScaling = plyr.dexterity;
    } else if (weapon.scalingTipe == "inteligence") {  
        statScaling = plyr.inteligence;
    } 
    
    switch (weapon.scaling[0]) {
        case 'A': multiplier = 10; break;
        case 'B': multiplier = 8; break;
        case 'C': multiplier = 5; break;
        default : multiplier = 2; break;
    }
    return (statScaling * multiplier) / 2;
}

//sistem skill damage scaling hanya bergantung pada intelengence saja
int skillScaling(Skill spell, Player &plyr){  
    int statScaling = 0; 
    int multiplier = 0;

    if (spell.scalingTipe == "strength") {
        statScaling = plyr.strength;
    } else if (spell.scalingTipe == "dex") {
        statScaling = plyr.dexterity;
    } else if (spell.scalingTipe == "inteligence") {
        statScaling = plyr.inteligence;
    }
     
    switch(spell.scaling[0]){
        case 'A': multiplier = 10; break;
        case 'B': multiplier = 8; break;
        case 'C': multiplier = 5; break;
        default : multiplier = 2; break;
    }
    return (statScaling * multiplier) / 2;
}

void recalcStat(Player &plyr) {
    int oldMaxHp = plyr.maxHp;
    int oldMaxMana = plyr.maxMana;

    Equipment weapon;

    if (plyr.usingWeapon) {
        weapon = plyr.equip[plyr.equippedWeaponIndex];
    }

    plyr.maxHp = 150 + (plyr.vigor * 10);
    plyr.maxMana = 50 + (plyr.mind * 8);

    plyr.hp += (plyr.maxHp - oldMaxHp);
    plyr.mana += (plyr.maxMana - oldMaxMana);

    if(plyr.hp > plyr.maxHp){
        plyr.hp = plyr.maxHp;
    }

    if(plyr.mana > plyr.maxMana){
        plyr.mana = plyr.maxMana;
    }

    if(plyr.hp < 0){
        plyr.hp = 0;
    }

    if(plyr.mana < 0){
        plyr.mana = 0;
    }

    plyr.baseDamage = 5 + ((plyr.strength * 2) + plyr.dexterity) / 2;
    plyr.skillDamage = plyr.inteligence * 2;
    plyr.weaponDamage = plyr.baseDamage;

    if (plyr.usingWeapon == true) {
        plyr.weaponDamage = weapon.damageEquipment + weaponScaling(weapon, plyr);
    }
}

void showStats(Player &plyr) {
    cout << "Nama          : " << plyr.nama << endl;
    cout << "Class         : " << plyr.classType << endl;
    cout << "Level         : " << plyr.lvl << endl;
    cout << "Gold          : " << plyr.gold << endl;
    cout << "Exp           : " << plyr.exp << "/" << plyr.maxExp << endl;
    cout << "========================================" << endl;
    cout << "HP            : " << plyr.hp << "/" << plyr.maxHp << endl;
    cout << "Mana          : " << plyr.mana << "/" << plyr.maxMana << endl;
    cout << "Base Damage   : " << plyr.baseDamage << endl;
    cout << "Damage Weapon : " << plyr.weaponDamage << endl;
    cout << "Def           : " << plyr.def << endl;
    cout << "========================================" << endl;
    cout << "Strength      : " << plyr.strength  << " | Dexterity : " << plyr.dexterity << endl;
    cout << "Inteligence   : " << plyr.inteligence << " | Vigor : " << plyr.vigor << " | Mind : " << plyr.mind << endl;
}

// show inventory
void showInventory(Player &plyr) {
    cout << "========================================" << endl; 
    cout << "|               Inventory              |" << endl;
    cout << "========================================" << endl; 
    if (plyr.inventoryCount == 0){
        cout << "Inventory kosong" << endl;
        return;
    }
    for(int i = 0;i < plyr.inventoryCount; i++){
        cout << i+1 <<". " << plyr.inv[i].namaItem << " X " << plyr.inv[i].countItem << endl;
    }
}

void sortWeaponIndex(Player &plyr, int idx[], int opsiSort) {
    int n = plyr.equipmentCount;

    for(int gap = n / 2; gap > 0; gap /= 2) {
        for(int i = gap; i < n; i++) {
            int temp = idx[i];
            int j = i;

            while(j >= gap) {
                bool tukar = false;

                switch(opsiSort) {
                    case 1: 
                        if(plyr.equip[idx[j - gap]].damageEquipment <
                           plyr.equip[temp].damageEquipment) {
                            tukar = true;
                        }
                        break;
                    case 2:
                        if(plyr.equip[idx[j - gap]].damageEquipment >
                           plyr.equip[temp].damageEquipment) {
                            tukar = true;
                        }
                        break;
                    case 3: 
                        if(plyr.equip[idx[j - gap]].namaEquipment >
                           plyr.equip[temp].namaEquipment) {
                            tukar = true;
                        }
                        break;
                    case 4: 
                        if(plyr.equip[idx[j - gap]].namaEquipment <
                           plyr.equip[temp].namaEquipment) {
                            tukar = true;
                        }
                        break;
                }

                if(!tukar) {
                    break;
                }

                idx[j] = idx[j - gap];
                j -= gap;
            }

            idx[j] = temp;
        }
    }
}

void showAllWeapon(Player &plyr) {
    int idx[50];
    int opsiSort;

    if(plyr.equipmentCount == 0) {
        cout << "Tidak ada weapon!" << endl;
        return;
    }

    do {
        cout << "========================================" << endl;
        cout << "|           SHOW ALL WEAPON            |" << endl;
        cout << "========================================" << endl;
        cout << "[1] Damage Tertinggi" << endl;
        cout << "[2] Damage Terendah" << endl;
        cout << "[3] Nama A-Z" << endl;
        cout << "[4] Nama Z-A" << endl;
        cout << "[5] Default" << endl;
        cout << "========================================" << endl;
        cout << "Pilih sorting : ";
        cin >> opsiSort;
    
        if(opsiSort < 1 || opsiSort > 5) {
            system("cls");
            cout << "Pilihan sorting tidak valid!" << endl;
        }
    } while (opsiSort < 1 || opsiSort > 5);

    for(int i = 0; i < plyr.equipmentCount; i++) {
        idx[i] = i;
    }

    if(opsiSort != 5) {
        sortWeaponIndex(plyr, idx, opsiSort);
    }

    system("cls");

    cout << "========================================" << endl;
    cout << "|              WEAPON LIST             |" << endl;
    cout << "========================================" << endl;

    for(int i = 0; i < plyr.equipmentCount; i++) {
        int id = idx[i];
        int sellPrice = plyr.equip[id].price + (plyr.equip[id].upgradeLevel * 100);

        cout << "[" << id + 1 << "] " << plyr.equip[id].namaEquipment;
        if(id == plyr.equippedWeaponIndex && plyr.usingWeapon) {
            cout << " (Equipped)";
        }
        cout << endl;
        cout << "  Damage   : " << plyr.equip[i].damageEquipment << endl;
        cout << "  Scaling  : " << plyr.equip[i].scaling << " | " << plyr.equip[i].scalingTipe << endl;
        cout << "  Level    : " << plyr.equip[i].upgradeLevel << endl;
        cout << "  Price    : " << sellPrice << " Gold" << endl;
        cout << "----------------------------------------" << endl;
    }
}

// show equipment
void equipmentMenu(Player &plyr) {
    int opsi;
    bool ulangEquip = false;

    do {
        cout << "========================================" << endl; 
        cout << "|           Equipment Menu             |" << endl;
        cout << "========================================" << endl; 
    
        if (plyr.equipmentCount == 0){
            cout << "Equipment kosong" << endl;
            return;
        } 
    
        if (plyr.usingWeapon) {
            int weaponIndex = plyr.equippedWeaponIndex;
    
            int sellPrice = plyr.equip[weaponIndex].price + (plyr.equip[weaponIndex].upgradeLevel * 100);
    
            cout << "  " << plyr.equip[weaponIndex].namaEquipment << " (Equipped)" << endl;
            cout << "  Damage   : " << plyr.equip[weaponIndex].damageEquipment << endl;
            cout << "  Scaling  : " << plyr.equip[weaponIndex].scaling << " | " << plyr.equip[weaponIndex].scalingTipe << endl;
            cout << "  Level    : " << plyr.equip[weaponIndex].upgradeLevel << endl;
            cout << "  Price    : " << sellPrice << " Gold" << endl;
        } else {
            cout << "  None" << endl;
        }
    
        cout << "========================================" << endl;
    
        cout << "[1] Show All Weapon" << endl;
        cout << "[2] Equip Weapon" << endl;
        cout << "[3] Unequip Weapon" << endl;
        cout << "[4] Search Weapon" << endl;
        cout << "[5] Keluar" << endl;
        cout << "========================================" << endl;
    
        cout << "Masukkan pilihan : ";
        cin >> opsi;
    
        switch(opsi){
            case 1:
                system("cls");
                showAllWeapon(plyr);
                ulangEquip = backChildMenu();
                break;
            case 2:
                system("cls");
                equipWeapon(plyr);
                ulangEquip = backChildMenu();
                break;
            case 3:
                system("cls");
                unequipWeapon(plyr);
                ulangEquip = backChildMenu();
                break;
            case 4:
                system("cls");
                searchWeapon(plyr);
                ulangEquip = backChildMenu();
                break;
            case 5:
                ulangEquip = false;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    } while (ulangEquip == true);
    
}

void listWeapon(Player &plyr) {
    for(int i = 0; i < plyr.equipmentCount; i++) {
        int sellPrice = plyr.equip[i].price + (plyr.equip[i].upgradeLevel * 100);

        cout << "[" << i + 1 << "] " << plyr.equip[i].namaEquipment;
        if(i == plyr.equippedWeaponIndex && plyr.usingWeapon){
            cout << " (Equipped)";
        }
        cout << endl;
        cout << "  Damage   : " << plyr.equip[i].damageEquipment << endl;
        cout << "  Scaling  : " << plyr.equip[i].scaling << " | " << plyr.equip[i].scalingTipe << endl;
        cout << "  Level    : " << plyr.equip[i].upgradeLevel << endl;
        cout << "  Price    : " << sellPrice << " Gold" << endl;
        cout << "----------------------------------------" << endl;
    }
}

void equipWeapon(Player &plyr){
    int pilih;

    cout << "========================================" << endl;
    cout << "|             Equip Weapon             |" << endl;
    cout << "========================================" << endl;
    if(plyr.equipmentCount == 0){
        cout << "Tidak ada weapon!" << endl;
        return;
    }

    listWeapon(plyr);

    cout << "========================================" << endl;
    cout << "Pilih weapon : ";
    cin >> pilih;

    pilih--;

    if(pilih < 0 || pilih >= plyr.equipmentCount){
        cout << "Weapon tidak valid!" << endl;
        return;
    }

    if(pilih == plyr.equippedWeaponIndex && plyr.usingWeapon){
        cout << "Weapon ini sudah digunakan!" << endl;
        return;
    }

    plyr.equippedWeaponIndex = pilih;
    plyr.usingWeapon = true;

    recalcStat(plyr);

    system("cls");

    cout << "========================================" << endl;
    cout << plyr.equip[pilih].namaEquipment << " berhasil di equip!" << endl;
    cout << "Current Damage : " << plyr.weaponDamage << endl;
    cout << "========================================" << endl;
}

void unequipWeapon(Player &plyr){
    if(!plyr.usingWeapon){
        cout << "Tidak ada weapon yang sedang digunakan!" << endl;
        return;
    }
    cout << "========================================" << endl;
    cout << "Weapon " << plyr.equip[plyr.equippedWeaponIndex].namaEquipment << " berhasil di unequip!" << endl;

    plyr.usingWeapon = false;

    recalcStat(plyr);

    cout << "Damage kembali ke base damage : " << plyr.weaponDamage << endl;
    cout << "========================================" << endl;
}

void searchWeapon(Player &plyr){
    string keyword;
    bool ditemukan;
    char ulang;

    do {
        ditemukan = false;
        cin.ignore();

        cout << "========================================" << endl;
        cout << "|            SEARCH WEAPON             |" << endl;
        cout << "========================================" << endl;
        cout << "Masukkan nama / kode weapon : ";
        getline(cin, keyword);

        keyword = toLowerCase(keyword);
    
        for(int i = 0; i < plyr.equipmentCount; i++){
            string namaLower = toLowerCase(plyr.equip[i].namaEquipment);
            string kodeLower = toLowerCase(plyr.equip[i].codeEquipment);
            
            if(namaLower.find(keyword) != string::npos || kodeLower.find(keyword) != string::npos){
                int sellPrice = plyr.equip[i].price +  (plyr.equip[i].upgradeLevel * 100);
                
                cout << "Weapon ditemukan!" << endl;
                cout << endl;
    
                cout << "[" << i + 1 << "] " << plyr.equip[i].namaEquipment;
                if(i == plyr.equippedWeaponIndex && plyr.usingWeapon) {
                    cout << " (Equipped)";
                }
                cout << endl;
                cout << "  Damage   : " << plyr.equip[i].damageEquipment << endl;
                cout << "  Scaling  : " << plyr.equip[i].scaling << " | " << plyr.equip[i].scalingTipe << endl;
                cout << "  Level    : " << plyr.equip[i].upgradeLevel << endl;
                cout << "  Price    : " << sellPrice << " Gold" << endl;
                cout << "----------------------------------------" << endl;
    
                ditemukan = true;
                break;
            }
        }

        if(!ditemukan){
            cout << "Weapon tidak ditemukan!" << endl;
            cout << "\nCari lagi? (y/t) : ";
            cin >> ulang;

            system("cls");

            if(ulang != 'y' && ulang != 'Y'){
                return;
            }
        }
    } while (!ditemukan);
}


void townMenu() {
    system("cls");
    int opsiTown;
    bool ulangTown = true;

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
                break;
            case 2:
                system("cls");
                shopMenu();
                break;
            case 3:
                //inventori
                system("cls");
                showInventory(plyr);

                system("pause");
                system("cls");
                break;
            case 4:
                //equipment
                system("cls");
                equipmentMenu(plyr);
                
                system("pause");
                system("cls");
                break;
            case 5:
                system("cls");
                blacksmithMenu();
                break;
            case 6:
                system("cls");

                saveGame(plyr);
                
                break;
            case 7:
				system("cls");
                cout << "\nKeluar dari program...\n" << endl;
                exit(0);
                break;
            default:
				system("cls");
                invalidOption();
                break;
        }
    } while (ulangTown == true);
}

void enterDungeon() {
    system("cls");
    int opsiDungeon;
    bool ulangDungeon = true;

    do{
        cout << "========================================" << endl;
        cout << "|        Welcome to the Dungeon        |" << endl;
        cout << "========================================" << endl;
        cout << "|   [1] Enter Floor                    |" << endl;
        cout << "|   [2] About The Monster              |" << endl;
        cout << "|   [3] Inventory                      |" << endl;
        cout << "|   [4] Equipment                      |" << endl;
        cout << "|   [5] Show Stat                      |" << endl;
        cout << "|   [6] Level Up                       |" << endl;
        cout << "|   [7] Save Game                      |" << endl;
        cout << "|   [8] Return Town                    |" << endl;
        cout << "========================================" << endl;
        cout << "Masukkan pilihan : ";
        cin >> opsiDungeon;

        switch (opsiDungeon) {
            case 1:
                system("cls");
                enterFloor(plyr);
                // ulangDungeon = backChildMenu(); 
                break;
            case 2:
                system("cls");
                aboutMonster();
                ulangDungeon = backChildMenu();
                break;
            case 3:
                system("cls");
                showInventory(plyr);
                ulangDungeon = backChildMenu();
                break;
            case 4:
                system("cls");
                // Code for equipment
                equipmentMenu(plyr);
                // ulangDungeon = backChildMenu();
                break;
            case 5:
                system("cls");
                cout << "========================================" << endl;
                cout << "|            Statistik Karakter        |" << endl;
                cout << "========================================" << endl; 
                showStats(plyr);
                ulangDungeon = backChildMenu();
                break;
            case 6:
                system("cls");
                levelUp(plyr);
                ulangDungeon = backChildMenu();
                break;
            case 7:
                system("cls");
                saveGame(plyr);
                ulangDungeon = backChildMenu();
            break;
            case 8:
                system("cls");
                ulangDungeon = false;
                break;
            default:
                invalidOption();
                ulangDungeon = backChildMenu();
                break;
            }
    } while (ulangDungeon == true);
}

// list of monster in dungeon
void aboutMonster(){
    cout << "========================================" << endl;   
    cout << "|            List of Monster           |" << endl;
    cout << "========================================" << endl; 
    for (int i = 0; i < 5; i++) {

        monsterList[i].monsterHp += plyr.lvl * 20;
        monsterList[i].maxHp = monsterList[i].monsterHp;

        monsterList[i].monsterDamage += plyr.lvl * 5;

        monsterList[i].monsterExpDrop += plyr.lvl * 25;
        monsterList[i].monsterGoldDrop += plyr.lvl * 15;

        cout << "Nama Monster : " << monsterList[i].monsterName << endl;
        cout << "HP Monster   : " << monsterList[i].monsterHp << endl;
        cout << "Damage Monster : " << monsterList[i].monsterDamage << endl;
        cout << "========================================" << endl; 
    }
}

// function untuk menambah item ke inventori
void addItem(Player &plyr, Item itemBaru){
    for (int i = 0; i < plyr.inventoryCount; i++) {
        if(plyr.inv[i].codeItem == itemBaru.codeItem){
            plyr.inv[i].countItem += itemBaru.countItem;
            return;
        }
    }
    if (plyr.inventoryCount < 50) {
        plyr.inv[plyr.inventoryCount] = itemBaru;
        plyr.inventoryCount++;
    } else {
        cout << "Inventori sudah penuh " << endl;
        return;
    }
}

void shopMenu() {
    system("cls");
    int opsi;
    bool ulangShop = true;

    do {
        cout << "========================================" << endl;
        cout << "|                Shop                  |" << endl;
        cout << "========================================" << endl;
        cout << "Gold Player : " << plyr.gold << endl;
        cout << "========================================" << endl;
        cout << "[1] Buy Potion HP" << endl;
        cout << "[2] Buy Potion Mana" << endl;
        cout << "[3] Buy Weapon" << endl;
        cout << "[4] Buy Skill" << endl;
        cout << "[5] Sell Item / Weapon" << endl;
        cout << "[6] Exit" << endl;
        cout << "========================================" << endl;
        cout << "Masukkan pilihan : ";
        cin >> opsi;

        switch (opsi) {
            case 1:
                system("cls");
                buyItem(plyr, opsi);
                ulangShop = backChildMenu();
                break;
            case 2:
                system("cls");
                buyItem(plyr, opsi);
                ulangShop = backChildMenu();
                break;
            case 3:
                system("cls");
                buyWeapon(plyr);
                ulangShop = backChildMenu();
                break;
            case 4:
                system("cls");
                buySkill(plyr);
                ulangShop = backChildMenu();
                break;
            case 5:
                system("cls");
                sellItem(plyr);
                ulangShop = backChildMenu();
                break;
            case 6:
                system("cls");
                ulangShop = false;
                break;
            default:
                system("cls");
                invalidOption();
                ulangShop = backChildMenu();
                break;
        }
    } while (ulangShop == true);
}

void buyItem(Player &plyr, int opsi) {
    char konfirmasi;
    int qty;
    opsi--;
    Item opsiItem = shopItem[opsi];

    cout << "========================================" << endl;
    cout << "Item  : " << opsiItem.namaItem << endl;
    cout << "Harga : " << opsiItem.valueItem << " Gold" << endl;
    cout << "Gold Player : " << plyr.gold << endl;
    cout << "========================================" << endl;
    cout << "Masukkan Jumlah : ";
    cin >> qty;

    cout << "Beli item ini? (y/t) : ";
    cin >> konfirmasi;

    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        cout << "\nPembelian dibatalkan!" << endl;
        return;
    }

    if (plyr.gold < (opsiItem.valueItem*qty)) {
        cout << "========================================" << endl;
        cout << "Gold tidak cukup! Gold kamu : " << plyr.gold << endl;
        cout << "========================================" << endl;
        return;
    }

    plyr.gold -= (opsiItem.valueItem*qty);

    Item itemBeli = opsiItem;
    itemBeli.countItem = qty;

    addItem(plyr, itemBeli);

    system("cls");

    cout << "========================================" << endl;
    cout << opsiItem.namaItem << " berhasil dibeli!" << endl;
    cout << "Gold tersisa : " << plyr.gold << endl;
    cout << "========================================" << endl;
}

void buyWeapon(Player &plyr) {
    int pilih;
    char confirm;
    bool weaponSama = false;

    cout << "========================================" << endl;
    cout << "|             BUY WEAPON               |" << endl;
    cout << "========================================" << endl;
    for(int i = 0; i < 15; i++) {
        cout << "[" << i + 1 << "] " << weaponList[i].namaEquipment;
        cout << endl;
        cout << "  Damage   : " << weaponList[i].damageEquipment << endl;
        cout << "  Scaling  : " << weaponList[i].scaling << " | " << weaponList[i].scalingTipe << endl;
        cout << "  Price    : " << weaponList[i].price << " Gold" << endl;
        cout << "----------------------------------------" << endl;
    }
    cout << "========================================" << endl;
    cout << "Gold : " << plyr.gold << endl;
    cout << "\nPilih weapon : ";
    cin >> pilih;

    pilih--;

    if(pilih < 0 || pilih >= 15) {
        cout << "\nWeapon tidak valid!" << endl;
        return;
    }

    int harga = weaponList[pilih].price;

    if(plyr.gold < harga) {
        cout << "\nGold tidak cukup!" << endl;
        return;
    }

    for(int i = 0; i < plyr.equipmentCount; i++) {
        if(plyr.equip[i].codeEquipment == weaponList[pilih].codeEquipment) {
            weaponSama = true;

            cout << "========================================" << endl;
            cout << "Weapon yang sama sudah dimiliki!" << endl;
            cout << "\nWeapon Inventory:" << endl;
            cout << "Nama   : " << plyr.equip[i].namaEquipment << endl;
            cout << "Level  : " << plyr.equip[i].upgradeLevel << endl;
            cout << "Damage : " << plyr.equip[i].damageEquipment << endl;
            cout << "\nWeapon Shop:" << endl;
            cout << "Nama   : " << weaponList[pilih].namaEquipment << endl;
            cout << "Level  : " << weaponList[pilih].upgradeLevel << endl;
            cout << "Damage : " << weaponList[pilih].damageEquipment << endl;
            cout << "========================================" << endl;
            break;
        }
    }

    if(weaponSama) {
        cout << "Tetap beli weapon duplicate ini? (y/t) : ";
    } else {
        cout << "Beli weapon ini? (y/t) : ";
    }

    cin >> confirm;

    if(confirm != 'y' && confirm != 'Y') {
        cout << "\nPembelian dibatalkan!" << endl;
        return;
    }

    plyr.gold -= harga;

    plyr.equip[plyr.equipmentCount++] = weaponList[pilih];

    cout << "\n" << weaponList[pilih].namaEquipment << " berhasil dibeli!" << endl;
}

void buySkill(Player &plyr) {
    int pilih;
    char confirm;

    cout << "========================================" << endl;
    cout << "|              BUY SKILL               |" << endl;
    cout << "========================================" << endl;

    for(int i = 0; i < 8; i++) {
        cout << "[" << i + 1 << "] " << shopSkill[i].namaSkill << endl;
        cout << "  Damage   : " << shopSkill[i].damageSkill << endl;
        cout << "  Scaling  : " << shopSkill[i].scaling << " | " << shopSkill[i].scalingTipe << endl;
        cout << "  Price    : " << shopSkill[i].price << " Gold" << endl;
        cout << "----------------------------------------" << endl;
    }

    cout << "========================================" << endl;
    cout << "Gold : " << plyr.gold << endl;

    cout << "\nPilih skill : ";
    cin >> pilih;

    pilih--;

    if(pilih < 0 || pilih >= 8) {
        cout << "\nSkill tidak valid!" << endl;
        return;
    }

    if(plyr.skillCount >= 10) {
        cout << "\nSlot skill penuh!" << endl;
        return;
    }

    if(plyr.gold < shopSkill[pilih].price) {
        cout << "\nGold tidak cukup!" << endl;
        return;
    }

    for(int i = 0; i < plyr.skillCount; i++) {
        if(plyr.skill[i].codeSkill == shopSkill[pilih].codeSkill) {
            cout << "\nSkill sudah dimiliki!" << endl;
            return;
        }
    }

    cout << "Beli skill ini? (y/t) : ";
    cin >> confirm;

    if(confirm != 'y' && confirm != 'Y') {
        cout << "\nPembelian dibatalkan!" << endl;
        return;
    }

    plyr.gold -= shopSkill[pilih].price;

    plyr.skill[plyr.skillCount++] = shopSkill[pilih];

    cout << "\nSkill berhasil dibeli!" << endl;
}

void sellItem(Player &plyr) {
    int opsi;
    int itemDipilih;

    cout << "========================================" << endl;
    cout << "|             SELL MENU                |" << endl;
    cout << "========================================" << endl;
    cout << "1. Sell Item" << endl;
    cout << "2. Sell Weapon" << endl;
    cout << "========================================" << endl;
    cout << "Pilih : ";
    cin >> opsi;

    switch(opsi) {
        case 1: {
            cout << endl;
            int harga;
            int qty;

            showInventory(plyr);

            cout << "\nPilih item : ";
            cin >> itemDipilih;

            itemDipilih--;

            if(itemDipilih < 0 || itemDipilih >= plyr.inventoryCount) {
                cout << "\nItem tidak valid!" << endl;
                return;
            }

            cout << "Jumlah yang ingin dijual : ";
            cin >> qty;

            if(qty <= 0) {
                cout << "\nJumlah tidak valid!" << endl;
                return;
            }

            if(qty > plyr.inv[itemDipilih].countItem) {
                cout << "\nJumlah item tidak cukup!" << endl;
                return;
            }

            harga = (plyr.inv[itemDipilih].valueItem - 50) * qty;

            cout << "\n========================================" << endl;
            cout << qty << " "  << plyr.inv[itemDipilih].namaItem << " terjual seharga " << harga << " Gold" << endl;
            cout << "========================================" << endl;

            plyr.gold += harga;

            plyr.inv[itemDipilih].countItem -= qty;

            if(plyr.inv[itemDipilih].countItem <= 0) {
                for(int i = itemDipilih; i < plyr.inventoryCount - 1; i++) {
                    plyr.inv[i] = plyr.inv[i + 1];
                }
                plyr.inventoryCount--;
            }
            break;
        }

        case 2:
            cout << endl;
            sellWeapon(plyr);
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
    }
}

void sellWeapon(Player &plyr) {
    int pilih;
    char konfirmasi;

    cout << "========================================" << endl;
    cout << "|            Sell Weapon               |" << endl;
    cout << "========================================" << endl;

    if (plyr.equipmentCount == 0) {
        cout << "Tidak ada weapon untuk dijual!" << endl;
        return;
    }

    listWeapon(plyr);

    cout << "Pilih weapon yang ingin dijual : ";
    cin >> pilih;

    pilih--;

    if (pilih < 0 || pilih >= plyr.equipmentCount) {
        cout << "\nWeapon tidak valid!" << endl;
        return;
    }

    if (pilih == plyr.equippedWeaponIndex && plyr.equipmentCount == 1) {
        cout << "\nWeapon terakhir tidak bisa dijual!" << endl;   
        return;
    }

    int realPrice = plyr.equip[pilih].price + (plyr.equip[pilih].upgradeLevel * 100);
    int sellPrice = realPrice / 2;

    cout << "========================================" << endl;
    cout << "Harga asli : " << realPrice << " Gold" << endl;
    cout << "Harga jual : " << sellPrice << " Gold" << endl;
    cout << "========================================" << endl;
    cout << "\nJual " << plyr.equip[pilih].namaEquipment << " ? (y/t) : ";
    cin >> konfirmasi;

    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        cout << "\nPenjualan dibatalkan!" << endl;
        return;
    }

    plyr.gold += sellPrice;

    cout << "\nWeapon berhasil dijual!" << endl;
    cout << "Mendapatkan " << sellPrice  << " Gold" << endl;

    for (int i = pilih; i < plyr.equipmentCount - 1; i++) {
        plyr.equip[i] = plyr.equip[i + 1];
    }

    plyr.equipmentCount--;

    if (plyr.equippedWeaponIndex == pilih) {
        plyr.equippedWeaponIndex = 0;
    } else if (plyr.equippedWeaponIndex > pilih) {
        plyr.equippedWeaponIndex--;
    }

    recalcStat(plyr);
}

void blacksmithMenu(){
    system("cls");
    int opsi;
    bool ulangBlacksmith = true;

    do{
        cout << "========================================" << endl;
        cout << "|             BLACKSMITH               |" << endl;
        cout << "========================================" << endl;
        cout << "[1] Upgrade Weapon" << endl;
        cout << "[2] View Equipment" << endl;
        cout << "[3] Exit" << endl;
        cout << "========================================" << endl;
        cout << "Masukkan pilihan : ";
        cin >> opsi;

        switch (opsi) {
            case 1:
                system("cls");
                upgradeWeapon(plyr);
                ulangBlacksmith = backChildMenu();
                break;
            case 2:
                system("cls");
                equipmentMenu(plyr);
                ulangBlacksmith = backChildMenu();
                break;
            case 3:
                system("cls");
                ulangBlacksmith = false;
                break;
            default:
                system("cls");
                invalidOption();
                ulangBlacksmith = backChildMenu();
                break;
        }
    } while (ulangBlacksmith == true);
}

void upgradeWeapon(Player &plyr) {
    int opsi;
    char konfirmasi;

    cout << "========================================" << endl;
    cout << "|           Upgrade Weapon             |" << endl;
    cout << "========================================" << endl;

    for(int i = 0; i < plyr.equipmentCount; i++) {
        int biayaUpgrade = 400 + (plyr.equip[i].upgradeLevel * 50);
        cout << "[" << i + 1 << "] " << plyr.equip[i].namaEquipment;
        cout << endl;
        cout << "  Damage   : " << plyr.equip[i].damageEquipment << endl;
        cout << "  Scaling  : " << plyr.equip[i].scaling << " | " << plyr.equip[i].scalingTipe << endl;
        cout << "  Cost     : " << biayaUpgrade << " Gold" << endl;
        cout << "----------------------------------------" << endl;
    }

    cout << "========================================" << endl;
    cout << "Gold Player : " << plyr.gold << endl;

    cout << "\nPilih weapon : ";
    cin >> opsi;
    opsi--;

    if(opsi < 0 || opsi >= plyr.equipmentCount){
        cout << "Weapon tidak ditemukan!" << endl;
        return;
    }

    Equipment &weapon = plyr.equip[opsi];

    int biayaUpgrade = 400 + (weapon.upgradeLevel * 50);

    cout << "Upgrade weapon ini? (y/t) : ";
    cin >> konfirmasi;

    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        cout << "\nUpgrade dibatalkan!" << endl;
        return;
    }

    if(plyr.gold < biayaUpgrade){
        cout << "\nGold tidak cukup!" << endl;
        return;
    }

    plyr.gold -= biayaUpgrade;

    weapon.damageEquipment += 5;
    weapon.price += 200;
    weapon.upgradeLevel++;

    recalcStat(plyr);

    cout << "\n========================================" << endl;
    cout << weapon.namaEquipment << " berhasil diupgrade!" << endl;
    cout << "Level Weapon : " << weapon.upgradeLevel << endl;
    cout << "Damage Baru  : " << weapon.damageEquipment << endl;
    cout << "Sisa Gold    : " << plyr.gold << endl;
    cout << "========================================" << endl;
}


Monster randomMonster(){
    int idx = rand() % 5;
    Monster monster = monsterList[idx];
    monster.maxHp = monster.monsterHp;
    monster.isDefending = false;
    return monster;
}

void monsterAction(Player &plyr, Monster &monster){
    int inputMonster = 0; 
    inputMonster = rand() % 100;

    if(monster.monsterHp < monster.maxHp * 0.4) {
        if(inputMonster < 40) {
            monster.isDefending = true;
            cout << "========================================" << endl;
            cout << monster.monsterName << " bertahan!" << endl;
            cout << "========================================" << endl;
            system("pause");
            system("cls");
            return;
        }
    }

    int damage = monster.monsterDamage+(10*plyr.lvl);

    if(plyr.isDefending == true){
        damage /= 2;
    }

    damage -= plyr.def;

    if(damage < 0){
        damage = 0;
    }

    cout << "========================================" << endl;
    cout << monster.monsterName << " menyerang " << plyr.nama << endl;
    cout << plyr.nama << " Menerima Damage sebesar " << damage << endl; 
    cout << "========================================" << endl;

    plyr.hp -= damage;

    system("pause");
    system("cls");
}
void monsterDrop(Player &plyr, Monster monster){
    int rolldrop;
    int indexdrop;
    Item dropitem;
    rolldrop = rand() % 100;
    if(rolldrop < 40){
        indexdrop = rand() %3;
        dropitem = shopItem[indexdrop];
        addItem(plyr, dropitem);

        cout << "========================================" << endl;
        cout << monster.monsterName << " menjatuhkan 1 item!" << endl;
        cout << "Drop : " << dropitem.namaItem << endl;
        cout << "========================================" << endl;
        return;
    } else {
        cout << monster.monsterName << " tidak menjatuhkan item." << endl;}
}

void enterFloor(Player &plyr) {

    int randomMonster = rand() % 5;

    Monster monster = monsterList[randomMonster];
    
    monster.monsterHp += plyr.lvl * 10;
    monster.maxHp = monster.monsterHp;

    monster.monsterDamage += plyr.lvl * 5;

    monster.monsterExpDrop += plyr.lvl * 25;
    monster.monsterGoldDrop += plyr.lvl * 15;

    cout << "========================================" << endl;
    cout << "Monster muncul!" << endl;
    cout << "Nama Monster : " << monster.monsterName << endl;
    cout << "HP Monster   : " << monster.monsterHp << endl;
    cout << "========================================" << endl;

    system("pause");
    system("cls");

    battleMonster(plyr, monster);
}

void skillList(Player &plyr, Monster &monster){
    int pilih;

    cout << "========================================" << endl;
    cout << "|            List Skill                |" << endl;
    cout << "========================================" << endl;

    for(int i = 0; i < plyr.skillCount; i++) {
        cout << "[" << i + 1 << "] " << plyr.skill[i].namaSkill;
        cout << endl;
        cout << "  Base Damage   : " << plyr.skill[i].damageSkill << endl;
        cout << "  Mana Cost  : " << plyr.skill[i].manaCost << endl;
        cout << "----------------------------------------" << endl;
    }

    cout << "========================================" << endl;
    cout << "Pilih skill: ";
    cin >> pilih;

    pilih--;
    
    if(pilih < 0 || pilih >= plyr.skillCount){
        cout << "Skill tidak valid!" << endl;
        return;
    }

    Skill skillDipakai = plyr.skill[pilih];
    if(plyr.mana < skillDipakai.manaCost){
        cout << "Mana tidak cukup!" << endl;
        return;
    }

    // hitung damage skill
    int damageSkill = skillDipakai.damageSkill + skillScaling(skillDipakai, plyr);

    if(monster.isDefending){
        damageSkill /= 2;
        cout << monster.monsterName << " sedang bertahan! Damage skill berkurang!" << endl;
    }

    plyr.mana -= plyr.skill[pilih].manaCost;
    monster.monsterHp -= damageSkill;

    if(monster.monsterHp < 0) monster.monsterHp = 0;
    system("cls");
    cout << "========================================" << endl;
    cout << plyr.nama << " menggunakan skill " << skillDipakai.namaSkill << endl;
    cout << "Damage diberikan: " << damageSkill << endl;
    cout << "menggunakan mana sebesar : " << plyr.skill[pilih].manaCost << endl;
    cout << "========================================" << endl;
    system("pause");
    system("cls");
}

void levelUp(Player &plyr){
    int inputLevelUp;

    if(plyr.poinLevelUp <= 0){
        cout << "Poin anda kurang untuk level up" << endl;
        return;
    }

    cout << "========================================" << endl;
    cout << plyr.nama << " dapat menaikan level stat "<< endl;
    cout << "memiliki " << plyr.poinLevelUp << " poin stat yang bisa dinaikan" << endl;
    cout << "========================================" << endl;
    cout << "[1] Vigor" << endl;
    cout << "[2] Mind" << endl;
    cout << "[3] Def" << endl;
    cout << "[4] Strength" << endl;
    cout << "[5] Dexerity" << endl;
    cout << "[6] Intelegence" << endl;
    cout << "========================================" << endl;
    cout << "Pilih stat yang ingin anda naikan : ";
    cin >> inputLevelUp;

    if (inputLevelUp < 1 || inputLevelUp > 6) {
        cout << "Pilihan tidak valid!" << endl;
        levelUp(plyr); 
        return;
    }

    switch (inputLevelUp) {
        case 1: plyr.vigor++; break;
        case 2: plyr.mind++; break;
        case 3: plyr.def++; break;
        case 4: plyr.strength++; break;
        case 5: plyr.dexterity++; break;            
        case 6: plyr.inteligence++; break;
    }

    plyr.poinLevelUp--;
    recalcStat(plyr);

    cout << "\nStat berhasil ditingkatkan! Sisa poin: " << plyr.poinLevelUp << endl;

    if (plyr.poinLevelUp <= 0) {
        cout << "Semua poin telah digunakan!" << endl;
        return;
    }

    levelUp(plyr);
}

void useItem(Player &plyr){
    int potionIndex[50];
    int potionCount = 0;

    cout << "========================================" << endl;
    cout << "|            LIST POTION               |" << endl;
    cout << "========================================" << endl;

    // cari potion dalam inventory
    for(int i = 0; i < plyr.inventoryCount; i++) {
        if(plyr.inv[i].tipeItem == "heal" || plyr.inv[i].tipeItem == "mana") {
            potionIndex[potionCount] = i;
            cout << "[" << potionCount + 1 << "] " 
                 << plyr.inv[i].namaItem 
                 << " x" << plyr.inv[i].countItem << endl;
            potionCount++;
        }
    }

    if(potionCount == 0) {
        cout << "Tidak ada potion di inventory!" << endl;
        return;
    }

    cout << "========================================" << endl;
    cout << "[0] Cancel" << endl;
    cout << "Pilih potion: ";

    int pilih;
    cin >> pilih;

    if(pilih == 0) return;

    pilih--;

    if(pilih < 0 || pilih >= potionCount) {
        cout << "Pilihan tidak valid!" << endl;
        return;
    }

    int idx = potionIndex[pilih];
    Item &potion = plyr.inv[idx];

    system("cls");
    if(potion.tipeItem == "heal") {
        int healAmount = 50;
        plyr.hp += healAmount;
        if(plyr.hp > plyr.maxHp) plyr.hp = plyr.maxHp;

        cout << "========================================" << endl;
        cout << plyr.nama << " memakai " << potion.namaItem << endl;
        cout << "HP + " << healAmount << endl;
        cout << "HP sekarang: " << plyr.hp << "/" << plyr.maxHp << endl;
        cout << "========================================" << endl;
    } else if(potion.tipeItem == "mana") {
        int manaAmount = 40;
        plyr.mana += manaAmount;
        if(plyr.mana > plyr.maxMana) plyr.mana = plyr.maxMana;

        cout << "========================================" << endl;
        cout << plyr.nama << " memakai " << potion.namaItem << endl;
        cout << "Mana + " << manaAmount << endl;
        cout << "Mana sekarang: " << plyr.mana << "/" << plyr.maxMana << endl;
        cout << "========================================" << endl;
    }

    potion.countItem--;

    cout << "Sisa " << potion.namaItem << " : " << potion.countItem << endl;

    if(potion.countItem == 0) {
        for(int j = idx; j < plyr.inventoryCount - 1; j++) {
            plyr.inv[j] = plyr.inv[j + 1];
        }
        plyr.inventoryCount--;
    }
    plyr.isDefending = true;
}

void defeatHandling(Player &plyr){
    cout << "=============================================" << endl;
    cout << "| " << plyr.nama << " kalah dalam battle!    |" << endl;
    cout << "| Penalty: Kehilangan EXP dan gold farming!  |" << endl;
    cout << "=============================================" << endl;

    plyr.exp = 0;
    plyr.gold /= 2;
    plyr.hp = plyr.maxHp;
    plyr.mana = plyr.maxMana;

    system("pause");
    system("cls");
}

void battleMonster(Player &plyr, Monster monster) {
    int pilihan;
    bool ulangFloor = true;
    char kembali;

    do {
        int damagePlayer = plyr.weaponDamage;
        cout << "========================================" << endl;
        cout << "         TURN BASED BATTLE              " << endl;
        cout << "========================================" << endl;

        cout << plyr.nama << endl;
        cout << "HP : " << plyr.hp << "/" << plyr.maxHp << endl;
        cout << "Mana : " << plyr.mana << "/" << plyr.maxMana << endl;

        cout << "\nVS\n" << endl;

        cout << monster.monsterName << endl;
        cout << "HP : " << monster.monsterHp << endl;

        cout << "========================================" << endl;
        cout << "[1] Attack" << endl;
        cout << "[2] Skill" << endl;
        cout << "[3] Defend" << endl;
        cout << "[4] Use Potion" << endl;
        cout << "[5] Equip" << endl;
        cout << "[6] Run" << endl;
        cout << "========================================" << endl;

        cout << "Pilih aksi : ";
        cin >> pilihan;

        system("cls");

        switch(pilihan) {
            case 1:    
                if(monster.isDefending == true){
                    damagePlayer /= 2;
                }
                cout << "========================================" << endl;
                cout << plyr.nama << " menyerang " << monster.monsterName << endl;
                cout << plyr.nama << " memberikan " << damagePlayer << " damage " << endl;
                cout << "========================================" << endl;

                monster.monsterHp = monster.monsterHp -  damagePlayer;
                system("pause");
                system("cls");
                
                break;
            case 2:
                skillList(plyr, monster);
                break;
            case 3:
                plyr.isDefending = true;
                cout << plyr.nama << " bersiap bertahan!" << endl;
                break;
            case 4:
                useItem(plyr);
                system("pause");
                system("cls");
                break;
            case 5:
                equipmentMenu(plyr);
                system("pause");
                system("cls");
                break;
            case 6:
                cout << "\nApakah anda ingin kabur (y/t)? ";
                cin >> kembali;
                system("cls");

                if (kembali == 'y' || kembali == 'Y') {
                    return;
                } else {
                    continue;
                }
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                continue;
        }

        if(monster.monsterHp <= 0){
            cout << "========================================" << endl;
            cout << monster.monsterName << " telah mati" << endl;
            cout << "EXP+ = " << monster.monsterExpDrop << endl;
            cout << "Gold+ = " << monster.monsterGoldDrop << endl;
            cout << "========================================" << endl;
            plyr.exp += monster.monsterExpDrop;
            plyr.gold += monster.monsterGoldDrop;
            monster.isAlive = false;
            monsterDrop(plyr, monster);

            while(plyr.exp >= plyr.maxExp){
                plyr.exp -= plyr.maxExp;
                plyr.lvl++;
                plyr.poinLevelUp++;
                plyr.maxExp += 200; 

                cout << "========================================" << endl;
                cout << "LEVEL UP!" << endl;
                cout << "Level Sekarang : " << plyr.lvl << endl;
                cout << "Mendapatkan 1 Stat Point Tambahan!" << endl;
                cout << "========================================" << endl;

                recalcStat(plyr);
            }

            system("pause");
            system("cls");

            monster = randomMonster();
            monster.monsterHp += plyr.lvl * 5;
            monster.maxHp = monster.monsterHp;

            cout << "========================================" << endl;
            cout << "Monster muncul!" << endl;
            cout << "Nama Monster : " << monster.monsterName << endl;
            cout << "HP Monster   : " << monster.monsterHp << endl;
            cout << "========================================" << endl;

            system("pause");
            system("cls");

            continue;
        }
        
        monster.isDefending = false;

        monsterAction(plyr, monster);

        plyr.isDefending = false;
        
        
        if(plyr.hp <= 0){
            plyr.hp = 0;
            cout << "========================================" << endl;
            cout << plyr.nama << " telah dikalahkan oleh " << monster.monsterName << "!" << endl;
            cout << "========================================" << endl;

            system("pause");
            system("cls");

            defeatHandling(plyr);
            
            return;
        }
    } while(ulangFloor == true);
}

bool showSaveFiles() {
    string fileName;
    int no = 0;

    ifstream cekFile("save_list.txt");

    if(!cekFile) {
        ofstream buatFile("save_list.txt");
        buatFile.close();
    }

    cekFile.close();

    ifstream list("save_list.txt");

    cout << "========================================" << endl;
    cout << "|             SAVE FILES               |" << endl;
    cout << "========================================" << endl;

    while(getline(list, fileName)) {
        if(fileName == "") {
            continue;
        }

        cout << "[" << no + 1 << "] " << fileName << endl;
        no++;
    }

    if(no == 0) {
        cout << "Belum ada save game!" << endl;
        cout << "========================================" << endl;

        list.close();
        return false;
    }

    cout << "========================================" << endl;

    list.close();
    return true;
}

bool saveSudahAda(string saveName){
    ifstream file("save_list.txt");
    string nama;

    while(getline(file, nama)){
        if(nama == saveName){
            return true;
        }
    }
    return false;
}

void saveGame(Player &plyr) {
    string saveName;
    string fileName;
    char pilih;

    if(!showSaveFiles()) {
        system("pause");
        system("cls");
        return;
    }
    
    cout << "Masukkan nama save file : ";
    cin >> saveName;

    fileName = saveName + ".dat";

    ifstream cek(fileName, ios::binary);

    if(cek){
        cout << "Save sudah ada!" << endl;
        cout << "Overwrite save? (y/t) : ";
        cin >> pilih;

        if(pilih != 'y' && pilih != 'Y'){
            return;
        }
    }

    ofstream file(fileName, ios::binary);

    if(!file) {
        cout << "Gagal membuat save file!" << endl;
        return;
    }

    auto writeString = [&](string str) {
        int len = str.length();
        file.write((char*)&len, sizeof(len));
        file.write(str.c_str(), len);
    };

    writeString(plyr.nama);
    writeString(plyr.classType);

    file.write((char*)&plyr.exp, sizeof(plyr.exp));
    file.write((char*)&plyr.lvl, sizeof(plyr.lvl));
    file.write((char*)&plyr.gold, sizeof(plyr.gold));

    file.write((char*)&plyr.hp, sizeof(plyr.hp));
    file.write((char*)&plyr.maxHp, sizeof(plyr.maxHp));

    file.write((char*)&plyr.mana, sizeof(plyr.mana));
    file.write((char*)&plyr.maxMana, sizeof(plyr.maxMana));

    file.write((char*)&plyr.maxExp, sizeof(plyr.maxExp));
    file.write((char*)&plyr.baseDamage, sizeof(plyr.baseDamage));

    file.write((char*)&plyr.poinLevelUp, sizeof(plyr.poinLevelUp));

    file.write((char*)&plyr.isAlive, sizeof(plyr.isAlive));
    file.write((char*)&plyr.usingWeapon, sizeof(plyr.usingWeapon));
    file.write((char*)&plyr.isDefending, sizeof(plyr.isDefending));

    file.write((char*)&plyr.inventoryCount, sizeof(plyr.inventoryCount));

    for(int i = 0; i < plyr.inventoryCount; i++) {
        writeString(plyr.inv[i].codeItem);
        writeString(plyr.inv[i].namaItem);
        writeString(plyr.inv[i].tipeItem);

        file.write((char*)&plyr.inv[i].countItem, sizeof(plyr.inv[i].countItem));
        file.write((char*)&plyr.inv[i].valueItem, sizeof(plyr.inv[i].valueItem));
    }

    file.write((char*)&plyr.equipmentCount, sizeof(plyr.equipmentCount));

    for(int i = 0; i < plyr.equipmentCount; i++) {
        writeString(plyr.equip[i].codeEquipment);
        writeString(plyr.equip[i].namaEquipment);
        writeString(plyr.equip[i].scalingTipe);

        file.write((char*)&plyr.equip[i].damageEquipment, sizeof(plyr.equip[i].damageEquipment));
        file.write((char*)&plyr.equip[i].upgradeLevel, sizeof(plyr.equip[i].upgradeLevel));
        file.write((char*)&plyr.equip[i].price, sizeof(plyr.equip[i].price));

        writeString(plyr.equip[i].scaling);
    }

    file.write((char*)&plyr.skillCount, sizeof(plyr.skillCount));

    for(int i = 0; i < plyr.skillCount; i++) {
        writeString(plyr.skill[i].codeSkill);
        writeString(plyr.skill[i].namaSkill);
        writeString(plyr.skill[i].scalingTipe);

        file.write((char*)&plyr.skill[i].damageSkill, sizeof(plyr.skill[i].damageSkill));
        file.write((char*)&plyr.skill[i].manaCost, sizeof(plyr.skill[i].manaCost));
        file.write((char*)&plyr.skill[i].price, sizeof(plyr.skill[i].price));

        writeString(plyr.skill[i].scaling);
    }

    file.write((char*)&plyr.weaponDamage, sizeof(plyr.weaponDamage));
    file.write((char*)&plyr.skillDamage, sizeof(plyr.skillDamage));

    file.write((char*)&plyr.def, sizeof(plyr.def));
    file.write((char*)&plyr.vigor, sizeof(plyr.vigor));
    file.write((char*)&plyr.mind, sizeof(plyr.mind));
    file.write((char*)&plyr.dexterity, sizeof(plyr.dexterity));
    file.write((char*)&plyr.strength, sizeof(plyr.strength));
    file.write((char*)&plyr.inteligence, sizeof(plyr.inteligence));

    file.write((char*)&plyr.equippedWeaponIndex, sizeof(plyr.equippedWeaponIndex));

    file.close();

    if(!saveSudahAda(saveName)){
        ofstream list("save_list.txt", ios::app);
        list << saveName << endl;
        list.close();
    }

    cout << "\nGame berhasil disimpan!" << endl;
    cout << "File : " << fileName << endl;

    system("pause");
    system("cls");
}

void loadGame(Player &plyr) {
    string saveName;
    string fileName;

    if(!showSaveFiles()) {
        system("pause");
        system("cls");
        return;
    }

    cout << "Masukkan nama file save: ";
    cin >> saveName;

    fileName = saveName + ".dat";

    ifstream file(fileName, ios::binary);

    if(!file) {
        cout << "========================================" << endl;
        cout << "Save file tidak ditemukan!" << endl;
        cout << "Kembali ke menu..." << endl;
        cout << "========================================" << endl;

        system("pause");
        system("cls");
        return;
    }

    auto readString = [&](string &str) {
        int len;
        file.read((char*)&len, sizeof(len));

        char *buffer = new char[len + 1];

        file.read(buffer, len);
        buffer[len] = '\0';

        str = buffer;

        delete[] buffer;
    };

    readString(plyr.nama);
    readString(plyr.classType);

    file.read((char*)&plyr.exp, sizeof(plyr.exp));
    file.read((char*)&plyr.lvl, sizeof(plyr.lvl));
    file.read((char*)&plyr.gold, sizeof(plyr.gold));

    file.read((char*)&plyr.hp, sizeof(plyr.hp));
    file.read((char*)&plyr.maxHp, sizeof(plyr.maxHp));

    file.read((char*)&plyr.mana, sizeof(plyr.mana));
    file.read((char*)&plyr.maxMana, sizeof(plyr.maxMana));

    file.read((char*)&plyr.maxExp, sizeof(plyr.maxExp));
    file.read((char*)&plyr.baseDamage, sizeof(plyr.baseDamage));

    file.read((char*)&plyr.poinLevelUp, sizeof(plyr.poinLevelUp));

    file.read((char*)&plyr.isAlive, sizeof(plyr.isAlive));
    file.read((char*)&plyr.usingWeapon, sizeof(plyr.usingWeapon));
    file.read((char*)&plyr.isDefending, sizeof(plyr.isDefending));

    file.read((char*)&plyr.inventoryCount, sizeof(plyr.inventoryCount));

    for(int i = 0; i < plyr.inventoryCount; i++) {
        readString(plyr.inv[i].codeItem);
        readString(plyr.inv[i].namaItem);
        readString(plyr.inv[i].tipeItem);

        file.read((char*)&plyr.inv[i].countItem, sizeof(plyr.inv[i].countItem));
        file.read((char*)&plyr.inv[i].valueItem, sizeof(plyr.inv[i].valueItem));
    }

    file.read((char*)&plyr.equipmentCount, sizeof(plyr.equipmentCount));

    for(int i = 0; i < plyr.equipmentCount; i++) {
        readString(plyr.equip[i].codeEquipment);
        readString(plyr.equip[i].namaEquipment);
        readString(plyr.equip[i].scalingTipe);

        file.read((char*)&plyr.equip[i].damageEquipment, sizeof(plyr.equip[i].damageEquipment));
        file.read((char*)&plyr.equip[i].upgradeLevel, sizeof(plyr.equip[i].upgradeLevel));
        file.read((char*)&plyr.equip[i].price, sizeof(plyr.equip[i].price));

        readString(plyr.equip[i].scaling);
    }

    file.read((char*)&plyr.skillCount, sizeof(plyr.skillCount));

    for(int i = 0; i < plyr.skillCount; i++) {
        readString(plyr.skill[i].codeSkill);
        readString(plyr.skill[i].namaSkill);
        readString(plyr.skill[i].scalingTipe);

        file.read((char*)&plyr.skill[i].damageSkill, sizeof(plyr.skill[i].damageSkill));
        file.read((char*)&plyr.skill[i].manaCost, sizeof(plyr.skill[i].manaCost));
        file.read((char*)&plyr.skill[i].price, sizeof(plyr.skill[i].price));

        readString(plyr.skill[i].scaling);
    }

    file.read((char*)&plyr.weaponDamage, sizeof(plyr.weaponDamage));
    file.read((char*)&plyr.skillDamage, sizeof(plyr.skillDamage));

    file.read((char*)&plyr.def, sizeof(plyr.def));
    file.read((char*)&plyr.vigor, sizeof(plyr.vigor));
    file.read((char*)&plyr.mind, sizeof(plyr.mind));
    file.read((char*)&plyr.dexterity, sizeof(plyr.dexterity));
    file.read((char*)&plyr.strength, sizeof(plyr.strength));
    file.read((char*)&plyr.inteligence, sizeof(plyr.inteligence));

    file.read((char*)&plyr.equippedWeaponIndex, sizeof(plyr.equippedWeaponIndex));

    file.close();

    cout << "========================================" << endl;
    cout << "Game berhasil di load!" << endl;
    cout << "Welcome back " << plyr.nama << endl;
    cout << "========================================" << endl;

    recalcStat(plyr);

    system("pause");
    townMenu();
}