#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
struct color
{
int col;
}block;
struct savedfilename    // structure to save the name of all the paint files
{  char name[20];
}savedname[100];

int show();
void save();
void BEEP();
void saveindex();
int getindex();
void savename(char  *);
union REGS in,out;
int main()
{  int brushsize=2;
 int gd=DETECT ,gm,x,y,press=0,conti;
    clrscr();
     initgraph(&gd,&gm,"c:\\TURBOC3\\BGI");
     outtextxy(120,1,"press any key to exit");
     setfillstyle(SOLID_FILL,15);
     rectangle(50,10,590,475);
      floodfill(200,300,15);
     rectangle(590,10,639,475);
     rectangle(590,30,639,60);   //pen
     rectangle(590,60,639,90);   //erase
     rectangle(590,150,639,170);  //shape
     rectangle(590,170,615,190); //square
     rectangle(615,170,639,190); // circle
     rectangle(590,400,639,430); //save
     rectangle(590,430,639,460); //view
     rectangle(590,90,639,110);  //brush - small
     rectangle(590,110,639,130);  // brush - medium
     rectangle(590,130,639,150); // brush - large					  //inside the box
     outtextxy(593,155,"shapes");
     outtextxy(593,415,"save");
     outtextxy(593,445,"view");
     outtextxy(592,40," pen");
     outtextxy(591,70,"erease");
     rectangle(595,100,634,101);
     rectangle(595,120,634,121);
     rectangle(595,139,634,140);
     rectangle(595,119,634,121);
     rectangle(595,138,634,141);
     rectangle(598,175,607,185);
     circle(627,180,6);
    in.x.ax=1;
 int86(0x33,&in,&out);
    settextstyle(1,0,2);
       while(!kbhit())         //infinity loop  with key press break
       { start:
	in.x.ax =3;
	 int86(0x33,&in,&out);
	  x= out.x.cx;
	  y= out.x.dx;
	if(x>=590&&y>30&&y<60&&out.x.bx==1)         //output  from mouse
	 { press=1;
				  //pen
	 BEEP();
	  }
	 else if(x>=590&&y>60&&y<90&&out.x.bx==1)
	{  press=2;                              //eraser
	BEEP();
	    }
	else if(x>=590&&y>400&&y<430&&out.x.bx==1)
	{ BEEP();                                        //save
	  save();

	 }

      else if(x>=590&&y>430&&y<460&&out.x.bx==1)
	{ BEEP();                                        //show or view
	 conti= show();
	 if(conti ==1);
	 goto start;
	}
     else if(x>=590&&y>90&&y<110&&out.x.bx==1)
       {  BEEP();
	 brushsize=2;
       }
      else if(x>=590&&y>110&&y<130&&out.x.bx==1)
      { BEEP();
       brushsize=4;
      }
	else if(x>=590&&y>130&&y<150&&out.x.bx==1)
      { BEEP();
       brushsize=7;
      }

				 //main clicking of case
      if(press==1)
    {    setcolor(0);
	settextstyle(1,0,brushsize);
       if(out.x.bx==1&&x<585&&x>50)
	outtextxy(x,y,".");
       }
       else if(press==2)
     { // in.x.ax=2;
       //	int86(0x33,&in,&out);
      // { rectangle(x-1,y-1,x+1,y+1); }
      setcolor(15);
	settextstyle(1,0,brushsize);
      if(out.x.bx==1&&x<581&&x>50)
	 outtextxy(x,y,"*");
       }
       }
	getch();


       closegraph();

 return 0;
}
void BEEP()
{sound(550);
 delay(100);
 nosound();
 }
 void save()   //saving the file
 {  int i,j;
    char filename[20];
      FILE *fp;
       saveindex();
    gets(filename);
     savename( filename );   //save the name of the txt in a file
      fp=fopen(filename,"w");
    for(i=10;i<475;i++)
   { for(j=50;j<590;j++)
      { // block.x2=j;
	//  block.y2 = i;
	  block.col=getpixel(j,i);
     fprintf(fp,"%d ",block.col);
      }
    }
    fclose(fp);
  //  nextindex();
   BEEP();
   }
int show()
{
  int r,q, i=60,j=50,check,l=0;
  char p[20],s[100];
  char savedfile[20];
  FILE *save;
  FILE *fp;
 // r= getindex();
BEEP();
     setcolor(15);
   setfillstyle(SOLID_FILL,15);
  floodfill(450,450,15);
    save = fopen("savedname.txt","r");
       setcolor(4);
    settextstyle(1,0,2);
    fseek(0,0,0);
  while(!feof(save))	//feof() returns will return 0 if file pointer is at end of file else it will rteturn zero
  { for(q=0;q<4;q++)                     //while(0) terminates the loop as zero is false.. so not operator(!) turns 0 ->1
  {       //drawing box around the the name of the saved files
      fscanf(save,"%s",&s) ;
      if(!feof(save))
   { outtextxy(i,j,s);
  rectangle(i-4,j,i+95,j+22);
  i= i +100;}
   } j=j+25;i=60;
     }
     fclose(save);
  gets(savedfile);
   fp = fopen(savedfile,"r");
       for(i=10;i<475;i++)
   { for(j=50;j<590;j++)
     { fscanf(fp,"%d ",&block.col);
       putpixel(j,i,block.col);
     }
}
  fclose(fp);
  BEEP();
   getch();
  return 1;
}
void savename(char *p)     //called each time with func save() to save the name file name in file
{  FILE *save;
  save = fopen("savedname.txt","a");    //appends the name of the new files
  fprintf(save,"%s ",p);       //coders- in file the words are stored as char so they pointers stops ehen an space is encountered
  fclose(save);
}
void saveindex()
{  int n;
  FILE *next;
    next = fopen("gettingindex.txt","w");
   n =  getindex();
   fprintf(next,"%d",n+1);
    fclose(next);
}
int getindex()
{   int n;
   FILE *current;
   current = fopen("gettingindex.txt","r");
     fscanf(current,"%d",n);
     fclose(current);
     return n;
}
