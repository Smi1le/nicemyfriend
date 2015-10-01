#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include <sstream>

using namespace std;

void moveBot()
{
	int random_number = rand() % 12 + 1;
	cout << "random_number = " << random_number << endl;
}

int main()
{

	RenderWindow window(sf::VideoMode(576, 576), "Chess!");
	Image map_image;
	map_image.loadFromFile("images/map.png");

	int chess_board[8][8] = 
	{
		{0, 2, 0, 2, 0, 2, 0, 2},
		{2, 0, 2, 0, 2, 0, 2, 0},
		{0, 2, 0, 2, 0, 2, 0, 2},
		{3, 0, 3, 0, 3, 0, 3, 0},
		{0, 3, 0, 3, 0, 3, 0, 3},
		{1, 0, 1, 0, 1, 0, 1, 0},
		{0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 0}
	};

	int coor[9] = {0, 72, 144, 216, 288, 360, 432, 504, 576};
	

	Texture background_texture;
	background_texture.loadFromFile("images/background.png");
	Texture map;
	map.loadFromImage(map_image);
	Texture white_chess_texture;
	white_chess_texture.loadFromFile("images/white_chess.png");
	Texture black_chess_texture;
	black_chess_texture.loadFromFile("images/black_chess.png");

	Sprite background_sprite;
	background_sprite.setTexture(background_texture);
	background_sprite.setPosition(0, 0);
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(0, 0);

	Sprite wc1_sprite;
	wc1_sprite.setTexture(white_chess_texture);
	wc1_sprite.setPosition(72, 0);

	Sprite wc2_sprite;
	wc2_sprite.setTexture(white_chess_texture);
	wc2_sprite.setPosition(216, 0);
	Sprite wc3_sprite;
	wc3_sprite.setTexture(white_chess_texture);
	wc3_sprite.setPosition(360, 0);

	Sprite wc4_sprite;
	wc4_sprite.setTexture(white_chess_texture);
	wc4_sprite.setPosition(504, 0);

	Sprite wc5_sprite;
	wc5_sprite.setTexture(white_chess_texture);
	wc5_sprite.setPosition(0, 72);

	Sprite wc6_sprite;
	wc6_sprite.setTexture(white_chess_texture);
	wc6_sprite.setPosition(144, 72);

	Sprite wc7_sprite;
	wc7_sprite.setTexture(white_chess_texture);
	wc7_sprite.setPosition(288, 72);

	Sprite wc8_sprite;
	wc8_sprite.setTexture(white_chess_texture);
	wc8_sprite.setPosition(432, 72);

	Sprite wc9_sprite;
	wc9_sprite.setTexture(white_chess_texture);
	wc9_sprite.setPosition(72, 144);

	Sprite wc10_sprite;
	wc10_sprite.setTexture(white_chess_texture);
	wc10_sprite.setPosition(216, 144);

	Sprite wc11_sprite;
	wc11_sprite.setTexture(white_chess_texture);
	wc11_sprite.setPosition(360, 144);

	Sprite wc12_sprite;
	wc12_sprite.setTexture(white_chess_texture);
	wc12_sprite.setPosition(504, 144);

	Sprite bc1_sprite;
	bc1_sprite.setTexture(black_chess_texture);
	bc1_sprite.setPosition(0, 360);// 0 - по горизонтали, 360 - по вертикали

	Sprite bc2_sprite;
	bc2_sprite.setTexture(black_chess_texture);
	bc2_sprite.setPosition(144, 360);

	Sprite bc3_sprite;
	bc3_sprite.setTexture(black_chess_texture);
	bc3_sprite.setPosition(288, 360);

	Sprite bc4_sprite;
	bc4_sprite.setTexture(black_chess_texture);
	bc4_sprite.setPosition(432, 360);

	Sprite bc5_sprite;
	bc5_sprite.setTexture(black_chess_texture);
	bc5_sprite.setPosition(72, 432);

	Sprite bc6_sprite;
	bc6_sprite.setTexture(black_chess_texture);
	bc6_sprite.setPosition(216, 432);

	Sprite bc7_sprite;
	bc7_sprite.setTexture(black_chess_texture);
	bc7_sprite.setPosition(360, 432);

	Sprite bc8_sprite;
	bc8_sprite.setTexture(black_chess_texture);
	bc8_sprite.setPosition(504, 432);

	Sprite bc9_sprite;
	bc9_sprite.setTexture(black_chess_texture);
	bc9_sprite.setPosition(0, 504);

	Sprite bc10_sprite;
	bc10_sprite.setTexture(black_chess_texture);
	bc10_sprite.setPosition(144, 504);

	Sprite bc11_sprite;
	bc11_sprite.setTexture(black_chess_texture);
	bc11_sprite.setPosition(288, 504);

	Sprite bc12_sprite;
	bc12_sprite.setTexture(black_chess_texture);
	bc12_sprite.setPosition(432, 504);

	//String map[32] = {
	//	"a1: "
	//};

	bool isBegun = false;
	bool start = true;
	int num;
	bool youMove = true;
	Clock clock;
	bool isMove = false;//переменная для щелчка мыши по спрайту
	float dX = 0;//корректировка движения по х
	float dY = 0;//по у
	//int num;
	int coord_x;
	int coord_y;
	int place;
	int k;
	int i;
	int column_cell;
	int string_cell;
	int last_column_cell;
	int last_string_cell;
	int last_x;
	int last_y;
	Sprite * name_sprite;
	num = 0;
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
		//std::cout << pixelPos.x << "\n";//смотрим на координату Х позиции курсора в консоли (она не будет больше ширины окна)
		//std::cout << pos.x << "\n";//смотрим на Х,которая преобразовалась в мировые координаты

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (youMove)
			{
				if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
					if (event.key.code == Mouse::Left)
					{    //а именно левая
						k = 0;
						while (k < 9)
						{
							if (pos.x < coor[k])
							{
								last_string_cell = k - 1;
								k = 8;
							}
							k = k + 1;
							std::cout << "k" << k << "\n";

						}
						k = 0;
						while (k < 9)
						{
							if (pos.y < coor[k])
							{
								last_column_cell = k - 1;
								k = 8;
							}
							k = k + 1;
						}
						if (bc1_sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
						{
							dX = pos.x - bc1_sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dY = pos.y - bc1_sprite.getPosition().y;//тоже самое по игреку
							isMove = true;//можем двигать спрайт
							last_x = bc1_sprite.getPosition().x;
							last_y = bc1_sprite.getPosition().y;
							name_sprite =& bc1_sprite;
							num = 13;
						}
						if (bc2_sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
						{
							dX = pos.x - bc2_sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dY = pos.y - bc2_sprite.getPosition().y;//тоже самое по игреку
							isMove = true;//можем двигать спрайт
							last_x = bc2_sprite.getPosition().x;
							last_y = bc2_sprite.getPosition().y;
							name_sprite =& bc2_sprite;
							num = 14;
						}
						if (bc3_sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
						{
							dX = pos.x - bc3_sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dY = pos.y - bc3_sprite.getPosition().y;//тоже самое по игреку
							isMove = true;//можем двигать спрайт
							last_x = bc3_sprite.getPosition().x;
							last_y = bc3_sprite.getPosition().y;
							name_sprite =& bc3_sprite;
							num = 15;
						}
						if (bc4_sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
						{
							dX = pos.x - bc4_sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dY = pos.y - bc4_sprite.getPosition().y;//тоже самое по игреку
							isMove = true;//можем двигать спрайт
							last_x = bc4_sprite.getPosition().x;
							last_y = bc4_sprite.getPosition().y;
							name_sprite =& bc4_sprite;
							num = 16;
						}
						if (bc5_sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
						{
							dX = pos.x - bc5_sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dY = pos.y - bc5_sprite.getPosition().y;//тоже самое по игреку
							isMove = true;//можем двигать спрайт
							last_x = bc5_sprite.getPosition().x;
							last_y = bc5_sprite.getPosition().y;
							name_sprite =& bc5_sprite;
							num = 17;
						}
						if (bc6_sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
						{
							dX = pos.x - bc6_sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dY = pos.y - bc6_sprite.getPosition().y;//тоже самое по игреку
							isMove = true;//можем двигать спрайт
							last_x = bc6_sprite.getPosition().x;
							last_y = bc6_sprite.getPosition().y;
							name_sprite =& bc6_sprite;
							num = 18;
						}
						if (bc7_sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
						{
							dX = pos.x - bc7_sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dY = pos.y - bc7_sprite.getPosition().y;//тоже самое по игреку
							isMove = true;//можем двигать спрайт
							last_x = bc7_sprite.getPosition().x;
							last_y = bc7_sprite.getPosition().y;
							name_sprite =& bc7_sprite;
							num = 19;
						}
						if (bc8_sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
						{
							dX = pos.x - bc8_sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dY = pos.y - bc8_sprite.getPosition().y;//тоже самое по игреку
							isMove = true;//можем двигать спрайт
							last_x = bc8_sprite.getPosition().x;
							last_y = bc8_sprite.getPosition().y;
							name_sprite =& bc8_sprite;
							num = 20;
						}
						if (bc9_sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
						{
							dX = pos.x - bc9_sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dY = pos.y - bc9_sprite.getPosition().y;//тоже самое по игреку
							isMove = true;//можем двигать спрайт
							last_x = bc9_sprite.getPosition().x;
							last_y = bc9_sprite.getPosition().y;
							name_sprite =& bc9_sprite;
							num = 21;
						}
						if (bc10_sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
						{
							dX = pos.x - bc10_sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dY = pos.y - bc10_sprite.getPosition().y;//тоже самое по игреку
							isMove = true;//можем двигать спрайт
							last_x = bc10_sprite.getPosition().x;
							last_y = bc10_sprite.getPosition().y;
							name_sprite =& bc10_sprite;
							num = 22;
						}
						if (bc11_sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
						{
							dX = pos.x - bc11_sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dY = pos.y - bc11_sprite.getPosition().y;//тоже самое по игреку
							isMove = true;//можем двигать спрайт
							last_x = bc11_sprite.getPosition().x;
							last_y = bc11_sprite.getPosition().y;
							name_sprite =& bc11_sprite;
							num = 23;
						}
						if (bc12_sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
						{
							dX = pos.x - bc12_sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dY = pos.y - bc12_sprite.getPosition().y;//тоже самое по игреку
							isMove = true;//можем двигать спрайт
							last_x = bc12_sprite.getPosition().x;
							last_y = bc12_sprite.getPosition().y;
							name_sprite =& bc12_sprite;
							num = 24;
						}
					}
				if (event.type == Event::MouseButtonReleased)//если отпустили клавишу
					if (event.key.code == Mouse::Left) //а именно левую
					{
						isMove = false; //то не можем двигать спрайт
						k = 0;
						while (k < 9)
						{
							if (pos.x < coor[k])
							{
								std::cout << "k.x" << k << "\n";
								coord_x = coor[k - 1];
								string_cell = k - 1;
								k = 8;
							}
							k = k + 1;
							std::cout << "k" << k << "\n";

						}
						k = 0;
						while (k < 9)
						{
							if (pos.y < coor[k])
							{
								std::cout << "k.y" << k << "\n";
								coord_y = coor[k - 1];
								column_cell = k - 1;
								k = 8;
							}
							k = k + 1;
						}
						//std::cout << coord_y << "\n";
						//std::cout << coord_x << "\n";
						//std::cout << "chess_board[column_cell][string_cell]" << chess_board[column_cell][string_cell] << "\n";
						//std::cout << coord_x << "\n";
						if (chess_board[column_cell][string_cell] != 0)
						{
							if (chess_board[column_cell][string_cell] == 2 || chess_board[column_cell][string_cell] == 1)
							{
								
								std::cout << "Trolololololo" << endl;
								std::cout << "num = " << num << endl;
								std::cout << "chess_board[column_cell][string_cell]2 = " << chess_board[column_cell][string_cell] << endl;
								std::cout << "last_string_cell2 = " << last_string_cell << endl;
								std::cout << "last_column_cell2 = " << last_column_cell << endl;
								std::cout << "string_cell12 = " << string_cell << endl;
								std::cout << "column_cell2 = " << column_cell << endl;
								std::cout << "coor[last_column_cell] = " << coor[last_column_cell] << endl;
								std::cout << "coor[last_string_cell] = " << coor[last_string_cell] << endl;
								if (num == 13) {
									bc1_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
									bc1_sprite.setColor(Color::White);//красим спрайт в красный
								}
								if (num == 14) {
									bc2_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
									bc2_sprite.setColor(Color::White);//красим спрайт в красный
								}
								if (num == 15) {
									bc3_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
									bc3_sprite.setColor(Color::White);//красим спрайт в красный
								}
								if (num == 16) {
									bc4_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
									bc4_sprite.setColor(Color::White);//красим спрайт в красный
								}
								if (num == 17) {
									bc5_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
									bc5_sprite.setColor(Color::White);//красим спрайт в красный
								}
								if (num == 18) {
									bc6_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
									bc6_sprite.setColor(Color::White);//красим спрайт в красный
								}
								if (num == 19) {
									bc7_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
									bc7_sprite.setColor(Color::White);//красим спрайт в красный
								}
								if (num == 20) {
									bc8_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
									bc8_sprite.setColor(Color::White);//красим спрайт в красный
								}
								if (num == 21) {
									bc9_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
									bc9_sprite.setColor(Color::White);//красим спрайт в красный
								}
								if (num == 22) {
									bc10_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
									bc10_sprite.setColor(Color::White);//красим спрайт в красный
								}
								if (num == 23) {
									bc11_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
									bc11_sprite.setColor(Color::White);//красим спрайт в красный
								}
								if (num == 24) {
									bc12_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
									bc12_sprite.setColor(Color::White);//красим спрайт в красный
								}

							} //

							if (chess_board[column_cell][string_cell] == 3)
							{
								std::cout << "chess_board[column_cell][string_cell] = " << chess_board[column_cell][string_cell] << endl;
								std::cout << "last_string_cell = " << last_string_cell << endl;
								std::cout << "last_column_cell = " << last_column_cell << endl;
								std::cout << "string_cell = " << string_cell << endl;
								std::cout << "column_cell = " << column_cell << endl;
								if ((last_column_cell - column_cell) == 1) // Проверка на возможность хода для нашей шашки
								{
									if ((last_string_cell - string_cell) == 1 || (last_string_cell - string_cell) == -1)
									{
										if (num == 13) {
											bc1_sprite.setPosition(coord_x, coord_y);
											bc1_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 14) {
											bc2_sprite.setPosition(coord_x, coord_y);
											bc2_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 15) {
											bc3_sprite.setPosition(coord_x, coord_y);
											bc3_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 16) {
											bc4_sprite.setPosition(coord_x, coord_y);
											bc4_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 17) {
											bc5_sprite.setPosition(coord_x, coord_y);
											bc5_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 18) {
											bc6_sprite.setPosition(coord_x, coord_y);
											bc6_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 19) {
											bc7_sprite.setPosition(coord_x, coord_y);
											bc7_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 20) {
											bc8_sprite.setPosition(coord_x, coord_y);
											bc8_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 21) {
											bc9_sprite.setPosition(coord_x, coord_y);
											bc9_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 22) {
											bc10_sprite.setPosition(coord_x, coord_y);
											bc10_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 23) {
											bc11_sprite.setPosition(coord_x, coord_y);
											bc11_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 24) {
											bc12_sprite.setPosition(coord_x, coord_y);
											bc12_sprite.setColor(Color::White);//красим спрайт в красный
										}
										chess_board[last_column_cell][last_string_cell] = 3;
										chess_board[column_cell][string_cell] = 1;
									}
								}
								if ((last_column_cell - column_cell) == -1) //Удостоверяемся что наша шашка не пойдет назад
								{
									if ((last_string_cell - string_cell) == 1 || (last_string_cell - string_cell) == -1)
									{
										if (num == 13) {
											bc1_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
											bc1_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 14) {
											bc2_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
											bc2_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 15) {
											bc3_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
											bc3_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 16) {
											bc4_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
											bc4_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 17) {
											bc5_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
											bc5_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 18) {
											bc6_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
											bc6_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 19) {
											bc7_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
											bc7_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 20) {
											bc8_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
											bc8_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 21) {
											bc9_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
											bc9_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 22) {
											bc10_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
											bc10_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 23) {
											bc11_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
											bc11_sprite.setColor(Color::White);//красим спрайт в красный
										}
										if (num == 24) {
											bc12_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
											bc12_sprite.setColor(Color::White);//красим спрайт в красный
										}
									}
								}
								if ((last_column_cell - column_cell) == 2) // Проверка на возможность хода для нашей шашки
								{
									if ((last_string_cell - string_cell) == 2 || (last_string_cell - string_cell) == -2)
									{
										std::cout<<"chess_board[column_cell + 1][string_cell + 1] = " << chess_board[column_cell + 1][string_cell + 1] << endl;
										if (chess_board[column_cell + 1][string_cell + 1] == 2)
										{
											if (num == 13) {
												bc1_sprite.setPosition(coord_x, coord_y);
												bc1_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 14) {
												bc2_sprite.setPosition(coord_x, coord_y);
												bc2_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 15) {
												bc3_sprite.setPosition(coord_x, coord_y);
												bc3_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 16) {
												bc4_sprite.setPosition(coord_x, coord_y);
												bc4_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 17) {
												bc5_sprite.setPosition(coord_x, coord_y);
												bc5_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 18) {
												bc6_sprite.setPosition(coord_x, coord_y);
												bc6_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 19) {
												bc7_sprite.setPosition(coord_x, coord_y);
												bc7_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 20) {
												bc8_sprite.setPosition(coord_x, coord_y);
												bc8_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 21) {
												bc9_sprite.setPosition(coord_x, coord_y);
												bc9_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 22) {
												bc10_sprite.setPosition(coord_x, coord_y);
												bc10_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 23) {
												bc11_sprite.setPosition(coord_x, coord_y);
												bc11_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 24) {
												bc12_sprite.setPosition(coord_x, coord_y);
												bc12_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (wc1_sprite.getGlobalBounds().contains(coor[string_cell + 1], coor[column_cell + 1]))
											{
												for (i = 1; i < 3000; i++)
												{
													wc1_sprite.move(-0.1 * i, 0);
												}
											}
											if (wc2_sprite.getGlobalBounds().contains(coor[string_cell + 1], coor[column_cell + 1]))
											{
												for (i = 1; i < 3000; i++)
												{
													wc2_sprite.move(-0.1 * i, 0);
												}
											}
											if (wc3_sprite.getGlobalBounds().contains(coor[string_cell + 1], coor[column_cell + 1]))
											{
												for (i = 1; i < 3000; i++)
												{
													wc3_sprite.move(-0.1 * i, 0);
												}
											}
											if (wc4_sprite.getGlobalBounds().contains(coor[string_cell + 1], coor[column_cell + 1]))
											{
												for (i = 1; i < 3000; i++)
												{
													wc4_sprite.move(-0.1 * i, 0);
												}
											}
											if (wc5_sprite.getGlobalBounds().contains(coor[string_cell + 1], coor[column_cell + 1]))
											{
												for (i = 1; i < 3000; i++)
												{
													wc5_sprite.move(-0.1 * i, 0);
												}
											}
											if (wc6_sprite.getGlobalBounds().contains(coor[string_cell + 1], coor[column_cell + 1]))
											{
												for (i = 1; i < 3000; i++)
												{
													wc6_sprite.move(-0.1 * i, 0);
												}
											}
											if (wc7_sprite.getGlobalBounds().contains(coor[string_cell + 1], coor[column_cell + 1]))
											{
												for (i = 1; i < 3000; i++)
												{
													wc7_sprite.move(-0.1 * i, 0);
												}
											}
											if (wc8_sprite.getGlobalBounds().contains(coor[string_cell + 1], coor[column_cell + 1]))
											{
												for (i = 1; i < 3000; i++)
												{
													wc8_sprite.move(-0.1 * i, 0);
												}
											}
											if (wc9_sprite.getGlobalBounds().contains(coor[string_cell + 1], coor[column_cell + 1]))
											{
												for (i = 1; i < 3000; i++)
												{
													wc9_sprite.move(-0.1 * i, 0);
												}
											}
											if (wc10_sprite.getGlobalBounds().contains(coor[string_cell + 1], coor[column_cell + 1]))
											{
												for (i = 1; i < 3000; i++)
												{
													wc10_sprite.move(-0.1 * i, 0);
												}
											}
											if (wc11_sprite.getGlobalBounds().contains(coor[string_cell + 1], coor[column_cell + 1]))
											{
												for (i = 1; i < 3000; i++)
												{
													wc11_sprite.move(-0.1 * i, 0);
												}
											}
											if (wc12_sprite.getGlobalBounds().contains(coor[string_cell + 1], coor[column_cell + 1]))
											{
												for (i = 1; i < 3000; i++)
												{
													wc12_sprite.move(-0.1 * i, 0);
												}
											}
											chess_board[last_column_cell][last_string_cell] = 3;
											chess_board[column_cell][string_cell] = 1;
										}
										else 
										{
											if (num == 13) {
												bc1_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
												bc1_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 14) {
												bc2_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
												bc2_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 15) {
												bc3_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
												bc3_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 16) {
												bc4_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
												bc4_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 17) {
												bc5_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
												bc5_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 18) {
												bc6_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
												bc6_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 19) {
												bc7_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
												bc7_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 20) {
												bc8_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
												bc8_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 21) {
												bc9_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
												bc9_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 22) {
												bc10_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
												bc10_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 23) {
												bc11_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
												bc11_sprite.setColor(Color::White);//красим спрайт в красный
											}
											if (num == 24) {
												bc12_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
												bc12_sprite.setColor(Color::White);//красим спрайт в красный
											}
										}
									}
								}
								
							}
						}
						else
						{
							if (num == 13) {
								bc1_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
								bc1_sprite.setColor(Color::White);//красим спрайт в красный
							}
							if (num == 14) {
								bc2_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
								bc2_sprite.setColor(Color::White);//красим спрайт в красный
							}
							if (num == 15) {
								bc3_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
								bc3_sprite.setColor(Color::White);//красим спрайт в красный
							}
							if (num == 16) {
								bc4_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
								bc4_sprite.setColor(Color::White);//красим спрайт в красный
							}
							if (num == 17) {
								bc5_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
								bc5_sprite.setColor(Color::White);//красим спрайт в красный
							}
							if (num == 18) {
								bc6_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
								bc6_sprite.setColor(Color::White);//красим спрайт в красный
							}
							if (num == 19) {
								bc7_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
								bc7_sprite.setColor(Color::White);//красим спрайт в красный
							}
							if (num == 20) {
								bc8_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
								bc8_sprite.setColor(Color::White);//красим спрайт в красный
							}
							if (num == 21) {
								bc9_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
								bc9_sprite.setColor(Color::White);//красим спрайт в красный
							}
							if (num == 22) {
								bc10_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
								bc10_sprite.setColor(Color::White);//красим спрайт в красный
							}
							if (num == 23) {
								bc11_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
								bc11_sprite.setColor(Color::White);//красим спрайт в красный
							}
							if (num == 24) {
								bc12_sprite.setPosition(coor[last_string_cell], coor[last_column_cell]);
								bc12_sprite.setColor(Color::White);//красим спрайт в красный
							}
						}
					}
				if (isMove) {//если можем двигать
					if (num == 1) {
						wc1_sprite.setColor(Color::Red);//красим спрайт в красный
						wc1_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 2) {
						wc2_sprite.setColor(Color::Red);//красим спрайт в красный
						wc2_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 3) {
						wc3_sprite.setColor(Color::Red);//красим спрайт в красный
						wc3_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 4) {
						wc4_sprite.setColor(Color::Red);//красим спрайт в красный
						wc4_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 5) {
						wc5_sprite.setColor(Color::Red);//красим спрайт в красный
						wc5_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 6) {
						wc6_sprite.setColor(Color::Red);//красим спрайт в красный
						wc6_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 7) {
						wc7_sprite.setColor(Color::Red);//красим спрайт в красный
						wc7_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 8) {
						wc8_sprite.setColor(Color::Red);//красим спрайт в красный
						wc8_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 9) {
						wc9_sprite.setColor(Color::Red);//красим спрайт в красный
						wc9_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 10) {
						wc10_sprite.setColor(Color::Red);//красим спрайт в красный
						wc10_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 11) {
						wc11_sprite.setColor(Color::Red);//красим спрайт в красный
						wc11_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 12) {
						wc12_sprite.setColor(Color::Red);//красим спрайт в красный
						wc12_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 13) {
						bc1_sprite.setColor(Color::Red);//красим спрайт в красный
						bc1_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 14) {
						bc2_sprite.setColor(Color::Red);//красим спрайт в красный
						bc2_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 15) {
						bc3_sprite.setColor(Color::Red);//красим спрайт в красный
						bc3_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 16) {
						bc4_sprite.setColor(Color::Red);//красим спрайт в красный
						bc4_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 17) {
						bc5_sprite.setColor(Color::Red);//красим спрайт в красный
						bc5_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 18) {
						bc6_sprite.setColor(Color::Red);//красим спрайт в красный
						bc6_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 19) {
						bc7_sprite.setColor(Color::Red);//красим спрайт в красный
						bc7_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 20) {
						bc8_sprite.setColor(Color::Red);//красим спрайт в красный
						bc8_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 21) {
						bc9_sprite.setColor(Color::Red);//красим спрайт в красный
						bc9_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 22) {
						bc10_sprite.setColor(Color::Red);//красим спрайт вкрасный
						bc10_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 23) {
						bc11_sprite.setColor(Color::Red);//красим спрайт в красный
						bc11_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
					if (num == 24) {
						bc12_sprite.setColor(Color::Red);//красим спрайт в красный
						bc12_sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
					}
				}
			}


			if (isBegun)
			{
				window.clear();
				window.draw(background_sprite);
				window.display();
			}
			else
			{
				window.clear();
				window.draw(s_map);
				window.draw(wc1_sprite);
				window.draw(wc2_sprite);
				window.draw(wc3_sprite);
				window.draw(wc4_sprite);
				window.draw(wc5_sprite);
				window.draw(wc6_sprite);
				window.draw(wc7_sprite);
				window.draw(wc8_sprite);
				window.draw(wc9_sprite);
				window.draw(wc10_sprite);
				window.draw(wc11_sprite);
				window.draw(wc12_sprite);
				window.draw(bc1_sprite);
				window.draw(bc2_sprite);
				window.draw(bc3_sprite);
				window.draw(bc4_sprite);
				window.draw(bc5_sprite);
				window.draw(bc6_sprite);
				window.draw(bc7_sprite);
				window.draw(bc8_sprite);
				window.draw(bc9_sprite);
				window.draw(bc10_sprite);
				window.draw(bc11_sprite);
				window.draw(bc12_sprite);
				window.display();
			}
		}

	}
	return 0;
}