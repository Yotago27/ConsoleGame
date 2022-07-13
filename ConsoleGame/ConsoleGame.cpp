using namespace std;
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include "item.h"


class Inventory {
public:

    

    //for sort function
    enum class sortTypes {
        nameAZ,
        nameZA,
        value,
        id,
        weight
    };

    vector<Item> inventory;

    void addItem(Item _item, int _amount) {

        int amountLeft = _amount;

        //for loop to see if item exists with room in inventory
        for (unsigned int i = 0; i < inventory.size(); i++) {
            //if item id equals item id trying to add
            if (_item.getID() == getItem(i).getID() && amountLeft > 0) {

                int spaceInSlot = _item.getMaxStack() - getItem(i).getAmount();

                if (spaceInSlot < amountLeft) {
                    //if not all can be added in that slot

                    inventory[i].setAmount(_item.getMaxStack());

                    amountLeft = amountLeft - spaceInSlot;
                }
                else {
                    //if all can be added in that space

                    
                    getItem(i).setAmount(getItem(i).getAmount() + amountLeft);

                    amountLeft = 0;
                }               
            }
        }
            
        while (amountLeft > 0) {
            if (amountLeft > 0) {
                inventory.push_back(_item);

                Item lastItem = inventory.back();

                if (_item.getMaxStack() < amountLeft) {
                    inventory.back().setAmount(_item.getMaxStack());
                    amountLeft -= _item.getMaxStack();
                }
                else {
                    inventory.back().setAmount(amountLeft);
                    amountLeft = 0;
                }

                
            };

        }


    }

    void replaceItem(Item _item, int pos) {
        if (pos >= inventory.size()) {
            throw "tried to get item bigger than inv size";
        }
        else {
            inventory[pos] = _item;
        }
    }

    Item getItem(unsigned int pos) {
        if (pos >= inventory.size()) {
            throw "tried to get item bigger than inv size";
        }
        else {
            return inventory[pos];
        }
    }

    int getSize() {
        return inventory.size();
    }

    void sort(sortTypes _sortType) {
        //uses sortTypes as input

        for (unsigned int x = 0; x < inventory.size(); x++) {
            for (unsigned int y = 0; y < ((inventory.size() - x) - 1); y++) {
                float compareVal1 = 0.0f;
                float compareVal2 = 0.0f;
                if (_sortType == sortTypes::id) {
                    compareVal1 = float(getItem(y).getID());
                    compareVal2 = float(getItem(y + 1).getID());
                }
                if (_sortType == sortTypes::nameAZ) {
                    unsigned int i = 0;
                    while(compareVal1 == compareVal2 && i < getItem(y).getName().length()){
                        //swapped compareVal1 and compareVal2 for AZ
                        compareVal2 = float(getItem(y).getName()[i]);
                        compareVal1 = float(getItem(y + 1).getName()[i]);
                        i++;
                    }
                    
                }
                if (_sortType == sortTypes::nameZA) {
                    unsigned int i = 0;
                    while (compareVal1 == compareVal2 && i < getItem(y).getName().length()) {
                        //swapped compareVal1 and compareVal2 for AZ
                        compareVal1 = float(getItem(y).getName()[i]);
                        compareVal2 = float(getItem(y + 1).getName()[i]);
                        i++;
                    }

                }
                if (_sortType == sortTypes::value) {
                    compareVal1 = getItem(y).getValueTotal();
                    compareVal2 = getItem(y + 1).getValueTotal();
                }
                if (_sortType == sortTypes::weight) {
                    compareVal1 = getItem(y).getWeightTotal();
                    compareVal2 = getItem(y + 1).getWeightTotal();
                }

                if (compareVal1 < compareVal2) {
                    Item temp = getItem(y + 1);
                    replaceItem(getItem(y),y + 1);
                    replaceItem(temp, y);
                }
                

            }
        }

    }

    float totalWeight() {
        float weightTotal = 0.0f;
        for (unsigned int i = 0; i < inventory.size(); i++) {
            weightTotal += getItem(i).getWeightTotal();
        }
        return weightTotal;
    }

    void print() {
        for (unsigned int i = 0; i < inventory.size(); i++) {
            cout << (i + 1) << ")" << endl;
            getItem(i).printInfo();
            cout << endl;
        }
    }

};

//////////////////
//creautre class//
//////////////////

class Creature {
protected:

    int level = 0;

    float hp = 10.0f;
    float maxHp = 10.0f;
    float mana = 10.0f;
    float maxMana = 10.0f;
    float stamina = 10.0f;
    float maxStamina = 10.0f;

    

    bool canEquipWeapon = false;
    bool canEqipHelmet = false;

    int equippedWeapon = -1;
    int equippedHelmet = -1;

    
    float carryWeight = 10.0f;

    float endurance = 10.0f;
    float vigor = 10.0f;
    float strength = 10.0f;
    float dexterity = 10.0f;
    float intelligence = 10.0f;

    float wisdom = 10.0f;
    float charisma = 10.0f;
    float luck = 10.0f;
    float faith = 10.0f;
    float resilience = 10.0f;
    
    
    float characterWeight = 10.0f;  
    float speed = 10.0f;
    float fortitude = 10.0f;
    float temp = 10.0f;
    float jumpHeight = 10.0f;

    float resistanceSharp = 10.0f;
    float resistanceBlunt = 10.0f;
    float resistanceFire = 10.0f;
    float resistanceFreeze = 10.0f;
    float resistanceElectric = 10.0f;
    float resistancePoison = 10.0f;
    float resistanceMagic = 10.0f;

    float baseResistanceSharp = 10.0f;
    float baseResistanceBlunt = 10.0f;
    float baseResistanceFire = 10.0f;
    float baseResistanceFreeze = 10.0f;
    float baseResistanceElectric = 10.0f;
    float baseResistancePoison = 10.0f;
    float baseResistanceMagic = 10.0f;

    string name;

    bool tryEquipWeapon(int _inventoryIndex) {

        bool ableToEquip = false;

        if (canEquipWeapon == true) {
            if (_inventoryIndex < inv.getSize()) {

                //cout << inv.getItem(_inventoryIndex).getItemTypeString() << endl;

                if (inv.getItem(_inventoryIndex).isWeapon == true) {
                    equippedWeapon = _inventoryIndex;
                    ableToEquip = true;
                }
                else {
                    ableToEquip = false;
                    //"tried to equip non weapon"
                }

            }
            else {
                ableToEquip = false;
                //"tried to equip item index outside inventory"
            }
        }
        else {
            ableToEquip = false;
            //equip not enabled
        }
        return ableToEquip;

    }

public:

    Inventory inv;

    Creature(string _name) {
        name = _name;
    }

    //seperate from try for output text
    bool equipWeapon(int _inventoryIndex) {
        _inventoryIndex -= 1;
        bool ableToEquip = tryEquipWeapon(_inventoryIndex);
        if (ableToEquip == true) {
            cout << "Equipped weapon " << inv.getItem(_inventoryIndex).getName() << endl;
            return true;
        }
        else {
            cout << "Could not equip weapon " << inv.getItem(_inventoryIndex).getName() << endl;
            return false;
        }
    }
    

    


};


class Player : public Creature{
public:

    Player(string _name): Creature(_name){
        canEquipWeapon = true;
        canEqipHelmet = true;
    }

    
};




int main()
{

    Item rock("Rock", 10.0, 50.0, 100);
    Item paper("Paper", 0.01, 2.0, 100);

    Helmet ironHelmet("Iron Helmet", 15.0, 200.0, 1);
    ironHelmet.defenceSharp = 10.0f;
    ironHelmet.defenceBlunt = 10.0f;

    Weapon ironSword("Iron Sword", 7.5, 300.0, 1);
    ironSword.damageSharp = 10.0f;
    ironSword.damageBlunt = 10.0f;

    Player player("Test Player");



    player.inv.addItem(paper, 50);
    player.inv.addItem(rock,1);
    player.inv.addItem(rock,105);
    player.inv.addItem(ironHelmet, 1);
    player.inv.addItem(ironSword, 2);

    player.equipWeapon(5);

    player.inv.sort(Inventory::sortTypes::nameAZ);

    player.inv.print();

    cout << player.inv.totalWeight();
    
}
