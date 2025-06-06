#pragma once
#include <string>

namespace GymManagementSystem {
    using namespace System;

    public ref class User {
    public:
        property int Id;
        property String^ Name;
        property String^ Mobile;
        property String^ Password;
    };
}