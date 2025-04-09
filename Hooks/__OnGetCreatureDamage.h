#pragma once
#include "../cube.h"
#include "../scale_functions.h"
#include "__OnGetItemDamage.h"

void* ASMOnGetCreatureDamage_jmpback;
void* ASMOnGetCreatureProjectileDamage_jmpback;

bool IsWearingWeaponsClass(uint32_t race) {
    if (race >= 0 && race <= 16) return true;
    if (race >= 43 && race <= 45) return true;
    if (race >= 48 && race <= 49) return true;
    if (race >= 51 && race <= 52) return true;
    if (race == 68) return true;
    if (race >= 77 && race <= 85) return true;
    if (race >= 148 && race <= 149) return true;
    return false;
}

// TODO: Tweak base damage as base damage feel too powerfull.

double __fastcall GetCreatureDamage(Creature* creature, int32_t skill_id) {
    double base_damage = 1.0;
    double scale_value = GetScaleValue(creature->entity_data.level);
    double creature_damage = (0.1 * scale_value) + base_damage;
    //if (creature->entity_data.hostility_flags == 0) {
    if (IsWearingWeaponsClass(creature->entity_data.race)) {
        creature_damage *= 0.1;
    }

    creature_damage *= creature->entity_data.damage_multiplier;

    if (skill_id != 0) {
        creature_damage += GetItemDamage(&creature->entity_data.equipment.left_weapon);
        creature_damage += GetItemDamage(&creature->entity_data.equipment.right_weapon);
    }
    else {
        // TODO figure out what var_20 is
        return 0;
    }

    if (creature->entity_data.affiliation == Creature::Affiliations::Ennemy) {
        creature_damage *= 0.8;
    }
    if (creature->entity_data.affiliation == Creature::Affiliations::Pet) {
        creature_damage *= 5.0;
    }

    switch (creature->entity_data.skill_id - Creature::Animations::FireExplosionLong) {
    case 0: {
        creature_damage *= 50.0;
        break;
    }
    case 4: {
        creature_damage *= 2.0;
        break;
    }
    case 6: {
        creature_damage *= 5.0;
        break;
    }
    case 9: {
        creature_damage *= 3.0;
        break;
    }
    }

    if (creature->entity_data.affiliation != Creature::Affiliations::Player) {
        creature_damage *= (1 + creature->entity_data.power_base * 0.25);
    }

    return creature_damage;
}

void __declspec(naked) ASMOnGetCreatureDamage() {
    __asm {
        PUSH_ALL

        mov edx, [ebp - 0x1c]

        call GetCreatureDamage

        POP_ALL

        jmp[ASMOnGetCreatureDamage_jmpback];
    }
}

double __fastcall GetCreatureProjectileDamage(Creature* creature) {
    double base_damage = 1.0;
    double scale_value = GetScaleValue(creature->entity_data.level);
    double creature_damage = (0.01 * scale_value + base_damage);
    //if (creature->entity_data.hostility_flags == 0) {
    if (IsWearingWeaponsClass(creature->entity_data.race)) {
        creature_damage *= 0.1;
    }

    creature_damage *= creature->entity_data.damage_multiplier;

    if (true) {
        creature_damage += GetItemDamage(&creature->entity_data.equipment.left_weapon);
        creature_damage += GetItemDamage(&creature->entity_data.equipment.right_weapon);
    }
    else {
        // TODO figure out what var_20 is
        return 99999;
    }

    // Water mage nerf
    if (creature->entity_data.char_class == 3) {
        if (creature->entity_data.char_specialization == 1) {
            creature_damage *= 0.75;
        }
    }

    if (creature->entity_data.skill_id == Creature::Animations::FireRayM2) {
        creature_damage *= 0.75;
    }

    return creature_damage;
}

void __declspec(naked) ASMOnGetCreatureProjectileDamage() {
    __asm {
        PUSH_ALL

        call GetCreatureProjectileDamage

        POP_ALL

        jmp[ASMOnGetCreatureProjectileDamage_jmpback];
    }
}

void SetupOnGetCreatureDamage() {
    WriteJMP((void*)(base + 0x3DC74), (void*)&ASMOnGetCreatureDamage);
    ASMOnGetCreatureDamage_jmpback = (void*)(base + 0x3DF3B);
    WriteJMP((void*)(base + 0x46E83), (void*)&ASMOnGetCreatureProjectileDamage);
    ASMOnGetCreatureProjectileDamage_jmpback = (void*)(base + 0x4710B);
}
