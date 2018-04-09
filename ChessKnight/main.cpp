#include "ChessKnight.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	ChessKnight chessKnight;
	chessKnight.show();

	return QApplication::exec();
}
