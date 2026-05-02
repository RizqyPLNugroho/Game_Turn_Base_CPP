#include <iostream>
#include <iomanip>
using namespace std;

struct Item
{
    int id_item;
    string nama_item; 
    string tipe_item;
    int count_item;
    
};

struct Monster{
    int id_monster; 
    string monster_name;
    int monster_hp;
    int monster_mana;
};


struct Player
{
    string nama;
    string origin;
    int hp; 
    int maxhp;

    int exp;
    int lvl;

    int mana;
    int maxmana;

    int def;
    int basedamage;
    
    bool isalive = true;
    bool weapon = true;

    int inv[50];
    int inventory_count;

    int vigor; 
    int mind;
    int dexterity;
    int strength; 
    int intelegence;

};



Player p;

void maxHp(Player &p){
    p.hp = 100 + (p.vigor*10);
    if(p.maxhp < p.hp){
        p.hp = p.maxhp;
    }
}

void maxMana(Player &p){
    p.mana = 100 + (p.mana*5);
    if(p.maxmana < p.mana){
        p.mana = p.mana;
    }
}



int menuGame(){
    int pilll; 

    cout << setfill('=')<< setw(33) <<"="<<endl;
    cout << "|\t DUNGEON CRAWLER \t|" << endl;
    cout << setfill('=')<< setw(33) <<"="<<endl;
    cout << "|\t    1. Main \t\t|" <<endl;
    cout << "|\t    2. keluar \t\t|" <<endl;

    cout << "masukan pilihan anda : ";
    cin >> pilll;
    return pilll;
    
}

void Menu_utama(){

}

void mC(Player &p){

}

void mame(){

}

int main(){

    system("cls");
    bool ulang = false;

    while (ulang = true)
    {
        int pilih = Menu();
    
        if(pilih == 1){
            system("cls");
            cout << "game mulai";
            ulang == true;
            break;
        } else if(pilih == 2){
            cout << "keluar dari game" << endl;
            return 0;
        } else{
            system("cls");
            cout << "input anda salah"<< endl;
        }


    }
    

    




}