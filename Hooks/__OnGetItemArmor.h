#pragma once
#include "../cube.h"
#include "../scale_functions.h"

void* ASMOnGetItemArmor_jmpback;

// TODO: rebalance the adaption level boost
double __fastcall GetItemArmor(Item* item) {
    int8_t type = item->category_id;

    if (type != 4 && type != 7 && type != 5 && type != 6)
        return 0;

    double multiplier = 0.5;

    if (type == 4) {
        multiplier = 1.0;
    }

    switch (item->material) {
    case 18: {
        multiplier *= 0.8;
        break;
    }
    case 19:
    case 26:
    case 27: {
        multiplier *= 0.85;
        break;
    }
    case 23:
    case 25: {
        multiplier *= 0.75;
        break;
    }
    }

    double armor = GetItemScalingValue(item->level, item->rarity) * multiplier;

    return armor;
}

void __declspec(naked) ASMOnGetItemArmor() {
    __asm {
        PUSH_ALL

        call GetItemArmor

        POP_ALL

        //original code
        //mov esp, ebp

        jmp[ASMOnGetItemArmor_jmpback];
    }
}

void SetupOnGetItemArmor() {
    WriteJMP((void*)(base + 0xC6A93), (void*)&ASMOnGetItemArmor);
    ASMOnGetItemArmor_jmpback = (void*)(base + 0xC6B51);
}
