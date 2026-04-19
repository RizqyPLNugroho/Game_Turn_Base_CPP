#include <iostream>
#include <iomanip>
using namespace std;




struct item
{
    int id_item;
    string nama_item; 
    string tipe_item;
    int count_item;
    
};

struct monster{
    int id_monster; 
    string monster_name;
    int monster_hp;
    int monster_mana;
};


struct player
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
    int str; 
    int dex; 
    int arc; 
    int intl;

};



player p;

void maxhp(player &p){
    p.hp = 100 + (p.vigor*10);
    if(p.maxhp < p.hp){
        p.hp = p.maxhp;
    }
}

void maxmana(player &p){
    p.mana = 100 + (p.mana*5);
    if(p.maxmana < p.mana){
        p.mana = p.mana;
    }
}

int menu(){
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

void mc(player &p){

}

void game(){

}

int main(){

    system("cls");
    bool ulang = false;

    while (ulang = true)
    {
        int pilih = menu();
    
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