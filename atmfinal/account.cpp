#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include "account.h"
#include<cctype>
#include<iomanip>
using namespace std;


void account::create_account()
{
	cout << "|************************* NEW ACCOUNT *****************************|"<<endl<<endl;
	cout << "  Enter The account No.(ID) : ";
	cin>>acno;
	cout << "  Enter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout << "|--------------------- Choose type deposit -------------------------|"<<endl;
	cout << "  Enter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout << "  Enter The day of deposit : ";
	cin>>deday;
	cout << "  Enter The Initial amount : ";
	cin>>deposit;
	cout << "                     Account Created!!..."<<endl;
	cout << "|___________________________________________________________________|"<<endl;
}

void account::show_account() const
{
	cout << "|************************* SHOW ACCOUNT ****************************|"<<endl<<endl;
	cout << "          Account No.(ID) : "<<acno<<endl;
	cout << "          Account Holder Name : "<<name<<endl;
	cout << "          Type of Account : "<<type<<endl;
	cout << "          Day of deposit : "<<deday<<endl;
	cout << "          Balance amount : "<<deposit<<endl;
	cout << "|___________________________________________________________________|"<<endl;
}


void account::modify()
{
	cout << "|************************* ACCOUNT MODIFY **************************|"<<endl<<endl;
	cout << "            Account No. : "<<acno<<endl;
	cout << "            Modify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout << "            Modify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout << "            Enter Deposite Day(>90) You have 2.55% balance : ";
	cin>>deday;
	cout << "            Modify Balance amount : ";
	cin>>deposit;
	cout << "\n                       Success!!..."<<endl;
	cout << "|___________________________________________________________________|"<<endl;
}

	
void account::dep(float x)
{
	if(deday>=90){
	x = deposit+(((deposit*(0.55/100))*deday)/365);
	deposit+=x;}
	else{
	deposit += x;
	}
}
	
void account::draw(float x)
{
	deposit-=x;
}
	
void account::report() const
{
	cout<<acno<<"\t\t"<<name<<"\t\t"<<type<<"\t     "<<deposit<<endl;
}

	
int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}

int account::daydeposit() const 
{
	return deday;
}

