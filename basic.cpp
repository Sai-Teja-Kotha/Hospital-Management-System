#include <bits/stdc++.h>
using namespace std;

class Hospital {
public:
    string name;
    string city;
    int beds;
    float rating;
    string contact;
    string doctor;
    int cost_per_bed;
    string specialization;
    string availability;
};

class Patient : public Hospital {
public:
    string name;
    int id;
    string appointment_date;
    string password;
    string contact;
};

class Doctor {
public:
    int doctor_id;
    string name;
    string specialization;
    string availability;
    int fee;
    string password;
};

void savePatientsToFile(const vector<Patient>& list) {
    ofstream file("patients.txt");
    for (const auto& p : list) {
        file << p.name << "," << p.id << "," << p.contact << "," << p.password << ","
             << p.Hospital::name << "," << p.cost_per_bed << "," << p.appointment_date << "," << p.doctor << "\n";
    }
    file.close();
}

vector<Patient> loadPatientsFromFile() {
    vector<Patient> patients;
    ifstream file("patients.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Patient p;
        getline(ss, p.name, ',');
        ss >> p.id; ss.ignore();
        getline(ss, p.contact, ',');
        getline(ss, p.password, ',');
        getline(ss, p.Hospital::name, ',');
        ss >> p.cost_per_bed; ss.ignore();
        getline(ss, p.appointment_date, ',');
        getline(ss, p.doctor, '\n');
        patients.push_back(p);
    }
    return patients;
}

bool authenticatePatient(const vector<Patient>& patients, int id, const string& password) {
    for (const auto& p : patients) {
        if (p.id == id && p.password == password) return true;
    }
    return false;
}

bool patientExists(const vector<Patient>& patients, int id) {
    for (const auto& p : patients) {
        if (p.id == id) return true;
    }
    return false;
}

void displayAllDoctors(const vector<Doctor>& doctors) {
    cout << "\n--- Available Doctors ---\n";
    for (const auto& doc : doctors) {
        cout << "Doctor ID: " << doc.doctor_id << ", Name: " << doc.name << ", Specialization: " << doc.specialization
             << ", Time: " << doc.availability << ", Fee: Rs. " << doc.fee << endl;
    }
}

bool authenticateDoctor(const vector<Doctor>& doctors, const string& name, const string& password) {
    for (const auto& d : doctors) {
        if (d.name == name && d.password == password) return true;
    }
    return false;
}

void doctorDashboard(int doctor_id, const vector<Doctor>& doctors, const vector<Patient>& patients) {
    auto it = find_if(doctors.begin(), doctors.end(), [&](const Doctor& d){ return d.doctor_id == doctor_id; });
    if (it == doctors.end()) {
        cout << "Doctor not found!\n";
        return;
    }
    string doctorName = it->name;
    cout << "\n--- Doctor Dashboard ---\n";
    cout << "Appointments for Dr. " << doctorName << ":\n";
    for (const auto& p : patients) {
        if (p.doctor == doctorName) {
            cout << "Patient Name: " << p.name << ", ID: " << p.id
                 << ", Appointment Date: " << p.appointment_date << ", Contact: " << p.contact << "\n";
        }
    }
}

void patientDashboard(vector<Patient>& patients, vector<Doctor>& doctors, int pid) {
    int choice;
    do {
        cout << "\n--- Patient Dashboard ---\n";
        cout << "1. View Doctors\n2. Book Appointment\n3. Logout\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                displayAllDoctors(doctors);
                break;
            case 2: {
                displayAllDoctors(doctors);
                string pname, contact, app_date;
                int id, doc_id;
                cout << "Enter Patient Name: "; cin >> pname;
                cout << "Enter Patient ID: "; cin >> id;
                cout << "Enter Contact: "; cin >> contact;
                cout << "Enter Appointment Date (YYYY-MM-DD): "; cin >> app_date;
                cout << "Enter Doctor ID: "; cin >> doc_id;

                auto it = find_if(doctors.begin(), doctors.end(), [&](Doctor& d) { return d.doctor_id == doc_id; });
                if (it == doctors.end()) {
                    cout << "Doctor not found!\n";
                    break;
                }

                Patient p;
                p.name = pname;
                p.id = id;
                p.password = "";
                p.contact = contact;
                p.appointment_date = app_date;
                p.Hospital::name = "CityCare Hospital";
                p.doctor = it->name;
                p.specialization = it->specialization;
                p.availability = it->availability;
                p.cost_per_bed = it->fee;
                patients.push_back(p);
                savePatientsToFile(patients);
                cout << "Appointment booked successfully!\n";
                break;
            }
            case 3:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}

void runSystem() {
    vector<Doctor> doctors = {
        {101, "Dr_Reddy", "Cardiology", "10:00 AM - 2:00 PM", 1500, "doc123"},
        {102, "Dr_Sharma", "Orthopedics", "11:00 AM - 3:00 PM", 1200, "doc123"},
        {103, "Dr_Iqbal", "Neurology", "9:00 AM - 1:00 PM", 1600, "doc123"},
        {104, "Dr_Singh", "Dermatology", "12:00 PM - 4:00 PM", 1000, "doc123"},
        {105, "Dr_Patel", "Gastroenterology", "2:00 PM - 6:00 PM", 1300, "doc123"},
        {106, "Dr_Kumar", "ENT", "10:30 AM - 1:30 PM", 1100, "doc123"},
        {107, "Dr_Bose", "Oncology", "3:00 PM - 7:00 PM", 1800, "doc123"},
        {108, "Dr_Das", "Pediatrics", "9:00 AM - 12:00 PM", 900, "doc123"},
        {109, "Dr_Varma", "Ophthalmology", "1:00 PM - 5:00 PM", 950, "doc123"},
        {110, "Dr_Gupta", "Psychiatry", "11:00 AM - 3:00 PM", 1400, "doc123"}
    };

    vector<Patient> patient_list = loadPatientsFromFile();

    int choice;
    cout << "\n--- Welcome to Hospital Management System ---\n";
    cout << "1. Patient Login\n2. Patient Sign Up\n3. Doctor Login\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        int login_id;
        string login_pass;
        cout << "\n--- Patient Login ---\n";
        cout << "Enter ID: "; cin >> login_id;
        cout << "Enter Password: "; cin >> login_pass;
        if (authenticatePatient(patient_list, login_id, login_pass)) {
            cout << "Patient login successful!\n";
            patientDashboard(patient_list, doctors, login_id);
        } else {
            cout << "Login failed. Returning to main menu...\n";
        }
    } else if (choice == 2) {
        string pname, contact, password;
        int id;
        cout << "\n--- Patient Sign Up ---\n";
        cout << "Enter Patient Name: "; cin >> pname;
        cout << "Enter Patient ID: "; cin >> id;
        cout << "Create Password: "; cin >> password;
        cout << "Enter Contact: "; cin >> contact;
        Patient p;
        p.name = pname;
        p.id = id;
        p.password = password;
        p.contact = contact;
        patient_list.push_back(p);
        savePatientsToFile(patient_list);
        cout << "Sign up successful! Please login.\n";
    } else if (choice == 3) {
        string doc_name, doc_pass;
        cout << "\n--- Doctor Login ---\n";
        cout << "Enter Doctor Name: "; cin >> doc_name;
        cout << "Enter Password: "; cin >> doc_pass;
        auto it = find_if(doctors.begin(), doctors.end(), [&](Doctor& d) {
            return d.name == doc_name && d.password == doc_pass;
        });
        if (it != doctors.end()) {
            cout << "Doctor login successful!\n";
            doctorDashboard(it->doctor_id, doctors, patient_list);
        } else {
            cout << "Doctor login failed!\n";
        }
    } else {
        cout << "Invalid choice.\n";
    }
}

int main() {
    runSystem();
    return 0;
}
