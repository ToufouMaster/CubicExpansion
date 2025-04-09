#pragma once
#include "../cube.h"
#include "../scale_functions.h"

void* ASMOnGetItemResistance_jmpback;

// TODO: rebalance the adaption level boost
double __fastcall GetItemResistance(Item* item) {
    int8_t type = item->category_id;

    if (type != 4 && type != 7 && type != 5 && type != 6)
        return 0;

    double multiplier = 0.5;

    if (type == 4) {
        multiplier = 1.0;
    }

    switch (item->material) {
    case 1:
    case 19: {
        multiplier *= 0.85;
        break;
    }
    case 26:
    case 27: {
        multiplier *= 0.75;
        break;
    }
    }

    double resistance = GetItemScalingValue(item->level, item->rarity) * multiplier;

    return resistance * GetRarityMultiplicator(item) * 0.8;
}

void __declspec(naked) ASMOnGetItemResistance() {
    __asm {
        PUSH_ALL

        call GetItemResistance

        POP_ALL

        //original code
        //mov esp, ebp

        jmp[ASMOnGetItemResistance_jmpback];
    }
}

void SetupOnGetItemResistance() {
    WriteJMP((void*)(base + 0xC7AF3), (void*)&ASMOnGetItemResistance);
    ASMOnGetItemResistance_jmpback = (void*)(base + 0xC7BA5);
}
