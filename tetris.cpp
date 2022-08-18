#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "header.h"

IMAGE *GAME_image[14];
bool flags[9] = { 0 }; // ����� ��� �������� ����� ������� � ������ �� ������

// ���������� ��� �������� ������
int record = 0; // ������
int score = 0; // ����� ����
int lines = 0; // ����� ���������� �����
int once_lines = 0; // ���������� ����� �������� �� ���� ���
int level = 0; // �������

int field[M][N + 1]; // ������� ����
int speed; // �������� ������� �����
int count_hold = 0; // ������� ���������� ��� ������� �� ������� Shift
int ri = -1; // ���������� ��� ��������� ���������� ������
int count_page = 0; // ������� ������������ �������
int k = 8; // ���������� ��� �������� �������� ���������
int p = 0; // ���������� ��� ������������ �������

// ���������� ������ ����//
item GAME_item[14] =
{
   {474, 350, 754 - 474, 452 - 350}, // 0 - � ���������
   {474, 481, 745 - 474, 584 - 481}, // 1 - �������
   {351, 614, 868 - 351, 808 - 614},  // 2 - ������
   {1045, 40, 1155 - 1045, 145 - 40},  // 3 - �����
   {892, 166, 996 - 892, 268 - 166},  // 4 - ������� ���� �������
   {460, 625, 590 - 460, 760 - 625},  // 5 - �����
   {615, 625, 740 - 615, 760 - 625},  // 6 - �����
   {945, 725, 1038 - 945, 815 - 725}, //  7 - �����
   {1050, 725, 1145 - 1050, 815 - 725}, // 8 - ������� ���� 
   {300, 320, 895 - 300, 540 - 320}, // 9 - ����������
   {290, 485, 440 - 290, 630 - 485}, // 10 - ��
   {755, 485, 900 - 755, 630 - 485}, // 11 - ���
   {400, 600, 760 - 400, 750 - 600}, // 12 - ������
   {915, 115, 1010 - 915, 215 - 115}, // 13 - ������� ���� �����������
};

// ������� ��������������� �������� ������� �� ��������� ���������//
int figures[7][4] =
{
   {1, 3, 5, 7},   // I
   {2, 4, 5, 7},   // Z
   {3, 5, 4, 6},   // S
   {3, 5, 4, 7},   // T
   {2, 3, 5, 7},   // L
   {3, 5, 7, 6},   // J
   {2, 3, 4, 5}    // O
};

// �������� ������������� ������ ���������
color Color[7] =
{
   {225, 50, 50}, // �������
   {225,117,9}, // ���������
   {225, 198, 8}, // ������
   {92,185,15}, // �������
   {81, 200, 215}, // �������
   {2, 110, 200}, // �����
   {185,49,193}, // ����������
};


void release_key()
{
   while (mousebuttons())
   {
      if (!mousebuttons())
         break;
   }
}

void load_images()
{
   GAME_image[0] = loadBMP("main.jpg"); // 0 - ������� �����
   GAME_image[1] = loadBMP("about.jpg"); // 1 - �������� "� ���������"
   GAME_image[2] = loadBMP("rules1.jpg"); // 2 - �������� ������ �1
   GAME_image[3] = loadBMP("rules2.jpg"); // 3 - �������� ������ �2
   GAME_image[4] = loadBMP("rules3.jpg"); // 4 - �������� ������ �3
   GAME_image[5] = loadBMP("background.jpg"); // 5 - ������ ��� �������� � �����
   GAME_image[6] = loadBMP("continue.jpg"); // 6 - ���������� ����
   GAME_image[7] = loadBMP("exit.jpg"); // 7 - ������������� ������
   GAME_image[8] = loadBMP("frame.jpg"); // 8 - �����
   GAME_image[9] = loadBMP("grid.jpg"); // 9 - �����
   GAME_image[10] = loadBMP("ready.jpg"); // 10 - �������� ������ (3)
   GAME_image[11] = loadBMP("steady.jpg"); // 11 - �������� ������ (2)
   GAME_image[12] = loadBMP("go.jpg"); // 12 - �������� ������ (1)
   GAME_image[13] = loadBMP("results.jpg"); // 13 - ����������
}

int main()
{
   srand(time(NULL));
   int win = initwindow(WIN_W, WIN_H, "Tetris");
   load_images();
   do
   {
      int once_lines = 0;
      bool exitCase1 = false;
      while (mousebuttons())
      {
         if (!mousebuttons())
            break;
      }
      release_key();
      putimage(0, 0, GAME_image[0], COPY_PUT);
      int a = select_menu(GAME_item, 4);
      switch (a)
      {
      case 1: // ������ ������ "� ���������"
         {
            about_program();
            break;
         }
      case 2: // ������ ������ "�������"
         {
            rules();
            break;
         }
      case 3: // ������ ������ "������"
         {
            game();
            break;
         }
      case 4: // ������ ������ "�����"
         {
            exitCase1 = true;
            closegraph();
            break;
         }
         break;
      }
      if (exitCase1) break;
   }
   while (true);

   return 0;
}

int about_program()
{
   release_key();
   cleardevice();
   putimage(0, 0, GAME_image[1], COPY_PUT);
   int a = select_menu(GAME_item + 4, 1);
   if (a == 1)  return 0;
   return 0;
}

int rules()
{
   int ki = 2;
   release_key();
   cleardevice();
   putimage(0, 0, GAME_image[ki], COPY_PUT);
    if (mousebuttons() == 0) {
      do
      {
         int a = select_menu(GAME_item + 4, 3);
         bool exitCase2 = false;
         switch (a)
         {
         case 1: // ������ ������ "������� ����"
            {
               exitCase2 = true;
               break;
            }
         case 2: // ������ ������ "�����"
            {
               if (ki > 2)
               {
                  ki--;
                  release_key();
                  cleardevice();
                  putimage(0, 0, GAME_image[ki], COPY_PUT);
               }
               break;
            }
         case 3: // ������ ������ "�����"
            {
               if (ki < 4)
               {
                  ki++;
                  release_key();
                  cleardevice();
                  putimage(0, 0, GAME_image[ki], COPY_PUT);
               }
               break;
            }
         }
         if (exitCase2) break;
      } while (true);
   }
   return 0;
}

int game()
{
   release_key();
   for (int i = 0; i < 3; i++)
   {
      putimage(0, 0, GAME_image[10 + i], COPY_PUT);
      delay(600);
   }

   clean_field(); // ������� ���� �� �����

   int x, y;
   count_hold = 0;
   k = 8;

   do
   {
      k = 8;
      clean_field();
      count_hold = 0;
      int p = 0, ri = -1;
      int n[2];

      for (int i = 0; i <= 7; i++)
         flags[i] = false;

      for (int i = 0; i < 2; i++) // � ����� ������ ���������� ��� ��������� ���������
         n[i] = rand() % 7;

      while (1) // ������� ����� ������
      {
         count_page = 0;
         for (int i = 0; i < 4; i++) // ���������� ���������� ������
         {
            a[i].x = figures[n[0]][i] % 2 + 5;
            a[i].y = figures[n[0]][i] / 2 + 5;
         }

         speed = 30;
         for (int i = 1; i <= 5; i++)
            flags[i] = false;

         while (1) // �������� ������� ������
         {
            count_page++;
            p = 1 - p;
            setactivepage(p);
            putimage(0, 0, GAME_image[5], COPY_PUT);
            putimage(0, 0, GAME_image[8], COPY_PUT);
            putimage(381, 1, GAME_image[9], COPY_PUT);
            
            // ��������� �� ������ ������//
            draw_quantity (200, 490, score);
            draw_quantity (200, 490 + 140, lines);
            draw_quantity (200, 490 + 140 * 2, level);
            draw_quantity (990, 495, record); 

            tetro_block(n[1], 15.7); // ��������� ������� ��������� � ���� ��������� �����

            n[0] = check_hold(n[0]); // ���������� ������ � ���� ���������
            if (flags[3]) // ���� ��������� ��������
            {
               for (int i = 0; i < 2; i++)
                  n[i] = rand() % 7;
               p = 1 - p;
               break;
            }
            if (flags[5]) // ���� ��������� �����
            {
               p = 1 - p;
               break; 
            }

            filling_field();
            if (flags[4]) results();
            if (flags[0]) break;

            for (int i = 0; i < 4; i++) //  ��������� �������� ������
               tetro(a[i].x, a[i].y, Color[n[0]].r, Color[n[0]].g, Color[n[0]].b);

            for (int i = 0; i < 4; i++) //  ������� ������
            {
               b[i] = a[i];
               if (speed == 30)
               {
                  if (count_page % k == 0)
                     a[i].y++;
               }
               else a[i].y++;
            }
            
            if (!check()) // ������ �����
            {
               flags[6] = false;
               flags[2] = true;
               score += 10; // ���������� ������ �� ���� ������� ������
               for (int i = 0; i < 4; i++)
               {
                  a[i] = b[i];
                  field[a[i].y][a[i].x] = n[0]; // ����������� ����� ����� ����, ���� ����� ������
               }
               n[0] = n[1];
               n[1] = rand() % 7;
               p = 1 - p;
               break;
            }
            putimage(0, 0, GAME_image[8], COPY_PUT);
            setvisualpage(p);
            delay(speed);
            
            if (speed != 1)
               speed = 30;

            if (mousebuttons()) game_bottom();
            while (kbhit()) move();
            if ((flags[0]) | (flags[1]) | (flags[2]) | (flags[5])) break;
         }
         if ((flags[0]) | (flags[1])) break;
      }
      if (flags[0])
         break;
   } while (true);
   return 0;
}

int filling_field()
{
   lines += once_lines;
   score += 40 * once_lines * (level + 1);
   once_lines = 0;
   level = lines / 5;
   
   if (score > record)
      record = score;

   int s = M - 1;

   for (int i = M - 1; i > 0; i--)
   {
      int count = 0;
      for (int j = 1; j <= N; j++)
      {
         field[s][j] = field[i][j];

         if (field[i][j] != -1)
         {
            count++;
            tetro(j, i, Color[field[i][j]].r, Color[field[i][j]].g, Color[field[i][j]].b); //  ������ ������� �� ���� ������
            if ((i < 10) && (field[i][j] != -1)) // ������ �������� ����� ����
            {
               flags[4]  = true;
               return 0;
            }
         }
      }
      if (count < N) s--; // �������� �� �����
      else
      {
         once_lines++;
         if (((lines + 1) % 5 == 0) && (level < 8)) k -= 1; // ���������� �������� ��� �������� �� ��������� �������
      }
   }

   return 0;
}

int game_bottom()
{
   int a = select_menu(GAME_item + 7, 2);
   if (a == 1) // ������ ������ "�����"
      pause();
   else if (a == 2) // ������ ������ "�����"
      quit();
   return 0;
}

int pause()
{
   setactivepage(3);
   putimage(0, 0, GAME_image[6], COPY_PUT);
   setvisualpage(3);
   int a = 0;
   do
   {
      a = select_menu(GAME_item + 9, 1); // ������ ������ "����������"
      if (a == 1) return 0;
   } while (a != 1);
   return 0;
}

int quit()
{
   setactivepage(3);
   putimage(0, 0, GAME_image[7], COPY_PUT);
   setvisualpage(3);
   int a = 0;
   do
   {
      a = select_menu(GAME_item + 10, 2);

      if (a == 1) // ��������� ����
      {
         results();
         return 0;
      }
      else if (a == 2) return 0; // ���������� ����
   } while (a != 1);
   return 0;
}

int results()
{
   setactivepage(3);
   putimage(0, 0, GAME_image[13], COPY_PUT);
   draw_quantity (560, 340, level);
   draw_quantity (560, 340 + 55, lines);
   draw_quantity (560, 340 + 55 * 2, score);
   draw_quantity (560, 510, record);
   setvisualpage(3);
   
   int a = 0;
   do
   {
      int a = select_menu(GAME_item + 12, 2);
      if (a == 1) // ������ ������
      {
         flags[1] = true;
         return 0;
      }
      else if (a == 2) // ����� � ����
      {
         flags[0] = true;
         return 0;
      }
   } while (a != 1);
   return 0;
}

int tetro(float x, float y, int r, int g, int b)
{
   int w = 37, p = 5;

   setfillstyle(SOLID_FILL, COLOR(0, 0, 0));
   bar(CENTER_X  - 1 + x * w, CENTER_Y - 1 + y * w, CENTER_X + x * w + 1 + w, CENTER_Y + y * w + 1 + w);

   for (int i = 0; i < 5; i++)
   {
      setfillstyle(SOLID_FILL, COLOR(r + 5 * i, g + 10 * i, b + 10 * i));
      bar(CENTER_X + p * i + x * w, CENTER_Y + p * i + y * w, CENTER_X + x * w - p * i + w, CENTER_Y + y * w - p * i + w);
   }
   return 0;
}

bool check()
{
   for (int i = 0; i < 4; i++)
   {
      if (a[i].x < 1 | a[i].x > N | a[i].y >= M)
         return 0;
      else if (field[a[i].y][a[i].x] != -1)
         return 0;
   }
   return 1;
}

int move()
{
   int dx = 0;
   int code = getch(); //  ��������  ��� �������
   switch (code)
   {
      case KEY_LEFT: // ����� ������ �����
      {
         for (int i = 0; i < 4; i++)
         {
            b[i] = a[i]; // ���������� ������� ��������� ������
            a[i].x--;
         }

         if (!check()) // ���� ������ ����������� � ������������...
         {
            for (int i = 0; i < 4; i++)
               a[i] = b[i]; //... ���������� ������ � ������� ���������
         }
         break;
      }

      case KEY_RIGHT: // ����� ������ ������
      {
         for (int i = 0; i < 4; i++)
         {
            dx = 1;
            b[i] = a[i];
            a[i].x += dx;
         }
         if (!check())
         {
            for (int i = 0; i < 4; i++)
               a[i] = b[i];
         }
         break;
      }

      case KEY_UP: // ������� ������
      {
         Point p = a[1]; // ����� ��������
         for (int i = 0; i < 4; i++)
         {
            b[i] = a[i];
            int k = a[i].x;
            a[i].x = - a[i].y + p.x + p.y;
            a[i].y = k + p.y - p.x;
         }
         if (!check())
         {
            for (int i = 0; i < 4; i++)
               a[i] = b[i];
         }
         break;
      }
      case KEY_SHIFT: // �������� ������
      {
         if (!flags[6])
            flags[7] = 0;
         count_hold++;
         break;
      }
      case KEY_DOWN: // ����� ������ ����
      {
         speed = 15;
         break;
      }
      case 32: // ������� ������
      {
         speed = 1;
         break;
      }
   }
   return 0;
}

int tetro_block(int x, float position)
{
   for (int i = 0; i < 4; i++) // ���������� ���������� ������
   {
      c[i].x = figures[x][i] % 2;
      c[i].y = figures[x][i] / 2;
      tetro(c[i].x + position, c[i].y + 11.6, Color[x].r, Color[x].g, Color[x].b);
   }
   return 0;
}

int clean_field()
{
   score = 0, lines = 0, level = 0, once_lines = 0;

   for (int i = 0; i < M; i++)
   {
      for (int j = 0; j <= N; j++)
         field[i][j] = -1; // �������� ����
   }

   return 0;
}

int check_hold(int x)
{
   if (count_hold != 0) // �������� �� ��, �� ��������� �� �� ���� � �� �� ������ � ���� ��������� ����� ������ ����
   {
      if (ri != -1) tetro_block(ri, -5.8); // ���� ���� ����������� ������, ������ ��
      if (!flags[6])
      {
         if (!flags[7])
         {
            flags[6] = 1;
            flags[7] = 1;
            if (count_hold == 1) // ���� "shift" ��� ����� ������� �� ����, ��...
            {
               ri = x; // ... ���������� ������ � ���� � ���� ���������
               flags[3] = true;
               count_hold++;
               return x;
            }
            else if (count_hold > 1) // ���� � ����� ��������� ��� ���� ������, ��...
            {
               int a = ri;
               ri =  x; // ... ������ ������� ������ � ���� � ������ �� ����� ���������
               x = a;
               flags[5] = true;
               return x;
            }
         }
      }
   }
   return x;
}

int select_menu(item GAME_item[], int nmenu)
{
   flags[9] = false;
   while (1)
   {
      if (mousebuttons() == 1)
      {
         int x = mousex();
         int y = mousey();

         for (int i = 0; i < nmenu; i++)
         {
            if (x <= (GAME_item + i) -> w + (GAME_item + i) -> x && x >= (GAME_item + i) -> x && y >= (GAME_item + i) -> y
                  && y <= (GAME_item + i) -> h + (GAME_item + i) -> y) // ����� ������
            {
               return (i + 1);
            }
            else if (i == nmenu - 1)
            {
               flags[9] = true;
               break;
            }
         }
      }
      if (flags[9]) break;
   }
   return 0;
}

int draw_quantity (int x, int y, int number)
{
   char str[12];
   sprintf(str, "%d", number);

   setbkmode(TRANSPARENT);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   settextstyle(EMPTY_FILL, HORIZ_DIR, 37);

   setcolor(COLOR(230,184,32));
   outtextxy(x, y + 2,  str);
   setcolor(COLOR(225,140,0));
   outtextxy(x, y,  str);

   return 0;
}