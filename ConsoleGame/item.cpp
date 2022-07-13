#include <iostream>
#include "item.h"

#pragma region Base Item Class
int Item::getID() {
    return id;
}
std::string Item::getName() {
    return name;
}

int Item::getMaxStack() {
    return maxStack;
}

int Item::getAmount() {
    return amount;
}

float Item::getValue() {
    return value;
}

float Item::getWeight() {
    return weight;
}

float Item::getValueTotal() {
    return value * static_cast<float>(amount);
}

float Item::getWeightTotal() {
    return weight * static_cast<float>(amount);
}

void Item::setAmount(int _amount) {
    amount = _amount;
}

void Item::setItemType(itemTypes _itemType) {
    itemType = _itemType;
}

Item::itemTypes Item::getItemType() {
    return itemType;
}

std::string Item::getItemTypeString() {
    std::string ret = "error";
    switch (itemType) {
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

Item::Item(std::string _name, float _weight, float _value, int _maxStack) {

    static int idCount;

    itemType = itemTypes::item;

    name = _name;
    weight = _weight;
    maxStack = _maxStack;
    value = _value;


    id = idCount;
    idCount += 1;
}

void Item::printInfo() {
    std::cout << "  name: " << name << " : " << amount << "/" << maxStack << std::endl;
    std::cout << "  id: " << id << std::endl;
    std::cout << "  weight single: " << weight << "/total: " << getWeightTotal() << std::endl;
    std::cout << "  value single: " << value << "/total: " << getValueTotal() << std::endl;
    //cout << " max stack: " << maxStack << endl;
    //cout << " amount: " << amount << endl;

}
#pragma endregion



Equipment::Equipment(std::string _name, float _weight, float _value, int _maxStack) : Item(_name, _weight, _value, _maxStack) {
    setItemType(itemTypes::equipment);
    isEquipment = true;
}

//weapon classes

Weapon::Weapon(std::string _name, float _weight, float _value, int _maxStack) : Equipment(_name, _weight, _value, _maxStack) {
    setItemType(itemTypes::weapon);
    isWeapon = true;
}

//armor item classes

Armor::Armor(std::string _name, float _weight, float _value, int _maxStack) : Equipment(_name, _weight, _value, _maxStack) {
    setItemType(itemTypes::armor);
    isArmor = true;
}


Helmet::Helmet(std::string _name, float _weight, float _value, int _maxStack) : Armor(_name, _weight, _value, _maxStack) {
    setItemType(itemTypes::helmet);
    isHelmet = true;
}
