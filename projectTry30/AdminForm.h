#pragma once
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>
#include "TrainerForm.h"
#include "CustomerForm.h"
#include "GymHallForm.h"
#include "EquipmentForm.h"
#include "ExercisePlanForm.h"
#include "LoginForm.h"

namespace GymManagementSystem {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class AdminForm : public System::Windows::Forms::Form {
    public:
        AdminForm() {
            try {
                InitializeComponent();
                this->Visible = true;
            }
            catch (Exception^ ex) {
                MessageBox::Show("AdminForm Initialization Error: " + ex->Message + "\nStack Trace: " + ex->StackTrace, "Error");
            }
        }

    protected:
        ~AdminForm() {
            if (components) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        System::Windows::Forms::Button^ btnTrainers;
        System::Windows::Forms::Button^ btnCustomers;
        System::Windows::Forms::Button^ btnGymHalls;
        System::Windows::Forms::Button^ btnEquipment;
        System::Windows::Forms::Button^ btnExercisePlans;
        System::Windows::Forms::Button^ btnLogout;

        void InitializeComponent() {
            try {
                this->components = gcnew System::ComponentModel::Container();

                // Initialize Buttons
                this->btnTrainers = gcnew System::Windows::Forms::Button();
                this->btnTrainers->Text = "Manage Trainers";
                this->btnTrainers->Location = System::Drawing::Point(50, 50);
                this->btnTrainers->Size = System::Drawing::Size(200, 40);
                this->btnTrainers->Click += gcnew System::EventHandler(this, &AdminForm::OnTrainersClick);

                this->btnCustomers = gcnew System::Windows::Forms::Button();
                this->btnCustomers->Text = "Manage Customers";
                this->btnCustomers->Location = System::Drawing::Point(50, 100);
                this->btnCustomers->Size = System::Drawing::Size(200, 40);
                this->btnCustomers->Click += gcnew System::EventHandler(this, &AdminForm::OnCustomersClick);

                this->btnGymHalls = gcnew System::Windows::Forms::Button();
                this->btnGymHalls->Text = "Manage Gym Halls";
                this->btnGymHalls->Location = System::Drawing::Point(50, 150);
                this->btnGymHalls->Size = System::Drawing::Size(200, 40);
                this->btnGymHalls->Click += gcnew System::EventHandler(this, &AdminForm::OnGymHallsClick);

                this->btnEquipment = gcnew System::Windows::Forms::Button();
                this->btnEquipment->Text = "Manage Equipment";
                this->btnEquipment->Location = System::Drawing::Point(50, 200);
                this->btnEquipment->Size = System::Drawing::Size(200, 40);
                this->btnEquipment->Click += gcnew System::EventHandler(this, &AdminForm::OnEquipmentClick);

                this->btnExercisePlans = gcnew System::Windows::Forms::Button();
                this->btnExercisePlans->Text = "Manage Exercise Plans";
                this->btnExercisePlans->Location = System::Drawing::Point(50, 250);
                this->btnExercisePlans->Size = System::Drawing::Size(200, 40);
                this->btnExercisePlans->Click += gcnew System::EventHandler(this, &AdminForm::OnExercisePlansClick);

                this->btnLogout = gcnew System::Windows::Forms::Button();
                this->btnLogout->Text = "Logout";
                this->btnLogout->Location = System::Drawing::Point(50, 300);
                this->btnLogout->Size = System::Drawing::Size(200, 40);
                this->btnLogout->Click += gcnew System::EventHandler(this, &AdminForm::OnLogoutClick);

                // Form setup
                this->Text = "Gym Management System - Admin Panel";
                this->Size = System::Drawing::Size(300, 400);
                this->StartPosition = FormStartPosition::CenterScreen;
                this->Controls->Add(this->btnTrainers);
                this->Controls->Add(this->btnCustomers);
                this->Controls->Add(this->btnGymHalls);
                this->Controls->Add(this->btnEquipment);
                this->Controls->Add(this->btnExercisePlans);
                this->Controls->Add(this->btnLogout);
                this->FormClosing += gcnew FormClosingEventHandler(this, &AdminForm::OnFormClosing);
            }
            catch (Exception^ ex) {
                MessageBox::Show("InitializeComponent Error: " + ex->Message + "\nStack Trace: " + ex->StackTrace, "Error");
            }
        }

        void OnTrainersClick(System::Object^ sender, System::EventArgs^ e) {
            try {
                TrainerForm^ form = gcnew TrainerForm();
                form->ShowDialog();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error opening Trainers form: " + ex->Message, "Error");
            }
        }

        void OnCustomersClick(System::Object^ sender, System::EventArgs^ e) {
            try {
                CustomerForm^ form = gcnew CustomerForm();
                form->ShowDialog();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error opening Customers form: " + ex->Message, "Error");
            }
        }

        void OnGymHallsClick(System::Object^ sender, System::EventArgs^ e) {
            try {
                GymHallForm^ form = gcnew GymHallForm();
                form->ShowDialog();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error opening Gym Halls form: " + ex->Message, "Error");
            }
        }

        void OnEquipmentClick(System::Object^ sender, System::EventArgs^ e) {
            try {
                EquipmentForm^ form = gcnew EquipmentForm();
                form->ShowDialog();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error opening Equipment form: " + ex->Message, "Error");
            }
        }

        void OnExercisePlansClick(System::Object^ sender, System::EventArgs^ e) {
            try {
                ExercisePlanForm^ form = gcnew ExercisePlanForm();
                form->ShowDialog();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error opening Exercise Plans form: " + ex->Message, "Error");
            }
        }

        void OnLogoutClick(System::Object^ sender, System::EventArgs^ e) {
            try {
                this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
                // Show LoginForm before closing AdminForm
                LoginForm^ loginForm = gcnew LoginForm();
                loginForm->Show();
                this->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("OnLogoutClick Error: " + ex->Message + "\nStack Trace: " + ex->StackTrace, "Error");
            }
        }

        void OnFormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
            try {
                if (this->DialogResult != System::Windows::Forms::DialogResult::Cancel) {
                    if (MessageBox::Show("Are you sure you want to exit?", "Confirm Exit",
                        MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::No) {
                        e->Cancel = true;
                    }
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("OnFormClosing Error: " + ex->Message + "\nStack Trace: " + ex->StackTrace, "Error");
            }
        }
    };
}