#pragma once
#include "../cube.h"
#include "../scale_functions.h"
#include "__OnGetItemPower.h"

void* ASMOnGetCreaturePower_jmpback;
int return_creature_power;

int __fastcall GetCreaturePower(Creature* creature) {
    return creature->entity_data.level;
}

void __declspec(naked) ASMOnGetCreaturePower() {
    __asm {
        PUSH_ALL

        call GetCreaturePower

        mov[return_creature_power], eax

        POP_ALL

        mov eax, [return_creature_power]

        jmp[ASMOnGetCreaturePower_jmpback];
    }
}

void SetupOnGetCreaturePower() {
    WriteJMP((void*)(base + 0x45f10), (void*)&ASMOnGetCreaturePower);
    ASMOnGetCreaturePower_jmpback = (void*)(base + 0x45f51);
}
