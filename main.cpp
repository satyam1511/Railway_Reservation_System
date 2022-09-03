#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<ctime>
#include<string>
using namespace std;

const int MAX_VALID_YR = 2022;
const int MIN_VALID_YR = 2020;
struct Date
{
    int dd,mm,yyyy;
} ;

class Ticket
{
    public:
    char Username[16];
    char Tno[6];
    char Src[4],Des[4];
    char Tname[12];
    int berthno;
    char berthtype[3];
    char Class[3];
    char Fname[10],Lname[10];
    char G;
    int age;
    Date dob,doj;
    char email[45];
    char mob[11];
    float total;

    Ticket()
    {

    }
    Ticket(char Tno[6],char Tname[12],char Src[4],char Des[4],int berthno,char Class[3],char Fname[10],char Lname[10],int age,char G,char Username[16],Date dob,Date doj,char email[20],char mob[10],float fare)
    {
        strcpy(this->Src,Src);
        strcpy(this->Des,Des);
        total=fare+30.0;
        strcpy(this->Username,Username);
        this->G=G;
        strcpy(this->Tname,Tname);
        strcpy(this->Tno,Tno);
        this->berthno=berthno;
        strcpy(this->Class,Class);
        if((strcmp(this->Class,"SL")==0)||(strcmp(this->Class,"3A")==0))
        switch((this->berthno%8))
        {
            case 0  :   strcpy(this->berthtype,"SU");
                        break;
            case 1  :   strcpy(this->berthtype,"LB");
                        break;
            case 2  :   strcpy(this->berthtype,"MB");
                        break;
            case 3  :   strcpy(this->berthtype,"UB");
                        break;
            case 4  :   strcpy(this->berthtype,"LB");
                        break;
            case 5  :   strcpy(this->berthtype,"MB");
                        break;
            case 6  :   strcpy(this->berthtype,"UB");
                        break;
            case 7  :   strcpy(this->berthtype,"SL");
                        break;
        }

        else if(strcmp(this->Class,"2A")==0)
        switch((this->berthno%6))
        {
            case 0  :   strcpy(this->berthtype,"SU");
                        break;
            case 1  :   strcpy(this->berthtype,"LB");
                        break;
            case 2  :   strcpy(this->berthtype,"UB");
                        break;
            case 3  :   strcpy(this->berthtype,"LB");
                        break;
            case 4  :   strcpy(this->berthtype,"UB");
                        break;
            case 5  :   strcpy(this->berthtype,"SL");
                        break;
        }
        else strcpy(this->berthtype,"LB");
        strcpy(this->Fname,Fname);
        strcpy(this->Lname,Lname);
        this->doj=doj;
        this->dob=dob;
        this->age=age;
        strcpy(this->email,email);
        strcpy(this->mob,mob);
    }

};

 class User
{
public:
    int age=0;
    char Fname[10]={},Lname[10]={};
    char username[16],password[20];
    char mob[10]={};
    char nationality[20]={};
    char G;
};
struct Admin{
char username[20],password[20];
};
class Train
{
    public:

    char Tno[6]="";
    char Tname[12]="";
    char Src[4]="",Des[4]="";
    float distance;
    char Class[4];
    float fare_sl,fare_3a,fare_2a,fare_1a,tot_sl,tot_3a,tot_2a,tot_1a;
    void fair_calc()
    {
        tot_1a=distance*fare_1a;
        tot_2a=distance*fare_2a;
        tot_3a=distance*fare_3a;
        tot_sl=distance*fare_sl;
    }
    Train()
    {
        distance=0.0;
        fare_sl=0.0;
        fare_3a=0.0;
        fare_2a=0.0;
        fare_1a=0.0;
        tot_sl=0.0;
        tot_3a=0.0;
        tot_2a=0.0;
        tot_1a=0.0;
    }
};
void gotoxy (int x, int y)
    {
         COORD coordinates;     // coordinates is declared as COORD
         coordinates.X = x;     // defining x-axis
         coordinates.Y = y;     //defining  y-axis
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
    }

void SignIn();
void EnterPassword(char p[20]);
void SignUp();
void WelcomePage(User t);
void ChangePassword(char un[16],char pwd[20]);
void Booking(User);
bool isValidDate(int,int,int);
bool isFutureDate(int,int,int);
bool isLeap(int);
void AdminMode();
void addTrain();
void TrainList();
void ticket_available(Date d,char Tno[6],int *sl=0,int *tier3=0,int *tier2=0,int *tier1=0,int s[72]={0},int t3[72]={0},int t2[54]={0},int t1[18]={0});
int berth_allocation(char b[3],int s[],int seats,int comp);
void BookedTicket(User U);
void Cancellation(User U);
void SignIn()
{
    char UName[20],Pwd[20];
    ifstream f;
    User temp;
    int flag=1;
    Label3:
    system("cls");
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
    cout<<"\n\t\t\t\t|______________________________________________________|";
    cout<<"\n\n\n\t\t\t\t Sign-In ";
    cout<<"\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t  User-Name : ";
    cin>>UName;
    cout<<"\n\t\t\t\t  Password : ";
    EnterPassword(Pwd);
    cout<<"\n\t\t\t\t ______________________________________________________";
    system("cls");
    f.open("login_details.txt",ios::in);
    if(!f.is_open())
    {
        cout<<"\n\t\t\t\t ______________________________________________________ ";
        cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
        cout<<"\n\t\t\t\t|______________________________________________________|";
        cout<<"\n\n\n\t\t\t\t Could not connect to Server.Please try again after sometime.\n\t\t\t\t ERROR 403 ";
        return;
    }
    while(!f.eof())
    {
        f.read((char*)&temp,sizeof(User));
        if(strcmp(temp.username,UName)==0&&strcmp(temp.password,Pwd)==0)
        {
            flag=0;
            break;
        }    //successful
    }
    f.seekg(0,ios::beg);
    if(!flag){
        f.close();
        WelcomePage(temp);
    }
        if(flag)
    {
        system("cls");
        cout<<"\n\t\t\t\t ______________________________________________________ ";
        cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
        cout<<"\n\t\t\t\t|______________________________________________________|";
        cout<<"\n\n\t\t\t\tEither Wrong User-name or Password! Try-Again(Press Enter)";
        f.close();
        system("pause");
        goto Label3;
    }
}

void SignUp()
{
    User temp,temp2;
    ifstream fin;
    int i;
    fin.open("login_details.txt",ios::in);
    system("cls");
    if(!fin)
    {
        cout<<"\n\t\t\t\t ______________________________________________________ ";
        cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
        cout<<"\n\t\t\t\t|______________________________________________________|";
        cout<<"\n\n\n\t\t\t\t Could not connect to Server.Please try again after sometime.\n\t\t\t\t ERROR 403 ";
        return;
    }
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
    cout<<"\n\t\t\t\t|______________________________________________________|";
    cout<<"\n\n\n\t\t\t\t Sign-Up ";
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t  First Name : ";
    Label4:
    cin>>temp.Fname;
    for(i=0;temp.Fname[i]!='\0';i++){
        if(!isalpha(temp.Fname[i]))
        {
        cout<<"\n\t\t\t\t  Enter a valid string comprising of alphabets(a-z or A-Z)";
        goto Label4;
        }
    }
    cout<<"\n\t\t\t\t  Last Name : ";
    Label5:
    cin>>temp.Lname;
    for(i=0;temp.Lname[i]!='\0';i++){
        if(!isalpha(temp.Lname[i]))
        {
        cout<<"\n\t\t\t\t  Enter a valid string comprising of alphabets(a-z or A-Z)";
        goto Label5;
        }
    }
    cout<<"\n\t\t\t\t  Gender(M/F) : ";
    Label6:
    cin>>temp.G;
    if(!(temp.G=='M'||temp.G=='F'))
        {
        cout<<"\n\t\t\t\t  Enter a valid input again";
        goto Label6;
        }
    cout<<"\n\t\t\t\t  Age : ";
    Label7:
    cin>>temp.age;
    if(temp.age<18||temp.age>120)
        {
        cout<<"\n\t\t\t\t  Enter a valid Age of User";
        goto Label7;
        }
    cout<<"\n\t\t\t\t  Mobile No. : ";
    Label8:
    cin>>temp.mob;
    for(i=1;temp.mob[i]!='\0';i++)
    {

    }
    if(i!=10)
        {
        cout<<"\n\t\t\t\t  Enter a valid Mobile No.";
        goto Label8;
        }
    cout<<"\n\t\t\t\t  Nationality: ";
    Label9:
    cin>>temp.nationality;
    for(i=0;temp.nationality[i]!='\0';i++){
        if(!isalpha(temp.nationality[i]))
        {
        cout<<"\n\t\t\t\t  Enter a valid string comprising of alphabets(a-z or A-Z)";
        goto Label9;
        }
    }
    cout<<"\n\t\t\t\t  User-name comprising of (a-z,A-Z,0-9,@): ";
    Label10:
    cin>>temp.username;
    for(i=0;temp.username[i]!='\0';i++){
        if(!isalnum(temp.username[i]))
        {
                if(temp.username[i]!='@')
       {
        cout<<"\n\t\t\t\t  Enter a valid string comprising of (a-z,A-Z,0-9,@): ";
        goto Label10;
       }
        }
    }
    while(!fin.eof())
    {
        fin.read((char*)&temp2,sizeof(User));
        if(strcmp(temp.username,temp2.username)==0)
        {
            fin.seekg(0);
            cout<<"\n\t\t\t\t  This User-name is not available. Try another! ";
            goto Label10;
        }
    }
    fin.seekg(0);
    fin.close();
    cout<<"\n\t\t\t\t  Password(minimum 8 characters) :";
    Label11:
    cin>>temp.password;
    for(i=0;temp.password[i]!='\0';i++)
    {
    }
    if(i<8)
    {
        cout<<"\n\t\t\t\t  The Password is too weak. Please enter password again :";
        goto Label11;
    }
      cout<<"\n\t\t\t\t Press Enter to Confirm Submission ";
      cout<<"\n\t\t\t\t|______________________________________________________|";
      system("pause");
    ofstream fout;
    fout.open("login_details.txt",ios::out|ios::app);
    system("cls");
    if(!fout)
    {
        cout<<"\n\t\t\t\t ______________________________________________________ ";
        cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
        cout<<"\n\t\t\t\t|______________________________________________________|";
        cout<<"\n\n\n\t\t\t\t Could not connect to Server.Please try again after sometime.\n\t\t\t\t ERROR 403 ";
        return;
    }
    fout.write((char*)&temp,sizeof(User));
    fout.close();
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
    cout<<"\n\t\t\t\t|______________________________________________________|";
    cout<<"\n\n\n\t\t\t\t Registration Successful! Please Login again to use our facilities.\n\t\t\t\t Press Enter to proceed";
    system("pause");
    SignIn();
}

void EnterPassword(char p[20])
{   int i=0;
    char ch;
    while(1)
    {
        ch=_getch();
        if(ch==13)
        {
            p[i]='\0';
            break;
        }
        else if(ch=='\b')
        {
            if(i>0)
            {
                 i--;
                 cout<<"\b \b";
            }
        }
        else{
        p[i]=ch;
        cout<<"*";
        i++;
        }
    }
}

void WelcomePage(User t)
{
    char ch;
    Label12:
    system("cls");
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
    cout<<"\n\t\t\t\t|______________________________________________________|";
    if(t.G=='M')
    {
    cout<<"\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t              Mr. "<<t.Fname<<" "<<t.Lname;
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    }
    else{
    cout<<"\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t              Mrs. "<<t.Fname<<" "<<t.Lname;
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    }
    cout<<"\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|     Press 1 For : Booking Tickets                    |";
    cout<<"\n\t\t\t\t|     Press 2 For : Booked Ticket History              |";
    cout<<"\n\t\t\t\t|     Press 3 For : Cancellation                       |";
    cout<<"\n\t\t\t\t|     Press 4 For : Change Password                    |";
    cout<<"\n\t\t\t\t|     Press 5 For : Log-Out                            |";
    cout<<"\n\t\t\t\t|______________________________________________________|";
    cin>>ch;
    switch(ch)
    {
        case '1'  :   Booking(t);
                       goto Label12;
                      break;
        case '2'  :   BookedTicket(t);
                       goto Label12;
                      break;
        case '3'  :   Cancellation(t);
                        goto Label12;
                      break;
        case '4'  :   ChangePassword(t.username,t.password);
                      goto Label12;
                      break;
        case '5'  :   system("cls");
                      cout<<"\n\n\n\n\t\t\t\t  ______________________________________________________________";
                      cout<<"\n\t\t\t\t |             Logged Out Successfully!(Press Enter)            |";
                      cout<<"\n\t\t\t\t |______________________________________________________________|";
                      system("pause");
                      break;

        default :   cout<<"\n\n\t\t\t\t _____________________________________________________________ ";
                    cout<<"\n\t\t\t\t|          You have entered wrong input!(Press Enter)         |";
                    cout<<"\n\t\t\t\t|_____________________________________________________________| ";
                    system("cls");
                    goto Label12;
                    break;
    }


}


void ChangePassword(char un[16],char pwd[20])
{
    User flag;
    int i;
    char p1[20],p2[20];
    ifstream ftemp;
    ftemp.open("login_details.txt",ios::in);
    ofstream ftemp2;
    ftemp2.open("temp.txt",ios::out|ios::app);
    if(!(ftemp.is_open()&&ftemp2.is_open()))
    {
        cout<<"\n\t\t\t\t ______________________________________________________ ";
        cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
        cout<<"\n\t\t\t\t|______________________________________________________|";
        cout<<"\n\n\n\t\t\t\t Could not connect to Server.Please try again after sometime.\n\t\t\t\t ERROR 403 ";
        return;
    }
    Label13:
    system("cls");
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
    cout<<"\n\t\t\t\t|______________________________________________________|";
    cout<<"\n\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t       Old Password : ";
    cin>>p1;
    cout<<"\n\t\t\t\t       New Password : ";
    cin>>p2;
    cout<<"\n\t\t\t\t ______________________________________________________";
    for(i=0;p2[i]!='\0';i++)
    {
    }
    if(i<8)
    {
        cout<<"\n\t\t\t\t  The Password is too weak. Please enter password again :";
        system("pause");
        goto Label13;
        }

    if(strcmp(p1,p2)==0)
    {
     cout<<"\n\n\t\t\t\tThe entered password is same as Old-password.Try Again!";
     system("pause");
     goto Label13;
    }
    if(strcmp(p1,pwd)!=0)
    {
     cout<<"\n\n\t\t\t\tThe Old Password does not match. Please Try Again!";
     system("pause");
     goto Label13;
    }
    else{
            strcpy(pwd,p2);
    while(!ftemp.eof())
    {
        ftemp.read((char*)&flag,sizeof(User));
        if(strcmp(un,flag.username)==0)
        {
         strcpy(flag.password,p2);
         }
        ftemp2.write((char*)&flag,sizeof(User));
        }
    }
    ftemp2.seekp(0,ios::beg);
    ftemp.close();
    ftemp2.close();
    remove("login_details.txt");
    rename("temp.txt","login_details.txt");
    cout<<"\n\n\n\n\t\t\t\t  ______________________________________________________________";
    cout<<"\n\t\t\t\t |           Password Changed Successfully!(Press Enter)        |";
    cout<<"\n\t\t\t\t |______________________________________________________________|";
    system("pause");

}

void Booking(User U)
{

    string date;
    char src[4],des[4];
    Train T;
    Label14:
    system("cls");
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
    cout<<"\n\t\t\t\t|______________________________________________________|";
    if(U.G=='M')
    {
    cout<<"\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t              Mr. "<<U.Fname<<" "<<U.Lname;
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    }
    else{
    cout<<"\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t              Mrs. "<<U.Fname<<" "<<U.Lname;
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    }
    cout<<"\n\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t      Date Of Journey(dd-mm-yyyy) : ";
    cin.ignore();
    getline(cin,date);
    Date doj;
    sscanf(date.c_str(),"%d-%d-%d",&doj.dd,&doj.mm,&doj.yyyy);
    if(!(isValidDate(doj.dd,doj.mm,doj.yyyy)&&isFutureDate(doj.dd,doj.mm,doj.yyyy)))
    {
        cout<<"\n\t\t\t\t      Invalid Date! Press Enter to try again. ";
        system("pause");
        goto Label14;
    }
    cout<<"\n\t\t\t\t      From Station : "; cin.getline(src,4);
    cout<<"\n\t\t\t\t      To Station : "; cin.getline(des,4);
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\n\n\t\t\t\t ______________________________________________________ ";
    ifstream fTrain4;
    fTrain4.open("Train_list.txt",ios::in);
    if(!fTrain4.is_open())
    {
        cout<<"\t\t\tError connecting to Server. Error 404.";
        system("pause");
        return;
    }
    cout<<"\n\n\t\t\t\t_____________________________________________________________________";
    cout<<"\n\n\t\t\t\t Train no.  Train Name  Source  Destination  Distance  Fair(SL)/km  Fair(3A)/km  Fair(2A)/km  Fair(1A)/km  ";
    cout<<"\n\n\t\t\t\t ---------  ----------  ------  -----------  --------  -----------  -----------  -----------  -----------  ";
    int i=0,ch;
    while(fTrain4.read((char*)&T,sizeof(T)))
    {
        if(strcmp(src,T.Src)==0&&strcmp(des,T.Des)==0)
        {
        ++i;
        cout<<"\n\t\t\t   "<<T.Tno<<"   "<<T.Tname<<"   "<<T.Src<<"      "<<T.Des<<"          "<<T.distance<<"      "<<T.fare_sl<<"  "<<T.fare_3a<<"  "<<T.fare_2a<<"  "<<T.fare_1a;
        }
    }
    fTrain4.close();
    ifstream fTrain5;
    fTrain5.open("Train_list.txt");
    if(!fTrain5.is_open())
    {
        cout<<"\t\t\tError connecting to Server. Error 404.";
        system("pause");
        return;
    }

    cout<<"\n\n\t\t\t\t_____________________________________________________________________\n";
    cout<<"\n\n\t\t\t\tEnter your choice";
    cin>>ch;
    int j=1;
    while(j<=i)
    {

        fTrain5.read((char*)&T,sizeof(T));
        if(j==ch)
        break;
        if(strcmp(src,T.Src)==0&&strcmp(des,T.Des)==0)
        j++;
    }
    fTrain5.close();
    system("cls");
    int sl=0,tier3=0,tier2=0,tier1=0,s[72]={0},t3[72]={0},t2[54]={0},t1[18]={0},bno;
    ticket_available(doj,T.Tno,&sl,&tier3,&tier2,&tier1,s,t3,t2,t1);
    sl=72-sl;
    tier3=72-tier3;
    tier2=54-tier2;
    tier1=18-tier1;
    cout<<"\n\t\t\t\t_____________________________________________________________________\n";
    cout<<"\t\t\t\t"<<T.Tno<<"     "<<T.Tname<<"      "<<doj.dd<<" - "<<doj.mm<<" - "<<doj.yyyy;
    cout<<"\n\t\t\t\t_____________________________________________________________________\n";
    cout<<"\n\n\t\t\t\t_____________________________________________________________________\n";
    cout<<"\t\t\t\t Class         Tickets-Available\n";
    cout<<"\t\t\t\t -----         ---------------------";
    cout<<"\n\t\t\t\t SL            "<<sl;
    cout<<"\n\t\t\t\t 3A            "<<tier3;
    cout<<"\n\t\t\t\t 2A            "<<tier2;
    cout<<"\n\t\t\t\t 1A            "<<tier1;
    Label16:
    cout<<"\n\t\t\t\t Which Class you want to Reserve a ticket in?\n";
    cin>>ch;
    char cls[3];
    switch(ch)
    {
        case 1  :   if(sl>0)
                    strcpy(cls,"SL");
                    else {
                            cout<<"\n\t\t\t Try Another Class.No more berths available";
                            goto Label16;
                    }
                    break;

        case 2  :   if(tier3>0)
                    strcpy(cls,"3A");
                    else {
                            cout<<"\n\t\t\t Try Another Class.No more berths available";
                            goto Label16;
                    }
                    break;

        case 3  :   if(tier2>0)
                    strcpy(cls,"2A");
                    else {
                            cout<<"\n\t\t\t Try Another Class.No more berths available";
                            goto Label16;
                    }
                    break;

        case 4  :   if(tier1>0)
                    strcpy(cls,"1A");
                    else {
                            cout<<"\n\t\t\t Try Another Class.No more berths available";
                            goto Label16;
                    }
                    break;

        default :   cout<<"\n\t\t\t Wrong Input.Try Again";
                    goto Label16;

    }
         cout<<"\n\n\t\t\t_____________________________________________________________________\n";
        system("pause");
        system("cls");

        cout<<"\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
    cout<<"\n\t\t\t\t|______________________________________________________|";
    if(U.G=='M')
    {
    cout<<"\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t              Mr. "<<U.Fname<<" "<<U.Lname;
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    }
    else{
    cout<<"\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t              Mrs. "<<U.Fname<<" "<<U.Lname;
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    }



            char Fname[10],Lname[10],Mob[11],Email[45],G,berth[3];
            int age;
            Date dob;
         cout<<"\n\n\t\t\t\t_____________________________________________________________________\n";
         cout<<"\n\t\t\t\tFirst Name : "; cin.ignore();
         cin.ignore();
         cin.getline(Fname,10);
         cout<<"\n\t\t\t\tLast Name : "; cin.getline(Lname,10);
         cout<<"\n\t\t\t\tAge : "; cin>>age;
         cout<<"\n\t\t\t\tGender : "; cin>>G;
         cout<<"\n\t\t\t\tMobile : ";
         cin.ignore();
         cin.getline(Mob,11);
         cout<<"\n\t\t\t\tE-mail ID : "; cin.getline(Email,45);
         float fare;
         T.fair_calc();
         if(strcmp(cls,"SL")==0)
         {cout<<"\n\t\t\t\tBerth Preference(LB/MB/UB/SL/SU) : "; cin.getline(berth,3);
         bno=berth_allocation(berth,s,72,8);
         fare=T.tot_sl;
         }
         else if(strcmp(cls,"3A")==0)
         {cout<<"\n\t\t\t\tBerth Preference(LB/MB/UB/SL/SU) : "; cin.getline(berth,3);
         bno=berth_allocation(berth,t3,72,8);
         fare=T.tot_3a;
         }
         else if(strcmp(cls,"2A")==0)
         {cout<<"\n\t\t\t\tBerth Preference(LB/UB/SL/SU) : "; cin.getline(berth,3);
         bno=berth_allocation(berth,t2,54,8);
         fare=T.tot_2a;
         }
         else if(strcmp(cls,"1A")==0)
         {cout<<"\n\t\t\t\tBerth Preference(LB) : "; cin.getline(berth,3);
         bno=berth_allocation(berth,t1,18,8);
         fare=T.tot_1a;
         }
         //else cout<<"\n\t\t\t\tWrong Input!";

         time_t t=time(0);
         tm *local_time=localtime(&t);
         dob.dd=local_time->tm_mday;
         dob.mm=1+local_time->tm_mon;
         dob.yyyy=1900+local_time->tm_year;

         Ticket ticket=Ticket(T.Tno,T.Tname,T.Src,T.Des,bno,cls,Fname,Lname,age,G,U.username,dob,doj,Email,Mob,fare);
         ofstream fTicket;
         fTicket.open("Ticket_list.txt",ios::app);
         if(!fTicket.is_open())
        {
        cout<<"\t\t\tError connecting to Server. Error 404.";
        system("pause");
        return;
        }
        fTicket.write((char*)&ticket,sizeof(ticket));
        fTicket.close();
        cout<<"\n\t\t\t\t __________________________";
        cout<<"\n\t\t\t\t|Ticket Booked Successfully|";
        cout<<"\n\t\t\t\t|__________________________|";
        cout<<"\n\n\t\t\t\t_____________________________________________________________________\n";
        system("pause");
        return;
}

int berth_allocation(char b[3],int s[],int seats,int comp)
{
    int i;
        if(comp==8)
        {
            if(strcmp(b,"LB")==0)
            {
                for(i=1;i<=seats;i++)
                {
                    if((i%8==1||i%8==4)&&s[i-1]!=1)
                    {
                        return i;
                    }
                }
                for(i=1;i<=seats;i++)
                {
                    if(s[i-1]!=1)
                    {
                        return i;
                    }
                }
            }

            else if(strcmp(b,"MB")==0)
            {
                for(i=1;i<=seats;i++)
                {
                    if((i%8==2||i%8==5)&&s[i-1]!=1)
                    {
                        return i;
                    }
                }
                for(i=1;i<=seats;i++)
                {
                    if(s[i-1]!=1)
                    {
                        return i;
                    }
                }
            }

            else if(strcmp(b,"UB")==0)
            {
                for(i=1;i<=seats;i++)
                {
                    if((i%8==3||i%8==6)&&s[i-1]!=1)
                    {
                        return i;
                    }
                }
                for(i=1;i<=seats;i++)
                {
                    if(s[i-1]!=1)
                    {
                        return i;
                    }
                }
            }

            else if(strcmp(b,"SL")==0)
            {
                for(i=1;i<=seats;i++)
                {
                    if((i%8==7)&&s[i-1]!=1)
                    {
                        return i;
                    }
                }
                for(i=1;i<=seats;i++)
                {
                    if(s[i-1]!=1)
                    {
                        return i;
                    }
                }
            }

            else if(strcmp(b,"SU")==0)
            {
                for(i=1;i<=seats;i++)
                {
                    if((i%8==0)&&s[i-1]!=1)
                    {
                        return i;
                    }
                }
                for(i=1;i<=seats;i++)
                {
                    if(s[i-1]!=1)
                    {
                        return i;
                    }
                }
            }


        }


    else if(comp==6)
        {
            if(strcmp(b,"LB")==0)
            {
                for(i=1;i<=seats;i++)
                {
                    if((i%6==1||i%6==3)&&s[i-1]!=1)
                    {
                        return i;
                    }
                }
                for(i=1;i<=seats;i++)
                {
                    if(s[i-1]!=1)
                    {
                        return i;
                    }
                }
            }


            else if(strcmp(b,"UB")==0)
            {
                for(i=1;i<=seats;i++)
                {
                    if((i%6==2||i%6==4)&&s[i-1]!=1)
                    {
                        return i;
                    }
                }
                for(i=1;i<=seats;i++)
                {
                    if(s[i-1]!=1)
                    {
                        return i;
                    }
                }
            }

            else if(strcmp(b,"SL")==0)
            {
                for(i=1;i<=seats;i++)
                {
                    if((i%6==5)&&s[i-1]!=1)
                    {
                        return i;
                    }
                }
                for(i=1;i<=seats;i++)
                {
                    if(s[i-1]!=1)
                    {
                        return i;
                    }
                }
            }

            else if(strcmp(b,"SU")==0)
            {
                for(i=1;i<=seats;i++)
                {
                    if((i%6==0)&&s[i-1]!=1)
                    {
                        return i;
                    }
                }
                for(i=1;i<=seats;i++)
                {
                    if(s[i-1]!=1)
                    {
                        return i;
                    }
                }
            }


        }


    else if(comp==2)
        {
            if(strcmp(b,"LB")==0)
            {
                for(i=1;i<=seats;i++)
                {
                    if(s[i-1]!=1)
                    {
                        return i;
                    }
                }
            }
        }

}

bool isValidDate(int d,int m,int y){
// If year, month and day
    // are not in given range
    if (y > MAX_VALID_YR ||
        y < MIN_VALID_YR)
    return false;
    if (m < 1 || m > 12)
    return false;
    if (d < 1 || d > 31)
    return false;

    // Handle February month
    // with leap year
    if (m == 2)
    {
        if (isLeap(y))
        return (d <= 29);
        else
        return (d <= 28);
    }

    // Months of April, June,
    // Sept and Nov must have
    // number of days less than
    // or equal to 30.
    if (m == 4 || m == 6 || m == 9 || m == 11)
        return (d <= 30);

    return true;
}


bool isLeap(int year)
{
// Return true if year
// is a multiple pf 4 and
// not multiple of 100.
// OR year is multiple of 400.
return (((year % 4 == 0)&&(year % 100 != 0))||(year % 400 == 0));
}

bool isFutureDate(int d,int m,int y)
{
    time_t t=time(0);
    tm *local_time=localtime(&t);
    if((d>=local_time->tm_mday)&&(m>=1+local_time->tm_mon)&&(y>=1900+local_time->tm_year))
        return true;
    else return false;
}

void AdminMode(){
    ifstream f;
    Admin a;
    system("cls");
    system("cls");
    char username[20],password[20];
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
    cout<<"\n\t\t\t\t|______________________________________________________|";
    cout<<"\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t     User-name : ";cin>>username;
    cout<<"\n\t\t\t\t     Password : "; cin>>password;
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    f.open("AdminAccess.txt");
    if(!f.is_open())
    {
        cout<<"\n\n\n\t\t\t\tError connecting to Server. ERROR 404";
        system("pause");
        return;
    }
    while(!f.eof())
    {
        f.read((char*)&a,sizeof(Admin));
        if((strcmp(a.username,username)==0)&&(strcmp(a.password,password)==0))
        {
            char ch;
            f.close();
            Label15:
            system("cls");
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
    cout<<"\n\t\t\t\t|______________________________________________________|";
    cout<<"\n\n\t\t\t\t  _____________________________________________________ ";
    cout<<"\n\t\t\t\t |    1. For New Train.                                |";
    cout<<"\n\t\t\t\t |    2. For Train List.                               |";
    cout<<"\n\t\t\t\t |    3. For Exit.                                     |";
    cout<<"\n\t\t\t\t |_____________________________________________________|";
    cin>>ch;
            switch(ch)
            {
                case '1'    :   addTrain();
                                goto Label15;
                                break;
                case '2'    :   TrainList();
                                goto Label15;
                                break;
                case '3'    :   system("cls");
                                return;
                default     :   cout<<"\n\n\n\t\t\t\tWrong Input! Press Enter to try again!";
                                system("pause");
                                goto Label15;
            }
            return;
    }
    }
        cout<<"\n\n\n\t\t\t\tAccess Denied";
        f.close();
        return;

}

void addTrain()
{
    Train T,temp;
    ifstream fTrain;
    system("cls");
    fTrain.open("Train_list.txt",ios::in);
    if(!fTrain.is_open())
    {
        cout<<"\t\t\tError connecting to Server. Error 404.";
        system("pause");
        return;
    }
    Label16:
    cout<<"\n\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
    cout<<"\n\t\t\t\t|______________________________________________________|";
    cout<<"\n\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t       Train Number : ";
        cin.ignore();
        cin.getline(T.Tno,6);
        fTrain.read((char*)&temp,sizeof(Train));
    while(!fTrain.eof())
    {
        fTrain.read((char*)&temp,sizeof(Train));
        if(strcmp(temp.Tno,T.Tno)==0)
        {
                cout<<"\n\t\t\t\t       This Train Already Exists. Try Again.";
                fTrain.seekg(0,ios::beg);
                system("cls");
                system("pause");
                goto Label16;
        }
    }
        fTrain.seekg(0);
        fTrain.close();
    cout<<"\n\t\t\t\t       Train Name : ";
    //cin.ignore();
    cin.getline(T.Tname,12);
    cout<<"\n\t\t\t\t       Source Station : ";
    cin.getline(T.Src,4);
    cout<<"\n\t\t\t\t       Destination Station : ";
    cin.getline(T.Des,4);
    cout<<"\n\t\t\t\t       Distance in kms : ";
    cin>>T.distance;
    cout<<"\n\t\t\t\t       Fair decided(SL) per km : ";
    cin>>T.fare_sl;
    cout<<"\n\t\t\t\t       Fair decided(3A) per km : ";
    cin>>T.fare_3a;
    cout<<"\n\t\t\t\t       Fair decided(2A) per km : ";
    cin>>T.fare_2a;
    cout<<"\n\t\t\t\t       Fair decided(1A) per km : ";
    cin>>T.fare_1a;
    T.fair_calc();
//    T.doj.dd=0; T.doj.mm=0; T.doj.yyyy=0;

    cout<<"\n\t\t\t\t ______________________________________________________";
    cout<<"\n";
    system("pause");
    system("cls");
    ofstream fTrain2;
    fTrain2.open("Train_list.txt",ios::app);
    if(!fTrain2.is_open())
    {
        cout<<"\t\t\tError connecting to Server. Error 404.";
        system("pause");
        return;
    }
    fTrain2.write((char*)&T,sizeof(T));
    fTrain2.close();
    cout<<"\n\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
    cout<<"\n\t\t\t\t|______________________________________________________|";
    cout<<"\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|      Train Added Successfully!                       |";
    cout<<"\n\t\t\t\t|______________________________________________________|\n";
    system("pause");
    return;
}


void TrainList()
{
    system("cls");
    cout<<"\n\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
    cout<<"\n\t\t\t\t|______________________________________________________|";
    ifstream fTrain3;
    Train T;
    fTrain3.open("Train_list.txt",ios::in);
    if(!fTrain3.is_open())
    {
                cout<<"\t\t\tError connecting to Server. Error 404.";
                system("pause");
                return;
    }
    cout<<"\n\n\t\t\t_____________________________________________________________________";
    cout<<"\n\n\t\t\t Train no.  Train Name  Source  Destination  Distance  Fair(SL)/km  Fair(3A)/km  Fair(2A)/km  Fair(1A)/km  ";
    cout<<"\n\n\t\t\t ---------  ----------  ------  -----------  --------  -----------  -----------  -----------  -----------";

    while(fTrain3.read((char*)&T,sizeof(T)))
    {
        cout<<"\n\t\t\t   "<<T.Tno<<"   "<<T.Tname<<"   "<<T.Src<<"      "<<T.Des<<"          "<<T.distance<<"      "<<T.fare_sl<<"  "<<T.fare_3a<<"  "<<T.fare_2a<<"  "<<T.fare_1a;
    }
    fTrain3.close();
    cout<<"\n\n\t\t\t_____________________________________________________________________\n";
    system("pause");
    return;
}


void ticket_available(Date d,char Tno[6],int *sl,int *tier3,int *tier2,int *tier1,int s[72],int t3[72],int t2[54],int t1[18])
{
    ifstream fTicket;
    Ticket temp=Ticket();
    fTicket.open("Ticket_list.txt",ios::in);
    if(!fTicket.is_open())
    {
                cout<<"\t\t\tError connecting to Server. Error 404.";
                system("pause");
                return;
    }
    while(fTicket.read((char*)&temp,sizeof(temp)))
    {
        if((temp.doj.dd==d.dd)&&(temp.doj.mm=d.mm)&&(temp.doj.yyyy=d.yyyy)&&(strcmp(Tno,temp.Tno)==0))
        {
            if(strcmp(temp.Class,"SL")==0)
                {
                    (*sl)++;
                    s[temp.berthno-1]=1;
                }
            else if(strcmp(temp.Class,"3A")==0)
                {
                    (*tier3)++;
                    t3[temp.berthno-1]=1;
                }
            else if(strcmp(temp.Class,"2A")==0)
                {
                    (*tier2)++;
                   t2[temp.berthno-1]=1;
                }
            else if(strcmp(temp.Class,"1A")==0)
                {
                    (*tier1)++;
                    t1[temp.berthno-1]=1;
                }
        }

    }
    fTicket.close();
}

void BookedTicket(User U)
{
    Ticket T;
    ifstream fBook;
    system("cls");
    cout<<"\n\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
    cout<<"\n\t\t\t\t|______________________________________________________|";

    fBook.open("Ticket_list.txt",ios::in);
        if(!fBook.is_open())
    {
        cout<<"\t\t\tError connecting to Server. Error 404.";
        system("pause");
        return;
    }
        int i=0;
        while(fBook.read((char*)&T,sizeof(T)))
              {
                  if(strcmp(T.Username,U.username)==0)
                    {
                        i++;
                        cout<<"\n\n\n\t\t\t\t                    T"<<i;
                        cout<<"\n\n\n\t\t\t\t ______________________________________________________ ";
                        cout<<"\n\t\t\t\t Name : "<<T.Fname<<" "<<T.Lname;
                        cout<<"\n\t\t\t\t Age : "<<T.age<<"   Gender : "<<T.G;
                        cout<<"\n\t\t\t\t Train : "<<T.Tno<<" - "<<T.Tname;
                        cout<<"\n\t\t\t\t Source : "<<T.Src<<"       "<<"Destination : "<<T.Des;
                        cout<<"\n\t\t\t\t Date Of Journey : "<<T.doj.dd<<"-"<<T.doj.mm<<"-"<<T.doj.yyyy;
                        cout<<"\n\t\t\t\t Berth : "<<T.berthno<<"("<<T.berthtype<<")"<<" Class : "<<T.Class;
                        cout<<"\n\t\t\t\t Email Id : "<<T.email;
                        cout<<"\n\t\t\t\t Mobile no : "<<T.mob;
                        cout<<"\n\t\t\t\t Date Of Booking : "<<T.dob.dd<<"-"<<T.doj.mm<<"-"<<T.doj.yyyy;
                        cout<<"\n\t\t\t\t Total Fare : "<<T.total;
                        cout<<"\n\t\t\t\t ______________________________________________________ ";
                    }
              }
        fBook.close();
        system("pause");
        return;
}


void Cancellation(User U)
{

    Ticket T;
    ifstream fCancel;
    ofstream fCancel2;
    system("cls");
    cout<<"\n\n\n\t\t\t\t ______________________________________________________ ";
    cout<<"\n\t\t\t\t|              WELCOME TO INDIAN RAILWAYS              |";
    cout<<"\n\t\t\t\t|______________________________________________________|";

    fCancel.open("Ticket_list.txt",ios::in);
    fCancel2.open("temp2.txt",ios::app);
        if(!(fCancel.is_open()&&fCancel2.is_open()))
    {
        cout<<"\t\t\tError connecting to Server. Error 404.";
        system("pause");
        return;
    }
        int i=0,ch;
        while(fCancel.read((char*)&T,sizeof(T)))
              {
                  if(strcmp(T.Username,U.username)==0)
                    {
                        i++;
                        cout<<"\n\n\n\t\t\t\t                    T"<<i;
                        cout<<"\n\n\n\t\t\t\t ______________________________________________________ ";
                        cout<<"\n\t\t\t\t Name : "<<T.Fname<<" "<<T.Lname;
                        cout<<"\n\t\t\t\t Age : "<<T.age<<"   Gender : "<<T.G;
                        cout<<"\n\t\t\t\t Train : "<<T.Tno<<" - "<<T.Tname;
                        cout<<"\n\t\t\t\t Source : "<<T.Src<<"       "<<"Destination : "<<T.Des;
                        cout<<"\n\t\t\t\t Date Of Journey : "<<T.doj.dd<<"-"<<T.doj.mm<<"-"<<T.doj.yyyy;
                        cout<<"\n\t\t\t\t Berth : "<<T.berthno<<"("<<T.berthtype<<")"<<" Class : "<<T.Class;
                        cout<<"\n\t\t\t\t Email Id : "<<T.email;
                        cout<<"\n\t\t\t\t Mobile no : "<<T.mob;
                        cout<<"\n\t\t\t\t Date Of Booking : "<<T.dob.dd<<"-"<<T.doj.mm<<"-"<<T.doj.yyyy;
                        cout<<"\n\t\t\t\t Total Fare : "<<T.total;
                        cout<<"\n\t\t\t\t ______________________________________________________ ";
                    }
              }
           //   fBook.seekg(0);
                 cout<<"\n\n\n\t\t\t\t    Enter the Ticket to be Deleted :"; cin>>ch;
                   int j=0;
                     while(fCancel.read((char*)&T,sizeof(T)))
                               {
                                if(strcmp(T.Username,U.username)==0)
                                    {
                                        j++;
                                        if(j!=ch)
                                            fCancel2.write((char*)&T,sizeof(T));
                                    }
                                else fCancel2.write((char*)&T,sizeof(T));
                                }
                 fCancel.close();
                 fCancel2.close();
                 remove("Ticket_list.txt");
                 rename("temp2.txt","Ticket_list.txt");
                     cout<<"\n\n\n\t\t\t\t ______________________________________________________ ";
                     cout<<"\n\n\n\t\t\t\t|            Ticket Canceled Successfully!             | ";
                     cout<<"\n\n\n\t\t\t\t|______________________________________________________| ";

        system("pause");
        return;
}


int main()
{
    char ch;
//    int i=0;
    //gotoxy(40,40);
    label2:
    cout<<"\n\t\t\t\t\t _______________________________________ ";
    cout<<"\n\t\t\t\t\t|      WELCOME TO INDIAN RAILWAYS       |";
    cout<<"\n\t\t\t\t\t|      --------------------------       |";
    cout<<"\n\t\t\t\t\t|                                       |";
    cout<<"\n\t\t\t\t\t|      1. For Sign-In.                  |";
    cout<<"\n\t\t\t\t\t|      2. For Sign-Up.                  |";
    cout<<"\n\t\t\t\t\t|      3. For Administration-mode       |";
    cout<<"\n\t\t\t\t\t|      4. For Exit                      |";
    cout<<"\n\t\t\t\t\t|_______________________________________|\n";
    cin>>ch;
    switch(ch)
    {
        case '1'  :   SignIn();
                      break;
        case '2'  :   SignUp();
                      break;
        case '3'  :   AdminMode();
                      break;
        case '4'  :   system("cls");
                      goto label1;
                      break;
        default :   system("cls");
                    goto label2;
                    break;
    }

    label1:
    return 0;
}
