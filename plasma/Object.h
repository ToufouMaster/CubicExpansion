#pragma once
#include "../msvc_bincompat.h"

class Object
{
public:
    //void* vftable;
    void* plasma_d3d9engine;
    void* some_nodes_linked_list;
};

class NamedObject : Object
{
public:
    MSVCBinCompat::wstring object_name;
};
