#ifndef HEADER_H
#define HEADER_H

#include "graphics.h"

// Размеры окна в пикселях
#define WIN_W 1200
#define WIN_H 851

// Размеры игрового поля
#define M 29
#define N 10

// Начальные координаты падающей фигуры
#define CENTER_Y -286
#define CENTER_X 377

// Параметры кнопок//
struct item
{
   int x;
   int y;
   int w;
   int h;
};

//Координаты одного квадрата тетрамино
struct Point
{
   int x, y;
} a[4], b[4], c[4];

// Структура с элементами RGB
struct color
{
   int r, g, b;
};

int about_program(); // Рисование страницы "О программе"
int rules(); // Рисование страниц с правилами
int game(); // Рисование игрового поля
int pause(); // Рисование страницы "Пауза"
int quit(); // Рисование страницы "Выход из игры"
int results(); // Рисование страницы с результатами
int tetro(float x, float y, int r, int g, int b); // Рисование одного квадрата, из которых состоят тетрамино
int tetro_block(int x, float position); // Рисование фигур в блоках следующих фигур и удержания 
int move(); // Считывание кодов клавиш
int clean_field(); // Очистка игрового поля
int check_hold(int x) ; // Проверка на возможность добавить в блок удержания фигуру
bool check(); // Проверка на границы поля
int filling_field(); // Рисование упавших на поле фигур
int game_bottom(); // Проверка на нажатие клавиш на странице с игрой
int draw_quantity (int x, int y, int number); // Рисование баллов
void load_images(); //Загрузка изображений
int select_menu(item GAME_item[], int nmenu); // Выбор кнопки

#endif
