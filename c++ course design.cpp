#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>


using namespace std;


class account
{
	int accID;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();
	void display_account() const;
	void modify();
	void dep(int);
	void withdraw(int);
	void report() const;
	int retaccID() const;
	int retdeposit() const;
	char rettype() const;
};


void account::create_account()
{
	cout<<"\nEnter The Account ID :";
	cin>>accID;
	cout<<"\n\nEnter The Account Holder's name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The Account (C/S) :";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial Amount(>=1000 for Saving and >=2000 for current ) :";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}

void account::display_account() const
{
	cout<<"\nAccount ID : "<<accID;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance Amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nAccount ID : "<<accID;
	cout<<"\nModify Account Holder's Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}


void account::dep(int x){
	deposit+=x;
}

void account::withdraw(int x){
	deposit-=x;
}

void account::report() const{
	cout<<accID<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}


int account::retaccID() const{
	return accID;
}

int account::retdeposit() const{
	return deposit;
}

char account::rettype() const{
	return type;
}


void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();



int main()
{
	char ch;
	int n;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tEnter the number to choose your option: ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;

		case '2':
			cout<<"\n\n\tEnter The  Account ID : "; cin>>n;
			deposit_withdraw(n, 1);
			break;

		case '3':
			cout<<"\n\n\tEnter The Account ID : "; cin>>n;
			deposit_withdraw(n, 2);
			break;

		case '4':
			cout<<"\n\n\tEnter The  Account ID : "; cin>>n;
			display_sp(n);
			break;

		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The Account ID : "; cin>>n;
			delete_account(n);
			break;

		 case '7':
			cout<<"\n\n\tEnter The  Account ID : "; cin>>n;
			modify_account(n);
			break;

		 case '8':
			cout<<"\n\n\tThank You for Banking with us...";
			break;

		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');

	return 0;

}



void intro()
{
	cout<<"****************   Welcome to Our Bank Management System   ************"<< endl;
	cout<<"***********************************************************************"<<endl;
    cout<<"***********************************************************************"<<endl;
	cout<<"                       To continue press enter key                      "<<endl;

	cin.get();
}




void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}



void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press enter Key ";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retaccID()==n)
		{
			ac.display_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}



void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Invalid. Try again...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retaccID()==n)
		{
			ac.display_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record is invalid ";
}



void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press enter Key";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retaccID()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord deleted ..";
}




void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Invalid!!! Press enter to be back";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"=======================================================\n";
	cout<<"A/c no.           NAME            Type  Balance\n";
	cout<<"=======================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}




void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retaccID()==n)
		{
			ac.display_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<1000 && ac.rettype()=='S') || (bal<2000 && ac.rettype()=='C'))
					cout<<"Insufficient Balance";
				else
					ac.withdraw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Entered choice is invalid,Please try again";
}


