#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<mysql.h>
#include<string.h>
#include <termios.h>
#include <unistd.h>
MYSQL *oo,*conn;
MYSQL_RES *read1=NULL;
MYSQL_RES *res=NULL;
MYSQL_ROW row=NULL;


int getch(void)
{
    struct termios oldt,newt;
    int   ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}


char* login(int id, char pwd[25])
{
	char stmt[1500];
	char qry[]={"select * from login_details where emp_id='%d'and password='%s'"};
	oo=mysql_init(NULL);
	mysql_real_connect(oo, "localhost", "root", "1234","payroll", 3306, NULL, 0);
	if(oo)
    {
    	
            int n=sprintf(stmt,qry,id,pwd);
            mysql_query(oo,stmt);
            read1=mysql_store_result(oo);
            row = mysql_fetch_row(read1);
            if(row==NULL)
            { 
                return "\nWrong username or password\n\n\n\n\n";
        	
	        }
	    else
	    {
	        if(strcmp("I",row[3])==0)
	        {
			
	         return "\nUser is deactivated\n\n\n\n\n\n";
	        }
	        else
	        {
	            printf("\nSuccessfully logged in \n\n\n\n\n\n\n\n\n");
	            return row[2];
			
		    }
	    }
	}
    else
    {
        printf("not connected");
        printf("%s\n", mysql_error(oo));
    }
}
int main(int argc, char *argv[]) 
{
	int i,id;
	char ch;
	char pwd[25];
	char user_type[25];
	system("clear");
     	printf("\n*********************************************************************\n");
	printf("                               Login                                   \n");
	printf("\n*********************************************************************\n");	

	printf("                Press 1 LOGIN\n");
	printf("                Press 2 EXIT\n");
	scanf("%d",&i);
	switch(i)
	{
		case 1:{
			   printf("\nEnter your employee id:");
        	           scanf("%d",&id);
        	           getchar();
	                   printf("\nEnter your Password:");
        	           int p=0; 
    		           do
			   { 
       		           pwd[p]=getch();
       			   if(pwd[p]=='\b'&& p>0)
       		 	   {
       			       p--;
       			       printf("\b \b");
       			       continue;
       			    }
			    if(pwd[p]!='\r')
			    { 
                                printf("*"); 
                            }
			    if(pwd[p]=='\n'||pwd[p]==13)
			    {
				p++;
				break;
			    } 
                           p++; 
                           }while(pwd[p-1]!='\r'||pwd[p-1]!=13); 
                           pwd[p-1]='\0'; 
        	           strcpy(user_type,login(id,pwd));
			   printf("%s\n",user_type);
			   break;
		       }
			
		case 2:{
			printf("EXIT\n");
			break;		
			}
					
		default:
			{
				printf("Wrong Input");
				break;
			}
	    }
	
	if(strcmp("admin",user_type)==0)
	{
        	printf("                Press 1 Employee management\n");
		printf("                Press 2 Leave management\n");
		printf("                Press 3 Attendance management\n");
		printf("                Press 4 Salary management\n");
        	printf("                Press 5 Department management\n");
		printf("                Press 6 Increment management\n");
		printf("                Press 7 Grievances redressal\n");
		scanf("%d",&i);
		    
		switch(i)
		{
			case 1:
			{   
			       	printf("                Press 1 Add Employee\n");
		               	printf("                Press 2 Modify Employee\n");
		                printf("                Press 3 Deactivate Employee\n");
		                printf("                Press 4 Display Employee\n");
		                break;
			}
			
			case 2:
			{   
				printf("                Press 1 View pending requests\n");
		                printf("                Press 2 Display leaves\n");
		                break;
			}
				
			case 3:
			{   
				printf("                Press 1 Display attendance\n");
		                printf("                Press 2 Update attendance\n");
		                break;
			}
				
			case 4:
			{   
				printf("                Press 1 Display salary\n");
		                printf("                Press 2 Update salary\n");
		                break;
			}
				
			case 5:
			{   
				printf("                Press 1 Add Employee\n");
			        break;
			}
		
			case 6:
			{    
				printf("                Press 1 Increment Salary\n");
			        break;
			}
			
			case 7:
			{   
				printf("                Press 1 Grievance redressal\n");
			        break;
			}
								
			default:
			{
				printf("Wrong Input");
				break;
			}
		}			    
	}
		
		else if(strcmp("employee",user_type)==0)
		{
			int i;
			printf("                Press 1 Personal details management\n");
		    	printf("                Press 2 Attendance management\n");
		    	printf("                Press 3 Leave management\n");
		    	printf("                Press 4 Salary management\n");
        		printf("                Press 5 Grievances redressal\n");
        		scanf("%d",&i);
        	
			switch(i)
			{
				case 1:
				{   
			        	printf("                Press 1 Display employee details \n");
		                	printf("                Press 2 Update employee details\n");
		                	printf("                Press 3 View employee feedback\n");
		                	printf("                Press 4 Change password\n");
		                	break;
				}
				    
				case 2:
				{   
			        	printf("                Press 1 Display attendance\n");
		                	printf("                Press 2 Request attendance change\n");
		                	break;
				}
				    
				case 3:{   
			            printf("                Press 1 Request leave\n");
		                printf("                Press 2 Display leaves\n");
		                break;
				    }
				
			    				
			    case 4:{   
			            printf("                Press 1 Display salary (Hourly)\n");
		                printf("                Press 2 Display salary (Regular)\n");
		                break;
				    }

			    case 5:{   
			            printf("                Press 1 Raise Grievance\n");
			            break;
				    }
								
			    default:{
					    printf("Wrong Input");
					    break;
				    }
		    }		
		}
		
		else if(strcmp("manager",user_type)==0){
			printf("                Press 1 Personal details management\n");
		    printf("                Press 2 Attendance management\n");
		    printf("                Press 3 Leave management\n");
		    printf("                Press 4 Salary management\n");
        	printf("                Press 5 Grievances redressal\n");
			printf("                Press 6 Department management\n");
			
			scanf("%d",&i);
		    
		    switch(i){
			    case 1:{   
			            printf("                Press 1 Display employee details \n");
		                printf("                Press 2 Update employee details\n");
		                printf("                Press 3 Change password\n");
		                break;
				    }
				    
				case 2:{   
			            printf("                Press 1 Display attendance\n");
		                printf("                Press 2 Request attendance change\n");
		                break;
				    }
				    
				case 3:{   
			            printf("                Press 1 Request leave\n");
		                printf("                Press 2 Display leaves\n");
		                break;
				    }
							
			    case 4:{   
			            printf("                Press 1 Display salary (Hourly)\n");
		                printf("                Press 2 Display salary (Regular)\n");
		                break;
				    }

			    case 5:{   
			            printf("                Press 1 Raise Grievance\n");
			            break;
				    }
				    
				case 6:{ 
						printf("                Press 1 Request Employee\n");
			            printf("                Press 2 Rate employee\n");
			            printf("                Press 3 Display employee rating \n");
						break;
				    }
			    default:{
					    printf("Wrong Input");
					    break;
				    }
		    }
		}
		
		else{
			printf("Have a Good Day!");
		}
	
return 0;
}
