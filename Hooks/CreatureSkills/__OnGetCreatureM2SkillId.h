#pragma once
#include "../../cube.h"

void* ASMOnGetCreatureM2SkillID_jmpback;
int32_t return_m2_skill_id;

int32_t __fastcall GetCreatureM2SkillID(Creature* creature) {
    uint8_t category = creature->entity_data.equipment.right_weapon.category_id;
    uint8_t item_id = creature->entity_data.equipment.right_weapon.item_id;

    int32_t hit_counter = creature->entity_data.hit_counter & 0x80000001;
    bool is_odd_hit = (hit_counter < 0 && hit_counter & 1) ? true : false;

    if (category == 3 && item_id == 6)
        return Creature::Animations::DaggerM2;

    if (creature->entity_data.char_class != Creature::CharClass::Mage) {
        uint32_t race = creature->entity_data.race;

        if (race != 0x75 && race != 0x56) {
            if (category != 3) {
                return Creature::Animations::AltDaggerM1a + is_odd_hit;
            }

            if (item_id != 0xa && item_id != 0xb && item_id != 0xc) {
                if (category != 0) {
                    if (item_id == 5) {
                        return Creature::Animations::LongswordM2;
                    }

                    if (category == 3) {
                        switch (item_id) {
                        case 0xf:
                        case 0x10:
                        case 0x11:
                        case 0x5:
                        case 0xa:
                        case 0xb:
                        case 0x12:
                        case 0x8:
                        case 0x6:
                        case 0x7: {
                            return Creature::Animations::Cyclone + is_odd_hit;
                        }
                        }
                    }
                }

                return Creature::Animations::AltDaggerM1a + is_odd_hit;
            }
        }
    }

    uint32_t specialization = creature->entity_data.char_specialization;

    if (item_id == 0xb) {
        return Creature::Animations::FireRayM2;
        /* ORIGINAL CODE
        if (specialization == 1) {
            return Creature::Animations::WandWaterM2;
        }
        else {
            return Creature::Animations::WandFireM2;
        }*/
    }

    if (item_id == 0xa) {
        if (specialization == 1) {
            return Creature::Animations::StaffWaterM2;
        }
        else {
            return Creature::Animations::StaffFireM2;
        }
    }

    if (specialization == 1) {
        return Creature::Animations::BraceletWaterM2;
    }

    return Creature::Animations::BraceletFireM2;
}

void __declspec(naked) ASMOnGetCreatureM2SkillID() {
    __asm {
        PUSH_ALL

        call GetCreatureM2SkillID

        mov[return_m2_skill_id], eax;

        POP_ALL

        mov eax, [return_m2_skill_id];

        jmp[ASMOnGetCreatureM2SkillID_jmpback];
    }
}

void SetupOnGetCreatureM2SkillID() {
    WriteJMP((void*)(base + 0x452A0), (void*)&ASMOnGetCreatureM2SkillID);
    ASMOnGetCreatureM2SkillID_jmpback = (void*)(base + 0x453AB);
}
