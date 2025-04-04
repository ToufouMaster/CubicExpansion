#pragma once
#include "../cube.h"
#include "../InventoryWidget.h"

void* ASMOnUpdateCraftingInventoryItems_jmpback;

void __fastcall UpdateCraftingInventoryItems(uint32_t* game_controller) {
    InventoryWidget* widget = (InventoryWidget*)game_controller[0x200256]; // 0x800958

    // TODO: Make this change
    // This code might be put when changing which page is opened instead of when tab is open.
    // Check if opened tab is consumables
    if (widget->inventory_type == CRAFT) {
        widget->item_box_height = 40;
        if (widget->selected_category_button_id == 3 or widget->selected_category_button_id == 4) {
            widget->item_box_width = 100;
        }
        else { // Makes everything else behave normally
            widget->item_box_width = 300;
        }
    }
}

void __declspec(naked) ASMOnUpdateCraftingInventoryItems() {
    __asm {
        PUSH_ALL

        mov ecx, ebx

        call UpdateCraftingInventoryItems

        POP_ALL

        mov ecx, [ebx+0x800958]
        jmp[ASMOnUpdateCraftingInventoryItems_jmpback];
    }
}

void SetupOnUpdateCraftingInventoryItems() {
    WriteJMP((void*)(base + 0xA186f), (void*)&ASMOnUpdateCraftingInventoryItems, 6);
    ASMOnUpdateCraftingInventoryItems_jmpback = (void*)(base + 0xA1875);
}
