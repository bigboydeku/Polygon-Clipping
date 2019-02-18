// A3.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
This program belongs to Denis Nadarevic (104445626). This program is for educational purposes.
*/
//

#include "pch.h"
#include <stdio.h>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <SDL.h>
#include <math.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

void menu();
void refresh(SDL_Surface * canvas, SDL_Renderer * renderer, SDL_Texture * texture);
void drawPolygon(uint32_t pixels[][SCREEN_WIDTH], SDL_Surface * canvas, SDL_Renderer * renderer, SDL_Texture * texture);
void drawPoint(uint32_t pixels[][SCREEN_WIDTH], int x, int y, uint32_t color);
void drawLineAlg(uint32_t pixels[][SCREEN_WIDTH], const float x1, const float y1, const float x2, const float y2, uint32_t color);
std::vector<Point> listPolygon();

struct Point {
	int x;
	int y;
};

int main(int argc, char* args[]) {
	int userInput = 9;

	//Verify if SDL is initialized
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}
	//initialize window and verify if it works
	SDL_Window* window = SDL_CreateWindow("hello_sdl2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "could not create window: %s\n", SDL_GetError());
		return 1;
	}

	//create the renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0); //the "0" lets the SDL2 choose what's best.
	if (renderer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "could not create renderer: %s\n", SDL_GetError());
		return 1;
	}
	
	//create canvas
	SDL_Surface* canvas = SDL_CreateRGBSurfaceWithFormat(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_PIXELFORMAT_RGBA8888);
	if (canvas == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "could not create surface: %s\n", SDL_GetError());
		return 1;
	}


	//create texture
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (texture == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "could not create texture: %s\n", SDL_GetError());
		return 1;
	}

	//fill canvas with white
	SDL_FillRect(canvas, NULL, SDL_MapRGB(canvas->format, 0xFF, 0xFF, 0xFF));
	uint32_t(*pixels)[SCREEN_WIDTH] = (uint32_t(*)[SCREEN_WIDTH]) canvas->pixels;


	do
	{
		menu();
		scanf_s("%d", &userInput);
		switch (userInput)
		{
		case 1: //1. Input a polygon and a starting point on the screen so that the polygon can be rendered
			drawPolygon(pixels, canvas, renderer, texture);
			refresh(canvas, renderer, texture);
			break;
		case 2: //2. Input a polygon, clip it, and fill it. 
			refresh(canvas, renderer, texture);
			break;
		case 4: //end program, released resources
			SDL_DestroyTexture(texture);
			SDL_FreeSurface(canvas);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			printf("Bye.\n");
			SDL_Quit();
			break;
		default:
			printf("Invalid choice. Try again.\n");
			break;
		}


	} while (userInput != 3);
	return 0;
}


/*
Diplays menu
*/
void menu()
{
	printf("Welcome to assignment 1~\n");
	printf("1. Input a polygon\n2. Input a polygon, clip it, and fill it.\n3. Exit\n>>");
}

/*
Refreshes and updates textures
*/
void refresh(SDL_Surface * canvas, SDL_Renderer * renderer, SDL_Texture * texture)
{
	SDL_UpdateTexture(texture, NULL, canvas->pixels, canvas->pitch);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

/*
Draws and clips the polygon based on the algorithms
*/
void drawPolygon(uint32_t pixels[][SCREEN_WIDTH], SDL_Surface * canvas, SDL_Renderer * renderer, SDL_Texture * texture)
{
	int userInput;
	int start_x0, start_y0, start_y0, start_y1;
	printf("Enter the first point: >> ");
	scanf("%d %d", &start_x0, &start_y0);

	int start_x1, start_y1;
	printf("Enter the second point:  >> ");
	scanf("%d %d", &start_x1, &start_y1);

	while (true)
	{
		printf("1) Sutherland-Hodgman\n2) Liang-Barsky\n>> ");
		scanf("%d", &userInput);
		if (userInput == 1)
		{
			break;
		}//use algorithm
		else if (userInput == 2)
		{
			break;
			
		}//use algorithm
		else
		{
			printf("invalid choice.\n");
		}
	}
}

/*This algorithm allows the program to store user point inputs in order using push_back
which appends data to the end of an existing vector. Like a stack ADT. */
std::vector<Point> listPolygon() {
	std::vector<Point> pointList;
	int n, x, y;
	printf("# of vertices: >> ");
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("Enter point in a clockwise form: >> ");
		scanf("%d %d", &x, &y);
		pointList.push_back(Point{x, y});
	}
	return pointList;
}

/*
Draws a point inside the screen.
*/
void drawPoint(uint32_t pixels[][SCREEN_WIDTH], int x, int y, uint32_t color) {
	if ((y >= 0 && y < SCREEN_HEIGHT) && (x >= 0 && x < SCREEN_WIDTH)) { pixels[y][x] = color; }
}

/*
Bresenham's Line Algorithm
Source: https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B
The cited code was edited to work with the program.
*/
void drawLineAlg(uint32_t pixels[][SCREEN_WIDTH], const float x1, const float y1, const float x2, const float y2, uint32_t color)
{
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x < maxX; x++)
	{
		if (steep)
		{
			drawPoint(pixels, y, x, 0x000000);
		}
		else
		{
			drawPoint(pixels, x, y, 0x000000);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}


/*
This is a small algorithm that translates a list of existing verties and returns a new set
of points that have been translatedby a certain point
*/
std::vector<Point> movePolygon(std::vector<Point>& verticesList, Point point)
{
	std::vector<Point> newVertices(verticesList);
	for (auto&verticesList : newVertices)
	{
		verticesList.x += point.x;
		verticesList.y += point.y;
	}

	return newVertices;
}
