#pragma once
#include "../cube.h"
#include "../scale_functions.h"

void* ASMOnSetCraftItemCraftingComponents_jmpback;
int8_t return_SetCraftItemCraftingComponents_value;

enum CraftTypes {
    NONE,
    WATER,
    UNKNOWN,
    FURNACE,
    ANVIL,
    SPINNING_WEEL,
    LOOM,
    SAW,
    WORKBENCH,
    CAMPFIRE
};

typedef void* (__thiscall* AddIngredientToCraftItem_t)(MSVCBinCompat::vector<ItemStack>*, ReversedItemStack*);
AddIngredientToCraftItem_t AddIngredientToCraftItem;

void AddSoulFlowersToPotionCraft(Item* item, CraftItem* craft_item, ReversedItemStack* itemstack) {
    if (item->rarity == 0) return;
    itemstack->amount = 0x1;
    itemstack->item_id = 0x19;
    itemstack->rarity = item->rarity;
    itemstack->material = 0x0;
    AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
}

void AddRarityGems(Item* item, CraftItem* craft_item, ReversedItemStack* itemstack) {
    if (item->rarity > 0 && item->rarity <= 4) {
        itemstack->rarity = item->rarity;
        itemstack->material = 0xc + item->rarity;

        itemstack->amount = 1;
        itemstack->item_id = 0;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
    }
}

void AddConsumables(Item* item, CraftItem* craft_item, ReversedItemStack* itemstack) {
    switch (item->item_id) {
    case 1: {
        itemstack->amount = 1;
        itemstack->item_id = 0x16;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        itemstack->item_id = 0x1a;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        AddSoulFlowersToPotionCraft(item, craft_item, itemstack);
        break;
    }
    case 2: {
        itemstack->amount = 1;
        itemstack->item_id = 0x17;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        itemstack->item_id = 0xc;
        itemstack->material = 0x18;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        AddSoulFlowersToPotionCraft(item, craft_item, itemstack);
        break;
    }
    case 4: {
        itemstack->amount = 1;
        itemstack->item_id = 0x14;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        craft_item->craft_type = CAMPFIRE;
        break;
    }
    case 5: {
        itemstack->amount = 1;
        itemstack->item_id = 0x1b;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        break;
    }
    case 6: {
        itemstack->amount = 1;
        itemstack->item_id = 0xf;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        itemstack->item_id = 0x15;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        craft_item->craft_type = CAMPFIRE;
        break;
    }
    case 8: {
        itemstack->amount = 1;
        itemstack->item_id = 0x11;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        break;
    }
    case 9: {
        itemstack->amount = 1;
        itemstack->item_id = 0x10;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        craft_item->craft_type = CAMPFIRE;
        break;
    }
    }
}

void AddWeapons(Item* item, CraftItem* craft_item, ReversedItemStack* itemstack) {
    switch (item->item_id) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 13: {
        itemstack->amount = 8;
        itemstack->item_id = 0xa;
        itemstack->material = 1;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        craft_item->craft_type = ANVIL;
        break;
    }
    case 4: {
        itemstack->amount = 6;
        itemstack->item_id = 0xa;
        itemstack->material = 0x1;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        itemstack->amount = 2;
        itemstack->item_id = 0x9;
        itemstack->material = 0x1b;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        craft_item->craft_type = ANVIL;
        break;
    }
    case 5:
    case 15:
    case 16:
    case 17: {
        itemstack->amount = 16;
        itemstack->item_id = 0xa;
        itemstack->material = 1;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        craft_item->craft_type = ANVIL;
        break;
    }
    case 6: {
        itemstack->amount = 15;
        itemstack->item_id = 0xa;
        itemstack->material = 2;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        itemstack->amount = 1;
        itemstack->item_id = 0x9;
        itemstack->material = 0x1a;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        craft_item->craft_type = WORKBENCH;
        break;
    }
    case 7: {
        itemstack->amount = 6;
        itemstack->item_id = 0xa;
        itemstack->material = 1;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        itemstack->amount = 9;
        itemstack->item_id = 0xa;
        itemstack->material = 2;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        itemstack->amount = 1;
        itemstack->item_id = 0x9;
        itemstack->material = 0x1a;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        craft_item->craft_type = WORKBENCH;
        break;
    }
    case 8:
    case 10:
    case 11: {
        itemstack->amount = 16;
        itemstack->item_id = 0xa;
        itemstack->material = 0x2;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        craft_item->craft_type = WORKBENCH;
        break;
    }
    case 12: {
        itemstack->amount = 8;
        itemstack->item_id = 0xa;
        itemstack->material = item->material;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        craft_item->craft_type = ANVIL;
        break;
    }
    }
    AddRarityGems(item, craft_item, itemstack);
}

void ArmorDuplicatedLogic(Item* item, CraftItem* craft_item, ReversedItemStack* itemstack) {
    if (item->material == 1) {
        itemstack->item_id = 0xa;
        itemstack->material = 1;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        craft_item->craft_type = 4;
    }
    else {
        itemstack->material = item->material;
        itemstack->item_id = 9;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        craft_item->craft_type = 6;
    }
    AddRarityGems(item, craft_item, itemstack);
}

void AddChestplates(Item* item, CraftItem* craft_item, ReversedItemStack* itemstack) {
    itemstack->amount = 20;
    ArmorDuplicatedLogic(item, craft_item, itemstack);
}

void AddGloves(Item* item, CraftItem* craft_item, ReversedItemStack* itemstack) {
    itemstack->amount = 6;
    ArmorDuplicatedLogic(item, craft_item, itemstack);
}

void AddBoots(Item* item, CraftItem* craft_item, ReversedItemStack* itemstack) {
    itemstack->amount = 8;
    ArmorDuplicatedLogic(item, craft_item, itemstack);
}

void AddShoulders(Item* item, CraftItem* craft_item, ReversedItemStack* itemstack) {
    itemstack->amount = 8;
    ArmorDuplicatedLogic(item, craft_item, itemstack);
}

void AddAmulets(Item* item, CraftItem* craft_item, ReversedItemStack* itemstack) {
    itemstack->amount = 6;
    itemstack->item_id = 0xa;
    //22d264
    itemstack->material = item->material;
    AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
    AddRarityGems(item, craft_item, itemstack);
}

void AddRings(Item* item, CraftItem* craft_item, ReversedItemStack* itemstack) {
    itemstack->amount = 3;
    itemstack->item_id = 0xa;
    itemstack->material = item->material;
    AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
    AddRarityGems(item, craft_item, itemstack);
}

void AddMaterials(Item* item, CraftItem* craft_item, ReversedItemStack* itemstack) {
    switch (item->item_id) {
    case 9: {
        if (item->material == 0x19) {
            itemstack->item_id = 6;
            itemstack->material = 0;
            itemstack->amount = 1;
            AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
            craft_item->craft_type = SPINNING_WEEL;
        }
        else {
            if (item->material == 0x1a) {
                itemstack->item_id = 5;
                itemstack->material = 0x15;
                itemstack->amount = 1;
                AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
                craft_item->craft_type = SPINNING_WEEL;
            }
            if (item->material == 0x1b) {
                itemstack->item_id = 0xb;
                itemstack->material = 0x1b;
                itemstack->amount = 1;
                AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
                craft_item->craft_type = SPINNING_WEEL;
            }
        }
        break;
    }
    case 10: {
        itemstack->amount = 1;
        if (item->material != 2) {
            itemstack->item_id = 0;
            craft_item->craft_type = FURNACE;
        }
        else {
            itemstack->item_id = 1;
            craft_item->craft_type = SAW;
        }
        itemstack->material = item->material;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        break;
    }
    case 22: {
        itemstack->amount = 1;
        itemstack->item_id = 0x18;
        itemstack->material = 0;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        craft_item->craft_type = CAMPFIRE;
        break;
    }
    case 26: {
        itemstack->amount = 1;
        itemstack->item_id = 0xc;
        itemstack->material = 0x18;
        AddIngredientToCraftItem(&craft_item->crafting_components, itemstack);
        craft_item->craft_type = WATER;
        break;
    }
    }
}

// item is the item selected in the crafting inventory
int __stdcall SetCraftItemCraftingComponents(Item* item, CraftItem* craft_item) {

    typedef Item* (__thiscall* SetItemToItem_t)(Item*, Item*);
    auto SetItemToItem = (SetItemToItem_t)(base + 0x2C5B0);

    SetItemToItem(craft_item, item);

    // TODO: This might be a Craft item need to look in memory.
    ReversedItemStack itemstack = ReversedItemStack();
    itemstack.amount = 0;
    itemstack.category_id = 0xb; // 11 material
    itemstack.item_id = 0;
    itemstack.recipe_dummy_0 = 0;
    itemstack.recipe_dummy_1 = 0;
    itemstack.recipe_dummy_2 = 0;
    itemstack.recipe_dummy_3 = 0;
    itemstack.rarity = 0;
    itemstack.material = 0;
    itemstack.adapted = 0;
    itemstack.adaption_count = 0;
    memset(&itemstack.customization_data, 0, 0x100);
    itemstack.rarity = 0;
    itemstack.level = 1;

    /* 22d4dd
    itemstack.amount = 1
    sub_230d80(&craft_item->crafting_components, &itemstack)
    craft_item->craft_type = 9
    */

    switch (item->category_id) {
    case 1: {
        AddConsumables(item, craft_item, &itemstack);
        break;
    }
    case 3: {
        AddWeapons(item, craft_item, &itemstack);
        break;
    }
    case 4: {
        AddChestplates(item, craft_item, &itemstack);
        break;
    }
    case 5: {
        AddGloves(item, craft_item, &itemstack);
        break;
    }
    case 6: {
        AddBoots(item, craft_item, &itemstack);
        break;
    }
    case 7: {
        AddShoulders(item, craft_item, &itemstack);
        break;
    }
    case 8: {
        AddAmulets(item, craft_item, &itemstack);
        break;
    }
    case 9: {
        AddRings(item, craft_item, &itemstack);
        break;
    }
    case 11: {
        AddMaterials(item, craft_item, &itemstack);
        break;
    }
    }

    return 1;
}

void __declspec(naked) ASMOnSetCraftItemCraftingComponents() {
    __asm {
        PUSH_ALL

        push[ebp + 0xC]
        push[ebp + 0x8]

        call SetCraftItemCraftingComponents

        mov[return_SetCraftItemCraftingComponents_value], al

        POP_ALL

        mov al, [return_SetCraftItemCraftingComponents_value]

        jmp[ASMOnSetCraftItemCraftingComponents_jmpback];
    }
}

void SetupOnSetCraftItemCraftingComponents() {
    AddIngredientToCraftItem = (AddIngredientToCraftItem_t)(base + 0x1A0D80);
    //WriteCALL((void*)(base + 0x7BBA7), (void*)&SetCraftItemCraftingComponents);
    //WriteCALL((void*)(base + 0xA1604), (void*)&SetCraftItemCraftingComponents);
    WriteJMP((void*)(base + 0x19cff9), (void*)&ASMOnSetCraftItemCraftingComponents);
    ASMOnSetCraftItemCraftingComponents_jmpback = (void*)(base + 0x19d55d); // 8 instead of d maybe?
}
//5CE9A1DC