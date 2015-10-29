#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
//#include <stdlib>

using namespace sf;
using namespace std;

void specific_cell(float position, int coord[], int &last_cell, int &coordinate){
	int k;
	k = 0;
	while (k < 9){
		if (position < coord[k]){
			coordinate = coord[k - 1];
			last_cell = k - 1;
			k = 9;
		}
		k = k + 1;
	}
}

void det_coor(Sprite &sprite, int &x, int&y){
	x = sprite.getPosition().x;
	y = sprite.getPosition().y;
}

void move_step(Sprite &sprite, int x, int y){
	sprite.setPosition(x, y);
	sprite.setColor(Color::White);
}

void return_back(int coordinate[], int l_column, int l_string, Sprite &sprite){
	sprite.setPosition(coordinate[l_string], coordinate[l_column]);
	sprite.setColor(Color::White);
}

void checkFookBlack(int(&chess_board)[8][8], int &column, int &string, Sprite *black_chess, int coor[], bool *black_live, Sprite *white_chess, int &dead_black , int &j){
	if ((chess_board[column - 1][string + 1] == 2) && (chess_board[column - 2][string + 2] == 3)){
		int k = 0;
		while (k < 12){
			if (white_chess[k].getGlobalBounds().contains(coor[string + 1], coor[column - 1])){
				cout << "Фук у черных" << endl;
				black_live[j] = false;
				black_chess[j].setPosition(900, 900);
				dead_black = dead_black + 1;
				chess_board[column][string] = 3;
				k = 12;
				j = 12;
			}
			k = k + 1;
		}
	}
	else if ((chess_board[column - 1][string - 1] == 2) && (chess_board[column - 2][string - 2] == 3)){
		int k = 0;
		while (k < 12){
			if (white_chess[k].getGlobalBounds().contains(coor[string - 1], coor[column - 1])){
				cout << "Фук у черных" << endl;
				black_live[j] = false;
				black_chess[j].setPosition(900, 900);
				dead_black = dead_black + 1;
				chess_board[column][string] = 3;
				k = 12;
				j = 12;
			}
			k = k + 1;
		}
	}
}

void cutting_checkers_forward(int l_string, int l_column, int string, int column, int coordinate[], Sprite *black_chess, int number, int (&chess_board)[8][8], int x, int y, int &dead_white, bool *white_live, bool &youMove, int &dead_black, bool *black_live, Sprite *white_chess, bool *king_b, Sprite *black_king, Sprite *white_king, bool *king_w){
	if ((l_string - string) == 2 || (l_string - string) == -2){
		if (chess_board[column + 1][string + ((l_string - string) / 2)] == 2){
			move_step(black_chess[number], x, y);
			int i = 0;
			while (i < 12){
				if (white_chess[i].getGlobalBounds().contains(coordinate[string + ((l_string - string) / 2)], coordinate[column + 1])){
					dead_white = dead_white + 1;
					white_chess[i].setPosition(900, 900);
					white_live[i] = false;
					i = 13;
				}
				i = i + 1;
			}
			chess_board[column + 1][string + ((l_string - string) / 2)] = 3;
			chess_board[l_column][l_string] = 3;
			chess_board[column][string] = 1;
			youMove = false;
			if ((column == 0) && (black_live[number])){
				black_live[number] = false;
				black_chess[number].setPosition(900, 900);
				king_b[number] = true;
				black_king[number].setPosition(x, y);
				chess_board[column][string] = 5; // 5 - черные дамки
			}
		}
		else{
			return_back(coordinate, l_column, l_string, black_chess[number]);
		}
		if (chess_board[column + 1][string + ((l_string - string) / 2)] == 4){
			move_step(black_chess[number], x, y);
			int i = 0;
			while (i < 12){
				if (white_king[i].getGlobalBounds().contains(coordinate[string + ((l_string - string) / 2)], coordinate[column + 1])){
					dead_white = dead_white + 1;
					white_king[i].setPosition(900, 900);
					king_w[i] = false;
					i = 13;
				}
				i = i + 1;
			}
			chess_board[column + 1][string + ((l_string - string) / 2)] = 3;
			chess_board[l_column][l_string] = 3;
			chess_board[column][string] = 1;
			youMove = false;
		}
	}
}

void cutting_checkers_backward(int l_string, int l_column, int string, int column, int coordinate[], Sprite *black_chess, int number, int (&chess_board)[8][8], int x, int y, int &dead_white, bool *white_live, bool &youMove, int &dead_black, bool *black_live, Sprite *white_chess, bool *king_b, Sprite *black_king, Sprite *white_king, bool *king_w){
	if ((l_string - string) == 2 || (l_string - string) == -2){
		if (chess_board[column - 1][string + ((l_string - string) / 2)] == 2){
			move_step(black_chess[number], x, y);
			int i = 0;
			while (i < 12){
				if (white_chess[i].getGlobalBounds().contains(coordinate[string + ((l_string - string) / 2)], coordinate[column - 1])){
					white_live[i] = false;
					white_chess[i].setPosition(900, 900);
					dead_white = dead_white + 1;
					i = 13;
				}
				i = i + 1;
			}
			chess_board[column - 1][string + ((l_string - string) / 2)] = 3;
			chess_board[l_column][l_string] = 3;
			chess_board[column][string] = 1;
			youMove = false;
			if ((column == 0) ){
				black_live[number] = false;
				black_chess[number].setPosition(900, 900);
				king_b[number] = true;
				black_king[number].setPosition(x, y);
				chess_board[column][string] = 5; // 5 - черные дамки
			}
		}
		else{
			return_back(coordinate, l_column, l_string, black_chess[number]);
		}
		if (chess_board[column - 1][string + ((l_string - string) / 2)] == 4){
			move_step(black_chess[number], x, y);
			int i = 0;
			while (i < 12){

				if (white_king[i].getGlobalBounds().contains(coordinate[string + ((l_string - string) / 2)], coordinate[column - 1])){
					king_w[i] = false;
					white_king[i].setPosition(900, 900);
					dead_white = dead_white + 1;
					i = 13;
				}
				i = i + 1;
			}
			chess_board[column - 1][string + ((l_string - string) / 2)] = 3;
			chess_board[l_column][l_string] = 3;
			chess_board[column][string] = 1;
			youMove = false;
		}
	}
}

void move_checkers(Sprite &sprite, float pos_x, float pos_y, float d_X, float d_Y){
	sprite.setPosition(pos_x - d_X, pos_y - d_Y);
	sprite.setColor(Color::Blue);
}

void Move(int (&chess_board)[8][8], int column, int string, int *coord, int l_column, int l_string, Sprite *black_chess, Sprite *white_chess,int number, int coord_x, int coord_y, int &dead_black, bool black_live[], bool &youMove, int &dead_white, bool white_live[],Sprite *black_king, bool *king_b, Sprite*white_king, bool *king_w){
	int trashcan = 0;
	int check = 0;
	if ((chess_board[column][string] != 0)){
		bool fook = false;
		if ((chess_board[column][string] == 2) || (chess_board[column][string] == 1) || (chess_board[column][string] == 5) || (chess_board[column][string] == 4)) (return_back(coord, l_column, l_string, black_chess[number]));
		if (chess_board[column][string] == 3){
			if ((l_column - column) == -1){
				if ((l_string - string) == 1 || (l_string - string) == -1){
					return_back(coord, l_column, l_string, black_chess[number]);
					chess_board[l_column][l_string] = 3;
					chess_board[column][string] = 2;
					fook = true;
				}
				else{
					return_back(coord, l_column, l_string, black_chess[number]);
				}
			}
			else if ((l_column - column) == 1){
				if ((l_string - string) == 1 || (l_string - string) == -1){
					move_step(black_chess[number], coord_x, coord_y);
					chess_board[l_column][l_string] = 3;
					chess_board[column][string] = 1;
					fook = true;
					if ((column == 0)){
						black_live[number] = false;
						black_chess[number].setPosition(900, 900);
						king_b[number] = true;
						black_king[number].setPosition(coord_x, coord_y);
						chess_board[column][string] = 5; // 5 - черные дамки
					}
					youMove = false;
				}
				else{
					return_back(coord, l_column, l_string, black_chess[number]);
				}
			}
			else if ((l_column - column) == 2) (cutting_checkers_forward(l_string, l_column, string, column, coord, black_chess, number, chess_board, coord_x, coord_y, dead_white, white_live, youMove, dead_black, black_live, white_chess, king_b, black_king, white_king, king_w));
			else if ((l_column - column) == -2) (cutting_checkers_backward(l_string, l_column, string, column, coord, black_chess, number, chess_board, coord_x, coord_y, dead_white, white_live, youMove, dead_black, black_live, white_chess, king_b, black_king, white_king, king_w));
			else (return_back(coord, l_column, l_string, black_chess[number]));
		}
		int j = 0;
		while ((j < 12) && (fook)){
			if ((j != number) && (black_live[j])){
				det_coor(black_chess[j], coord_x, coord_y);
				specific_cell(coord_x, coord, string, trashcan);
				specific_cell(coord_y, coord, column, trashcan);
				checkFookBlack(chess_board, column, string, black_chess, coord, black_live, white_chess, dead_black, j);
			}
			j = j + 1;
		}
	}
	else (return_back(coord, l_column, l_string, black_chess[number]));
}

void live(bool white_live[], int check){
	int j = 0;
	while (j < 12){
		if (white_live[j]){
			check = 0;
			j = 12;
		}
		else{
			check++;
			j = j + 1;
		}
	}
}

void checkEnd(int &windows, int chess_board[8][8],Sprite black_chess[], bool &youMove, int coord[], bool *black_live){
	int i = 0;
	int check = 0;
	int xx, yy;
	int col, str;
	int trashcan;
	while (i < 12){
		det_coor(black_chess[i], xx, yy);
		specific_cell(xx, coord, str, trashcan);
		specific_cell(yy, coord, col, trashcan);
		if (black_live[i]){
			if ((col > 0) && (str > 0) && (chess_board[col - 1][str - 1] == 3)){
				check = 0;
				i = 12;
			}
			else if ((col > 0) && (str < 7) && (chess_board[col - 1][str + 1] == 3)){
				(check = 0);
				(i = 12);
			}
			else if ((col > 1) && (str > 1) && (chess_board[col - 1][str - 1] == 2) && (chess_board[col - 2][str - 2] != 3)) (check++);
			else if ((col > 1) && (str < 6) && (chess_board[col - 1][str + 1] == 2) && (chess_board[col - 2][str + 2] != 3)) (check++);
			else (check++);
			i = i + 1;
		}
	}
	if (check == 12){
		(windows = 4);
		youMove = true;
	}
}

void step_checkers_bot(int &string_cell, int (&chess_board)[8][8], int &column_cell, Sprite *white_chess, int &i, int coor[], int &count, int &number){
	if ((string_cell > 0) && (chess_board[column_cell + 1][string_cell - 1] == 3)){
		move_step(white_chess[i], coor[string_cell - 1], coor[column_cell + 1]);
		chess_board[column_cell][string_cell] = 3;
		chess_board[column_cell + 1][string_cell - 1] = 2;
		column_cell = column_cell + 1;
		string_cell = string_cell - 1;
		number = i;
		count = 1;
		i = 12;
	}
	else if (((string_cell < 7) && (chess_board[column_cell + 1][string_cell + 1] == 3))){
		move_step(white_chess[i], coor[string_cell + 1], coor[column_cell + 1]);
		chess_board[column_cell][string_cell] = 3;
		chess_board[column_cell + 1][string_cell + 1] = 2;
		column_cell = column_cell + 1;
		string_cell = string_cell + 1;
		number = i;
		count = 1; i = 12;
	}
}

void check_the_end(int column_cell, int i, bool *white_live, int &dead_white, Sprite *white_chess, int &count, bool *king_w, Sprite *king_white, int string_cell, int coord[], int (&chess_board)[8][8]){
	if ((column_cell == 7) && (white_live[i])){
		white_live[i] = false;
		white_chess[i].setPosition(900, 900);
		king_w[i] = true;
		king_white[i].setPosition(coord[string_cell], coord[column_cell]);
		chess_board[column_cell][string_cell] = 4; //4 - белые дамки
		count = 1;

	}
}

void check_hack(int &string_cell, int (&chess_board)[8][8], int &column_cell, Sprite *white_chess, int &i, int coor[], int &count, Sprite *black_chess, int &dead_black, bool *black_live, int &check, bool &fook, int &step, Sprite *black_king){
	if ((string_cell > 1) && (chess_board[column_cell + 1][string_cell - 1] == 1)){
		if (chess_board[column_cell + 2][string_cell - 2] == 3){
			move_step(white_chess[i], coor[string_cell - 2], coor[column_cell + 2]);
			chess_board[column_cell][string_cell] = 3;
			chess_board[column_cell + 1][string_cell - 1] = 3;
			chess_board[column_cell + 2][string_cell - 2] = 2;
			count = 1;
			i = 12;
			int j = 0;
			while (j < 12){
				if (black_chess[j].getGlobalBounds().contains(coor[string_cell - 1], coor[column_cell + 1])){
					dead_black = dead_black + 1;
					black_chess[j].setPosition(900, 900);
					black_live[j] = false;
					fook = false;
					step = 1;
					j = 12;
				}
				j = j + 1;
			}
			column_cell = column_cell + 2;
			string_cell = string_cell - 2;
		}
	}
	else if ((string_cell < 6) && (chess_board[column_cell + 1][string_cell + 1] == 1)){
		if ((chess_board[column_cell + 2][string_cell + 2] == 3) && (chess_board[column_cell + 2][string_cell + 2] != 1)){
			move_step(white_chess[i], coor[string_cell + 2], coor[column_cell + 2]);
			chess_board[column_cell][string_cell] = 3;
			chess_board[column_cell + 1][string_cell + 1] = 3;
			chess_board[column_cell + 2][string_cell + 2] = 2;
			count = 1;
			i = 12;
			int j = 0;
			while (j < 12){
				if (black_chess[j].getGlobalBounds().contains(coor[string_cell + 1], coor[column_cell + 1])){
					dead_black = dead_black + 1;
					black_chess[j].setPosition(900, 900);
					check = 0;
					black_live[j] = false;
					fook = true;
					step = 1;
					j = 12;
				}
				j = j + 1;
			}
			column_cell = column_cell + 2;
			string_cell = string_cell + 2;
		}
	}
	else if ((string_cell > 1) && (chess_board[column_cell + 1][string_cell - 1] == 5)){
		if (chess_board[column_cell + 2][string_cell - 2] == 3){
			move_step(white_chess[i], coor[string_cell - 2], coor[column_cell + 2]);
			chess_board[column_cell][string_cell] = 3;
			chess_board[column_cell + 1][string_cell - 1] = 3;
			chess_board[column_cell + 2][string_cell - 2] = 2;
			count = 1;
			i = 12;
			int j = 0;
			while (j < 12){
				if (black_king[j].getGlobalBounds().contains(coor[string_cell - 1], coor[column_cell + 1])){
					dead_black = dead_black + 1;
					black_king[j].setPosition(900, 900);
					black_live[j] = false;
					fook = false;
					step = 1;
					j = 12;
				}
				j = j + 1;
			}
			column_cell = column_cell + 2;
			string_cell = string_cell - 2;
		}
	}
	else if ((string_cell < 6) && (chess_board[column_cell + 1][string_cell + 1] == 5)){
		if ((chess_board[column_cell + 2][string_cell + 2] == 3) && (chess_board[column_cell + 2][string_cell + 2] != 1)){
			move_step(white_chess[i], coor[string_cell + 2], coor[column_cell + 2]);
			chess_board[column_cell][string_cell] = 3;
			chess_board[column_cell + 1][string_cell + 1] = 3;
			chess_board[column_cell + 2][string_cell + 2] = 2;
			count = 1;
			i = 12;
			int j = 0;
			while (j < 12){
				if (black_king[j].getGlobalBounds().contains(coor[string_cell + 1], coor[column_cell + 1])){
					dead_black = dead_black + 1;
					black_king[j].setPosition(900, 900);
					check = 0;
					fook = true;
					step = 1;
					j = 12;
				}
				j = j + 1;
			}
			column_cell = column_cell + 2;
			string_cell = string_cell + 2;
		}
	}
}

void checkFook(int (&chess_board)[8][8], int &column, int &string, Sprite *black_chess, int coor[], bool *white_live, Sprite *white_chess, int &dead_white, int &j, int &check){
	if ((chess_board[column + 1][string + 1] == 1) && (chess_board[column + 2][string + 2] == 3)){
		int k = 0;
		while (k < 12){
			if (black_chess[k].getGlobalBounds().contains(coor[string + 1], coor[column + 1])){
				cout << "Фук у белых" << endl;
				white_live[j] = false;
				white_chess[j].setPosition(900, 900);
				dead_white = dead_white + 1;
				chess_board[column][string] = 3;
				check = 1;
				k = 12;
				j = 12;
			}
			k = k + 1;
		}
	}
	else if ((chess_board[column + 1][string - 1] == 1) && (chess_board[column + 2][string - 2] == 3)){
		int k = 0;
		while (k < 12){
			if (black_chess[k].getGlobalBounds().contains(coor[string - 1], coor[column + 1])){
				cout << "Фук у белых" << endl;
				white_live[j] = false;
				white_chess[j].setPosition(900, 900);
				dead_white = dead_white + 1;
				check = 1;
				chess_board[column][string] = 3;
				k = 12;
				j = 12;
			}
			k = k + 1;
		}
	}
}

void definition_sprite(Sprite name_sprite[], float pos_x, float pos_y, float &d_X, float &d_Y, bool &move, int &num){
	int k;
	k = 0;
	while (k < 12){
		if (name_sprite[k].getGlobalBounds().contains(pos_x, pos_y)){
			d_X = pos_x - name_sprite[k].getPosition().x;
			d_Y = pos_y - name_sprite[k].getPosition().y;
			move = true;
			num = k;
			k = 12;
		}
		k = k + 1;
	}
}
void moveWhiteKingUp(int(&chess_board)[8][8], Sprite *white_king, Sprite *black_chess, Sprite *king_black, int &i, int coor[], bool *black_live, int &dead_black, bool &youMove, bool *king_b, int column, int string, int &step) {
	if ((column + 2 <= 7) && (string + 2 <= 7) && ((chess_board[column + 1][string + 1] == 1) || chess_board[column + 1][string + 1] == 5) && (chess_board[column + 2][string + 2] == 3)) {
		int k = 0;
		while (k < 12) {
			if (black_chess[k].getGlobalBounds().contains(coor[string + 1], coor[column + 1])) {
				black_live[k] = false;
				step = 1;
				black_chess[k].setPosition(900, 900);
				dead_black++;
				k = 12;
			}
			else if (king_black[k].getGlobalBounds().contains(coor[string + 1], coor[column + 1])) {
				step = 1;
				king_b[k] = false;
				dead_black++;
				king_black[k].setPosition(900, 900);
				k = 12;
			}
			white_king[i].setPosition(coor[string + 2], coor[column + 2]);
			chess_board[column][string] = 3;
			chess_board[column + 1][string + 1] = 3;
			chess_board[column + 2][string + 2] = 4;

			k++;
		}
	}
	else if ((column - 2 >= 0) && (string + 2 <= 7) && ((chess_board[column - 1][string + 1] == 1) || (chess_board[column - 1][string + 1] == 5)) && (chess_board[column - 2][string + 2] == 3)) {
		int k = 0;
		while (k < 12) {
			if (black_chess[k].getGlobalBounds().contains(coor[string + 1], coor[column - 1])) {
				black_chess[k].setPosition(900, 900);
				black_live[k] = false;
				step = 1;
				dead_black++;
				k = 12;
			}
			else if (king_black[k].getGlobalBounds().contains(coor[string + 1], coor[column - 1])) {
				king_b[k] = false;
				step = 1;
				king_black[k].setPosition(900, 900);
				dead_black++;
				k = 12;
			}
			white_king[i].setPosition(coor[string + 2], coor[column - 2]);
			chess_board[column][string] = 3;
			chess_board[column - 1][string + 1] = 3;
			chess_board[column - 2][string + 2] = 4;
			k++;
		}
	}
	else if ((column + 2 <= 7) && (string - 2 >= 0) && ((chess_board[column + 1][string - 1] == 1) || chess_board[column + 1][string - 1] == 5) && (chess_board[column + 2][string - 2] == 3)) {
		int k = 0;
		while (k < 12) {
			if (black_chess[k].getGlobalBounds().contains(coor[string - 1], coor[column + 1])) {
				step = 1;
				black_live[k] = false;
				black_chess[k].setPosition(900, 900);
				dead_black++;
				k = 12;
			}
			else if (black_chess[k].getGlobalBounds().contains(coor[string - 1], coor[column + 1])) {
				step = 1;
				king_b[k] = false;
				dead_black++;
				king_black[k].setPosition(900, 900);
				k = 12;
			}
			white_king[i].setPosition(coor[string - 2], coor[column + 2]);
			chess_board[column][string] = 3;
			chess_board[column + 1][string - 1] = 3;
			chess_board[column + 2][string - 2] = 4;
			k++;
		}
	}
	else if ((column - 2 >= 0) && (string - 2 >= 0) && ((chess_board[column - 1][string - 1] == 1) || chess_board[column - 1][string - 1] == 5) && (chess_board[column - 2][string - 2] == 3)) {
		int k = 0;
		while (k < 12) {
			if (black_chess[k].getGlobalBounds().contains(coor[string - 1], coor[column - 1])) {
				black_live[k] = false;
				step = 1;
				black_chess[k].setPosition(900, 900);
				dead_black++;
				k = 12;
			}
			else if (king_black[k].getGlobalBounds().contains(coor[string - 1], coor[column - 1])) {
				king_b[k] = false;
				step = 1;
				king_black[k].setPosition(900, 900);
				dead_black++;
				k = 12;
			}
			chess_board[column][string] = 3;
			chess_board[column - 1][string - 1] = 3;
			chess_board[column - 2][string - 2] = 4;
			white_king[i].setPosition(coor[string - 2], coor[column - 2]);
			k++;
		}
	}
}

void moveWhiteKing(int (&chess_board)[8][8], Sprite *white_king, Sprite *black_chess, Sprite *king_black, int &i, int coor[], bool *black_live, int &dead_black, bool &youMove, bool *king_b){
	int bot_x, bot_y, trashcan, string, column, str, col;
	bool fook = false;
	det_coor(white_king[i], bot_x, bot_y);
	specific_cell(bot_x, coor, string, trashcan);
	specific_cell(bot_y, coor, column, trashcan);
	str = 7 - string;
	col = 7 - column;
	int step = 0;
	if (step == 0){
		moveWhiteKingUp(chess_board, white_king, black_chess, king_black, i, coor, black_live, dead_black, youMove, king_b, column, string, step);
	}
	if (step == 0){
		if ((column + 1 <= 7) && (string + 1 <= 7) && (chess_board[column + 1][string + 1] == 3)){
			white_king[i].setPosition(coor[string + 1], coor[column + 1]);
			chess_board[column][string] = 3;
			chess_board[column + 1][string + 1] = 4;
			step = 1;
			fook - true;
		}
		else if ((column - 1 >= 0) && (string + 1 <= 7) && (chess_board[column - 1][string + 1] == 3)){
			white_king[i].setPosition(coor[string + 1], coor[column - 1]);
			chess_board[column][string] = 3;
			chess_board[column - 1][string + 1] = 4;
			step = 1;
			fook - true;
		}
		else if ((column + 1 <= 7) && (string - 1 >= 0)&& (chess_board[column + 1][string - 1] == 3)){
			white_king[i].setPosition(coor[string - 1], coor[column + 1]);
			chess_board[column][string] = 3;
			chess_board[column + 1][string - 1] = 4;
			step = 1;
			fook - true;
		}
		else if ((column - 1 >= 0) && (string - 1 >= 0) && (chess_board[column - 1][string - 1] == 3)){
			white_king[i].setPosition(coor[string - 1], coor[column - 1]);
			chess_board[column][string] = 3;
			step = 1;
			chess_board[column - 1][string - 1] = 4;
			fook - true;
		}

	}
	if (step == 0){
		i++;
	}
}

void loading_sprites(Sprite *name_sprite, Texture &texture, int &x, int &y){
	for (int j = 0; j < 12; j++){
		name_sprite[j].setTexture(texture);
		name_sprite[j].setPosition(x, y);
		if (x == 432){
			x = -72;
			y += 72;
		}
		if (x == 504){
			x = -144;
			y += 72;
		}
		x += 144;
	}
}

void step_bot(bool *white_live, Sprite *white_chess, int coor[], int string, int column, int (&chess_board)[8][8], Sprite *black_chess, int &dead_white, int &dead_black, bool *black_live, int &windows, bool &youMove, bool *king_w, Sprite *king_white, Sprite *black_king, bool *king_b){
	int trashcan;
	int number = -1;
	int count = 0;
	int check = 0;
	int chislo;
	int bot_x, bot_y;
	while (!(count == 1)){
		bool fook = true;
		int i = 0;
		int check_4 = 0;
		int steps = 0;
		while (i <= 12){
			chislo = i;
			live(white_live, check);
			det_coor(white_chess[i], bot_x, bot_y);
			specific_cell(bot_x, coor, string, trashcan);
			specific_cell(bot_y, coor, column, trashcan);
			int step = 0;
			if (white_live[i]){
				if (step == 0) (check_hack(string, chess_board, column, white_chess, i, coor, count, black_chess, dead_black, black_live, check, fook, step, black_king));
				if (step == 0) (step_checkers_bot(string, chess_board, column, white_chess, i, coor, count, number));
				check_the_end(column, i, white_live, dead_white, white_chess, count, king_w, king_white, string, coor, chess_board);
				if (step == 0){
					check = check + 1;
				}
				if (check == 12){
					i = 12;
					count = 1;
					windows = 3;
				}
			}
			if (chislo != i){
				int r = i;
				i = chislo;
				chislo = r;
			}
			if (king_w[i]){
				
				moveWhiteKing(chess_board, king_white, black_chess, black_king, i, coor, black_live, dead_black, youMove, king_b);
				chislo = 12;
				count = 1;
			}
			if (chislo != i){
				int r = i;
				i = chislo;
				chislo = r;
			}
			i = i + 1;
			if (dead_white == 12) (count = 1);
		}
		int j = 0;
		while ((j < 12) && (check_4 == 0) && (fook) &&(number != -1)){
			if ((j != number) &&(white_live[j])){
				det_coor(white_chess[j], bot_x, bot_y);
				specific_cell(bot_x, coor, string, trashcan);
				specific_cell(bot_y, coor, column, trashcan);
				checkFook(chess_board, column, string, black_chess, coor, white_live, white_chess, dead_white, j, check_4);
			}
			j = j + 1;
		}
		if (dead_white == 12) (windows = 4);
		youMove = true;
	}
}

void drawing(int windows, RenderWindow &window, Sprite *white_chess, Sprite *black_chess, Text text, int dead_black, int dead_white, Sprite *black_king, Sprite *white_king){
	if (dead_white >= 12){
		text.setPosition(100, 250);
		text.setString("Вы выиграли");
		window.draw(text);
	}
	else if (dead_black >= 12){
		text.setPosition(0, 250);
		text.setString("Вы проиграли");
		window.draw(text);
	}
	else if (windows == 1){
		for (char i = 0; i < 12; i++){
			window.draw(white_chess[i]);
			window.draw(black_chess[i]);
			window.draw(black_king[i]);
			window.draw(white_king[i]);
		}
	}
	else if (windows == 3){
		text.setPosition(0, 250);
		text.setString("Вы выиграли");
		window.draw(text);
	}
	else if (windows == 4){
		text.setPosition(0, 250);
		text.setString("Вы проиграли");
		window.draw(text);
	}
}

void loading(Font& font, Text &text, Texture &map, Texture &white, Texture & black, Sprite &s_map, Texture &black_king, Texture &white_king){
	font.loadFromFile("images/CyrilicOld.ttf");
	text.setColor(Color::Blue);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	map.loadFromFile("images/map.png");
	white.loadFromFile("images/white_chess.png");
	black.loadFromFile("images/black_chess.png");
	s_map.setTexture(map);
	s_map.setPosition(0, 0);
	black_king.loadFromFile("images/king_black.png");
	white_king.loadFromFile("images/king_white.png");

}

void moveKingUp(int string, int column, int l_column, int l_string, int &king, int (&chess_board)[8][8], bool &youMove, Sprite *white_chess, int coord[8], int &j, Sprite &sprite, bool *white_live, int &dead_white, Sprite *white_king, bool *king_w, int &i){
	if ((string - l_string > 0) && (king != 2)) {
		if ((white_chess[j].getGlobalBounds().contains(coord[l_string + i], coord[l_column + i])) && (chess_board[l_column + i + 1][l_string + i + 1] == 3)) {
			youMove = false;
			chess_board[column][string] = 5;
			sprite.setPosition(coord[string], coord[column]);
			chess_board[l_column + i][l_string + i] = 3;
			chess_board[l_column][l_string] = 3;
			white_live[j] = false;
			white_chess[j].setPosition(900, 900);
			dead_white++;
			king = 1;
			j = 12;
			i++;
		}
		else if ((white_king[j].getGlobalBounds().contains(coord[l_string + i], coord[l_column + i])) && (chess_board[l_column + i + 1][l_string + i + 1] == 3)) {
			youMove = false;
			chess_board[column][string] = 5;
			sprite.setPosition(coord[string], coord[column]);
			chess_board[l_column + i][l_string + i] = 3;
			chess_board[l_column][l_string] = 3;
			king_w[j] = false;
			white_king[j].setPosition(900, 900);
			dead_white++;
			king = 1;
			j = 12;
			i++;
		}
		else if ((chess_board[l_column + i][l_string + i] == 1) || (chess_board[l_column + i][l_string + i] == 5)) {
			j = 12;
			i = abs(column - l_column);
		}
	}
	else if ((string - l_string < 0) && (king != 2)) {
		if ((white_chess[j].getGlobalBounds().contains(coord[l_string - i], coord[l_column + i])) && (chess_board[l_column + i + 1][l_string - i - 1] == 3)) {
			youMove = false;
			chess_board[column][string] = 5;
			sprite.setPosition(coord[string], coord[column]);
			chess_board[l_column + i][l_string - i] = 3;
			chess_board[l_column][l_string] = 3;
			white_chess[j].setPosition(900, 900);
			white_live[j] = false;
			dead_white++;
			king = 1;
			j = 12;
			i++;
		}
		else if ((white_king[j].getGlobalBounds().contains(coord[l_string - i], coord[l_column + i])) && (chess_board[l_column + i + 1][l_string - i - 1] == 3)) {
			youMove = false;
			chess_board[column][string] = 5;
			sprite.setPosition(coord[string], coord[column]);
			chess_board[l_column + i][l_string - i] = 3;
			chess_board[l_column][l_string] = 3;
			white_king[j].setPosition(900, 900);
			king_w[j] = false;
			dead_white++;
			king = 1;
			j = 12;
			i++;
		}
		else if ((chess_board[l_column + i][l_string - i] == 1) || (chess_board[l_column + i][l_string - i] == 5)) {
			j = 12;
			i = abs(column - l_column);
		}
	}
}

void moveKingDown(int string, int column, int l_column, int l_string, int &king, int(&chess_board)[8][8], bool &youMove, Sprite *white_chess, int coord[8], int &j, Sprite &sprite, bool *white_live, int &dead_white, Sprite *white_king, bool *king_w, int &i) {
	if ((string - l_string > 0) && (king != 2)) {
		if ((white_chess[j].getGlobalBounds().contains(coord[l_string + i], coord[l_column - i])) && (chess_board[l_column - i - 1][l_string + i + 1] == 3)) {
			youMove = false;
			chess_board[column][string] = 5;
			chess_board[l_column - i][l_string + i] = 3;
			sprite.setPosition(coord[string], coord[column]);
			chess_board[l_column][l_string] = 3;
			white_live[j] = false;
			white_chess[j].setPosition(900, 900);
			dead_white++;
			king = 1;
			j = 12;
			i++;
		}
		else if ((white_king[j].getGlobalBounds().contains(coord[l_string + i], coord[l_column - i])) && (chess_board[l_column - i - 1][l_string + i + 1] == 3)) {
			youMove = false;
			chess_board[column][string] = 5;
			chess_board[l_column - i][l_string + i] = 3;
			sprite.setPosition(coord[string], coord[column]);
			chess_board[l_column][l_string] = 3;
			king_w[j] = false;
			white_king[j].setPosition(900, 900);
			dead_white++;
			king = 1;
			j = 12;
			i++;
		}
		else if ((chess_board[l_column - i][l_string + i] == 1) || (chess_board[l_column - i][l_string + i] == 5)) {
			j = 12;
			i = abs(column - l_column);
		}
	}
	if ((string - l_string < 0) && (king != 2)) {
		if ((white_chess[j].getGlobalBounds().contains(coord[l_string - i], coord[l_column - i])) && (chess_board[l_column - i - 1][l_string - i - 1] == 3)) {
			youMove = false;
			chess_board[column][string] = 5;
			chess_board[l_column - i][l_string - i] = 3;
			sprite.setPosition(coord[string], coord[column]);
			chess_board[l_column][l_string] = 3;
			white_live[j] = false;
			white_chess[j].setPosition(900, 900);
			dead_white++;
			king = 1;
			j = 12;
			i++;
		}
		else if ((white_king[j].getGlobalBounds().contains(coord[l_string - i], coord[l_column - i])) && (chess_board[l_column - i - 1][l_string - i - 1] == 3)) {
			youMove = false;
			chess_board[column][string] = 5;
			chess_board[l_column - i][l_string - i] = 3;
			sprite.setPosition(coord[string], coord[column]);
			chess_board[l_column][l_string] = 3;
			king_w[j] = false;
			white_king[j].setPosition(900, 900);
			dead_white++;
			king = 1;
			j = 12;
			i++;
		}
		else if ((chess_board[l_column - i][l_string - i] == 1) || (chess_board[l_column - i][l_string - i] == 5)) {
			j = 12;
			i = abs(column - l_column);
		}
	}
}

void moveKing(int (&chess_board)[8][8], int column, int string, int l_string, int l_column, Sprite &sprite, int *coord, Sprite *white_chess, Sprite *white_king, bool *white_live, bool *black_live, int &dead_white, bool &youMove, bool *king_w){
	int col = column - l_column;
	int str = string - l_string;
	int king = 0;
	int k = 0;
	if (chess_board[column][string] != 0){
		if ((chess_board[column][string] == 3)){
			if (abs(column - l_column) == abs(string - l_string)){
				int i = 1;
				if (king == 0){
					while (i < abs(column - l_column) + 1){
						int j = 0;
						if ((column - l_column > 0) && (string - l_string > 0))
						{
							cout << "]]]]]]]]]]]]]]]]]" << endl;
							cout << "chess_board[l_column + i + 1][l_string + i + 1] = "<< chess_board[l_column + i + 1][l_string + i + 1] << endl;
							cout << "chess_board[l_column + i + 2][l_string + i + 2] = " << chess_board[l_column + i + 2][l_string + i + 2] << endl;
							if ((chess_board[l_column + 1][l_string + 1] != 3) && (chess_board[l_column + i + 1][l_string + i + 1] != 3))
							{
								j = 12;
								cout << "trololololo0" << endl;
								i = abs(column - l_column);
								return_back(coord, l_column, l_string, sprite);
								youMove = true;
								king = 2;
							}
						}
						else if ((column - l_column > 0) && (string - l_string < 0))
						{
							if ((chess_board[l_column + 1][l_string - 1] != 3) && (chess_board[l_column + i + 1][l_string - i - 1] != 3))
							{
								j = 12;
								cout << "trololololo1" << endl;
								i = abs(column - l_column);
								return_back(coord, l_column, l_string, sprite);
								youMove = true;
								king = 2;
							}
						}
						else if ((column - l_column < 0) && (string - l_string > 0))
						{
							if ((chess_board[l_column - 1][l_string + 1] != 3) && (chess_board[l_column - i - 1][l_string + i + 1] != 3))
							{
								j = 12;
								cout << "trololololo2" << endl;
								i = abs(column - l_column);
								return_back(coord, l_column, l_string, sprite);
								youMove = true;
								king = 2;
							}
						}
						else if ((column - l_column < 0) && (string - l_string < 0))
						{
							if ((chess_board[l_column- 1][l_string - 1] != 3) && (chess_board[l_column - i - 1][l_string - i - 1] != 3))
							{
								j = 12;
								cout << "l_column = " << l_column << endl;
								cout << "l_string = " << l_string << endl;
								cout << "trololololo3" << endl;
								i = abs(column - l_column);
								return_back(coord, l_column, l_string, sprite);
								youMove = true;
								king = 2;
							}
						}
						if ((king == 0) && (j == 0))
						{
							move_step(sprite, coord[string], coord[column]);
							youMove = false;
							k = 1;
						}
						while (j < 12){
							if (column - l_column > 0) {
								moveKingUp(string, column, l_column, l_string, king, chess_board, youMove, white_chess, coord, j, sprite, white_live, dead_white, white_king, king_w, i);
							}
							else if (column - l_column < 0){
								moveKingDown(string, column, l_column, l_string, king, chess_board, youMove, white_chess, coord, j, sprite, white_live, dead_white, white_king, king_w, i);
							}
							j = j + 1;
						}
						i++;
					}
					
				}
				if (king == 1){
					chess_board[column][string] = 5;
					chess_board[l_column][l_string] = 3;
				}
				if (k == 1){
					chess_board[column][string] = 5;
					chess_board[l_column][l_string] = 3;
				}
			}
			else (return_back(coord, l_column, l_string, sprite));
		}
		else (return_back(coord, l_column, l_string, sprite));
	}
	else (return_back(coord, l_column, l_string, sprite));
}

void StartGame(int *coord,int l_string, int l_column, int string, int column, int coord_x, int coord_y, int trashcan,bool isMove, bool youMove, bool white_live[], bool black_live[], float dX, float dY, int (&chess_board)[8][8], int number, bool *king_b, Sprite *black_king, Sprite *white_king){
	Font font;
	Text text("", font, 40);
	sf::RenderWindow window(sf::VideoMode(576, 576), "Checkers! Tim Garanin, PS-22");
	Texture map;
	Texture white_chess_texture;
	Texture black_chess_texture;
	Texture king_black, king_white;
	Sprite white_chess[13], black_chess[13], s_map;;
	loading(font, text, map, white_chess_texture, black_chess_texture, s_map, king_black, king_white);
	int x = 900;
	int y = 900;
	bool king_w[13] = { false, false, false, false, false, false, false, false, false, false, false, false, false};
	loading_sprites(black_king, king_black, x, y);
	loading_sprites(white_king, king_white, x, y);
	coord_x = 72;
	coord_y = 0;
	loading_sprites(white_chess, white_chess_texture, coord_x, coord_y);
	coord_x = 0;
	coord_y = 360;
	loading_sprites(black_chess, black_chess_texture, coord_x, coord_y);
	int dead_black = 0;
	int dead_white = 0;
	int windows = 1;
	while (window.isOpen()){
		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);
		sf::Event event;
		while (window.pollEvent(event)){
			//checkEnd(windows, chess_board, black_chess, youMove, coord, black_live);
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)
				if ((event.key.code == Mouse::Left) && (youMove)){
					specific_cell(pos.x, coord, l_string, trashcan);
					specific_cell(pos.y, coord, l_column, trashcan);
					definition_sprite(black_chess, pos.x, pos.y, dX, dY, isMove, number);
					definition_sprite(black_king, pos.x, pos.y, dX, dY, isMove, number);
				}
			if (event.type == Event::MouseButtonReleased && isMove && youMove)
				if (event.key.code == Mouse::Left && youMove){
					isMove = false;
					specific_cell(pos.x, coord, string, coord_x);
					specific_cell(pos.y, coord, column, coord_y);
					if (black_live[number]) (Move(chess_board, column, string, coord, l_column, l_string, black_chess, white_chess, number, coord_x, coord_y, dead_black, black_live, youMove, dead_white, white_live, black_king, king_b, white_king, king_w));
					else if (king_b[number]) (moveKing(chess_board, column, string, l_string, l_column, black_king[number], coord, white_chess, white_king, white_live, black_live, dead_white, youMove, king_w));
				}
			if (isMove){
				if (black_live[number]) (move_checkers(black_chess[number], pos.x, pos.y, dX, dY));
				else if (king_b[number]) (move_checkers(black_king[number], pos.x, pos.y, dX, dY));
				
			}
			if (!youMove) (step_bot(white_live, white_chess, coord, string, column, chess_board, black_chess, dead_white, dead_black, black_live, windows, youMove, king_w, white_king, black_king, king_b));
		}
		window.clear();
		window.draw(s_map);
		drawing(windows, window, white_chess, black_chess, text, dead_black, dead_white, black_king, white_king);
		window.display();
	}
}


int main(){
	int chess_board[8][8] ={
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
	int last_string_cell = 0, last_column_cell = 0, string_cell = 0, column_cell = 0, coord_x = 0, coord_y = 0, trashcan = 0;
	int count, k, number = 0;
	bool isMove = false;
	bool youMove = true;
	bool king_b[12] = { false, false, false, false, false, false, false, false, false, false, false, false };
	bool white_live[13] = { true, true, true, true, true, true, true, true, true, true, true, true, true };
	bool black_live[13] = { true, true, true, true, true, true, true, true, true, true, true, true, true };
	float dX = 0;
	float dY = 0;
	int windows = 1;
	int i, j;
	Sprite white_chess[13], black_chess[13], black_king[13], white_king[13];
	StartGame(coor, last_string_cell, last_column_cell, string_cell, column_cell, coord_x, coord_y, trashcan, isMove, youMove, white_live, black_live, dX, dY, chess_board, number, king_b, black_king, white_king);
	return 0;
}