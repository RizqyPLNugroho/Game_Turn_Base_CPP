#include <iostream>
#include <iomanip>
#include <ctime>

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
};

Equipment weaponList[10]{
    {"str001", "Hammer", "strength", 100, "B", 0},
    {"str002", "Great Sword", "strength", 200, "A", 0},
    {"str003", "Claymore", "strength", 80, "C", 0},
    {"dex001", "Dagger", "dex", 100, "C", 0},
    {"str001", "Claw", "dex", 120, "B", 0},
    {"str001", "Katana", "dex", 90, "A", 0},
    {"str001", "Spell Book", "inteligence", 50, "B", 0},
    {"str001", "Wizard wand", "inteligence", 60, "A", 0},
    {"str001", "Magic Wand", "inteligence", 40, "A", 0}
};

struct Skill {
    string codeSkill;
    string namaSkill;
    string scalingTipe;
    int damageSkill;
    string scaling;
    int manaCost;
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

Monster monsterList[5] = {
    {"GBL001", "Goblin", 100, 100, 20, 100, 100, 20},
    {"SKL001", "Skeleton", 80, 80, 50, 120, 80, 10},
    {"SKM001", "Skeleton Mage", 60, 60, 100, 150, 150 ,70},
    {"ORC001", "Orc", 150, 150, 30, 200, 200, 50},
    {"DMN001", "Demon", 200, 200, 80, 300, 300, 80}
};

Item shopItem[2] = {
    {"HP001", "Potion HP", "heal", 1, 500},
    {"MP001", "Potion Mana", "mana", 1, 1000}
};

Player plyr;

// loop control
bool ulangHome = false;
bool ulangChild = false;

// help function
void backMain();
bool backChildMenu();
void invalidOption();

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

void showEquipment(Player &plyr);
void listWeapon(Player &plyr);
void equipWeapon(Player &plyr);
void unequipWeapon(Player &plyr);

// sistem game
int weaponScaling(Equipment weapon, Player &plyr); //weapon scaling
int skillScaling(Skill Spell, Player &plyr); //skill scaling
void skillList(Player &plyr, Monster &monster, Skill &spell);


void shopMenu();
void buyItem(Player &plyr, int opsi);
void sellWeapon(Player &plyr);

void blacksmithMenu();
void upgradeWeapon(Player &plyr);

void enterFloor(Player &plyr);
void battleMonster(Player &plyr, Monster monster, Skill Spell);
void monsterAction(Player &plyr, Monster &monster);

void useItem(Player &plyr);
void levelUp(Player &plyr);
void defeatHandling(Player &plyr);

Monster randomMonster();

int main() {
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

                //
                
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
            plyr.strength = 99;
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
        Skill shieldBash = {"SK001", "Shield Bash", "strength", 30, "C", 15};

        plyr.skill[plyr.skillCount++] = shieldBash;
    } else if (plyr.classType == "Ranger") {
        Skill piercingArrow = {"SK002", "Piercing Arrow", "dex", 35, "B", 20};

        plyr.skill[plyr.skillCount++] = piercingArrow;
    } else if (plyr.classType == "Mage") {
        Skill fireBall = {"SK003", "Fire Ball", "inteligence", 50, "A", 5};

        plyr.skill[plyr.skillCount++] = fireBall;
    } else if (plyr.classType == "Warrior") {
        Skill berserkSlash = {"SK004", "Berserk Slash", "strength", 45, "B", 20};

        plyr.skill[plyr.skillCount++] = berserkSlash;
    } else if (plyr.classType == "Assassin") {
        Skill shadowStrike = {"SK005", "Shadow Strike", "dex", 40, "B", 20 };

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
    Equipment weapon = plyr.equip[plyr.equippedWeaponIndex];

    plyr.maxHp = 100 + (plyr.vigor * 10);
    plyr.maxMana = 50 + (plyr.mind * 8);

    plyr.hp = plyr.maxHp;
    plyr.mana = plyr.maxMana;
    
    plyr.baseDamage = 5 + ((plyr.strength * 2) + plyr.dexterity) / 2;
    //skill damage
    plyr.skillDamage = plyr.inteligence * 2;

    //menginisiate damage senjata player
    plyr.weaponDamage = plyr.baseDamage;

    // jika memakai weapon
    if (plyr.usingWeapon == true) {
        plyr.weaponDamage = weapon.damageEquipment + weaponScaling(weapon, plyr);
    }
}

void showStats(Player &plyr) {
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

    showInventory(plyr);
    showEquipment(plyr);
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

void listWeapon(Player &plyr) {
    for(int i = 0; i < plyr.equipmentCount; i++) {
        int sellPrice = (plyr.equip[i].damageEquipment * 20) + (plyr.equip[i].upgradeLevel * 100);

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

void skillList(Player &plyr, Monster &monster, Skill &spell){
int pilih;

    cout << "========================================" << endl;
    cout << "|            List Skill                |" << endl;
    cout << "========================================" << endl;

    for(int i = 0; i < plyr.skillCount; i++) {
        cout << "[" << i+1 << "] " << plyr.skill[i].namaSkill
             << " | Base Damage: " << plyr.skill[i].damageSkill
             << " | Mana Cost: " << plyr.skill[i].manaCost
             << endl;
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
    if(plyr.mana < spell.manaCost){
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

// show equipment
void showEquipment(Player &plyr) {
    int opsi;

    cout << "========================================" << endl; 
    cout << "|              Equipment               |" << endl;
    cout << "========================================" << endl; 

    if (plyr.equipmentCount == 0){
        cout << "Equipment kosong" << endl;
        return;
    } 

    cout << "Current Weapon : ";

    if (plyr.usingWeapon) {
        cout << plyr.equip[plyr.equippedWeaponIndex].namaEquipment;
    } else {
        cout << "None";
    }

    cout << endl;
    cout << "========================================" << endl;

    listWeapon(plyr);

    cout << "[1] Equip Weapon" << endl;
    cout << "[2] Unequip Weapon" << endl;
    cout << "[3] Keluar" << endl;
    cout << "========================================" << endl;

    cout << "Masukkan pilihan : ";
    cin >> opsi;

    switch(opsi){
        case 1:
            system("cls");
            equipWeapon(plyr);
            break;
        case 2:
            system("cls");
            unequipWeapon(plyr);
            break;
        case 3:
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
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

                if (!backChildMenu()) {
                    backMain(); 
                    return;
                }
                break;
            case 4:
                //equipment
                system("cls");
                showEquipment(plyr);
                
                if (!backChildMenu()) {
                    backMain(); 
                    return;
                }
                break;
            case 5:
                system("cls");
                blacksmithMenu();
                break;
            case 6:
                system("cls");

                //
                
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
                ulangDungeon = backChildMenu();
                break;
            case 2:
                system("cls");
                // Code for about the monster
                aboutMonster();
                ulangDungeon = backChildMenu();
                break;
            case 3:
                system("cls");
                showInventory(plyr);
                // code fo inventori
                ulangDungeon = backChildMenu();
                break;
            case 4:
                system("cls");
                // Code for equipment
                showEquipment(plyr);
                ulangDungeon = backChildMenu();
                break;
            case 5:
                system("cls");
                showStats(plyr);
                // Code for level up
                ulangDungeon = backChildMenu();
                break;
            case 6:
                system("cls");
                levelUp(plyr);
                ulangDungeon = backChildMenu();
                // Code for save game

                break;
            case 7:
                system("cls");
                
                // Code for save game

            break;
            case 8:
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
        cout << "Nama Monster : " << monsterList[i].monsterName << endl;
        cout << "HP Monster   : " << monsterList[i].monsterHp << endl;
        cout << "Mana Monster : " << monsterList[i].monsterMana << endl;
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
        for (int i = 0; i < 2; i++) {
            cout << "[" << i + 1 << "] "
                 << shopItem[i].namaItem
                 << " | Price : "
                 << shopItem[i].valueItem
                 << endl;
        }
        cout << "[3] Sell Weapon" << endl;
        cout << "[4] Keluar" << endl;
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
                sellWeapon(plyr);
                ulangShop = backChildMenu();
                break;
            case 4:
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
    Item opsiItem = shopItem[opsi];
    opsi--;

    cout << "========================================" << endl;
    cout << "Item  : " << opsiItem.namaItem << endl;
    cout << "Harga : " << opsiItem.valueItem << " Gold" << endl;
    cout << "Gold Player : " << plyr.gold << endl;
    cout << "========================================" << endl;

    cout << "Beli item ini? (y/t) : ";
    cin >> konfirmasi;

    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        cout << "\nPembelian dibatalkan!" << endl;
        return;
    }

    if (plyr.gold < opsiItem.valueItem) {
        cout << "========================================" << endl;
        cout << "Gold tidak cukup! Gold kamu : " << plyr.gold << endl;
        cout << "========================================" << endl;
        return;
    }

    plyr.gold -= opsiItem.valueItem;

    Item itemBeli = opsiItem;
    itemBeli.countItem = 1;

    addItem(plyr, itemBeli);

    cout << "========================================" << endl;
    cout << opsiItem.namaItem << " berhasil dibeli!" << endl;
    cout << "Gold tersisa : " << plyr.gold << endl;
    cout << "========================================" << endl;
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
        cout << "Weapon tidak valid!" << endl;
        return;
    }

    if (pilih == plyr.equippedWeaponIndex && plyr.equipmentCount == 1) {
        cout << "Weapon terakhir tidak bisa dijual!" << endl;
        return;
    }

    int hargaJual = (plyr.equip[pilih].damageEquipment * 20) + (plyr.equip[pilih].upgradeLevel * 100);

    cout << "Jual " << plyr.equip[pilih].namaEquipment << " ? (y/t) : ";
    cin >> konfirmasi;

    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        cout << "Penjualan dibatalkan!" << endl;
        return;
    }

    plyr.gold += hargaJual;

    cout << "\nWeapon berhasil dijual!" << endl;
    cout << "Mendapatkan " << hargaJual  << " Gold" << endl;

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
                showEquipment(plyr);
                ulangBlacksmith = backChildMenu();
                break;
            case 3:
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
    for (int i = 0; i < plyr.equipmentCount; i++) {
        int biayaUpgrade = 400 + (plyr.equip[i].upgradeLevel * 50);
        cout << "[" << i + 1 << "] "
             << plyr.equip[i].namaEquipment
             << " Lv." << plyr.equip[i].upgradeLevel
             << " | Damage : " << plyr.equip[i].damageEquipment
             << " | Cost : " << biayaUpgrade
             << " Gold" << endl;
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

    int damage = monster.monsterDamage;

    if(plyr.isDefending == true){
        damage = (monster.monsterDamage/2)-plyr.def;
    } 
    
    if(damage < 0) damage = 0;
    cout << "========================================" << endl;
    cout << monster.monsterName << " menyerang " << plyr.nama << endl;
    cout << plyr.nama << " Menerima Damage sebesar " << damage << endl; 
    cout << "========================================" << endl;

    plyr.hp -= damage;

    system("pause");
    system("cls");
}

void enterFloor(Player &plyr) {
    srand(time(0));

    int randomMonster = rand() % 5;

    Monster monster = monsterList[randomMonster];
    Skill spell;
    monster.monsterHp += plyr.lvl*5;
    cout << "========================================" << endl;
    cout << "Monster muncul!" << endl;
    cout << "Nama Monster : " << monster.monsterName << endl;
    cout << "HP Monster   : " << monster.monsterHp << endl;
    cout << "========================================" << endl;

    system("pause");
    system("cls");

    battleMonster(plyr, monster, spell);
}

void levelUp(Player &plyr){
    int inputLevelUp;

    // tolong buatkan agar bisa menampilkan pesan konfirmasi
    if(plyr.poinLevelUp <=0){
        cout << "poin anda kurang untuk level up" << endl;
        return;
    }
    plyr.lvl += plyr.poinLevelUp;
    plyr.maxExp += plyr.maxExp*0.1;
    while (plyr.poinLevelUp >= 1)
    {
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
        cout << "pilih stat yang ingin anda naikan : ";
        cin >> inputLevelUp;
        cout << "----------------------------------------" << endl;
        switch (inputLevelUp)
            {
            case 1: plyr.vigor += 1; break;
            case 2: plyr.mind += 1; break;
            case 3: plyr.def += 1; break;
            case 4: plyr.strength += 1; break;
            case 5: plyr.dexterity += 1; break;            
            case 6: plyr.inteligence += 1; break;
            default: cout << "Pilihan tidak valid!" << endl; continue;
            }
        plyr.poinLevelUp -= 1;
    }
    recalcStat(plyr);
    cout << "Stat berhasil ditingkatkan!" << endl;
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
    cout << "=========================================" << endl;
    cout << "| " <<plyr.nama << " kalah dalam battle! |" << endl;
    cout << "Penalty: Kehilangan EXP dan gold farming! |" << endl;
    cout << "=========================================" << endl;

    plyr.exp = 0;
    plyr.gold /= 2;

    recalcStat(plyr);
}

void battleMonster(Player &plyr, Monster monster, Skill Spell) {
    int pilihan;
    
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
                skillList(plyr, monster, Spell);
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
                showEquipment(plyr);
                system("pause");
                system("cls");
                break;
            case 6:
                return;
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

            if(plyr.exp > plyr.maxExp){
                system("cls");
                cout << "========================================" << endl;
                cout << "Level Naik" <<endl; 
                plyr.poinLevelUp++;
                cout << "poin yang dimiliki saat ini : " << plyr.poinLevelUp << "poin" << endl;
                cout << "========================================" << endl;
                plyr.exp = 0;
            }

            system("pause");
            system("cls");

            monster = randomMonster();
            monster.maxHp += plyr.lvl * 5;
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
        
        monsterAction(plyr, monster);
        
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
        // return battle's code 
    } while(true);
}