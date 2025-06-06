#pragma once
#using <System.dll>
#using <System.Data.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>
#include "DatabaseHelper.h"
#include "AddEditExercisePlanForm.h"

namespace GymManagementSystem {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Data::SqlClient;

    public ref class ExercisePlanForm : public System::Windows::Forms::Form {
    public:
        ExercisePlanForm() {
            try {
                InitializeComponent();
                LoadData();
            }
            catch (Exception^ ex) {
                MessageBox::Show("ExercisePlanForm Initialization Error: " + ex->Message + "\nStack Trace: " + ex->StackTrace, "Error");
            }
        }

    protected:
        ~ExercisePlanForm() {
            if (components) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        System::Windows::Forms::DataGridView^ dataGridView;
        System::Windows::Forms::Button^ btnAdd;
        System::Windows::Forms::Button^ btnEdit;
        System::Windows::Forms::Button^ btnDelete;

        void InitializeComponent() {
            try {
                this->components = gcnew System::ComponentModel::Container();
                this->dataGridView = gcnew System::Windows::Forms::DataGridView();
                this->btnAdd = gcnew System::Windows::Forms::Button();
                this->btnEdit = gcnew System::Windows::Forms::Button();
                this->btnDelete = gcnew System::Windows::Forms::Button();

                this->dataGridView->Dock = DockStyle::Top;
                this->dataGridView->Height = 400;
                this->dataGridView->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
                this->dataGridView->AllowUserToAddRows = false;
                this->dataGridView->ReadOnly = true;
                this->dataGridView->SelectionMode = DataGridViewSelectionMode::FullRowSelect;

                this->btnAdd->Text = "Add";
                this->btnAdd->Location = System::Drawing::Point(50, 450);
                this->btnAdd->Size = System::Drawing::Size(100, 30);
                this->btnAdd->Click += gcnew System::EventHandler(this, &ExercisePlanForm::OnAddClick);

                this->btnEdit->Text = "Edit";
                this->btnEdit->Location = System::Drawing::Point(160, 450);
                this->btnEdit->Size = System::Drawing::Size(100, 30);
                this->btnEdit->Click += gcnew System::EventHandler(this, &ExercisePlanForm::OnEditClick);

                this->btnDelete->Text = "Delete";
                this->btnDelete->Location = System::Drawing::Point(270, 450);
                this->btnDelete->Size = System::Drawing::Size(100, 30);
                this->btnDelete->Click += gcnew System::EventHandler(this, &ExercisePlanForm::OnDeleteClick);

                this->Text = "Manage Exercise Plans";
                this->Size = System::Drawing::Size(1000, 600);
                this->StartPosition = FormStartPosition::CenterScreen;
                this->Controls->Add(this->dataGridView);
                this->Controls->Add(this->btnAdd);
                this->Controls->Add(this->btnEdit);
                this->Controls->Add(this->btnDelete);
            }
            catch (Exception^ ex) {
                MessageBox::Show("InitializeComponent Error: " + ex->Message + "\nStack Trace: " + ex->StackTrace, "Error");
            }
        }

        void LoadData() {
            try {
                dataGridView->DataSource = DatabaseHelper::GetAllExercisePlans();
            }
            catch (Exception^ ex) {
                MessageBox::Show("LoadData Error: " + ex->Message + "\nStack Trace: " + ex->StackTrace, "Error");
            }
        }

        void OnAddClick(System::Object^ sender, System::EventArgs^ e) {
            try {
                AddEditExercisePlanForm^ form = gcnew AddEditExercisePlanForm(nullptr);
                if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                    LoadData();
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("OnAddClick Error: " + ex->Message + "\nStack Trace: " + ex->StackTrace, "Error");
            }
        }

        void OnEditClick(System::Object^ sender, System::EventArgs^ e) {
            try {
                if (dataGridView->SelectedRows->Count > 0) {
                    DataGridViewRow^ selectedRow = dataGridView->SelectedRows[0];
                    AddEditExercisePlanForm^ form = gcnew AddEditExercisePlanForm(selectedRow);
                    if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                        LoadData();
                    }
                }
                else {
                    MessageBox::Show("Please select a row to edit.", "Error");
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("OnEditClick Error: " + ex->Message + "\nStack Trace: " + ex->StackTrace, "Error");
            }
        }

        void OnDeleteClick(System::Object^ sender, System::EventArgs^ e) {
            try {
                if (dataGridView->SelectedRows->Count > 0) {
                    int id = System::Convert::ToInt32(dataGridView->SelectedRows[0]->Cells["id"]->Value);
                    if (MessageBox::Show("Are you sure you want to delete this exercise plan?",
                        "Confirm Delete", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes) {
                        String^ query = "DELETE FROM ExercisePlans WHERE id = @id";
                        DatabaseHelper::OpenConnection();
                        SqlCommand^ command = gcnew SqlCommand(query, DatabaseHelper::GetConnection());
                        command->Parameters->AddWithValue("@id", id);
                        if (command->ExecuteNonQuery() > 0) {
                            LoadData();
                            MessageBox::Show("Exercise Plan deleted successfully", "Success");
                        }
                        DatabaseHelper::CloseConnection();
                    }
                }
                else {
                    MessageBox::Show("Please select a row to delete.", "Error");
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("OnDeleteClick Error: " + ex->Message + "\nStack Trace: " + ex->StackTrace, "Error");
            }
        }
    };
}