#pragma once
#using <System.dll>
#include "User.h"

namespace GymManagementSystem {
    public ref class Trainer : public User {
    public:
        System::String^ specialization;
        System::String^ experience;
        System::String^ certification;
        double hourlyRate;

        Trainer() {
            specialization = "";
            experience = "";
            certification = "";
            hourlyRate = 0.0;
        }
    };
}