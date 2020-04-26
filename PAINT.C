#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
struct color
{
int col;
}block;
int show();
void save();
void BEEP();
int savedindex(int);
void nextindex();
int getindex();
union REGS in,out;
int main()
{   int gd=DETECT ,gm,x,y,press=0,conti;
    clrscr();
     initgraph(&gd,&gm,"c:\\TURBOC3\\BGI");
     outtextxy(120,1,"press any key to exit");
     setfillstyle(SOLID_FILL,15);
     rectangle(50,10,590,475);
      floodfill(200,300,15);
     rectangle(590,10,639,475);
     rectangle(590,30,639,60);   //pen
     rectangle(590,60,639,90);   //erase
     rectangle(590,90,639,110);  //shape
     rectangle(590,110,615,130); //square
     rectangle(615,110,639,130); // circle
     rectangle(590,400,639,430); //save
     rectangle(590,430,639,460); //view
					  //inside the box
     outtextxy(593,95,"shapes");
     outtextxy(593,415,"save");
     outtextxy(593,445,"view");
     outtextxy(592,40," pen");
     outtextxy(591,70,"erease");
     rectangle(598,115,607,125);
     circle(627,120,6);
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
	 { press=1;                         //pen
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
     else if(x>=590&&y>110&&y<130&&x<=615&&out.x.bx==1)          //square
       {  BEEP();                                     //590,110,615,130
       //	  rectangle();
       }
      else if(x>=616&&y>110&&y<130&&out.x.bx==1) //circle
      { BEEP();
      //	circle();
      }

				 //main clicking of case
      if(press==1)
    {    setcolor(0);
       if(out.x.bx==1&&x<589&&x>2)
	outtextxy(x,y,".");
       }
       else if(press==2)
     { // in.x.ax=2;
       //	int86(0x33,&in,&out);
      // { rectangle(x-1,y-1,x+1,y+1); }
      setcolor(15);
	settextstyle(1,0,4);
      if(out.x.bx==1&&x<589&&x>2)
       {
	 outtextxy(x,y,"*");
	}
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
 void save()
 {  int i,j;
    char filename[20];
      FILE *fp;
    gets(filename);
    // a= getindex();
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
  int i,j;
  char savedfile[20];
    FILE *fp;
  gets(savedfile);
   ;
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
 /*int getindex()
{ int a;
     FILE *index;
     index = fopen("index.txt","r");
     fscanf(index,"%d",&a);
     fclose(index);
 return a;
} * /
/* void nextindex()
 {
    int a;
    FILE *index;
    a = getindex();
     index = fopen("index.txt","w");
     fprintf(index,"%d",(a+1));
     fclose(index);
} */
/*int savedindex(int n)
{  int i,a;
// char ch[5];
// setcolor(0);
  // setfillstyle(SOLID_FILL,0);
// rectangle(290,225,350,275);
// floodfill(295,350,7);
 // settextstyle(1,0,0);
 // outtextxy(292,224,"select the file number to view");
 // for(i=0;i<=n;i++)
 // {   itoa(n,ch,5);
  // outtextxy(292+i,224+i,ch);
//  }
    scanf("%d",&a);
  return a;
} */