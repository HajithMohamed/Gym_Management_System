#pragma once
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Data.dll>
#include "DatabaseHelper.h"

namespace GymManagementSystem {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Data::SqlClient;

    public ref class AddEditEquipmentForm : public System::Windows::Forms::Form {
    public:
        AddEditEquipmentForm(DataGridViewRow^ row) {
            isEditMode = (row != nullptr);
            selectedRow = row;
            InitializeComponent();
            if (isEditMode) {
                this->Text = "Edit Equipment";
                txtName->Text = row->Cells["name"]->Value ? row->Cells["name"]->Value->ToString() : "";
                txtCategory->Text = row->Cells["category"]->Value ? row->Cells["category"]->Value->ToString() : "";
                txtQuantity->Text = row->Cells["quantity"]->Value ? row->Cells["quantity"]->Value->ToString() : "";
                dtpLastMaintenance->Value = row->Cells["last_maintenance_date"]->Value ? Convert::ToDateTime(row->Cells["last_maintenance_date"]->Value) : DateTime::Now;
            }
            else {
                this->Text = "Add New Equipment";
                dtpLastMaintenance->Value = DateTime::Now; // Default to current date, user can change
            }
        }

    protected:
        ~AddEditEquipmentForm() {
            if (components) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        System::Windows::Forms::Label^ lblName;
        System::Windows::Forms::TextBox^ txtName;
        System::Windows::Forms::Label^ lblCategory;
        System::Windows::Forms::TextBox^ txtCategory;
        System::Windows::Forms::Label^ lblQuantity;
        System::Windows::Forms::TextBox^ txtQuantity;
        System::Windows::Forms::Label^ lblLastMaintenance;
        System::Windows::Forms::DateTimePicker^ dtpLastMaintenance;
        System::Windows::Forms::Button^ btnSave;
        bool isEditMode;
        DataGridViewRow^ selectedRow;

        void InitializeComponent() {
            this->components = gcnew System::ComponentModel::Container();
            this->lblName = gcnew System::Windows::Forms::Label();
            this->txtName = gcnew System::Windows::Forms::TextBox();
            this->lblCategory = gcnew System::Windows::Forms::Label();
            this->txtCategory = gcnew System::Windows::Forms::TextBox();
            this->lblQuantity = gcnew System::Windows::Forms::Label();
            this->txtQuantity = gcnew System::Windows::Forms::TextBox();
            this->lblLastMaintenance = gcnew System::Windows::Forms::Label();
            this->dtpLastMaintenance = gcnew System::Windows::Forms::DateTimePicker();
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

            // Category Label
            this->lblCategory->Text = "Category:";
            this->lblCategory->Location = System::Drawing::Point(20, 60);
            this->lblCategory->Size = System::Drawing::Size(80, 20);

            // Category TextBox
            this->txtCategory->Location = System::Drawing::Point(100, 60);
            this->txtCategory->Size = System::Drawing::Size(150, 20);
            this->txtCategory->Text = "";

            // Quantity Label
            this->lblQuantity->Text = "Quantity:";
            this->lblQuantity->Location = System::Drawing::Point(20, 90);
            this->lblQuantity->Size = System::Drawing::Size(80, 20);

            // Quantity TextBox
            this->txtQuantity->Location = System::Drawing::Point(100, 90);
            this->txtQuantity->Size = System::Drawing::Size(150, 20);
            this->txtQuantity->Text = "";

            // Last Maintenance Date Label
            this->lblLastMaintenance->Text = "Last Maintenance:";
            this->lblLastMaintenance->Location = System::Drawing::Point(20, 120);
            this->lblLastMaintenance->Size = System::Drawing::Size(80, 20);

            // Last Maintenance DateTimePicker
            this->dtpLastMaintenance->Location = System::Drawing::Point(100, 120);
            this->dtpLastMaintenance->Size = System::Drawing::Size(150, 20);
            this->dtpLastMaintenance->Format = DateTimePickerFormat::Short;

            // Save Button
            this->btnSave->Text = "Save Equipment";
            this->btnSave->Location = System::Drawing::Point(100, 160);
            this->btnSave->Size = System::Drawing::Size(100, 30);
            this->btnSave->Click += gcnew System::EventHandler(this, &AddEditEquipmentForm::OnSaveClick);

            this->Controls->Add(this->lblName);
            this->Controls->Add(this->txtName);
            this->Controls->Add(this->lblCategory);
            this->Controls->Add(this->txtCategory);
            this->Controls->Add(this->lblQuantity);
            this->Controls->Add(this->txtQuantity);
            this->Controls->Add(this->lblLastMaintenance);
            this->Controls->Add(this->dtpLastMaintenance);
            this->Controls->Add(this->btnSave);
        }

        void OnSaveClick(System::Object^ sender, System::EventArgs^ e) {
            try {
                if (String::IsNullOrEmpty(txtName->Text) || String::IsNullOrEmpty(txtCategory->Text) || String::IsNullOrEmpty(txtQuantity->Text)) {
                    MessageBox::Show("Please fill in all required fields.", "Input Error");
                    return;
                }

                int quantity;
                if (!Int32::TryParse(txtQuantity->Text, quantity)) {
                    MessageBox::Show("Quantity must be a valid number.", "Input Error");
                    return;
                }

                DatabaseHelper::OpenConnection();
                SqlConnection^ conn = DatabaseHelper::GetConnection();

                if (isEditMode) {
                    // Update Equipment table
                    String^ query = "UPDATE Equipment SET name = @name, category = @category, quantity = @quantity, last_maintenance_date = @lastMaintenanceDate WHERE id = @id";
                    SqlCommand^ command = gcnew SqlCommand(query, conn);
                    command->Parameters->AddWithValue("@name", txtName->Text);
                    command->Parameters->AddWithValue("@category", txtCategory->Text);
                    command->Parameters->AddWithValue("@quantity", quantity);
                    command->Parameters->AddWithValue("@lastMaintenanceDate", dtpLastMaintenance->Value.Date);
                    command->Parameters->AddWithValue("@id", selectedRow->Cells["id"]->Value);
                    command->ExecuteNonQuery();
                }
                else {
                    // Insert into Equipment table
                    String^ query = "INSERT INTO Equipment (name, category, quantity, last_maintenance_date) VALUES (@name, @category, @quantity, @lastMaintenanceDate)";
                    SqlCommand^ command = gcnew SqlCommand(query, conn);
                    command->Parameters->AddWithValue("@name", txtName->Text);
                    command->Parameters->AddWithValue("@category", txtCategory->Text);
                    command->Parameters->AddWithValue("@quantity", quantity);
                    command->Parameters->AddWithValue("@lastMaintenanceDate", dtpLastMaintenance->Value.Date);
                    command->ExecuteNonQuery();
                }

                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Save Error: " + ex->Message, "Equipment Save Failed");
            }
            finally {
                DatabaseHelper::CloseConnection();
            }
        }
    };
}