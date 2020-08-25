#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
using namespace std;
class student
{
	int rollno;
	char name[50];
	int Tution_fee, computer_fee, hostel_fee, bus_fee, mess_fee;
	int total;
	void calculate();
public:
	void getdata();
	void showdata() const;
	void show_tabular() const;
	int retrollno() const;
};


void student::calculate()
{
	total = Tution_fee + computer_fee + hostel_fee + bus_fee + mess_fee;
}
void student::getdata()
{
	cout<<"\nEnter The roll number of student: ";
	cin>>rollno;
	cout<<"\n\nEnter The Name of student: ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter The Tution Fee : ";
	cin>>Tution_fee;
	cout<<"\nEnter The Computer fee : ";
	cin>>computer_fee;
	cout<<"\nEnter The Hostel fee: ";
	cin>>hostel_fee;
	cout<<"\nEnter The Bus fee : ";
	cin>>bus_fee;
	cout<<"\nEnter The Mess fee : ";
	cin>>mess_fee;
	calculate();
}

void student::showdata() const
{
	cout<<"\nRoll number of student : "<<rollno;
	cout<<"\nName of student : "<<name;
	cout<<"\nTution fee : "<<Tution_fee;
	cout<<"\nComputer fee : "<<computer_fee;
	cout<<"\nHostel fee : "<<hostel_fee;
	cout<<"\nBus fee: "<<bus_fee;
	cout<<"\nMess fee :"<<mess_fee;
	cout<<"\nTotal fees  :"<<total;
}

void student::show_tabular() const
{
	cout<<rollno<<setw(4)<<" "<<name<<setw(12)<<Tution_fee<<setw(18)<<computer_fee<<setw(15)<<hostel_fee<<setw(10)<<bus_fee<<setw(12)<<mess_fee<<setw(10)<<total<<setw(10)<<endl;
}

int  student::retrollno() const
{
	return rollno;
}

void write_student();
void display_all();
void display_sp(int);
void modify_studentfee(int);
void delete_studentfee(int);
void total_fee();
void fees();
void intro();
void entry_menu();

int main()
{

	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2);
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. FEES MENU";
		cout<<"\n\n\t02. ENTRY/EDIT MENU";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		switch(ch)
		{
			case '1': fees();
				break;
			case '2': entry_menu();
				break;
			case '3':
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
	return 0;
}

void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.txt",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    cout<<"\n\nStudent record Has Been Created ";
	cin.ignore();
	cin.get();
}

void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}

void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
}

void modify_studentfee(int n)
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.txt",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}

	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
		    int pos=(-1)*static_cast<int>(sizeof(st));
		    File.seekp(pos,ios::cur);
		    File.write(reinterpret_cast<char *> (&st), sizeof(student));
		    cout<<"\n\n\t Record Updated";
		    found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();

}

void delete_studentfee(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.txt",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.txt");
	rename("Temp.txt","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}
void total_fee()
{
	student st;
	ifstream inFile;
	inFile.open("student.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS FEES \n\n";
	cout<<"====================================================================================================================\n";
	cout<<"R.No   	Name          	 Tution fee 	  Computer fee 	  Hostel fee     Bus fee   Mess fee   Total "<<endl;
	cout<<"====================================================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}

void fees()
{
	char ch;
	int rno;
	system("cls");
	cout<<"\n\n\n\tFEES MENU";
	cout<<"\n\n\n\t1. Student FEE";
	cout<<"\n\n\t2. Class FEE";
	cout<<"\n\n\t3. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	total_fee();
				 break;
	case '2' :	cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
				display_sp(rno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}

void intro()
{
	cout<<" \t\t**********************************************************\n\n";
	cout<<" \t\t\tCHANDIGARH GROUP OF COLLEGES\n\n";
	cout<<" \t\t\tB.TECH STUDENT\n\n";
	cout<<" \t\t**********************************************************";
	cout<<"\n\n\n\t\t\t\t\t     STUDENT";
	cout<<"\n\n\t\t\t\t        FEES MANAGEMENT";
	cout<<"\n\n\t\t\t\t\t      PROJECT";
	cout<<"\n\n\n\t\tMADE BY : HIMANSHU RAJ";
	cout<<"\n\t\tCOLLEGE : CHANDIGARH GROUP OF COLLEGES";
	cout<<"\n\t\tROLL. no. : 1815687\n";
	cout<<"\n\t\tPress Enter: ";
	cin.get();
}

void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE STUDENT FEES";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS FEES";
	cout<<"\n\n\t3.SEARCH STUDENT FEES ";
	cout<<"\n\n\t4.MODIFY STUDENT FEES";
	cout<<"\n\n\t5.DELETE STUDENT FEES";
	cout<<"\n\n\t6.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				display_sp(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				modify_studentfee(num);
				break;
	case '5':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				delete_studentfee(num);break;
	case '6':	break;
	default:	cout<<"\a"; entry_menu();
	}
}

