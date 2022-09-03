#include<fstream>
#include<iostream>
#include<conio.h>
using namespace std;

struct Admin
{
    char username[20],password[20];
};
int main()
{
    ofstream fAdmin;
    Admin A;
    fAdmin.open("AdminAccess.txt",ios::out|ios::app);
    if(!fAdmin.is_open())
    {
        cout<<"\n\t\tError connecting to server. ERROR 404 ";
        return 0;
    }
     system("cls");
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
    cout<<"\n\t\t\t\t|______________________________________________________|";
    cout<<"\n\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\n\n\t\t\t\t     Enter User-name : "; cin>>A.username;
    cout<<"\n\t\t\t\t|    Enter Password : ";  cin>>A.password;
    fAdmin.write((char*)&A,sizeof(Admin));
    cout<<"\n\n\n\t\t\t\t     Admin Added Successfully!";
    cout<<"\n\n\n\t\t\t\t ______________________________________________________ ";
    fAdmin.close();
    return 0;
}
