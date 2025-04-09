#pragma once
#include "../cube.h"
#include "../scale_functions.h"
#include "__OnGetItemArmor.h"

void* ASMOnGetCreatureArmor_jmpback;

double __fastcall GetCreatureArmor(Creature* creature) {
    double scale_value = GetScaleValue(creature->entity_data.level);
    double creature_armor = (0.01 * scale_value);
    creature_armor *= creature->entity_data.armor_multiplier / 10.0; // 1 -> 0.1;

    if (creature->entity_data.equipment.chest.category_id == 4) {
        creature_armor += GetItemArmor(&creature->entity_data.equipment.chest);
    }

    if (creature->entity_data.equipment.feet.category_id == 6) {
        creature_armor += GetItemArmor(&creature->entity_data.equipment.feet);
    }

    if (creature->entity_data.equipment.hands.category_id == 5) {
        creature_armor += GetItemArmor(&creature->entity_data.equipment.hands);
    }

    if (creature->entity_data.equipment.shoulder.category_id == 7) {
        creature_armor += GetItemArmor(&creature->entity_data.equipment.shoulder);
    }

    if (creature->entity_data.affiliation == Creature::Affiliations::Ennemy) {
        creature_armor *= 0.6;
    }
    if (creature->entity_data.affiliation == Creature::Affiliations::Pet) {
        creature_armor *= 5;
    }


    if (creature->entity_data.affiliation != Creature::Affiliations::Player) {
        creature_armor*= (1 + creature->entity_data.power_base * 0.25);
    }

	return creature_armor;
}

void __declspec(naked) ASMOnGetCreatureArmor() {
    __asm {
        PUSH_ALL

        call GetCreatureArmor

        POP_ALL

        jmp[ASMOnGetCreatureArmor_jmpback];
    }
}

void SetupOnGetCreatureArmor() {
    WriteJMP((void*)(base + 0x3cff6), (void*)&ASMOnGetCreatureArmor);
    ASMOnGetCreatureArmor_jmpback = (void*)(base + 0x3d18f);
}
