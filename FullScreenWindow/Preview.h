#pragma once
#include "main.h"

#include "Profile.h"
#include "Monitor.h"

#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsItem>


class Preview
{
public:
	Preview(QGraphicsView* preview);
	~Preview();

	void defaultView(Monitor* mon);
	void update(Profile* pro, Monitor* mon);
	void drawScreen(double width, double height);
	void drawWindow(double xpos, double ypos, double width, double height, bool isTitleBarHidden, bool isTaskBarShown);

private:
	// Real life monitor size
	double screenWidth = 1,
		screenHeight = 1;
	// Size of the preview, 0,0 is in the top left corner
	double gX, gY, gWidth, gHeight;
	double sX, sY, sWidth, sHeight;
	double wX, wY, wWidth, wHeight;

	double cBorderWidth,
		cTaskBarHeight, cTaskBarButtonSize,
		cWindowBorderWidth, cWindowTitleBarHeight, cWindowMenuBarHeight;

	QGraphicsView* preview;
	QGraphicsScene* scene;

	QPen invisiblePen;

	QBrush borderBrush,
		screenBrush,
		taskBarBrush, taskBarButtonBrush,
		windowContentBrush,
		windowTitleBarBrush,
		windowBackgroundBrush;

	QGraphicsRectItem
		*border,
		*screen,
		*taskBar, *taskBarButton,
		*windowContent,
		*windowTitleBar,
		*windowBackground;
};

