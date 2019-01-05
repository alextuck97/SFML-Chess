#include "..\header\Moves.h"

Moves::Moves()
{

}


Moves::Moves(const Gameboard & gameBoard) : gameBoard(gameBoard)
{
	registerMoveFunction<KnightMoves>(Pieces::Knight);
	registerMoveFunction<RookMoves>(Pieces::Rook);
	registerMoveFunction<BishopMoves>(Pieces::Bishop);
	registerMoveFunction<KingMoves>(Pieces::King);
	registerMoveFunction<QueenMoves>(Pieces::Queen);
	registerMoveFunction<PawnMoves>(Pieces::Pawn);
}


std::list<sf::Vector2f> * Moves::getMoves(const GamePiece & piece)
{
	return (*getMoveFunction(piece.piece))(piece.position, piece.color);
}


MoveFunction * Moves::getMoveFunction(Pieces piece)
{
	return moves[piece];
}

