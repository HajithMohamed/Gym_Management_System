#pragma once
#using <System.dll>

namespace GymManagementSystem {
    public ref class Equipment {
    public:
        int id;
        System::String^ name;
        System::String^ category;
        int quantity;
        bool isAvailable;
        System::DateTime^ lastMaintenanceDate;

        Equipment() {
            id = 0;
            name = "";
            category = "";
            quantity = 0;
            isAvailable = true;
            lastMaintenanceDate = System::DateTime::Now;
        }
    };
}