#pragma once
#include "../cube.h"
#include "../scale_functions.h"

void* ASMOnGetItemDamage_jmpback;
void* ASMOnGetItemScalingValue_jmpback;

// When hitting ennemies as a player the calculation work but when looking at stats or being hit by ennemies display negative values.
double __fastcall GetItemDamage(Item* item) { 
    double base_damage = 8.0;
    double item_damage = (0.5 * GetItemScalingValue(item->level, item->rarity) + base_damage);

    uint32_t id = item->item_id;
    if (id >= 3 && id <= 13) {
        switch (id - 3) {
        case 0:
        case 1:
        case 10: {
            return item_damage / 1.8; // 2.0
        }
        case 2: {
            return item_damage;
        }
        }
    }

    if (id != 0xf && id != 0x10 && id != 0x11 && id != 0x5 && id != 0xa && id != 0xb && id != 0x12 && id != 0x8 && id != 0x6 && id != 0x7) {
        return item_damage;
    }

    return item_damage*2;
}

void __declspec(naked) ASMOnGetItemDamage() {
    __asm {
        PUSH_ALL

        call GetItemDamage

        POP_ALL

        //original code
        //mov esp, ebp

        jmp[ASMOnGetItemDamage_jmpback];
    }
}

void __declspec(naked) ASMOnGetItemScalingValue() {
    __asm {
        PUSH_ALL

        call GetItemScalingValue

        POP_ALL

        //original code
        //mov esp, ebp

        jmp[ASMOnGetItemScalingValue_jmpback];
    }
}

void SetupOnGetItemDamage() {
    WriteJMP((void*)(base + 0xC7F63), (void*)&ASMOnGetItemDamage);
    ASMOnGetItemDamage_jmpback = (void*)(base + 0xC8108);

    WriteJMP((void*)(base + 0x45F63), (void*)&ASMOnGetItemScalingValue);
    ASMOnGetItemScalingValue_jmpback = (void*)(base + 0x45FE4);
}
