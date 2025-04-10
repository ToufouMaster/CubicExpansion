#pragma once
#include <iostream>
#include "cube.h"

const int RARITY_POWER = 20;
const int MAX_RARITY = 4;

static double GetScaleValue(double level) {
    return pow(level, 1.3);
}

double GetItemScalingValue(float level, int32_t rarity) {
    double scaling_value = GetScaleValue(level); //  + ((float)RARITY_POWER * rarity)
    return scaling_value;
}

bool IsItemEquipedByCreature(Item* item, Creature* creature) {
    if (&creature->entity_data.equipment.left_weapon == item) return true;
    if (&creature->entity_data.equipment.right_weapon == item) return true;
    if (&creature->entity_data.equipment.left_ring == item) return true;
    if (&creature->entity_data.equipment.right_ring == item) return true;
    if (&creature->entity_data.equipment.chest == item) return true;
    if (&creature->entity_data.equipment.feet == item) return true;
    if (&creature->entity_data.equipment.hands == item) return true;
    if (&creature->entity_data.equipment.light == item) return true;
    if (&creature->entity_data.equipment.necklace == item) return true;
    if (&creature->entity_data.equipment.pet == item) return true;
    if (&creature->entity_data.equipment.shoulder == item) return true;
    if (&creature->entity_data.equipment.special == item) return true;
    return false;
}

bool IsItemHoveredInInventory(Item* item) {
    Item* list_item = nullptr;

    // Inventory
    InventoryWidget* widget = ((InventoryWidget**)GetGameController())[0x200255];
    if (not (widget == nullptr || widget->itemstack_list_vector == nullptr || widget->hovered_category_id == -1 || widget->hovered_item_id == -1)) {
        list_item = &widget->itemstack_list_vector->at(widget->hovered_category_id).at(widget->hovered_item_id).item;
        if (item->IsItemSimilar(list_item)) return true;
    }

    // Craft
    widget = ((InventoryWidget**)GetGameController())[0x200256];
    if (not (widget == nullptr || widget->itemstack_list_vector == nullptr || widget->hovered_category_id == -1 || widget->hovered_item_id == -1)) {
        list_item = &widget->itemstack_list_vector->at(widget->hovered_category_id).at(widget->hovered_item_id).item;
        if (item->IsItemSimilar(list_item)) return true;
    }

    // Shop
    widget = ((InventoryWidget**)GetGameController())[0x200257];
    if (not (widget == nullptr || widget->itemstack_list_vector == nullptr || widget->hovered_category_id == -1 || widget->hovered_item_id == -1)) {
        list_item = &widget->itemstack_list_vector->at(widget->hovered_category_id).at(widget->hovered_item_id).item;
        if (item->IsItemSimilar(list_item)) return true;
    }

    return false;
}

bool IsItemInteractingPickupableItem(Item* item) {
    void* gc = GetGameController();
    char* world = ((char*)gc) + 0x2E4;
    int32_t zone_x = ((int32_t*)gc)[0x20029E];
    int32_t zone_y = ((int32_t*)gc)[0x20029F];
    int32_t idx = ((int32_t*)gc)[0x2002A0];
    if (zone_x == -1 && zone_y == -1 && idx == -1) return false;

    typedef Zone* (__thiscall* GetZone_t)(void* world, int x, int y);
    auto GetZone = (GetZone_t)(base + 0x34D10);

    Zone* cur_zone = GetZone((void*)world, zone_x, zone_y);
    if (cur_zone == nullptr) return false;
    zone_pickupable_object* object = &cur_zone->pickupable_objects.at(idx);
    
    return item->IsItemSimilar(&object->item);
}

double GetRarityMultiplicator(Item* item, bool force = false) {
    double rarity = item->rarity * 0.25;
    double multiplicator = 1.0;
    if (IS_SERVER) force = true;
    if (force) return multiplicator + rarity;
    Creature* creature = GetLocalCreature(GetGameController());

    if ((not IsItemEquipedByCreature(item, creature) && not IsItemHoveredInInventory(item))) {
        if (not IsItemInteractingPickupableItem(item)) {
            return multiplicator + rarity;
        }
    }

    int level_difference = creature->entity_data.level - item->level;
    if (level_difference > 10) {
        rarity *= max(0, 1 - (level_difference - 10) * 0.1);
    }
    return multiplicator + rarity;
}
