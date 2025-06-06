#pragma once
#using <System.dll>
#include "Customer.h"
#include "Trainer.h"

namespace GymManagementSystem {
    public ref class ExercisePlan {
    public:
        int id;
        System::String^ name;
        System::String^ description;
        System::String^ difficulty;
        int duration; // in minutes
        Customer^ customer;
        Trainer^ trainer;

        ExercisePlan() {
            id = 0;
            name = "";
            description = "";
            difficulty = "";
            duration = 0;
            customer = nullptr;
            trainer = nullptr;
        }
    };
}