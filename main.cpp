#include <graphics.h>
#include <fstream>

using namespace std;

void menu_pac()
{
    setbkcolor(BLUE);
    cleardevice();
    settextstyle(6,HORIZ_DIR,5);
    outtextxy(100,100,"PACMAN");
    settextstyle(6,HORIZ_DIR,2);
    outtextxy(100,150,"Vigyazz a csapdakra!!");
    settextstyle(6,HORIZ_DIR,3);
    outtextxy(100,200,"START (I)");
    outtextxy(100,250,"KILEPES (K)");
    settextstyle(6,HORIZ_DIR,1);
    outtextxy(100,400,"*A jatek lenyege hogy felszedd az osszes pottyot");
}
void halal()
{
    setbkcolor(BLUE);
    cleardevice();
    settextstyle(6,HORIZ_DIR,5);
    outtextxy(100,100,"MEGHALTAL!!!");
    settextstyle(6,HORIZ_DIR,2);
    outtextxy(100,200,"KILEPES(2X K)");
}
void vege()
{
    setbkcolor(BLUE);
    cleardevice();
    settextstyle(6,HORIZ_DIR,5);
    outtextxy(100,100,"GRATULALOK");
    settextstyle(6,HORIZ_DIR,3);
    outtextxy(100,200,"Sikerult az osszes pottyot felvenned");
    settextstyle(6,HORIZ_DIR,3);
    outtextxy(100,300,"KILEPES (K)");
}

// beolvassuk a labirintust az a matrixba
void beolvas(int a[][30],int &n,int &m)
{
    ifstream f("be.txt");
    f>>n>>m;
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            {
                f>>a[i][j];
            }
    f.close();
}
//sajtot rajzol
void pont(int x,int y,int h)
{
    setcolor(YELLOW);
    circle(x+2*h/3.5,y+h/2,h/10);
    setfillstyle(1,YELLOW);
    floodfill(x+2*h/3.5,y+h/2,YELLOW);
}

//kirajzolja a labirintust
void kirajzol(int a[][30],int n,int m,int h)
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
        {   setbkcolor(BLUE);
            if (a[i][j]==2) pont(j*h,i*h,h);
            else {
            if (a[i][j]==0) setfillstyle(8,BLUE);
            if (a[i][j]==3 || a[i][j]==4) setfillstyle(1,BLACK);
            if (a[i][j]==5) setfillstyle(4,RED);
            bar(j*h,i*h,(j+1)*h,(i+1)*h);
            }
        }
}

//emberket rajzol
void ember(int x,int y,int h)
{
    arc(x+h/2,y+h/2,0,270,h/3);
    line(x+h/2,y+h/2,x+h/2+h/3,y+h/2);
    line(x+h/2,y+h/2,x+h/2,y+h/2+h/3);
    circle(x+2*h/3,y+h/3,h/10);
}
//setal a labirintusban az emberke
void setal(int a[][30],int n,int m,int x,int y,int h,int &g)
{
    bool kilep=false;
    int i=0,j=0,db=0;
    while(!kilep)
    {
        if (a[i][j]==3) setcolor(BLACK);
                    else setcolor(BLACK);
        ember(x,y,h);
        if(GetAsyncKeyState( 'K' )) kilep=true;
        if(GetAsyncKeyState( VK_UP ) && i>0 && a[i-1][j]>0) { y=y-h; i--; }
        if(GetAsyncKeyState(VK_DOWN) && i<n-1 && a[i+1][j]>0) { y=y+h; i++; }
        if(GetAsyncKeyState(VK_RIGHT)&& j<m-1 && a[i][j+1]>0) { x=x+h; j++; }
        if(GetAsyncKeyState(VK_LEFT) && i>0 && a[i][j-1]>0) { x=x-h; j--; }
        setcolor(YELLOW);ember(x,y,h);setfillstyle(1,YELLOW);floodfill(x+h/3,y+h/2,YELLOW); Sleep(100);
        setfillstyle(1,BLACK);floodfill(x+h/3,y+h/2,BLACK);
        if(a[i][j]==5)
        {
            g=1;
            halal();
            Sleep(100);}
        if (a[i][j]==2){
         db++;
         a[i][j]=10;
         setfillstyle(1,BLACK);
         floodfill(x+2*h/3.5,y+h/2,BLACK);
         floodfill(x+h/3,y+h/2,BLACK);
                 }
        else{
         if(db==71)
         {
            setfillstyle(1,BLACK);
            bar(j*h,i*h,(j+1)*h,(i+1)*h);
            setfillstyle(1,GREEN);
            bar((m-1)*h,(n-1)*h,m*h,n*h);
            }
            if (i==n-1 && j==m-1&& db==71)
            kilep=true;
        }
    }
}
using namespace std;
int main() {
  int gdriver = DETECT, gmode;
  initgraph(&gdriver, &gmode, "");
  int n,m,a[30][30],d=0,g=0;
  bool ki=false, indul=false;
      do
  {
      if(d<1 && g!=1){
      menu_pac();
      Sleep(50);
      }
      else
      if(g!=1 && d==1)
      {
        vege();
        Sleep(50);
      }
      else
      if(g==1)
      {
          halal();
          Sleep(100);
      }
    if(GetAsyncKeyState( 'K' )) ki=true;
    if(GetAsyncKeyState( 'I' )) indul=true;
    if (indul)
    {
        setbkcolor(BLACK);
        cleardevice();
        while(d<1){
            beolvas(a,n,m);
            kirajzol(a,n,m,40);
            setal(a,n,m,0,0,40,g);
            d++;
           }
    }
    else{
    menu_pac();
    Sleep(50);
    }
  } while (ki==false);
  getch();
  return 0;
}
