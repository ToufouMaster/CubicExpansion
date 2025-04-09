#pragma once

class Zone {
public:
    int32_t vftable;
    int32_t field_4;
    int32_t field_8;
    struct MSVCBinCompat::vector<zone_static_object> static_objects;
    struct MSVCBinCompat::vector<void*> creature_data_unk_list;
    int32_t field_24;
    int32_t field_28;
    int32_t field_2C;
    struct MSVCBinCompat::vector<zone_pickupable_object> pickupable_objects;
    int32_t field_3C;
    int32_t field_40;
    int32_t field_44;
    int32_t field_48;
    int32_t field_4C;
    int32_t field_50;
    int32_t field_54;
    int32_t field_58;
    int32_t field_5C;
    int32_t posx;
    int32_t posy;
    int32_t field_68;
    int32_t field_6C;
    int32_t field_70;
    int32_t field_74;
    int32_t field_78;
    int32_t field_7C;
    int32_t field_80;
    int32_t field_84;
    int32_t field_88;
    int32_t field_8C;
    int32_t field_90;
    int32_t field_94;
    int32_t field_98;
    int32_t field_9C;
    int32_t field_A0;
    int32_t field_A4;
    struct Field* fields;
    int32_t field_AC;
    int32_t field_B0;
    int32_t field_B4;
    int32_t field_B8;
    int32_t field_BC;
    int32_t field_C0;
    int32_t field_C4;
};