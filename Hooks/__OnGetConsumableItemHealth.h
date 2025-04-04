#pragma once
#include "../cube.h"
#include "../scale_functions.h"

void* ASMOnGetConsumableItemHealth_jmpback;

// TODO: rebalance the adaption level boost
double __fastcall GetConsumableItemHealth(Item* item) {
    int8_t type = item->category_id;

    if (type == 1) {
        switch (item->item_id) {
        case 1:
        case 2:
        case 4:
        case 5:
        case 6: {
            return GetCreatureBaseMaxHealth(item->level + RARITY_POWER*item->rarity, 0, 0)*1.1;
            //return 200 + GetItemScalingValue(item->level, item->rarity) * 30.0; // 20
        }
        case 8:
        case 9: {
            return (GetCreatureBaseMaxHealth(item->level + RARITY_POWER*item->rarity, 0, 0) / 2.0) * 1.1;
            //return 100 + GetItemScalingValue(item->level, item->rarity) * 15.0; // 15
        }
        }
    }

    return 0;
}

void __declspec(naked) ASMOnGetConsumableItemHealth() {
    __asm {
        PUSH_ALL

        call GetConsumableItemHealth

        POP_ALL

        //original code
        //mov esp, ebp

        jmp[ASMOnGetConsumableItemHealth_jmpback];
    }
}

void SetupOnGetConsumableItemHealth() {
    WriteJMP((void*)(base + 0xC6E13), (void*)&ASMOnGetConsumableItemHealth);
    ASMOnGetConsumableItemHealth_jmpback = (void*)(base + 0xC6EE9);
}
