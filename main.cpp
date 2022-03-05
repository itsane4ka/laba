#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <chrono>
#include <time.h>
#include <array>
#include <random>
#include <sstream>
#include <thread>
#include <algorithm>
#include <functional>
#include <windows.h>

using namespace sf;

int main()
{
	Font font;
	if (!font.loadFromFile("edf7f-eirik-raude.ttf"))
		return 0;
	Text text;
	text.setFont(font);
	text.setString("This is IT-stamina! Train your code-typing skills with us and make your \nown records!");
	text.setCharacterSize(22);
	text.setFillColor(Color(0,0,0));
	text.move(25, 25);
	

	ContextSettings settings;
	settings.antialiasingLevel = 8;

	RenderWindow window(VideoMode(700, 200), "IT-stamina");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear(Color(222, 202, 245, 0));

		ConvexShape convex;
		window.draw(convex);
		RectangleShape rectangle(Vector2f(650.f, 50.f));
		rectangle.move(25, 100);
		rectangle.setFillColor(Color(255, 255, 255));
		rectangle.setOutlineThickness(2.f);
		rectangle.setOutlineColor(Color(209, 224, 255));
		window.draw(rectangle);

		window.draw(text);

		window.display();
	}
	return 0;
}