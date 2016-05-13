

//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include "account.h"
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************





//***************************************************************
//    	function declaration
//****************************************************************
void write_account();	//function to write record in binary file
void display_sp(float);	//function to display account details given by user
void modify_account(float);	//function to modify record of file
void delete_account(float);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(float, float); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
	char ch;
	float num;
	intro();
	do
	{
		system("cls");
		cout << "|*************** Please select an ATM to continue ********************|"<<endl;
		cout << "|_____________________________________________________________________|"<<endl;
		cout << "|                    Automatic Teller Machine                         |"<<endl;
		cout << "|_____________________________________________________________________|"<<endl;
	    cout << "|                            MAIN MENU                                |"<<endl;
		cout << "|                        1. NEW ACCOUNT                               |"<<endl;
		cout << "|                        2. DEPOSIT AMOUNT                            |"<<endl;
		cout << "|                        3. WITHDRAW AMOUNT                           |"<<endl;
		cout << "|                        4. BALANCE ENQUIRY                           |"<<endl;
		cout << "|                        5. ALL ACCOUNT HOLDER LIST                   |"<<endl;
		cout << "|                        6. CLOSE AN ACCOUNT                          |"<<endl;
		cout << "|                        7. MODIFY AN ACCOUNT                         |"<<endl;
		cout << "|                        8. EXIT                                      |"<<endl;
		cout << "|_____________________________________________________________________|"<<endl<<endl;
		cout << "                      Select Your Option (1-8) : ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
        cout << "|*********************************************************************|"<<endl;
			write_account();
			break;
		case '2':
			cout<<"\n     Enter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n     Enter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n     Enter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n     Enter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n     Enter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n     Thanks for using bank managemnt system";
			cout << "|_________________________________________________________________|"<<endl;
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}


//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile; 
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(float n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}


//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_account(float n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			float pos=(-1)*static_cast<float>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_account(float n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no."<<"\t\t"<<"NAME"<<"\t\t"<<"Type"<<"\t     "<<"Balance"<<"\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(float n, float option)
{
	float amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited : ";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw : " ;
				cin>>amt;
				float bal=ac.retdeposit()-amt;
				//if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					//cout<<"Insufficience balance";
				//else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<float>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}


//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************


void intro()
{
	
	//cin.get();
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************


