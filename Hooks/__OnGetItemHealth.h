#pragma once
#include "../cube.h"
#include "../scale_functions.h"

void* ASMOnGetItemHealth_jmpback;

// TODO: rebalance the adaption level boost
double __fastcall GetItemHealth(Item* item) {
    uint8_t type = item->category_id;

    if (type != 3 && type != 4 && type != 7 && type != 5 && type != 6)
        return 0;

    double multiplier = 0.5;

    if (type == 4) {
        multiplier = 1.0;
    }

    uint32_t fake_random_modifier = (item->modifier * 8) % 0x15; // predictable but seemingly random
    double temp = 0.0;
    if (fake_random_modifier < 0x80000000) { // is int(fake_random_modifier) positive
        temp = -1.5;
    }

    double multiplier2 = 1.0 - (((fake_random_modifier)) + temp) / 20.0 + 1.0;

    switch (item->material) {
    case 1: {
        multiplier2 += 1.0;
        break;
    }
    case 26: {
        multiplier2 += 0.5;
        break;
    }
    case 27: {
        multiplier2 += 0.75;
        break;
    }
    }

    double health = GetItemScalingValue(item->level, item->rarity) * 0.5 * multiplier * multiplier2;

    return health;
}

void __declspec(naked) ASMOnGetItemHealth() {
    __asm {
        PUSH_ALL

        call GetItemHealth

        POP_ALL

        //original code
        //mov esp, ebp

        jmp[ASMOnGetItemHealth_jmpback];
    }
}

void SetupOnGetItemHealth() {
    WriteJMP((void*)(base + 0xC70B3), (void*)&ASMOnGetItemHealth);
    ASMOnGetItemHealth_jmpback = (void*)(base + 0xC71B0);
}
