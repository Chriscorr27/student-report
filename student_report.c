 #include<stdio.h>
 #include<conio.h>
 #include<stdlib.h>
 #include<process.h>
 struct student{
     int roll_no;
     char name[50];
     int p_marks,c_marks,m_marks,e_marks,cs_marks;
     float perc;
     char grade;
 }st;
 FILE *fptr;
int student_exist(int n,int roll)
{
    FILE *fptr1;
    fptr1 = fopen("student_report.dat","rb");
    while((fread(&st,sizeof(st),1,fptr1))>0)       //to check whether student report is already created
    {
     if(st.roll_no==roll && st.roll_no!=n )
	{
        printf("\n\n  student already existing \n ");
	    return 0;
	}
    }
    return 1;
}
int write_student()    //create a student report
 {
     FILE *fptr1;
     int flag=0,n;
    clrscr();
    fptr = fopen("student_report.dat","ab");
    fptr1 = fopen("student_report.dat","rb");
    printf("\n  Please Enter The New Details of student \n");
    printf("\n  Enter The roll number of student : ");
    scanf("%d",&n);

    while((fread(&st,sizeof(st),1,fptr1))>0)       //to check whether student report is already created
    {
     if(st.roll_no==n)
	{
	 flag=1;
	}
    }
    if(flag==1)
    {
	printf("\n\n  student already existing \n ");
	getch();
	return 0;
    }
    st.roll_no = n;
    fflush(stdin);
    printf("\n\n  Enter The Name of student : ");
    gets(st.name);
    printf("\n  Enter The marks in physics out of 100 : ");
    scanf("%d",&st.p_marks);
    printf("\n  Enter The marks in chemistry out of 100 : ");
    scanf("%d",&st.c_marks);
    printf("\n  Enter The marks in maths out of 100 : ");
    scanf("%d",&st.m_marks);
    printf("\n  Enter The marks in english out of 100 : ");
    scanf("%d",&st.e_marks);
    printf("\n  Enter The marks in computer science out of 100 : ");
    scanf("%d",&st.cs_marks);
    st.perc = (st.p_marks+st.c_marks+st.m_marks+st.e_marks+st.cs_marks)/6.0;
    if(st.perc<40)
    {
        st.grade='F';
    }
    else if(st.perc<50)
    {
        st.grade='C';
    }
    else if(st.perc<60)
    {
        st.grade='B';
    }
    else
    {
        st.grade='A';
    }
    fwrite(&st,sizeof(st),1,fptr);
    fclose(fptr1);
    fclose(fptr);
    printf("\n\n  Student Record Has Been Created \n  ");
    getch();
    return 0;
 }
 void display_all()     //display all the report
 {
    clrscr();
    printf("\n\n\n\t\t  DISPLAY ALL RECORD !!!\n\n");
    fptr=fopen("student_report.dat","rb");
    while((fread(&st,sizeof(st),1,fptr))>0)
    {
      printf("\n  Roll Number of Student : %d",st.roll_no);
      printf("\n  Name of student : %s",st.name);
      printf("\n  Marks in Physics : %d",st.p_marks);
      printf("\n  Marks in Chemistry : %d",st.c_marks);
      printf("\n  Marks in Maths : %d",st.m_marks);
      printf("\n  Marks in English : %d",st.e_marks);
      printf("\n  Marks in Computer Science : %d",st.cs_marks);
      printf("\n  Percentage of student is  : %.2f",st.perc);
      printf("\n  Grade of student is : %c",st.grade);
      printf("\n\n=======================================\n  ");
      getch();
    }
    fclose(fptr);
    getch();
 }
 void modify_student()   //update student report
 {
    int n,found=0,roll;
    clrscr();
    printf("\n\n\t\t  To Modify\n ");
    printf("\n\n\t  Please Enter The roll number of student : ");
    scanf("%d",&n);
    fptr=fopen("student_report.dat","rb+");
    while((fread(&st,sizeof(st),1,fptr))>0 && found==0)
    {
    if(st.roll_no==n)
           {
            printf("\n  Roll number of student : %d",st.roll_no);
            printf("\n  Name of student : %s",st.name);
            printf("\n  Marks in Physics : %d",st.p_marks);
            printf("\n  Marks in Chemistry : %d",st.c_marks);
            printf("\n  Marks in Maths : %d",st.m_marks);
            printf("\n  Marks in English : %d",st.e_marks);
            printf("\n  Marks in Computer Science : %d",st.cs_marks);
            printf("\n  Percentage of student is  : %.2f",st.perc);
            printf("\n  Grade of student is : %c",st.grade);
            printf("\n  Please Enter The New Details of student \n");
            printf("\n  Enter The roll number of student : ");
	        scanf("%d",&roll);
            if(student_exist(n,roll))
            {
                st.roll_no = roll;
                fflush(stdin);
                printf("\n\n  Enter The Name of student : ");
                gets(st.name);
                printf("\n  Enter The marks in physics out of 100 : ");
                scanf("%d",&st.p_marks);
                printf("\n  Enter The marks in chemistry out of 100 : ");
                scanf("%d",&st.c_marks);
                printf("\n  Enter The marks in maths out of 100 : ");
                scanf("%d",&st.m_marks);
                printf("\n  Enter The marks in english out of 100 : ");
                scanf("%d",&st.e_marks);
                printf("\n  Enter The marks in computer science out of 100 : ");
                scanf("%d",&st.cs_marks);
                st.perc=(st.p_marks+st.c_marks+st.m_marks+st.e_marks+st.cs_marks)/5.0;
                if(st.perc>=60)
                st.grade='A';
                else if(st.perc>=50 && st.perc<60)
                st.grade='B';
                else if(st.perc>=33 && st.perc<50)
                st.grade='C';
                else
                st.grade='F';
                fseek(fptr,-(long)sizeof(st),1);
                fwrite(&st,sizeof(st),1,fptr);
                printf("\n\n\t   Record Updated...\n");
            }
            found=1;
           }
         }
    fclose(fptr);
    if(found==0)
    {
        printf("\n\n\t   Record Not Found\n ");
    }
    getch();
 }
 void delete_student()  //delete student
 {
    int n;
    FILE *fptr1;
    fptr=fopen("student_report.dat","rb");
    fptr1=fopen("temp.dat","wb");
    clrscr();
    printf("\n\n\n\t\t  Delete Record\n");
    printf("\n\n  Please Enter The roll number of student You Want To Delete : ");
    scanf("%d",&n);
    rewind(fptr) ;
    while((fread(&st,sizeof(st),1,fptr))>0)
    {
       if(st.roll_no!=n)
       {
         fwrite(&st,sizeof(st),1,fptr1);
       }
    }
    fclose(fptr);
    fclose(fptr1);
    remove("student_report.dat");
    rename("temp.dat","student_report.dat");
     printf("\n\n\t  Record Deleted ..");
    getch();
 }
 void display_sp(int n)   //report of single student
 {
 int flag = 0;
     fptr = fopen("student_report.dat","rb");

     clrscr();
    while((fread(&st,sizeof(st),1,fptr))>0)
    {
     if(st.roll_no==n)
        {
            clrscr();
	    printf("\n  Roll number of student : %d",st.roll_no);
            printf("\n  Name of student : %s",st.name);
            printf("\n  Marks in Physics : %d",st.p_marks);
            printf("\n  Marks in Chemistry : %d",st.c_marks);
            printf("\n  Marks in Maths : %d",st.m_marks);
            printf("\n  Marks in English : %d",st.e_marks);
            printf("\n  Marks in Computer Science : %d",st.cs_marks);
	    printf("\n  Percentage of student is  : %.2f",st.perc);
            printf("\n  Grade of student is : %c\n",st.grade);
            flag=1;
        }
    }
    fclose(fptr);
    if(flag==0)
    {
        printf("\n\n  record not exist\n");
    }
    getch();
 }
 void class_result()
 {
    clrscr();
    fptr = fopen("student_report.dat","rb");
    if(fptr==NULL)
    {
       printf("  ERROR!!! FILE COULD NOT BE OPEN\n\n\n  Go To Entry Menu to create File");
       printf("\n\n\n    Program is closing ....");
       getch();
       exit(0);
    }

    printf("\n\n\t\t  ALL STUDENTS RESULT \n\n");
    printf("  ==========================================================\n");
    printf("  R.No.  Name               P   C   M   E   CS  %age   Grade\n");
    printf("  ==========================================================\n");
    while((fread(&st,sizeof(st),1,fptr))>0)
     {
       printf("  %-6d %-18s %-3d %-3d %-3d %-3d %-3d %-3.2f    %-1c\n",st.roll_no,st.name,st.p_marks,st.c_marks,st.m_marks,st.e_marks,st.cs_marks,st.perc,st.grade);
     }
     fclose(fptr);
    getch();
 }

 int result()//result menu
   {
    int choice,rno;
    char ch;
    clrscr();
    printf("\n\n\n  RESULT MENU");
    printf("\n\n\n  1. Class Result\n\n  2. Student Report Card\n\n  3.Back to Main Menu");
    printf("\n\n\n  Enter Choice (1-3)?\n   ");
    scanf("%d",&choice);
    switch(choice)
    {
     case 1 : class_result();break;
     case 2 : {
        do{

        clrscr();
        printf("\n\n   Enter Roll Number Of Student : ");
        scanf("%d",&rno);
        display_sp(rno);
        printf("\n\n   Do you want to See More Result (y/n)?");
        fflush(stdin);
	scanf("%c",&ch);
	}while(ch=='y'||ch=='Y');
        break;
           }
     case 3: return 0 ;
     default:  printf("\a");
    }
    result();
    return 0;
 }
 
 
int entry_menu()   //entering report
{
    char ch2;
    int num;
   clrscr();
  printf("\n\n\n\tENTRY MENU");
  printf("\n\n\t1.CREATE STUDENT RECORD");
  printf("\n\n\t2.DISPLAY ALL STUDENTS RECORDS");
  printf("\n\n\t3.SEARCH STUDENT RECORD ");
  printf("\n\n\t4.MODIFY STUDENT RECORD");
  printf("\n\n\t5.DELETE STUDENT RECORD");
  printf("\n\n\t6.BACK TO MAIN MENU");
  printf("\n\n\tPlease Enter Your Choice (1-6) \n");
  ch2=getche();
  switch(ch2)
  {
    case '1': clrscr();
          write_student();
          
          break;
    case '2': display_all();break;
    case '3':  {
           
           clrscr();
           printf("\n\n\tPlease Enter The roll number ");
           scanf("%d",&num);
           display_sp(num);
           }
           break;
      case '4': modify_student();break;
      case '5': delete_student();break;
      case '6': return 0;
      default:printf("\a");entry_menu();
   }
   entry_menu();
   return 0;
}
 
 
 void mainmenu()       //MAIN MENU
 {
	char ch;
     do                        
    {
      clrscr();
      printf("\n\n\n\tMAIN MENU");
      printf("\n\n\t01. RESULT MENU");
      printf("\n\n\t02. ENTRY/EDIT MENU");
      printf("\n\n\t03. EXIT");
      printf("\n\n\tPlease Select Your Option (1-3)\n\t ");
       ch=getche();
      switch(ch)
      {
         case '1': clrscr();
               result();
               break;
          case '2': entry_menu();
                break;
          case '3':exit(0);
          default :printf("\a");
    }
    }while(ch!='3');
 }
 void intro()
{
 clrscr();
 gotoxy(35,11);
 printf("STUDENT");
 gotoxy(33,14);
 printf(" REPORT CARD");
 gotoxy(35,17);
 printf("PROJECT");
 printf("\n\n\n\n\n\n  MADE BY : CHRIS CORREIA");
 printf("\n\n  COLLEGE : DJ. SANGHVI COLLEGE OF ENGINEERING ");
 getch();
}
 void main()
 {
  clrscr();
    intro();                   //INTRODUCTION

    mainmenu();

 }
