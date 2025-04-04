#pragma once
#include "../cube.h"
#include "../InventoryWidget.h"

void* ASMOnInventoryWidgetTabUpdate_jmpback;

void __fastcall InventoryWidgetTabUpdate(InventoryWidget* widget) {
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

void __declspec(naked) ASMOnInventoryWidgetTabUpdate() {
    __asm {
        PUSH_ALL

        mov ecx, esi

        call InventoryWidgetTabUpdate

        POP_ALL

        mov ecx, [esi + 0x164]
        jmp[ASMOnInventoryWidgetTabUpdate_jmpback];
    }
}

void SetupOnInventoryWidgetTabUpdate() {
    WriteJMP((void*)(base + 0xc5b96), (void*)&ASMOnInventoryWidgetTabUpdate, 6);
    ASMOnInventoryWidgetTabUpdate_jmpback = (void*)(base + 0xc5b9c);
}
