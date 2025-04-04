#include "CubicExpansion.h"

/*
Most CubeWorld structs come from Andoryuuta's cwsdk for alpha
https://github.com/Andoryuuta/cwsdk
Thanks for his amazing job
*/

using namespace std;

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

    SetupOnGetConsumableItemHealth();

    SetupOnGetCreaturePower();
    SetupOnGetItemPower();
    SetupOnGetItemHealth();
    SetupOnGetItemDamage();
    SetupOnGetItemArmor();
    SetupOnGetItemResistance();
    SetupOnGetItemRegeneration();

    SetupOnGetCoinAmount();
    SetupOnRessourceCreatureGetItemDrop();

    return 0;
}

extern "C" BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    base = (UINT_PTR)GetModuleHandle(NULL);

    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SetupHooks, 0, 0, NULL);
        break;
    }
    return TRUE;
}