#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace std;

// constants defining game board and tiles
const int GAME_X = 8;
const int GAME_Y = 10;
const int TILE_SIZE = 16;
const int TILE_DISTANCE = 45;

//declaring a constant tagret and gloab variable score and move
const int TARGET = 5000;
int SCORE = 0;
int MOVES = 40;

//declaring the x and y component of the tile that is to be selected
int SELECT_X = -1;
int SELECT_Y = -1;

//declaring global bool to reset a game or tell the user the move is not possible
bool MOVE_NOT_POSSIBLE = false;
bool GAME_RESET = false;

//declaing bool and x and y components of the hint rectangle (hint x is for a horizontal rectangle and hint y is for a vertical rectangle)
bool HINT_X = false;
bool HINT_Y = false;
int HINT_SELECT_X = -1;
int HINT_SELECT_Y = -1;

//declaring global 2D array of the board game 
int BOARD[GAME_X][GAME_Y];

//declaring global array of tiles corners and colors(to be used to make different types of polygons)
const int TOTAL_TYPES_OF_TILES = 8;
int CORNERS[TOTAL_TYPES_OF_TILES] = { 3,10,5,6,8,30,4,4 };
sf::Color COLORS[TOTAL_TYPES_OF_TILES] = { sf::Color::Cyan, sf::Color::Blue, sf::Color::Red, sf::Color::Magenta,
						                   sf::Color::Green, sf::Color::Yellow, sf::Color::White, sf::Color::Black };

//this function gives different candies/ polygons to draw tiles function
sf::CircleShape getShape(int x, int y)
{
	float pos_x = 320 + TILE_DISTANCE * x;
	float pos_y = 80 + TILE_DISTANCE * y;


	//as color and corner array starts with 0 index but i used 0 as a no tile in BOARD, so subtracting 1 from the value of array of BOARD that ranges from 1 to 6 by rand function
	int n = BOARD[x][y] - 1;

	sf::CircleShape shape(TILE_SIZE, CORNERS[n]);
	shape.setOutlineThickness(4.f);
	shape.setOutlineColor(sf::Color::Black);
	shape.setFillColor(COLORS[n]);
	shape.setPosition(pos_x, pos_y);
	return shape;
}

//this function returns the type of highlighted rectangle based on the global booleans(circumstances)
sf::RectangleShape highlightRectangle (int x, int y)
{

	float pos_x = 320 + TILE_DISTANCE * x;
	float pos_y = 80 + TILE_DISTANCE * y;

	//as color and corner array starts with 0 index but i used 0 as a no tile in BOARD, so subtracting 1 from the value of array of BOARD that ranges from 1 to 6 by rand function
	int n = BOARD[x][y] - 1;

	sf::RectangleShape select_rectangle;
	select_rectangle.setSize(sf::Vector2f(TILE_SIZE * 2, TILE_SIZE * 2));
	select_rectangle.setFillColor(sf::Color(255, 255, 255, 128));
	select_rectangle.setOutlineColor(sf::Color::White);
	select_rectangle.setOutlineThickness(3);
	select_rectangle.setPosition(pos_x, pos_y);

	sf::RectangleShape hint_rectangle_X;
	hint_rectangle_X.setSize(sf::Vector2f(TILE_SIZE * 4 + 10, TILE_SIZE * 2));
	hint_rectangle_X.setFillColor(sf::Color(255, 255, 255, 128));
	hint_rectangle_X.setOutlineColor(sf::Color::Magenta);
	hint_rectangle_X.setOutlineThickness(3);
	hint_rectangle_X.setPosition(pos_x, pos_y);

	sf::RectangleShape hint_rectangle_Y;
	hint_rectangle_Y.setSize(sf::Vector2f(TILE_SIZE * 2, TILE_SIZE * 4 + 10));
	hint_rectangle_Y.setFillColor(sf::Color(255, 255, 255, 128));
	hint_rectangle_Y.setOutlineColor(sf::Color::Magenta);
	hint_rectangle_Y.setOutlineThickness(3);
	hint_rectangle_Y.setPosition(pos_x, pos_y);

	if (HINT_X == true)
		return hint_rectangle_X;
	else if (HINT_Y == true)
		return hint_rectangle_Y;
	else
		return select_rectangle;
}

//this function finds the x coordinate and y coordinate (row and coloum number) of the board game when the user left clicks with the mouse
void selectTileOnClick(int px, int py)
{

	int x = px - px % TILE_DISTANCE - 310;
	int y = py - py % TILE_DISTANCE - 80;
	x /= TILE_DISTANCE;
	y /= TILE_DISTANCE;

	SELECT_X = x;
	SELECT_Y = y;

}

//this function draws the game board, tiles(based on the initialization numbers given to the 2d array BOARD) and the highlight rectangles(for hint and select) 
void drawTiles(int tiles[][GAME_Y], sf::RenderWindow& window)
{
	int n = GAME_X * TILE_DISTANCE + 10;
	int m = GAME_Y * TILE_DISTANCE + 10;

	sf::RectangleShape rectangle(sf::Vector2f(n, m));
	rectangle.setOutlineThickness(4.f);
	rectangle.setOutlineColor(sf::Color(153,51,0));
	rectangle.setFillColor(sf::Color(153,51,0, 128));
	rectangle.setPosition(310, 70);

	window.draw(rectangle);

	for (int i = 0; i < GAME_X; i++)
		for (int j = 0; j < GAME_Y; j++)
		{
			if (BOARD[i][j] != 0)
				window.draw(getShape(i, j));
			if (SELECT_X == i && SELECT_Y == j)
				window.draw(highlightRectangle(SELECT_X, SELECT_Y));
			if (HINT_X == true && HINT_SELECT_X == i && HINT_SELECT_Y == j)
				window.draw(highlightRectangle(HINT_SELECT_X, HINT_SELECT_Y));
			if (HINT_Y == true && HINT_SELECT_X == i && HINT_SELECT_Y == j)
				window.draw(highlightRectangle(HINT_SELECT_X, HINT_SELECT_Y));

		}
}

//initializes the game boards with a number given to each tile from 1 to 6 (max number of normal tiles possible)
void initialize(int BOARD[][GAME_Y])
{
	for (int x = 0; x < GAME_X; x++)
		for (int y = 0; y < GAME_Y; y++)
			BOARD[x][y] = rand() % 6 + 1;
}

//this function draws a message to user for hint or load a game
void drawLoad_and_help(sf::RenderWindow& window)
{

	sf::RectangleShape loaded_game(sf::Vector2f(255, 70));
	loaded_game.setFillColor(sf::Color(0, 0, 0, 230));
	loaded_game.setPosition(80, 560);


	sf::RectangleShape hint(sf::Vector2f(255, 70));
	hint.setFillColor(sf::Color(0 ,0 , 0, 230));
	hint.setPosition(415, 560);

	sf::Font font;
	if (!font.loadFromFile("font.otf"))
		cout << "Error";

	sf::Text load_text;
	load_text.setFont(font);
	load_text.setString("Press L to Load game");
	load_text.setCharacterSize(25);
	load_text.setFillColor(sf::Color(102, 255, 204));
	load_text.setPosition(95, 578);

	sf::Text hint_text;
	hint_text.setFont(font);
	hint_text.setString("Press H for Hint");
	hint_text.setCharacterSize(25);
	hint_text.setFillColor(sf::Color(102, 255, 204));
	hint_text.setPosition(455, 578);

	window.draw(loaded_game);
	window.draw(hint);
	window.draw(load_text);
	window.draw(hint_text);
}

//finction loading the background
void loadBG(sf::RenderWindow& window)
{
	sf::Texture texture;
	sf::Sprite sprite;

	if (!texture.loadFromFile("bgg.jpg"))
		cout << "Error";

	sprite.setTexture(texture);

	window.draw(sprite);
}

//this function displays a message on the screen if no moves are possible or if the board has been reset
void tryAgain_and_gameReseted(sf::RenderWindow& window)
{
	sf::Font font;
	if (!font.loadFromFile("font.otf"))
		cout << "Error";

	sf::Text try_again;
	try_again.setFont(font);
	try_again.setString("Move not possible, try again.");
	try_again.setCharacterSize(25);
	try_again.setFillColor(sf::Color(51, 0, 51));
	try_again.setPosition(350, 30);

	sf::Text reset_game;
	reset_game.setFont(font);
	reset_game.setString("No more possible switches! Shuffling.");
	reset_game.setCharacterSize(25);
	reset_game.setFillColor(sf::Color(51, 0, 51));
	reset_game.setPosition(350, 30);

	if (MOVE_NOT_POSSIBLE == true) {
		window.draw(try_again);
	}
	if (GAME_RESET == true) {
		window.draw(reset_game);
	}
}

//this function displays clears the window and displays a message when the game ends
void gameOver_or_youWon(sf::RenderWindow& window)
{
	sf::Font font;
	if (!font.loadFromFile("font.otf"))
		cout << "Error";

	sf::Text game_over;
	game_over.setFont(font);
	game_over.setString("       Out of Moves! \nBetter luck next time :)");
	game_over.setCharacterSize(60);
	game_over.setFillColor(sf::Color(153, 50, 204));
	game_over.setPosition(100, 250);

	sf::Text you_win;
	you_win.setFont(font);
	you_win.setString("YOU WIN!!!");
	you_win.setCharacterSize(60);
	you_win.setFillColor(sf::Color(153, 50, 204));
	you_win.setPosition(200, 300);

	if (MOVES <= 0)
		window.draw(game_over);

	if (SCORE >= TARGET)
		window.draw(you_win);

}

//this function draws the target, moves and scores on window
void scorePanel(sf::RenderWindow& window)
{
	sf::Font font;
	if (!font.loadFromFile("font.otf"))
		cout << "Error";

	char text[100], buffer[10];

	sf::Text target;
	target.setFont(font);
	_itoa_s(TARGET, buffer, 10);
	strcpy_s(text, "Target: \n");
	strcat_s(text, buffer);
	target.setString(text);
	target.setCharacterSize(40);
	target.setFillColor(sf::Color::Black);
	target.setPosition(70, 70);

	sf::Text moves;
	moves.setFont(font);
	_itoa_s(MOVES, buffer, 10);
	strcpy_s(text, "Moves: \n");
	strcat_s(text, buffer);
	moves.setString(text);
	moves.setCharacterSize(40);
	moves.setFillColor(sf::Color::Black);
	moves.setPosition(70, 200);

	sf::Text score;
	score.setFont(font);
	_itoa_s(SCORE, buffer, 10);
	strcpy_s(text, "Score: \n");
	strcat_s(text, buffer);
	score.setString(text);
	score.setCharacterSize(40);
	score.setFillColor(sf::Color::Black);
	score.setPosition(70, 330);

	window.draw(target);
	window.draw(moves);
	window.draw(score);

}

//this function checks if any tiles are making a possible match and changes the matched tiles to 0 so they can be removed and replaced
bool matched()
{
	bool isMatch = false;

	// for upper right elbow
	for (int y = 0; y < GAME_Y; y++)
		for (int x = 0; x < GAME_X - 2; x++)
			if (BOARD[x][y] == BOARD[x + 1][y] && BOARD[x + 1][y] == BOARD[x + 2][y] &&
				BOARD[x][y] == BOARD[x][y + 1] && BOARD[x][y + 1] == BOARD[x][y + 2] &&
				BOARD[x][y] != 0)
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 60;

					for (int n = 0; n < 3; n++) {
						BOARD[x + n][y] = 0;
						BOARD[x][y + n] = 0;
					}
					BOARD[x][y] = 8;
				}
			}

	//for upper left elbow
	for (int y = 0; y < GAME_Y; y++)
		for (int x = GAME_X; x > 2; x--)
			if (BOARD[x][y] == BOARD[x - 1][y] && BOARD[x - 1][y] == BOARD[x - 2][y] &&
				BOARD[x][y] == BOARD[x][y + 1] && BOARD[x][y + 1] == BOARD[x][y + 2] &&
				BOARD[x][y] != 0)
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 60;
					for (int n = 0; n < 3; n++) {
						BOARD[x - n][y] = 0;
						BOARD[x][y + n] = 0;
					}
					BOARD[x][y] = 8;
				}
			}

	//for lower right elbow
	for (int y = GAME_Y; y > 2; y--)
		for (int x = 0; x < GAME_X - 2; x++)
			if (BOARD[x][y] == BOARD[x + 1][y] && BOARD[x + 1][y] == BOARD[x + 2][y] &&
				BOARD[x][y] == BOARD[x][y - 1] && BOARD[x][y - 1] == BOARD[x][y - 2] &&
				BOARD[x][y] != 0)
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 50;

					for (int n = 0; n < 3; n++) {
						BOARD[x + n][y] = 0;
						BOARD[x][y - n] = 0;
					}
					BOARD[x][y] = 8;
				}
			}

	// for lower left elbow
	for (int y = GAME_Y; y > 2; y--)
		for (int x = GAME_X; x > 2; x--)
			if (BOARD[x][y] == BOARD[x - 1][y] && BOARD[x - 1][y] == BOARD[x - 2][y] &&
				BOARD[x][y] == BOARD[x][y - 1] && BOARD[x][y - 1] == BOARD[x][y - 2] &&
				BOARD[x][y] != 0)
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 50;

					for (int n = 0; n < 3; n++) {
						BOARD[x - n][y] = 0;
						BOARD[x][y - n] = 0;
					}
					BOARD[x][y] = 8;
				}
			}

	//for 5 same in a row
	for (int y = 0; y < GAME_Y; y++)
		for (int x = 0; x < GAME_X - 4; x++)
			if (BOARD[x][y] == BOARD[x + 1][y] && BOARD[x + 1][y] == BOARD[x + 2][y] &&
				BOARD[x + 2][y] == BOARD[x + 3][y] && BOARD[x + 3][y] == BOARD[x + 4][y] &&
				BOARD[x][y] != 0)
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 50;

					for (int n = 1; n < 5; n++)
						BOARD[x + n][y] = 0;

					BOARD[x][y] = 8;
				}
			}
	//for 5 same in a coloum
	for (int x = 0; x < GAME_X; x++)
		for (int y = 0; y < GAME_Y - 4; y++)
			if (BOARD[x][y] == BOARD[x][y + 1] && BOARD[x][y + 1] == BOARD[x][y + 2] &&
				BOARD[x][y + 2] == BOARD[x][y + 3] && BOARD[x][y + 3] == BOARD[x][y + 4] &&
				BOARD[x][y] != 0)
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 50;

					for (int n = 1; n < 5; n++)
						BOARD[x][y + n] = 0;

					BOARD[x][y] = 8;
				}
			}


	//For 5 same in a right diagnol
	for (int y = 0; y < GAME_Y; y++)
		for (int x = 0; x < GAME_X - 4; x++)
			if (BOARD[x][y] == BOARD[x + 1][y + 1] && BOARD[x + 1][y + 1] == BOARD[x + 2][y + 2] &&
				BOARD[x + 2][y + 2] == BOARD[x + 3][y + 3] && BOARD[x + 3][y + 3] == BOARD[x + 4][y + 4] &&
				BOARD[x][y] != 0)
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 50;

					for (int n = 1; n < 5; n++)
						BOARD[x + n][y + n] = 0;

					BOARD[x][y] = 8;
				}
			}

	//For 5 same in a left diagnol
	for (int y = GAME_Y; y > 4; y--)
		for (int x = 0; x < GAME_X - 4; x++)
			if (BOARD[x][y] == BOARD[x + 1][y - 1] && BOARD[x + 1][y - 1] == BOARD[x + 2][y - 2] &&
				BOARD[x + 2][y - 2] == BOARD[x + 3][y - 3] && BOARD[x + 3][y - 3] == BOARD[x + 4][y - 4] &&
				BOARD[x][y] != 0)
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 50;

					for (int n = 1; n < 5; n++)
						BOARD[x + n][y - n] = 0;

					BOARD[x][y] = 8;
				}
			}

	//for 4 same in a row
	for (int y = 0; y < GAME_Y; y++)
		for (int x = 0; x < GAME_X - 3; x++)
			if (BOARD[x][y] == BOARD[x + 1][y] && BOARD[x + 1][y] == BOARD[x + 2][y] &&
				BOARD[x + 2][y] == BOARD[x + 3][y] && BOARD[x][y] != 0)
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 40;
					for (int n = 1; n < 4; n++)
						BOARD[x + n][y] = 0;

					BOARD[x][y] = 7;
				}
			}

	//for 4 same in a coloum
	for (int x = 0; x < GAME_X; x++)
		for (int y = 0; y < GAME_Y - 3; y++)
			if (BOARD[x][y] == BOARD[x][y + 1] && BOARD[x][y + 1] == BOARD[x][y + 2] &&
				BOARD[x][y + 2] == BOARD[x][y + 3] && BOARD[x][y] != 0)
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 30;

					for (int n = 1; n < 4; n++)
						BOARD[x][y + n] = 0;

					BOARD[x][y] = 7;
				}
			}

	//For 4 same in a right diagnol
	for (int y = 0; y < GAME_Y; y++)
		for (int x = 0; x < GAME_X - 3; x++)
			if (BOARD[x][y] == BOARD[x + 1][y + 1] && BOARD[x + 1][y + 1] == BOARD[x + 2][y + 2] &&
				BOARD[x + 2][y + 2] == BOARD[x + 3][y + 3] && BOARD[x][y] != 0)
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 40;

					for (int n = 1; n < 4; ++n)
						BOARD[x + n][y + n] = 0;

					BOARD[x][y] = 7;
				}
			}

	//For 4 same in a left diagnol
	for (int y = GAME_Y; y > 3; y--)
		for (int x = 0; x < GAME_X - 3; x++)
			if (BOARD[x][y] == BOARD[x + 1][y - 1] && BOARD[x + 1][y - 1] == BOARD[x + 2][y - 2] &&
				BOARD[x + 2][y - 2] == BOARD[x + 3][y - 3] && BOARD[x][y] != 0)
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 40;

					for (int n = 1; n < 4; ++n)
						BOARD[x + n][y - n] = 0;

					BOARD[x][y] = 7;
				}
			}

	//For 3 same in a row
	for (int y = 0; y < GAME_Y; y++)
		for (int x = 0; x < GAME_X - 2; x++)
			if (BOARD[x][y] == BOARD[x + 1][y] && BOARD[x + 1][y] == BOARD[x + 2][y] && BOARD[x][y] != 0) 
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 30;

					for (int n = 0; n < 3; ++n)
						BOARD[x + n][y] = 0;
				}
			}

	//for 3 same in a coloum
	for (int x = 0; x < GAME_X; x++)
		for (int y = 0; y < GAME_Y - 2; y++)
			if (BOARD[x][y] == BOARD[x][y + 1] && BOARD[x][y + 1] == BOARD[x][y + 2] && BOARD[x][y] != 0)
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 30;

					for (int n = 0; n < 3; ++n)
						BOARD[x][y + n] = 0;
				}
			}


	//For 3 same in a right diagnol
	for (int y = 0; y < GAME_Y; y++)
		for (int x = 0; x < GAME_X - 2; x++)
			if (BOARD[x][y] == BOARD[x + 1][y + 1] && BOARD[x + 1][y + 1] == BOARD[x + 2][y + 2] && BOARD[x][y] != 0)
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 30;

					for (int n = 0; n < 3; ++n)
						BOARD[x + n][y + n] = 0;
				}
			}

	//For 3 same in a left diagnol
	for (int y = GAME_Y; y > 2; y--)
		for (int x = 0; x < GAME_X - 2; x++)
			if (BOARD[x][y] == BOARD[x + 1][y - 1] && BOARD[x + 1][y - 1] == BOARD[x + 2][y - 2] && BOARD[x][y] != 0) 
			{
				isMatch = true;
				if (HINT_X == false && HINT_Y == false) {
					SCORE += 30;

					for (int n = 0; n < 3; ++n)
						BOARD[x + n][y - n] = 0;
				}
			}
	
	return isMatch;
}

//this function removes gives a effect of the tiles falling down when a match is made by bringing the 0 up and giving it another value
void moveTiles()
{
	//moving all the tiles that are 0 upwards by swapping the zero with the value above ( + 1 in the y coordinate)
	for (int i = 0; i < GAME_Y; i++)
		for (int x = 0; x < GAME_X; x++)
			for (int y = 0; y < GAME_Y - 1; y++)
			{
				if (BOARD[x][y + 1] == 0)
				{
					BOARD[x][y + 1] = BOARD[x][y];
					BOARD[x][y] = 0;
				}
			}

	//giveing a random number( 1 to 6 ) to the zero
	for (int x = 0; x < GAME_X; x++)
		for (int y = 0; y < GAME_Y - 1; y++)
			if (BOARD[x][y] == 0)
			{
				BOARD[x][y] = rand() % 6 + 1;

			}

}

//funtion that explodes some tiles whenever a special tile i.e diamond is swappped 
void specialExplosion(int x, int y)
{
	if (HINT_X == false && HINT_Y == false) {
		SCORE += 100;

		//for 3x3 white diamond explosion
		if (BOARD[x][y] == 7) {
			for (int n = -1; n < 2; n++)
				for (int m = -1; m < 2; m++)
					if (x + m >= 0 && x + m < GAME_X && y + n >= 0 && y + n < GAME_Y)
						BOARD[x + m][y + n] = 0;
		}

		//for row and coloum black diamond explosion
		if (BOARD[x][y] == 8) {
			for (int n = 0; n < GAME_X; n++)
				BOARD[n][y] = 0;
			for (int m = 0; m < GAME_Y; m++)
				BOARD[x][m] = 0;
		}
	}
}

//this function swaps the selected polygon and then reverses it if no match is made
void swap(int x, int y, int to_x, int to_y)
{
	//two tmp necessary for the reversing
	int tmp1 = BOARD[x][y];
	int tmp2 = BOARD[x + to_x][y + to_y];
	BOARD[x][y] = tmp2;
	BOARD[x + to_x][y + to_y] = tmp1;

	bool reverse = true;


	//checks if a special tile was selected then swapped
	if (BOARD[x][y] == 7 || BOARD[x][y] == 8) {
		specialExplosion(x, y);
		moveTiles();
		reverse = false;
	}

	//checks if a special tile was swapped with another selected tile
	if (BOARD[x + to_x][y + to_y] == 7 || BOARD[x + to_x][y + to_y] == 8) {
		specialExplosion(x + to_x, y + to_y);
		moveTiles();
		reverse = false;
	}

	while (matched())
	{
		moveTiles();
		SELECT_X = -1;
		SELECT_Y = -1;
		reverse = false;
	}

	if (reverse)
	{
		BOARD[x][y] = tmp1;
		BOARD[x + to_x][y + to_y] = tmp2;
		MOVE_NOT_POSSIBLE = true;
	}
}

//a test swap used by the hint function to check matches
void testSwap(int x, int y, int to_x, int to_y)
{
	int tmp1 = BOARD[x][y];
	int tmp2 = BOARD[x + to_x][y + to_y];
	BOARD[x][y] = tmp2;
	BOARD[x + to_x][y + to_y] = tmp1;
}

//function looks for hint
void hint()
{
	//loops to check for any matches when a tile is moved to right (x coordinate)
	for (int i = 0; i < GAME_Y; ++i) {
		for (int j = 0; j < GAME_X - 1; ++j) {
			testSwap(i, j, 1, 0);
			if (matched()) {
				HINT_SELECT_X = i;
				HINT_SELECT_Y = j;
				testSwap(i, j, 1, 0);
				HINT_Y = false;
				return;
			}
			testSwap(i, j, 1, 0);
		}
	}

	//loops to check for any matches when a tile is moved down (y coordinate)
	for (int i = 0; i < GAME_Y - 1; ++i) {
		for (int j = 0; j < GAME_X ; ++j) {
			testSwap(i, j, 0, 1);
			if (matched()) {
				swap(i, j, 0, 1);
				HINT_SELECT_X = i;
				HINT_SELECT_Y = j;
				testSwap(i, j, 1, 0);
				HINT_X = false;
				return;
			}
			testSwap(i, j, 0, 1);
		}
	}
}

//initalizes the board again if there is no moves possible
void checkIsStuck()
{
	HINT_X = true;
	HINT_Y = true;

	//hint function checks for all the possible matches and if at the end bothh hint_x and hint_y are false it means no moves are possible
	hint();

	if (HINT_X = true && HINT_Y == true)
	{
		GAME_RESET = true;
		initialize(BOARD);
		HINT_X = false;
		HINT_Y = false;
		while (matched())
			moveTiles();
	}
}

//function saves the game in a txt file when the window/ game is closed
void SaveGame()
{
	ofstream fout;

	fout.open("GameState.txt", ios::out);

	fout << SCORE << endl << MOVES << endl;
	for (int i = 0; i < GAME_X; i++)
		for (int j = 0; j < GAME_Y; j++)
			fout << BOARD[i][j] << endl;
	
	fout.close();
}

//function loads the last saved game from a txt file whenever the user presses L
void LoadGame()
{
	ifstream fin("GameState.txt");

	fin >> SCORE >> MOVES;

	for (int i = 0; i < GAME_X; i++)
		for (int j = 0; j < GAME_Y; j++)
			fin >> BOARD[i][j];

	fin.close();
}

int main()
{
	initialize(BOARD);
	while (matched())
		moveTiles();

	sf::RenderWindow window(sf::VideoMode(750, 700), "My Candy Crush");

	while (window.isOpen())
	{

		//initializing the booleans after every window frame
		HINT_X = false;
		HINT_Y = false;
		MOVE_NOT_POSSIBLE = false;
		GAME_RESET = false;

		sf::Event game;
		while (window.pollEvent(game))
		{
			if (game.type == sf::Event::Closed)
			{
				SaveGame();
				window.close();
				break;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				int px = sf::Mouse::getPosition(window).x;
				int py = sf::Mouse::getPosition(window).y;

				selectTileOnClick(px, py);
				break;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				swap(SELECT_X, SELECT_Y, -1, 0);
				if (MOVE_NOT_POSSIBLE == false)
					MOVES--;
				break;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				swap(SELECT_X, SELECT_Y, 1, 0);
				if (MOVE_NOT_POSSIBLE == false)
					MOVES--;
				break;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				swap(SELECT_X, SELECT_Y, 0, -1);
				if (MOVE_NOT_POSSIBLE == false)
					MOVES--;
				break;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				swap(SELECT_X, SELECT_Y, 0, 1);
				if (MOVE_NOT_POSSIBLE == false)
					MOVES--;
				break;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
			{
				HINT_X = true;
				HINT_Y = true;
				hint();
				break;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			{
				LoadGame();
				break;
			}


		}

		if (MOVES <= 0 || SCORE >= TARGET) {
			window.clear();
			gameOver_or_youWon(window);
			window.display();
		}
		else {
			window.clear();
			loadBG(window);
			scorePanel(window);
			drawTiles(BOARD, window);
			drawLoad_and_help(window);
			checkIsStuck();
			tryAgain_and_gameReseted(window);
			window.display();
		}
		
	}
	return 0;
}