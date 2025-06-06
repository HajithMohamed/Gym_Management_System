#include "loginForm.h"
#include "AdminForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    GymManagementSystem::LoginForm^ loginForm = gcnew GymManagementSystem::LoginForm();
    DialogResult result = loginForm->ShowDialog();
    MessageBox::Show("DialogResult: " + result.ToString(), "Debug Info"); // Debug
    if (result == System::Windows::Forms::DialogResult::OK) {
        try {
            MessageBox::Show("Launching AdminForm", "Debug Info"); // Debug
            Application::Run(gcnew GymManagementSystem::AdminForm());
        }
        catch (Exception^ ex) {
            MessageBox::Show("AdminForm Error: " + ex->Message, "Error");
        }
    }
    return 0;
}