#pragma once
#include "../cube.h"
#include "../scale_functions.h"

void* ASMOnCharacterWidgetWeaponRatingUpdate_jmpback;
void* ASMOnCharacterWidgetArmorRatingUpdate_jmpback;
float return_weapon_rating;
float return_armor_rating;

void __fastcall CharacterWidgetWeaponRatingUpdate(void* game_controller) {
    Creature* creature = GetLocalCreature(game_controller);
    Item* left_weapon = &creature->entity_data.equipment.left_weapon;
    Item* right_weapon = &creature->entity_data.equipment.right_weapon;

    typedef bool(__fastcall* IsWearingOneHandedWeapon_t)(Creature*);
    auto IsWearingOneHandedWeapon = (IsWearingOneHandedWeapon_t)(base + 0x44230);

    double rating = 0.0;

    if (left_weapon->category_id == 3) {
        if (creature->entity_data.level != 0) {
            double base_scaling = GetItemScalingValue((uint32_t)left_weapon->level, 0);
            base_scaling = base_scaling / GetItemScalingValue(creature->entity_data.level, 0);
            rating += base_scaling * (1 + left_weapon->rarity * 0.25);

            //double rarity_scaling = GetItemScalingValue((uint32_t)left_weapon->rarity * RARITY_POWER, 0);
            //rating += base_scaling * (1 + rarity_scaling / GetItemScalingValue(MAX_RARITY * RARITY_POWER, 0));
        }
    }
    if (right_weapon->category_id == 3) {
        if (creature->entity_data.level != 0) {
            double base_scaling = GetItemScalingValue((uint32_t)right_weapon->level, 0);
            base_scaling = base_scaling / GetItemScalingValue(creature->entity_data.level, 0);
            rating += base_scaling * (1 + right_weapon->rarity * 0.25);
            
            //double rarity_scaling = GetItemScalingValue((uint32_t)right_weapon->rarity * RARITY_POWER, 0);
            //rating += base_scaling * (1 + rarity_scaling / GetItemScalingValue(MAX_RARITY * RARITY_POWER, 0));
        }
    }

    if (IsWearingOneHandedWeapon(creature) == false) {
        rating *= 0.5;
    }

    return_weapon_rating = rating;
}

void __fastcall CharacterWidgetArmorRatingUpdate(void* game_controller) {
    Creature* creature = GetLocalCreature(game_controller);
    Item* shoulder = &creature->entity_data.equipment.shoulder;
    Item* gloves = &creature->entity_data.equipment.hands;
    Item* boots = &creature->entity_data.equipment.feet;
    Item* chest = &creature->entity_data.equipment.chest;

    double rating = 0.0;

    if (chest->category_id == 4) {
        if (creature->entity_data.level != 0) {
            double base_scaling = GetItemScalingValue((uint32_t)chest->level, 0);
            base_scaling = base_scaling / GetItemScalingValue(creature->entity_data.level, 0);
            double rarity_scaling = GetItemScalingValue((uint32_t)chest->rarity * RARITY_POWER, 0);
            rating += 2*(base_scaling * (1 + rarity_scaling / GetItemScalingValue(MAX_RARITY * RARITY_POWER, 0)));
        }
    }

    if (shoulder->category_id == 7) {
        if (creature->entity_data.level != 0) {
            double base_scaling = GetItemScalingValue((uint32_t)shoulder->level, 0);
            base_scaling = base_scaling / GetItemScalingValue(creature->entity_data.level, 0);
            double rarity_scaling = GetItemScalingValue((uint32_t)shoulder->rarity * RARITY_POWER, 0);
            rating += base_scaling * (1 + rarity_scaling / GetItemScalingValue(MAX_RARITY * RARITY_POWER, 0));
        }
    }

    if (gloves->category_id == 5) {
        if (creature->entity_data.level != 0) {
            double base_scaling = GetItemScalingValue((uint32_t)gloves->level, 0);
            base_scaling = base_scaling / GetItemScalingValue(creature->entity_data.level, 0);
            double rarity_scaling = GetItemScalingValue((uint32_t)gloves->rarity * RARITY_POWER, 0);
            rating += base_scaling * (1 + rarity_scaling / GetItemScalingValue(MAX_RARITY * RARITY_POWER, 0));
        }
    }

    if (boots->category_id == 6) {
        if (creature->entity_data.level != 0) {
            double base_scaling = GetItemScalingValue((uint32_t)boots->level, 0);
            base_scaling = base_scaling / GetItemScalingValue(creature->entity_data.level, 0);
            double rarity_scaling = GetItemScalingValue((uint32_t)boots->rarity * RARITY_POWER, 0);
            rating += base_scaling * (1 + rarity_scaling / GetItemScalingValue(MAX_RARITY * RARITY_POWER, 0));
        }
    }

    rating *= 0.2; // divide by 5;

    return_armor_rating = rating;
}

void __declspec(naked) ASMOnCharacterWidgetWeaponRatingUpdate() {
    __asm {
        PUSH_ALL

        call CharacterWidgetWeaponRatingUpdate

        POP_ALL

        movd xmm0, [return_weapon_rating]

        jmp[ASMOnCharacterWidgetWeaponRatingUpdate_jmpback];
    }
}

void __declspec(naked) ASMOnCharacterWidgetArmorRatingUpdate() {
    __asm {
        PUSH_ALL

        call CharacterWidgetArmorRatingUpdate

        POP_ALL

        movd xmm0, [return_armor_rating]

        jmp[ASMOnCharacterWidgetArmorRatingUpdate_jmpback];
    }
}

void SetupOnCharacterWidgetRatingsUpdate() {
    WriteJMP((void*)(base + 0x382CB), (void*)&ASMOnCharacterWidgetWeaponRatingUpdate);
    ASMOnCharacterWidgetWeaponRatingUpdate_jmpback = (void*)(base + 0x38425);
    WriteJMP((void*)(base + 0x38AA4), (void*)&ASMOnCharacterWidgetArmorRatingUpdate);
    ASMOnCharacterWidgetArmorRatingUpdate_jmpback = (void*)(base + 0x38D31);
}
