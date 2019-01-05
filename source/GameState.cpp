#include "..\header\GameState.h"

GameState::GameState(StateStack & stack, Context context) : State(stack, context), gameBoard(8)
{
	initializeBoard();
	initTextureMap();
	pieceTexture.loadFromFile("resources/ChessPiecesArray.png");
	mMoves = Moves(gameBoard);
	if (!gameFont.loadFromFile("resources/NeonMachine.ttf"))
	{
		std::cout << "Error loading font file" << std::endl;
	}

	text.setFont(gameFont);
	text.setFillColor(sf::Color::Red);
	

	possibleMoves = nullptr;

}

//Delete game piece objects
GameState::~GameState()
{
	for (auto & itr1 = gameBoard.rbegin(); itr1 != gameBoard.rend(); itr1++)
	{
		for (auto & itr2 = itr1->rbegin(); itr2 != itr1->rend(); itr2++)
		{
			delete *itr2;
		}
	}
}

GamePiece::GamePiece(Pieces piece, Orientation orientation,  sf::Vector2f &position, PieceColor color, bool inPlay)
{
	this->piece = piece;
	this->orientation = orientation;
	this->position = position;
	this->color = color;
	this->inPlay = inPlay;
}

std::list<sf::Vector2f> * GameState::getMoves(GamePiece piece)
{
	return (*mMoves.getMoveFunction(piece.piece))(piece.position, piece.color);
}


void GameState::draw()
{
	drawGameBoard();
}


bool GameState::update(sf::Time dt)
{
	std::cout << "I like to update too" << std::endl;
	return true;
}
bool GameState::handleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::Resized)
	{
		getContext().window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		//check where it was pressed
		//draw the legal moves
		
		mouseButtonPressed(event);
		return false;
	}
	return true;
}

void GameState::initializeBoard()
{
	//Fill in starting black pieces
	gameBoard[0].push_back(new GamePiece(Rook, Left, sf::Vector2f(0, 0), Black, true));
	gameBoard[0].push_back(new GamePiece(Knight, Left, sf::Vector2f(1, 0), Black, true));
	gameBoard[0].push_back(new GamePiece(Bishop, Left, sf::Vector2f(2, 0), Black, true));
	gameBoard[0].push_back(new GamePiece(Queen, Royalty, sf::Vector2f(3, 0), Black, true));
	gameBoard[0].push_back(new GamePiece(King, Royalty, sf::Vector2f(4, 0), Black, true));
	gameBoard[0].push_back(new GamePiece(Bishop, Right, sf::Vector2f(5, 0), Black, true));
	gameBoard[0].push_back(new GamePiece(Knight, Right, sf::Vector2f(6, 0), Black, true));
	gameBoard[0].push_back(new GamePiece(Rook, Right, sf::Vector2f(7, 0), Black, true));
	
	for (int i = 0; i < 8; i++)
	{
		gameBoard[1].push_back(new GamePiece(Pawn, NA, sf::Vector2f(i, 1), Black, true));
	}

	//Fill in blank spaces
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			gameBoard[i].push_back(new GamePiece(None, NA, sf::Vector2f(j, i), Unaffiliated, false));
		}
	}
	
	//Fill in starting white pieces
	gameBoard[7].push_back(new GamePiece(Rook, Left, sf::Vector2f(0, 7), White, true));
	gameBoard[7].push_back(new GamePiece(Knight, Left, sf::Vector2f(1, 7), White, true));
	gameBoard[7].push_back(new GamePiece(Bishop, Left, sf::Vector2f(2, 7), White, true));
	gameBoard[7].push_back(new GamePiece(Queen, Royalty, sf::Vector2f(3, 7), White, true));
	gameBoard[7].push_back(new GamePiece(King, Royalty, sf::Vector2f(4, 7), White, true));
	gameBoard[7].push_back(new GamePiece(Bishop, Right, sf::Vector2f(5, 7), White, true));
	gameBoard[7].push_back(new GamePiece(Knight, Right, sf::Vector2f(6, 7), White, true));
	gameBoard[7].push_back(new GamePiece(Rook, Right, sf::Vector2f(7, 7), White, true));

	for (int i = 0; i < 8; i++)
	{
		gameBoard[6].push_back(new GamePiece(Pawn, NA, sf::Vector2f(i, 6), White, true));
	}

}

//Tentative
void GameState::initTextureMap()
{
	textureRects[std::pair<Pieces,PieceColor>(Queen,Black)] = sf::IntRect(0, 0, 60, 60);
	textureRects[std::pair<Pieces, PieceColor>(King, Black)] = sf::IntRect(60, 0, 60, 60);
	textureRects[std::pair<Pieces, PieceColor>(Rook, Black)] = sf::IntRect(120, 0, 60, 60);
	textureRects[std::pair<Pieces, PieceColor>(Knight, Black)] = sf::IntRect(180, 0, 60, 60);
	textureRects[std::pair<Pieces, PieceColor>(Bishop, Black)] = sf::IntRect(240, 0, 60, 60);
	textureRects[std::pair<Pieces, PieceColor>(Pawn, Black)] = sf::IntRect(300, 0, 60, 60);

	textureRects[std::pair<Pieces, PieceColor>(Queen, White)] = sf::IntRect(0, 60, 60, 60);//Sprites probably. Also I think gamepiece should be own class
	textureRects[std::pair<Pieces, PieceColor>(King, White)] = sf::IntRect(60, 60, 60, 60);
	textureRects[std::pair<Pieces, PieceColor>(Rook, White)] = sf::IntRect(120, 60, 60, 60);
	textureRects[std::pair<Pieces, PieceColor>(Knight, White)] = sf::IntRect(180, 60, 60, 60);
	textureRects[std::pair<Pieces, PieceColor>(Bishop, White)] = sf::IntRect(240, 60, 60, 60);
	textureRects[std::pair<Pieces, PieceColor>(Pawn, White)] = sf::IntRect(300, 60, 60, 60);
}

void GameState::drawGameBoard()
{//Concerns with scope of drawn shapes

	float x = getContext().window->getSize().x;
	
	float y = getContext().window->getSize().y;

	sf::Vector2f gameSquareCoords = sf::Vector2f(.15*x, .0333*y);

	sf::RectangleShape boardOutline  = sf::RectangleShape(sf::Vector2f(.75*x, y));
	sf::RectangleShape boardSquare = sf::RectangleShape(sf::Vector2f(.0875*x, .1167*y));

	boardOutline.setFillColor(sf::Color::Yellow);
	boardSquare.setFillColor(sf::Color::Blue);

	boardOutline.setPosition(sf::Vector2f(.125*x, 0));
	boardSquare.setPosition(sf::Vector2f(.15*x, .033*y));

	getContext().window->draw(boardOutline);
	
	//Draw the board
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			boardSquare.setPosition(gameSquareCoords.x, gameSquareCoords.y);
			getContext().window->draw(boardSquare);
			
			//drawPiece(*gameBoard[i][j], gameSquareCoords.x, gameSquareCoords.y);
			
			gameSquareCoords.x += .0875*x;
			
			swapColor(boardSquare);
			
		}
		swapColor(boardSquare);
		gameSquareCoords.x = .15*x;
		gameSquareCoords.y += .1167*y;
	}
	drawPossibleMoves();

	gameSquareCoords = sf::Vector2f(.15*x, .0333*y);

	//Draw pieces
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			drawPiece(*gameBoard[i][j], gameSquareCoords.x, gameSquareCoords.y);
			gameSquareCoords.x += .0875*x;
		}
		gameSquareCoords.x = .15*x;
		gameSquareCoords.y += .1167*y;
	}

	

}

void GameState::drawPiece(const GamePiece & gamePiece, float x, float y)
{
	sf::Sprite pieceSprite;
	if (gamePiece.piece != None)
	{
		int sizex = getContext().window->getSize().x;
		int sizey = getContext().window->getSize().y;
		
		pieceSprite.setTexture(pieceTexture);
		pieceSprite.setTextureRect(textureRects[std::pair<Pieces, PieceColor>(gamePiece.piece, gamePiece.color)]);
		pieceSprite.setPosition(x,y);
		pieceSprite.setScale(.075*sizex / 60, .1*sizey / 60);
		
		getContext().window->draw(pieceSprite);
	}
}

void GameState::drawPossibleMoves()
{
	if (possibleMoves != nullptr)
	{
		float x = getContext().window->getSize().x;
		float y = getContext().window->getSize().y;

		sf::Vector2f gameSquareCoords;
		sf::RectangleShape legalMove = sf::RectangleShape(sf::Vector2f(.0875*x, .1167*y));
		
		legalMove.setFillColor(sf::Color::Red);
		legalMove.setOutlineColor(sf::Color::Black);
		legalMove.setOutlineThickness(2.f);

		//Overlay squares with a legal move
		for (auto vec : *possibleMoves)
		{
			gameSquareCoords.x = vec.x * .0875*x + .15*x;
			gameSquareCoords.y = vec.y * .1167*y + .0333*y;
			legalMove.setPosition(gameSquareCoords);
			getContext().window->draw(legalMove);
		}
	}
}

void GameState::swapColor(sf::RectangleShape & boardSquare)
{
	if (boardSquare.getFillColor() == sf::Color::White)
	{
		boardSquare.setFillColor(sf::Color::Blue);
	}
	else
	{
		boardSquare.setFillColor(sf::Color::White);
	}
}


void GameState::mouseButtonPressed(const sf::Event & event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*(getContext().window)));
		sf::Vector2i boardCoords = thePlayers.clickSquare(mousePos, getContext().window->getSize());

		if(boardCoords.x <= 7 && boardCoords.x >= 0)
		{
			if (boardCoords.y <= 7 && boardCoords.y >= 0)
			{
				//Get the possible moves if the clicked square has the players piece
				if (thePlayers.getWhoseTurn() == gameBoard[boardCoords.y][boardCoords.x]->color)
				{
					if(possibleMoves != nullptr){possibleMoves->clear();}
			
					possibleMoves = mMoves.getMoves(*gameBoard[boardCoords.y][boardCoords.x]);
					thePlayers.setSelectedPiece(boardCoords);
				}
				//Clicked square does not have players piece, so check if the clicked square is a legal move
				//If so move piece
				else if (inPossibleMoves(boardCoords) && gameBoard[boardCoords.y][boardCoords.x]->color == Unaffiliated)
				{
					//Swap the players selected piece with boardCoords
					movePiece(boardCoords);
				}
				else if(inPossibleMoves(boardCoords))
				{
					//Capture a piece!
					std::pair<Pieces, PieceColor> capPiece = capturePiece(boardCoords);
					endGame(capPiece);

				}
			}	
		}
	}
}

bool GameState::inPossibleMoves(sf::Vector2i selectedMove)
{
	if (possibleMoves != nullptr)
	{
		for (auto vec : *possibleMoves)
		{
			if (sf::Vector2i(vec) == selectedMove)
				return true;
		}
	}
	return false;
}

std::pair<Pieces, PieceColor> GameState::capturePiece(sf::Vector2i boardCoords)
{
	sf::Vector2i selectedPiece = thePlayers.getSelectedPiece();
	std::pair<Pieces, PieceColor> capPiece;

	std::swap(*gameBoard[boardCoords.y][boardCoords.x], *gameBoard[selectedPiece.y][selectedPiece.x]);
	gameBoard[boardCoords.y][boardCoords.x]->position = sf::Vector2f(boardCoords);
	
	capPiece.second = gameBoard[selectedPiece.y][selectedPiece.x]->color;
	gameBoard[selectedPiece.y][selectedPiece.x]->color = Unaffiliated;
	
	capPiece.first = gameBoard[selectedPiece.y][selectedPiece.x]->piece;
	gameBoard[selectedPiece.y][selectedPiece.x]->piece = None;

	gameBoard[selectedPiece.y][selectedPiece.x]->position = sf::Vector2f(selectedPiece);
	if (possibleMoves != nullptr) { possibleMoves->clear(); }
	thePlayers.switchTurn();

	return capPiece;
}


void GameState::movePiece(sf::Vector2i boardCoords)
{
	sf::Vector2i selectedPiece = thePlayers.getSelectedPiece();
	
	std::swap(*gameBoard[boardCoords.y][boardCoords.x], *gameBoard[selectedPiece.y][selectedPiece.x]);
	
	gameBoard[boardCoords.y][boardCoords.x]->position = sf::Vector2f(boardCoords);
	gameBoard[selectedPiece.y][selectedPiece.x]->position = sf::Vector2f(selectedPiece);
	
	if (possibleMoves != nullptr) { possibleMoves->clear(); }
	
	thePlayers.switchTurn();
}


void GameState::endGame(const std::pair<Pieces, PieceColor> &piece)
{
	if (piece.first == King)
	{
		
		if (piece.second == White)
			setWinner(Black);
		else
			setWinner(White);
		
		//Instantiate the game end state
		requestStackPush(States::GameEnd);
	}
}
