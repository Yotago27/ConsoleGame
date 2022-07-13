using namespace std;
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <fstream>



////////////////
//item classes//
////////////////

class Item {
protected:
    
    int id = 0;
    string name = "";
    float weight = 0.0f;
    int maxStack = 10;
    int amount = 1;
    float value = 0.0f;
    
public:

    int getID() {
        return id;
    }

    string getName() {
        return name;
    }

    int getMaxStack() {
        return maxStack;
    }

    int getAmount() {
        return amount;
    }

    float getValue() {
        return value;
    }

    float getWeight() {
        return weight;
    }

    float getValueTotal() {
        return value * static_cast<float>(amount);
    }

    float getWeightTotal() {
        return weight * static_cast<float>(amount);
    }

    void setAmount(int _amount) {
        amount = _amount;
    }

    

public:

    enum class itemTypes {
        item,
        equipment,
        weapon,
        armor,
        helmet
    };

    itemTypes itemType;

    

    void setItemType(itemTypes _itemType) {
        itemType = _itemType;
    }
    itemTypes getItemType() {
        return itemType;
    }
    string getItemTypeString() {
        string ret = "error";
        switch(itemType){
        case itemTypes::item:
            ret = "item";
            break;
        case itemTypes::equipment:
            ret = "equipment";
            break;
        case itemTypes::weapon:
            ret = "weapon";
            break;
        case itemTypes::armor:
            ret = "armor";
            break;
        case itemTypes::helmet:
            ret = "helmet";
            break;
        }
        return ret;
    }

    Item(string _name, float _weight , float _value, int _maxStack) {

        static int idCount;

        itemType = itemTypes::item;

        name = _name;
        weight = _weight;
        maxStack = _maxStack;
        value = _value;


        id = idCount;
        idCount += 1;
    }

    void printInfo() {
        cout << "  name: " << name << " : " << amount << "/" << maxStack << endl;
        cout << "  id: " << id << endl;
        cout << "  weight single: " << weight << "/total: " << getWeightTotal() << endl;
        cout << "  value single: " << value << "/total: " << getValueTotal() << endl;
        //cout << " max stack: " << maxStack << endl;
        //cout << " amount: " << amount << endl;

    }
};

class Equipment : public Item {
public:



    Equipment(string _name, float _weight, float _value, int _maxStack) : Item(_name, _weight, _value, _maxStack) {
        setItemType(itemTypes::equipment);
    }
};


//weapon classes

class Weapon : public Equipment {
public:

    float damageSharp = 0.0f;
    float damageBlunt = 0.0f;
    float damageFire = 0.0f;
    float damageFreeze = 0.0f;
    float damageElectric = 0.0f;
    float damagePoison = 0.0f;
    float damageMagic = 0.0f;

    Weapon(string _name, float _weight, float _value, int _maxStack) : Equipment(_name, _weight, _value, _maxStack) {
        setItemType(itemTypes::weapon);
    }
};

//armor item classes

class Armor : public Equipment {
public:

    float defenceSharp = 0.0f;
    float defenceBlunt = 0.0f;
    float defenceFire = 0.0f;
    float defenceFreeze = 0.0f;
    float defenceElectric = 0.0f;
    float defencePoison = 0.0f;
    float defenceMagic = 0.0f;

    Armor(string _name, float _weight, float _value, int _maxStack) : Equipment(_name, _weight, _value, _maxStack) {
        setItemType(itemTypes::armor);
    }
};

class Helmet : public Armor {
public:



    Helmet(string _name, float _weight, float _value, int _maxStack) : Armor(_name, _weight, _value, _maxStack) {
        setItemType(itemTypes::helmet);
    }
};



class Inventory {
public:

    

    //for sort function
    int sortTypeName = 0;
    int sortTypeValue = 1;
    int sortTypeID = 2;
    int sortTypeWeight = 3;

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

    void sort(int _sortType) {
        //uses sortTypeName/sortTypeValue/sortTypeID as input

        for (unsigned int x = 0; x < inventory.size(); x++) {
            for (unsigned int y = 0; y < ((inventory.size() - x) - 1); y++) {
                float compareVal1 = 0.0f;
                float compareVal2 = 0.0f;
                if (_sortType == sortTypeID) {
                    compareVal1 = float(getItem(y).getID());
                    compareVal2 = float(getItem(y + 1).getID());
                }
                if (_sortType == sortTypeName) {
                    compareVal1 = float(getItem(y).getName()[0]);
                    compareVal2 = float(getItem(y + 1).getName()[0]);
                }
                if (_sortType == sortTypeValue) {
                    compareVal1 = getItem(y).getValueTotal();
                    compareVal2 = getItem(y + 1).getValueTotal();
                }
                if (_sortType == sortTypeWeight) {
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
            cout << i << ")" << endl;
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

                if (inv.getItem(_inventoryIndex).getItemType() == Item::itemTypes::weapon) {
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

    player.inv.sort(player.inv.sortTypeWeight);

    player.inv.print();
    cout << player.inv.totalWeight();
    
}
