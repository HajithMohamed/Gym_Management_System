#pragma once
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Data.dll>
#include "DatabaseHelper.h"

namespace GymManagementSystem {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Data::SqlClient;

    public ref class AddEditGymHallForm : public System::Windows::Forms::Form {
    public:
        AddEditGymHallForm(DataGridViewRow^ row) {
            isEditMode = (row != nullptr);
            selectedRow = row;
            InitializeComponent();
            if (isEditMode) {
                this->Text = "Edit Gym Hall";
                txtName->Text = row->Cells["name"]->Value ? row->Cells["name"]->Value->ToString() : "";
                txtLocation->Text = row->Cells["location"]->Value ? row->Cells["location"]->Value->ToString() : "";
                txtCapacity->Text = row->Cells["capacity"]->Value ? row->Cells["capacity"]->Value->ToString() : "";
                chkIsAvailable->Checked = row->Cells["is_available"]->Value ? Convert::ToBoolean(row->Cells["is_available"]->Value) : false;
            }
            else {
                this->Text = "Add New Gym Hall";
            }
        }

    protected:
        ~AddEditGymHallForm() {
            if (components) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        System::Windows::Forms::Label^ lblName;
        System::Windows::Forms::TextBox^ txtName;
        System::Windows::Forms::Label^ lblLocation;
        System::Windows::Forms::TextBox^ txtLocation;
        System::Windows::Forms::Label^ lblCapacity;
        System::Windows::Forms::TextBox^ txtCapacity;
        System::Windows::Forms::Label^ lblIsAvailable;
        System::Windows::Forms::CheckBox^ chkIsAvailable;
        System::Windows::Forms::Button^ btnSave;
        bool isEditMode;
        DataGridViewRow^ selectedRow;

        void InitializeComponent() {
            this->components = gcnew System::ComponentModel::Container();
            this->lblName = gcnew System::Windows::Forms::Label();
            this->txtName = gcnew System::Windows::Forms::TextBox();
            this->lblLocation = gcnew System::Windows::Forms::Label();
            this->txtLocation = gcnew System::Windows::Forms::TextBox();
            this->lblCapacity = gcnew System::Windows::Forms::Label();
            this->txtCapacity = gcnew System::Windows::Forms::TextBox();
            this->lblIsAvailable = gcnew System::Windows::Forms::Label();
            this->chkIsAvailable = gcnew System::Windows::Forms::CheckBox();
            this->btnSave = gcnew System::Windows::Forms::Button();

            this->Size = System::Drawing::Size(300, 250);
            this->StartPosition = FormStartPosition::CenterParent;

            // Name Label
            this->lblName->Text = "Name:";
            this->lblName->Location = System::Drawing::Point(20, 30);
            this->lblName->Size = System::Drawing::Size(80, 20);

            // Name TextBox
            this->txtName->Location = System::Drawing::Point(100, 30);
            this->txtName->Size = System::Drawing::Size(150, 20);
            this->txtName->Text = "";

            // Location Label
            this->lblLocation->Text = "Location:";
            this->lblLocation->Location = System::Drawing::Point(20, 60);
            this->lblLocation->Size = System::Drawing::Size(80, 20);

            // Location TextBox
            this->txtLocation->Location = System::Drawing::Point(100, 60);
            this->txtLocation->Size = System::Drawing::Size(150, 20);
            this->txtLocation->Text = "";

            // Capacity Label
            this->lblCapacity->Text = "Capacity:";
            this->lblCapacity->Location = System::Drawing::Point(20, 90);
            this->lblCapacity->Size = System::Drawing::Size(80, 20);

            // Capacity TextBox
            this->txtCapacity->Location = System::Drawing::Point(100, 90);
            this->txtCapacity->Size = System::Drawing::Size(150, 20);
            this->txtCapacity->Text = "";

            // Is Available Label
            this->lblIsAvailable->Text = "Is Available:";
            this->lblIsAvailable->Location = System::Drawing::Point(20, 120);
            this->lblIsAvailable->Size = System::Drawing::Size(80, 20);

            // Is Available CheckBox
            this->chkIsAvailable->Location = System::Drawing::Point(100, 120);
            this->chkIsAvailable->Size = System::Drawing::Size(20, 20);
            this->chkIsAvailable->Checked = false;

            // Save Button
            this->btnSave->Text = "Save Gym Hall";
            this->btnSave->Location = System::Drawing::Point(100, 160);
            this->btnSave->Size = System::Drawing::Size(100, 30);
            this->btnSave->Click += gcnew System::EventHandler(this, &AddEditGymHallForm::OnSaveClick);

            this->Controls->Add(this->lblName);
            this->Controls->Add(this->txtName);
            this->Controls->Add(this->lblLocation);
            this->Controls->Add(this->txtLocation);
            this->Controls->Add(this->lblCapacity);
            this->Controls->Add(this->txtCapacity);
            this->Controls->Add(this->lblIsAvailable);
            this->Controls->Add(this->chkIsAvailable);
            this->Controls->Add(this->btnSave);
        }

        void OnSaveClick(System::Object^ sender, System::EventArgs^ e) {
            try {
                if (String::IsNullOrEmpty(txtName->Text) || String::IsNullOrEmpty(txtLocation->Text) || String::IsNullOrEmpty(txtCapacity->Text)) {
                    MessageBox::Show("Please fill in all required fields.", "Input Error");
                    return;
                }

                int capacity;
                if (!Int32::TryParse(txtCapacity->Text, capacity)) {
                    MessageBox::Show("Capacity must be a valid number.", "Input Error");
                    return;
                }

                DatabaseHelper::OpenConnection();
                SqlConnection^ conn = DatabaseHelper::GetConnection();

                if (isEditMode) {
                    // Update GymHalls table
                    String^ query = "UPDATE GymHalls SET name = @name, location = @location, capacity = @capacity, is_available = @isAvailable WHERE id = @id";
                    SqlCommand^ command = gcnew SqlCommand(query, conn);
                    command->Parameters->AddWithValue("@name", txtName->Text);
                    command->Parameters->AddWithValue("@location", txtLocation->Text);
                    command->Parameters->AddWithValue("@capacity", capacity);
                    command->Parameters->AddWithValue("@isAvailable", chkIsAvailable->Checked);
                    command->Parameters->AddWithValue("@id", selectedRow->Cells["id"]->Value);
                    command->ExecuteNonQuery();
                }
                else {
                    // Insert into GymHalls table
                    String^ query = "INSERT INTO GymHalls (name, location, capacity, is_available) VALUES (@name, @location, @capacity, @isAvailable)";
                    SqlCommand^ command = gcnew SqlCommand(query, conn);
                    command->Parameters->AddWithValue("@name", txtName->Text);
                    command->Parameters->AddWithValue("@location", txtLocation->Text);
                    command->Parameters->AddWithValue("@capacity", capacity);
                    command->Parameters->AddWithValue("@isAvailable", chkIsAvailable->Checked);
                    command->ExecuteNonQuery();
                }

                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Save Error: " + ex->Message, "Gym Hall Save Failed");
            }
            finally {
                DatabaseHelper::CloseConnection();
            }
        }
    };
}