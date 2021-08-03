#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>

using namespace std;

//Record specification
class product{
public: char ind[5],pid[5],name[15],cost[5],stock[5],type[15];
}prdrec[20];

int no;

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
		cout<<"\n"<<"Product details : ";
		cout<<"\nProduct ID\t:"<<prdrec[i].pid<<"\nName\t:"<<prdrec[i].name<<"\nCost\t:" <<prdrec[i].cost<<"\nStock\t:"<<prdrec[i].stock<<"\nType\t:"<<prdrec[i].type<<"\n";
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
		cout<<"\nError opening index file!\n";
		exit(0);
	}

	file2.open("product_record.dat",ios::out|ios::app);
	if(!file2)
	{
		cout<<"\nError product record file!\n";
		exit(0);
	}

	cout<<"\nEnter the no. of products : ";
	cin>>no;
	cout<<"\nEnter the details:"; 

	for(I=cnt; I<(cnt+no); I++)
    {                  
		cout<<"\nProduct ID\t: ";
		cin>>s.pid;
		cout<<"\nName\t: ";
		cin>>s.name;
		cout<<"\nCost\t: ";
		cin>>s.cost;
		cout<<"\nStock\t: ";
		cin>>s.stock;
		cout<<"\nType\t: ";
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

	cout<<"\nPlease enter the pid of the product whose info is to be displayed: ";
	cin>>st_pid;
	file1.open("index.dat",ios::in); 
	if(!file1)
	{
		cout<<"\nError opening index file!";
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
	cout<<"\nRecord search failed!"; 
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
		cout<<"\nError! Record not found!";
		return;
	}
	if(flag==(no-1))            //Delete found last record
	{
		no--;
		cout<<"\nDeleted!";
		
	}
	else
	{
		for(I=flag;I<no;I++)
		{
			prdrec[I] = prdrec[I+1];
		}
		no--;
		cout<<"\nDeleted!";
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

	cout<<"\nPlease enter the pid of the product whose info is to be deleted: ";
	cin>>st_pid;
	file1.open("index.dat",ios::in);
	if(!file1)
	{
		cout<<"\nError opening the index file!";
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
	cout<<"\nDeletion failed!"; 
	file1.close();
	
	
}

void display_products()
{
	fstream file2;
	product s;
	
	file2.open("product_record.dat",ios::in);
	cout<<"\nInventory details: \n";
	cout<<"Index"<<"\t"<<"PID"<<"\t"<<"Name"<<"\t"<<"Cost"<<"\t"<<"Stock"<<"\t"<<"Type"<<"\t"<<endl; 
	while(!file2.fail()) //Unpacking record data
 	{
		file2.getline(s.ind,5,'|');
		file2.getline(s.pid,5,'|');
		file2.getline(s.name,15,'|');
		file2.getline(s.cost,5,'|');
		file2.getline(s.stock,5,'|');
		file2.getline(s.type,15,'\n');
		cout<<s.ind<<"\t"<<s.pid<<"\t"<<s.name<<"\t"<<s.cost<<"\t"<<s.stock<<"\t"<<s.type<<"\n";
	 	
 	}
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
      cout<<"\nError opening the product record!"; 
      exit(0);
  }

  cout<<"\nEnter the pid of the product to be modified: ";
  cin>>pid;

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
          cout<<"\nThe old values of the record with pid "<<pid<<" are ";
          cout<<"\nPID    = "<<s1[j].pid;
          cout<<"\nName   = "<<s1[j].name;
          cout<<"\nCost   = "<<s1[j].cost;
          cout<<"\nStock  = "<<s1[j].stock;
          cout<<"\nType   = "<<s1[j].type;

          cout<<"\nEnter the new values (The PID can't be changed)\n";
          cout<<"\nName   = ";  cin>>s1[j].name;
          cout<<"\nCost   = ";  cin>>s1[j].cost;
          cout<<"\nStock  = ";  cin>>s1[j].stock;
          cout<<"\nType   = ";  cin>>s1[j].type;
          break;
      }//end of if
  }//end of for

    if(j==I)
    {
        cout<<"\nThe product with pid "<<pid<<" is not present"; 
        return;
    }

    file2.close();

    fstream out1;
    out1.open("product_record.dat",ios::out);
    if(!out1)
    {
          cout<<"\nError opening the product record!"; 
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

	for(;;)
	{
		cout<<"\n1. Add a product";
		cout<<"\n2. Search a product";
		cout<<"\n3. Delete a product";
		cout<<"\n4. Display all products";
        cout<<"\n5. Modify a product info";
        cout<<"\n0. Exit";
		cout<<"\nPlease enter your choice: ";
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
			default:cout<<"\nInvalid choice!";
					exit(0);	
		}
	}
}