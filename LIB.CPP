
//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>

//****************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************


/*****************************************************************
		     CLASS TO HOLD BOOK RECORDS
 *****************************************************************/


class book
{
	char bno[6];
	char bname[50];
	char aname[20];
  public:
	void create_book()//Entering New book
	{       sound(900);
		delay(300);
		nosound();
		textcolor(9);
		cout<<"\n";
		cprintf("NEW BOOK ENTRY...");
		cout<<"\n";
		textcolor(15);
		cout<<"\n";
		cprintf("Enter The book no.:");
		cin>>bno;
		textcolor(9);
		cout<<"\n\n";
		cprintf("Enter The Name of The Book: ");
		gets(bname);
		textcolor(15);
		cout<<"\n\n";
		cprintf("Enter The Author's Name: ");
		gets(aname);
		textcolor(9);
		cout<<"\n\n\n";
		cprintf("Book Created..");
	}

	void show_book()
	{
		textcolor(15);
		cout<<"\n";
		cprintf("Book no. : ");
		cout<<bno;
		cout<<"\n";
		cprintf("Book Name : ");
		puts(bname);
		cprintf("Author Name : ");
		puts(aname);
	}

	void modify_book()
	{
		textcolor(6);
		cout<<"\n";
		cprintf("Book no. : ");
		cout<<bno;
		textcolor(15);
		cout<<"\n";
		cprintf("Modify Book Name : ");
		gets(bname);
		textcolor(6);
		cprintf("Modify Author's Name of Book : ");
		gets(aname);
	}

	char* retbno()
	{
		return bno;
	}

	void report()
	{cout<<"\t"<<bno<<setw(30)<<bname<<setw(25)<<aname<<endl;}


}b1;         //End of book class


/******************************************************************
		    CLASS TO HOLD STUDENT RECORDS
 ******************************************************************/

class student
{
	char admno[6];
	char name[20];
	char stbno[6];
	int token;
public:
	void create_student()  //Creating student record
	{
		clrscr();
		textcolor(5);
		cout<<"\n";
		cprintf("NEW STUDENT ENTRY...");
		cout<<"\n\n";
		textcolor(15);
		cout<<"\n";
		cprintf("Enter The admission no.: ");
		cin>>admno;
		cout<<"\n\n";
		cprintf("Enter The Name of The Student: ");
		gets(name);
		token=0;
		stbno[0]='/0';
		textcolor(4);
		cout<<"\n\n";
		cprintf("Student Record Created..");
	}

	void show_student()     //Display student record
	{
		textcolor(15);
		cout<<"\n";
		cprintf("Admission no. : ");
		cout<<admno;
		cout<<"\n";
		cprintf("Student Name : ");
		puts(name);
		cout<<"\n";
		cprintf("No of Book issued : ");
		cout<<token;
		if(token==1)
		{	textcolor(15);
			cout<<"\n";
			cprintf("Book No:");
			cout<<stbno;
		}
	}

	void modify_student()
	{
		textcolor(9);
		cout<<"\n";
		cprintf("Admission no. : ");
		cout<<admno;
		textcolor(6);
		cout<<"\n";
		cprintf("Modify Student Name : ");
		gets(name);
	}

	char* retadmno()
	{
		return admno;
	}

	char* retstbno()
	{
		return stbno;
	}

	int rettoken()
	{
		return token;
	}

	void addtoken()
	{token=1;}

	void resettoken()
	{token=0;}

	void getstbno(char t[])
	{
		strcpy(stbno,t);
	}



	void report()
	{
	cout<<"\t"<<admno<<setw(30)<<name<<setw(20)<<token<<endl;
	}

};         //End of student class




//*****************************************************************
//    	    Global declaration for stream object, object
//*****************************************************************

fstream fp,fp1;
book bk;
student st;




//***************************************************************
//    	    Function to write in file
//****************************************************************

void write_book()
{
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do
	{
		clrscr();
		bk.create_book();
		fp.write((char*)&bk,sizeof(book));
		textcolor(15);
		cout<<"\n\n";
		cprintf("Do you want to add more record..(y/n?):");
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void write_student()
{
	char ch;
	fp.open("student.dat",ios::out|ios::app);
	do
	{
		st.create_student();
		fp.write((char*)&st,sizeof(student));
		textcolor(6);
		cout<<"\n\n";
		cprintf("Do you want to add more record..(y/n?):");
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}







//***************************************************************
//    	Function to read specific record from file
//****************************************************************


void display_spb(char n[])
{
	textcolor(5);
	cout<<"\n";
	cprintf("BOOK DETAILS");
	int flag=0;
	fp.open("book.dat",ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
	{       textcolor(9);
		cout<<"\n\n\t";
		cprintf("Book does not exist");
	}
	getch();
}

void display_sps(char n[])
{
	textcolor(6);
	cout<<"\n";
	cprintf("STUDENT DETAILS");
	int flag=0;
	fp.open("student.dat",ios::in);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if((strcmpi(st.retadmno(),n)==0))
		{
			st.show_student();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
	{
	 textcolor(15);
	 cout<<"\n\n";
	 cprintf("Student does not exist");
	}
	getch();
}


//***************************************************************
//    	function to modify record of file
//****************************************************************


void modify_book()
{
	char n[6];
	int found=0;
	clrscr();
	textcolor(9);
	cout<<"\n\n\t";
	cprintf("MODIFY BOOK REOCORD.... ");
	textcolor(15);
	cout<<"\n\n\t";
	cprintf("Enter The book no. of The book:");
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found==0)
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
			textcolor(15);
			cout<<"\n";
			cprintf("Enter The New Details of book:");
			cout<<endl;
			bk.modify_book();
			int pos=-1*sizeof(bk);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&bk,sizeof(book));
			textcolor(5);
			cout<<"\n\n\t";
			cprintf(" Record Updated");
			found=1;
		}
	}

	fp.close();
	if(found==0)
	{
		textcolor(6);
		cout<<"\n\n\t";
		cprintf(" Record Not Found ");
	}
	getch();
}


void modify_student()
{
	char n[6];
	int found=0;
	clrscr();
	textcolor(12);
	cout<<"\n\n\t";
	cprintf("MODIFY STUDENT RECORD... ");
	textcolor(15);
	cout<<"\n\n\t";
	cprintf("Enter The admission no. of The student:");
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.show_student();
			textcolor(15);
			cout<<"\n\t";
			cprintf("Enter The New Details of student");
			cout<<endl;
			st.modify_student();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
			textcolor(6);
			cout<<"\n\n\t";
			cprintf(" Record Updated");
			found=1;
		}
	}

	fp.close();
	if(found==0)
	{       textcolor(5);
		cout<<"\n\n\t";
		cprintf(" Record Not Found ");
	}
	getch();
}


//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_student()
{
	char n[6];
	int flag=0;
	clrscr();
	textcolor(2);
	cout<<"\n\n\n\t";
	cprintf("DELETE STUDENT...");
	textcolor(15);
	cout<<"\n\n\t";
	cprintf("Enter The admission no. of the Student You Want To Delete : ");
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),n)!=0)
			fp2.write((char*)&st,sizeof(student));
		else
			flag=1;
	}

	fp2.close();
	fp.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	if(flag==1)
	{       textcolor(9);
		cout<<"\n\n\t";
		cprintf("Record Deleted ..");
	}
	else
	{	textcolor(5);
		cout<<"\n\n\t";
		cprintf("Record not found");
	}
	getch();
}
void delete_book()
{
	char n[6];
	clrscr();
	textcolor(CYAN);
	cout<<"\n\n\n\t";
	cprintf("DELETE BOOK ...");
	textcolor(15);
	cout<<"\n\n\t";
	cprintf("Enter The Book no. of the Book You Want To Delete : ");
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)!=0)
		{
			fp2.write((char*)&bk,sizeof(book));
		}
	}

	fp2.close();
	fp.close();
	remove("book.dat");
	rename("Temp.dat","book.dat");
	textcolor(6);
	cout<<"\n\n\t";
	cprintf("Record Deleted (IF IT EXISTED)...");
	getch();
}
/********************************************************************
	     Function to view Book Catalogue
 ********************************************************************/



void catalogue()
{
	clrscr();
	for(int hk=0;hk<80;hk++)
	cout<<'*';
	cout<<"\t";
	textcolor(YELLOW);
	cprintf("Book Id");
	cout<<"\t\t\t";
	textcolor(YELLOW);
	cprintf("Book Name");
	cout<<"\t\t";
	textcolor(YELLOW);
	cprintf("Author Name");
	cout<<endl;
	for( hk=0;hk<80;hk++)
	cout<<'*';
	ifstream fin("book.dat",ios::in);
	fin.read((char*)&b1,sizeof(book));
	while(! fin.eof())
	{

		b1.report();
		fin.read((char*)&b1,sizeof(book));
	}

	getch();
}


//***************************************************************
//    	function to display all students list
//****************************************************************

void display_alls()
{
	clrscr();
	fp.open("student.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	textcolor(5);
	cout<<"\n\n\t\t\t\t";
	cprintf("STUDENT LIST");
	cout<<"\n\n";
	textcolor(15);
	cprintf("================================================================================");
	cout<<"\n";
	cout<<"\t";
	cprintf("Adm No.");
	cout<<"\t\t\t";
	cprintf("Name");
	cout<<"\t\t\t";
	cprintf("Book Issued");
	cout<<"\n";
	cprintf("================================================================================");
	cout<<"\n";
	while(fp.read((char*)&st,sizeof(student)))
	{
		st.report();
	}

	fp.close();
	getch();
}


//****************************************************************
//    	function to display Books list
//****************************************************************

void display_allb()
{
	clrscr();
	fp.open("book.dat",ios::in);
	if(!fp)
	{
		textcolor(4);
		cprintf("ERROR!!! FILE COULD NOT BE OPENED ");
		getch();
		return;
	}

	textcolor(2);
	cout<<"\n\n\t\t\t\t";
	cprintf("Book LIST");
	cout<<"\n\n";
	textcolor(15);
	cprintf("================================================================================");
	cout<<"\n";
	cout<<"\t";
	cprintf("Book No.");
	cout<<"\t\t";
	cprintf("Book Name");
	cout<<"\t\t";
	cprintf("Author");
	cout<<"\n";
	cprintf("================================================================================");
	cout<<"\n";

	while(fp.read((char*)&bk,sizeof(book)))
	{
		bk.report();
	}
	fp.close();
	getch();
}



//***************************************************************
//    	      function to issue book
//****************************************************************

void book_issue()
{
	char sn[6],bn[6];
	int found=0,flag=0;
	clrscr();
	textcolor(YELLOW);
	cout<<"\n\n";
	cprintf("BOOK ISSUE ...");
	textcolor(15);
	cout<<"\n\n\t";
	cprintf("Enter The student's admission no.:");
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==0)
			{
				textcolor(15);
				cout<<"\n\n\t";
				cprintf("Enter the book no.: ");
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
				{
					if(strcmpi(bk.retbno(),bn)==0)
					{
						bk.show_book();
						flag=1;
						st.addtoken();
						st.getstbno(bk.retbno());
						int pos=-1*sizeof(st);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						textcolor(15);
						cout<<"\n\n\t";
						cprintf(" Book issued successfully");
						cout<<"\n\n";
						textcolor(5);
						cprintf("Please Note: Write the current date !! ");
						textcolor(CYAN);
						cout<<"\n\n";
						cprintf("Tentative period of keeping the book is 15 days....");
						textcolor(2);
						cout<<"\n";
						cprintf("Fine: Re 1 per day");


					}
				}
				if(flag==0)
				{	textcolor(6);
					cout<<"Book no does not exist";
				}
			}
			else
			 {      textcolor(3);
				cout<<"You have not returned the last book ";
			 }
		}
	}
	if(found==0)
	{       textcolor(15);
		cprintf("Student record does not exist...");
	}
	getch();
	fp.close();
	fp1.close();
}

//***************************************************************
//    	Function to deposit book
//****************************************************************

void book_deposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    clrscr();
    textcolor(2);
    cout<<"\n\n";
    cprintf("BOOK DEPOSIT ...");
    textcolor(15);
    cout<<"\n\n\t";
    cprintf("Enter The students admission no.:");
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
	    if(strcmpi(st.retadmno(),sn)==0)
	    {
		    found=1;
		    if(st.rettoken()==1)
		    {
			while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			{
			   if(strcmpi(bk.retbno(),st.retstbno())==0)
			{
				bk.show_book();
				flag=1;
				textcolor(15);
				cout<<"\n\n";
				cprintf("Book deposited in no. of days:");
				cin>>day;
				if(day>15)
				{
				   fine=(day-15)*1;
				   textcolor(9);
				   cout<<"\n\n";
				   cprintf("Fine has to deposited Rs: ");
				   cout<<fine;
				}
					st.resettoken();
					int pos=-1*sizeof(st);
					fp.seekp(pos,ios::cur);
					fp.write((char*)&st,sizeof(student));
					textcolor(5);
					cout<<"\n\n\t";
					cprintf(" Book deposited successfully");
			}
		    }
		  if(flag==0)
		   {
		    textcolor(15);
		    cprintf("Book no does not exist");
		   }
		      }
		 else
		  {	textcolor(6);
			cprintf("No book is issued..please check!!");
		  }
		}
	   }
      if(found==0)
      { textcolor(15);
	cprintf("Student record does not exist...");
      }
	getch();
  fp.close();
  fp1.close();
  }




//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	clrscr();
	gotoxy(20,0);
	textcolor(6);
	cout<<"\n";
	cprintf(" B.D.M.INTERNATIONAL");
	gotoxy(20,2);
	textcolor(6);
	cout<<"\n";
	cprintf(" PRATAPGARH");
	gotoxy(35,9);
	textcolor(9);
	cprintf("LIBRARY");
	gotoxy(35,12);
	cprintf("MANAGEMENT");
	gotoxy(35,15);
	cprintf("SYSTEM");
	textcolor(15);
	cout<<"\n\n\n\n";
	cprintf("MADE BY:  Indrasish Ghosh");
	cout<<"\n\t";
	cprintf("  Abhishek Bhattaharya");
	cout<<"\n\t";
	cprintf("  Dwaipayan Sarkar");
	cout<<"\n\t";
	cprintf("  Snehail Gupta");
	textcolor(CYAN);
	cout<<"\n\n";
	cprintf("SCHOOL : B.D.M.I.");
	getch();
}



//***************************************************************
//    	ADMINISTRATOR MENU FUNCTION
//****************************************************************

void admin_menu()
{
	clrscr();
	int ch2;
	textcolor(5);
	cout<<"\n\n\t";
	cprintf("ADMINISTRATOR MENU");
	textcolor(15);
	cout<<"\n\n\t";
	cprintf("1.CREATE STUDENT RECORD");
	cout<<"\n\n\t";
	cprintf("2.DISPLAY ALL STUDENTS RECORD");
	cout<<"\n\n\t";
	cprintf("3.DISPLAY SPECIFIC STUDENT RECORD ");
	cout<<"\n\n\t";
	cprintf("4.MODIFY STUDENT RECORD");
	cout<<"\n\n\t";
	cprintf("5.DELETE STUDENT RECORD");
	cout<<"\n\n\t";
	cprintf("6.CREATE BOOK ");
	cout<<"\n\n\t";
	cprintf("7.DISPLAY ALL BOOKS ");
	cout<<"\n\n\t";
	cprintf("8.DISPLAY SPECIFIC BOOK ");
	cout<<"\n\n\t";
	cprintf("9.MODIFY BOOK ");
	cout<<"\n\n\t";
	cprintf("10.DELETE BOOK ");
	cout<<"\n\n\t";
	cprintf("11.BACK TO MAIN MENU");
	textcolor(2);
	cout<<"\n\n\t";
	cprintf("Please Enter Your Choice (1-11): ");
	cin>>ch2;
	switch(ch2)
	{
		case 1: clrscr();
			write_student();break;
		case 2: textcolor(15);
			display_alls();break;
		case 3: char num[6];
			clrscr();
			textcolor(15);
			cout<<"\n\n\t";
			cprintf("Please Enter The Admission No. :");
			cin>>num;
			display_sps(num);
			break;
		case 4: modify_student();break;
		case 5: delete_student();break;
		case 6: clrscr();
			write_book();break;
		case 7: display_allb();break;
		case 8: {
			char num[6];
			clrscr();
			textcolor(15);
			cout<<"\n\n\n\t";
			cprintf("Please Enter The book No.: ");
			cin>>num;
			display_spb(num);
			break;
			}
		case 9: modify_book();break;
		case 10:delete_book();break;
		case 11: return;
		default:cout<<"\a";
	}
	admin_menu();
}


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


void main()
{


	clrscr();


	for(int g=40;g>=20;g--)
{
	textcolor(YELLOW);
	delay(100);
	gotoxy(g,12);
	cputs(" WELCOME TO B.D.M.INTERNATIONAL LIBRARY ");
}
	char ch,ab;

	sound (196);delay(125);
	sound (262);delay(125);
	sound (330);delay(125);
	sound (392);delay(125);
	sound (523);delay(125);
	sound (660);delay(125);
	sound (784);delay(575);
	sound (660);delay(575);
	sound (207);delay(125);
	sound (262);delay(125);
	sound (311);delay(125);
	sound (415);delay(125);
	sound (523);delay(125);
	sound (622);delay(125);
	sound (830);delay(575);
	sound (622);delay(575);
	sound (233);delay(125);
	sound (294);delay(125);
	sound (349);delay(125);
	sound (466);delay(125);
	sound (587);delay(125);
	sound (698);delay(125);
	sound (932);delay(575);
	sound (932);delay(125);
	sound (932);delay(125);
	sound (932);delay(125);


       nosound();

       intro();

	do
	{
		clrscr();
		textcolor(YELLOW);
		cout<<"\n\n\t";
		cprintf("MAIN MENU");
		cout<<"\n";
		cout<<"\n\n\t";
		textcolor(15);
		cprintf("01. BOOK ISSUE");
		cout<<"\n\n\t";
		textcolor(15);
		cprintf("02. BOOK DEPOSIT");
		cout<<"\n\n\t";
		textcolor(15);
		cprintf("03. ADMINISTRATOR MENU");
		cout<<"\n\n\t";
		textcolor(15);
		cprintf("04. SHOW CATALOGUE");
		cout<<"\n\n\t";
		textcolor(15);
		cprintf("05. EXIT");
		textcolor(5);
		cout<<"\n\n\t";
		cprintf("Please Select Your Option (1-5): ");
		ch=getche();
		switch(ch)
		{
			case '1':clrscr();
				 book_issue();
				 break;
			case '2':book_deposit();
				 break;
			case '3':textcolor(15);
				 cout<<"\n\n\t";
				 cprintf("Please enter your password:");
				ab=getche();
				if(ab=='p'||ab=='P')
				   admin_menu();

				else
				{       textcolor(9);
					cout<<"\n\n\t";
					cprintf("WRONG PASSWORD!! TRY AGAIN!!");
					getch();
				}

				break;

			case '4':textcolor(15);
				 catalogue();break;

			case '5': exit(0);break;
			default :cout<<"\a";
		}
	}
	while(ch!='5');
}


