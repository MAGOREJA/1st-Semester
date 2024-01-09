#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iomanip>

using namespace std;

void gotoxy(int x, int y);

void printBox();
char menu();
void About();
void Instructions();
void maze();

void character();
void eraseCharacter();
void movePlayerLeft();
void movePlayerRight();
void movePlayerDown();
void movePlayerUp();

void printfire();
void removefire();
void movefire();

void printfire2();
void removefire2();
void movefire2();

void enemy();
void moveEnemy();
void eraseEnemy();
void drawEnemyBullet();
void moveEnemyBullet(int &eX, int &eY, int &pX, int &pY);
void removeEnemyBullet();

void enemy2();
void moveEnemy2();
void eraseEnemy2();
void moveEnemyBullet2(int &eX2, int &eY2, int &pX, int &pY);
void drawEnemyBullet2();

void eraseEnemy3();
void enemy3();
void moveEnemy3();

void displayScore();

bool WinnerLoserCheck();    // function for checking game winner
void winMsg(int x, int y);  // function for printing win message
void loseMsg(int x, int y); // function for printing losing message
void border(int x, int y);  // function for printing border around messages

char getCharAtxy(short int x, short int y);

int eX = 95, eY = 7;
int eX2 = 68, eY2 = 14;
int eX3 = 6, eY3 = 6;
int pX = 128, pY = 29;
int scoreX = 40, scoreY = 36;
int enemy1_Back, enemy2_Back, enemy3_Back;
int bX = pX + 15;
int bY = pY + 2;
bool bulletActive = false;
char bulletDir = 'r';
int Enemylife = 0;
int Enemy2life = 0;
int Enemy3life = 0;

int enemyX = 0;
int enemyY = 0;
int enemyX2 = 0;
int enemyY2 = 0;
bool enemi2 = true;
bool enemi3 = true;

int Showscore = 500;
int EnemyLeft = 3;
int CountHealth = 0;

string setcolor(unsigned short color)
{
   HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hcon, color);
   return "";
}
int health2 = 100;
int black = 0, blue = 1, green = 2, cyan = 3, red = 4, magenta = 5, brown = 6, lightwhite = 7, darkwhite = 8, lightblue = 9, lightgreen = 10, lightcyan = 11, lightred = 12, lightmagenta = 13, yellow = 14, white = 15;

main()
{
   while (true)
   {
      system("cls");
      char option; // variable for options

      option = menu(); // main menu

      if (option == '1') // for option 1
      {
         system("cls");
         maze();
         character();
         enemy();
         enemy2();
         while (true)
         {
            if (GetAsyncKeyState(VK_LEFT))
            {
               movePlayerLeft();
            }
            if (GetAsyncKeyState(VK_RIGHT))
            {
               movePlayerRight();
            }
            if (GetAsyncKeyState(VK_UP))
            {
               movePlayerUp();
            }
            if (GetAsyncKeyState(VK_DOWN))
            {
               movePlayerDown();
            }
            if (GetAsyncKeyState(VK_SPACE))
            {
               if (!bulletActive)
               {
                  bX = pX - 2;
                  bY = pY + 1;
                  bulletActive = true;

                  bulletDir = 'r';
               }
            }
            if (GetAsyncKeyState(VK_RSHIFT))
            {
               if (!bulletActive)
               {
                  bX = pX;
                  bY = pY + 2;
                  bulletActive = true;
                  bulletDir = 'u';
               }
            }
            if (bulletActive && (bX + 3 <= 122))
            {
               movefire();
            }
            else
            {
               gotoxy(bX + 17, bY);
               cout << "  ";
               gotoxy(bX + 17, bY + 1);
               cout << "  ";
               gotoxy(bX + 17, bY + 2);
               cout << "  ";
               gotoxy(bX + 17, bY + 3);
               cout << "  ";
               bulletActive = false;
            }

            if (Enemylife < 5 && Enemy2life >= 5)
            {
               moveEnemy();
               moveEnemyBullet(eX, eY, pX, pY);
               gotoxy(123, 26);
               cout << "                    " << endl;
               EnemyLeft = 2;
            }
            else
            {
               eraseEnemy();
               
            }
            if (Enemy2life < 5)
            {
               moveEnemy2();
               if (Enemylife >= 5)
               {
                  gotoxy(123, 21);
                  cout << "                    " << endl;
                  EnemyLeft = 1;
               }
            }
            else
            {
               eraseEnemy2();
            }
            if (Enemy3life < 5)
            {
               moveEnemy3();
               moveEnemyBullet2(eX3, eX3, pX, pY);
               EnemyLeft = 1;
            }
            else
            {
               eraseEnemy3();
            }
            Sleep(20);
            displayScore();
            WinnerLoserCheck();
            if (WinnerLoserCheck()) // checking for winner or loser
            {
               // game over
               break; // breaking game loop
            }
         }
      }
      else if (option == '2') // for option 2
      {
         Instructions(); // instructions
      }
      else if (option == '3') // for option 3
      {
         About(); // about
      }
      else if (option == '4') // for option 4
      {
         break; // exit
      }

      gotoxy(1, 27); // taking cursor below on screen
   }
}

void maze()
{
   setcolor(5);
   cout << endl;
   cout << "################################################################################################################################################ " << endl;
   cout << "#                            .' \\/_  _//_  _/.' \\ ,'_/ / //7  ,' \\ / |/ /  /_  _// //_  _/.' \\ / |/ /                                          # " << endl;
   cout << "#                           / o / / /   / / / o // /_ /  ,'  / o |/ || /    / / / /  / / / o // || /                                           # " << endl;
   cout << "#                          /_n_/ /_/   /_/ /_n_/ |__//_/\\\\   |_,'/_/|_/    /_/ /_/  /_/ /_n_//_/|_/                                            # " << endl;
   cout << "################################################################################################################################################ " << endl;
   setcolor(15);
   cout << "#                     #                                                                                                                        # " << endl;
   cout << "#                     #                                                                                                                        # " << endl;
   cout << "#                     #                                                                                                                        # " << endl;
   cout << "#                     #                                                                                                                        # " << endl;
   cout << "#                     #                                                                                                                        # " << endl;
   cout << "#                     #                                                                                                                        # " << endl;
   cout << "#                     #                                                                                                                        # " << endl;
   cout << "#                     #                                   ###################################################################################### " << endl;
   cout << "#                     #                                                                                                   #                    # " << endl;
   cout << "#                     #                                                                                                   #                    # " << endl;
   cout << "#                     #                                                                                                   #                    # " << endl;
   cout << "#                     #                                                                                                   #       HEALTH       # " << endl;
   cout << "#                     #                                                                                                   #                    # " << endl;
   cout << "#                     #                                                                                                   #                    # " << endl;
   cout << "#                     #                                                                                                   #                    # " << endl;
   cout << "#                     #                                                                                                   #                    # " << endl;
   cout << "#                     #                                                                                                   #                    # " << endl;
   cout << "#                     #                                                                                                   #                    # " << endl;
   cout << "#                     #                                                                                                   #                    # " << endl;
   cout << "#                     #                                                                                                   #                    # " << endl;
   cout << "#                     ############################################                    ##################################### ##### GATE 1 ##### # " << endl;
   cout << "#                                                                                                                                              # " << endl;
   cout << "#                                                                                                                                              # " << endl;
   cout << "#                                                                                                                                              # " << endl;
   cout << "#                                                                                                                                              # " << endl;
   cout << "#                                                                                                                                              # " << endl;
   cout << "#                                                                                                                                              # " << endl;
   cout << "#                                                                                                                                              # " << endl;
   cout << "#                                                                                                                                              # " << endl;
   setcolor(5);
   cout << "################################################################################################################################################ " << endl;
   cout << R"(#           ||  __  __  _   _   __ ||                                                                                                          # )" << endl;
   cout << R"(#           || (_  /   / \ |_) |_  ||                                                                                                          # )" << endl;
   cout << R"(#           || __) \__ \_/ | \ |__ ||                                                                                                          # )" << endl;
   cout << "################################################################################################################################################ " << endl;
}
void gotoxy(int x, int y)
{
   COORD coordinates;
   coordinates.X = x;
   coordinates.Y = y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void character()
{
   setcolor(12);
   gotoxy(pX, pY);
   cout << "    _/***\\_  " << endl;
   gotoxy(pX, pY + 1);
   cout << "   #  ===  #  " << endl;
   gotoxy(pX, pY + 2);
   cout << "  #  | 8 |  # " << endl;
   gotoxy(pX, pY + 3);
   cout << " #   | 8 |   #" << endl;
   gotoxy(pX, pY + 4);
   cout << "    / ___ \\  " << endl;
   gotoxy(pX, pY + 5);
   cout << "   /_/   \\_\\" << endl;
}

void eraseCharacter()
{
   gotoxy(pX, pY);
   cout << "              " << endl;
   gotoxy(pX, pY + 1);
   cout << "              " << endl;
   gotoxy(pX, pY + 2);
   cout << "              " << endl;
   gotoxy(pX, pY + 3);
   cout << "              " << endl;
   gotoxy(pX, pY + 4);
   cout << "              " << endl;
   gotoxy(pX, pY + 5);
   cout << "              " << endl;
}

void printfire()
{
   gotoxy(bX + 20, bY);
   cout << ">>";
   gotoxy(bX + 20, bY + 1);
   cout << ">>";
   gotoxy(bX + 20, bY + 2);
   cout << ">>";
   gotoxy(bX + 20, bY + 3);
   cout << ">>";
   bX += 1;
}

void removefire()
{
   gotoxy(bX + 20 - 4, bY);
   cout << "  ";
   gotoxy(bX + 20 - 4, bY + 1);
   cout << "  ";
   gotoxy(bX + 20 - 4, bY + 2);
   cout << "  ";
   gotoxy(bX + 20 - 4, bY + 3);
   cout << "  ";
}

void movefire()
{
   if (bulletDir == 'u')
   {
      removefire2();
      printfire2();
      if (bY - 5 <= eY3 + 4 && bY - 5 >= eY3 && bX <= eX3 + 10)
      {
         bulletActive = false;
         Enemy3life++;
      }
      if (bY - 5 <= eY2 + 4 && bY - 5 >= eY2 && bX <= eX2 + 10)
      {
         bulletActive = false;
         Enemy2life++;
      }
      if (getCharAtxy(bX, bY - 5) != '#')
      {
         bY -= 1; // Move up
      }
      else
      {
         bulletActive = false;
         gotoxy(bX, bY - 3 + 2);
         cout << "  ";
         gotoxy(bX, bY - 4 + 2);
         cout << "  ";
         gotoxy(bX, bY - 5 + 2);
         cout << "  ";
         gotoxy(bX, bY - 6 + 2);
         cout << "  ";
      }
   }
   if (bulletDir == 'r')
   {
      printfire();
      removefire();
      if (bX + 16 >= eX && bX + 16 <= eX + 10 && bY <= eY + 5)
      {
         bulletActive = false;
         Enemylife++;
      }
      if (getCharAtxy(bX + 2, bY) != '#')
      {
         bX += 2; // Move right
      }
      else
      {
         bulletActive = false;
      }
   }
}

void printfire2()
{
   gotoxy(bX, bY - 2);
   cout << "--";
   gotoxy(bX, bY - 3);
   cout << "||";
   gotoxy(bX, bY - 4);
   cout << "||";
   gotoxy(bX, bY - 5);
   cout << "--";
   bY -= 1;
}

void removefire2()
{
   gotoxy(bX, bY - 2 + 4);
   cout << "  ";
   gotoxy(bX, bY - 3 + 4);
   cout << "  ";
   gotoxy(bX, bY - 4 + 4);
   cout << "  ";
   gotoxy(bX, bY - 5 + 4);
   cout << "  ";
}

void enemy()
{
   setcolor(10);
   gotoxy(eX, eY);
   cout << "@^@^@^@^@" << endl;
   gotoxy(eX, eY + 1);
   cout << "@  ^ ^  @" << endl;
   gotoxy(eX, eY + 2);
   cout << "@   *   @" << endl;
   gotoxy(eX, eY + 3);
   cout << "@  777  @" << endl;
}
void eraseEnemy()
{
   gotoxy(eX, eY);
   cout << "             " << endl;
   gotoxy(eX, eY + 1);
   cout << "             " << endl;
   gotoxy(eX, eY + 2);
   cout << "             " << endl;
   gotoxy(eX, eY + 3);
   cout << "             " << endl;
}
void moveEnemy()
{
   eraseEnemy();
   if (enemy1_Back == 0)
   {
      eX = eX + 1;
   }
   if (eX == 125)
   {
      enemy1_Back = 1;
   }
   if (enemy1_Back == 1)
   {
      eX = eX - 1;
   }
   if (eX == 95)
   {
      enemy1_Back = 0;
   }
   enemy();
}

void enemy2()
{
   setcolor(9);
   gotoxy(eX2, eY2);
   cout << "@^@^@^@^@" << endl;
   gotoxy(eX2, eY2 + 1);
   cout << "@  ^ ^  @" << endl;
   gotoxy(eX2, eY2 + 2);
   cout << "@   *   @" << endl;
   gotoxy(eX2, eY2 + 3);
   cout << "@  777  @" << endl;
}

void eraseEnemy2()
{
   gotoxy(eX2, eY2);
   cout << "             " << endl;
   gotoxy(eX2, eY2 + 1);
   cout << "             " << endl;
   gotoxy(eX2, eY2 + 2);
   cout << "             " << endl;
   gotoxy(eX2, eY2 + 3);
   cout << "             " << endl;
}

void moveEnemy2()
{
   eraseEnemy2();
   if (enemy2_Back == 0)
   {
      eY2 = eY2 + 1;
      eX2 = eX2 + 1;
   }
   if (eY2 == 23 && eX2 == 77)
   {
      enemy2_Back = 1;
   }
   if (enemy2_Back == 1)
   {
      eY2 = eY2 - 1;
      eX2 = eX2 - 1;
   }
   if (eY2 == 14 && eX2 == 68)
   {
      enemy2_Back = 0;
   }
   enemy2();
}

void enemy3()
{
   setcolor(7);
   gotoxy(eX3, eY3);
   cout << "@^@^@^@^@" << endl;
   gotoxy(eX3, eY3 + 1);
   cout << "@  ^ ^  @" << endl;
   gotoxy(eX3, eY3 + 2);
   cout << "@   *   @" << endl;
   gotoxy(eX3, eY3 + 3);
   cout << "@  777  @" << endl;
}

void eraseEnemy3()
{
   gotoxy(eX3, eY3);
   cout << "             " << endl;
   gotoxy(eX3, eY3 + 1);
   cout << "             " << endl;
   gotoxy(eX3, eY3 + 2);
   cout << "             " << endl;
   gotoxy(eX3, eY3 + 3);
   cout << "             " << endl;
}
void moveEnemy3()
{
   eraseEnemy3();
   if (enemy2_Back == 0)
   {
      eY3 = eY3 + 1;
   }
   if (eY3 == 14)
   {
      enemy3_Back = 1;
   }
   if (enemy3_Back == 1)
   {
      eY3 = eY3 - 1;
   }
   if (eY3 == 6)
   {
      enemy3_Back = 0;
   }
   enemy3();
}

void movePlayerLeft()
{
   if (getCharAtxy(pX - 1, pY) == ' ')
   {
      eraseCharacter();
      pX = pX - 1;
      character();
   }
}
void movePlayerRight()
{
   if (getCharAtxy(pX + 14, pY) == ' ')
   {
      eraseCharacter();
      pX = pX + 1;
      character();
   }
}
void movePlayerUp()
{
   if (getCharAtxy(pX, pY - 1) == ' ')
   {
      eraseCharacter();
      pY = pY - 1;
      character();
   }
}
void movePlayerDown()
{
   if (getCharAtxy(pX, pY + 6) == ' ')
   {
      eraseCharacter();
      pY = pY + 1;
      character();
   }
}
char getCharAtxy(short int x, short int y)
{
   CHAR_INFO ci;
   COORD xy = {0, 0};
   SMALL_RECT rect = {x, y, x, y};
   COORD coordBufSize;
   coordBufSize.X = 1;
   coordBufSize.Y = 1;
   return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar
                                                                                           : ' ';
}
void increaseHealth()
{
   if (CountHealth == 0)
   {
      if (getCharAtxy(132, 17) == ' ')
      {
         health2 = health2 + 50;
         CountHealth++;
      }
   }
}

void displayScore()
{
   increaseHealth();
   gotoxy(scoreX+1, scoreY+1);
   cout << "Your Health:\t" << health2 << endl;
}

// function for displaying winning message
void winMsg(int x, int y)
{
   setcolor(10);   // for green color
   border(38, 16); // calling border
   gotoxy(x, y);
   cout << "         __                    __          " << endl;
   gotoxy(x, y + 1);
   cout << " \\   /  /  \\  |    |  |    |  /  \\  |\\   | " << endl;
   gotoxy(x, y + 2);
   cout << "  \\ /  |    | |    |  |    | |    | | \\  | " << endl;
   gotoxy(x, y + 3);
   cout << "   /   |    | |    |  | /\\ | |    | |  \\ | " << endl;
   gotoxy(x, y + 4);
   cout << "  /     \\__/   \\__/   |/  \\|  \\__/  |   \\| " << endl;
   setcolor(7); // for white color
}

// function for displaying losing message
void loseMsg(int x, int y)
{
   setcolor(4);    // for red color
   border(38, 16); // calling border
   gotoxy(x, y);
   cout << "         __                  __    __   ___ " << endl;
   gotoxy(x, y + 1);
   cout << " \\   /  /  \\  |    |  |     /  \\  /  \\ |    " << endl;
   gotoxy(x, y + 2);
   cout << "  \\ /  |    | |    |  |    |    | \\    |___ " << endl;
   gotoxy(x, y + 3);
   cout << "   /   |    | |    |  |    |    |   \\  |    " << endl;
   gotoxy(x, y + 4);
   cout << "  /     \\__/   \\__/   |___  \\__/  \\__/ |___ " << endl;
   setcolor(7); // for white color
}

// function for displaying border around message
void border(int x, int y)
{
   gotoxy(x, y);
   cout << " ============================================= ";
   gotoxy(x, y + 1);
   cout << "|                                             | ";
   gotoxy(x, y + 2);
   cout << "|                                             | ";
   gotoxy(x, y + 3);
   cout << "|                                             | ";
   gotoxy(x, y + 4);
   cout << "|                                             | ";
   gotoxy(x, y + 5);
   cout << "|                                             | ";
   gotoxy(x, y + 6);
   cout << " ============================================= ";
}

// functionf for checking winner or loser
bool WinnerLoserCheck()
{
   if (Enemylife >= 5 && Enemy2life >= 5 && Enemy3life >=5)
   {
      winMsg(40, 17); // than print win msg
      return true;
   }
   else if (health2 <= 0)
   {
      loseMsg(40, 17); // than print lose msg
      return true;
   }
   return false;
}

void drawEnemyBullet()
{
   if (enemi2)
   {
      gotoxy(enemyX, enemyY);
      cout << "$";
   }
}

void removeEnemyBullet()
{
   if (enemi2)
   {
      gotoxy(enemyX, enemyY);
      cout << " ";
   }
}

void moveEnemyBullet(int &eX, int &eY, int &pX, int &pY)
{
   if (!enemi2 && rand() % 100 < 5)
   {
      enemyX = eX;
      enemyY = eY + 2;
      enemi2 = true;
   }

   if (enemi2)
   {
      removeEnemyBullet();

      if (getCharAtxy(enemyX - 2, enemyY) == ' ')
      {
         enemyX--;
         if (enemyX >= pX && enemyX <= pX + 15 && enemyY >= pY)
         {
            health2 = health2 - 10;
         }
      }
      else
      {

         enemi2 = false;
      }

      if (enemyX <= 0)
      {
         enemi2 = false;
      }

      drawEnemyBullet();
   }
}

void drawEnemyBullet2()
{
   if (enemi3)
   {
      gotoxy(enemyX2, enemyY2);
      cout << "(_)";
   }
}

void removeEnemyBullet2()
{
   if (enemi3)
   {
      gotoxy(enemyX2, enemyY2);
      cout << "   ";
   }
}

void moveEnemyBullet2(int &eX3, int &eY3, int &pX, int &pY)
{
   if (!enemi3 && rand() % 100 < 5)
   {
      enemyX2 = eX3 + 3;
      enemyY2 = eY3 + 5;
      enemi3 = true;
   }

   if (enemi3)
   {
      removeEnemyBullet2();

      if (getCharAtxy(enemyX2, enemyY2 + 2) == ' ')
      {
         enemyY2++;
         if (enemyX2 >= pX && enemyX2 <= pX + 20 && (enemyY2 >= pY - 2 || enemyY2 >= pY + 6))
         {
            health2 = health2 - 10;
         }
      }
      else
      {
         enemi3 = false;
      }
      if (enemyX2 < 4)
      {
         enemi3 = false;
      }

      drawEnemyBullet2();
   }
}

// function for printing menu box
void printBox()
{
   fstream file;
   string line;
   file.open("Box.txt", ios::in); // opening file
   while (!file.eof())
   {
      getline(file, line);  // line by line
      cout << line << endl; // displaying menu box
   }
   file.close(); // closing file
}

// function for displaying instructions
void Instructions()
{
   system("cls");
   printBox();
   gotoxy(34, 8);
   cout << "*** INSTRUCTIONS ***";

   setcolor(1); // for blue color
   gotoxy(30, 12);
   cout << "<< How To Play Game >>";
   setcolor(4); // for red color
   gotoxy(35, 14);
   cout << "[ CONTROLS ]"; // controls
   setcolor(10);           // for green color
   gotoxy(28, 17);
   cout << " SHOOT RIGHTWARDS >> Space key";
   gotoxy(28, 18);
   cout << " SHOOT UPWARDS    >> Right Shift Key";
   gotoxy(28, 19);
   cout << " Move UPWARDS     >> Up Arrow Key";
   gotoxy(28, 20);
   cout << " Move DOWNWARDS   >> Up Arrow Key";
   gotoxy(28, 21);
   cout << " Move LEFTWARDS   >> Left Arrow Key";
   gotoxy(28, 22);
   cout << " MOVE RIGHTWARDS  >> Right Arrow Key";
   setcolor(7); // for white color
   gotoxy(28, 23);
   cout << " Press any key to continue.....";
   getch();
}

// function for displaying about of the game
void About()
{
   system("cls");
   printBox();

   gotoxy(34, 8);
   cout << "*** ABOUT ***";

   setcolor(10); // for green color
   gotoxy(25, 14);
   cout << "VERSION >> 1.0 "; // version
   gotoxy(25, 15);
   cout << "DEVELOPER >> MUHAMMAD AYYAN GOREJA (2023-CS-5)";

   setcolor(7); // for white color
   gotoxy(25, 22);
   cout << " Press any key to continue.....";
   getch();
}
// function for main menu
char menu()
{
   setcolor(6);
   fstream file;
   string line;
   file.open("MenuBox.txt", ios::in); // opening file
   while (!file.eof())                // reading until enf of file
   {
      getline(file, line);  // line by line
      cout << line << endl; // displaying main menu box
   }
   file.close(); // closing file
   char option;  // variable for option
   gotoxy(40, 22);
   cout << " YOUR OPTION .... : ";
   option = getche(); // taking input
   return option;
}
