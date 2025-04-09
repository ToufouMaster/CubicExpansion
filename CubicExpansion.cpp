#include "CubicExpansion.h"


/*
Most CubeWorld structs come from Andoryuuta's cwsdk for alpha
https://github.com/Andoryuuta/cwsdk
Thanks for his amazing job
*/

using namespace std;
const bool DEBUG = false;

DWORD WINAPI SetupHooks() {
    //DEBUG
    //SetupOnTemporaryFunctionDebug();
    
    
    SetupOnAddPotionCraftKnowledge();
    SetupOnInventoryWidgetTabUpdate();
    SetupOnUpdateCraftingInventoryItems();
    SetupOnSetCraftItemCraftingComponents();

    SetupOnCanCreatureEquipItem();
    SetupOnCharacterWidgetRatingsUpdate();

    SetupOnGetCreatureMaxHealth();
    SetupOnGetCreatureDamage();
    SetupOnGetCreatureArmor();
    SetupOnGetCreatureResistance();

    SetupOnGetConsumableItemHealth();

    SetupOnGetCreaturePower();
    SetupOnGetItemPower();
    SetupOnGetItemHealth();
    SetupOnGetItemDamage();
    SetupOnGetItemArmor();
    SetupOnGetItemResistance();
    SetupOnGetItemRegeneration();
    SetupOnGetItemCoinValue();

    SetupOnGetCoinAmount();
    SetupOnRessourceCreatureGetItemDrop();

    SetupOnGetCreatureM1SkillID();
    SetupOnGetCreatureM2SkillID();

    return 0;
}

DWORD WINAPI MainLoop() {
    SetupHooks();
    while (true) {
        if (DEBUG == false) break;
        if (GetAsyncKeyState((int)'H') & 0x8000) {
            char* gc = (char*)GetGameController();

            char* world = gc + 0x2E4;
            auto critical_section = (LPCRITICAL_SECTION)(world + 0x8000C0);// World + CriticalSection
            EnterCriticalSection(critical_section);

            Creature* player = *(Creature**)(gc + 0x8006D0);

            typedef zone_static_object* (__fastcall* StaticObjectInit_t)(zone_static_object*);
            auto StaticObjectInit = (StaticObjectInit_t)(base + 0x18EAA0);

            typedef Zone* (__thiscall* GetZone_t)(void* world, int x, int y);
            auto GetZone = (GetZone_t)(base + 0x34D10);

            zone_static_object object = zone_static_object();
            StaticObjectInit(&object);

            int zone_x = (player->entity_data.position.X / 65536) / 256;
            int zone_y = (player->entity_data.position.Y / 65536) / 256;
            Zone* cur_zone = GetZone((void*)world, zone_x, zone_y);

            object.type = 0x2D;
            object.cuwo_orientation = 0;
            object.vis_scale = 4.0f;
            object.phys_scale = 4.0f;
            object.height = 5.0f;
            object.position = player->entity_data.position;

            typedef void* (__thiscall* AddStaticObjectToVector_t)(MSVCBinCompat::vector<zone_static_object>* vec, zone_static_object* object);
            auto AddStaticObjectToVector = (AddStaticObjectToVector_t)(base + 0x1A0E00);

            

            AddStaticObjectToVector((MSVCBinCompat::vector<zone_static_object>*)&cur_zone->static_objects, &object);

            LeaveCriticalSection(critical_section);
            Sleep(250);
        }
    }
    return 0;
}

extern "C" BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    base = (UINT_PTR)GetModuleHandle(NULL);

    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainLoop, 0, 0, NULL);
        break;
    }
    return TRUE;
}