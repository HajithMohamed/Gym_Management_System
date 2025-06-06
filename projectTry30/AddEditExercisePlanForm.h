#pragma once
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Data.dll>
#include "DatabaseHelper.h"

namespace GymManagementSystem {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Data::SqlClient;

    public ref class AddEditExercisePlanForm : public System::Windows::Forms::Form {
    public:
        AddEditExercisePlanForm(DataGridViewRow^ row) {
            isEditMode = (row != nullptr);
            selectedRow = row;
            InitializeComponent();
            PopulateCustomers();
            PopulateTrainers();
            if (isEditMode) {
                this->Text = "Edit Exercise Plan";
                // Handle DBNull for customer_id
                if (row->Cells["customer_id"]->Value != DBNull::Value) {
                    cmbCustomer->SelectedValue = Convert::ToInt32(row->Cells["customer_id"]->Value);
                }
                // Handle DBNull for trainer_id
                if (row->Cells["trainer_id"]->Value != DBNull::Value) {
                    cmbTrainer->SelectedValue = Convert::ToInt32(row->Cells["trainer_id"]->Value);
                }
                // Handle DBNull for name (mapped from plan_name)
                txtPlanName->Text = (row->Cells["name"]->Value != DBNull::Value) ? row->Cells["name"]->Value->ToString() : "";
                // Handle DBNull for description
                txtDescription->Text = (row->Cells["description"]->Value != DBNull::Value) ? row->Cells["description"]->Value->ToString() : "";
                // Remove start_date and end_date since they are not in the table
            }
            else {
                this->Text = "Add New Exercise Plan";
                // No need for dtpStartDate and dtpEndDate default values since they are not used
            }
        }

    protected:
        ~AddEditExercisePlanForm() {
            if (components) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        System::Windows::Forms::Label^ lblCustomer;
        System::Windows::Forms::ComboBox^ cmbCustomer;
        System::Windows::Forms::Label^ lblTrainer;
        System::Windows::Forms::ComboBox^ cmbTrainer;
        System::Windows::Forms::Label^ lblPlanName;
        System::Windows::Forms::TextBox^ txtPlanName;
        System::Windows::Forms::Label^ lblDescription;
        System::Windows::Forms::TextBox^ txtDescription;
        System::Windows::Forms::Label^ lblStartDate;
        System::Windows::Forms::DateTimePicker^ dtpStartDate;
        System::Windows::Forms::Label^ lblEndDate;
        System::Windows::Forms::DateTimePicker^ dtpEndDate;
        System::Windows::Forms::Button^ btnSave;
        bool isEditMode;
        DataGridViewRow^ selectedRow;

        void InitializeComponent() {
            this->components = gcnew System::ComponentModel::Container();
            this->lblCustomer = gcnew System::Windows::Forms::Label();
            this->cmbCustomer = gcnew System::Windows::Forms::ComboBox();
            this->lblTrainer = gcnew System::Windows::Forms::Label();
            this->cmbTrainer = gcnew System::Windows::Forms::ComboBox();
            this->lblPlanName = gcnew System::Windows::Forms::Label();
            this->txtPlanName = gcnew System::Windows::Forms::TextBox();
            this->lblDescription = gcnew System::Windows::Forms::Label();
            this->txtDescription = gcnew System::Windows::Forms::TextBox();
            this->lblStartDate = gcnew System::Windows::Forms::Label();
            this->dtpStartDate = gcnew System::Windows::Forms::DateTimePicker();
            this->lblEndDate = gcnew System::Windows::Forms::Label();
            this->dtpEndDate = gcnew System::Windows::Forms::DateTimePicker();
            this->btnSave = gcnew System::Windows::Forms::Button();

            this->Size = System::Drawing::Size(300, 350);
            this->StartPosition = FormStartPosition::CenterParent;

            // Customer Label
            this->lblCustomer->Text = "Customer:";
            this->lblCustomer->Location = System::Drawing::Point(20, 30);
            this->lblCustomer->Size = System::Drawing::Size(80, 20);

            // Customer ComboBox
            this->cmbCustomer->Location = System::Drawing::Point(100, 30);
            this->cmbCustomer->Size = System::Drawing::Size(150, 20);
            this->cmbCustomer->DropDownStyle = ComboBoxStyle::DropDownList;

            // Trainer Label
            this->lblTrainer->Text = "Trainer:";
            this->lblTrainer->Location = System::Drawing::Point(20, 60);
            this->lblTrainer->Size = System::Drawing::Size(80, 20);

            // Trainer ComboBox
            this->cmbTrainer->Location = System::Drawing::Point(100, 60);
            this->cmbTrainer->Size = System::Drawing::Size(150, 20);
            this->cmbTrainer->DropDownStyle = ComboBoxStyle::DropDownList;

            // Plan Name Label
            this->lblPlanName->Text = "Plan Name:";
            this->lblPlanName->Location = System::Drawing::Point(20, 90);
            this->lblPlanName->Size = System::Drawing::Size(80, 20);

            // Plan Name TextBox
            this->txtPlanName->Location = System::Drawing::Point(100, 90);
            this->txtPlanName->Size = System::Drawing::Size(150, 20);
            this->txtPlanName->Text = "";

            // Description Label
            this->lblDescription->Text = "Description:";
            this->lblDescription->Location = System::Drawing::Point(20, 120);
            this->lblDescription->Size = System::Drawing::Size(80, 20);

            // Description TextBox
            this->txtDescription->Location = System::Drawing::Point(100, 120);
            this->txtDescription->Size = System::Drawing::Size(150, 60);
            this->txtDescription->Multiline = true;
            this->txtDescription->Text = "";

            // Start Date Label (optional, can be removed if not used)
            this->lblStartDate->Text = "Start Date:";
            this->lblStartDate->Location = System::Drawing::Point(20, 190);
            this->lblStartDate->Size = System::Drawing::Size(80, 20);

            // Start Date DateTimePicker (optional, can be removed if not used)
            this->dtpStartDate->Location = System::Drawing::Point(100, 190);
            this->dtpStartDate->Size = System::Drawing::Size(150, 20);
            this->dtpStartDate->Format = DateTimePickerFormat::Short;

            // End Date Label (optional, can be removed if not used)
            this->lblEndDate->Text = "End Date:";
            this->lblEndDate->Location = System::Drawing::Point(20, 220);
            this->lblEndDate->Size = System::Drawing::Size(80, 20);

            // End Date DateTimePicker (optional, can be removed if not used)
            this->dtpEndDate->Location = System::Drawing::Point(100, 220);
            this->dtpEndDate->Size = System::Drawing::Size(150, 20);
            this->dtpEndDate->Format = DateTimePickerFormat::Short;

            // Save Button
            this->btnSave->Text = "Save Exercise Plan";
            this->btnSave->Location = System::Drawing::Point(100, 260);
            this->btnSave->Size = System::Drawing::Size(100, 30);
            this->btnSave->Click += gcnew System::EventHandler(this, &AddEditExercisePlanForm::OnSaveClick);

            this->Controls->Add(this->lblCustomer);
            this->Controls->Add(this->cmbCustomer);
            this->Controls->Add(this->lblTrainer);
            this->Controls->Add(this->cmbTrainer);
            this->Controls->Add(this->lblPlanName);
            this->Controls->Add(this->txtPlanName);
            this->Controls->Add(this->lblDescription);
            this->Controls->Add(this->txtDescription);
            this->Controls->Add(this->lblStartDate);
            this->Controls->Add(this->dtpStartDate);
            this->Controls->Add(this->lblEndDate);
            this->Controls->Add(this->dtpEndDate);
            this->Controls->Add(this->btnSave);
        }

        void PopulateCustomers() {
            try {
                DatabaseHelper::OpenConnection();
                SqlConnection^ conn = DatabaseHelper::GetConnection();
                String^ query = "SELECT c.id, u.name FROM Customers c JOIN Users u ON c.user_id = u.id";
                SqlCommand^ command = gcnew SqlCommand(query, conn);
                SqlDataAdapter^ adapter = gcnew SqlDataAdapter(command);
                DataTable^ dt = gcnew DataTable();
                adapter->Fill(dt);
                cmbCustomer->DisplayMember = "name";
                cmbCustomer->ValueMember = "id";
                cmbCustomer->DataSource = dt;
                cmbCustomer->SelectedIndex = -1; // No default selection
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading customers: " + ex->Message, "Database Error");
            }
            finally {
                DatabaseHelper::CloseConnection();
            }
        }

        void PopulateTrainers() {
            try {
                DatabaseHelper::OpenConnection();
                SqlConnection^ conn = DatabaseHelper::GetConnection();
                String^ query = "SELECT t.id, u.name FROM Trainers t JOIN Users u ON t.user_id = u.id";
                SqlCommand^ command = gcnew SqlCommand(query, conn);
                SqlDataAdapter^ adapter = gcnew SqlDataAdapter(command);
                DataTable^ dt = gcnew DataTable();
                adapter->Fill(dt);
                cmbTrainer->DisplayMember = "name";
                cmbTrainer->ValueMember = "id";
                cmbTrainer->DataSource = dt;
                cmbTrainer->SelectedIndex = -1; // No default selection
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading trainers: " + ex->Message, "Database Error");
            }
            finally {
                DatabaseHelper::CloseConnection();
            }
        }

        void OnSaveClick(System::Object^ sender, System::EventArgs^ e) {
            try {
                if (cmbCustomer->SelectedIndex == -1 || cmbTrainer->SelectedIndex == -1 || String::IsNullOrEmpty(txtPlanName->Text)) {
                    MessageBox::Show("Please fill in all required fields (Customer, Trainer, Plan Name).", "Input Error");
                    return;
                }

                DatabaseHelper::OpenConnection();
                SqlConnection^ conn = DatabaseHelper::GetConnection();

                if (isEditMode) {
                    // Update ExercisePlans table
                    String^ query = "UPDATE ExercisePlans SET customer_id = @customerId, trainer_id = @trainerId, " +
                        "name = @name, description = @description " +
                        "WHERE id = @id";
                    SqlCommand^ command = gcnew SqlCommand(query, conn);
                    command->Parameters->AddWithValue("@customerId", cmbCustomer->SelectedValue);
                    command->Parameters->AddWithValue("@trainerId", cmbTrainer->SelectedValue);
                    command->Parameters->AddWithValue("@name", txtPlanName->Text);
                    command->Parameters->AddWithValue("@description", String::IsNullOrEmpty(txtDescription->Text) ? (Object^)DBNull::Value : (Object^)txtDescription->Text);
                    command->Parameters->AddWithValue("@id", selectedRow->Cells["id"]->Value);
                    command->ExecuteNonQuery();
                }
                else {
                    // Insert into ExercisePlans table
                    String^ query = "INSERT INTO ExercisePlans (customer_id, trainer_id, name, description) " +
                        "VALUES (@customerId, @trainerId, @name, @description)";
                    SqlCommand^ command = gcnew SqlCommand(query, conn);
                    command->Parameters->AddWithValue("@customerId", cmbCustomer->SelectedValue);
                    command->Parameters->AddWithValue("@trainerId", cmbTrainer->SelectedValue);
                    command->Parameters->AddWithValue("@name", txtPlanName->Text);
                    command->Parameters->AddWithValue("@description", String::IsNullOrEmpty(txtDescription->Text) ? (Object^)DBNull::Value : (Object^)txtDescription->Text);
                    command->ExecuteNonQuery();
                }

                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Save Error: " + ex->Message, "Exercise Plan Save Failed");
            }
            finally {
                DatabaseHelper::CloseConnection();
            }
        }
    };
}