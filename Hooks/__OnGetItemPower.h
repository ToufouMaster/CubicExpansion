#pragma once
#include "../cube.h"
#include "../scale_functions.h"

void* ASMOnGetItemPower_jmpback;
int32_t return_item_power;

// TODO: rebalance the adaption level boost
int __fastcall GetItemPower(Item* item) {
    return item->level;
}

void __declspec(naked) ASMOnGetItemPower() {
    __asm {
        PUSH_ALL

        call GetItemPower
        mov[return_item_power], eax

        POP_ALL

        mov eax, [return_item_power]

        jmp[ASMOnGetItemPower_jmpback];
    }
}

void SetupOnGetItemPower() {
    WriteJMP((void*)(base + 0xC76A3), (void*)&ASMOnGetItemPower);
    ASMOnGetItemPower_jmpback = (void*)(base + 0xC76D9);
}
