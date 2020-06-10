#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<math.h>
struct color
{
int col;
}block;
struct pixel
{ int x,y,c;
 }pix;
struct savedfilename  // structure to save the name of all the paint files
{  char name[20];
}savedname[100];
void savecurrent();
void showcurrent(float );
int show();
void save();
void BEEP();
void rect();
void fillcolor(int );
void colorboxes();
void saveindex();
int getindex();
void layout();
void savename(char  *);
void rect(int );
void circ(int );
union REGS in,out;
int main()
{  int brushsize=2,brushcolour=0;
 float zoomin =1.1,zoomout=0.9;
 int gd=DETECT ,gm,x,y,press=0,conti;
    clrscr();
     initgraph(&gd,&gm,"c:\\TURBOC3\\BGI");
     layout();
    in.x.ax=1;
 int86(0x33,&in,&out);
   // settextstyle(1,0,2);
       while(!kbhit())         //infinity loop ends when any key is pressed
       { start:
	in.x.ax =3;
	 int86(0x33,&in,&out);
	  x= out.x.cx;
	  y= out.x.dx;
	  if(x>=590&&y>10&&y<30&&out.x.bx==1)    //clear for new page.
	  {  BEEP();
	  clearviewport();
	  layout();}
	else if(x>=590&&y>30&&y<60&&out.x.bx==1)         //output  from mouse
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
	 else if(x>590&&y>170&&y<190&&x<615&&out.x.bx==1)   //rectangle
	 {
	 BEEP();
	 rect(brushcolour);
	 }
	  else if(x>615&&y>170&&y<190&&x<639&&out.x.bx==1)   //circle
	 {
	 BEEP();
	 circ(brushcolour);
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
	 else if(x>=590&&y>190&&y<210&&out.x.bx==1)
	 {BEEP();
	     fillcolor(brushcolour);
	      }

if(x>=590&&y>210&&y<225&&x<615&&out.x.bx==1)
{brushcolour=0;
BEEP();
}
else if(x>=615&&y>210&&y<225&&x<639&&out.x.bx==1)
{brushcolour=1;
BEEP();
}
else if(x>=590&&y>225&&y<240&&x<615&&out.x.bx==1)
{brushcolour=2;
BEEP();
}
else if(x>=615&&y>225&&y<240&&x<639&&out.x.bx==1)
{brushcolour=3;
BEEP();
}
else if(x>=590&&y>240&&y<255&&x<615&&out.x.bx==1)
{brushcolour=4;
BEEP();
}
else if(x>=615&&y>240&&y<255&&x<639&&out.x.bx==1)
{brushcolour=5;
BEEP();
}
else if(x>=590&&y>255&&y<270&&x<615&&out.x.bx==1)
{brushcolour=6;
BEEP();
}
else if(x>=615&&y>255&&y<270&&x<639&&out.x.bx==1)
{brushcolour=7;
BEEP();
}
else if(x>=590&&y>270&&y<285&&x<615&&out.x.bx==1)
{brushcolour=8;
BEEP();
}
else if(x>=615&&y>270&&y<285&&x<639&&out.x.bx==1)
{brushcolour=9;
BEEP();
}
else if(x>=590&&y>285&&y<300&&x<615&&out.x.bx==1)
{brushcolour=10;
BEEP();
}
else if(x>=615&&y>285&&y<300&&x<639&&out.x.bx==1)
{brushcolour=11;
BEEP();
}
else if(x>=590&&y>300&&y<315&&x<615&&out.x.bx==1)
{brushcolour=12;
BEEP();
}
else if(x>=615&&y>300&&y<315&&x<639&&out.x.bx==1)
{brushcolour=13;
BEEP();
}
else if(x>=590&&y>315&&y<330&&x<615&&out.x.bx==1)
{brushcolour=14;
BEEP();
}
else if(x>=615&&y>315&&y<330&&x<639&&out.x.bx==1)
{brushcolour=15;
BEEP();
}
else if(x>=590&&y>330&&y<350&&x<639&&out.x.bx==1)
{BEEP();
savecurrent();
 clearviewport();
	  layout();
showcurrent(zoomin);
layout();
}
else if(x>=590&&y>350&&y<370&&x<639&&out.x.bx==1)
{BEEP();
 savecurrent();
  clearviewport();
	  layout();
  showcurrent(zoomout);
}
				 //main clicking of case
      if(press==1)
    {    setcolor(brushcolour);
	settextstyle(1,0,brushsize);
       if(out.x.bx==1&&x<585&&x>83)
	outtextxy(x,y,".");
       }
       else if(press==2)
     { // in.x.ax=2;
       //	int86(0x33,&in,&out);
      // { rectangle(x-1,y-1,x+1,y+1); }
      setcolor(15);
	settextstyle(1,0,brushsize);
      if(out.x.bx==1&&x<581&&x>83)
	 outtextxy(x,y,"*");
       }
       }
	getch();


       closegraph();

 return 0;
}
void layout() //shows all the outlines and the layout
{       setcolor(15);
       rectangle(79,9,590,475);
   setfillstyle(SOLID_FILL,15);    //for white board
    floodfill(200,300,15);        //for  white board
    settextstyle(0,0,1);
     outtextxy(120,1,"press any key to exit");
     rectangle(590,10,639,475);
     rectangle(590,30,639,60);   //pen
     rectangle(590,60,639,90);   //erase
     rectangle(590,150,639,170);  //shape
     rectangle(590,170,615,190); //square
     rectangle(615,170,639,190); // circle
     rectangle(590,400,639,430); //save
     rectangle(590,430,639,460); //view
     rectangle(590,90,639,110);  //brush - small
     rectangle(590,110,639,130); // brush - medium
     rectangle(590,130,639,150); // brush - large
     rectangle(590,190,639,210); // colour fill					  //inside the box
     outtextxy(593,155,"shapes");
     outtextxy(593,415,"save");
     outtextxy(593,445,"view");
     outtextxy(592,40," pen");
     outtextxy(592,20,"clear");
     outtextxy(591,70,"erease");
     outtextxy(591,192,"fill");
     outtextxy(590,200,"colour");
     outtextxy(590,332,"zoomin");
     outtextxy(590,352," zoom");
     outtextxy(590,362," out");
    rectangle(595,100,634,101);
    rectangle(595,120,634,121);
    rectangle(595,139,634,140);
     rectangle(595,119,634,121);
     rectangle(595,138,634,141);
     rectangle(598,175,607,185);
    rectangle(590,330,639,350);// zoomin
     rectangle(590,350,639,370);// zoomout
    circle(627,180,6);
    colorboxes();// produces the small boxes of colour
}
void savecurrent()
{   int i,j,c;
    FILE *fp;
	in.x.ax =2;
	 int86(0x33,&in,&out);
     fp=fopen("cur.txt","wb");
    for(i=10;i<475;i++)
   { for(j=80;j<590;j++)
      {
	c=getpixel(j,i);
	if(c!=15)
	{ pix.c=c;
	 pix.x=j;
	 pix.y = i;
	 fwrite(&pix,sizeof(struct pixel),1,fp);  //formate def-fwrite(address ofstruct variable,size of the structure,quantity,file pointer)
	 }                                       //store data in bin format..
   //  fprintf(fp,"%d ",block.col);
      }
    }
    fclose(fp);
	in.x.ax =1;
	 int86(0x33,&in,&out);
}
void showcurrent(float n)
 { 	FILE *fp;
	fp= fopen("cur.txt","rb");
	while(!feof(fp))
{
       fread(&pix,sizeof(struct pixel),1,fp);
	putpixel(pix.x*n,pix.y*n,pix.c);}
	fclose(fp);
	 }
     /*void showcurrent()
{ int i,j;
  FILE *fp;
  fp = fopen("cur.txt","r");
       for(i=10;i<475;i++)    //10  //475
   { for(j=80;j<590;j++)
     { fscanf(fp,"%d ",&block.col);

       putpixel(j,i,block.col);
   }
}
  fclose(fp);
}
*/
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
   { for(j=80;j<590;j++)
      {
	  block.col=getpixel(j,i);
     fprintf(fp,"%d ",block.col);
      }
    }
    fclose(fp);
  //  nextindex();
   BEEP();
   }
int show() //VIEW
{
  int r,q, i=85,j=50,check,l=0;
  char p[20],s[100];
  char savedfile[20];
  FILE *save;
  FILE *fp;

 // r= getindex();
BEEP();
  // layout();
   setfillstyle(SOLID_FILL,0);
      rectangle(79,9,590,475);
  floodfill(81,60,15);
   clearviewport();
      layout();
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
   } j=j+25;i=85;
     }
     fclose(save);
  gets(savedfile);
   fp = fopen(savedfile,"r");
    clearviewport();
      layout();
       for(i=10;i<475;i++)
   { for(j=80;j<590;j++)
     { fscanf(fp,"%d ",&block.col);
      if(block.col!=15)
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
void colorboxes()
{   int n=0;
   int i =0,y=210;
   for(i=0;i<8;i++)
   {
     rectangle(590,y,615,y+15);
     setcolor(15);
     setfillstyle(SOLID_FILL,n++);
     floodfill(592,y+2,15);
     rectangle(615,y,639,y+15);
     setfillstyle(SOLID_FILL,n++);
     floodfill(617,y+2,15);
     y +=15;
   }
}
 void fillcolor(int n)       // not working
 { int x,y, brushcolour=15 ;
  in.x.ax=3;
 int86(0x33,&in,&out);

   while(!kbhit())
   {   x=out.x.cx;
   y=out.x.cx;
if(x>=590&&y>210&&y<225&&x<615&&out.x.bx==1)
{brushcolour=0;
BEEP();
}
else if(x>=615&&y>210&&y<225&&x<639&&out.x.bx==1)
{brushcolour=1;
BEEP();
}
else if(x>=590&&y>225&&y<240&&x<615&&out.x.bx==1)
{brushcolour=2;
BEEP();
}
else if(x>=615&&y>225&&y<240&&x<639&&out.x.bx==1)
{brushcolour=3;
BEEP();
}
else if(x>=590&&y>240&&y<255&&x<615&&out.x.bx==1)
{brushcolour=4;
BEEP();
}
else if(x>=615&&y>240&&y<255&&x<639&&out.x.bx==1)
{brushcolour=5;
BEEP();
}
else if(x>=590&&y>255&&y<270&&x<615&&out.x.bx==1)
{brushcolour=6;
BEEP();
}
else if(x>=615&&y>255&&y<270&&x<639&&out.x.bx==1)
{brushcolour=7;
BEEP();
}
else if(x>=590&&y>270&&y<285&&x<615&&out.x.bx==1)
{brushcolour=8;
BEEP();
}
else if(x>=615&&y>270&&y<285&&x<639&&out.x.bx==1)
{brushcolour=9;
BEEP();
}
else if(x>=590&&y>285&&y<300&&x<615&&out.x.bx==1)
{brushcolour=10;
BEEP();
}
else if(x>=615&&y>285&&y<300&&x<639&&out.x.bx==1)
{brushcolour=11;
BEEP();
}
else if(x>=590&&y>300&&y<315&&x<615&&out.x.bx==1)
{brushcolour=12;
BEEP();
}
else if(x>=615&&y>300&&y<315&&x<639&&out.x.bx==1)
{brushcolour=13;
BEEP();
}
else if(x>=590&&y>315&&y<330&&x<615&&out.x.bx==1)
{brushcolour=14;
BEEP();
}
else if(x>=615&&y>315&&y<330&&x<639&&out.x.bx==1)
{brushcolour=15;
BEEP();
}
      setcolor(0);
      if(out.x.bx==2)
      {  setfillstyle(SOLID_FILL,brushcolour);
	  floodfill(out.x.cx,out.x.dx,0);

     }
   }

 }
 void rect(int n) //rectangle
 { int x=1,y=1,x1,y1,x2,y2;
     savecurrent();
  while(1)
    {
	in.x.ax =3;
	 int86(0x33,&in,&out);
      if(out.x.bx==1&&x==1)
	 { x1=out.x.cx;
	   y1=out.x.dx;
	   x=0;
	    in.x.ax=2;
 int86(0x33,&in,&out);
	 }
       if(out.x.bx==1&&x==0)
       {    in.x.ax=3;
	int86(0x33,&in,&out);
	  x2=out.x.cx;
	  y2=out.x.dx;
	 // delay(60);
	  clearviewport();//clear the whole screen and sets the mouse pointer to 0,0
	  layout();
	  showcurrent(1);

	  setcolor(n);
	 rectangle(x1,y1,x2,y2);
	 delay(80);
	in.x.ax=3;
	int86(0x33,&in,&out);
	if(out.x.bx==0)
	{ x=1;
	  in.x.ax=1;
	  int86(0x33,&in,&out);
	}
       }
    if(out.x.bx==4&&x==1)
      break;
     }

    }
  void circ(int n)//for circle
  {    int x=1,y=1,x1,y1,x2,y2,r,A,B;
     savecurrent();
  while(1)
    {
	in.x.ax =3;
	 int86(0x33,&in,&out);
      if(out.x.bx==1&&x==1)
	 { x1=out.x.cx;
	   y1=out.x.dx;
	   x=0;
	    in.x.ax=2;
 int86(0x33,&in,&out);
	 }
       if(out.x.bx==1&&x==0)
       {    in.x.ax=3;
	int86(0x33,&in,&out);
	  x2=out.x.cx;
	  y2=out.x.dx;
	 // delay(60);
	  clearviewport();//clear the whole screen and sets the mouse pointer to 0,0
	  layout();
	  showcurrent(1);
	  setcolor(n);
	  A = (x2-x1)/2;
	  A = A>=0?A:-A;
	  B = (y2-y1)/2;
	  B = B>=0?B:-B;
	   ellipse((x1+x2)/2,(y1+y2)/2,0,360,A,B);
	 delay(80);
	in.x.ax=3;
	int86(0x33,&in,&out);
	if(out.x.bx==0)
	{ x=1;
	  in.x.ax=1;
	  int86(0x33,&in,&out);
	}
       }
    if(out.x.bx==4&&x==1)
      break;

  if(out.x.bx==2)
  { r=1;
  }
  while(r==1)
  {circle(out.x.cx,out.x.dx,50);}
  if(out.x.bx==4)
  r=0;
  }
   }
