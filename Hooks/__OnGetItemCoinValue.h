#pragma once
#include "../cube.h"
//#include "../plasma.h"
#include "../scale_functions.h"
#include "__OnGetCoinAmount.h"

void* ASMOnGetItemCoinValue_jmpback;
int32_t return_item_coin_value;

int32_t __fastcall GetItemCoinValue(Item* item) {
    int32_t value = GetCoinAmount(item->level, item->rarity) * 10 * 3;
    uint32_t item_id = item->item_id;

    switch (item->category_id) {
    case 1: {
        value /= 5;
        break;
    }
    case 2: {
        value /= 3;
        break;
    }
    case 3: {
        if (item_id == 0xf || item_id == 0x10 || item_id == 0x11 || item_id == 5 || item_id == 0xa || item_id == 0xb || item_id == 0x12 || item_id == 8 || item_id == 6 || item_id == 7) {
            value *= 2;
        }
        break;
    }
    case 4: {
        value *= 2;
        break;
    }

    case 11: { // Materials such as bottles
        value = 10;
        break;
    }

    case 20: { // Materials such as bottles
        value = 500;
        break;
    }

    case 23: { // Boat and Glider
        value = 1000; // 10 silvers
        break;
    }


    case 24: { // Lamps
        value = 50; // 50c Common, 5s Uncommon, 50s Rare, 5g Epic, 50g Legendary
        for (int i = 0; i < item->rarity; i++) {
            value *= 10;
        }
        break;
    }
    }

    /* DOES NOT WORK (find the function that give the value to each item.)
    InventoryWidget* shop_widget = ((InventoryWidget**)GetGameController())[0x200257];
    if (not (shop_widget == nullptr)) {
        if (shop_widget->selected_category_id == 1) value /= 4;
    }*/

    return max(1, value);
}


void __declspec(naked) ASMOnGetItemCoinValue() {
    __asm {
        PUSH_ALL

        call GetItemCoinValue

        mov [return_item_coin_value], eax

        POP_ALL

        mov eax, [return_item_coin_value]

        jmp[ASMOnGetItemCoinValue_jmpback];
    }
}

void SetupOnGetItemCoinValue() {
    WriteJMP((void*)(base + 0xC76E6), (void*)&ASMOnGetItemCoinValue);
    ASMOnGetItemCoinValue_jmpback = (void*)(base + 0xC77F6);
}
