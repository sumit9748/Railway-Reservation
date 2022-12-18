#include <bits/stdc++.h>
using namespace std;

class train
{
private:
    // train details
    int si;
    long tno;
    string tname;
    string splace;
    string dplace;
    int price;
    int seats = 700;
    string time;
    // book details
    string passname;
    string passphone;
    int passtrainnum;
    int passseats;
    string passdate;
    int passfare;
    // user validation
    string email;
    string pass;

public:
    void menu();
    void view();
    void bookticket();
    void cancelticket();
    void admin();
    void viewpass();
    void addtrain();
    void deletetrain();
    void updatetrain();
};

void train::view()
{

    fstream data;
    string t;

    if (!data)
    {
        cout << "sorry no record found...\n";
        return;
    }
    else
    {
        data.open("train.txt", ios::in);
        cout << "SI\train no\train name\tstart place\tdestination place\tprice\tseat\ttime\n";
        data >> si >> tno >> tname >> splace >> dplace >> price >> seats >> time;

        while (!data.eof())
        {
            cout << si << "\t" << tno << "\t" << tname << "\t" << splace << "\t" << dplace << "\t" << price << "\t" << seats << "\t" << time << endl;
            data >> si >> tno >> tname >> splace >> dplace >> price >> seats >> time;
        }
        data.close();
    }
}
void train::bookticket()
{
    fstream data, data1, book;
    cout << "\n\t****welcome to train booking system****\n";
    int trno, avlseats, fare, flg = 0;
    string pname, pphone, date;

    cout << "Enter your name: ";
    cin >> pname;
    cout << "Enter your phone number: ";
    cin >> pphone;
    cout << "Enter train number: ";
    cin >> trno;
    cout << "Enter number of seats: ";
    cin >> avlseats;
    cout << "Enter date :";
    cin >> date;

    data.open("train.txt", ios::in);
    data >> si >> tno >> tname >> splace >> dplace >> price >> seats >> time;
    data1.open("train1.txt", ios::app | ios::out);

    while (!data.eof())
    {
        if (tno == trno)
        {
            fare = price;
            if (seats - avlseats < 0)
            {
                cout << "Number of seats available is 0:\n";
                remove("train1.txt");
                data.close();
                data1.close();
                admin();
            }
            data1 << " " << si << " " << tno << " " << tname << " " << splace << " " << dplace << " " << price << " " << (seats - avlseats) << " " << time << endl;
        }
        else
        {
            data1 << " " << si << " " << tno << " " << tname << " " << splace << " " << dplace << " " << price << " " << seats << " " << time << endl;
        }
        data >> si >> tno >> tname >> splace >> dplace >> price >> seats >> time;
    }
    data.close();
    data1.close();

    remove("train.txt");
    rename("train1.txt", "train.txt");
    book.open("bookseat.txt", ios::in);

    if (!book)
    {
        book.open("bookseat.txt", ios::app | ios::out);

        book << " " << pname << " " << pphone << " " << trno << " " << avlseats << " " << date << " " << (avlseats * fare) << endl;
        book.close();
    }
    else
    {

        book >> passname >> passphone >> passtrainnum >> passseats >> passdate >> passfare;
        while (!book.eof())
        {
            if (pphone == passphone && passtrainnum == trno)
            {
                flg = 1;
                break;
            }
            book >> passname >> passphone >> passtrainnum >> passseats >> passdate >> passfare;
        }
        book.close();
        if (flg == 0)
        {
            book.open("bookseat.txt", ios::app | ios::out);
            book << " " << pname << " " << pphone << " " << trno << " " << avlseats << " " << date << " " << (avlseats * fare) << endl;
            book.close();
        }
        else
        {
            cout << "you already book\n";
        }
    }
    cout << "total amount :" << (avlseats * fare) << endl;
    cout << "successfully booked ...\n";

    admin();
}
void train::cancelticket()
{
    fstream data, data1, book, book1;
    int delseat, trno, flg = 0;

    string phone;
    cout << "\n****Cancel Booking****\n";
m:
    cout << "\nEnter your phone number";
    cin >> phone;
    book.open("bookseat.txt", ios::in);
    if (!book)
    {
        cout << "sorry no record found\n";
        menu();
    }
    else
    {

        book1.open("bookseat1.txt", ios::app | ios::out);

        book >> passname >> passphone >> passtrainnum >> passseats >> passdate >> passfare;
        while (!book.eof())
        {
            if (passphone == phone)
            {
                delseat = passseats;
                trno = passtrainnum;
                cout << "\nbooking cancelation sucessfull\n";
                flg = 1;
            }
            else
            {
                book1 << " " << passname << " " << passphone << " " << passtrainnum << " " << passseats << " " << passdate << " " << passfare << endl;
            }
            book >> passname >> passphone >> passtrainnum >> passseats >> passdate >> passfare;
        }
        book.close();
        book1.close();
        remove("bookseat.txt");
        rename("bookseat1.txt", "bookseat.txt");

        if (flg == 0)
        {
            cout << "wrong input..\n";
            goto m;
        }
        else
        {
            data.open("train.txt", ios::in);
            data1.open("train1.txt", ios::app | ios::out);

            data >> si >> tno >> tname >> splace >> dplace >> price >> seats >> time;

            while (!data.eof())
            {
                if (tno == trno)
                {
                    data1 << " " << si << " " << tno << " " << tname << " " << splace << " " << dplace << " " << price << " " << (seats + delseat) << " " << time << endl;
                }
                else
                {
                    data1 << " " << si << " " << tno << " " << tname << " " << splace << " " << dplace << " " << price << " " << seats << " " << time << endl;
                }
                data >> si >> tno >> tname >> splace >> dplace >> price >> seats >> time;
            }
            data.close();
            data1.close();
            remove("train.txt");
            rename("train1.txt", "train.txt");
            menu();
        }
    }

    menu();
}
void train::admin()
{
    string e, p;
    cout << "\n\t**Login**\n";
    cout << "\nYour Email\n";
    cin >> e;
    cout << "\nYour Password\n";
    cin >> p;

    fstream user;
    int flg = 0;
    user.open("userdata.txt", ios::in);
    user >> email >> pass;
    while (!user.eof())
    {
        if (email == e && pass == p)
        {
            flg = 1;
        }
        user >> email >> pass;
    }
    if (flg == 0)
    {
        cout << "\nwrong credentials..\n";
        menu();
    }

    cout << "\t******************************\n";
    cout << "\t\t choose your task\n";
    cout << "\t******************************\n";
    cout << "[1] view passengers\n";
    cout << "[2] add train\n";
    cout << "[3] delete train\n";
    cout << "[4] update train\n";
    cout << "[5] back\n";

m:
    int ch;
    cin >> ch;
    switch (ch)
    {
    case 1:
    {
        viewpass();
        break;
    }
    case 2:
    {
        addtrain();
        break;
    }
    case 3:
    {
        deletetrain();
        break;
    }
    case 4:
    {
        updatetrain();
        break;
    }
    case 5:
    {
        admin();
        break;
    }
    default:
    {
        goto m;
        break;
    }
    }
}

void train::viewpass()
{
    fstream book;

    book.open("bookseat.txt", ios::in);
    if (!book)
    {
        cout << "Database is empty..\n";
        admin();
    }
    else
    {
        book >> passname >> passphone >> passtrainnum >> passseats >> passdate >> passfare;

        cout << "passenger name"
             << "\t"
             << "passenger phone"
             << "\t"
             << "train number"
             << "\t"
             << "seats booked"
             << "\t"
             << "booking date"
             << "\t"
             << "total fare" << endl;
        while (!book.eof())
        {
            cout << passname << "\t" << passphone << "\t" << passtrainnum << "\t" << passseats << "\t" << passdate << "\t" << passfare << endl;
            book >> passname >> passphone >> passtrainnum >> passseats >> passdate >> passfare;
        }
    }
}
void train::addtrain()
{
    cout << "\n\t****add train****\n";

    fstream data;
    int token = 0;
m:
    int sn;
    int tr_no;
    string t_name;
    string st_p;
    string ds_p;
    int price;
    int avl_seats;
    string dep;

    cout << "\nEnter serial number :";
    cin >> sn;
    cout << "\nEnter train number :";
    cin >> tr_no;
    cout << "\nEnter train name :";
    cin >> t_name;
    cout << "\nEnter train start point :";
    cin >> st_p;
    cout << "\nEnter train destination point :";
    cin >> ds_p;
    cout << "\nEnter train fair :";
    cin >> price;
    cout << "\nEnter total seats :";
    cin >> avl_seats;
    cout << "\nEnter departure time :";
    cin >> dep;
    data.open("train.txt", ios::in);
    if (!data)
    {
        data.open("train.txt", ios::app | ios::out);
        data << " " << sn << " " << tr_no << " " << t_name << " " << st_p << " " << ds_p << " " << price << " " << avl_seats << " " << dep << endl;
        data.close();
        admin();
    }

    data >> si >> tno >> tname >> splace >> dplace >> price >> seats >> time;
    while (!data.eof())
    {
        if (tr_no == tno)
        {
            token = 1;
            break;
        }
        data >> si >> tno >> tname >> splace >> dplace >> price >> seats >> time;
    }
    data.close();

    if (token == 1)
    {
        cout << "train already exist..\n";
        menu();
    }
    else
    {
        data.open("train.txt", ios::app | ios::out);
        data << " " << sn << " " << tr_no << " " << t_name << " " << st_p << " " << ds_p << " " << price << " " << avl_seats << " " << dep << endl;
        data.close();
        admin();
    }
}

void train::deletetrain()
{
    cout << "\n\t****delete train****\n";
    fstream data, data1;

    int trno, flag = 0;
    cout << "\nEnter the train number ";
    cin >> trno;
    data.open("train.txt", ios::in);
    if (!data)
    {
        cout << "sorry no train exists...\n";
        admin();
    }
    else
    {
        data1.open("train1.txt", ios::app | ios::out);
        data >> si >> tno >> tname >> splace >> dplace >> price >> seats >> time;

        while (!data.eof())
        {
            if (trno == tno)
            {
                cout << "train deleted successfully\n";
                flag = 1;
            }
            else
            {
                data1 << " " << si << " " << tno << " " << tname << " " << splace << " " << dplace << " " << price << " " << seats << " " << time << endl;
            }
            data >> si >> tno >> tname >> splace >> dplace >> price >> seats >> time;
        }
        data.close();
        data1.close();
        remove("train.txt");
        rename("train1.txt", "train.txt");

        if (flag == 0)
            cout << "Record not found\n";
    }
}
void train::updatetrain()
{
    cout << "\n\t****updateh train****\n";

    fstream data, data1;

    string trainname = "", starting = "", destination = "", departure = "";
    int fare = 0, avlseats = 0;
    ;

    int trno, flg = 0;

    cout << "\nEnter train number: ";
    cin >> trno;

    cout << "\nEnter details  want to update except train number:";
    cout << "[1] train name\n";
    cout << "[2] train fare\n";
    cout << "[3] starting place\n";
    cout << "[4] desnination place\n";
    cout << "[5] departure time\n";
    cout << "[6] update seats\n";

    int ch;
    cin >> ch;
    switch (ch)
    {
    case 1:
    {
        cin >> trainname;
        break;
    }
    case 2:
    {
        cin >> fare;
        break;
    }
    case 3:
    {
        cin >> starting;
        break;
    }
    case 4:
    {
        cin >> destination;
        break;
    }
    case 5:
    {
        cin >> departure;
        break;
    }
    case 6:
    {
        cin >> avlseats;
        break;
    }
    default:
    {
        admin();
    }
    }

    data.open("train.txt", ios::in);
    if (!data)
    {
        cout << "\n no record found\n";
        admin();
    }
    else
    {
        data1.open("train1.txt", ios::app | ios::out);
        data >> si >> tno >> tname >> splace >> dplace >> price >> seats >> time;
        while (!data.eof())
        {
            if (tno == trno)
            {
                cout << "\ntrain details updated successfully\n";
                data1 << " " << si << " " << tno << " " << (trainname == "" ? tname : trainname) << " " << (starting == "" ? splace : starting) << " " << (destination == "" ? dplace : destination) << " " << (fare == 0 ? price : fare)
                      << " " << (avlseats == 0 ? seats : avlseats) << " " << (departure == "" ? time : departure) << endl;
                flg = 1;
            }
            else
            {
                data1 << " " << si << " " << tno << " " << tname << " " << splace << " " << dplace << " " << price << " " << seats << " " << time << endl;
            }
            data >> si >> tno >> tname >> splace >> dplace >> price >> seats >> time;
        }
        data.close();
        data1.close();

        remove("train.txt");
        rename("train1.txt", "train.txt");

        if (flg == 0)
        {
            cout << "record not exists\n ";
        }
        admin();
    }
}
void train::menu()
{

    cout << "\t***Menu***" << endl;
    cout << "[1] VIEW INFORMATION" << endl;
    cout << "[2] BOOK TICKET" << endl;
    cout << "[3] CANCEL TICKET" << endl;
    cout << "[4] ADMIN" << endl;
    cout << "[5] Exit" << endl;
m:
    int ch;
    cin >> ch;
    switch (ch)
    {
    case 1:
    {
        view();
        break;
    }
    case 2:
    {
        bookticket();
        break;
    }
    case 3:
    {
        cancelticket();
        break;
    }
    case 4:
    {
        admin();
        break;
    }
    case 5:
    {
        exit;
    }
    default:
    {
        goto m;
    }
    }
}
int main()
{
    cout << "*******************************" << endl;
    cout << "**Railway reservation System***" << endl;
    cout << "*******************************" << endl;
    cout << "<<<<<<Welcome user>>>>>>" << endl;

    train t;
    t.menu();
}