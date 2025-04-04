#pragma once
#include "../cube.h"

void* ASMOnTemporaryFunctionDebug_jmpback;

void __fastcall TemporaryFunctionDebug(Creature* creature) {
    creature->entity_data.level = 99999;
}

void __declspec(naked) ASMOnTemporaryFunctionDebug() {
    __asm {
        PUSH_ALL

        mov ecx, esi

        call TemporaryFunctionDebug

        POP_ALL

        jmp[ASMOnTemporaryFunctionDebug_jmpback];
    }
}

void SetupOnTemporaryFunctionDebug() {
    WriteJMP((void*)(base + 0x210025), (void*)&ASMOnTemporaryFunctionDebug);
    ASMOnTemporaryFunctionDebug_jmpback = (void*)(base + 0x21002b);
}
