#pragma once
#include "../cube.h"
#include "../scale_functions.h"
#include "__OnGetItemHealth.h"

void* ASMOnGetCreatureMaxHealth_jmpback;

double GetCreatureBaseMaxHealth(int level, char char_class, char specialization, float hp_multiplier = 100.0f) {
    double base_health = 200;

    double health_multiplier = hp_multiplier / 10.0; // hp_multiplier is 100 -> scale it to 10
    double scale_value = GetScaleValue(level);
    double class_multiplier = 1.0;

    switch (char_class) {
    case 1: {
        class_multiplier = 1.3;
        break;
    }
    case 2: {
        class_multiplier = 1.1;
        break;
    }
    case 4: {
        class_multiplier = 1.2;
        break;
    }
    }

    double creature_max_health = health_multiplier * (class_multiplier * scale_value) + base_health * class_multiplier;

    if (char_class == 1 && specialization == 1) {
        creature_max_health *= 1.25;
    }
    return creature_max_health;
}

double __fastcall GetCreatureMaxHealth(Creature* creature) {
    double creature_max_health = GetCreatureBaseMaxHealth(
        creature->entity_data.level,
        creature->entity_data.char_class,
        creature->entity_data.char_specialization,
        creature->entity_data.hp_multiplier
    );

    if (creature->entity_data.equipment.left_weapon.category_id == 3) {
        creature_max_health += GetItemHealth(&creature->entity_data.equipment.left_weapon);
    }

    if (creature->entity_data.equipment.right_weapon.category_id == 3) {
        creature_max_health += GetItemHealth(&creature->entity_data.equipment.right_weapon);
    }

    if (creature->entity_data.equipment.chest.category_id == 4) {
        creature_max_health += GetItemHealth(&creature->entity_data.equipment.chest);
    }

    if (creature->entity_data.equipment.feet.category_id == 6) {
        creature_max_health += GetItemHealth(&creature->entity_data.equipment.feet);
    }

    if (creature->entity_data.equipment.hands.category_id == 5) {
        creature_max_health += GetItemHealth(&creature->entity_data.equipment.hands);
    }

    if (creature->entity_data.equipment.shoulder.category_id == 7) {
        creature_max_health += GetItemHealth(&creature->entity_data.equipment.shoulder);
    }

    if (creature->entity_data.affiliation == Creature::Affiliations::Ennemy) {
        creature_max_health *= 0.8;
    }
    if (creature->entity_data.affiliation == Creature::Affiliations::Pet) {
        creature_max_health *= 5;
    }

    if (creature->entity_data.affiliation != Creature::Affiliations::Player) {
        creature_max_health*= (1 + creature->entity_data.power_base * 0.25);
    }

	return creature_max_health;
}

void __declspec(naked) ASMOnGetCreatureMaxHealth() {
    __asm {
        PUSH_ALL

        call GetCreatureMaxHealth

        POP_ALL

        //original code
        //mov esp, ebp

        jmp[ASMOnGetCreatureMaxHealth_jmpback];
    }
}

void SetupOnGetCreatureMaxHealth() {
    //WriteJMP((void*)(base + 0x44fd8), (void*)&ASMOnGetCreatureMaxHealth);
    //ASMOnGetCreatureMaxHealth_jmpback = (void*)(base + 0x44fdd);

    WriteJMP((void*)(base + 0x44db6), (void*)&ASMOnGetCreatureMaxHealth);
    ASMOnGetCreatureMaxHealth_jmpback = (void*)(base + 0x44fdb);
}
