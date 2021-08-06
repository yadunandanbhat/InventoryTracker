#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<regex>

using namespace std;

//Record specification
class product{
public: char ind[5],pid[5],name[15],cost[5],stock[5],type[15];
}prdrec[20];

int no;
regex integer("(\\+|-)?[[:digit:]]+");

int get_prd_records()
{
	int I=0;
	fstream file2;
	file2.open("product_record.dat",ios::in);
	if(!file2)
	{
		return 0;
	}
	while(!file2.fail()) //Unpacking record data
 	{
		file2.getline(prdrec[I].ind,5,'|');
		file2.getline(prdrec[I].pid,5,'|');
		file2.getline(prdrec[I].name,15,'|');
		file2.getline(prdrec[I].cost,5,'|');
		file2.getline(prdrec[I].stock,5,'|');
		file2.getline(prdrec[I].type,15,'\n');
		I++; 	
 	}
	I--;
	file2.close();
	return I;
}

void retrieve_details(char st_no[])
{

	no = get_prd_records();
	for(int i=0;i<no;i++)
 	{
		if(strcmp(prdrec[i].ind,st_no)==0) 
	 	{
		// cout<<"\n"<<"Product details : ";
		// cout<<"\nProduct ID\t:"<<prdrec[i].pid<<"\nName\t:"<<prdrec[i].name<<"\nCost\t:" <<prdrec[i].cost<<"\nStock\t:"<<prdrec[i].stock<<"\nType\t:"<<prdrec[i].type<<"\n";
		printf("\n\t+-----------------------------+\n");
		printf("\t|       Product Details       |\n");
		printf("\t+-----------------------------+\n");
		printf("\t| Product ID:            %5s|\n", prdrec[i].pid);
		printf("\t| Name:        %15s|\n", prdrec[i].name);
		printf("\t| Cost:                  %5s|\n", prdrec[i].cost);
		printf("\t| Stock:                 %5s|\n", prdrec[i].stock);
		printf("\t| Type:        %15s|\n", prdrec[i].type);
		printf("\t+-----------------------------+\n");
		break;
	 	}
 	}
}


void add_product()
{
	char buf1[100],buf2[20];
	fstream file1,file2;
	int I,cnt;
	product s;

	cnt=get_prd_records();

	file1.open("index.dat",ios::out|ios::app);
	if(!file1)
	{
		cout<<R"(
    +--------------------------------------------------------------------------------------+    
    |                            Error opening the index file!                             |
    +--------------------------------------------------------------------------------------+    )"<<'\n';
		exit(0);
	}

	file2.open("product_record.dat",ios::out|ios::app);
	if(!file2)
	{
		cout<<R"(
    +--------------------------------------------------------------------------------------+    
    |                           Error opening the product record!                          |
    +--------------------------------------------------------------------------------------+    )"<<'\n';
		exit(0);
	}
	// cout<<"\nEnter the no. of products : ";
	// cin>>no;
	cout<<R"(
================================================================================================

	Enter the no. of products: )";
	cin>>no;
	cout<<"\tEnter the details below!\n"; 

	for(I=cnt; I<(cnt+no); I++)
    {                  
		cout<<R"(
================================================================================================)"<<'\n';
		cout<<"\n\tProduct ID\t: ";
		cin>>s.pid;
		while(!regex_match(s.pid,integer))
 		{
	 		if(!cin) break;
 			cout<<"\tInvalid datatype input. Enter integer: ";
 			cin>>s.pid;
 		}
		cout<<"\n\tName      \t: ";
		cin>>s.name;
		cout<<"\n\tCost      \t: ";
		cin>>s.cost;
		while(!regex_match(s.cost,integer))
 		{
	 		if(!cin) break;
 			cout<<"\tInvalid datatype input. Enter integer: ";
 			cin>>s.cost;
 		}
		cout<<"\n\tStock     \t: ";
		cin>>s.stock;
		while(!regex_match(s.stock,integer))
 		{
	 		if(!cin) break;
 			cout<<"\tInvalid datatype input. Enter integer: ";
 			cin>>s.stock;
 		}
		cout<<"\n\tType      \t: ";
		cin>>s.type;

		sprintf(buf2,"%s|%d\n",s.pid,I);
		file1<<buf2;

		sprintf(buf1,"%d|%s|%s|%s|%s|%s\n",I,s.pid,s.name,s.cost,s.stock,s.type);
		file2<<buf1;
	}
		file1.close();
		file2.close();
}

void search_product()
{
	int I,flag1;
	char st_no[5],st_pid[5],rt_pid[5];
	fstream file1;

	cout<<R"(
================================================================================================

	Enter the pid of the product whose info is to be displayed: )";
	cin>>st_pid;
	while(!regex_match(st_pid,integer))
 		{
	 		if(!cin) break;
 			cout<<"\tInvalid datatype input. Enter integer: ";
 			cin>>st_pid;
 		}
	cout<<R"(
================================================================================================)"<<'\n';
	file1.open("index.dat",ios::in); 
	if(!file1)
	{
		cout<<R"(
    +--------------------------------------------------------------------------------------+    
    |                            Error opening the index file!                             |
    +--------------------------------------------------------------------------------------+    )"<<'\n';
		exit(0);
	}
	flag1=0;
	while(!file1.eof())
	{
		file1.getline(rt_pid,5,'|');
		file1.getline(st_no,5,'\n');    
		if(strcmp(st_pid,rt_pid)==0)
		{
			retrieve_details(st_no);         
			flag1=1;                  
			break;
		}
	}
	if(!flag1)
	cout<<R"(
    +--------------------------------------------------------------------------------------+    
    |                                Record search failed!                                 |
    +--------------------------------------------------------------------------------------+    )"<<'\n';
	file1.close();
}

void delete_stdproduct(char pido[])
{
	int I=0;
	fstream file1,file2;

	no = get_prd_records();	
	int flag=-1;
	for(I=0;I<no;I++)       //Check for the record's existence
	{
		if(strcmp(prdrec[I].ind,pido)==0)
		{
			flag=I;
			break;
		}	

	}
	if(flag==-1)                //Record not found
	{
		cout<<R"(
    +--------------------------------------------------------------------------------------+    
    |                               Error! Record not found!                               |
    +--------------------------------------------------------------------------------------+    )"<<'\n';
		return;
	}
	if(flag==(no-1))            //Delete found last record
	{
		no--;
		cout<<R"(
    +--------------------------------------------------------------------------------------+    
    |                                       Deleted!                                       |
    +--------------------------------------------------------------------------------------+    )"<<'\n';
	}
	else
	{
		for(I=flag;I<no;I++)
		{
			prdrec[I] = prdrec[I+1];
		}
		no--;
		cout<<R"(
    +--------------------------------------------------------------------------------------+    
    |                                       Deleted!                                       |
    +--------------------------------------------------------------------------------------+    )"<<'\n';
	}

	file1.open("index.dat",ios::out);  
	file2.open("product_record.dat",ios::out);  
	for(I=0;I<no;I++)                   
	{                                   
		file1<<prdrec[I].pid<<"|"<<I<<"\n";
		file2<<I<<"|"<<prdrec[I].pid<<"|"<<prdrec[I].name <<"|"<<prdrec[I].cost<<"|"<<prdrec[I].stock<<"|"<<prdrec[I].type<<"\n";
	}
	file1.close();
	file2.close();
	return;
}



void delete_product()
{
	int I,flag;
	char st_no[5],st_pid[5],rt_pid[5];
	fstream file1;

	cout<<R"(
================================================================================================

	Enter the pid of the product to be deleted: )";
	cin>>st_pid;
	while(!regex_match(st_pid,integer))
 		{
	 		if(!cin) break;
 			cout<<"\tInvalid datatype input. Enter integer: ";
 			cin>>st_pid;
 		}
	cout<<R"(
================================================================================================)"<<'\n';
	file1.open("index.dat",ios::in);
	if(!file1)
	{
		cout<<R"(
    +--------------------------------------------------------------------------------------+    
    |                            Error opening the index file!                             |
    +--------------------------------------------------------------------------------------+    )"<<'\n';
		exit(0);
	}
	flag=0;

	while(!file1.eof())
	{
		file1.getline(rt_pid,5,'|');      //Search index file and
		file1.getline(st_no,5,'\n');       //call deletion
		//if index found
		if(strcmp(st_pid,rt_pid)==0)
		{
			delete_stdproduct(st_no); 
			flag=1;
			break;
		}
	}
	if(!flag)
	cout<<R"(
    +--------------------------------------------------------------------------------------+    
    |                                   Deletion failed!                                   |
    +--------------------------------------------------------------------------------------+    )"<<'\n'; 
	file1.close();
	
	
}

void display_products()
{
	fstream file2;
	product s;
	
	file2.open("product_record.dat",ios::in);
	cout<<R"(
    +--------------------------------------------------------------------------------------+    
    |                                  Inventory Details!                                  |
    +--------------------------------------------------------------------------------------+    )"<<'\n';
	printf("\t      +-------+-------+-----------------+-------+-------+-----------------+\n");
	printf("\t      | Index |  PID  |       Name      |  Cost | Stock |       Type      |\n");
	printf("\t      +-------+-------+-----------------+-------+-------+-----------------+");
	while(!file2.fail()) //Unpacking record data
 	{
		file2.getline(s.ind,5,'|');
		file2.getline(s.pid,5,'|');
		file2.getline(s.name,15,'|');
		file2.getline(s.cost,5,'|');
		file2.getline(s.stock,5,'|');
		file2.getline(s.type,15,'\n');
		printf("\n\t      | %-5s | %-5s | %-15s | %-5s | %-5s | %-15s |", s.ind, s.pid, s.name, s.cost, s.stock, s.type);
 	}
	printf("\n\t      +-------+-------+-----------------+-------+-------+-----------------+\n");
	file2.close();
}

void modify_product()
{
  fstream file2;
  char pid[5];
  int I,j;
  product s1[20];

  file2.open("product_record.dat",ios::in);
  if(!file2)
  {
      cout<<R"(
    +--------------------------------------------------------------------------------------+    
    |                           Error opening the product record!                          |
    +--------------------------------------------------------------------------------------+    )"<<'\n';
      exit(0);
  }

  cout<<R"(
================================================================================================

	Enter the pid of the product to be modified: )";
  cin>>pid;
  while(!regex_match(pid,integer))
 		{
	 		if(!cin) break;
 			cout<<"\tInvalid datatype input. Enter integer: ";
 			cin>>pid;
 		}
  cout<<R"(
================================================================================================)"<<'\n';
  I=0;

  while(!file2.eof())//Loop through end of file & extract all records
  {
      file2.getline(s1[I].ind,5,'|');
      file2.getline(s1[I].pid,5,'|');
      file2.getline(s1[I].name,15,'|');
      file2.getline(s1[I].cost,5,'|');
      file2.getline(s1[I].stock,5,'|');
      file2.getline(s1[I].type,15,'\n');
      I++;
  }
  I--;
  
  for(j=0;j<I;j++)
  {
      if(strcmp(pid,s1[j].pid)==0)
      {
          cout<<"\n\tThe old values of the record with pid "<<pid<<" are: ";
          cout<<"\n\n\tPID    = "<<s1[j].pid;
          cout<<"\n\n\tName   = "<<s1[j].name;
          cout<<"\n\n\tCost   = "<<s1[j].cost;
          cout<<"\n\n\tStock  = "<<s1[j].stock;
          cout<<"\n\n\tType   = "<<s1[j].type;
		  cout<<'\n'<<R"(
================================================================================================)";
          cout<<"\n\n\tEnter the new values (The PID can't be changed)\n";
          cout<<"\n\tName   = ";  cin>>s1[j].name;
          cout<<"\n\tCost   = ";  cin>>s1[j].cost;
		  while(!regex_match(s1[j].cost,integer))
 		  {
	 		if(!cin) break;
 			cout<<"\tInvalid datatype input. Enter integer: ";
 			cin>>s1[j].cost;
 		  }
          cout<<"\n\tStock  = ";  cin>>s1[j].stock;
		  while(!regex_match(s1[j].stock,integer))
 		  {
	 		if(!cin) break;
 			cout<<"\tInvalid datatype input. Enter integer: ";
 			cin>>s1[j].stock;
 		  }
          cout<<"\n\tType   = ";  cin>>s1[j].type;
		  cout<<'\n';
          break;
      }//end of if
  }//end of for

    if(j==I)
    {
        cout<<R"(
    +--------------------------------------------------------------------------------------+    
    |                    The product with the given pid is not present!                    |
    +--------------------------------------------------------------------------------------+    )"<<'\n';
        return;
    }

    file2.close();

    fstream out1;
    out1.open("product_record.dat",ios::out);
    if(!out1)
    {
          cout<<R"(
    +--------------------------------------------------------------------------------------+    
    |                           Error opening the product record!                          |
    +--------------------------------------------------------------------------------------+    )"<<'\n'; 
          return;
    }
    for(j=0;j<I;j++)
    {
        out1<<s1[j].ind<<'|'<<s1[j].pid<<'|'<<s1[j].name<<'|'<<s1[j].cost<<'|'<<s1[j].stock<<'|'<<s1[j].type<<'\n';
    }
    out1.close();
}

int main()
{
	int choice;
	cout<<R"(
    +--------------------------------------------------------------------------------------+    
    |  _____                      _                     _______             _              |    
    | |_   _|                    | |                   |__   __|           | |             |    
    |   | |  _ ____   _____ _ __ | |_ ___  _ __ _   _     | |_ __ __ _  ___| | _____ _ __  |    
    |   | | | '_ \ \ / / _ \ '_ \| __/ _ \| '__| | | |    | | '__/ _` |/ __| |/ / _ \ '__| |    
    |  _| |_| | | \ V /  __/ | | | || (_) | |  | |_| |    | | | | (_| | (__|   <  __/ |    |    
    | |_____|_| |_|\_/ \___|_| |_|\__\___/|_|   \__, |    |_|_|  \__,_|\___|_|\_\___|_|    |    
    |                                            __/ |                                     |    
    |                                           |___/                                      |    
    +--------------------------------------------------------------------------------------+    )"<<'\n';
	for(;;)
	{
		cout<<R"(
================================================================================================

	+--------------------------+
	|   Available Operations   |
	+--------------------------+
	| 1. Add a product         |
	| 2. Search for a product  |
	| 3. Delete a product      |
	| 4. Display all products  |
	| 5. Modify a product info |
	| 0. Exit                  |
	+--------------------------+

	Enter your choice: )";
		cin>>choice;
		switch(choice)
		{
			case 1: add_product();
					break;
			case 2: search_product();
					break;
			case 3: delete_product();
					break;
			case 4: display_products();
					break;
            case 5: modify_product();
                    break;
            case 0: exit(1);
			default:cout<<R"(
	Invalid choice! The program will be terminating!)";
					exit(0);	
		}
	}
}