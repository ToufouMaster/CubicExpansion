#pragma once
#include "../cube.h"

void* ASMOnTemporaryFunctionDebug_jmpback;

void __fastcall TemporaryFunctionDebug(Creature* creature) {
    creature->entity_data.level = 99999;
}

Field* __stdcall TemporaryGetFieldFunctionDebug(uint32_t x, uint32_t y, void* zone) {
    typedef Field* (__stdcall* GetField_t)(uint32_t x, uint32_t y, void* zone);
    GetField_t GetField = (GetField_t)(base + 0x347a0);
    Field* field = GetField(x, y, zone);
    return field;
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


void __declspec(naked) ASMOnTemporaryGetFieldFunctionDebug() {
    __asm {
        PUSH_ALL

        push esi
        push edx
        push ecx

        call TemporaryGetFieldFunctionDebug

        POP_ALL

        jmp[ASMOnTemporaryFunctionDebug_jmpback];
    }
}

void SetupOnTemporaryFunctionDebug() {
    //WriteJMP((void*)(base + 0x210025), (void*)&ASMOnTemporaryFunctionDebug);
    //ASMOnTemporaryFunctionDebug_jmpback = (void*)(base + 0x21002b);
    WriteJMP((void*)(base + 0x4e7d2), (void*)&ASMOnTemporaryGetFieldFunctionDebug);
    ASMOnTemporaryFunctionDebug_jmpback = (void*)(base + 0x4e7d7);
}
