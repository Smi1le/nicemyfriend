#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

struct chess
{
	void det_coor(Sprite &sprite,int &x, int&y)
	{
		x = sprite.getPosition().x;
		y = sprite.getPosition().y;
	}

	void random(int &number)
	{
		number = rand() % 12 + 1;
	}
	
	void draw(Sprite &name_sprite, RenderWindow &win)
	{
		win.draw(name_sprite);
	}
	
	void move_checkers(Sprite &sprite, float pos_x, float pos_y, float d_X, float d_Y)
	{
		sprite.setPosition(pos_x - d_X, pos_y - d_Y);
		sprite.setColor(Color::Blue);
	}

	void move_step(Sprite &sprite, int x, int y)
	{
		sprite.setPosition(x, y);
		sprite.setColor(Color::White);
	}
	
	void return_back(int coordinate[], int l_column, int l_string, Sprite &sprite)
	{
		sprite.setPosition(coordinate[l_string], coordinate[l_column]);
		sprite.setColor(Color::White);
	}
};



void specific_cell(float position,int coord[], int &last_cell, int &coordinate)
{
	int k;
	k = 0;
	while (k < 9)
	{
		if (position < coord[k])
		{
			coordinate = coord[k - 1];
			last_cell = k - 1;
			k = 9;
		}
		k = k + 1;
	}
}

void definition_sprite(Sprite name_sprite[],float pos_x,float pos_y,float &d_X, float &d_Y, bool &move, int &num)
{
	int k;
	k = 0;
	while (k < 12)
	{
		if (name_sprite[k].getGlobalBounds().contains(pos_x, pos_y))
		{
			d_X = pos_x - name_sprite[k].getPosition().x;
			d_Y = pos_y - name_sprite[k].getPosition().y;
			move = true;
			num = k;
			k = 12;
		}
		k = k + 1;
	}
}

int main()
{
	RenderWindow window(sf::VideoMode(576, 576), "SFML works!");

	int chess_board[8][8] =
	{
		{ 0, 2, 0, 2, 0, 2, 0, 2 },
		{ 2, 0, 2, 0, 2, 0, 2, 0 },
		{ 0, 2, 0, 2, 0, 2, 0, 2 },
		{ 3, 0, 3, 0, 3, 0, 3, 0 },
		{ 0, 3, 0, 3, 0, 3, 0, 3 },
		{ 1, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0 }
	};
	
	int coor[9] = { 0, 72, 144, 216, 288, 360, 432, 504, 576 };
	int black_king[12], white_king[12];
	int last_string_cell, last_column_cell, string_cell, column_cell, coord_x, coord_y;
	int trashcan;
	int number, number_step;
	int bot_x, bot_y;
	int count, random_string, random_column;
	int number_checker_bot;
	int kyky_1, kyky_2;
	int white_dead[13];
	int de = 0;
	bool isMove = false;
	bool youMove = true;
	bool draw, white_move, live;
	bool white_live[12] = { true, true, true, true, true, true, true, true, true, true, true, true };
	bool black_live[12] = { true, true, true, true, true, true, true, true, true, true, true, true };
	float dX = 0;
	float dY = 0;
	int windows = 1;
	int i, j;
	int num_live_black = 12;


	Texture map;
	map.loadFromFile("images/map.png");
	
	Texture white_chess_texture;
	white_chess_texture.loadFromFile("images/white_chess.png");
	
	Texture black_chess_texture;
	black_chess_texture.loadFromFile("images/black_chess.png");

	Sprite white_chess[13], black_chess[13], king_white[13], king_black[13];
	
	coord_x = 72;
	coord_y = 0;
	for (j = 0;j < 12; j++)
	{
		white_chess[j].setTexture(white_chess_texture);
		white_chess[j].setPosition(coord_x, coord_y);
		if (coord_x == 432)
		{
			coord_x = -72;
			coord_y += 72;
		}
		if (coord_x == 504)
		{
			coord_x = -144;
			coord_y += 72;
		}
		coord_x += 144;
	}
	coord_x = 0;
	coord_y = 360;
	for (i = 0; i < 12; i++)
	{
		black_chess[i].setTexture(black_chess_texture);
		black_chess[i].setPosition(coord_x, coord_y);
		if (coord_x == 504)
		{
			
			coord_x = -144;	
			coord_y += 72;
		}
		if (coord_x == 432)
		{
			coord_x = -72;
			coord_y += 72;
		}
		coord_x += 144;
	}

	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(0, 0);

	//Sprite *black_chess[12] = { &bc1_sprite, &bc2_sprite, &bc3_sprite, &bc4_sprite, &bc5_sprite, &bc6_sprite, &bc7_sprite, &bc8_sprite, &bc9_sprite, &bc10_sprite, &bc11_sprite, &bc12_sprite };
	//Sprite *black_chess[12] = { &bc1_sprite, &bc2_sprite, &bc3_sprite, &bc4_sprite, &bc5_sprite, &bc6_sprite, &bc7_sprite, &bc8_sprite, &bc9_sprite, &bc10_sprite, &bc11_sprite, &bc12_sprite };
	chess black;
	chess white;
	while (window.isOpen())
	{
		sf::Event event;

		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			chess black;
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if ((event.key.code == Mouse::Left) && (youMove))
				{
					specific_cell(pos.x, coor, last_string_cell, trashcan) ;
					specific_cell(pos.y, coor, last_column_cell, trashcan);
					definition_sprite(black_chess, pos.x, pos.y, dX, dY, isMove, number);
					/*cout << "pos.x = " << pos.x << endl;
					cout << "pos.y = " << pos.y << endl;
					cout << "dX = " << dX << endl;
					cout << "dY = " << dY << endl;
					cout << "isMove = " << isMove << endl;
					cout << "number = " << number << endl;
					cout << "last_string_cell = " << last_string_cell << endl;
					cout << "last_column_cell = " << last_column_cell << endl;
					cout << "trashcan = " << trashcan << endl;*/

				}
			if (event.type == Event::MouseButtonReleased && isMove && youMove)//если отпустили клавишу
				if (event.key.code == Mouse::Left)
				{
					isMove = false;
						specific_cell(pos.x, coor, string_cell, coord_x);
						specific_cell(pos.y, coor, column_cell, coord_y);
						if (chess_board[column_cell][string_cell] != 0)
						{
							if ((chess_board[column_cell][string_cell] == 2) || (chess_board[column_cell][string_cell] == 1))
							{
								black.return_back(coor, last_column_cell, last_string_cell, black_chess[number]);
								//black_chess[number].setPosition(coor[last_string_cell], coor[last_column_cell]);
								//black_chess[number].setColor(Color::White);
							}
							if (chess_board[column_cell][string_cell] == 3)
							{
								if ((last_column_cell - column_cell) == -1)
								{
									if ((last_string_cell - string_cell) == 1 || (last_string_cell - string_cell) == -1)
									{
										black.return_back(coor, last_column_cell, last_string_cell, black_chess[number]);
										//black.move_one_step(black_chess[number], coord_x, coord_y);
										chess_board[last_column_cell][last_string_cell] = 3;
										chess_board[column_cell][string_cell] = 2;
									}
									else
									{
										black.return_back(coor, last_column_cell, last_string_cell, black_chess[number]);
									}
								}
								else if ((last_column_cell - column_cell) == 1)
								{
									if ((last_string_cell - string_cell) == 1 || (last_string_cell - string_cell) == -1)
									{
										black.move_step(black_chess[number], coord_x, coord_y);
										chess_board[last_column_cell][last_string_cell] = 3;
										chess_board[column_cell][string_cell] = 1;
									}
									else
									{
										black.return_back(coor, last_column_cell, last_string_cell, black_chess[number]);
									}
									youMove = false;
								}
								else if ((last_column_cell - column_cell) == 2)
								{
									if ((last_string_cell - string_cell) == 2 || (last_string_cell - string_cell) == -2)
									{
										if (chess_board[column_cell + 1][string_cell + ((last_string_cell - string_cell) / 2)] == 2)
										{
											black.move_step(black_chess[number], coord_x, coord_y);
											for (i = 0; i < 12; i++)
											{
												if (white_chess[i].getGlobalBounds().contains(coor[string_cell + ((last_string_cell - string_cell) / 2)], coor[column_cell + 1]))
												{
													white_dead[de] = i;
													de = de + 1;
													white_live[i] = false;
												}
											}
											chess_board[column_cell + 1][string_cell + ((last_string_cell - string_cell) / 2)] = 3;
											chess_board[last_column_cell][last_string_cell] = 3;
											chess_board[column_cell][string_cell] = 1;
										}
										else
										{
											black.return_back(coor, last_column_cell, last_string_cell, black_chess[number]);
										}
									}
									else
									{
										black.return_back(coor, last_column_cell, last_string_cell, black_chess[number]);
									}
								}
								else if ((last_column_cell - column_cell) == -2)
								{
									if ((last_string_cell - string_cell) == 2 || (last_string_cell - string_cell) == -2)
									{
										if (chess_board[column_cell - 1][string_cell + ((last_string_cell - string_cell) / 2)] == 2)
										{
											black.move_step(black_chess[number], coord_x, coord_y);
											for (i = 0; i < 12; i++)
											{
												
												if (white_chess[i].getGlobalBounds().contains(coor[string_cell + ((last_string_cell - string_cell) / 2)], coor[column_cell - 1]))
												{
													std::cout << "fdfdf" << endl;
													white_dead[de] = i + 1;
													de = de + 1;
													white_live[i] = false;
												}
											}
											chess_board[column_cell - 1][string_cell + ((last_string_cell - string_cell) / 2)] = 3;
											chess_board[last_column_cell][last_string_cell] = 3;
											chess_board[column_cell][string_cell] = 1;
										}
										else
										{
											black.return_back(coor, last_column_cell, last_string_cell, black_chess[number]);
										}
									}
									else {
										black.return_back(coor, last_column_cell, last_string_cell, black_chess[number]);
									}
								}
								else //if (((last_column_cell - column_cell) == 0))
								{
									black.return_back(coor, last_column_cell, last_string_cell, black_chess[number]);
								}


							}
						}
						else
						{
							black.return_back(coor, last_column_cell, last_string_cell, black_chess[number]);
						}
						
					
				}
				if (!youMove)
				{
					count = 0;
					number_step = 0;
					while (!(count == 1))
					{
						white.random(number_checker_bot);
						std::cout << "number_checker_bot = " << number_checker_bot << endl;
						white.det_coor(white_chess[number_checker_bot - 1], bot_x, bot_y);
						//coord_x = white_chess[number_checker_bot - 1].getPosition().x;
						//coord_y = white_chess[number_checker_bot - 1].getPosition().y;
						std::cout << "white_chess[number_checker_bot].getPosition().x = " << bot_x << endl;
						std::cout << "white_chess[number_checker_bot].getPosition().y = " << bot_y << endl;
						specific_cell(bot_x, coor, last_string_cell, trashcan);
						specific_cell(bot_y, coor, last_column_cell, trashcan);
						std::cout << "last_string_cell = " << last_string_cell << endl;
						std::cout << "last_column_cell = " << last_column_cell << endl;
						random_string = rand() %2 + 1;
						random_column = rand() %2 + 1;
						if ((last_string_cell != 0) || (last_string_cell != 7))
						{
							if (random_string == 2) (random_string = 1);
							else (random_string = -1);
						}
						std::cout << "last_column_cell + 1 = " << last_column_cell + 1 << endl;
						std::cout << "last_string_cell + random_string = " << last_string_cell + random_string << endl;
						std::cout << "chess_board[last_column_cell + 1][last_string_cell + random_string] = " << chess_board[last_column_cell + 1][last_string_cell + random_string] << endl;
						int k = 0;
						live = true;
						std::cout << "size(white_dead)" << size(white_dead) << endl;
						while (k < size(white_dead))
						{
							std::cout << "white_dead[k]" << white_dead[k] << endl;
							std::cout << "number_checker_bot"<< number_checker_bot << endl;
							if ((white_dead[k] == number_checker_bot - 1) && (white_dead[k] != NULL))
							{
								std::cout << "BLYATb" << endl;
								k = size(white_dead);
								live = false;
								number_step = number_step - 1;
							}
							k = k + 1;
						}
						std::cout << "live = " << live << endl;
						if ((chess_board[last_column_cell + 1][last_string_cell + random_string] == 1) && live)
						{
							if ((chess_board[last_column_cell + 2][last_string_cell + (random_string * 2)] == 3) && live)
							{
								kyky_1 = bot_x + (144 * random_string);
								kyky_2 = bot_y + 144;
								column_cell = last_column_cell + 2;
								string_cell = last_string_cell + (random_string * 2);
								std::cout << "coord_x + 72 = " << kyky_1 << endl;
								std::cout << "coord_y + (72 * random_string) = " << kyky_2 << endl;
								white.move_step(white_chess[number_checker_bot - 1], kyky_1, kyky_2);
								//count = 1;
								for (i = 0; i < 12; i++)
								{
									if (black_chess[i].getGlobalBounds().contains(coor[last_string_cell + random_string], coor[last_column_cell + 1]))
									{
										std::cout << "fdfdf" << endl;
										black_live[i] = false;
										chess_board[last_column_cell + 1][last_string_cell + random_string] = 3;
										chess_board[last_column_cell][last_string_cell] = 3;
										chess_board[column_cell][string_cell] = 2;
										std::cout << "fdfdflast_column_cell = "<< last_column_cell << endl;
										std::cout << "last_string_cell = "<< last_string_cell << endl;
										std::cout << "random_string = "<< random_string << endl;
										std::cout << "column_cell = "<< column_cell << endl;
										std::cout << "string_cell = "<< string_cell << endl;
										std::cout << "chess_board[last_column_cell + 1][string_cell + random_string] = "<< chess_board[last_column_cell + 1][string_cell + random_string] << endl;
										std::cout << "chess_board[last_column_cell][last_string_cell]" << chess_board[last_column_cell][last_string_cell] << endl;
										std::cout << "chess_board[column_cell][string_cell] = "<< chess_board[column_cell][string_cell] << endl;

									}
								}
							}
						}
						else if ((chess_board[last_column_cell + 1][last_string_cell + random_string] == 3) && live)
						{
							kyky_1 = bot_x + (72 * random_string);
							kyky_2 = bot_y + 72;
							std::cout << "coord_x + 72 = " << kyky_1 << endl;
							std::cout << "coord_y + (72 * random_string) = " << kyky_2 << endl;
							white.move_step(white_chess[number_checker_bot - 1],kyky_1 ,kyky_2 );
							chess_board[last_column_cell][last_string_cell] = 3;
							chess_board[last_column_cell + 1][last_string_cell + random_string] = 2;
							count = 1;
						}
						if (number_step == 12)
						{
							windows = 2;
							count = 1;
							std::cout << "Ходов больше нет ,вы проиграли" << endl;
						}
						number_step = number_step + 1;
						
					}
					youMove = true;
				}
			if (isMove)
			{
				//white_move = false;
				//black.move_checkers(black_chess[number], pos.x, pos.y, dX, dY);
				black.move_checkers(black_chess[number], pos.x, pos.y, dX, dY);
				//black_chess[number].setPosition(pos.x - dX, pos.y - dY);
			
			}
		}

		window.clear();
		
		black.draw(s_map, window);
		//cout << "black_chess[4].getPosition.x = " << black_chess[4].getPosition().x << endl;
		//cout << "black_chess[4].getPosition.y = " << black_chess[4].getPosition().y << endl;
		//window.draw(black_chess[4]);
		if (windows == 1)
		{
			for (char i = 0; i < 12; i++) {
				draw = true;
				if ((draw) && black_live[i])
					window.draw(black_chess[i]);
				if ((draw) && (white_live[i]))
					window.draw(white_chess[i]);
			}
			window.display();
		}
		else if (windows == 2) {
			RenderWindow window(sf::VideoMode(400, 200), "The End");
			Texture back;
			back.loadFromFile("images/background.png");
			Sprite background;
			background.setTexture(back);
			background.setPosition(0, 0);
		}
	}

	return 0;
}