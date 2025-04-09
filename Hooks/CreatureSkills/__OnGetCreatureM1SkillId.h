#pragma once
#include "../../cube.h"

void* ASMOnGetCreatureM1SkillID_jmpback;
int32_t return_m1_skill_id;

int32_t __fastcall GetCreatureM1SkillID(Creature* creature) {

    typedef int32_t (__fastcall* GetAnimationLengthInMS_t)(Creature* creature);
    auto GetAnimationLengthInMS = (GetAnimationLengthInMS_t)(base + 0x3d1a0);

    typedef bool(__fastcall* IsWearingOneHandedWeapon_t)(Creature*);
    auto IsWearingOneHandedWeapon = (IsWearingOneHandedWeapon_t)(base + 0x44230);

    uint32_t right_category = creature->entity_data.equipment.right_weapon.category_id;
    uint32_t left_category = creature->entity_data.equipment.left_weapon.category_id;
    uint32_t right_item_id = creature->entity_data.equipment.right_weapon.item_id;
    uint32_t left_item_id = creature->entity_data.equipment.left_weapon.item_id;

    if (creature->entity_data.char_class != Creature::CharClass::Mage) {
        uint32_t race = creature->entity_data.race;

        if (race != 0x75 && race != 0x56) {
            if ((right_category != 3) || (right_item_id != 0xa && right_item_id != 0xb && right_item_id != 0xc)) {
                //d5074
                if (race != 0x68) {
                    if ((right_category != 3) || (right_item_id != 6 && right_item_id != 7)) {
                        //d5091
                        if (left_category == 3) {
                            if (left_item_id == 6 || left_item_id == 7) {
                                return Creature::Animations::ShootArrow;
                            }
                        }

                        if (right_item_id == 3) {
                            if (creature->entity_data.skill_id == Creature::Animations::DaggerM1b) {
                                int32_t cooldown = GetAnimationLengthInMS(creature) + 200;

                                if (creature->entity_data.skill_timer < cooldown) {
                                    return Creature::Animations::DaggerM1a;
                                }
                            }
                            return Creature::Animations::DaggerM1b;
                        }

                        if (right_item_id == 4 || right_item_id == 0) {
                            if (creature->entity_data.skill_id == Creature::Animations::FistM1a) {
                                int32_t cooldown = GetAnimationLengthInMS(creature) + 200;

                                if (creature->entity_data.skill_timer < cooldown) {
                                    return Creature::Animations::FistM1b;
                                }
                            }
                            return Creature::Animations::FistM1a;
                        }

                        if (right_item_id == 5) {
                            if (creature->entity_data.skill_id == Creature::Animations::LongswordM1b) {
                                int32_t cooldown = GetAnimationLengthInMS(creature) + 200;

                                if (creature->entity_data.skill_timer < cooldown) {
                                    return Creature::Animations::LongswordM1a;
                                }
                            }
                            return Creature::Animations::LongswordM1b;
                        }

                        if (right_item_id == 3 || right_item_id == 8) {
                            return Creature::Animations::BoomerangThrow;
                        }

                        if (IsWearingOneHandedWeapon(creature)) {
                            if (creature->entity_data.skill_id == Creature::Animations::GreatweaponM1a) {
                                int32_t cooldown = GetAnimationLengthInMS(creature) + 200;

                                if (creature->entity_data.skill_timer < cooldown) {
                                    return Creature::Animations::GreatweaponM1b;
                                }
                            }

                            if (creature->entity_data.skill_id == Creature::Animations::GreatweaponM1b) {
                                int32_t cooldown = GetAnimationLengthInMS(creature) + 200;

                                if (creature->entity_data.skill_timer < cooldown) {
                                    return Creature::Animations::GreatweaponM1c;
                                }
                            }

                            return Creature::Animations::GreatweaponM1a;
                        }

                        if (left_category == 3 && left_item_id == 0xd) {
                            if (creature->entity_data.skill_id == Creature::Animations::ShieldM1b) {
                                int32_t cooldown = GetAnimationLengthInMS(creature) + 200;

                                if (creature->entity_data.skill_timer < cooldown) {
                                    return Creature::Animations::ShieldM1a;
                                }
                            }
                            return Creature::Animations::ShieldM1b;
                        }

                        if ((creature->entity_data.appearance.movement_flags & 0x10) != 0) {
                            return Creature::Animations::QuadrupedAttack;
                        }

                        if (creature->entity_data.skill_id == Creature::Animations::DualWieldM1a) {
                            int32_t cooldown = GetAnimationLengthInMS(creature) + 200;

                            if (creature->entity_data.skill_timer < cooldown) {
                                return Creature::Animations::DualWieldM1b;
                            }
                        }
                        return Creature::Animations::DualWieldM1a;
                    }
                }

                return Creature::Animations::ShootArrow;
            }
        }
    }

    uint32_t specialization = creature->entity_data.char_specialization;

    if (right_item_id == 0xb) {
        return Creature::Animations::FireBeamM1;
        /* ORIGINAL CODE
        if (specialization == 1) {
            return Creature::Animations::WandWaterM1;
        }
        return Creature::Animations::WandFireM1;
        */
    }

    if (right_item_id == 0xa) {
        if (specialization == 1) {
            return Creature::Animations::StaffWaterM1;
        }
        return Creature::Animations::StaffFireM1;
    }

    if (specialization == 1) {
        if (creature->entity_data.skill_id == Creature::Animations::BraceletsWaterM1b) {
            int32_t cooldown = GetAnimationLengthInMS(creature) + 200;

            if (creature->entity_data.skill_timer < cooldown) {
                return Creature::Animations::BraceletsWaterM1a;
            }
        }
        return Creature::Animations::BraceletsWaterM1b;
    }

    if (creature->entity_data.skill_id == Creature::Animations::BraceletsFireM1b) {
        int32_t cooldown = GetAnimationLengthInMS(creature) + 200;

        if (creature->entity_data.skill_timer < cooldown) {
            return Creature::Animations::BraceletsFireM1a;
        }
    }

    return Creature::Animations::BraceletsFireM1b;
}

void __declspec(naked) ASMOnGetCreatureM1SkillID() {
    __asm {
        PUSH_ALL

        call GetCreatureM1SkillID

        mov[return_m1_skill_id], eax;

        POP_ALL

        mov eax, [return_m1_skill_id];
        
        jmp[ASMOnGetCreatureM1SkillID_jmpback];
    }
}

void SetupOnGetCreatureM1SkillID() {
    WriteJMP((void*)(base + 0x45020), (void*)&ASMOnGetCreatureM1SkillID);
    ASMOnGetCreatureM1SkillID_jmpback = (void*)(base + 0x4529C);
}
