#pragma once	

#include <windows.h>
#include <iostream>

#include "Hooks/__OnTemporaryFunctionDebug.h"
#include "Hooks/__OnAddingPotionCraftKnowledge.h"
#include "Hooks/__OnUpdateCraftingInventoryItems.h"
#include "Hooks/__OnInventoryWidgetTabUpdate.h"
#include "Hooks/__OnSetCraftItemCraftingComponents.h"

#include "Hooks/__OnCanCreatureEquipItem.h"
#include "Hooks/__OnCharacterWidgetRatingsUpdate.h"

#include "Hooks/__OnGetCreatureMaxHealth.h"
#include "Hooks/__OnGetCreatureDamage.h"
#include "Hooks/__OnGetCreatureArmor.h"
#include "Hooks/__OnGetCreatureResistance.h"

#include "Hooks/__OnGetConsumableItemHealth.h"

#include "Hooks/__OnGetCreaturePower.h"
#include "Hooks/__OnGetItemPower.h"
#include "Hooks/__OnGetItemHealth.h"
#include "Hooks/__OnGetItemDamage.h"
#include "Hooks/__OnGetItemArmor.h"
#include "Hooks/__OnGetItemResistance.h"
#include "Hooks/__OnGetItemRegeneration.h"
#include "Hooks/__OnGetItemCoinValue.h"

#include "Hooks/__OnGetCoinAmount.h"
#include "Hooks/__OnRessourceCreatureGetItemDrop.h"

#include "Hooks/CreatureSkills/__OnGetCreatureM1SkillId.h"
#include "Hooks/CreatureSkills/__OnGetCreatureM2SkillId.h"

#include "cube.h"
#include "non_cube.h"
#include "scale_functions.h"

bool IsItemEquipedByCreature(Item* item, Creature* creature);