#pragma once
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Data.dll>
#include "DatabaseHelper.h"

namespace GymManagementSystem {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Data::SqlClient;

    public ref class LoginForm : public System::Windows::Forms::Form {
    public:
        LoginForm() {
            InitializeComponent();
        }

    protected:
        ~LoginForm() {
            if (components) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        System::Windows::Forms::Label^ lblUsername;
        System::Windows::Forms::TextBox^ txtUsername;
        System::Windows::Forms::Label^ lblPassword;
        System::Windows::Forms::TextBox^ txtPassword;
        System::Windows::Forms::Button^ btnLogin;

        void InitializeComponent() {
            this->components = gcnew System::ComponentModel::Container();
            this->lblUsername = gcnew System::Windows::Forms::Label();
            this->txtUsername = gcnew System::Windows::Forms::TextBox();
            this->lblPassword = gcnew System::Windows::Forms::Label();
            this->txtPassword = gcnew System::Windows::Forms::TextBox();
            this->btnLogin = gcnew System::Windows::Forms::Button();

            // Form setup
            this->Text = "Gym Management System Login";
            this->Size = System::Drawing::Size(300, 220);
            this->StartPosition = FormStartPosition::CenterScreen;

            // Username Label
            this->lblUsername->Text = "Username:";
            this->lblUsername->Location = System::Drawing::Point(20, 30);
            this->lblUsername->Size = System::Drawing::Size(80, 20);

            // Username TextBox
            this->txtUsername->Location = System::Drawing::Point(100, 30);
            this->txtUsername->Size = System::Drawing::Size(150, 20);
            this->txtUsername->Text = ""; // Removed default value

            // Password Label
            this->lblPassword->Text = "Password:";
            this->lblPassword->Location = System::Drawing::Point(20, 60);
            this->lblPassword->Size = System::Drawing::Size(80, 20);

            // Password TextBox
            this->txtPassword->Location = System::Drawing::Point(100, 60);
            this->txtPassword->Size = System::Drawing::Size(150, 20);
            this->txtPassword->UseSystemPasswordChar = true;
            this->txtPassword->Text = ""; // Removed default value

            // Login Button
            this->btnLogin->Text = "Sign In";
            this->btnLogin->Location = System::Drawing::Point(100, 100);
            this->btnLogin->Size = System::Drawing::Size(100, 30);
            this->btnLogin->Click += gcnew System::EventHandler(this, &LoginForm::OnLoginClick);

            // Add controls to form
            this->Controls->Add(this->lblUsername);
            this->Controls->Add(this->txtUsername);
            this->Controls->Add(this->lblPassword);
            this->Controls->Add(this->txtPassword);
            this->Controls->Add(this->btnLogin);
        }

        void OnLoginClick(System::Object^ sender, System::EventArgs^ e) {
            try {
                // Validate input fields
                if (String::IsNullOrEmpty(txtUsername->Text) || String::IsNullOrEmpty(txtPassword->Text)) {
                    MessageBox::Show("Please enter both username and password.", "Input Error");
                    return;
                }

                String^ query = "SELECT * FROM Users WHERE name = @username AND password = @password";
                DataTable^ dt = gcnew DataTable();
                DatabaseHelper::OpenConnection();
                SqlCommand^ command = gcnew SqlCommand(query, DatabaseHelper::GetConnection());
                command->Parameters->AddWithValue("@username", txtUsername->Text);
                command->Parameters->AddWithValue("@password", txtPassword->Text);
                SqlDataAdapter^ adapter = gcnew SqlDataAdapter(command);
                adapter->Fill(dt);
                if (dt->Rows->Count > 0) {
                    this->DialogResult = System::Windows::Forms::DialogResult::OK;
                    this->Close();
                }
                else {
                    MessageBox::Show("Invalid username or password.", "Login Failed");
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Login Error: " + ex->Message, "Login Failed");
            }
            finally {
                DatabaseHelper::CloseConnection();
            }
        }
    };
}