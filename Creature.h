#pragma once

#include "non_cube.h"

class Creature {
public:
	int vftable;
	int field_4;
	int64_t GUID;

	struct EntityData {
		Vector3<int64_t> position;
		Vector3<float> rotation;
		Vector3<float> velocity;
		Vector3<float> acceleration;
		Vector3<float> retreat_force;
		int head_rotation;

		// 0b00000100 = Touching wall
		uint8_t physics_flags;
		uint8_t field_4D;
		char field_4E;
		char field_4F;
		uint8_t hostility_flags; // 0x50
		uint32_t race;
		uint8_t skill_id;
		int skill_timer;
		int hit_counter;
		int time_since_last_hit;
		struct Appearance {
			char appearance_struct_field_0;
			char field_1;
			uint8_t hair_color_red;
			uint8_t hair_color_green;
			uint8_t hair_color_blue;
			char field_5;
			uint16_t movement_flags;
			float graphical_size;
			float hitbox_size;
			float physical_size;
			uint16_t face_id;
			uint16_t hair_id;
			uint16_t hands_id;
			uint16_t feet_id;
			uint16_t chest_id;
			uint16_t tail_id;
			uint16_t shoulder_id;
			uint16_t wings_id;
			float head_scale;
			float chest_scale;
			float hand_scale;
			float feet_scale;
			float unk_scale;
			float weapon_scale;
			float tail_scale;
			float shoulder_scale;
			float wings_scale;
			int chest_rotation;
			Vector3<float> hands_rotation;
			int feet_rotation;
			int wings_rotation;
			int unk_rotation;
			Vector3<float> chest_position;
			Vector3<float> head_position;
			Vector3<float> hands_position;
			Vector3<float> feet_position;
			Vector3<float> unk_position;
			Vector3<float> wings_position;
		} appearance;

		// 0x0001 = Climbing
		// 0x0010 = Glider
		// 0x0200 = Light
		uint16_t binary_toggles;
		uint16_t field_116;
		int rolling_duration;
		float stun_timer;
		int unknown_effect;
		int ice_spirit_effect;
		int wind_spirit_effect;
		int show_patch_time;
		char char_class;
		char char_specialization;
		char field_132;
		char field_133;
		int special_hit_power_or_charge;
		int field_138;
		int field_13C;
		int field_140;
		int field_144;
		int field_148;
		float field_14C;
		Vector3<float> camera_offset;
		float hp;
		float mp;
		float block_power;
		float hp_multiplier;
		float attack_speed_multiplier;
		float damage_multiplier;
		float armor_multiplier;
		float resistance_multiplier;
		float unk_multiplier;
		int level;
		int experience;
		int64_t parent_owner;
		int field_190;
		int field_194;
		int power_base;
		int field_19C;
		int field_1A0;
		int field_1A4;
		int field_1A8;
		int field_1AC;
		int field_1B0;
		int field_1B4;
		int field_1B8;
		int field_1BC;
		int camera_distance;
		int field_1C4;
		int field_1C8;
		int field_1CC;
		int field_1D0;
		int field_1D4;
		int field_1D8;
		int field_1DC;
		int field_1E0;
		int field_1E4;
		int field_1E8;
		char some_buf[256];
		int field_2EC;
		WornEquipment equipment;
		int skill_level_petmaster;
		int skill_level_riding;
		int skill_level_climbing;
		int skill_level_gliding;
		int skill_level_swimming;
		int skill_level_sailing;
		int skill_level_class_1;
		int skill_level_class_2;
		int skill_level_class_3;
		int skill_level_class_4;
		int skill_level_class_5;
		int field_1154;
		/*
		int64_t field_1158;
		int64_t field_1160;
		*/
		char name[16];
	} entity_data;

	int field_1178;
	int field_117C;
	int field_1180;
	int field_1184;
	int field_1188;
	int field_118C;
	int field_1190;
	float stamina;
	int field_1198;
	int field_119C;
	int field_11A0;
	int field_11A4;
	int field_11A8;
	void* field_11AC_map;
	int field_11B0;
	void* field_11B4_map;
	int field_11B8;
	int field_11BC;
	int field_11C0;
	int field_11C4;
	int field_11C8;
	int field_11CC;
	int field_11D0;
	int field_11D4;
	int field_11D8;
	STDVector Inventory_Tabs_Vec;
	int selected_item_count;
	Item selected_item;
	int money;
	int platinum_coins;
	char other_stuff[0xA1C]; // field_1308
	uint32_t* field_1D28;
	char other_stuff_2[0x130]; // field_1D2C
	int field_1E5C;

};
