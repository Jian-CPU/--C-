/* Note:Your choice is C IDE */
#include "stdio.h"
#include <windows.h>
#include <conio.h>
#include <time.h>
//???????
#define FrameX 4   //?????????????X??????
#define FrameY 4   //?????????????Y??????
#define Frame_height  20 //??????????
#define Frame_width   18 //???????????
//??????????
int i,j,temp,temp1,temp2; //temp,temp1,temp2??????????????????????
int a[80][80]={0};   //?????????????????2,1,0????????��????????????�?????;???????????
int b[4];     //????4??"??"???�1????��??�0????????
  
//??????????????????
struct Tetris
{
 int x;     //?????????x??????
 int y;     //?????????y??????
 int flag;    //????????????????
 int next;    //???????????????????????
 int speed;    //?????????????????
 int count;    //??????????????????
 int score;    //????????
 int level;    //???????
};
//???????????
//??????????��??
void gotoxy(HANDLE hOut, int x, int y);
//???????????
void make_frame();
//?????????????????????
void get_flag(struct Tetris *);
//?????????????
void make_tetris(struct Tetris *);
//????????????
void print_tetris(HANDLE hOut,struct Tetris *);
//?????????????????
void clear_tetris(HANDLE hOut,struct Tetris *);
//?��?????????????????1?????????????????
int if_moveable(struct Tetris *);
//?��???????��?????????��?????????
void del_full(HANDLE hOut,struct Tetris *);
//??????
void start_game();

int main()
{ 
 //???????????
 make_frame();      
 //??????
 start_game();
}
/******??????????��??**************************************************************/
void gotoxy(HANDLE hOut, int x, int y)
{
 COORD pos;
 pos.X = x;  //??????
 pos.Y = y;  //??????
 SetConsoleCursorPosition(hOut, pos);
}
/******???????????******************************************************************/
void make_frame()
{
 HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  //?????????????????
 gotoxy(hOut,FrameX+Frame_width-5,FrameY-2);   //??????????
 printf("?????????");
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+7);  //?????????
 printf("**********????????�");
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+13);
 printf("**********");
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+17);
 printf("??????????");
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+19);
 printf("???????????");
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+15);
 printf("Esc ????????");
 gotoxy(hOut,FrameX,FrameY);       //?????????????????????
 printf("*");
 gotoxy(hOut,FrameX+2*Frame_width-2,FrameY);
 printf("*");
 gotoxy(hOut,FrameX,FrameY+Frame_height);
 printf("*");
 gotoxy(hOut,FrameX+2*Frame_width-2,FrameY+Frame_height);
 printf("*");
 a[FrameX][FrameY+Frame_height]=2;     
 a[FrameX+2*Frame_width-2][FrameY+Frame_height]=2;
 for(i=2;i<2*Frame_width-2;i+=2)
 {
  gotoxy(hOut,FrameX+i,FrameY);
  printf("*");         //????????
 }
 for(i=2;i<2*Frame_width-2;i+=2)
 {
  gotoxy(hOut,FrameX+i,FrameY+Frame_height);
  printf("*");         //????o???
  a[FrameX+i][FrameY+Frame_height]=2;    //????o????????
 }
 for(i=1;i<Frame_height;i++)
 {
  gotoxy(hOut,FrameX,FrameY+i); 
  printf("*");         //?????????
  a[FrameX][FrameY+i]=2;       //??????????????
 }
 for(i=1;i<Frame_height;i++)
 {
  gotoxy(hOut,FrameX+2*Frame_width-2,FrameY+i); 
  printf("*");         //?????????
  a[FrameX+2*Frame_width-2][FrameY+i]=2;   //??????????????
 }
}
/******?????????????********************************************************************/
void make_tetris(struct Tetris *tetris)
{
 a[tetris->x][tetris->y]=b[0];    //???????��????????:1-??,0-??
 switch(tetris->flag)      //??6????19??????
 {
  case 1:         //???????
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x+2][tetris->y-1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 2:         //??????:----
   {  
    a[tetris->x-2][tetris->y]=b[1];
    a[tetris->x+2][tetris->y]=b[2];
    a[tetris->x+4][tetris->y]=b[3];
    break;
   }
  case 3:         //??????: |
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x][tetris->y-2]=b[2];
    a[tetris->x][tetris->y+1]=b[3];
    break;
   }
  case 4:         //T?????
   {  
    a[tetris->x-2][tetris->y]=b[1];
    a[tetris->x+2][tetris->y]=b[2];
    a[tetris->x][tetris->y+1]=b[3];
    break;
   }
  case 5:         //T???????90?????
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x][tetris->y+1]=b[2];
    a[tetris->x-2][tetris->y]=b[3];
    break;
   }
  case 6:         //T???????180?????
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x-2][tetris->y]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 7:         //T???????270?????
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x][tetris->y+1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 8:         //Z?????
   {  
    a[tetris->x][tetris->y+1]=b[1];
    a[tetris->x-2][tetris->y]=b[2];
    a[tetris->x+2][tetris->y+1]=b[3];
    break;
   }
  case 9:         //Z???????90?????
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x-2][tetris->y]=b[2];
    a[tetris->x-2][tetris->y+1]=b[3];
    break;
   }
  case 10:        //Z???????180?????
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x-2][tetris->y-1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 11:        //Z???????270?????
   {  
    a[tetris->x][tetris->y+1]=b[1];
    a[tetris->x+2][tetris->y-1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 12:        //7?????
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x][tetris->y+1]=b[2];
    a[tetris->x-2][tetris->y-1]=b[3];
    break;
   }
  case 13:        //7???????90?????
   {  
    a[tetris->x-2][tetris->y]=b[1];
    a[tetris->x-2][tetris->y+1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 14:        //7???????180?????
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x][tetris->y+1]=b[2];
    a[tetris->x+2][tetris->y+1]=b[3];
    break;
   }
  case 15:        //7???????270?????
   {
    a[tetris->x-2][tetris->y]=b[1];
    a[tetris->x+2][tetris->y-1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 16:        //??7?????
   { 
    a[tetris->x][tetris->y+1]=b[1];
    a[tetris->x][tetris->y-1]=b[2];
    a[tetris->x+2][tetris->y-1]=b[3];
    break;
   }
  case 17:        //??7???????90?????
   { 
    a[tetris->x-2][tetris->y]=b[1];
    a[tetris->x-2][tetris->y-1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 18:        //??7???????180?????
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x][tetris->y+1]=b[2];
    a[tetris->x-2][tetris->y+1]=b[3];
    break;
   }
  case 19:        //??7???????270?????
   {  
    a[tetris->x-2][tetris->y]=b[1];
    a[tetris->x+2][tetris->y+1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
 } 
}

int if_moveable(struct Tetris *tetris)
{
 if(a[tetris->x][tetris->y]!=0)//?????????��??????????????????0???????????
 {
  return 0;
 }
 else
 {
  if( //????????????????????��????????"??"?????��??????????????????1?????????
   ( tetris->flag==1  && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x+2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
   //???????????????????��????????"??"?????��??????????????????1?????????
   ( tetris->flag==2  && ( a[tetris->x-2][tetris->y]==0   && 
    a[tetris->x+2][tetris->y]==0 && a[tetris->x+4][tetris->y]==0 ) )   ||
   ( tetris->flag==3  && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x][tetris->y-2]==0 && a[tetris->x][tetris->y+1]==0 ) )   ||
   ( tetris->flag==4  && ( a[tetris->x-2][tetris->y]==0   &&
    a[tetris->x+2][tetris->y]==0 && a[tetris->x][tetris->y+1]==0 ) )   ||
   ( tetris->flag==5  && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x][tetris->y+1]==0 && a[tetris->x-2][tetris->y]==0 ) )   ||
   ( tetris->flag==6  && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x-2][tetris->y]==0 && a[tetris->x+2][tetris->y]==0 ) )   ||
   ( tetris->flag==7  && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x][tetris->y+1]==0 && a[tetris->x+2][tetris->y]==0 ) )   ||
   ( tetris->flag==8  && ( a[tetris->x][tetris->y+1]==0   &&
    a[tetris->x-2][tetris->y]==0 && a[tetris->x+2][tetris->y+1]==0 ) ) ||
   ( tetris->flag==9  && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x-2][tetris->y]==0 && a[tetris->x-2][tetris->y+1]==0 ) ) ||
   ( tetris->flag==10 && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x-2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
   ( tetris->flag==11 && ( a[tetris->x][tetris->y+1]==0   &&
    a[tetris->x+2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
   ( tetris->flag==12 && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x][tetris->y+1]==0 && a[tetris->x-2][tetris->y-1]==0 ) ) ||
   ( tetris->flag==13 && ( a[tetris->x-2][tetris->y]==0   &&
    a[tetris->x-2][tetris->y+1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
   ( tetris->flag==14 && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x][tetris->y+1]==0 && a[tetris->x+2][tetris->y+1]==0 ) ) ||
   ( tetris->flag==15 && ( a[tetris->x-2][tetris->y]==0   &&
    a[tetris->x+2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
   ( tetris->flag==16 && ( a[tetris->x][tetris->y+1]==0   &&
    a[tetris->x][tetris->y-1]==0 && a[tetris->x+2][tetris->y-1]==0 ) ) ||
   ( tetris->flag==17 && ( a[tetris->x-2][tetris->y]==0   &&
    a[tetris->x-2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
   ( tetris->flag==18 && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x][tetris->y+1]==0 && a[tetris->x-2][tetris->y+1]==0 ) ) ||
   ( tetris->flag==19 && ( a[tetris->x-2][tetris->y]==0   &&
    a[tetris->x+2][tetris->y+1]==0 && a[tetris->x+2][tetris->y]==0 ) ) )
   {
    return 1;
   }
 }
 return 0;
}
/******??????????????????????????**********************************************************/
void get_flag(struct Tetris *tetris)
{
 tetris->count++;     //????????????????
 srand((unsigned)time(NULL));  //???????????
 if(tetris->count==1)
 {
  tetris->flag = rand()%19+1;  //??????????????????
 }
 tetris->next = rand()%19+1;   //??????????????????
}
/******????????????**********************************************************************/
void print_tetris(HANDLE hOut,struct Tetris *tetris)
{
 for(i=0;i<4;i++)
 {
  b[i]=1;         //????b[4]?????????????1
 }
 make_tetris(tetris);      //?????????????
 for( i=tetris->x-2; i<=tetris->x+4; i+=2 )
 {
  for(j=tetris->y-2;j<=tetris->y+1;j++)
  {
   if( a[i][j]==1 && j>FrameY )
   {
    gotoxy(hOut,i,j);
    printf("??");     //????????????
   }
  }
 }
 //?????????
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+1);
 printf("level : %d",tetris->level);
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+3);
 printf("score : %d",tetris->score);
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+5);
 printf("speed : %dms",tetris->speed);
}
/******?????????????????****************************************************************/
void clear_tetris(HANDLE hOut,struct Tetris *tetris)
{
 for(i=0;i<4;i++)
 {
  b[i]=0;         //????b[4]?????????????0
 }
 make_tetris(tetris);      //?????????????
 for( i=tetris->x-2; i<=tetris->x+4; i+=2 )
 {
  for(j=tetris->y-2;j<=tetris->y+1;j++)
  {
   if( a[i][j]==0 && j>FrameY )
   {
    gotoxy(hOut,i,j);
    printf("  ");     //????????
   }
  }
 }
}
/******?��???????��???????��?????????****************************************************/
void del_full(HANDLE hOut,struct Tetris *tetris)
{       //???????Frame_width-2???????????????
 int k,del_count=0;  //???????????��????????????????????????????
 for(j=FrameY+Frame_height-1;j>=FrameY+1;j--)
 {
  k=0;
  for(i=FrameX+2;i<FrameX+2*Frame_width-2;i+=2)
  {  
   if(a[i][j]==1) //?????????��???????????????????????????��????????
   {
    k++;  //??????��????????
    if(k==Frame_width-2)
    {
     for(k=FrameX+2;k<FrameX+2*Frame_width-2;k+=2)
     {  //??????��????
      a[k][j]=0;
      gotoxy(hOut,k,j);
      printf("  ");
      Sleep(1);
     }
     for(k=j-1;k>FrameY;k--)
     {  //??????????????��???��??�????????????????????????��??
      for(i=FrameX+2;i<FrameX+2*Frame_width-2;i+=2)
      {
       if(a[i][k]==1)
       {
        a[i][k]=0;
        gotoxy(hOut,i,k);
        printf("  ");
        a[i][k+1]=1;
        gotoxy(hOut,i,k+1);
        printf("??");
       }
      }
     }
     j++;   //????????????????��?????????????
     del_count++; //????????????????
    }
   }
  }
 }
 tetris->score+=100*del_count; //??????��???100??
 if( del_count>0 && ( tetris->score%1000==0 || tetris->score/1000>tetris->level-1 ) )
 {        //??????1000?????????10?��??????20ms???????
  tetris->speed-=20;
  tetris->level++;
 }
}
/******??????******************************************************************************/
void start_game()
{
 HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  //?????????????????
 struct Tetris t,*tetris=&t;       //????????????????????????
 unsigned char ch;         //????????????????????
 tetris->count=0;      //?????????????????0??
 tetris->speed=300;      //??????????300ms
 tetris->score=0;      //????????????0??
 tetris->level=1;      //?????????1??
 while(1)
 {//??????????�??????????
  get_flag(tetris);     //?????????????????????????
  temp=tetris->flag;     //???????????????????
  //??????????????????????(??????)
  tetris->x=FrameX+2*Frame_width+6;
  tetris->y=FrameY+10;
  tetris->flag = tetris->next;
  print_tetris(hOut,tetris);
  tetris->x=FrameX+Frame_width;  //??????????x????
  tetris->y=FrameY-1;     //??????????y????
  tetris->flag=temp;     //????????????????????
  while(1)
  {//??????��??????????��??????
   label:print_tetris(hOut,tetris);//????????????
   Sleep(tetris->speed);   //??????
   clear_tetris(hOut,tetris);  //???????
   temp1=tetris->x;    //???????????????????
   temp2=tetris->flag;    //???????????????????
   if(kbhit())   
   {        //?��?????��?????????????ch??????
    ch=getch(); 
    if(ch==75)     //?????????????????????????2
    {      
     tetris->x-=2;
    }
    if(ch==77)     //??????????????????????????2
    {      
     tetris->x+=2;    
    }
    if(ch==72)     //???????????��????????????90??
    {      
     if( tetris->flag>=2 && tetris->flag<=3 )
     {
      tetris->flag++; 
      tetris->flag%=2;
      tetris->flag+=2;
     }
     if( tetris->flag>=4 && tetris->flag<=7 )
     {
      tetris->flag++;
      tetris->flag%=4;
      tetris->flag+=4;
     }    
     if( tetris->flag>=8 && tetris->flag<=11 )
     {
      tetris->flag++;
      tetris->flag%=4;
      tetris->flag+=8;
     }    
     if( tetris->flag>=12 && tetris->flag<=15 )
     {
      tetris->flag++;
      tetris->flag%=4;
      tetris->flag+=12;
     }    
     if( tetris->flag>=16 && tetris->flag<=19 )
     {
      tetris->flag++;
      tetris->flag%=4;
      tetris->flag+=16;
     }
    }
    if(ch==32)     //????????????
    {
     print_tetris(hOut,tetris);
     while(1)
     {
      if(kbhit())   //?????????????????
      {
       ch=getch();
       if(ch==32)
       {
        goto label;
       }
      }
     }
    }
    if(if_moveable(tetris)==0) //?????????????????????��
    {
     tetris->x=temp1;
     tetris->flag=temp2;
    }
    else      //???????????��???
    {
     goto label;
    }
   }
   tetris->y++;     //??????��?????????????????
   if(if_moveable(tetris)==0)  //?????????????????????????????
   {    
    tetris->y--;
    print_tetris(hOut,tetris);
    del_full(hOut,tetris);
    break;
   }
  }
  for(i=tetris->y-2;i<tetris->y+2;i++)
  {//????????????????��??????��??
   if(i==FrameY)
   {
    j=0;      //?????????????j=0
   }
  }
  if(j==0)       
  {
   system("cls");
   getch();
   break;
  }
  //???????????????????????(??????)
  tetris->flag = tetris->next;
  tetris->x=FrameX+2*Frame_width+6;
  tetris->y=FrameY+10;
  clear_tetris(hOut,tetris);  
 }
}
