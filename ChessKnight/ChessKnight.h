#pragma once

#ifndef CHESSKNIGHT_H
#define CHESSKNIGHT_H
#include <QtWidgets/QMainWindow>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <vector>
#include "ui_ChessKnight.h"
#define BLOCK_SIZE 80
#define BOARD_SIZE (BLOCK_SIZE * 8)
#define KNIGHT_RADIUS (BLOCK_SIZE / 2 - 5)

enum ChessObjectData
{
	CDType
};

enum ChessObjectType
{
	COKnight,
	COOrder
};

class Chess
{
private:
	// the position the knight is currently in
	std::pair<int, int> currentKnight;
	// if the knight was in the block, the element is the order
	// else, the element is 0
	std::vector<std::vector<int>> board;
	const int dir[8][2] = { { -2,-1 },{ -2,1 },{ -1,2 },{ 1,2 },{ 2,1 },{ 2,-1 },{ 1,-2 },{ -1,-2 } };
	// find out all the exits of the given position
	std::vector<std::pair<int, int>> getExits(const std::pair<int, int> & position) const;

public:
	Chess();
	const std::vector<std::vector<int>>& getBoard() const;
	const std::pair<int, int>& getKnight() const;
	void reset(const std::pair<int, int>& knightPosition);
	bool next();
};

class ChessController : public QObject
{
	Q_OBJECT
public:
	explicit ChessController(QGraphicsScene& scene, QObject *parent = Q_NULLPTR);
	~ChessController();

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;

private:
	void drawOrder();
	void drawKnight();
	void redrawAll();
	void chessReset(const std::pair<int, int>& position);
	void chessNext();
	void chessFinish();
	void handleMouseClicked(QGraphicsSceneMouseEvent* event);
	QGraphicsScene& scene;
	Chess *chess;
};

class Knight : public QGraphicsItem
{
public:
	Knight(qreal x, qreal y);
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
	QPainterPath shape() const override;
};

class Order : public QGraphicsItem
{
public:
	Order(qreal x, qreal y, int n);
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
private:
	QString orderNo;
};

class ChessKnight : public QMainWindow
{
	Q_OBJECT

public:
	explicit ChessKnight(QWidget* parent = Q_NULLPTR);
	~ChessKnight();

private:
	void initScene();
	void initSceneBackground();

	QGraphicsScene* scene;
	QGraphicsView* view;
	ChessController* ctrl;
};

#endif
