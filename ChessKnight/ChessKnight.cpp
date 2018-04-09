#include "ChessKnight.h"
#include <QMessageBox>
#include <sstream>

ChessKnight::ChessKnight(QWidget *parent) : QMainWindow(parent)
{
	this->scene = new QGraphicsScene(this);
	this->view = new QGraphicsView(scene, this);
	this->ctrl = new ChessController(*scene, this);
	this->setCentralWidget(view);
	this->setFixedSize(BOARD_SIZE + 2, BOARD_SIZE + 2);
	this->initScene();
	this->initSceneBackground();
	QMessageBox::information(Q_NULLPTR, QString("How to use!"), QString("Left button click: move to the next block.\nRight button click: choose the block to reset.\nMiddle button click: finish the traversal."));
}

ChessKnight::~ChessKnight()
= default;

void ChessKnight::initScene()
{
	this->scene->setSceneRect(0, 0, BOARD_SIZE, BOARD_SIZE);
}

void ChessKnight::initSceneBackground()
{
	QPixmap bg(BLOCK_SIZE * 2, BLOCK_SIZE * 2);
	QPainter p(&bg);
	p.setPen(QPen(Qt::NoPen));
	p.setBrush(QBrush(Qt::white));
	p.drawRect(0, 0, BLOCK_SIZE, BLOCK_SIZE);
	p.drawRect(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
	p.setBrush(QBrush(Qt::lightGray));
	p.drawRect(0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
	p.drawRect(BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE);
	view->setBackgroundBrush(QBrush(bg));
}

Chess::Chess() : currentKnight(0, 1)
{
	for(auto i = 0; i < 8; i++)
	{
		this->board.emplace_back(8, 0);
	}
	this->board[0][1] = 1;
}

void Chess::reset(const std::pair<int, int>& knightPosition)
{
	this->currentKnight = knightPosition;
	for(auto i = 0; i < 8; i++)
		for(auto j = 0; j < 8; j++)
			this->board[i][j] = 0;
	this->board[knightPosition.first][knightPosition.second] = 1;
}

std::vector<std::pair<int, int>> Chess::getExits(const std::pair<int, int>& position) const
{
	std::vector<std::pair<int, int>> exits;
	for (auto i : dir)
	{
		const int row = position.first + i[0];
		const int col = position.second + i[1];
		if (row >= 0 && row < 8 && col >= 0 && col < 8 && this->board[row][col] == 0)
			exits.emplace_back(row, col);
	}
	return exits;
}

bool Chess::next()
{
	auto min = SIZE_MAX;
	const auto order = this->board[this->currentKnight.first][this->currentKnight.second];
	auto exitsOfPresent = this->getExits(this->currentKnight);
	if (exitsOfPresent.empty())
		return false;
	for (const auto& exit : exitsOfPresent)
	{
		const auto temp = this->getExits(exit).size();
		if (min > temp)
		{
			min = temp;
			this->currentKnight = exit;
		}
	}
	this->board[this->currentKnight.first][this->currentKnight.second] = order + 1;
	return true;
}

const std::vector<std::vector<int>>& Chess::getBoard() const
{
	return this->board;
}

const std::pair<int, int>& Chess::getKnight() const
{
	return this->currentKnight;
}

ChessController::ChessController(QGraphicsScene& scene, QObject* parent) : scene(scene)
{
	this->chess = new Chess();
	this->redrawAll();
	this->scene.installEventFilter(this);
}

ChessController::~ChessController()
{
	free(this->chess);
}

void ChessController::chessReset(const std::pair<int, int>& position)
{
	this->chess->reset(position);
	this->redrawAll();
}

void ChessController::chessNext()
{
	if(!this->chess->next()) // failed to continue
	{
		QMessageBox::warning(Q_NULLPTR, QString("Warning!"), QString("Can not move!"));
	}
	else
	{
		this->redrawAll();
	}
}

void ChessController::chessFinish()
{
	if (!this->chess->next()) // failed to continue
	{
		QMessageBox::warning(Q_NULLPTR, QString("Warning!"), QString("Can not move!"));
	}
	else
	{
		while (this->chess->next());
		this->redrawAll();
	}
}

bool ChessController::eventFilter(QObject* watched, QEvent* event)
{
	if(event->type() == QEvent::GraphicsSceneMousePress)
	{
		this->handleMouseClicked(dynamic_cast<QGraphicsSceneMouseEvent*>(event));
		return true;
	}
	else
	{
		return QObject::eventFilter(watched, event);
	}
}

void ChessController::handleMouseClicked(QGraphicsSceneMouseEvent* event)
{
	if(event->button() == Qt::LeftButton)
	{
		this->chessNext();
	}
	else if(event->button() == Qt::RightButton)
	{
		const auto x = event->scenePos().x();
		const auto y = event->scenePos().y();
		this->chessReset(std::pair<int, int>(static_cast<int>(y) / BLOCK_SIZE, static_cast<int>(x) / BLOCK_SIZE));
	}
	else if(event->button() == Qt::MiddleButton)
	{
		this->chessFinish();
	}
}

void ChessController::drawOrder()
{
	for (auto i = 0; i < 8; i++)
	{
		for(auto j = 0; j < 8; j++)
		{
			if(this->chess->getBoard()[i][j] != 0)
			{
				this->scene.addItem(new Order(j * BLOCK_SIZE, i * BLOCK_SIZE, this->chess->getBoard()[i][j]));
			}
		}
	}
}

void ChessController::drawKnight()
{
	const auto x = this->chess->getKnight().second;
	const auto y = this->chess->getKnight().first;
	this->scene.addItem(new Knight(x * BLOCK_SIZE, y * BLOCK_SIZE));
}

void ChessController::redrawAll()
{
	scene.clear();
	this->drawKnight();
	this->drawOrder();
}

Knight::Knight(qreal x, qreal y)
{
	this->setPos(x, y);
	this->setData(CDType, COKnight);
}

QRectF Knight::boundingRect() const
{
	return {0, 0, BLOCK_SIZE, BLOCK_SIZE};
}

void Knight::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->fillPath(this->shape(), Qt::darkCyan);
	painter->restore();
}

QPainterPath Knight::shape() const
{
	QPainterPath p;
	p.addEllipse(QPoint(BLOCK_SIZE / 2, BLOCK_SIZE / 2), KNIGHT_RADIUS, KNIGHT_RADIUS);
	return p;
}

Order::Order(qreal x, qreal y, int n) : orderNo(QString::number(n, 10))
{
	this->setPos(x, y);
	this->setData(CDType, COOrder);
}

QRectF Order::boundingRect() const
{
	return {0, 0, BLOCK_SIZE, BLOCK_SIZE};
}

void Order::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->drawText(BLOCK_SIZE / 2 - 5, BLOCK_SIZE / 2 + 5, this->orderNo);
	painter->restore();
}
