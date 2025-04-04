#pragma once
#include "../cube.h"
#include "../InventoryWidget.h"

void* ASMOnAddPotionCraftKnowledge_jmpback;

void __fastcall AddPotionCraftKnowledge(uint32_t* game_controller, int32_t level) {
    typedef bool(__thiscall* IsCraftItemKnown_t)(Creature*, Item*);
    auto IsCraftItemKnown = (IsCraftItemKnown_t)(base + 0x44A90);

    typedef uint32_t** (__thiscall* AddItemToKnownCrafts_t)(char*, Item*);
    auto AddItemToKnownCrafts = (AddItemToKnownCrafts_t)(base + 0x4D460);

    Item item = Item();
    item.category_id = 0;
    item.item_id = 0;
    item.modifier = 0;
    item.recipe_dummy_0 = 0;
    item.recipe_dummy_1 = 0;
    item.recipe_dummy_2 = 0;
    item.recipe_dummy_3 = 0;
    item.adapted = 0;
    item.adaption_count = 0;
    memset(&item.customization_data, 0, 0x100);
    item.level = level;
    item.rarity = 0;
    item.material = 0;

    int32_t mod_level = level & 0x80000003;

    Creature* creature = (Creature*)game_controller[0x2001B4]; // 0x8006d0, &item);
    uint32_t* craftData = creature->field_1D28;

    if (mod_level == 1) {
        item.category_id = 1;
        item.item_id = 1;
        for (int i = 0; i <= 4; i++) {
            item.rarity = i;
            if (not IsCraftItemKnown(creature, &item)) {
                AddItemToKnownCrafts((char*)(craftData + 5), &item);
            }
        }
    } else if (mod_level == 3) {
        item.category_id = 1;
        item.item_id = 2;
        for (int i = 0; i <= 4; i++) {
            item.rarity = i;
            if (not IsCraftItemKnown(creature, &item)) {
                AddItemToKnownCrafts((char*)(craftData + 5), &item);
            }
        }
    }
}

void __declspec(naked) ASMOnAddPotionCraftKnowledge() {
    __asm {
        PUSH_ALL

        mov ecx, edi
        mov edx, [ebp + 0x08]

        call AddPotionCraftKnowledge

        POP_ALL

        jmp[ASMOnAddPotionCraftKnowledge_jmpback];
    }
}

void SetupOnAddPotionCraftKnowledge() {
    WriteJMP((void*)(base + 0x7fb5f), (void*)&ASMOnAddPotionCraftKnowledge, 5);
    ASMOnAddPotionCraftKnowledge_jmpback = (void*)(base + 0x7fc59);
}
