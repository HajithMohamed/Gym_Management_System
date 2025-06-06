#pragma once
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Data.dll>
#include "DatabaseHelper.h"

namespace GymManagementSystem {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Data::SqlClient;

    public ref class AddEditCustomerForm : public System::Windows::Forms::Form {
    public:
        AddEditCustomerForm(DataGridViewRow^ row) {
            isEditMode = (row != nullptr);
            selectedRow = row;
            InitializeComponent();
            if (isEditMode) {
                this->Text = "Edit Customer Profile";
                txtName->Text = row->Cells["name"]->Value ? row->Cells["name"]->Value->ToString() : "";
                txtMobile->Text = row->Cells["mobile"]->Value ? row->Cells["mobile"]->Value->ToString() : "";
                txtMembershipType->Text = row->Cells["membership_type"]->Value ? row->Cells["membership_type"]->Value->ToString() : "";
                dtpJoinDate->Value = row->Cells["join_date"]->Value ? Convert::ToDateTime(row->Cells["join_date"]->Value) : DateTime::Now;
                dtpExpiryDate->Value = row->Cells["expiry_date"]->Value ? Convert::ToDateTime(row->Cells["expiry_date"]->Value) : DateTime::Now;
                txtMembershipFee->Text = row->Cells["membership_fee"]->Value ? row->Cells["membership_fee"]->Value->ToString() : "";
                txtPassword->Text = ""; // Optional in edit mode, left empty
            }
            else {
                this->Text = "Add New Customer";
                dtpJoinDate->Value = DateTime::Now;
                dtpExpiryDate->Value = DateTime::Now.AddYears(1); // Default to 1 year from now
                txtPassword->Text = ""; // Empty by default for new entries
            }
        }

    protected:
        ~AddEditCustomerForm() {
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
        System::Windows::Forms::Label^ lblMembershipType;
        System::Windows::Forms::TextBox^ txtMembershipType;
        System::Windows::Forms::Label^ lblJoinDate;
        System::Windows::Forms::DateTimePicker^ dtpJoinDate;
        System::Windows::Forms::Label^ lblExpiryDate;
        System::Windows::Forms::DateTimePicker^ dtpExpiryDate;
        System::Windows::Forms::Label^ lblMembershipFee;
        System::Windows::Forms::TextBox^ txtMembershipFee;
        System::Windows::Forms::Label^ lblPassword;
        System::Windows::Forms::TextBox^ txtPassword;
        System::Windows::Forms::Button^ btnSave;
        bool isEditMode;
        DataGridViewRow^ selectedRow;

        void InitializeComponent() {
            this->components = gcnew System::ComponentModel::Container();
            this->lblName = gcnew System::Windows::Forms::Label();
            this->txtName = gcnew System::Windows::Forms::TextBox();
            this->lblMobile = gcnew System::Windows::Forms::Label();
            this->txtMobile = gcnew System::Windows::Forms::TextBox();
            this->lblMembershipType = gcnew System::Windows::Forms::Label();
            this->txtMembershipType = gcnew System::Windows::Forms::TextBox();
            this->lblJoinDate = gcnew System::Windows::Forms::Label();
            this->dtpJoinDate = gcnew System::Windows::Forms::DateTimePicker();
            this->lblExpiryDate = gcnew System::Windows::Forms::Label();
            this->dtpExpiryDate = gcnew System::Windows::Forms::DateTimePicker();
            this->lblMembershipFee = gcnew System::Windows::Forms::Label();
            this->txtMembershipFee = gcnew System::Windows::Forms::TextBox();
            this->lblPassword = gcnew System::Windows::Forms::Label();
            this->txtPassword = gcnew System::Windows::Forms::TextBox();
            this->btnSave = gcnew System::Windows::Forms::Button();

            this->Size = System::Drawing::Size(300, 350);
            this->StartPosition = FormStartPosition::CenterParent;

            // Name Label
            this->lblName->Text = "Name:";
            this->lblName->Location = System::Drawing::Point(20, 30);
            this->lblName->Size = System::Drawing::Size(80, 20);

            // Name TextBox
            this->txtName->Location = System::Drawing::Point(100, 30);
            this->txtName->Size = System::Drawing::Size(150, 20);
            this->txtName->Text = "";

            // Mobile Label
            this->lblMobile->Text = "Mobile:";
            this->lblMobile->Location = System::Drawing::Point(20, 60);
            this->lblMobile->Size = System::Drawing::Size(80, 20);

            // Mobile TextBox
            this->txtMobile->Location = System::Drawing::Point(100, 60);
            this->txtMobile->Size = System::Drawing::Size(150, 20);
            this->txtMobile->Text = "";

            // Membership Type Label
            this->lblMembershipType->Text = "Membership Type:";
            this->lblMembershipType->Location = System::Drawing::Point(20, 90);
            this->lblMembershipType->Size = System::Drawing::Size(80, 20);

            // Membership Type TextBox
            this->txtMembershipType->Location = System::Drawing::Point(100, 90);
            this->txtMembershipType->Size = System::Drawing::Size(150, 20);
            this->txtMembershipType->Text = "";

            // Join Date Label
            this->lblJoinDate->Text = "Join Date:";
            this->lblJoinDate->Location = System::Drawing::Point(20, 120);
            this->lblJoinDate->Size = System::Drawing::Size(80, 20);

            // Join Date DateTimePicker
            this->dtpJoinDate->Location = System::Drawing::Point(100, 120);
            this->dtpJoinDate->Size = System::Drawing::Size(150, 20);
            this->dtpJoinDate->Format = DateTimePickerFormat::Short;

            // Expiry Date Label
            this->lblExpiryDate->Text = "Expiry Date:";
            this->lblExpiryDate->Location = System::Drawing::Point(20, 150);
            this->lblExpiryDate->Size = System::Drawing::Size(80, 20);

            // Expiry Date DateTimePicker
            this->dtpExpiryDate->Location = System::Drawing::Point(100, 150);
            this->dtpExpiryDate->Size = System::Drawing::Size(150, 20);
            this->dtpExpiryDate->Format = DateTimePickerFormat::Short;

            // Membership Fee Label
            this->lblMembershipFee->Text = "Membership Fee:";
            this->lblMembershipFee->Location = System::Drawing::Point(20, 180);
            this->lblMembershipFee->Size = System::Drawing::Size(80, 20);

            // Membership Fee TextBox
            this->txtMembershipFee->Location = System::Drawing::Point(100, 180);
            this->txtMembershipFee->Size = System::Drawing::Size(150, 20);
            this->txtMembershipFee->Text = "";

            // Password Label
            this->lblPassword->Text = "Password:";
            this->lblPassword->Location = System::Drawing::Point(20, 210);
            this->lblPassword->Size = System::Drawing::Size(80, 20);

            // Password TextBox
            this->txtPassword->Location = System::Drawing::Point(100, 210);
            this->txtPassword->Size = System::Drawing::Size(150, 20);
            this->txtPassword->UseSystemPasswordChar = true;
            this->txtPassword->Text = "";

            // Save Button
            this->btnSave->Text = "Save Customer";
            this->btnSave->Location = System::Drawing::Point(100, 250);
            this->btnSave->Size = System::Drawing::Size(100, 30);
            this->btnSave->Click += gcnew System::EventHandler(this, &AddEditCustomerForm::OnSaveClick);

            this->Controls->Add(this->lblName);
            this->Controls->Add(this->txtName);
            this->Controls->Add(this->lblMobile);
            this->Controls->Add(this->txtMobile);
            this->Controls->Add(this->lblMembershipType);
            this->Controls->Add(this->txtMembershipType);
            this->Controls->Add(this->lblJoinDate);
            this->Controls->Add(this->dtpJoinDate);
            this->Controls->Add(this->lblExpiryDate);
            this->Controls->Add(this->dtpExpiryDate);
            this->Controls->Add(this->lblMembershipFee);
            this->Controls->Add(this->txtMembershipFee);
            this->Controls->Add(this->lblPassword);
            this->Controls->Add(this->txtPassword);
            this->Controls->Add(this->btnSave);
        }

        void OnSaveClick(System::Object^ sender, System::EventArgs^ e) {
            try {
                if (String::IsNullOrEmpty(txtName->Text) || String::IsNullOrEmpty(txtMobile->Text) ||
                    String::IsNullOrEmpty(txtMembershipType->Text) || String::IsNullOrEmpty(txtMembershipFee->Text)) {
                    MessageBox::Show("Please fill in all required fields.", "Input Error");
                    return;
                }

                Decimal membershipFee;
                if (!Decimal::TryParse(txtMembershipFee->Text, membershipFee)) {
                    MessageBox::Show("Membership Fee must be a valid number.", "Input Error");
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
                    userQuery += " WHERE id = (SELECT user_id FROM Customers WHERE id = @customerId)";
                    SqlCommand^ userCommand = gcnew SqlCommand(userQuery, conn);
                    userCommand->Parameters->AddWithValue("@name", txtName->Text);
                    userCommand->Parameters->AddWithValue("@mobile", txtMobile->Text);
                    if (!String::IsNullOrEmpty(txtPassword->Text)) {
                        userCommand->Parameters->AddWithValue("@password", txtPassword->Text);
                    }
                    userCommand->Parameters->AddWithValue("@customerId", selectedRow->Cells["id"]->Value);
                    userCommand->ExecuteNonQuery();

                    // Update Customers table
                    String^ customerQuery = "UPDATE Customers SET membership_type = @membershipType, join_date = @joinDate, " +
                        "expiry_date = @expiryDate, membership_fee = @membershipFee WHERE id = @customerId";
                    SqlCommand^ customerCommand = gcnew SqlCommand(customerQuery, conn);
                    customerCommand->Parameters->AddWithValue("@membershipType", txtMembershipType->Text);
                    customerCommand->Parameters->AddWithValue("@joinDate", dtpJoinDate->Value.Date);
                    customerCommand->Parameters->AddWithValue("@expiryDate", dtpExpiryDate->Value.Date);
                    customerCommand->Parameters->AddWithValue("@membershipFee", membershipFee);
                    customerCommand->Parameters->AddWithValue("@customerId", selectedRow->Cells["id"]->Value);
                    customerCommand->ExecuteNonQuery();
                }
                else {
                    // Insert into Users table with a default password if empty
                    String^ userQuery = "INSERT INTO Users (name, mobile, password) OUTPUT INSERTED.id VALUES (@name, @mobile, @password)";
                    SqlCommand^ userCommand = gcnew SqlCommand(userQuery, conn);
                    userCommand->Parameters->AddWithValue("@name", txtName->Text);
                    userCommand->Parameters->AddWithValue("@mobile", txtMobile->Text);
                    userCommand->Parameters->AddWithValue("@password", String::IsNullOrEmpty(txtPassword->Text) ? "default123" : txtPassword->Text); // Default password if empty
                    int userId = (int)userCommand->ExecuteScalar();

                    // Insert into Customers table
                    String^ customerQuery = "INSERT INTO Customers (user_id, membership_type, join_date, expiry_date, membership_fee) " +
                        "VALUES (@userId, @membershipType, @joinDate, @expiryDate, @membershipFee)";
                    SqlCommand^ customerCommand = gcnew SqlCommand(customerQuery, conn);
                    customerCommand->Parameters->AddWithValue("@userId", userId);
                    customerCommand->Parameters->AddWithValue("@membershipType", txtMembershipType->Text);
                    customerCommand->Parameters->AddWithValue("@joinDate", dtpJoinDate->Value.Date);
                    customerCommand->Parameters->AddWithValue("@expiryDate", dtpExpiryDate->Value.Date);
                    customerCommand->Parameters->AddWithValue("@membershipFee", membershipFee);
                    customerCommand->ExecuteNonQuery();
                }

                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Save Error: " + ex->Message, "Customer Save Failed");
            }
            finally {
                DatabaseHelper::CloseConnection();
            }
        }
    };
}