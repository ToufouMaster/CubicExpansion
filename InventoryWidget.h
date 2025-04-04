#pragma once
#include "plasma.h"
#include "msvc_bincompat.h"

enum InventoryType {
    INVENTORY,
    SHOPINVENTORY,
    CRAFT,
    SHOP,
};

class InventoryWidget : Widget {
public:
    int32_t field_0x15c;
    MSVCBinCompat::vector<MSVCBinCompat::vector<ItemStack>>* itemstack_list_vector;
    void* game_controller;
    Node* node_1;
    Node* node_2;
    Node* node_3;
    Node* node_4;
    Node* node_5;
    int32_t field_0x17c;
    int32_t field_0x180;
    int32_t hovered_category_id;
    int32_t hovered_item_id;
    int32_t selected_category_id;
    int32_t selected_item_id;
    int32_t inventory_type;
    MSVCBinCompat::vector<uint32_t> item_category_scrolling_vector;
    int32_t field_0x1a4;
    int32_t item_box_width;
    int32_t item_box_height;
    int32_t hover_category_button_id;
    int32_t selected_category_button_id;
};