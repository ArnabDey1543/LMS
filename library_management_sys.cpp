#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <fstream>

using namespace std;

class book
{
    char bookNo[6];
    char bookName[50];
    char authorName[20];

public:
    // function to create book...
    void create_book()
    {
        cout << "\nNEW BOOK ENTRY...\n";
        cout << "\nENTER THE BOOK NUMBER";
        cin >> bookNo;
        cout << "\nENTER THE BOOK NAME";
        gets(bookName);
        cout << "\nENTER THE AUTHOR NAME";
        gets(authorName);
        cout << "\n\nBOOK CREATED";
    }

    // fucntion to display book...
    void showBook()
    {
        cout << "\nBOOK NUMBER : " << bookNo;
        cout << "\nBOOK NAME : ";
        puts(bookName);
        cout << "\nAUTHOR NAME : ";
        puts(authorName);
    }

    // function to modify book...
    void modify_book()
    {
        cout << "\nBOOK NUMBER : " << bookNo;
        cout << "\nMODIFY BOOK NAME : ";
        gets(bookName);
        cout << "\nMODIFY AUTHOR'S NAME : ";
        gets(authorName);
    }

    char* return_bookNo()
    {
        return bookNo;
    }

    void report()
    {
        cout << bookNo << setw(30) << bookName << setw(20) << authorName << endl;
    }

}; // class end here

class student
{
    char admno[6];
    char name[20];
    char stu_bookNo[6];
    int token;

public:
    void createstudent()
    {
        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "\nEnter your Admission number ";
        cin >> admno;
        cout << "\nEnter the Student name ";
        gets(name);
        token = 0;
        stu_bookNo[0] = '\0';
        cout << "\nStudent record created..";
    }

    void show_student()
    {
        cout << "\nAdmission Number : " << admno;
        cout << "\nStudent Name : ";
        puts(name);
        cout << "\nNumber of books issued : " << token;
        if (token == 1)
        {
            cout << "\nBook Number : " << stu_bookNo;
        }
    }

    void modify_stu()
    {
        cout << "\nAdmission Number : " << admno;
        cout << "\nModify Student Name : ";
        gets(name);
    }

    char *ret_admNo()
    {
        return admno;
    }

    char *ret_stuBookNo()
    {
        return stu_bookNo;
    }

    int ret_token()
    {
        return token;
    }

    void add_token()
    {
        token = 1;
    }

    void reset_token()
    {
        token = 0;
    }

    void get_stuBookNo(char t[])
    {
        strcpy(stu_bookNo, t);
    }

    void report()
    {
        cout << "\t" << admno << setw(20) << name << setw(10) << token << endl;
    }

}; // class ends here

// file Handling for book, student
fstream fp, fp1;
book bk;
student st;

void write_book()
{
    char ch;
    fp.open("book.dat", ios::out | ios::app);
    do
    {
        bk.create_book();
        fp.write((char *)&bk, sizeof(book));
        cout << "\n\nDo you want to add more record...(y/n?)";
        cin >> ch;

    } while (ch == 'Y' || ch == 'y');
    fp.close();
}

void write_stu()
{
    char ch;
    fp.open("student.dat", ios::out | ios::app);
    do
    {
        st.createstudent();
        fp.write((char *)&bk, sizeof(student));
        cout << "\n\nDo you want to add more record...(y/n?)";
        cin >> ch;

    } while (ch == 'Y' || ch == 'y');
    fp.close();
}

void disp_spe_book(char n[])
{
    cout << "\nBOOK DETAILS\n";
    int flag = 0;

    fp.open("book.dat", ios::in);
    while (fp.read((char *)&bk, sizeof(book)))
    {
        if (strcmpi(bk.return_bookNo(), n) == 0)
        {
            bk.showBook();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
    {
        cout << "Book does not exist";
        getch();
    }
}

void disp_spe_stu(char n[])
{
    cout << "\nSTUDENT DETAILS\n";
    int flag = 0;

    fp.open("student.dat", ios::in);
    while (fp.read((char *)&st, sizeof(student)))
    {
        if (strcmpi(st.ret_admNo(), n) == 0)
        {
            st.show_student();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
    {
        cout << "Student does not exist";
        getch();
    }
}

void modify_book()
{
    char n[6];
    int found = 0;
    cout << "\n\nMODIFY BOOK RECORD...";
    cout << "\n\nEnter the book No. ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    while (fp.read((char *)&bk, sizeof(book)) && found == 0)
    {
        if (strcmpi(bk.return_bookNo(), n) == 0)
        {
            bk.showBook();
            cout << "\nEnter the new details of book" << endl;
            bk.modify_book();
            int pos = -1 * sizeof(bk);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&bk, sizeof(book));
            cout << "\n\n\t RECORD UPDATED..";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        cout << "\n\nRECORD NOT FOUND";
    }
    getch();
}

void modify_stu()
{
    char n[6];
    int found = 0;
    cout << "\n\nMODIFY STUDENT RECORD...";
    cout << "\n\nEnter the admission no. ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0)
    {
        if (strcmpi(st.ret_admNo(), n) == 0)
        {
            st.show_student();
            cout << "\nEnter the new details of book" << endl;
            st.modify_stu();
            int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&st, sizeof(student));
            cout << "\n\n\t RECORD UPDATED..";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        cout << "\n\nRECORD NOT FOUND";
    }
    getch();
}

void del_stu()
{
    char n[6];
    int flag = 0;
    cout << "\n\n\n\tDELETE STUDENT...";
    cout << "\n\nEnter the Admission no. : ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&st, sizeof(student)))
    {
        if (strcmpi(st.ret_admNo(), n) != 0)
        {
            fp2.write((char *)&st, sizeof(student));
        }
        else
        {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");
    if (flag == 1)
    {
        cout << "\n\n\tRECORD DELETED...";
    }
    else
    {
        cout << "\n\nRECORD NOT FOUND...";
    }
    getch();
}

void del_book()
{
    char n[6];
    int flag = 0;
    cout << "\n\n\n\tDELETE BOOK...";
    cout << "\n\nEnter the Book no. : ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&st, sizeof(book)))
    {
        if (strcmpi(st.ret_stuBookNo(), n) != 0)
        {
            fp2.write((char *)&st, sizeof(book));
        }
        else
        {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("book.dat");
    rename("temp.dat", "book.dat");
    if (flag == 1)
    {
        cout << "\n\n\tRECORD DELETED...";
    }
    else
    {
        cout << "\n\nRECORD NOT FOUND...";
    }
    getch();
}

void disp_all_stu()
{
    fp.open("student.dat", ios::in );
    if (!fp)
    {
        cout << "FILE COULD NOT BE OPEN";
        getch();
        return;
    }
    cout << "\n\n\t\tStudent List\n\n";
    cout << "================================================================\n";
    cout << "\tAdmission Number" << setw(10) << "Name" << setw(20) << "Book Issued\n";
    cout << "================================================================\n";
    while (fp.read((char*)&st, sizeof(student)))
    {
        st.report();
    }
    fp.close();
    getch();
}

void disp_all_book()
{
    fp.open("book.dat", ios::in);
    if (!fp)
    {
        cout << "FILE COULD NOT BE OPEN";
        getch();
        return;
    }
    cout << "\n\n\t\tBook Lidt\n\n";
    cout << "===============================================================\n";
    cout << "\tBook Number" << setw(20) << "Book Name" << setw(25) << "Author\n";
    cout << "===============================================================\n";
    while (fp.read((char *)&bk, sizeof(book)))
    {
        bk.report();
    }
    fp.close();
    getch();
}

void bookissue()
{
    char sn[6], bn[6];
    int found = 0, flag = 0;
    cout << "\n\nBOOK ISSUE...";
    cout << "\n\n\tEnter admission number of the student";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(student)) && found == 0)
    {
        if (strcmpi(st.ret_admNo(), sn) == 0)
        {
            found = 1;

            if (st.ret_token() == 0)
            {
                cout << "\n\n\tEnter the Book number";
                cin >> bn;
                while (fp1.read((char *)&bk, sizeof(book)) && flag == 0)
                {
                    if (strcmpi(st.ret_stuBookNo(), bn) == 0)
                    {
                        flag = 1;
                        st.add_token();
                        st.get_stuBookNo(bk.return_bookNo());
                        int pos = -1 * sizeof(st);
                        fp.seekg(pos, ios::cur);
                        fp.write((char *)&st, sizeof(student));
                        cout << "\n\n\tBook issued successfully\n\nPlease Note : Write the Book issue date in backside of your Book and return book within 15 days, Fine Rs.1 for each day after 15 days period";
                    }
                }
                if (flag == 0)
                {
                    cout << "BOOK NUMBER DOES NOT EXIST";
                }
            }
            else
            {
                cout << "You have not returned the last book";
            }
        }
    }
    if (found == 0)
    {
        cout << "STUDENT RECORD DOES NOT EXIST";
    }
    getch();
    fp.close();
    fp1.close();
}

void book_deposit()
{
    char sn[6], bn[6];
    int found = 0, flag = 0, day, fine;
    cout << "\n\nBOOK DEPOSIT...";
    cout << "\n\n\tEnter admission number of the student";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0)
    {
        if (strcmpi(st.ret_admNo(), sn) == 0)
        {
            found = 1;

            if (st.ret_token() == 0)
            {

                while (fp1.read((char *)&bk, sizeof(book)) && flag == 0)
                {
                    if (strcmpi(bk.return_bookNo(), st.ret_stuBookNo()) == 0)
                    {
                        flag = 1;
                        bk.showBook();
                        cout << "\n\nBook Deposited in no. of days";
                        cin >> day;
                        if (day > 15)
                        {
                            fine = (day - 15) * 1;
                            cout << "\n\nFine has to deposited Rs. " << fine;
                        }
                        st.reset_token();
                        int pos = -1 * sizeof(st);
                        fp.seekg(pos, ios::cur);
                        fp.write((char *)&st, sizeof(student));
                        cout << "\n\n\tBook issued successfully";
                    }
                }
                if (flag == 0)
                {
                    cout << "BOOK NUMBER DOES NOT EXIST";
                }
            }
            else
            {
                cout << "No book is issued..";
            }
        }
    }
    if (found == 0)
    {
        cout << "STUDENT RECORD DOES NOT EXIST";
    }
    getch();
    fp.close();
    fp1.close();
}

void start()
{
    // clrscr();
    // gotoxy(35,11);
    cout << "LIBRARY ";
    // gotoxy(35,14);
    cout << "MANAGEMENT ";
    // gotoxy(35,17);
    cout << "SYSTEM";
    cout << "\n\nDEVELOPER : ARNAB DEY    GITHUB : https://www.linkedin.com/in/arnab-dey-65b814222/ \n\n\t";
    getch();
}

void Admin_menu()
{
    int ch2;
    cout << "\n\n\n\tADMINISTRATOR MENU";
    cout << "\n\n\t1. Create student record";
    cout << "\n\n\t2. Display all student record";
    cout << "\n\n\t3. Display student record";
    cout << "\n\n\t4. Modify student record";
    cout << "\n\n\t5. Delete student record";
    cout << "\n\n\t6. Create book";
    cout << "\n\n\t7. Display all book";
    cout << "\n\n\t8. Display specific book";
    cout << "\n\n\t9. Modify book record";
    cout << "\n\n\t10. Delete book record";
    cout << "\n\n\t11. BACK TO MAIN MENU";
    cout << "\n\n\t12. Please Enter Your Choice(1-11)";
    cin >> ch2;
    switch (ch2)
    {
    case 1:
        write_stu();
        break;
    case 2:
        disp_all_stu();
        break;
    case 3:
        char num[6];
        cout << "Enter the admisssion no.";
        cin >> num;
        disp_spe_stu(num);
        break;
    case 4:
        modify_stu();
        break;
    case 5:
        del_stu();
        break;
    case 6:
        write_book();
        break;
    case 7:
        disp_all_book();
        break;
    case 8:
    {
        char num[6];
        cout << "Enter the book no.";
        cin >> num;
        disp_spe_book(num);
        break;
    }
    case 9:
        modify_book();
        break;
    case 10:
        del_book();
        break;
    case 11:
        return;
    default:
        cout << "INVALID CHOICE , TRY AGAIN";
    }
    Admin_menu();
}

// driver function..

int main()
{
    char ch;
    start();

    do
    {
        // clrscr();
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\n\t1. BOOK ISSUE";
        cout << "\n\n\n\t2. BOOK DEPOSIT";
        cout << "\n\n\n\t3. ADMINISTRATOR MENU";
        cout << "\n\n\n\t4. EXIT";
        cout << "\n\n\n\tPLEASE SELET YOUR OPTION (1-4)";
        ch = getche();
        switch (ch)
        {
        case '1':
            bookissue();
            break;
        case '2':
            book_deposit();
            break;
        case '3':
            Admin_menu();
            break;
        case '4':
            exit(0);
            break;
        default:
            cout << "INVALID CASE , TRY AGAIN";
        }
    } while (ch != 4);
}