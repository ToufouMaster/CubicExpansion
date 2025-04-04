#pragma once
#include "../cube.h"
#include "../InventoryWidget.h"

void* ASMOnRessourceCreatureGetItemDrop_jmpback;
void* ASMOnRessourceCreatureGetItemDropLoop_jmpback;

void SetItemDataToSoulFlower(Item* item_data, float* drop_size) {
    if (item_data->category_id == 0xb) {
        // Loot soul flower item
        if ((rand() % 3) == 0) { // 1/3 odds
            item_data->category_id = 0xb; // 11 (Material)
            item_data->item_id = 0x19; // 25 (SoulFlower)
            item_data->material = 0x0;
            item_data->rarity = 1; // 40%
            int rarity_value = (rand() % 10);
            if (rarity_value < 6)
                item_data->rarity = 2; // 30%
            if (rarity_value < 3)
                item_data->rarity = 3; // 20%
            if (rarity_value == 0)
                item_data->rarity = 4; // 10%
            *drop_size = 0.8f;
        }
    }
}

void __fastcall RessourceCreatureGetItemDrop(Item* item_data, Creature* creature, float* size) {
    //item_data->category_id = 11; // ressource/ingredient/material

    uint32_t race = creature->entity_data.race;
    float drop_size = *size;
    item_data->level = 1;

    if (race <= 0x8b && race >= 0x3a) {
        switch (race) {
        case 0x3a: {
            item_data->category_id = 0xb;
            item_data->item_id = 2;
            item_data->material = 0x13;
            drop_size = 0.8f;
            break;
        }
        case 0x46: {
            item_data->category_id = 0xb;
            item_data->item_id = 0x12;
            drop_size = 0.8f;
            break;
        }
        case 0x47: {
            item_data->category_id = 0xb;
            item_data->item_id = 0x15;
            drop_size = 0.8f;
            break;
        }
        case 0x78:
        case 0x79:
        case 0x7c: 
        case 0x7e: {
            int32_t eax_57 = rand() & 0x80000001;
            bool cond_11_1 = eax_57 == 0;

            if (eax_57  < 0) {
                cond_11_1 = ((eax_57 - 1) | 0xfffffffe) == 0xffffffff;
            }

            if (cond_11_1) {
                item_data->category_id = 0xb;
                item_data->item_id = 5;
                item_data->material = 0x15;
                drop_size = 0.8f;
            }
            else {
                item_data->category_id = 0xb;
                item_data->item_id = 1;
                item_data->material = 2;
                drop_size = 0.8f;
            }
            SetItemDataToSoulFlower(item_data, &drop_size);
            break;
        }
        case 0x7a: {
            item_data->category_id = 0xb;
            item_data->item_id = 0x1b;
            item_data->material = 0;
            drop_size = 0.8f;
            SetItemDataToSoulFlower(item_data, &drop_size);
            break;
        }
        case 0x7b: {
            item_data->category_id = 0xb;
            item_data->item_id = 0xb;
            item_data->material = 0x1b;
            drop_size = 0.8f;
            SetItemDataToSoulFlower(item_data, &drop_size);
            break;
        }
        case 0x7d: {
            item_data->category_id = 0xb;
            item_data->item_id = 6;
            item_data->material = 0;
            drop_size = 0.8f;
            SetItemDataToSoulFlower(item_data, &drop_size);
            break;
        }
        case 0x7f: {
            item_data->category_id = 0xb;
            item_data->item_id = 0x14;
            drop_size = 0.8f;
            SetItemDataToSoulFlower(item_data, &drop_size);
            break;
        }
        case 0x80: {
            item_data->category_id = 0xb;
            item_data->item_id = 0x17;
            drop_size = 0.8f;
            SetItemDataToSoulFlower(item_data, &drop_size);
            break;
        }
        case 0x83: {
            item_data->category_id = 0xb;
            item_data->item_id = 0x0;
            item_data->material = 0xb;
            drop_size = 1.5f;
            break;
        }
        case 0x84: {
            item_data->category_id = 0xb;
            item_data->item_id = 0x0;
            item_data->material = 0x1;
            drop_size = 1.5f;
            break;
        }
        case 0x85: {
            item_data->category_id = 0xb;
            item_data->item_id = 0x0;
            item_data->material = 0xc;
            drop_size = 1.5f;
            break;
        }
        case 0x86: {
            item_data->category_id = 0xb;
            item_data->item_id = 0x0;
            item_data->material = 0x11;
            drop_size = 1.5f;
            break;
        }
        case 0x87: {
            item_data->category_id = 0xb;
            item_data->item_id = 0x0;
            item_data->rarity = 0x1;
            item_data->material = 0xd;
            drop_size = 1.5f;
            break;
        }
        case 0x88: {
            item_data->category_id = 0xb;
            item_data->item_id = 0x0;
            item_data->rarity = 0x2;
            item_data->material = 0xe;
            drop_size = 1.5f;
            break;
        }
        case 0x89: {
            item_data->category_id = 0xb;
            item_data->item_id = 0x0;
            item_data->rarity = 0x3;
            item_data->material = 0xf;
            drop_size = 1.5f;
            break;
        }
        case 0x8a: {
            item_data->category_id = 0xb;
            item_data->item_id = 0x0;
            item_data->rarity = 0x4;
            item_data->material = 0x10;
            drop_size = 1.5f;
            break;
        }
        case 0x8b: {
            item_data->category_id = 0xb;
            item_data->item_id = 8;
            item_data->material = 0x16;
            drop_size = 0.8f;
            break;
        }
    }
    }

    size = &drop_size;
}

void __declspec(naked) ASMOnRessourceCreatureGetItemDrop() {
    __asm {
        PUSH_ALL

        lea ecx, [ebp - 0x164]
        //mov ecx, eax
        mov edx, ebx
        push [ebp-0x168] // size

        call RessourceCreatureGetItemDrop

        mov al, byte ptr [ebp - 0x164]
        test al, al
        jz jumploop

        POP_ALL

        jmp[ASMOnRessourceCreatureGetItemDrop_jmpback];

        jumploop:
            POP_ALL
            jmp [ASMOnRessourceCreatureGetItemDropLoop_jmpback]
    }
}

void SetupOnRessourceCreatureGetItemDrop() {
    WriteJMP((void*)(base + 0x19b737), (void*)&ASMOnRessourceCreatureGetItemDrop, 9);
    ASMOnRessourceCreatureGetItemDrop_jmpback = (void*)(base + 0x19b89e);
    ASMOnRessourceCreatureGetItemDropLoop_jmpback = (void*)(base + 0x19bb28);
}
