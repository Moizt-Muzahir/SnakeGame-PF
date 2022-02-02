//============================================================================
// Name        : Tetris.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Tetris...
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<string>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sstream>
#include<cmath>      
using namespace std;
bool Recordbreaker=false;
int Highscore=0;
int gameEnd = 2;
int score_int=0;
char score_str[650];



void Food(int);
void Time();
int string_int(char []);
void Num_string(int ,char []);

void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); 
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}


 int food[2][5];
 int obstacles[4][5];
     int grid[66][66];
 int c;
 
int startx=32,starty=40;
int snake[2][650];
int length=3;



void Display1(){
    
    glClearColor(0, 0.0,
            0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT); 
    
    
    	
    	
    DrawCircle(startx*10,starty*10,10,colors[1]);
    
 			DrawCircle(300,300,10,colors[5]);
			DrawString( 0, 400, "GAME END", colors[MISTY_ROSE]);
    		DrawString(320, 290,"Retry(press R)",colors[MISTY_ROSE]);
    		if (Recordbreaker)
    		{
    			DrawString(0,500,"New high score",colors[MISTY_ROSE]);
    			}
    			else
    		{
    		 DrawString(0,500,"your score",colors[MISTY_ROSE]);
			}
			DrawString(0,450,score_str,colors[MISTY_ROSE]);
	
   glutSwapBuffers(); 
}

void Display_pre(){

 glClearColor(0, 0.0,
            0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
        DrawCircle(startx*10,starty*10,10,colors[1]);
    DrawCircle(300,300,10,colors[5]);
   
    DrawString(320, 290,"Start Game(Press P)",colors[MISTY_ROSE]);
  
    
     glutSwapBuffers(); 

}
void Display(){

    glClearColor(0, 0.0,
            0.0, 0 );
    glClear(GL_COLOR_BUFFER_BIT);   
    
    
     if (gameEnd==2)
    Display_pre();
    else if(gameEnd==1)
    Display1(); 
    else
    	
    { 
 DrawString(0,550,score_str,colors[MISTY_ROSE]);
 int *ptr=&grid[startx][starty];
 if (*ptr==1)
 
 {
 	
 	length++;
 	score_int+=5;
 	Num_string(score_int,score_str);
 	for(int i=0;i<5;i++)
	{
	if ((food[0][i]==startx)&&(food[1][i]==starty));
	{
		grid[food[0][i]][food[1][i]]=0;
		food[0][i]=rand()%66;
		food[1][i]=rand()%66;
		grid[food[0][i]][food[1][i]]=1;
	}
	}
 	
 	}
 	if(*ptr==2)
 	
 	{
 		
 		Time();
 		
 	}
 	

 	
 	
for (int i=0;i<5;i++)
{
	DrawCircle(food[0][i]*10,food[1][i]*10,10,colors[rand()%139]);
   }
     
   DrawCircle( startx*10 , starty*10 , 10 , colors[0]);
	snake[0][0]=startx;
  	snake[1][0]=starty;
  	
  	
	for(int i=0;i<length;i++)
	{
		DrawSquare(snake[0][i]*10,snake[1][i]*10,5,colors[i]);
	}
	
	for(int i=0;i<length;i++)
			{
					grid[snake[0][length-i]][snake[1][length-i]]=0;
				}
  		switch(c)
		{
			case 0:
			{startx--;;
			if (startx<0)
			startx=65;
			break;}
			case 1:
			{startx++;
			if(startx>65)
			startx=0;
			break;}
			case 2:
			{starty++;
			if(starty>65)
			starty=0;
			break;
			}
			case 3:
			{
			starty--;
			if(starty<0)
			starty=65;
			break;
			}												
			}
			for(int i=0;i<length;i++)
  		{	
  		snake[0][length-i]=snake[0][length-1-i];
  		snake[1][length-i]=snake[1][length-1-i];

  		grid[snake[0][length-i]][snake[1][length-i]]=2;
  		}
  		
			
   
	}
   glutSwapBuffers(); 
   
}




void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT   ) {
	
	if((gameEnd==1)||(gameEnd==2))
	startx--;
	else
	c=0;										
      
      
    } else if (key == GLUT_KEY_RIGHT  ) {
		
		if((gameEnd==1)||(gameEnd==2))
	startx++;
	else
	c=1;		
    } else if (key == GLUT_KEY_UP)  {
        
        if((gameEnd==1)||(gameEnd==2))
	starty++;
	else
	c=2;		
    }
    else if (key == GLUT_KEY_DOWN)   {
		
		if((gameEnd==1)||(gameEnd==2))
		starty--;
		else
		c=3;
    }
    

     glutPostRedisplay();

}

void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC) {
        exit(1); 
    }
    if (key == 'R' || key=='r') {
         if ((startx==30)&&(starty==30)&&(gameEnd==1))
         {
         	for(int i=0;i<length;i++)
			{
					grid[snake[0][length-i]][snake[1][length-i]]=0;
				}
				
         	length=3;;
         	gameEnd=0;
         	score_int=0;
         	Num_string(score_int,score_str);
         	}
         	
         }	
    
    
   else  if ((key == 'p')||(key=='P'))
    {  
     if ((startx==30)&&(starty==30)&&(gameEnd==2))
        { 	for(int i=0;i<length;i++)
			{
					grid[snake[0][length-i]][snake[1][length-i]]=0;
				}
         	length=3;;
         	gameEnd=0;
         	score_int=0;
         	Num_string(score_int,score_str);
	}
	}
    
    glutPostRedisplay();
}


void Food(int m)
{

for(int i=0;i<5;i++)
{
	grid[food[0][i]][food[1][i]]=0;
}
for(int i=0;i<5;i++)
{
	food[0][i]=rand()%66;
	
	food[1][i]=rand()%66;
	while((grid[food[0][i]][food[1][i]]!=0))
	{
		food[0][i]=rand()%66;
		food[1][i]=rand()%66;
	}
	
		
		
	grid[food[0][i]][food[1][i]]=1;
}


 glutPostRedisplay();
 
 	 glutTimerFunc(30000.0 / FPS, Food, 0);	

 }
 

void Time()
{

	if (score_int>Highscore)
				{
					Highscore=score_int;
					Recordbreaker=true;
				}
				else
				{
					Recordbreaker=false;
				}
	gameEnd = 1;

	
	}
void Timer(int m) {



  	
		

	glutPostRedisplay();

    glutTimerFunc(1000.0 / FPS, Timer, 0);
}
int string_int(char A[])

{
	int Sum=0;
	for (int i=0;	A[i]!='\0';	i++)
	{
		if ((A[i]>'9')||(A[i]<'0'))
		{
			cout<<"Not a number\n";
			Sum=-1;
			break;
		}
		else
		{
			Sum+=A[i]-'0';
			Sum*=10;
		}
	}
	if (Sum>=0)
	Sum/=10;
	return Sum;
}
void Num_string(int A,char L[])
{
	int i;
	char str[100];
	for(i=0;	A>0;	i++)
	{
		
		L[i]=char(A%10+'0');
		A/=10;
	}
	L[i]='\0';
	i--;
	for(int j=0;j<i;j++,i--)
	swap(L[j],L[i]);
	
}	

int main(int argc, char*argv[]) {
    int width = 650, height = 650; 
    InitRandomizer();
    glutInit(&argc, argv); 

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
    glutInitWindowPosition(50, 50); 
    glutInitWindowSize(width, height);
    glutCreateWindow("PF's Snake Game"); 
    SetCanvasSize(width, height); // 


    
    glutDisplayFunc(Display); 
    glutSpecialFunc(NonPrintableKeys); 
    glutKeyboardFunc(PrintableKeys); 

    glutTimerFunc(5.0 / FPS, Timer, 0);
    glutTimerFunc(5.0 / FPS, Food, 0);

    glutMainLoop();
    return 1;
}
#endif 

