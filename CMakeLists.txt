# CMakeList.txt : CMake project for CubicExpansion, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CubicExpansion")

add_library(CubicExpansion SHARED "CubicExpansion.cpp" "cube.h" "Creature.h" "Hooks/__OnGetCreatureDamage.h" "scale_functions.h" "Hooks/__OnGetItemHealth.h" "Hooks/__OnGetItemDamage.h" "Hooks/__OnGetItemArmor.h" "Hooks/__OnGetItemRegeneration.h" "Hooks/__OnGetItemPower.h" "Hooks/__OnGetItemResistance.h" "Hooks/__OnCanCreatureEquipItem.h" "Hooks/__OnSetCraftItemCraftingComponents.h" "Hooks/__OnGetCoinAmount.h" "Hooks/__OnUpdateCraftingInventoryItems.h" "plasma/Widget.h" "plasma/Node.h" "InventoryWidget.h" "plasma.h" "Hooks/__OnTemporaryFunctionDebug.h" "Hooks/__OnAddingPotionCraftKnowledge.h" "Hooks/__OnInventoryWidgetTabUpdate.h" "Hooks/__OnRessourceCreatureGetItemDrop.h" "Hooks/__OnCharacterWidgetRatingsUpdate.h" "Hooks/__OnGetCreaturePower.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CubicExpansion PROPERTY CXX_STANDARD 20)
endif()