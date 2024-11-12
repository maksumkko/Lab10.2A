#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

enum Speciality { ITIS, RE, KN, KI, PZ };
string speciality_str[] = { "Інформатика ",
                            "Радіоелектроніка", "Комп'ютерні науки",
                            "Комп'ютерна інженерія", "Програмне забезпечення" };

struct Students
{
    string surname;
    int course;
    Speciality speciality;
    int grade_physics;
    int grade_math;
    int grade_info;

    double average_grade() const {
        return (grade_physics + grade_math + grade_info) / 3.0;
    }
};

void Create(Students* S, const int N);
void count_good_grades(Students* S, int N, int& count_math, int& count_physics, int& count_info, int& count_physics_5);
void Print(Students* S, const int N);
void Print_students_without_threes(Students* S, const int N);
void sort_students(Students* S, int N);
int binary_search(const Students* S, int N, const string& surname, Speciality speciality, double average);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: "; cin >> N;

    Students* S = new Students[N];

    Create(S, N);
    sort_students(S, N);
    Print(S, N);

    int count_math = 0;
    int count_physics = 0;
    int count_info = 0;
    int count_physics_5 = 0;

    count_good_grades(S, N, count_math, count_physics, count_info, count_physics_5);

    cout << "Кількість студентів, які отримали '5' з фізики: " << count_physics_5 << endl;

    cout << "Студенти, які вчаться без трійок (на 'відмінно' та 'добре'):" << endl;
    Print_students_without_threes(S, N);

    string search_surname;
    Speciality search_speciality;
    double search_average;

    cout << "Введіть прізвище для пошуку: "; cin >> search_surname;
    cout << "Введіть спеціальність (0 - Інформатика, 1 - Радіоелектроніка, 2 - Комп'ютерні науки, 3 - Комп'ютерна інженерія, 4 - Програмне забезпечення): ";
    int speciality_input;
    cin >> speciality_input;
    search_speciality = (Speciality)speciality_input;
    cout << "Введіть середній бал: "; cin >> search_average;

    int index = binary_search(S, N, search_surname, search_speciality, search_average);

    if (index != -1) {
        cout << "Студент знайдений на позиції: " << index + 1 << endl;
    }
    else {
        cout << "Студент не знайдений." << endl;
    }

    delete[] S;
    return 0;
}

void Create(Students* S, const int N)
{
    for (int i = 0; i < N; i++)
    {
        int speciality;
        cout << "Номер студента: " << i + 1 << endl;
        cin.get();
        cin.sync();
        cout << "Прізвище: "; getline(cin, S[i].surname); cout << endl;
        cout << "Курс: "; cin >> S[i].course; cout << endl;
        cout << "Спеціальність(0 - Інформатика, 1 - Радіоелектроніка, 2 - Комп'ютерні науки," << endl;
        cout << "3 - Комп'ютерна інженерія, 4 - Програмне забезпечення): ";
        cin >> speciality;
        S[i].speciality = (Speciality)speciality;
        cout << "Оцінка з фізики: "; cin >> S[i].grade_physics; cout << endl;
        cout << "Оцінка з математики: "; cin >> S[i].grade_math; cout << endl;
        cout << "Оцінка з інформатики: "; cin >> S[i].grade_info; cout << endl;
        cout << endl;
    }
}

void count_good_grades(Students* S, int N, int& count_math, int& count_physics, int& count_info, int& count_physics_5)
{
    count_math = 0;
    count_physics = 0;
    count_info = 0;
    count_physics_5 = 0;

    for (int i = 0; i < N; i++) {
        if (S[i].grade_math == 4) {
            count_math++;
        }
        if (S[i].grade_physics == 4) {
            count_physics++;
        }
        if (S[i].grade_info == 4) {
            count_info++;
        }
        if (S[i].grade_physics == 5) {
            count_physics_5++;
        }
    }
}

void Print(Students* S, const int N)
{
    cout << "==================================================================================================================" << endl;
    cout << "|  №  |   Прізвище   |  Курс  |     Спеціальність     |  Фізика  |  Математика  |  Інформатика  |  Середній бал  |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        double avg = S[i].average_grade();
        cout << "|" << setw(4) << left << i + 1 << " ";
        cout << "|" << setw(14) << left << S[i].surname;
        cout << "|" << setw(8) << left << S[i].course;
        cout << "|" << setw(23) << left << speciality_str[S[i].speciality];
        cout << "|" << setw(10) << left << S[i].grade_physics;
        cout << "|" << setw(14) << left << S[i].grade_math;
        cout << "|" << setw(15) << left << S[i].grade_info;
        cout << "|" << setw(15) << left << fixed << setprecision(2) << avg << "|" << endl;
    }
    cout << "=============================================================================================================" << endl << endl;
}

void Print_students_without_threes(Students* S, const int N)
{
    for (int i = 0; i < N; i++)
    {
        if (S[i].grade_physics > 3 && S[i].grade_math > 3 && S[i].grade_info > 3)
        {
            cout << S[i].surname << endl;
        }
    }
}

void sort_students(Students* S, int N)
{
    sort(S, S + N, [](const Students& a, const Students& b) {
        if (a.speciality != b.speciality) {
            return a.speciality < b.speciality;
        }
        if (a.average_grade() != b.average_grade()) {
            return a.average_grade() > b.average_grade();  // більший середній бал йде першим
        }
        return a.surname < b.surname;
        });
}

int binary_search(const Students* S, int N, const string& surname, Speciality speciality, double average)
{
    int left = 0, right = N - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        const Students& student = S[mid];

        if (student.speciality < speciality || (student.speciality == speciality && student.average_grade() < average) ||
            (student.speciality == speciality && student.average_grade() == average && student.surname < surname)) {
            left = mid + 1;
        }
        else if (student.speciality > speciality || (student.speciality == speciality && student.average_grade() > average) ||
            (student.speciality == speciality && student.average_grade() == average && student.surname > surname)) {
            right = mid - 1;
        }
        else {
            return mid;
        }
    }

    return -1; // не знайдений
}