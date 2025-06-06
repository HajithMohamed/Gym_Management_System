#pragma once
#using <System.dll>

namespace GymManagementSystem {
    public ref class GymHall {
    public:
        int id;
        System::String^ name;
        System::String^ location;
        int capacity;
        bool isAvailable;

        GymHall() {
            id = 0;
            name = "";
            location = "";
            capacity = 0;
            isAvailable = true;
        }
    };
}