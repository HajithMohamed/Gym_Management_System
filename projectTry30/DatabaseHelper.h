#pragma once
#using <System.dll>
#using <System.Data.dll>
#using <System.Windows.Forms.dll>
#include <msclr/marshal_cppstd.h>
#include <msclr/marshal.h>
#include <vcclr.h>

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Windows::Forms;

namespace GymManagementSystem {
    public ref class DatabaseHelper {
    private:
        static String^ connectionString = "Data Source=localhost\\sqlexpress;Initial Catalog=GymManagementSystem;Integrated Security=True;Encrypt=True;TrustServerCertificate=True";
        static SqlConnection^ connection;

    public:
        static void Initialize() {
            connection = gcnew SqlConnection(connectionString);
            try {
                connection->Open();
                MessageBox::Show("Database connection successful!");
                connection->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Database connection failed: " + ex->Message);
            }
        }

        static void OpenConnection() {
            if (connection == nullptr) Initialize();
            if (connection->State == ConnectionState::Closed)
                connection->Open();
        }

        static void CloseConnection() {
            if (connection != nullptr && connection->State == ConnectionState::Open)
                connection->Close();
        }

        static SqlConnection^ GetConnection() {
            if (connection == nullptr) Initialize();
            return connection;
        }

        static DataTable^ ExecuteQuery(String^ query) {
            DataTable^ dataTable = gcnew DataTable();
            try {
                OpenConnection();
                SqlCommand^ command = gcnew SqlCommand(query, connection);
                SqlDataAdapter^ adapter = gcnew SqlDataAdapter(command);
                adapter->Fill(dataTable);
            }
            catch (Exception^ ex) {
                MessageBox::Show("Database Error: " + ex->Message);
            }
            finally {
                CloseConnection();
            }
            return dataTable;
        }

        static int ExecuteNonQuery(String^ query) {
            int result = 0;
            try {
                OpenConnection();
                SqlCommand^ command = gcnew SqlCommand(query, connection);
                result = command->ExecuteNonQuery();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Database Error: " + ex->Message);
            }
            finally {
                CloseConnection();
            }
            return result;
        }

        static DataTable^ GetAllTrainers() {
            return ExecuteQuery("SELECT t.*, u.name, u.mobile FROM Trainers t JOIN Users u ON t.user_id = u.id");
        }

        static DataTable^ GetAllCustomers() {
            return ExecuteQuery("SELECT c.*, u.name, u.mobile FROM Customers c JOIN Users u ON c.user_id = u.id");
        }

        static DataTable^ GetAllGymHalls() {
            return ExecuteQuery("SELECT * FROM GymHalls");
        }

        static DataTable^ GetAllEquipment() {
            return ExecuteQuery("SELECT * FROM Equipment");
        }

        static DataTable^ GetAllExercisePlans() {
            return ExecuteQuery("SELECT ep.*, c.user_id as customer_user_id, t.user_id as trainer_user_id, " +
                "cu.name as customer_name, tu.name as trainer_name " +
                "FROM ExercisePlans ep " +
                "JOIN Customers c ON ep.customer_id = c.id " +
                "JOIN Trainers t ON ep.trainer_id = t.id " +
                "JOIN Users cu ON c.user_id = cu.id " +
                "JOIN Users tu ON t.user_id = tu.id");
        }
    };
}