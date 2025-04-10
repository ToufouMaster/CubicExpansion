#pragma once
#include "../cube.h"
#include "../scale_functions.h"
#include "__OnGetItemResistance.h"

void* ASMOnGetCreatureResistance_jmpback;

double __fastcall GetCreatureResistance(Creature* creature) {
    double scale_value = GetScaleValue(creature->entity_data.level);
    double creature_resistance = (0.01 * scale_value);
    creature_resistance *= creature->entity_data.resistance_multiplier / 10.0; // 1 -> 0.1;

    if (creature->entity_data.equipment.chest.category_id == 4) {
        creature_resistance += GetItemResistance(&creature->entity_data.equipment.chest);
    }

    if (creature->entity_data.equipment.feet.category_id == 6) {
        creature_resistance += GetItemResistance(&creature->entity_data.equipment.feet);
    }

    if (creature->entity_data.equipment.hands.category_id == 5) {
        creature_resistance += GetItemResistance(&creature->entity_data.equipment.hands);
    }

    if (creature->entity_data.equipment.shoulder.category_id == 7) {
        creature_resistance += GetItemResistance(&creature->entity_data.equipment.shoulder);
    }

    // TODO: this does not workd meaning this is calculated elsewhere
    if (creature->entity_data.affiliation == Creature::Affiliations::Ennemy) {
        creature_resistance *= 0.6;
    }
    if (creature->entity_data.affiliation == Creature::Affiliations::Pet) {
        creature_resistance *= 5.0;
    }
    
    if (creature->entity_data.affiliation != Creature::Affiliations::Player) {
        creature_resistance *= (1 + creature->entity_data.power_base * 0.25);
    }

    return creature_resistance;
}

void __declspec(naked) ASMOnGetCreatureResistance() {
    __asm {
        PUSH_ALL

        call GetCreatureResistance

        POP_ALL

        jmp[ASMOnGetCreatureResistance_jmpback];
    }
}

void SetupOnGetCreatureResistance() {
    WriteJMP((void*)(base + 0x467A6), (void*)&ASMOnGetCreatureResistance);
    ASMOnGetCreatureResistance_jmpback = (void*)(base + 0x4693F);
}

void SetupOnServerGetCreatureResistance() {
    WriteJMP((void*)(base + 0x11546), (void*)&ASMOnGetCreatureResistance);
    ASMOnGetCreatureResistance_jmpback = (void*)(base + 0x116DF);
}
