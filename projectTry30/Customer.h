#pragma once
#using <System.dll>
#include "User.h"

namespace GymManagementSystem {
    public ref class Customer : public User {
    public:
        System::String^ membershipType;
        System::DateTime^ joinDate;
        System::DateTime^ expiryDate;
        double membershipFee;

        Customer() {
            membershipType = "";
            joinDate = System::DateTime::Now;
            expiryDate = System::DateTime::Now;
            membershipFee = 0.0;
        }
    };
}