#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#define _WIN32_WINDOWS 0x0501
#define _WIN32_IE 0x0600
#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <windows.h>
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <ctime>
#include <cmath>

using namespace sf;

const unsigned int DIM1 = 10;
const unsigned int DIM2 = 2;

int arr[DIM1][DIM2] = {
	{ 70, 617 },
	{ 445, 590 },
	{ 970, 587 },
	{ 1410, 582 },
	{ 1150, 587 },
	{ 1520, 530 },
	{ 74, 82 },
	{ 267, 143 },
	{ 751, 18 },
	{ 1270, 110 },
};

int FileWork(int score)
{
	// trying to get something from the file
	std::string buff;
	std::ifstream fin("record.txt");

	if (!fin.is_open())
	{
		std::cout << "Can not open the file!\n";
		return 0;
	}
	else
	{
		fin >> buff;
		if (buff == "")
		{
			std::string str_record = std::to_string(score);
			std::ofstream fout("record.txt");
			fout << score;
			fout.close();
			return score;
		}
		else
		{
			int n = atoi(buff.c_str());
			if (score > n)
			{
				// getting new rec to the file
				std::string str_record = std::to_string(score);
				std::ofstream fout("record.txt");
				fout << score;
				fout.close();
				return score;
			}
			else
				return n;
		}
	}
}

int getRandomCar()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int flag = gen() % 4;
	std::cout << "NUMBER: " << flag << std::endl;
	return flag;
}

bool triangle_check_fuck(double x11, double y11, double x21, double y21, double x31, double y31, double x, double y)
{
	int a = (x11 - x) * (y21 - y11) - (x21 - x11) * (y11 - y);
	int b = (x21 - x) * (y31 - y21) - (x31 - x21) * (y21 - y);
	int c = (x31 - x) * (y11 - y31) - (x11 - x31) * (y31 - y);

	if ((a > 0 && b > 0 && c > 0) || (a < 0 && b < 0 && c < 0) || (a == 0 || b == 0 || c == 0))
		return true;
	else false;
}

void racing()
{
	// window render
	RenderWindow window(VideoMode(1650, 715), "racing!");
	window.setFramerateLimit(60);

	// figures angles sharpness 
	ContextSettings settings;
	settings.antialiasingLevel = 10;

	// get textures
	Texture back;
	back.loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\maps\\back.png");

	Texture cars[5];
	cars[0].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Taxi.png");
	cars[1].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Ambulance.png");
	cars[2].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Mini_truck.png");
	cars[3].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Mini_van.png");
	cars[4].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Audi.png");

	Texture speed_cars[5];
	speed_cars[0].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Taxi-speed.png");
	speed_cars[1].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Ambulance.png");
	speed_cars[2].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Mini_truck-speed.png");
	speed_cars[3].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Mini_van-speed.png");
	speed_cars[4].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Audi-speed.png");

	Texture cars_broken[5];
	cars_broken[0].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Taxi-broken.png");
	cars_broken[1].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Ambulance.png");
	cars_broken[2].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Mini_truck-broken.png");
	cars_broken[3].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Mini_van-broken.png");
	cars_broken[4].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Audi-broken.png");

	Texture cars_broken_hard[5];
	cars_broken_hard[0].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Taxi-broken-hard.png");
	cars_broken_hard[1].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Ambulance.png");
	cars_broken_hard[2].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Mini_truck-broken-hard.png");
	cars_broken_hard[3].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Mini_van-broken-hard.png");
	cars_broken_hard[4].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\Audi-broken-hard.png");

	Texture speed_ambulance[3];
	speed_ambulance[0].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\ambulance_animation\\1.png");
	speed_ambulance[1].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\ambulance_animation\\2.png");
	speed_ambulance[2].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\ambulance_animation\\3.png");

	Texture ambulance_speed[3];
	ambulance_speed[0].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\ambulance_animation\\1-speed.png");
	ambulance_speed[1].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\ambulance_animation\\2-speed.png");
	ambulance_speed[2].loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\cars\\ambulance_animation\\3-speed.png");

	Texture swamp;
	swamp.loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\maps\\swamp.png");

	Texture bridge;
	bridge.loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\maps\\bridge-new.png");

	Texture bush;
	bush.loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\maps\\bushese.png");

	Texture house;
	house.loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\maps\\house.png");

	Texture plane;
	plane.loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\maps\\plane.png");

	Texture money;
	money.loadFromFile("C:\\programming\\fight for ukraine\\fight for ukraine\\Sprites\\money.png");

	// sprites
	Sprite background_s;
	background_s.setTexture(back);

	Sprite bridge_s;
	bridge_s.setTexture(bridge);
	bridge_s.setPosition(-30, 150);

	Sprite car_s;
	int random = getRandomCar();
	random = 1;
	std::cout << "RANDOM " << random << std::endl;
	car_s.setTexture(cars[random]);
	car_s.setPosition(100, 170);
	car_s.setOrigin(22, 22);

	Sprite swamp_s;
	swamp_s.setTexture(swamp);
	swamp_s.setPosition(422, 187.5);

	Sprite bush_s;
	bush_s.setTexture(bush);
	bush_s.setPosition(188, 560);

	Sprite house_s;
	house_s.setTexture(house);
	house_s.setPosition(550, 160);

	Sprite money_s;
	money_s.setTexture(money);
	money_s.setPosition(50, 50);

	int x_plane, y_plane;
	x_plane = 1300; y_plane = 710;
	Sprite plane_s;
	plane_s.setTexture(plane);
	plane_s.setPosition(x_plane, y_plane);

	// result bottom text
	Font font;
	if (!font.loadFromFile("edf7f-eirik-raude.ttf"))
		exit(0);

	Text result;
	result.setFont(font);
	result.setString("Result: \n\t0");
	result.setCharacterSize(43);
	result.setFillColor(Color(247, 168, 24));
	result.setOutlineColor(Color::Black);
	result.setOutlineThickness(1.f);
	result.move(1520, 70);

	Text time;
	time.setFont(font);
	time.setString("Timing: \n\t0");
	time.setCharacterSize(43);
	time.setFillColor(Color(247, 168, 24));
	time.setOutlineColor(Color::Black);
	time.setOutlineThickness(1.f);
	time.move(1520, 170);

	Text gameover;
	gameover.setFont(font);
	gameover.setString("G A M E O V E R\nR E S U L T: ");
	gameover.setCharacterSize(85);
	gameover.setFillColor(Color(247, 168, 24));
	gameover.setOutlineColor(Color::Black);
	gameover.setOutlineThickness(1.f);
	gameover.move(600, 270);

	Text recordtxt;
	recordtxt.setFont(font);
	recordtxt.setString("Your record: \n");
	recordtxt.setCharacterSize(85);
	recordtxt.setFillColor(Color(247, 168, 24));
	recordtxt.setOutlineColor(Color::Black);
	recordtxt.setOutlineThickness(1.f);
	recordtxt.move(600, 470);

	// important variables
	int timing = 0;
	float x = 100;
	float y = 170;
	float speed = 0;
	float angle = 0;
	float maxSpeed = 12.0;
	float acc = 0.2, dec = 0.3;
	float turnSpeed = 0.08;
	int AmountCollision = 0;
	int result_money = 0;
	bool eaten = true; int fg = 0;
	double x11 = 726, y11 = 467, x21 = 1018, y21 = 446, x31 = 856, y31 = 360;
	double x12 = 724, y12 = 472, x22 = 788, y22 = 518, x32 = 900, y32 = 460;
	double x13 = 900, y13 = 460, x23 = 972, y23 = 488, x33 = 1025, y33 = 450;
	int x_money = 0, y_money = 0;

	RectangleShape rectangle1(Vector2f(52.f, 38.f));
	rectangle1.move(44, 287);
	rectangle1.setFillColor(Color::White);

	RectangleShape rectangle2(Vector2f(55.f, 48.f));
	rectangle2.move(10, 308);
	rectangle2.setFillColor(Color::White);

	RectangleShape rectangle3(Vector2f(65.f, 58.f));
	rectangle3.move(133, 377);
	rectangle3.setFillColor(Color::White);

	RectangleShape rectangle4(Vector2f(68.f, 48.f));
	rectangle4.move(182, 351);
	rectangle4.setFillColor(Color::White);

	ConvexShape convex1;
	convex1.setPointCount(3);
	convex1.setPoint(0, Vector2f(726.f, 467.f));
	convex1.setPoint(1, Vector2f(1038.f, 454.f));
	convex1.setPoint(2, Vector2f(856.f, 360.f));
	convex1.setFillColor(Color::White);

	ConvexShape convex2;
	convex2.setPointCount(3);
	convex2.setPoint(0, Vector2f(726.f, 467.f));
	convex2.setPoint(1, Vector2f(790.f, 520.f));
	convex2.setPoint(2, Vector2f(902.f, 467.f));
	convex2.setFillColor(Color::White);

	ConvexShape convex3;
	convex3.setPointCount(3);
	convex3.setPoint(0, Vector2f(902.f, 467.f));
	convex3.setPoint(1, Vector2f(970.f, 487.f));
	convex3.setPoint(2, Vector2f(1030.f, 453.f));
	convex3.setFillColor(Color::White);

	auto begin_timing = std::chrono::steady_clock::now();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// get out
			if (event.type == Event::Closed)
				window.close(); // тогда закрываем его

			// getting fixed size
			if (event.type == Event::Resized)
			{
				std::cout << "trying to resize window" << std::endl;
				window.setSize(Vector2u(1651, 715));
			}
		}

		if (timing <= 60 && AmountCollision < 20)
		{
			bool Up = 0, Right = 0, Left = 0, Down = 0;

			if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) Right = 1;
			if (Right) std::cout << "right" << std::endl;
			if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) Left = 1;
			if (Left) std::cout << "left" << std::endl;
			if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) Up = 1;
			if (Up) std::cout << "up" << std::endl;
			if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) Down = 1;
			if (Down) std::cout << "down" << std::endl;

			// car movement
			if (Up && speed < maxSpeed)
				if (speed < 0) speed += dec;
				else speed += acc;

			if (Down && speed > -maxSpeed)
				if (speed < 0) speed -= dec;
				else speed -= acc;

			if (!Up && !Down)
				if (speed - dec > 0) speed -= dec;
				else if (speed + dec < 0) speed += dec;
				else speed = 0;

			if (Right && speed != 0) angle += turnSpeed * speed / maxSpeed;
			if (Left && speed != 0) angle -= turnSpeed * speed / maxSpeed;

			// std::cout << "speed: " << speed << "\n" << "angle: "<< angle << std::endl;

			x += sin(angle) * speed;
			y -= cos(angle) * speed;

			// checking the end of the map
			if (x < 0 || y < 0 || x > 1650 || y > 710)
			{
				speed = 0 - speed * 0.75;
				if (abs(speed) < 0.4)
				{
					if (x < -5 || y < -5 || x > 1656 || y > 715)
					{
						if (x < -20 || y < -20 || x > 1670 || y > 730)
						{
							window.close();
							system("cls");
							HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(hConsole, 4);
							std::cout << "you okay? wtf you trying to do bro?" << std::endl;
							std::cout << "i don't like it.\n\n" << std::endl;
							std::cout << "THERE IS NO WAY THERE." << std::endl;
							Sleep(6000);
							SetConsoleTextAttribute(hConsole, 7);
							break;
						}
						else
						{
							if (x < -5)
							{
								x += 105;
								speed = -5;
							}
							if (y < -5)
							{
								y += 105;
								speed = -5;
							}
							if (x > 1656)
							{
								x -= 105;
								speed = -5;
							}
							if (y > 730)
							{
								y -= 105;
								speed = -5;
							}
						}
					}
				}
				else if (abs(speed) > 5)
					AmountCollision++;
			}

			// cheching the circles of bushes and swamp
			if (x > 44 && x < 96 && y > 287 && y < 325)
			{
				if (abs(speed) < 1)
					speed = 0 - speed * 1.5;
				else
					speed = 0 - speed * 0.75;
			}
			if (x > 10 && x < 65 && y > 308 && y < 356)
			{
				if (abs(speed) < 1)
					speed = 0 - speed * 1.5;
				else
					speed = 0 - speed * 0.75;
			}
			if (x > 133 && x < 180 && y > 377 && y < 407)
			{
				if (abs(speed) < 1)
					speed = 0 - speed * 1.5;
				else
					speed = 0 - speed * 0.75;
			}
			if (x > 182 && x < 242 && y > 351 && y < 385)
			{
				if (abs(speed) < 1)
					speed = 0 - speed * 1.5;
				else
					speed = 0 - speed * 0.75;
			}

			// cheching the house triangles

			/*
			bool abobus1 = triangle_check_fuck(x11, y11, x21, y21, x31, y31, x, y);
			std::cout << abobus << std::endl;
			*/

			int a1 = (x11 - x) * (y21 - y11) - (x21 - x11) * (y11 - y);
			int b1 = (x21 - x) * (y31 - y21) - (x31 - x21) * (y21 - y);
			int c1 = (x31 - x) * (y11 - y31) - (x11 - x31) * (y31 - y);
			if ((a1 > 0 && b1 > 0 && c1 > 0) || (a1 < 0 && b1 < 0 && c1 < 0) || (a1 == 0 || b1 == 0 || c1 == 0))
			{
				if (abs(speed) > 1)
				{
					speed = 0 - speed * 0.75;
					if (abs(speed) > 5)
						AmountCollision++;
				}
				else
					speed = 0 - speed * 1.5;
			}
			int a2 = (x12 - x) * (y22 - y12) - (x22 - x12) * (y12 - y);
			int b2 = (x22 - x) * (y32 - y22) - (x32 - x22) * (y22 - y);
			int c2 = (x32 - x) * (y12 - y32) - (x12 - x32) * (y32 - y);
			if ((a2 > 0 && b2 > 0 && c2 > 0) || (a2 < 0 && b2 < 0 && c2 < 0) || (a2 == 0 || b2 == 0 || c2 == 0))
			{
				if (abs(speed) > 1)
				{
					speed = 0 - speed * 0.75;
					if (abs(speed) > 5)
						AmountCollision++;
				}
				else
					speed = 0 - speed * 1.5;
			}
			int a3 = (x13 - x) * (y23 - y13) - (x23 - x13) * (y13 - y);
			int b3 = (x23 - x) * (y33 - y23) - (x33 - x23) * (y23 - y);
			int c3 = (x33 - x) * (y13 - y33) - (x13 - x33) * (y33 - y);
			if ((a3 > 0 && b3 > 0 && c3 > 0) || (a3 < 0 && b3 < 0 && c3 < 0) || (a3 == 0 || b3 == 0 || c3 == 0))
			{
				if (abs(speed) > 1)
				{
					speed = 0 - speed * 0.75;
					if (abs(speed) > 5)
						AmountCollision++;
				}
				else
					speed = 0 - speed * 1.5;

			}


			// cheching the circles of bushes and swamp
			if (abs(speed) > 1.0)
			{
				if ((x - 510) * (x - 510) + (y - 235) * (y - 235) <= pow(87.5, 2))
					speed *= 0.65;
				if ((x - 300) * (x - 300) + (y - 650) * (y - 650) <= pow(110, 2))
					speed *= 0.85;
				if ((x - 1267) * (x - 1267) + (y - 430) * (y - 430) <= pow(97.5, 2))
					speed *= 0.85;

				// speed and drift effect
				if (abs(speed) > 10.0 && (int)angle % 90 != 0 && !Down)
				{
					cars[random].setSmooth(true);
					car_s.setTexture(speed_cars[random]);
				}
				else
				{
					cars[random].setSmooth(false);
					car_s.setTexture(cars[random]);
				}
			}

			// money spawn
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(0, 9);

			if (eaten)
			{
				fg = dist(gen);
				x_money = arr[fg][0];
				y_money = arr[fg][1];
				std::cout << "IMPORTANT :::: " << x_money << " " << y_money << std::endl;
				money_s.setPosition(x_money, y_money);
				eaten = false;
				std::cout << x_money << "\t" << y_money << std::endl;
				result_money++;
			}

			if ((x_money + 46 - x) * (x_money + 46 - x) + (y_money + 46 - y) * (y_money + 46 - y) < 33*33)
			{
				eaten = true;
			}

			// car broken
			if (AmountCollision > 5)
			{
				if (AmountCollision > 10)
				{
					maxSpeed = 3.0;
					car_s.setTexture(cars_broken_hard[random]);
				}
				else
				{
					maxSpeed = 8.0;
					car_s.setTexture(cars_broken[random]);
				}
			}

			// getting timing
			auto end_timing = std::chrono::steady_clock::now();
			auto elapsed_ms_timing = std::chrono::duration_cast<std::chrono::milliseconds>(end_timing - begin_timing);
			timing = (float)elapsed_ms_timing.count() / 1000;
			std::cout << timing << std::endl;
			int timing_not_real = 60 - timing;
			time.setString("Timing: \n\t" + std::to_string(timing_not_real));


			// ambulance animation 
			if (random == 1 && abs(speed) > 1)
			{
				if (abs(speed) > 10.0 && (int)angle % 90 != 0 && !Down)
				{
					if (timing % 2 == 0)
						car_s.setTexture(ambulance_speed[0]);
					else if (timing % 2 == 1)
						car_s.setTexture(ambulance_speed[2]);
				}
				else
				{
					if (timing % 2 == 0)
						car_s.setTexture(speed_ambulance[0]);
					else if (timing % 2 == 1)
						car_s.setTexture(speed_ambulance[2]);
				}
			}
			else if (random == 1 && abs(speed) < 1)
			{
				car_s.setTexture(speed_ambulance[1]);
			}
		}

		if (timing > 60 || AmountCollision > 20)
		{
			background_s.setColor(Color(120, 120, 120));
			bridge_s.setColor(Color(120, 120, 120));
			car_s.setColor(Color(120, 120, 120));
			swamp_s.setColor(Color(120, 120, 120));
			bush_s.setColor(Color(120, 120, 120));
			house_s.setColor(Color(120, 120, 120));
			plane_s.setColor(Color(100, 100, 100));
			money_s.setColor(Color(100, 100, 100));
			result.setFillColor(Color(100, 100, 100));
			time.setFillColor(Color(120, 120, 120));
			time.setString("Timing: \n\t0");
		}

		// draw 1 MAIN
		window.clear(Color::White);
		window.draw(background_s);
		window.draw(swamp_s);

		car_s.setPosition(x, y);
		car_s.setRotation(angle * 180 / 3.141592);

		y_plane -= 1;
		plane_s.setPosition(x_plane, y_plane);

		result.setString("Result: \n\t" + std::to_string(result_money));

		// draw 2
		window.draw(car_s);
		window.draw(bridge_s);
		window.draw(bush_s);
		window.draw(house_s);
		window.draw(money_s);
		window.draw(result);
		window.draw(time);
		if (timing % 30 < 15)
		{
			y_plane = 710;
			window.draw(plane_s);
		}

		if (timing > 60 || AmountCollision > 20)
		{
			system("cls");
			int rec = FileWork(result_money);
			recordtxt.setString("Your record: " + std::to_string(rec));
			gameover.setString("G A M E O V E R\n R E S U L T: " + std::to_string(result_money));

			window.draw(gameover);
			window.draw(recordtxt);
		}

		/*
		* convex triangls house
		* rectangles bridge
		*
		if (timing % 2 == 0)
		{
			window.draw(convex1);
			window.draw(convex2);
			window.draw(convex3);
		}
		if (timing % 2 == 0)
		{
			window.draw(rectangle1);
			window.draw(rectangle2);
			window.draw(rectangle3);
			window.draw(rectangle4);
		}
		*/

		window.display();
	}
}

int main()
{
	racing();
	std::cout << "endline" << std::endl;

	return 0;
}