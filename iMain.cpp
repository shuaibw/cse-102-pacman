#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#define screenheight 1080
#define screenwidth 1920
#define mazepixel 40
#include "iGraphics.h"
#include<time.h>
#include<stdlib.h>
#include<Windows.h>
//ALL FUNCTION PROTOTYPES
void iPauseAll();
void iResumeAll();
void pacmove();
void introchange();
void setstr();
int calcDist(int x1, int y1, int x2, int y2);
void setMazeAra();
void checkTrigger();
void deathScene();
void frozTimeCheck();
void ghostIniCords();
void dirGen2(int ara[], int dir, int ghostIdx);
void directionGen(int a, int ghostIdx);
void moveghost();
void change();
void reset();
void readData();
//PROTO END

char *itoa(int num, char *str)
{
        if(str == NULL)
        {
                return NULL;
        }
        sprintf(str, "%d", num);
        return str;
}

int mazeHeight = 840;
int mazeWidth = 760;
int mazeX = (screenwidth / 2) - (mazeWidth / 2) - 20;
int mazeY = (screenheight / 2) - (mazeHeight / 2) + 40;
int mazeLevel = 0;
int ara[2][21][19] =
{
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1,
		0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
		1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,
		0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
		1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
		1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	},
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1,
		0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
		1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	}
};
int cellY;
int cellX;			//pacman cell
int mazeXcor[198];
int mazeYcor[198];
int foodXcor[201][2];
int foodYcor[201];
int fruitGen[201];
int blueGhost;
char *str[284];
char pacScore[20] = "00";
char *pacdeath[12];



char difficulty[4][30] = { "sprite\\difficulty\\df.bmp", "sprite\\difficulty\\df1.bmp", "sprite\\difficulty\\df2.bmp", "sprite\\difficulty\\df3.bmp" };
char goImg[4][30] = { "sprite\\go\\gameover.bmp", "sprite\\go\\gameover1.bmp", "sprite\\go\\gameover2.bmp", "sprite\\go\\gameover3.bmp" };
char eblinkImg[4][30] = { "sprite\\eblink\\enter.bmp", "sprite\\eblink\\enter1.bmp", "sprite\\eblink\\enter2.bmp", "sprite\\eblink\\enter3.bmp" };
char rulesImg[14][30] = { "sprite\\rules\\rules.bmp", "sprite\\rules\\rules1.bmp", "sprite\\rules\\rules2.bmp", "sprite\\rules\\rules3.bmp", "sprite\\rules\\rules4.bmp", "sprite\\rules\\rules5.bmp", "sprite\\rules\\rules6.bmp", "sprite\\rules\\rules7.bmp", "sprite\\rules\\rules8.bmp", "sprite\\rules\\rules9.bmp", "sprite\\rules\\rules10.bmp", "sprite\\rules\\rules11.bmp", "sprite\\rules\\rules12.bmp", "sprite\\rules\\rules13.bmp" };
char paused[2][30] = { "sprite\\pause\\pause.bmp", "sprite\\pause\\pause1.bmp" };
char selBG[5][35] = { "sprite\\selBG\\selBG.bmp", "sprite\\selBG\\selBG1.bmp", "sprite\\selBG\\selBG2.bmp", "sprite\\selBG\\selBG3.bmp", "sprite\\selBG\\selBG4.bmp" };
char BGImg[4][30] = { "sprite\\bg\\bg1.bmp", "sprite\\bg\\bg2.bmp", "sprite\\bg\\bg3.bmp", "sprite\\bg\\bg4.bmp" };
char maze[8][30] = { "sprite\\Bricks\\brick3.bmp", "sprite\\Bricks\\brick1.bmp", "sprite\\Bricks\\brick2.bmp", "sprite\\Bricks\\brick3.bmp", "sprite\\Bricks\\brick4.bmp", "sprite\\Bricks\\brick5.bmp", "sprite\\Bricks\\brick6.bmp", "sprite\\Bricks\\brick7.bmp" };
char playGameInt[2][30] = { "sprite\\playgame.bmp", "sprite\\playgame1.bmp" };
char introsplash[2][40] = { "sprite\\splash\\splash 1.bmp", "sprite\\splash\\splash 2.bmp" };
char menu[7][30] = { "sprite\\menu\\mainmenu.bmp", "sprite\\menu\\menu1.bmp", "sprite\\menu\\menu2.bmp", "sprite\\menu\\menu3.bmp", "sprite\\menu\\menu4.bmp", "sprite\\menu\\menu5.bmp", "sprite\\menu\\menu6.bmp" };
char settingImg[6][35] = { "sprite\\settings\\settings1.bmp", "sprite\\settings\\settings2.bmp", "sprite\\settings\\settings3.bmp", "sprite\\settings\\settings4.bmp", "sprite\\settings\\settings5.bmp", "sprite\\settings\\settings6.bmp" };
char selectMazeImg[8][40] = { "sprite\\selectMaze\\selmaze.bmp", "sprite\\selectMaze\\selmaze1.bmp", "sprite\\selectMaze\\selmaze2.bmp", "sprite\\selectMaze\\selmaze3.bmp", "sprite\\selectMaze\\selmaze4.bmp", "sprite\\selectMaze\\selmaze5.bmp", "sprite\\selectMaze\\selmaze6.bmp", "sprite\\selectMaze\\selmaze7.bmp" };
char exitImg[3][30] = { "sprite\\exit\\exit.bmp", "sprite\\exit\\exityes.bmp", "sprite\\exit\\exitno.bmp" };

char pacManRight[2][30] = { "sprite\\pacman\\1.bmp", "sprite\\pacman\\2.bmp" };
char pacManLeft[2][30] = { "sprite\\pacman\\3.bmp", "sprite\\pacman\\4.bmp" };
char pacManUp[2][30] = { "sprite\\pacman\\5.bmp", "sprite\\pacman\\6.bmp" };
char pacManDown[2][30] = { "sprite\\pacman\\7.bmp", "sprite\\pacman\\8.bmp" };
char *fruit[7];

char inkyUp[2][30] = { "sprite\\ghost\\inky\\(5).bmp", "sprite\\ghost\\inky\\(6).bmp" };
char inkyDown[2][30] = { "sprite\\ghost\\inky\\(7).bmp", "sprite\\ghost\\inky\\(8).bmp" };
char inkyLeft[2][30] = { "sprite\\ghost\\inky\\(3).bmp", "sprite\\ghost\\inky\\(4).bmp" };
char inkyRight[2][30] = { "sprite\\ghost\\inky\\(1).bmp", "sprite\\ghost\\inky\\(2).bmp" };

char blinkyUp[2][30] = { "sprite\\ghost\\blinky\\(5).bmp", "sprite\\ghost\\blinky\\(6).bmp" };
char blinkyDown[2][30] = { "sprite\\ghost\\blinky\\(7).bmp", "sprite\\ghost\\blinky\\(8).bmp" };
char blinkyLeft[2][30] = { "sprite\\ghost\\blinky\\(3).bmp", "sprite\\ghost\\blinky\\(4).bmp" };
char blinkyRight[2][30] = { "sprite\\ghost\\blinky\\(1).bmp", "sprite\\ghost\\blinky\\(2).bmp" };

char pinkyUp[2][30] = { "sprite\\ghost\\pinky\\(5).bmp", "sprite\\ghost\\pinky\\(6).bmp" };
char pinkyDown[2][30] = { "sprite\\ghost\\pinky\\(7).bmp", "sprite\\ghost\\pinky\\(8).bmp" };
char pinkyLeft[2][30] = { "sprite\\ghost\\pinky\\(3).bmp", "sprite\\ghost\\pinky\\(4).bmp" };
char pinkyRight[2][30] = { "sprite\\ghost\\pinky\\(1).bmp", "sprite\\ghost\\pinky\\(2).bmp" };

char clydeUp[2][30] = { "sprite\\ghost\\clyde\\(5).bmp", "sprite\\ghost\\clyde\\(6).bmp" };
char clydeDown[2][30] = { "sprite\\ghost\\clyde\\(7).bmp", "sprite\\ghost\\clyde\\(8).bmp" };
char clydeLeft[2][30] = { "sprite\\ghost\\clyde\\(3).bmp", "sprite\\ghost\\clyde\\(4).bmp" };
char clydeRight[2][30] = { "sprite\\ghost\\clyde\\(1).bmp", "sprite\\ghost\\clyde\\(2).bmp" };

char frozenGhost[2][40] = { "sprite\\ghost\\frozen\\(1).bmp", "sprite\\ghost\\frozen\\(2).bmp" };
char frozenGhostEnd[2][40] = { "sprite\\ghost\\frozen\\(2).bmp", "sprite\\ghost\\frozen\\(3).bmp" };
char eatScore[4][50] = { "sprite\\ghost\\eatscore\\(1).bmp", "sprite\\ghost\\eatscore\\(2).bmp", "sprite\\ghost\\eatscore\\(3).bmp", "sprite\\ghost\\eatscore\\(4).bmp" };

typedef struct{
	int upInd, downInd, leftInd, rightInd;
	int x;
	int y;
	bool upCount, downCount, leftCount, rightCount;
	bool trigRight, trigLeft, trigUp, trigDown;
	int right, left, up, down;
}move;

typedef struct{
	int upInd, downInd, leftInd, rightInd;   //animation
	int x;
	int y;
	int cellX, cellY;
	bool flagRight, flagLeft, flagUp, flagDown;
	int left, right, up, down;
	int speed;
	bool blueOn;
	int dist1, dist2;
}ghost;

ghost cutie[4];
move pac;

int brickNum;
int foodNum;
int score;
int pactime = 10;
int pacspeed = 5;
int pacMouth = 5;
int pacInd;
int intro = 1;
int pacLife = 3;
bool startintro = true;
int deadSceneCount;
int blueScore = 0;
int scoreX;
int scoreY;
int randGen;
int foodhelp;
int t;
int *foodCor = &t;				//just to pre-initialize
int timeToGenFood = 500;		//increasing will delay in food spawning
int totalFool = 188;

bool pacDead;
bool mazeExitFlagRight;
bool mazeExitFlagLeft;
bool mainMenu;
bool gtext1;
bool splash = false;
bool settings;
bool credit;
bool quit;
bool playGame;
bool gameOver;
bool highScore = false;
bool rules;
bool playGameIntro;
bool pause;
bool selBg;
int slideselbg;
bool rulesenter;
bool selectDf;
bool pausedMenu;
bool selectMaze;
bool soundOn;


int r = 255, g = 255, b = 255;

char namestr[100];
char playername[100];
int len;
int line;
int *number;
char **name;
char buffer[100];
char *intermission[276];


int menuInd;
int selMazeInd;
int selMazeInd1;
int settingsInd;
int bgInd;
int t_rakib;
int slide;
int splashInd;
int settingInd;

bool chase=false;
bool scatter=true;
int artiScore=0;
int difficInd;
int diffSpeed = 5;

void iDraw()
{
	iClear();
	/*iSetColor(255, 255, 255);
	iFilledRectangle(mazeX-5, mazeY-5, mazeWidth+10, mazeHeight+10);
	iSetColor(0, 0, 0);
	iFilledRectangle(mazeX, mazeY, mazeWidth, mazeHeight);*/

	if (startintro)
	{
		iShowBMP(0, 0, str[intro]);
	}
	else if (splash)
	{
		iShowBMP(0, 0, introsplash[slide]);
	}
	else if (mainMenu)
	{
		iShowBMP(0, 0, menu[menuInd]);
	}
	else if (settings)
	{
		iShowBMP(0, 0, settingImg[settingsInd]);
	}
	else if (highScore)
	{
		iShowBMP(0, 0, "sprite\\highScore.bmp");
		for (int i = 0; i < 5; i++)
		{
		    if(i==0) iSetColor(240,230,140);
		    else if(i==1) iSetColor(135,206,235);
		    else if(i==2) iSetColor(150,150,150);
		    else iSetColor(255,255,255);
			iText(220, 690 - (i * 115), name[i], GLUT_BITMAP_TIMES_ROMAN_24);
			iText(520, 690 - (i * 115), itoa(number[i],buffer), GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
	else if (selectMaze)
	{
		iShowBMP(0, 0, selectMazeImg[selMazeInd]);
	}
	else if (selBg)
	{
		iShowBMP(0, 0, selBG[slideselbg]);
	}
	else if (credit)
	{
		iShowBMP(0, 0, "sprite\\credits.bmp");
	}
	else if (playGameIntro)
	{
		iShowBMP(0, 0, playGameInt[slide]);
		iText(630, 480, namestr, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (quit)
	{
		iShowBMP(0, 0, exitImg[slide]);
	}
	else if (pause)
	{
		iShowBMP(0, 0, paused[slide]);
	}
	else if (rules)
	{
		iShowBMP(0, 0, rulesImg[slide]);
	}
	else if (rulesenter)
	{
		iShowBMP(0, 0, eblinkImg[slide]);
	}
	else if (selectDf)
	{
		iShowBMP(0, 0, difficulty[slide]);
	}
	else if (playGame)
	{
		//iShowBMP(0, 0, BGImg[slide]);
		iText(1500, 900, pacScore, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1475, 950, "SCORE", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1725, 950, "LIVES", GLUT_BITMAP_TIMES_ROMAN_24);
		for (int i = 0; i < pacLife; i++)
			iShowBMP2(1700 + 40 * i, 890, "sprite\\pacman\\1.bmp", 0);
		for (int i = 0; i <= brickNum; i++)
		{
			iShowBMP(mazeX + mazeXcor[i], mazeY + mazeYcor[i], maze[selMazeInd1]);
		}
		//if (startintro) iShowBMP(0, 0, str[intro]);
		if (!pacDead && pacLife)
		{
			if (pac.rightCount)
				iShowBMP2(pac.x, pac.y, pacManRight[pac.rightInd], 0);
			else if (pac.leftCount)
				iShowBMP2(pac.x, pac.y, pacManLeft[pac.leftInd], 0);
			else if (pac.upCount)
				iShowBMP2(pac.x, pac.y, pacManUp[pac.upInd], 0);
			else if (pac.downCount)
				iShowBMP2(pac.x, pac.y, pacManDown[pac.downInd], 0);
			else
				iShowBMP2(pac.x, pac.y, pacManRight[pac.rightInd], 0);
		}
		else if (pacDead)
		{
			iShowBMP2(pac.x, pac.y, pacdeath[deadSceneCount], 0);
		}
		else
		{
			playGame = false;
			gameOver = true;
		}

		iSetColor(r, g, b);
		for (int i = 0; i <= foodNum; i++)
		{
			if (foodXcor[i][1] != -1)
			{
				iFilledCircle(mazeX + foodXcor[i][0] + 20, mazeY + foodYcor[i] + 20, 3);
				if ((i == 41 || i == 55 || i == 179 || i == 184) && mazeLevel == 0)
				{
					iSetColor(50, 205, 50);
					iFilledCircle(mazeX + foodXcor[i][0] + 20, mazeY + foodYcor[i] + 20, 6);
					iSetColor(255, 255, 255);
				}
				else if ((i == 41 || i == 55 || i == 165 || i == 156) && mazeLevel == 1)
				{
					iSetColor(50, 205, 50);
					iFilledCircle(mazeX + foodXcor[i][0] + 20, mazeY + foodYcor[i] + 20, 6);
					iSetColor(255, 255, 255);
				}
			}
			if (foodXcor[i][1] == -2)
			{
				iShowBMP2(mazeX + foodXcor[i][0], mazeY + foodYcor[i], fruit[randGen], 0);
			}
		}
		if (!blueGhost)
		{
			if (cutie[0].flagRight)
				iShowBMP2(cutie[0].x, cutie[0].y, inkyRight[cutie[0].rightInd], 0);
			else if (cutie[0].flagLeft)
				iShowBMP2(cutie[0].x, cutie[0].y, inkyLeft[cutie[0].leftInd], 0);
			else if (cutie[0].flagUp)
				iShowBMP2(cutie[0].x, cutie[0].y, inkyUp[cutie[0].upInd], 0);
			else if (cutie[0].flagDown)
				iShowBMP2(cutie[0].x, cutie[0].y, inkyDown[cutie[0].downInd], 0);

			if (cutie[1].flagRight)
				iShowBMP2(cutie[1].x, cutie[1].y, blinkyRight[cutie[1].rightInd], 0);
			else if (cutie[1].flagLeft)
				iShowBMP2(cutie[1].x, cutie[1].y, blinkyLeft[cutie[1].leftInd], 0);
			else if (cutie[1].flagUp)
				iShowBMP2(cutie[1].x, cutie[1].y, blinkyUp[cutie[1].upInd], 0);
			else if (cutie[1].flagDown)
				iShowBMP2(cutie[1].x, cutie[1].y, blinkyDown[cutie[1].downInd], 0);

			if (cutie[2].flagRight)
				iShowBMP2(cutie[2].x, cutie[2].y, clydeRight[cutie[2].rightInd], 0);
			else if (cutie[2].flagLeft)
				iShowBMP2(cutie[2].x, cutie[2].y, clydeLeft[cutie[2].leftInd], 0);
			else if (cutie[2].flagUp)
				iShowBMP2(cutie[2].x, cutie[2].y, clydeUp[cutie[2].upInd], 0);
			else if (cutie[2].flagDown)
				iShowBMP2(cutie[2].x, cutie[2].y, clydeDown[cutie[2].downInd], 0);

			if (cutie[3].flagRight)
				iShowBMP2(cutie[3].x, cutie[3].y, pinkyRight[cutie[3].rightInd], 0);
			else if (cutie[3].flagLeft)
				iShowBMP2(cutie[3].x, cutie[3].y, pinkyLeft[cutie[3].leftInd], 0);
			else if (cutie[3].flagUp)
				iShowBMP2(cutie[3].x, cutie[3].y, pinkyUp[cutie[3].upInd], 0);
			else if (cutie[3].flagDown)
				iShowBMP2(cutie[3].x, cutie[3].y, pinkyDown[cutie[3].downInd], 0);
		}
		else
		{
			if (blueScore >= 0)
			{
				iShowBMP2(scoreX, scoreY, eatScore[blueScore], 0);
			}
			if (blueGhost > 3)
			{
				for (int i = 0; i < 4; i++)
				{
					if (cutie[i].blueOn)
					{
						if (cutie[i].flagRight)
							iShowBMP2(cutie[i].x, cutie[i].y, frozenGhost[cutie[i].rightInd], 0);
						else if (cutie[i].flagLeft)
							iShowBMP2(cutie[i].x, cutie[i].y, frozenGhost[cutie[i].leftInd], 0);
						else if (cutie[i].flagUp)
							iShowBMP2(cutie[i].x, cutie[i].y, frozenGhost[cutie[i].upInd], 0);
						else if (cutie[i].flagDown)
							iShowBMP2(cutie[i].x, cutie[i].y, frozenGhost[cutie[i].downInd], 0);
					}
					else
					{
						if (i == 0)
						{
							if (cutie[0].flagRight)
								iShowBMP2(cutie[0].x, cutie[0].y, inkyRight[cutie[0].rightInd], 0);
							else if (cutie[0].flagLeft)
								iShowBMP2(cutie[0].x, cutie[0].y, inkyLeft[cutie[0].leftInd], 0);
							else if (cutie[0].flagUp)
								iShowBMP2(cutie[0].x, cutie[0].y, inkyUp[cutie[0].upInd], 0);
							else if (cutie[0].flagDown)
								iShowBMP2(cutie[0].x, cutie[0].y, inkyDown[cutie[0].downInd], 0);
						}
						else if (i == 1)
						{
							if (cutie[1].flagRight)
								iShowBMP2(cutie[1].x, cutie[1].y, blinkyRight[cutie[1].rightInd], 0);
							else if (cutie[1].flagLeft)
								iShowBMP2(cutie[1].x, cutie[1].y, blinkyLeft[cutie[1].leftInd], 0);
							else if (cutie[1].flagUp)
								iShowBMP2(cutie[1].x, cutie[1].y, blinkyUp[cutie[1].upInd], 0);
							else if (cutie[1].flagDown)
								iShowBMP2(cutie[1].x, cutie[1].y, blinkyDown[cutie[1].downInd], 0);
						}
						else if (i == 2)
						{
							if (cutie[2].flagRight)
								iShowBMP2(cutie[2].x, cutie[2].y, clydeRight[cutie[2].rightInd], 0);
							else if (cutie[2].flagLeft)
								iShowBMP2(cutie[2].x, cutie[2].y, clydeLeft[cutie[2].leftInd], 0);
							else if (cutie[2].flagUp)
								iShowBMP2(cutie[2].x, cutie[2].y, clydeUp[cutie[2].upInd], 0);
							else if (cutie[2].flagDown)
								iShowBMP2(cutie[2].x, cutie[2].y, clydeDown[cutie[2].downInd], 0);
						}
						else if (i == 3)
						{
							if (cutie[3].flagRight)
								iShowBMP2(cutie[3].x, cutie[3].y, pinkyRight[cutie[3].rightInd], 0);
							else if (cutie[3].flagLeft)
								iShowBMP2(cutie[3].x, cutie[3].y, pinkyLeft[cutie[3].leftInd], 0);
							else if (cutie[3].flagUp)
								iShowBMP2(cutie[3].x, cutie[3].y, pinkyUp[cutie[3].upInd], 0);
							else if (cutie[3].flagDown)
								iShowBMP2(cutie[3].x, cutie[3].y, pinkyDown[cutie[3].downInd], 0);
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					if (cutie[i].blueOn)
					{
						if (cutie[i].flagRight)
							iShowBMP2(cutie[i].x, cutie[i].y, frozenGhostEnd[cutie[i].rightInd], 0);
						else if (cutie[i].flagLeft)
							iShowBMP2(cutie[i].x, cutie[i].y, frozenGhostEnd[cutie[i].leftInd], 0);
						else if (cutie[i].flagUp)
							iShowBMP2(cutie[i].x, cutie[i].y, frozenGhostEnd[cutie[i].upInd], 0);
						else if (cutie[i].flagDown)
							iShowBMP2(cutie[i].x, cutie[i].y, frozenGhostEnd[cutie[i].downInd], 0);
					}
					else
					{
						if (i == 0)
						{
							if (cutie[0].flagRight)
								iShowBMP2(cutie[0].x, cutie[0].y, inkyRight[cutie[0].rightInd], 0);
							else if (cutie[0].flagLeft)
								iShowBMP2(cutie[0].x, cutie[0].y, inkyLeft[cutie[0].leftInd], 0);
							else if (cutie[0].flagUp)
								iShowBMP2(cutie[0].x, cutie[0].y, inkyUp[cutie[0].upInd], 0);
							else if (cutie[0].flagDown)
								iShowBMP2(cutie[0].x, cutie[0].y, inkyDown[cutie[0].downInd], 0);
						}
						else if (i == 1)
						{
							if (cutie[1].flagRight)
								iShowBMP2(cutie[1].x, cutie[1].y, blinkyRight[cutie[1].rightInd], 0);
							else if (cutie[1].flagLeft)
								iShowBMP2(cutie[1].x, cutie[1].y, blinkyLeft[cutie[1].leftInd], 0);
							else if (cutie[1].flagUp)
								iShowBMP2(cutie[1].x, cutie[1].y, blinkyUp[cutie[1].upInd], 0);
							else if (cutie[1].flagDown)
								iShowBMP2(cutie[1].x, cutie[1].y, blinkyDown[cutie[1].downInd], 0);
						}
						else if (i == 2)
						{
							if (cutie[2].flagRight)
								iShowBMP2(cutie[2].x, cutie[2].y, clydeRight[cutie[2].rightInd], 0);
							else if (cutie[2].flagLeft)
								iShowBMP2(cutie[2].x, cutie[2].y, clydeLeft[cutie[2].leftInd], 0);
							else if (cutie[2].flagUp)
								iShowBMP2(cutie[2].x, cutie[2].y, clydeUp[cutie[2].upInd], 0);
							else if (cutie[2].flagDown)
								iShowBMP2(cutie[2].x, cutie[2].y, clydeDown[cutie[2].downInd], 0);
						}
						else if (i == 3)
						{
							if (cutie[3].flagRight)
								iShowBMP2(cutie[3].x, cutie[3].y, pinkyRight[cutie[3].rightInd], 0);
							else if (cutie[3].flagLeft)
								iShowBMP2(cutie[3].x, cutie[3].y, pinkyLeft[cutie[3].leftInd], 0);
							else if (cutie[3].flagUp)
								iShowBMP2(cutie[3].x, cutie[3].y, pinkyUp[cutie[3].upInd], 0);
							else if (cutie[3].flagDown)
								iShowBMP2(cutie[3].x, cutie[3].y, pinkyDown[cutie[3].downInd], 0);
						}
					}
				}
			}
		}
	}
	else if (gameOver)
	{
		iShowBMP(0, 0, goImg[slide]);
		iText(965, 460, pacScore, GLUT_BITMAP_TIMES_ROMAN_24);
	}

}





/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{

}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	if (mainMenu){
		if ((mx >= 700 && mx <= 1000) && (my >= 710 && my <= 760))
		{
			menuInd = 1;
		}
		else if ((mx >= 700 && mx <= 1000) && (my >= 610 && my <= 660))
		{
			menuInd = 2;
		}
		else if ((mx >= 700 && mx <= 960) && (my >= 510 && my <= 560))
		{
			menuInd = 3;
		}
		else if ((mx >= 700 && mx <= 935) && (my >= 410 && my <= 460))
		{
			menuInd = 4;
		}
		else if ((mx >= 700 && mx <= 900) && (my >= 310 && my <= 360))
		{
			menuInd = 5;
		}
		else if ((mx >= 700 && mx <= 890) && (my >= 210 && my <= 260))
		{
			menuInd = 6;
		}
		else
		{
			menuInd = 0;
		}
	}
	else if (selectMaze)
	{
		if ((mx >= 691 && mx <= 1219) && (my >= 780 && my <= 841))
		{
			selMazeInd = 1;
		}
		else if ((mx >= 618 && mx <= 1048) && (my >= 683 && my <= 735))
		{
			selMazeInd = 2;
		}
		else if ((mx >= 705 && mx <= 1043) && (my >= 581 && my <= 643))
		{
			selMazeInd = 3;
		}
		else if ((mx >= 668 && mx <= 941) && (my >= 480 && my <= 541))
		{
			selMazeInd = 4;
		}
		else if ((mx >= 684 && mx <= 1218) && (my >= 380 && my <= 437))
		{
			selMazeInd = 5;
		}
		else if ((mx >= 612 && mx <= 995) && (my >= 277 && my <= 339))
		{
			selMazeInd = 6;
		}
		else if ((mx >= 738 && mx <= 1194) && (my >= 181 && my <= 239))
		{
			selMazeInd = 7;
		}
		else
		{
			selMazeInd = selMazeInd1;
		}
	}
	else if (settings)
	{
		if ((mx >= 785 && mx <= 1128) && (my >= 516 && my <= 583))
		{
			if (soundOn)
				settingsInd = 4;
			else
				settingsInd = 2;
		}
		else if ((mx >= 697 && mx <= 1220) && (my >= 350 && my <= 420))
		{
			if (soundOn)
				settingsInd = 5;
			else
				settingsInd = 3;
		}
		else
		{
			if (soundOn)
				settingsInd = 0;
			else
				settingsInd = 1;
		}
	}
	else if (quit)
	{
		if ((mx >= 526 && mx <= 684) && (my >= 534 && my <= 626))
		{
			slide = 1;
		}
		else if ((mx >= 1288 && mx <= 1373) && (my >= 548 && my <= 622))
		{
			slide = 2;
		}
		else
		{
			slide = 0;
		}
	}
	else if (selBg)
	{
		if ((mx >= 825 && mx <= 1088) && (my >= 638 && my <= 713))
		{
			slideselbg = 1;
		}
		else if ((mx >= 821 && mx <= 1073) && (my >= 528 && my <= 597))
		{
			slideselbg = 2;
		}
		else if ((mx >= 845 && mx <= 1058) && (my >= 409 && my <= 474))
		{
			slideselbg = 3;
		}
		else if ((mx >= 823 && mx <= 1087) && (my >= 292 && my <= 360))
		{
			slideselbg = 4;
		}
		else
		{
			slideselbg = bgInd + 1;
		}
	}
	else if (selectDf)
	{
		if ((mx >= 761 && mx <= 1124) && (my >= 727 && my <= 796))
		{
			slide = 1;
		}
		else if ((mx >= 761 && mx <= 1040) && (my >= 590 && my <= 643))
		{
			slide = 2;
		}
		else if ((mx >= 761 && mx <= 1100) && (my >= 442 && my <= 492))
		{
			slide = 3;
		}
		else
			slide = 0;
	}
}

void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (mainMenu)
		{
			if (menuInd == 1)
			{
				selectDf = true;
				mainMenu = false;
			}
			else if (menuInd == 2)
			{
				highScore = true;
				mainMenu = false;
			}
			else if (menuInd == 3)
			{
				mainMenu = false;
				settings = true;
			}
			else if (menuInd == 4)
			{
				credit = true;
				mainMenu = false;
			}
			else if (menuInd == 5)
			{
				rules = true;
				mainMenu = false;
			}
			else if (menuInd == 6)
			{
				mainMenu = false;
				quit = true;
			}
		}
		else if (settings)
		{
			if ((mx >= 780 && mx <= 1129) && (my >= 664 && my <= 738))
			{
				settingsInd = (++settingsInd) % 2;

				if (settingsInd == 0)
					soundOn = true;
				else
					soundOn = false;
			}
			else if (settingsInd == 2 || settingsInd == 4)
			{
				settings = false;
				selectMaze = true;
			}
			else if (settingsInd == 3 || settingsInd == 5)
			{
				settings = false;
				selBg = true;

			}
		}
		else if (selectMaze)
		{
			if (selMazeInd == 1)
			{
				selMazeInd1 = 1;
				selectMaze = false;
				settings = true;
			}
			else if (selMazeInd == 2)
			{
				selMazeInd1 = 2;
				selectMaze = false;
				settings = true;
			}
			else if (selMazeInd == 3)
			{
				selMazeInd1 = 3;
				selectMaze = false;
				settings = true;
			}
			else if (selMazeInd == 4)
			{
				selMazeInd1 = 4;
				selectMaze = false;
				settings = true;
			}
			else if (selMazeInd == 5)
			{
				selMazeInd1 = 5;
				selectMaze = false;
				settings = true;
			}
			else if (selMazeInd == 6)
			{
				selMazeInd1 = 6;
				selectMaze = false;
				settings = true;
			}
			else if (selMazeInd == 7)
			{
				selMazeInd1 = 7;
				selectMaze = false;
				settings = true;
			}
			else
			{
				selMazeInd = 0;
			}
		}
		else if (selBg)
		{
			if (slideselbg == 1)
			{
				bgInd = 0;
				selBg = false;
				settings = true;
			}
			else if (slideselbg == 2)
			{
				bgInd = 1;
				selBg = false;
				settings = true;
			}
			else if (slideselbg == 3)
			{
				bgInd = 2;
				selBg = false;
				settings = true;
			}
			else if (slideselbg == 4)
			{
				bgInd = 3;
				selBg = false;
				settings = true;
			}
			else
			{
				bgInd = 0;
			}
		}
		else if (quit)
		{
			if (slide == 1)
			{
				exit(0);
			}
			else if (slide == 2)
			{
				quit = false;
				mainMenu = true;
				slide = 0;
			}
		}
		else if (selectDf)
		{
			if(slide==1)
            {
               diffSpeed=4;
            }
            else if(slide == 2)
            {
                diffSpeed=5;
            }
            else if(slide==3)
            {
                diffSpeed=8;
            }
            selectDf = false;
            playGameIntro = true;
            slide = 0;
		}
	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key)
{
	if (splash)
	{
		if (key == '\r')
		{
			splash = false;
			mainMenu = true;
			slide = 0;
		}
		else if (key == 27)
		{
			exit(0);
		}
	}
	else if (settings && pausedMenu)
	{
		if (key == 27)
		{
			settings = false;
			pause = true;
			pausedMenu = false;
		}

	}
	else if (settings)
	{
		if (key == 27)
		{
			menuInd = 0;
			settings = false;
			mainMenu = true;
			slide = 0;
		}
	}
	else if (highScore)
	{
		if (key == 27)
		{
			highScore = false;
			mainMenu = true;
		}
	}

	else if (selectMaze)
	{
		if (key == 27)
		{
			settings = true;
			selectMaze = false;
		}
	}
	else if (credit)
	{
		if (key == 27)
		{
			credit = false;
			mainMenu = true;
		}
	}
	else if (rulesenter)
	{
		if (key == '\r')
		{
			slide = 0;
			rulesenter = false;
			mainMenu = true;
		}
	}
	else if (selectDf)
	{
		if (key == 27)
		{
			mainMenu = true;
			selectDf = false;
			slide = 0;
		}
	}
	else if (playGameIntro)
	{
		if (key == '\r' && len!=0)
		{
			namestr[len] = '\0';
			strcpy(playername, namestr);
			for (int i = 0; namestr[i]; i++) namestr[i] = 0;
			len = 0;
			playGameIntro = false;
			score=0;
			itoa(00,pacScore);

            pacLife=3;
			blueGhost = false;
			cutie[0].blueOn = false;
			cutie[1].blueOn = false;
			cutie[2].blueOn = false;
			cutie[3].blueOn = false;

			iResumeAll();
			playGame = true;
			slide = 0;
		}
		else if (key == 27)
		{
			for (int i = 0; namestr[i]; i++) namestr[i] = 0;
			len = 0;
			playGameIntro = false;
			selectDf = true;
			slide = 0;
		}
		else if (len && key == 8)
		{
			namestr[--len] = '\0';
		}
		else
		{
			namestr[len++] = key;
		}
	}
	else if (selBg)
	{
		if (key == 27)
		{
			selBg = false;
			settings = true;
			slide = 0;
		}
	}
	else if (playGame)
	{
		if (key == 27)
		{
			playGame=false;
			pause = true;
			iPauseAll();
		}
		else if (key == 'C')
		{
			pacLife++;
		}
	}
	else if (pause)
	{
		if (key == '\r')
		{
			pause = false;
			playGame = true;
			iResumeAll();
		}
		else if (key == 's' || key == 'S')
		{
			pause = false;
			settings = true;
			pausedMenu = true;
		}
		else if(key==27)
        {
            pause=false;
            mainMenu=true;
            reset();
        }

	}
	else if (gameOver)
	{
		if (key == '\r')
		{
			gameOver = false;
			mainMenu = true;
			slide = 0;
			pacLife = 1;
			score = 0;
			itoa(00, pacScore);
			reset();
		}
	}
}
void iPauseAll()
{
    for(int i=1;i<=5;i++)
    {
        iPauseTimer(i);
    }
}
void iResumeAll()
{
    for(int i=1;i<=5;i++)
    {
        iResumeTimer(i);
    }
}
/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{


	if (key == GLUT_KEY_RIGHT)
	{
		if (playGame)
		{
			if (!(pac.x % mazepixel) && !(pac.y % mazepixel))
			{
				pac.downCount = false;
				pac.upCount = false;
				pac.leftCount = false;
				pac.rightCount = true;
			}
			else
			{
				pac.trigRight = true;
				pac.trigLeft = false;
				pac.trigDown = false;
				pac.trigUp = false;
			}
		}
	}
	if (key == GLUT_KEY_LEFT)
	{
		if (playGame)
		{
			if (!(pac.x % mazepixel) && !(pac.y % mazepixel))
			{
				pac.downCount = false;
				pac.rightCount = false;
				pac.upCount = false;
				pac.leftCount = true;
			}
			else
			{
				pac.trigRight = false;
				pac.trigLeft = true;
				pac.trigDown = false;
				pac.trigUp = false;
			}
		}
	}
	if (key == GLUT_KEY_UP)
	{
		if (mainMenu)
		{
			menuInd--;
			if (menuInd < 1) menuInd = 6;
		}
		else if (playGame)
		{
			if (!(pac.y % mazepixel) && !(pac.x % mazepixel))
			{
				pac.downCount = false;
				pac.rightCount = false;
				pac.leftCount = false;
				pac.upCount = true;
			}
			else
			{
				pac.trigRight = false;
				pac.trigLeft = false;
				pac.trigDown = false;
				pac.trigUp = true;
			}
		}
	}
	if (key == GLUT_KEY_DOWN)
	{
		if (mainMenu)
		{
			menuInd++;
			if (menuInd > 6)
				menuInd = 1;
		}
		else if (playGame)
		{
			if (!(pac.y % mazepixel) && !(pac.x % mazepixel))
			{
				pac.rightCount = false;
				pac.leftCount = false;
				pac.upCount = false;
				pac.downCount = true;
			}
			else
			{
				pac.trigRight = false;
				pac.trigLeft = false;
				pac.trigDown = true;
				pac.trigUp = false;
			}
		}
	}
	if (key == GLUT_KEY_HOME)
	{

	}

}
void pacmove()
{
	if (pac.rightCount)
	{
		pac.right++;
		if (!ara[mazeLevel][cellY][cellX + 1])
		{
			pac.x += pacspeed;
			if (!(pac.right % 2))
				pac.rightInd++;

			if (!(pac.x % mazepixel))
				cellX++;

			if (cellX == 18 && cellY == 9)
			{
				if (!mazeExitFlagRight)
				{
					cellX = 17;
					mazeExitFlagRight = true;
				}
				else
				{
					cellX = 0;
					cellY = 9;
					pac.x = mazeX + (cellX)* mazepixel;
					pac.y = mazeY + (20 - cellY) * mazepixel;
					mazeExitFlagRight = false;
				}
			}
		}
		if (pac.rightInd > 1) pac.rightInd = 0;

	}
	else if (pac.leftCount)
	{
		pac.left++;
		if (!ara[mazeLevel][cellY][cellX - 1])
		{
			pac.x -= pacspeed;
			if (!(pac.left % 2))
				pac.leftInd++;

			if (!(pac.x % mazepixel))
				cellX--;

			if (cellX == 0 && cellY == 9)
			{
				if (!mazeExitFlagLeft)
				{
					cellX = 1;
					mazeExitFlagLeft = true;
				}
				else
				{
					cellX = 18;
					cellY = 9;
					pac.x = mazeX + (cellX)* mazepixel;
					pac.y = mazeY + (20 - cellY) * mazepixel;
					mazeExitFlagLeft = false;
				}
			}
		}

		if (pac.leftInd > 1)pac.leftInd = 0;
	}
	else if (pac.upCount)
	{
		pac.up++;
		if (!ara[mazeLevel][cellY - 1][cellX])
		{
			pac.y += pacspeed;
			if (!(pac.up % 2))
				pac.upInd++;

			if (!(pac.y % mazepixel))
				cellY--;
		}
		if (pac.upInd > 1)pac.upInd = 0;
	}
	else if (pac.downCount)
	{
		pac.down++;
		if (!ara[mazeLevel][cellY + 1][cellX])
		{
			pac.y -= pacspeed;
			if (!(pac.down % 2))
				pac.downInd++;

			if (!(pac.y % mazepixel))
				cellY++;
		}
		if (pac.downInd > 1) pac.downInd = 0;
	}
}
void introchange()
{
	if (startintro)
	{
		intro++;
		if (intro > 283)
		{
			//intro = 1;
			startintro = false;
			splash=true;
			iPauseTimer(0);
		}
	}
}
void setstr()
{
	FILE *fp;
	fp = fopen("sprite\\introFilePath.txt", "r");
	for (int i = 1; i <= 283; i++)
	{
		str[i] = (char*)malloc(sizeof(char)* 100);
		fscanf(fp, "%s", str[i]);
	}
	fclose(fp);

	fp = fopen("sprite\\pacdeath.txt", "r");
	for (int i = 0; i < 12; i++)
	{
		pacdeath[i] = (char*)malloc(sizeof(char)* 50);
		fscanf(fp, "%s", pacdeath[i]);
	}
	fclose(fp);

	fp = fopen("sprite\\fruits.txt", "r");
	for (int i = 0; i < 7; i++)
	{
		fruit[i] = (char*)malloc(sizeof(char)* 50);
		fscanf(fp, "%s", fruit[i]);
	}
	fclose(fp);
	fp = fopen("sprite\\levelChange.txt", "r");
	for (int i = 1; i <= 275; i++)
	{
		intermission[i] = (char*)malloc(sizeof(char)* 50);
		fscanf(fp, "%s", intermission[i]);
	}
	fclose(fp);
}
int calcDist(int x1, int y1, int x2, int y2)
{
	int dx = x1 - x2;
	int dy = y1 - y2;
	return dx*dx + dy*dy;
}
void setMazeAra()
{
	int i, c, p, j, t = 0, z;
	brickNum = 0;
	foodNum = 0;

	for (i = 20, c = 0, t = 0; i >= 0; i--)
	{
		for (j = 0; j<19; j++)
		{
			if (ara[mazeLevel][i][j])
			{
				brickNum = c++;
				mazeXcor[brickNum] = mazepixel*j;
				mazeYcor[brickNum] = mazepixel*(20 - i);
			}
			else
			{
				foodNum = t++;
				foodXcor[foodNum][0] = mazepixel*j;
				foodYcor[foodNum] = mazepixel*(20 - i);
				foodXcor[foodNum][1] = 0;
			}
		}
	}
	for (int i = 0; i < 201; i++)
	{
		fruitGen[i] = 0;
	}
	printf("%d %d\n", brickNum, foodNum);
	if (mazeLevel == 0)
	{
		foodXcor[8][1] = -1;
		foodXcor[82][1] = -1;
		foodXcor[83][1] = -1;
		foodXcor[84][1] = -1;
		foodXcor[94][1] = -1;
		foodXcor[95][1] = -1;
		foodXcor[96][1] = -1;
		foodXcor[123][1] = -1;
		foodXcor[124][1] = -1;
		foodXcor[125][1] = -1;
		foodXcor[135][1] = -1;
		foodXcor[136][1] = -1;
		foodXcor[137][1] = -1;
	}
	cellX = 9;
	cellY = 19;
	pac.x = mazeX + (cellX)*mazepixel;
	pac.y = mazeY + (20 - cellY)*mazepixel;

	pac.downCount=false;
	pac.rightCount=false;
	pac.upCount=false;
	pac.leftCount=false;

}
void checkTrigger()
{
	if (!totalFool)
	{
		if (mazeLevel == 0)
		{
			mazeLevel = 1;
			totalFool = 199;
			ghostIniCords();
			setMazeAra();
			scatter=true;
			chase=false;
		}
		else if(mazeLevel == 1)
        {
            chase=false;
            scatter=true;
            mazeLevel=0;
        }
	}
	if(mazeLevel==1)
    {
        artiScore++;
        if(artiScore>2500)
        {
            chase=true;
            scatter=false;
        }
    }
	foodhelp++;
	if (pac.trigRight && !(pac.x % mazepixel) && !(pac.y % mazepixel) && !ara[mazeLevel][cellY][cellX + 1])
	{
		pac.downCount = false;
		pac.upCount = false;
		pac.leftCount = false;
		pac.rightCount = true;
		pac.trigRight = false;
	}
	else if (pac.trigLeft && !(pac.x % mazepixel) && !(pac.y % mazepixel) && !ara[mazeLevel][cellY][cellX - 1])
	{
		pac.downCount = false;
		pac.rightCount = false;
		pac.upCount = false;
		pac.leftCount = true;
		pac.trigLeft = false;
	}
	else if (pac.trigUp && !(pac.x % mazepixel) && !(pac.y % mazepixel) && !ara[mazeLevel][cellY - 1][cellX])
	{
		pac.downCount = false;
		pac.rightCount = false;
		pac.leftCount = false;
		pac.upCount = true;
		pac.trigUp = false;
	}
	else if (pac.trigDown && !(pac.x % mazepixel) && !(pac.y % mazepixel) && !ara[mazeLevel][cellY + 1][cellX])
	{
		pac.rightCount = false;
		pac.leftCount = false;
		pac.upCount = false;
		pac.downCount = true;
		pac.trigDown = false;
	}


	if (!(foodhelp % timeToGenFood) && foodXcor[*foodCor][1] != -2 && foodXcor[*foodCor][1] != 0)
	{
		foodCor = &fruitGen[rand() % (t - 1)];
		foodXcor[*foodCor][1] = -2;
		randGen = rand() % 7;
	}

	for (int i = 0; i <= foodNum; i++)
	{
		if ((pac.x == (foodXcor[i][0] + mazeX) && pac.y == (foodYcor[i] + mazeY)) && foodXcor[i][1] != -1)
		{
			if (foodXcor[i][1] == -2)
			{
				if (randGen == 6)
				{
					pacLife++;
				}
				foodXcor[i][1] = -1;
				score += 300;
				itoa(score, pacScore);
			}
			else
			{
				printf("%d\n", totalFool);
				totalFool--;
				foodXcor[i][1] = -1;
				score += 10;
				itoa(score, pacScore);
				fruitGen[t++] = i;
				if(score>1200)
                {
                    chase=true;
                    scatter=false;
                }
			}

			if ((i == 41 || i == 55 || i == 179 || i == 184) && mazeLevel == 0)
			{

				blueScore = -1;
				score += 40;
				blueGhost = 10;  //add foodXcor[i][1]!=-2
				for (int i = 0; i < 4; i++)
					cutie[i].blueOn = true;
			}
			else if ((i == 41 || i == 55 || i == 156 || i == 165) && mazeLevel == 1)
			{
				blueScore = -1;
				score += 40;
				blueGhost = 10;  //add foodXcor[i][1]!=-2
				for (int i = 0; i < 4; i++)
					cutie[i].blueOn = true;
			}
		}
	}
	if (blueGhost && (cutie[0].speed != 2 || cutie[1].speed != 2 || cutie[2].speed != 2 || cutie[3].speed != 2))
	{
		for (int i = 0; i < 4; i++)
		{
			if (cutie[i].blueOn)
			{
				if (!(cutie[i].x % 40) && !(cutie[i].y % 40))
				{
					cutie[i].speed = 2;
				}
			}
		}
	}
	else if (!blueGhost && (cutie[0].speed != diffSpeed || cutie[1].speed != diffSpeed || cutie[2].speed != diffSpeed || cutie[3].speed != diffSpeed))
	{
		for (int i = 0; i < 4; i++)
		{
			if (!(cutie[i].x % 40) && !(cutie[i].y % 40))
			{
				cutie[i].speed = diffSpeed;
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (abs(pac.x - cutie[i].x) <= 30 && abs(pac.y - cutie[i].y) <= 30)
		{
			if (!blueGhost || !cutie[i].blueOn)
			{
				pacDead = true;
				iPauseTimer(3);
				iPauseTimer(2);
			}
			else
			{
				if (cutie[i].blueOn)
				{
					scoreX = cutie[i].x;
					scoreY = cutie[i].y;
					blueScore++;
					score += (200) * pow((double)2, blueScore);
					cutie[i].blueOn = false;
					if (i == 0)
					{
						cutie[0].cellX = 9;
						cutie[0].cellY = 7;
						cutie[0].x = mazeX + (cutie[0].cellX)*mazepixel;
						cutie[0].y = mazeY + (20 - cutie[0].cellY)*mazepixel;
						cutie[0].flagRight = true;
						cutie[0].speed = diffSpeed;
					}
					else if (i == 1)
					{
						cutie[1].cellX = 9;
						cutie[1].cellY = 9;
						cutie[1].x = mazeX + (cutie[1].cellX)*mazepixel;
						cutie[1].y = mazeY + (20 - cutie[1].cellY)*mazepixel;
						cutie[1].flagUp = true;
						cutie[1].speed = diffSpeed;
					}
					else if (i == 2)
					{
						cutie[2].cellX = 10;
						cutie[2].cellY = 9;
						cutie[2].x = mazeX + (cutie[2].cellX)*mazepixel;
						cutie[2].y = mazeY + (20 - cutie[2].cellY)*mazepixel;
						cutie[2].flagRight = true;
						cutie[2].speed = diffSpeed;
					}
					else if (i == 3)
					{
						cutie[3].cellX = 8;
						cutie[3].cellY = 9;
						cutie[3].x = mazeX + (cutie[3].cellX)*mazepixel;
						cutie[3].y = mazeY + (20 - cutie[3].cellY)*mazepixel;
						cutie[3].flagRight = true;
						cutie[3].speed = diffSpeed;
					}
				}
			}
		}

	}
}
void deathScene()
{
	if (pacDead)
	{
		deadSceneCount++;
		if (deadSceneCount > 11)
		{
			deadSceneCount = 0;
			pacDead = false;
			cellX = 9;
			cellY = 19;
			pac.x = mazeX + (cellX)*mazepixel;
			pac.y = mazeY + (20 - cellY)*mazepixel;
			pac.rightCount = false;
			pac.leftCount = false;
			pac.downCount = false;
			pac.upCount = false;
			pac.trigDown = false;
			pac.trigLeft = false;
			pac.trigRight = false;
			pac.trigUp = false;
			pacLife--;
			ghostIniCords();
			blueGhost = false;
			cutie[0].blueOn = false;
			cutie[1].blueOn = false;
			cutie[2].blueOn = false;
			cutie[3].blueOn = false;
			Sleep(800);
			if(pacLife==0)
            {
                totalFool=188;
                chase=false;
                scatter=true;
                readData();
            }
			iResumeTimer(2);
			iResumeTimer(3);
		}
	}
}
void frozTimeCheck()
{
	if (blueGhost)
	{
		blueGhost--;
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			cutie[i].blueOn = false;
		}
	}
}
void ghostIniCords()
{
	cutie[0].cellX = 9;                //Inky
	cutie[0].cellY = 7;
	cutie[0].x = mazeX + (cutie[0].cellX)*mazepixel;
	cutie[0].y = mazeY + (20 - cutie[0].cellY)*mazepixel;
	cutie[0].flagRight = true;
	cutie[0].speed = diffSpeed;

	cutie[1].cellX = 9;                //Blinky
	cutie[1].cellY = 9;
	cutie[1].x = mazeX + (cutie[1].cellX)*mazepixel;
	cutie[1].y = mazeY + (20 - cutie[1].cellY)*mazepixel;
	cutie[1].flagUp = true;
	cutie[1].speed = diffSpeed;

	cutie[2].cellX = 10;               //Pinky
	cutie[2].cellY = 9;
	cutie[2].x = mazeX + (cutie[2].cellX)*mazepixel;
	cutie[2].y = mazeY + (20 - cutie[2].cellY)*mazepixel;
	cutie[2].flagRight = true;
	cutie[2].speed = diffSpeed;

	cutie[3].cellX = 8;					//Clyde
	cutie[3].cellY = 9;
	cutie[3].x = mazeX + (cutie[3].cellX)*mazepixel;
	cutie[3].y = mazeY + (20 - cutie[3].cellY)*mazepixel;
	cutie[3].flagRight = true;
	cutie[3].speed = diffSpeed;
}
void dirGen2(int ara[], int dir, int ghostIdx)
{
	if (ara[dir] == 0)
	{
		cutie[ghostIdx].flagLeft = true;
	}
	else if (ara[dir] == 1)
	{
		cutie[ghostIdx].flagRight = true;
	}
	else if (ara[dir] == 2)
	{
		cutie[ghostIdx].flagUp = true;
	}
	else if (ara[dir] == 3)
	{
		cutie[ghostIdx].flagDown = true;
	}
}
void directionGen(int a, int ghostIdx)   //--->MEGA EDIT FOR AI
{
	time_t t;        // 0 1 2 3   Inky Blinky Clyde Pinky
	srand((unsigned)time(&t));
	int dir;
	cutie[ghostIdx].flagDown = false;
	cutie[ghostIdx].flagLeft = false;
	cutie[ghostIdx].flagRight = false;      //2301 UDLR  0123 LRUD
	cutie[ghostIdx].flagUp = false;
	int para[4] = { -1, -1, -1, -1 };
	bool flag = false;
	int distUp = calcDist(cutie[ghostIdx].x, cutie[ghostIdx].y + mazepixel, pac.x, pac.y);
	int distDown = calcDist(cutie[ghostIdx].x, cutie[ghostIdx].y - mazepixel, pac.x, pac.y);
	int distLeft = calcDist(cutie[ghostIdx].x - mazepixel, cutie[ghostIdx].y, pac.x, pac.y);
	int distRight = calcDist(cutie[ghostIdx].x + mazepixel, cutie[ghostIdx].y, pac.x, pac.y);
	int currentDist = calcDist(cutie[ghostIdx].x, cutie[ghostIdx].y, pac.x, pac.y);
	if (a > 3)
	{
		if (!ara[mazeLevel][cutie[ghostIdx].cellY - 1][cutie[ghostIdx].cellX] && !flag)  //UP
		{
			if (distUp < currentDist && !flag)
			{
				cutie[ghostIdx].flagUp = true;
				flag = true;
			}
		}
		if (!ara[mazeLevel][cutie[ghostIdx].cellY + 1][cutie[ghostIdx].cellX] && !flag)  //DOWN
		{
			if (distDown < currentDist)
			{
				cutie[ghostIdx].flagDown = true;
				flag = true;
			}
		}
		if (!ara[mazeLevel][cutie[ghostIdx].cellY][cutie[ghostIdx].cellX - 1] && !flag)
		{
			if (distLeft < currentDist)
			{
				cutie[ghostIdx].flagLeft = true;
				flag = true;
			}
		}
		if (!ara[mazeLevel][cutie[ghostIdx].cellY][cutie[ghostIdx].cellX + 1] && !flag)
		{
			if (distRight < currentDist)
			{
				cutie[ghostIdx].flagRight = true;
				flag = true;
			}
		}
		if (!flag)
		{
			if (!ara[mazeLevel][cutie[ghostIdx].cellY - 1][cutie[ghostIdx].cellX])
			{
				para[2] = 2;
			}
			if (!ara[mazeLevel][cutie[ghostIdx].cellY + 1][cutie[ghostIdx].cellX])
			{
				para[3] = 3;
			}
			if (!ara[mazeLevel][cutie[ghostIdx].cellY][cutie[ghostIdx].cellX - 1])
			{
				para[0] = 0;
			}
			if (!ara[mazeLevel][cutie[ghostIdx].cellY][cutie[ghostIdx].cellX + 1])
			{
				para[1] = 1;
			}
			for (dir = rand() % 4; para[dir] == -1; dir = rand() % 4);
			dirGen2(para, dir, ghostIdx);
		}

	}
	else
	{
		if (a == 0)
			cutie[ghostIdx].flagLeft = true;
		else if (a == 1)
			cutie[ghostIdx].flagRight = true;
		else if (a == 2)
			cutie[ghostIdx].flagUp = true;
		else if (a == 3)
			cutie[ghostIdx].flagDown = true;
	}
}
void moveghost()
{
	if (playGame)
	{
		for (int ghostIdx = 0; ghostIdx < 4; ghostIdx++)
		{
                int playerX = pac.x;
                int playerY = pac.y;
            if(chase)
            {
                if (ghostIdx == 3)     //0123 IBCP
                {
                    if (pac.rightCount)
                        playerX += mazepixel * 4;
                    else if (pac.leftCount)
                        playerX -= mazepixel * 4;
                    else if (pac.upCount)
                        playerY += mazepixel * 4;
                    else if (pac.downCount)
                        playerY -= mazepixel * 4;
                }
                else if (ghostIdx == 0)
                {
                    if (pac.rightCount)
                        playerX -= mazepixel * 4;
                    else if (pac.leftCount)
                        playerX += mazepixel * 4;
                    else if (pac.upCount)
                        playerY -= mazepixel * 4;
                    else if (pac.downCount)
                        playerY += mazepixel * 4;
                }
                else if(ghostIdx==2)
                {
                    playerY+=mazepixel*4;
                }
            }
            else if(scatter)
            {
                if(ghostIdx==0)
                {
                    playerX=mazeX;
                    playerY=mazeY;
                }
                else if(ghostIdx==1)
                {
                    playerX=mazeX+mazeWidth;
                    playerY=mazeY;
                }
                else if(ghostIdx==2)
                {
                    playerX=mazeX;
                    playerY=mazeY+mazeHeight;
                }
                else if(ghostIdx==3)
                {
                    playerX=mazeX+mazeWidth;
                    playerY=mazeY+mazeHeight;
                }
            }
			int distUp = calcDist(cutie[ghostIdx].x, cutie[ghostIdx].y + mazepixel, playerX, playerY);
			int distDown = calcDist(cutie[ghostIdx].x, cutie[ghostIdx].y - mazepixel, playerX, playerY);
			int distLeft = calcDist(cutie[ghostIdx].x - mazepixel, cutie[ghostIdx].y, playerX, playerY);
			int distRight = calcDist(cutie[ghostIdx].x + mazepixel, cutie[ghostIdx].y, playerX, playerY);
			int currentDist = calcDist(cutie[ghostIdx].x, cutie[ghostIdx].y, playerX, playerY);
			if (cutie[ghostIdx].flagRight)												 //0123 LRUD
			{
				if (!ara[mazeLevel][cutie[ghostIdx].cellY][cutie[ghostIdx].cellX + 1])
				{
					cutie[ghostIdx].x += cutie[ghostIdx].speed;
					cutie[ghostIdx].right++;											//used for animation time control
					if (!(cutie[ghostIdx].right % 5))
					{
						cutie[ghostIdx].rightInd++;
					}
					if (cutie[ghostIdx].rightInd > 1)
                        cutie[ghostIdx].rightInd = 0;

					cutie[ghostIdx].flagRight = true;
					cutie[ghostIdx].flagLeft = false;
					cutie[ghostIdx].flagDown = false;
					cutie[ghostIdx].flagUp = false;
					if (!(cutie[ghostIdx].x % mazepixel))							    //move to another cell only when multiple of 40px covered
					{
						cutie[ghostIdx].cellX++;

						if (!ara[mazeLevel][cutie[ghostIdx].cellY - 1][cutie[ghostIdx].cellX])
						{
						    if(cutie[ghostIdx].cellX==9 && cutie[ghostIdx].cellY==9)
                                directionGen(2,ghostIdx);
							else if (distUp < currentDist)
							{
								directionGen(2, ghostIdx);
							}
						}
						else if (!ara[mazeLevel][cutie[ghostIdx].cellY + 1][cutie[ghostIdx].cellX])
						{
						    if(cutie[ghostIdx].cellX==9 && cutie[ghostIdx].cellY==7)
                            {
                                if(rand()%2)
                                    directionGen(0,ghostIdx);
                                else
                                    directionGen(1,ghostIdx);
                            }
							else if (distDown < currentDist)
							{
								directionGen(3, ghostIdx);
							}
						}
					}

					if (cutie[ghostIdx].cellX == 18 && cutie[ghostIdx].cellY == 9)
					{
						cutie[ghostIdx].cellX = 0;
						cutie[ghostIdx].cellY = 9;
						cutie[ghostIdx].x = mazeX + (cutie[ghostIdx].cellX)*mazepixel;
						cutie[ghostIdx].y = mazeY + (20 - cutie[ghostIdx].cellY)*mazepixel;
					}

				}
				else
					directionGen(4, ghostIdx);
			}
			else if (cutie[ghostIdx].flagDown)
			{
				if (!ara[mazeLevel][cutie[ghostIdx].cellY + 1][cutie[ghostIdx].cellX])
				{
					cutie[ghostIdx].y -= cutie[ghostIdx].speed;
					cutie[ghostIdx].down++;
					if (!(cutie[ghostIdx].down % 5))
					{
						cutie[ghostIdx].downInd++;
					}
					if (cutie[ghostIdx].downInd > 1) cutie[ghostIdx].downInd = 0;
					cutie[ghostIdx].flagRight = false;
					cutie[ghostIdx].flagLeft = false;
					cutie[ghostIdx].flagDown = true;
					cutie[ghostIdx].flagUp = false;
					if (!(cutie[ghostIdx].y % mazepixel))
					{
						cutie[ghostIdx].cellY++;

						if (!ara[mazeLevel][cutie[ghostIdx].cellY][cutie[ghostIdx].cellX + 1])
						{
							if (distRight < currentDist)
							{
								directionGen(1, ghostIdx);
							}
						}
						else if (!ara[mazeLevel][cutie[ghostIdx].cellY][cutie[ghostIdx].cellX - 1])
						{
							if (distLeft < currentDist)
							{
								directionGen(0, ghostIdx);
							}
						}
					}
				}

				else directionGen(4, ghostIdx);
			}
			else if (cutie[ghostIdx].flagLeft)
			{
				if (!ara[mazeLevel][cutie[ghostIdx].cellY][cutie[ghostIdx].cellX - 1])
				{
					cutie[ghostIdx].x -= cutie[ghostIdx].speed;
					cutie[ghostIdx].left++;
					if (!(cutie[ghostIdx].left % 5))
					{
						cutie[ghostIdx].leftInd++;
					}
					if (cutie[ghostIdx].leftInd > 1) cutie[ghostIdx].leftInd = 0;
					cutie[ghostIdx].flagRight = false;
					cutie[ghostIdx].flagLeft = true;
					cutie[ghostIdx].flagDown = false;
					cutie[ghostIdx].flagUp = false;
					if (!(cutie[ghostIdx].x % mazepixel))
					{
						cutie[ghostIdx].cellX--;
						if (!ara[mazeLevel][cutie[ghostIdx].cellY - 1][cutie[ghostIdx].cellX])
						{
						    if(cutie[ghostIdx].cellX==9 && cutie[ghostIdx].cellY==9)
                                directionGen(2,ghostIdx);
							if (distUp < currentDist)
							{
								directionGen(2, ghostIdx);
							}
						}
						else if (!ara[mazeLevel][cutie[ghostIdx].cellY + 1][cutie[ghostIdx].cellX])
						{
						    if(cutie[ghostIdx].cellX==9 && cutie[ghostIdx].cellY==7)
                            {
                                if(rand()%2)
                                    directionGen(0,ghostIdx);
                                else
                                    directionGen(1,ghostIdx);
                            }
							else if (distDown < currentDist)
							{
								directionGen(3, ghostIdx);
							}
						}
					}
					if (cutie[ghostIdx].cellX == 0 && cutie[ghostIdx].cellY == 9)
					{
						cutie[ghostIdx].cellX = 18;
						cutie[ghostIdx].cellY = 9;
						cutie[ghostIdx].x = mazeX + (cutie[ghostIdx].cellX)*mazepixel;
						cutie[ghostIdx].y = mazeY + (20 - cutie[ghostIdx].cellY)*mazepixel;

					}

				}
				else directionGen(4, ghostIdx);
			}
			else if (cutie[ghostIdx].flagUp)
			{
				if (!ara[mazeLevel][cutie[ghostIdx].cellY - 1][cutie[ghostIdx].cellX])
				{
					cutie[ghostIdx].y += cutie[ghostIdx].speed;
					cutie[ghostIdx].up++;
					if (!(cutie[ghostIdx].up % 5))
					{
						cutie[ghostIdx].upInd++;
					}
					if (cutie[ghostIdx].upInd > 1) cutie[ghostIdx].upInd = 0;
					cutie[ghostIdx].flagRight = false;
					cutie[ghostIdx].flagLeft = false;
					cutie[ghostIdx].flagDown = false;
					cutie[ghostIdx].flagUp = true;
					if (!(cutie[ghostIdx].y % mazepixel))
					{
						cutie[ghostIdx].cellY--;
						if (!ara[mazeLevel][cutie[ghostIdx].cellY][cutie[ghostIdx].cellX + 1])
						{
						    if(cutie[ghostIdx].cellX==9 && cutie[ghostIdx].cellY==7)
                            {
                                if(rand()%2)
                                    directionGen(0,ghostIdx);
                                else
                                    directionGen(1,ghostIdx);
                            }
							else if (distRight < currentDist)
							{
								directionGen(1, ghostIdx);
							}
						}
						else if (!ara[mazeLevel][cutie[ghostIdx].cellY][cutie[ghostIdx].cellX - 1])
						{
							if (distLeft < currentDist)
							{
								directionGen(0, ghostIdx);
							}
						}
					}

				}
				else directionGen(4, ghostIdx);
			}
		}
	}
}
void change()
{
	if (playGameIntro || splash || pause)
	{
		slide = (++slide) % 2;
	}
	else if (rules)
	{
		t_rakib++;
		if (slide < 13 && !(t_rakib % 4))
			slide++;
		if (slide == 13)
		{
			rules = false;
			rulesenter = true;
			slide = 0;
		}
	}
	else if (rulesenter || gameOver)
	{
		slide = (++slide) % 4;
	}
}
void reset()
{
	ghostIniCords();
	setMazeAra();
}
void readData()
{
	FILE *fp;
	char ch;
	line = 0;
	if (score != 0)
	{
		//Sub write
		fp = fopen("subsidiary.txt", "a");
		fprintf(fp, "%s %d\n", playername, score);
		fclose(fp);
	}
	//count line
	fp = fopen("subsidiary.txt", "r");
	while (fscanf(fp, "%c", &ch) == 1)
	{
		if (ch == '\n') line++;
	}
	fclose(fp);
	//Store data
	fp = fopen("subsidiary.txt", "r");
	name = (char**)malloc(sizeof(char*)*line);
	number = (int*)malloc(sizeof(int)*line);
	for (int i = 0; i<line; i++)
	{
		name[i] = (char*)malloc(sizeof(char)* 20);
		fscanf(fp, " %s %d", name[i], &number[i]);
	}
	fclose(fp);
	//Sort data
	for (int i = 0; i<line; i++)
	{
		for (int j = 0; j<line; j++)
		{
			if (number[i]>number[j])
			{
				int t = number[i];
				number[i] = number[j];
				number[j] = t;
				char *p = name[i];
				name[i] = name[j];
				name[j] = p;
			}
		}
	}
	//Write Data
	fp = fopen("highScore.txt", "w");
	for (int i = 0; i < line; i++)
	{
		fprintf(fp, "%s %d\n", name[i], number[i]);
	}
	fclose(fp);
}
int main()
{
	readData();
	setstr();
	setMazeAra();
	ghostIniCords();

    iSetTimer(20, introchange);
	iSetTimer(10, checkTrigger);
	iSetTimer(pactime, pacmove);
	iSetTimer(20, moveghost);
	iSetTimer(1000, frozTimeCheck);
	iSetTimer(120, deathScene);
	iSetTimer(300, change);
	iInitialize(screenwidth, screenheight, "PACMAN");
    iStart();
	///updated see the documentations
	return 0;
}
