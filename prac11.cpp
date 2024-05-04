
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Record
{
private:
    int rollno;
    char name[20];
    char subject[20];
    int subcode;
    float internal_asses;
    float university_exam;

public:
    Record()
    {
        rollno = 0;
        strcpy(name, "");
        strcpy(subject, "");
        subcode = 0;
        internal_asses = 0.0;
        university_exam = 0.0;
    }

    int getRollno() { return rollno; }

    void getData()
    {
        cout << "\nEnter Details : ";
        cout << "\nRoll no : ";
        cin >> rollno;
        cout << "Name : ";
        cin >> name;
        cout << "Subject Code : ";
        cin >> subcode;
        cout << "Subject Name : ";
        cin >> subject;
        cout << "Internal Assessment Marks : ";
        cin >> internal_asses;
        cout << "University Exam Marks : ";
        cin >> university_exam;
    }

    void putData()
    {
        cout << "\nRoll No. : " << rollno;
        cout << "\t\tName : " << name;
        cout << "\nSubject Code : " << subcode;
        cout << "\tSubject Name : " << subject;
        cout << "\nInternal Assessment Marks : " << internal_asses;
        cout << "\nUniversity Exam Marks : " << university_exam << "\n\n";
    }
};

class File
{
private:
    ifstream fin;
    ofstream fout;

public:
    void insert();
    void display();
    void search(int);
    int Delete(int);
    int edit(int);
};

void File::insert()
{
    Record r;
    r.getData();
    fout.open("Madhu.dat", ios::ate | ios::app | ios::binary);
    fout.write(reinterpret_cast<char *>(&r), sizeof(r));
    fout.close();
}

void File::display()
{
    Record r;
    fin.open("Madhu.dat", ios::in | ios::binary);
    while (fin.read(reinterpret_cast<char *>(&r), sizeof(r)))
    {
        r.putData();
    }
    fin.close();
}

void File::search(int rollno)
{
    Record r;
    int found = 0;
    fin.open("Madhu.dat", ios::in | ios::binary);
    while (fin.read(reinterpret_cast<char *>(&r), sizeof(r)))
    {
        if (r.getRollno() == rollno)
        {
            cout << "\nRecord Found:";
            r.putData();
            found = 1;
            break;
        }
    }
    fin.close();
    if (!found)
        cout << "\nRecord not Found\n";
}

int File::Delete(int rollno)
{
    Record r;
    int found = 0;
    fin.open("Madhu.dat", ios::in | ios::binary);
    fout.open("Temp.dat", ios::out | ios::binary);
    while (fin.read(reinterpret_cast<char *>(&r), sizeof(r)))
    {
        if (r.getRollno() != rollno)
            fout.write(reinterpret_cast<char *>(&r), sizeof(r));
        else
            found = 1;
    }
    fin.close();
    fout.close();
    remove("Madhu.dat");
    rename("Temp.dat", "Madhu.dat");
    return found;
}

int File::edit(int rollno)
{
    Record r;
    int found = 0;
    fstream fs;
    fs.open("Madhu.dat", ios::in | ios::out | ios::binary);
    while (fs.read(reinterpret_cast<char *>(&r), sizeof(r)))
    {
        if (r.getRollno() == rollno)
        {
            found = 1;
            cout << "\nEnter New Details : ";
            r.getData();
            fs.seekp(-sizeof(r), ios::cur);
            fs.write(reinterpret_cast<char *>(&r), sizeof(r));
            break;
        }
    }
    fs.close();
    return found;
}

int main()
{
    File f;
    int ch, n, i, flag = 0;
    do
    {
        cout << "\n\n\t-----M E N U-----";
        cout << "\n\n1. Build A Master Table";
        cout << "\n2. List A Table";
        cout << "\n3. Insert a New Entry";
        cout << "\n4. Delete Old Entry";
        cout << "\n5. Edit an Entry";
        cout << "\n6. Search for a Record";
        cout << "\n7. Quit";
        cout << "\n Enter your Choice : ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            if (flag == 0)
            {
                cout << "\n Enter No of Records to insert : ";
                cin >> n;
                for (i = 0; i < n; i++)
                {
                    f.insert();
                }
                flag = 1;
            }
            else
            {
                cout << "\n Sorry.. Table is Already built...\n If want to add record please select Insert a New Entry in option.....";
            }
            break;
        case 2:
            f.display();
            break;
        case 3:
            f.insert();
            break;
        case 4:
            cout << "\nEnter Roll No of Student Whose Record is to be Deleted : ";
            cin >> n;
            if (f.Delete(n))
                cout << "\nRecord Deleted Successfully";
            else
                cout << "\nRecord not Found";
            break;
        case 5:
            cout << "\nEnter Roll No of Student Whose Record is to be Edited : ";
            cin >> n;
            if (f.edit(n))
                cout << "\nRecord Modified Successfully";
            else
                cout << "\nRecord not Found";
            break;
        case 6:
            cout << "\nEnter Roll No of Student Whose Record is to be Searched : ";
            cin >> n;
            f.search(n);
            break;
        case 7:
            break;
        default:
            cout << "\n Enter Valid Choice...";
        }
    } while (ch != 7);
    return 0;
}
