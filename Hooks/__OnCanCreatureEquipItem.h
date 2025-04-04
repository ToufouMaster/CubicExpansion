#pragma once
#include "../cube.h"
#include "../scale_functions.h"
#include "__OnGetItemPower.h"
#include "__OnGetCreaturePower.h"

void* ASMOnCanCreatureEquipItem_jmpback;
bool return_can_equip;

bool __fastcall CanCreatureEquipItem(Creature* creature, Item* item) {
    typedef bool (__thiscall* IsItemSameClassAsCreature_t)(Item*, int32_t);
    auto IsItemSameClassAsCreature = (IsItemSameClassAsCreature_t)(base + 0xC6F20);

    if (GetItemPower(item) <= GetCreaturePower(creature)) {
        return IsItemSameClassAsCreature(item, creature->entity_data.char_class) != 0;
    }

    return false;
}

void __declspec(naked) ASMOnCanCreatureEquipItem() {
    __asm {
        PUSH_ALL

        mov edx, [ebp + 8]

        call CanCreatureEquipItem

        mov[return_can_equip], al

        POP_ALL

        mov al, [return_can_equip]

        jmp[ASMOnCanCreatureEquipItem_jmpback];
    }
}

void SetupOnCanCreatureEquipItem() {
    WriteJMP((void*)(base + 0x3E423), (void*)&ASMOnCanCreatureEquipItem);
    ASMOnCanCreatureEquipItem_jmpback = (void*)(base + 0x3e493);
}
