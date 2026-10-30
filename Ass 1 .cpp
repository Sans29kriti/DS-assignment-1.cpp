include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

struct Passenger
{
    int seat;
    string name;
    int age;
    string gender;
    Passenger *next;
};

Passenger *start = NULL;
int *seats;
int total = 30;

void book()
{
    int i;

    for(i = 0; i < total; i++)
    {
        if(seats[i] == 0)
        {
            break;
        }
    }

    if(i == total)
    {
        cout << "No seat available";
    }
    else
    {
        Passenger *ptr = new Passenger;

        cout << "Enter name: ";
        cin >> ptr->name;

        cout << "Enter age: ";
        cin >> ptr->age;

        cout << "Enter gender: ";
        cin >> ptr->gender;

        ptr->seat = i + 1;

        ptr->next = start;
        start = ptr;

        seats[i] = 1;

        cout << "Ticket booked successfully";
        cout << "Your seat number is: " << i + 1<<endl;
    }
}

void cancel()
{
    int s;

    cout << "Enter seat number: ";
    cin >> s;

    if(s < 1 or s > total)
    {
        cout << "Invalid seat number";
    }
    else if(seats[s-1] == 0)
    {
        cout << "Seat is  empty";
    }
    else
    {
        Passenger *ptr = start;
        Passenger *prev = NULL;

        while(ptr != NULL && ptr->seat != s)
        {
            prev = ptr;
            ptr = ptr->next;
        }

        if(prev == NULL)
        {
            start = ptr->next;
        }
        else
        {
            prev->next = ptr->next;
        }

        delete ptr;
        seats[s-1] = 0;

        cout << "Ticket cancelled successfully";
    }
}


void status()
{
    for(int i = 0; i < total; i++)
    {
        cout << "\nSeat " << i+1 << " : ";

        if(seats[i] == 0)
        {
            cout << "Available";
        }
        else
        {
            cout << "Booked";
        }
    }
}

void passengers()
{
    Passenger *ptr = start;

    if(ptr == NULL)
    {
        cout << "No passenger found";
    }

    while(ptr != NULL)
    {
        cout << "\nSeat: " << ptr->seat;
        cout << "\nName: " << ptr->name;
        cout << "\nAge: " << ptr->age;
        cout << "\nGender: " << ptr->gender;

        ptr= ptr->next;
    }
}


void cleanup()
{
    Passenger *ptr;

    while(start!= NULL)
    {
        ptr = start;
        start = start->next;
        delete ptr;
    }

    free(seats);
}


int main()
{
    seats = (int*)malloc(total * sizeof(int));

    if(seats == NULL)
    {
        cout << "Memory not allocated";
        return 0;
    }

    for(int i = 0; i < total; i++)
    {
        seats[i] = 0;
    }

    int choice;

    do
    {
        cout << "\n\n~~~RAILWAY RESERVATION ~~~"<<endl;
        cout << "1. Book Ticket"<<endl;
        cout << "2. Cancel Ticket"<<endl;
        cout << "3. Train Status"<<endl;
        cout << "4. Passenger List"<<endl;
        cout << "5. Exit"<<endl;

        cout << "Enter choice: "<<endl;
        cin >> choice;

        switch(choice)
        {
            case 1:
                book();
                break;

            case 2:
                cancel();
                break;

            case 3:
                status();
                break;

            case 4:
                passengers();
                break;

            case 5:
                cleanup();
                cout << "Program ended";
                break;

            default:
                cout << "Wrong choice";
        }

    } while(choice != 5);

    return 0;
}
