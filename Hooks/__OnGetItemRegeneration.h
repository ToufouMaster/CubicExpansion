#pragma once
#include "../cube.h"
#include "../scale_functions.h"

void* ASMOnGetItemRegeneration_jmpback;

// TODO: rebalance the adaption level boost
double __fastcall GetItemRegeneration(Item* item) {
    uint8_t type = item->category_id;

    if (type != 3 && type != 4 && type != 7 && type != 5 && type != 6)
        return 0;

    double multiplier = 0.01;

    if (type == 4) {
        multiplier = 0.2;
    }

    uint32_t fake_random_modifier = (item->modifier * 8) % 0x15; // predictable but seemingly random
    double temp = 0.0;
    if (fake_random_modifier < 0x80000000) { // is int(fake_random_modifier) positive
        temp = -1.5;
    }

    double multiplier2 = 1.0 - (((fake_random_modifier)) + temp) / 20.0;

    switch (item->material) {
    case 26: {
        multiplier2 += 0.5;
        break;
    }
    case 27: {
        multiplier2 += 1.0;
        break;
    }
    }

    double regeneration = GetItemScalingValue(item->level, item->rarity) * 5.0 * multiplier * multiplier2;

    return regeneration;
}

void __declspec(naked) ASMOnGetItemRegeneration() {
    __asm {
        PUSH_ALL

        call GetItemRegeneration

        POP_ALL

        //original code
        //mov esp, ebp

        jmp[ASMOnGetItemRegeneration_jmpback];
    }
}

void SetupOnGetItemRegeneration() {
    WriteJMP((void*)(base + 0xC78C3), (void*)&ASMOnGetItemRegeneration);
    ASMOnGetItemRegeneration_jmpback = (void*)(base + 0xC79A4);
}
