#pragma once
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Data.dll>
#include "DatabaseHelper.h"

namespace GymManagementSystem {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Data::SqlClient;

    public ref class AddEditTrainerForm : public System::Windows::Forms::Form {
    public:
        AddEditTrainerForm(DataGridViewRow^ row) {
            isEditMode = (row != nullptr);
            selectedRow = row;
            InitializeComponent();
            if (isEditMode) {
                this->Text = "Edit Trainer Profile";
                txtName->Text = row->Cells["name"]->Value->ToString();
                txtMobile->Text = row->Cells["mobile"]->Value->ToString();
                txtPassword->Text = "";
                txtSpecialization->Text = row->Cells["specialization"]->Value ? row->Cells["specialization"]->Value->ToString() : "";
                txtExperience->Text = row->Cells["experience"]->Value ? row->Cells["experience"]->Value->ToString() : "";
                txtCertification->Text = row->Cells["certification"]->Value ? row->Cells["certification"]->Value->ToString() : "";
                txtHourlyRate->Text = row->Cells["hourly_rate"]->Value ? row->Cells["hourly_rate"]->Value->ToString() : "";
            }
            else {
                this->Text = "Add New Trainer";
            }
        }

    protected:
        ~AddEditTrainerForm() {
            if (components) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        System::Windows::Forms::Label^ lblName;
        System::Windows::Forms::TextBox^ txtName;
        System::Windows::Forms::Label^ lblMobile;
        System::Windows::Forms::TextBox^ txtMobile;
        System::Windows::Forms::Label^ lblPassword;
        System::Windows::Forms::TextBox^ txtPassword;
        System::Windows::Forms::Label^ lblSpecialization;
        System::Windows::Forms::TextBox^ txtSpecialization;
        System::Windows::Forms::Label^ lblExperience;
        System::Windows::Forms::TextBox^ txtExperience;
        System::Windows::Forms::Label^ lblCertification;
        System::Windows::Forms::TextBox^ txtCertification;
        System::Windows::Forms::Label^ lblHourlyRate;
        System::Windows::Forms::TextBox^ txtHourlyRate;
        System::Windows::Forms::Button^ btnSave;
        bool isEditMode;
        DataGridViewRow^ selectedRow;

        void InitializeComponent() {
            this->components = gcnew System::ComponentModel::Container();
            this->lblName = gcnew System::Windows::Forms::Label();
            this->txtName = gcnew System::Windows::Forms::TextBox();
            this->lblMobile = gcnew System::Windows::Forms::Label();
            this->txtMobile = gcnew System::Windows::Forms::TextBox();
            this->lblPassword = gcnew System::Windows::Forms::Label();
            this->txtPassword = gcnew System::Windows::Forms::TextBox();
            this->lblSpecialization = gcnew System::Windows::Forms::Label();
            this->txtSpecialization = gcnew System::Windows::Forms::TextBox();
            this->lblExperience = gcnew System::Windows::Forms::Label();
            this->txtExperience = gcnew System::Windows::Forms::TextBox();
            this->lblCertification = gcnew System::Windows::Forms::Label();
            this->txtCertification = gcnew System::Windows::Forms::TextBox();
            this->lblHourlyRate = gcnew System::Windows::Forms::Label();
            this->txtHourlyRate = gcnew System::Windows::Forms::TextBox();
            this->btnSave = gcnew System::Windows::Forms::Button();

            // Form setup
            this->Size = System::Drawing::Size(300, 350);
            this->StartPosition = FormStartPosition::CenterParent;

            // Name Label
            this->lblName->Text = "Name:";
            this->lblName->Location = System::Drawing::Point(20, 30);
            this->lblName->Size = System::Drawing::Size(80, 20);

            // Name TextBox
            this->txtName->Location = System::Drawing::Point(100, 30);
            this->txtName->Size = System::Drawing::Size(150, 20);
            this->txtName->Text = "Enter Trainer Name";

            // Mobile Label
            this->lblMobile->Text = "Mobile:";
            this->lblMobile->Location = System::Drawing::Point(20, 60);
            this->lblMobile->Size = System::Drawing::Size(80, 20);

            // Mobile TextBox
            this->txtMobile->Location = System::Drawing::Point(100, 60);
            this->txtMobile->Size = System::Drawing::Size(150, 20);
            this->txtMobile->Text = "Enter Mobile Number";

            // Password Label
            this->lblPassword->Text = "Password:";
            this->lblPassword->Location = System::Drawing::Point(20, 90);
            this->lblPassword->Size = System::Drawing::Size(80, 20);

            // Password TextBox
            this->txtPassword->Location = System::Drawing::Point(100, 90);
            this->txtPassword->Size = System::Drawing::Size(150, 20);
            this->txtPassword->UseSystemPasswordChar = true;
            this->txtPassword->Text = "Enter Password";

            // Specialization Label
            this->lblSpecialization->Text = "Specialization:";
            this->lblSpecialization->Location = System::Drawing::Point(20, 120);
            this->lblSpecialization->Size = System::Drawing::Size(80, 20);

            // Specialization TextBox
            this->txtSpecialization->Location = System::Drawing::Point(100, 120);
            this->txtSpecialization->Size = System::Drawing::Size(150, 20);
            this->txtSpecialization->Text = "Enter Specialization";

            // Experience Label
            this->lblExperience->Text = "Experience (yrs):";
            this->lblExperience->Location = System::Drawing::Point(20, 150);
            this->lblExperience->Size = System::Drawing::Size(80, 20);

            // Experience TextBox
            this->txtExperience->Location = System::Drawing::Point(100, 150);
            this->txtExperience->Size = System::Drawing::Size(150, 20);
            this->txtExperience->Text = "Enter Years";

            // Certification Label
            this->lblCertification->Text = "Certification:";
            this->lblCertification->Location = System::Drawing::Point(20, 180);
            this->lblCertification->Size = System::Drawing::Size(80, 20);

            // Certification TextBox
            this->txtCertification->Location = System::Drawing::Point(100, 180);
            this->txtCertification->Size = System::Drawing::Size(150, 20);
            this->txtCertification->Text = "Enter Certification";

            // Hourly Rate Label
            this->lblHourlyRate->Text = "Hourly Rate:";
            this->lblHourlyRate->Location = System::Drawing::Point(20, 210);
            this->lblHourlyRate->Size = System::Drawing::Size(80, 20);

            // Hourly Rate TextBox
            this->txtHourlyRate->Location = System::Drawing::Point(100, 210);
            this->txtHourlyRate->Size = System::Drawing::Size(150, 20);
            this->txtHourlyRate->Text = "Enter Rate";

            // Save Button
            this->btnSave->Text = "Save Trainer";
            this->btnSave->Location = System::Drawing::Point(100, 250);
            this->btnSave->Size = System::Drawing::Size(100, 30);
            this->btnSave->Click += gcnew System::EventHandler(this, &AddEditTrainerForm::OnSaveClick);

            // Add controls
            this->Controls->Add(this->lblName);
            this->Controls->Add(this->txtName);
            this->Controls->Add(this->lblMobile);
            this->Controls->Add(this->txtMobile);
            this->Controls->Add(this->lblPassword);
            this->Controls->Add(this->txtPassword);
            this->Controls->Add(this->lblSpecialization);
            this->Controls->Add(this->txtSpecialization);
            this->Controls->Add(this->lblExperience);
            this->Controls->Add(this->txtExperience);
            this->Controls->Add(this->lblCertification);
            this->Controls->Add(this->txtCertification);
            this->Controls->Add(this->lblHourlyRate);
            this->Controls->Add(this->txtHourlyRate);
            this->Controls->Add(this->btnSave);
        }

        void OnSaveClick(System::Object^ sender, System::EventArgs^ e) {
            try {
                if (String::IsNullOrEmpty(txtName->Text) || String::IsNullOrEmpty(txtMobile->Text) ||
                    (!isEditMode && String::IsNullOrEmpty(txtPassword->Text)) ||
                    String::IsNullOrEmpty(txtSpecialization->Text) || String::IsNullOrEmpty(txtExperience->Text) ||
                    String::IsNullOrEmpty(txtCertification->Text) || String::IsNullOrEmpty(txtHourlyRate->Text)) {
                    MessageBox::Show("Please fill in all required fields.", "Input Error");
                    return;
                }

                DatabaseHelper::OpenConnection();
                SqlConnection^ conn = DatabaseHelper::GetConnection();

                if (isEditMode) {
                    // Update Users table
                    String^ userQuery = "UPDATE Users SET name = @name, mobile = @mobile";
                    if (!String::IsNullOrEmpty(txtPassword->Text)) {
                        userQuery += ", password = @password";
                    }
                    userQuery += " WHERE id = (SELECT user_id FROM Trainers WHERE id = @trainerId)";
                    SqlCommand^ userCommand = gcnew SqlCommand(userQuery, conn);
                    userCommand->Parameters->AddWithValue("@name", txtName->Text);
                    userCommand->Parameters->AddWithValue("@mobile", txtMobile->Text);
                    if (!String::IsNullOrEmpty(txtPassword->Text)) {
                        userCommand->Parameters->AddWithValue("@password", txtPassword->Text);
                    }
                    userCommand->Parameters->AddWithValue("@trainerId", selectedRow->Cells["id"]->Value);
                    userCommand->ExecuteNonQuery();

                    // Update Trainers table
                    String^ trainerQuery = "UPDATE Trainers SET specialization = @specialization, experience = @experience, " +
                        "certification = @certification, hourly_rate = @hourlyRate WHERE id = @trainerId";
                    SqlCommand^ trainerCommand = gcnew SqlCommand(trainerQuery, conn);
                    trainerCommand->Parameters->AddWithValue("@specialization", txtSpecialization->Text);
                    trainerCommand->Parameters->AddWithValue("@experience", Int32::Parse(txtExperience->Text));
                    trainerCommand->Parameters->AddWithValue("@certification", txtCertification->Text);
                    trainerCommand->Parameters->AddWithValue("@hourlyRate", Decimal::Parse(txtHourlyRate->Text));
                    trainerCommand->Parameters->AddWithValue("@trainerId", selectedRow->Cells["id"]->Value);
                    trainerCommand->ExecuteNonQuery();
                }
                else {
                    // Insert into Users table
                    String^ userQuery = "INSERT INTO Users (name, mobile, password) OUTPUT INSERTED.id VALUES (@name, @mobile, @password)";
                    SqlCommand^ userCommand = gcnew SqlCommand(userQuery, conn);
                    userCommand->Parameters->AddWithValue("@name", txtName->Text);
                    userCommand->Parameters->AddWithValue("@mobile", txtMobile->Text);
                    userCommand->Parameters->AddWithValue("@password", txtPassword->Text);
                    int userId = (int)userCommand->ExecuteScalar();

                    // Insert into Trainers table
                    String^ trainerQuery = "INSERT INTO Trainers (user_id, specialization, experience, certification, hourly_rate) " +
                        "VALUES (@userId, @specialization, @experience, @certification, @hourlyRate)";
                    SqlCommand^ trainerCommand = gcnew SqlCommand(trainerQuery, conn);
                    trainerCommand->Parameters->AddWithValue("@userId", userId);
                    trainerCommand->Parameters->AddWithValue("@specialization", txtSpecialization->Text);
                    trainerCommand->Parameters->AddWithValue("@experience", Int32::Parse(txtExperience->Text));
                    trainerCommand->Parameters->AddWithValue("@certification", txtCertification->Text);
                    trainerCommand->Parameters->AddWithValue("@hourlyRate", Decimal::Parse(txtHourlyRate->Text));
                    trainerCommand->ExecuteNonQuery();
                }

                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Save Error: " + ex->Message, "Trainer Save Failed");
            }
            finally {
                DatabaseHelper::CloseConnection();
            }
        }
    };
}