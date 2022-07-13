#pragma once
#include <iostream>
class Item {
protected:

    int id = 0;
    std::string name = "";
    float weight = 0.0f;
    int maxStack = 10;
    int amount = 1;
    float value = 0.0f;

public:

    bool isWeapon = false;
    bool isArmor = false;
    bool isHelmet = false;
    bool isEquipment = false;

    enum class itemTypes {
        item,
        equipment,
        weapon,
        armor,
        helmet
    };

    itemTypes itemType;

    //functions
    int getID();
    std::string getName();
    int getMaxStack();
    int getAmount();
    float getValue();
    float getWeight();
    float getValueTotal();
    float getWeightTotal();
    void setAmount(int _amount);
    void setItemType(itemTypes _itemType);
    itemTypes getItemType();
    std::string getItemTypeString();
    Item(std::string _name, float _weight, float _value, int _maxStack);
    void printInfo();
};

class Equipment : public Item {
public:



    Equipment(std::string _name, float _weight, float _value, int _maxStack);
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

    Weapon(std::string _name, float _weight, float _value, int _maxStack);
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

    Armor(std::string _name, float _weight, float _value, int _maxStack);
};

class Helmet : public Armor {
public:

    Helmet(std::string _name, float _weight, float _value, int _maxStack);
};