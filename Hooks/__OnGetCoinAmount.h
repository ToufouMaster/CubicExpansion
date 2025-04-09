#pragma once
#include "../cube.h"
#include "../scale_functions.h"

void* ASMOnGetCoinAmount_jmpback;

// The return value of this function is always multiplied by 10 afterward.
double GetCoinAmount(float level, int32_t rarity) {
    return 1 + (level / 10.f) * (1 + (float)rarity/0.25);
}
/* UNUSED
void __declspec(naked) ASMOnGetCoinAmount() {
    __asm {
        PUSH_ALL

        call GetCoinAmount

        POP_ALL

        jmp[ASMOnGetCoinAmount_jmpback];
    }
}*/

void SetupOnGetCoinAmount() {
    WriteCALL((void*)(base + 0x19BCB4), (void*)&GetCoinAmount);
    //ASMOnGetCoinAmount_jmpback = (void*)(base + 0xDFAAB);
}