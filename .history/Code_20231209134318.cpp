#include <iostream>
using namespace std;
#include <string.h>
#include <stdio.h>
#include <time.h>
#define 	MINX 		20
#define 	MINY 		20
#define 	MAXX 		600
#define 	MAXY 		500
#define 	BACKGROUND	15

struct Point {
	int x,y,x0,y0;
};

void initGame ();
bool checkPoint ();
void drawPoint (int x,int y,int r);
void drawSnake ();
void drawFood ();
void drawGame ();
void classic();
void modern();
void mainLoop (void (*gloop)());
void run ();
void changeDirecton (int x);
void showText(int x,int y,char *str);
void showTextBackground(int x,int y,char *str,int color);

int level;
bool endGame;
int snakeLength;
Point snake[100];
Point direction;
Point food;
const int DIRECTION	= 10;
char* gamescore = new char[20];

void showTextBackground(int x,int y,char *str,int color){
	int bk = getbkcolor();
	setbkcolor(color);
	outtextxy(x,y,str);
	delay(200);
	setbkcolor(bk);
}

void showText(int x,int y,char *str){
	int c = getcolor();
	int color = rand() % 16 + 1;
	setcolor(color);
	outtextxy(x,y,str);
	setcolor(c);
	delay(30);
}

bool checkPoint (){
	for (int i = 0;i < snakeLength;i++){
		if (food.x == snake[i].x && food.y == snake[i].y)
		return false;
	}
	return true;
}

void initGame(){
	setbkcolor (BACKGROUND);
	cleardevice ();
	setwindowtitle ("IN GAME");
	endGame = false;
	setfillstyle (1,8); 
	//draw the border
	bar (MINX,MINY,MAXX,MINY+5);
	bar (MAXX,MINY,MAXX-5,MAXY);
	bar (MAXX,MAXY,MINX,MAXY-5);
	bar (MINX,MINY,MINX+5,MAXY);
    setcolor (0);
    int bk = getbkcolor();
	//first place the snake start to move
	snake[0].x = 60;
	snake[0].y = 50;
	snake[1].x = 50;
	snake[1].y = 50;
	snake[2].x = 40;
	snake[2].y = 50;
	snakeLength = 3;
	setfillstyle (1,BACKGROUND);
	bar (25,25,415,215);
	//snake will go down when the game start
	direction.x = 0;
	direction.y = 10; 
	setcolor (2);
	srand ( time(NULL));
	// create food
    do{
        food.x = (rand() % (57) + 3)*10;
    	food.y = (rand() % (47) + 3)*10;
	}while (checkPoint() == false);
}

void modern(){
	for (int i = 0;i < snakeLength;i++){
		if (i == 0){
			snake[0].x0 = snake[0].x;
			snake[0].y0 = snake[0].y;
			snake[0].x += direction.x;
			snake[0].y += direction.y;
		}
		else {
			snake[i].x0 = snake[i].x;
			snake[i].y0 = snake[i].y;
			snake[i].x = snake[i-1].x0;
			snake[i].y = snake[i-1].y0;
		}
		if (snake[0].x < MINX+5 || snake[0].y < MINY+5 || snake[0].x > MAXX-5 || snake[0].y > MAXY - 5 )
			endGame = true;
		if (i != 0 && snake[0].x == snake[i].x && snake[0].y == snake[i].y)	 
		endGame = true;
	}
	if (snake[0].x == food.x && snake[0].y == food.y){
		snake[snakeLength].x = snake[snakeLength-1].x0;
		snake[snakeLength].y = snake[snakeLength-1].y0;
		snakeLength++;
		PlaySound(TEXT("HuanHoaHong.wav"), NULL, SND_ASYNC);
		srand ( time(NULL));
		do{
        	food.x = (rand() % (57) + 3)*10;
    		food.y = (rand() % (47) + 3)*10;
		}while (checkPoint() == false);
	}
}

void classic(){
    for (int i = 0; i < snakeLength; i++) {
        if (i == 0) {
            snake[0].x0 = snake[0].x;
			snake[0].y0 = snake[0].y;
			snake[0].x += direction.x;
			snake[0].y += direction.y;
        }else{
            snake[i].x0 = snake[i].x;
			snake[i].y0 = snake[i].y;
			snake[i].x = snake[i-1].x0;
			snake[i].y = snake[i-1].y0;
        }
         
        if (snake[i].x >= MAXX) 
		    snake[i].x = MINX + 10;
        if (snake[i].x <= MINX) 
		    snake[i].x = MAXX - 10;
        if (snake[i].y >= MAXY) 
		    snake[i].y = MINY + 10;
        if (snake[i].y <= MINY) 
		    snake[i].y = MAXY - 10;
        
        if (i != 0 && (snake[0].x == snake[i].x && snake[0].y == snake[i].y)) 
		endGame = true;
    }
    if (snake[0].x == food.x && snake[0].y == food.y){
		snake[snakeLength].x = snake[snakeLength-1].x0;
		snake[snakeLength].y = snake[snakeLength-1].y0;
		snakeLength++;
		PlaySound(TEXT("HuanHoaHong.wav"), NULL, SND_ASYNC);
		srand ( time(NULL));
        do{
        	food.x = (rand() % (57) + 3)*10;
    		food.y = (rand() % (47) + 3)*10;
		}while (checkPoint() == false);
	}
}

void drawPoint (int x,int y,int r){
	circle (x,y,r);
	floodfill(x,y,getcolor());
}

void drawSnake (){
	setfillstyle (1,5);//color of snake
	int count = 0;
	for (int i = 0;count < snakeLength;i++){
			drawPoint(snake[i].x, snake[i].y,5);
			count++;
		} 
	int x = getcolor();
	setfillstyle (1,BACKGROUND);
	drawPoint(snake[snakeLength-1].x0,snake[snakeLength-1].y0,5);
	setcolor (BACKGROUND);
	circle (snake[snakeLength-1].x0,snake[snakeLength-1].y0,5);
	setcolor(x);
	setfillstyle (1,5);
}

void drawFood (){
	int x = getcolor();
	int c = rand() % 14 + 1;
	setcolor(c);
	setfillstyle (SOLID_FILL, c);
	drawPoint(food.x, food.y,5);
	setcolor(x);
	setfillstyle (1,BACKGROUND);
}


void drawGame (){
	drawSnake();
	drawFood();
	int x = getcolor ();
	setcolor (9);
	sprintf(gamescore,"%d",snakeLength*level*10-level*30);
    settextstyle(4,0,3);
    outtextxy(610,20,"SCORE");
    setcolor(12);
    outtextxy(660,50,gamescore);
	setcolor (x);
}

void mainLoop (void (*xxx)()){
	int x = getcolor();
	if (!kbhit()){
		xxx();
	}
	else{
		char ch;
        ch = getch();
        changeDirecton(ch);
        mainLoop (xxx);
    }
}

void changeDirecton (int x){
	switch(x){
                case 72: 
                    if (direction.y != DIRECTION) {
                    	PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
            			direction.x = 0; 
						direction.y = -DIRECTION;
        			}
                    break;
                case 80: 
                	if (direction.y != -DIRECTION) {
                		PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
            			direction.x = 0; 
						direction.y = DIRECTION;
        			}
                   break;
                case 77:
                    if (direction.x != -DIRECTION) {
                    	PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
            			direction.x = DIRECTION; 
						direction.y = 0;
        			}
                    break;
                case 75:
                    if (direction.x != DIRECTION) {
                    	PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
            			direction.x = -DIRECTION; 
						direction.y = 0;
        			}
                    break;
                case 27:
                	endGame = true;
					break;
            }
}

void run (){
	initwindow (800,600);
	x1:
	PlaySound(TEXT("wewillrockyou.wav"), NULL , SND_ASYNC);
	setwindowtitle ("SNAKEGAME.exe");
	while (true){
	x11:
	int bk = getbkcolor();
	setbkcolor(0);
	cleardevice();
	clearmouseclick(WM_LBUTTONDOWN);
	while (!ismouseclick(WM_LBUTTONDOWN) || mousex() < 200 || mousey() > 465 || mousey() < 190 || mousex() > 580 ){
		settextstyle(2,0,10);
		setcolor (10);
		outtextxy(240,70,"GAME MENU");
		settextstyle(10,0,5);
		showText (290,200,"New Game");
		showText (325,270,"About");
		showText (280,340,"Quit Game");
	}
	clearmouseclick(WM_LBUTTONDOWN);
	if (mousey() <= 255){
		x2:
		setbkcolor(0);
		cleardevice();
		int nameFunction;
		clearmouseclick(WM_LBUTTONDOWN);
		while (!ismouseclick(WM_LBUTTONDOWN) || mousex() < 290 || mousex() > 520 || mousey() < 240 || mousey() > 400){
			settextstyle(1,0,6);
			setcolor(10);
			showText(130,150,"GAME TYPE");
			setcolor(15);
			settextstyle(10,0,6);
			showTextBackground(260,250,"Classic",0);
			showTextBackground(280,350,"Modern",0);
		}
		if (ismouseclick(WM_LBUTTONDOWN) && mousex() >= 290 && mousex() <= 520 && mousey() >= 240 && mousey() <= 400){
			if(mousey() <= 300) 
			nameFunction = 1;
			else nameFunction = 2;
		}
        setbkcolor(0);
		cleardevice();
		settextstyle (4,0,6);
		setcolor (10);
		outtextxy (50,100,"DIFFICULT LEVEL");
        setcolor(5);
        settextstyle(2,0,8);
		int xx = 330;
		char str1[2];
		clearmouseclick(WM_LBUTTONDOWN);
		while (!ismouseclick(WM_LBUTTONDOWN) || mousex() < 0 || mousex() > 790 || mousey() < 280 || mousey() > 550){
		showTextBackground(10,300,"Baby",0);
		showTextBackground(160,300,"Easy",0);
		showTextBackground(320,300,"Normal",0);
		showTextBackground(520,300,"Hard",0);
		showTextBackground(670,300,"Insand",0);
	    showText(300,500,"God Mode");
	}
	    if (ismouseclick(WM_LBUTTONDOWN) && mousex() >= 0 && mousex() <= 790 && mousey() >= 280 && mousey() <= 550){
			if(mousex() <= 100) level = 1;
			else if(mousex() <= 240 && mousey() <= 350) level = 2;
			else if(mousex() <= 450 && mousey() <= 350) level = 3;
			else if(mousex() <= 600 && mousey() <= 350) level = 4;
			else if(mousex() <= 750 && mousey() <= 350) level = 5;
			else level =6 ;
		}
		PlaySound(TEXT("start.wav"), NULL , SND_ASYNC);
		initGame();
		while (!endGame){
		//Speed of snake 
		if(level<6)
		delay (230 - (level)*40);
		else delay(5);
		if (nameFunction == 1)
		mainLoop(classic);
		else mainLoop(modern);
		drawGame();
	    } 
	    cleardevice();
	    setbkcolor(0);
		PlaySound(TEXT("nevergonnagiveyouup.wav"), NULL , SND_ASYNC);
		setcolor(15);
		settextstyle (0,0,1);
        outtextxy(150, 0,"xxxxxxxxxxddddddddddol;'.....'''''';cdxxxxxxxxxxxxxxxxxxxxxx");
        outtextxy(150, 15,"kkkkkxxxxxxxxxdxdoolc:;,'.....''''',;cdxxxxxxxxxxxxxxxxxxxxx");
        outtextxy(150, 30,"OOkkkkkkkkxxxxxxddlc:::;;:;;;;::;;;,,;oxxxxxxxxxxxxxxxxxxxxx");
        outtextxy(150, 45,"OOOOkkkOOkkxxxxdxd:,;::::clllllllol:,;oxxxxxxxxxxxxkxxxxxxxx");
        outtextxy(150, 60,"OOOkkkkkkkkkkxxxdl;,::;;::cllllllllc;:oxxkxkxxxxxxxkxxxxxxxx");
        outtextxy(150, 75,"OOOOkOOOOOkkxxxxdl;;:;;;;;;:cc:ccllc;cdxxxxxxxxxxxkkxxxxxxxx");
        outtextxy(150, 90,"kOOOkOOOkkxxxxxdllllc::::;;:cc:;::cc:oxxxxxxxxxxxxxkxxxxxxxx");
        outtextxy(150, 105,"kkOOkkkkkxxxxxdl::ooc::::;;:lllllllcoxxxxxxxxxxxxxxxxxxxxxxx");
        outtextxy(150, 120,"kkOOkkxxxxxxxxxdc:ccc::;;;::cllllllcoxxxxxxxxdxxxxxxxxxxxxxx");
        outtextxy(150, 135,"kkkkkxxxxxxxkkxxxolc:::;,;::clllllloxkkkkxxxxxxxxxxxxxxkkkkk");
        
        outtextxy(150, 150,"kkkkxxxxxxkkkkkkkkdc:::;,;;;:clllodxkkkkkkxxxxxxxxxxxxxkkkkk");
        outtextxy(150, 165,"kkxkxxxkkkkkkkkkkxoc::::::cllllloxkkkxkkkkxxxxxxxxxxxxxkkkkk");
        outtextxy(150, 180,"kkxxxxxxxxxxxxxxxxoc::::::ccllclodxxxxxxxxxxxxxxxxxxxxxxxkkk");
        outtextxy(150, 195,"xxxxxxxxxxxxxxxxxdoc:::;;::cllllc::odxxxxxxxxxxxxxxxxxxxxxxx");
        outtextxy(150, 210,"xxxxxxxkkkkkxxxxxdllllc::cccccclo;.';clooddxxxxxxxxxxxxkxxkk");
        outtextxy(150, 225,"xxxxxxxkkxxdollodo::c:::;::c:cloo;....',;;::cclooddxxxxxxxxk");
        outtextxy(150, 240,"xxxxxxxxdoc;,'',ldoc:::c:;;::loddl,.......'''...',,;:ldxxxxx");
        outtextxy(150, 255,"xxddolc;'.....'cdl::::c:;:codddo;...................'cdxxxxx");
        outtextxy(150, 270,"xdc;,'........'cdl::cccclodddl:,.....................,oxxxxx");
        outtextxy(150, 285,"xo,............,;;:clcc::cloc;'......................'lxxxxx");
        
        outtextxy(150, 300,"xl'..............';ldo::;;;;,'...........','.........'lxxxxx");
        outtextxy(150, 315,"xc...............';ldoc:;;;,,'...........,;;'.......':dxxxxx");
        outtextxy(150, 330,"xl'...............;lol:;;;;,,'............,;,.';cc,.,oxxxxxx");
        outtextxy(150, 345,"xo,...............;clc:;;;;,,'............,;;;:cc;,.,oxxxxxx");
        outtextxy(150, 360,"xd;...............,;:;;;;;,,,'............,;;::c:,..:dxxxxxx");
        outtextxy(150, 375,"xd;...............';:;;;;;,,,'............,;::ccc;..',lxxxxx");
        outtextxy(150, 390,"xo,................;:;;;;,,,,'...........',;:cccc,....'cxxxx");
        outtextxy(150, 405,"xd;................;;,,,,,,'''...........';:cllc:,.....'lxxx");
        outtextxy(150, 420,"xd:................,;,,,,''''..............';;::;'......,lxx");
        outtextxy(150, 435,"xxc................,,,,,,''''''''........................;ox");
        
        outtextxy(150, 450,"xxc................,,,,'''''''''.......    ..............'cx");
        outtextxy(150, 465,"xdc................,,,,,'''''''''.......      ............:d");
        outtextxy(150, 480,"xd:................,,,,,,'''',,'''.......      .....''...'cd");
        
        setbkcolor(BACKGROUND);
        setcolor (8);
		settextstyle (3,0,2);
		outtextxy (10,550,"Your Score : ");
		setcolor(10);
		outtextxy (140,550,gamescore);
		settextstyle (3,0,4);
		setcolor(9);
		outtextxy(315,540,"Play again?");
		clearmouseclick(WM_LBUTTONDOWN);
		while (!ismouseclick(WM_LBUTTONDOWN)){
			showText(50,270,"YES");
			showText(670,270,"YES");
			showText(240,500,"You've been rickrolled");
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			if (mousex() >= 10 && mousex() <= 150 && mousey() >= 260 && mousey() <= 310){
				delay(100);
				goto x1;
			}
			else if(mousex() >= 600 && mousex() <= 700 && mousey() >= 260 && mousey() <= 310){
				delay(100);
				goto x1;
			}
        	}
    	}else if (mousey() <= 325){
    		x3:
    		clearmouseclick(WM_LBUTTONDOWN);
    		cleardevice();
		    settextstyle (1,0,4);
		    setcolor (15);
		    int x = getcolor();
		    setcolor(x);
            while (!ismouseclick(WM_LBUTTONDOWN) || mousex() < 200 || mousey() > 465 || mousey() < 190 || mousex() > 580 ){
		    settextstyle(10,0,7);
		    setcolor (10);
		    showText (280,70,"About");
		    settextstyle(10,0,5);
		    outtextxy (325,200,"Game");
		    outtextxy (290,270,"Creator");
		    outtextxy (325,340,"Back");
	        }
	        clearmouseclick(WM_LBUTTONDOWN);
	        if (mousey() <= 255){
	        cleardevice();
		    settextstyle (1,0,4);
		    setcolor (15);
			while(!ismouseclick(WM_LBUTTONDOWN)){
			settextstyle(10,0,6);
			showText(280,10,"Game");
			settextstyle(10,0,4);
			showText(10,60,"Classic");
			settextstyle(1,0,3);
			setcolor(15);
			outtextxy(10,100,"The main objective of this game is to feed an");
			outtextxy(15,140,"increasing length of snake with food particles");
			outtextxy(15,180,"that are found atrandom positions. The player");
			outtextxy(15,220,"loses when the snake runs into itself.");
			settextstyle(10,0,4);
			showText(10,280,"Modern");
			settextstyle(1,0,3);
			setcolor(15);
			outtextxy(10,320,"The main objective of this game is to feed an");
			outtextxy(15,360,"increasing length of snake with food particles");
			outtextxy(15,400,"that are found at random positions. The player");
			outtextxy(15,440,"loses when the snake runs into the screen ");
			outtextxy(15,480,"border, other obstacle, or itself.");
			settextstyle(10,0,4);
			setcolor(11);
			outtextxy(320,540,"Back");
		    }
		    setcolor(x);
		    settextstyle (1,0,2);
		    setcolor (4);
		    goto x3;
			}
			else if (mousey() <= 300){
			cleardevice();
			while(!ismouseclick(WM_LBUTTONDOWN)){
			settextstyle(10,0,6);
			setcolor(11);
			showText(260,20,"Creator");
			settextstyle(10,0,4);
			setcolor(9);
			showText(180,200,"Pham Duc Dat");
			showText(230,250,"The little boy");
			showText(180,300,"Le Duy Duong");
			showText(230,350,"The third boy");
			outtextxy(320,540,"Back");
		    }
		    setcolor(x);
		    settextstyle (1,0,2);
		    setcolor (4);
		    goto x3;
			}
		    settextstyle (1,0,2);
		    setcolor (4);
		    goto x11;
		}else{
		exit(0);
		}
}
}
int main (){
	run();
	delete gamescore;
	getch();
	closegraph ();
    return 0;
}

