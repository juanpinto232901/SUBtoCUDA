#include <QtGui>
//#include <QtOpenGL>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "safeMain.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    safeMain = new SafeMain;

    QGridLayout *centralLayout = new QGridLayout;
    centralLayout->addWidget(safeMain, 0, 0);
    centralWidget->setLayout(centralLayout);


    setWindowTitle(tr("SUB_CUDA"));
    resize(1024, 768);
	setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
void MainWindow::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
	updateGL();

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();
	dx *= 0.25; dy *= 0.25;
	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot + dy);// +8 * dy);
		setYRotation(yRot + dx);// +8 * dx);
	}
	else if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot + dy);// +8 * dy);
		setZRotation(zRot + dx);// +8 * dx);
	}
	lastPos = event->pos();
	updateGL();
}


void MainWindow::wheelEvent(QWheelEvent* ptEvent)
{
	QMutex doStopMutex;
	doStopMutex.lock();
	setFocus();
	int iNumDegrees = ptEvent->delta() / 8;
	int iDelta = (float)(iNumDegrees / 15);
	if (iDelta > 0)
	{
		incZoom();
	}
	else
	{
		decZoom();
	}
	doStopMutex.unlock();
	updateGL();

}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
	int iMod = e->modifiers();

	qDebug("ddddddddddddddddddddddddddddddddddddddddddddd");
	if (e->key() == Qt::Key_Escape) {
		close();
	}
	if (e->key() == Qt::Key_Space) {
	}
	if (iMod == Qt::NoModifier) {
		if (e->key() == Qt::Key_C) {
			if (bSeeColor)bSeeColor = false;
			else bSeeColor = true;
			update();
		}

		if (e->key() == Qt::Key_0) {
			glClearColor(1.0, 0.5, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			int iPosBlock = 1;
			iNumBlocks = 1;
			filePos = 0;
			QVector3D* posns = ViewerVertexBuffer1->getPosns(filePos);
			QVector3Du* colors = ViewerVertexBuffer1->getColors(filePos);

			// clear the Vertex Buffer
			ViewerVertexBuffer1->clearVertexBufferMem(m_iNumVertices, iNumBlocks);
			ViewerVertexBuffer1->writeVertexBuffer(posns, m_iNumVertices, iPosBlock, false);

			// Clear the Color Buffer
			ViewerVertexBuffer1->clearColorBufferMem(m_iNumVertices, iNumBlocks);
			ViewerVertexBuffer1->writeColorBuffer(colors, m_iNumVertices, iPosBlock, false);

			iAvatar = 0;
		}
		if (e->key() == Qt::Key_1) {
			glClearColor(1.0, 0.5, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			int iPosBlock = 1;
			iNumBlocks = 1;
			filePos = 0;
			QVector3D* posns = ViewerVertexBuffer1->getPosns(filePos);
			QVector3Du* colors = ViewerVertexBuffer1->getColors(filePos);

			// clear the Vertex Buffer
			ViewerVertexBuffer1->clearVertexBufferMem(m_iNumVertices, iNumBlocks);
			ViewerVertexBuffer1->writeVertexBuffer(posns, m_iNumVertices, iPosBlock, false);

			// Clear the Color Buffer
			ViewerVertexBuffer1->clearColorBufferMem(m_iNumVertices, iNumBlocks);
			ViewerVertexBuffer1->writeColorBuffer(colors, m_iNumVertices, iPosBlock, false);

			iAvatar = 1;
		}
		if (e->key() == Qt::Key_2) {
			glClearColor(1.0, 0.5, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			int iPosBlock = 1;
			iNumBlocks = 1;
			filePos = 0;
			QVector3D* posns = ViewerVertexBuffer1->getPosns(filePos);
			QVector3Du* colors = ViewerVertexBuffer1->getColors(filePos);

			// clear the Vertex Buffer
			ViewerVertexBuffer1->clearVertexBufferMem(m_iNumVertices, iNumBlocks);
			ViewerVertexBuffer1->writeVertexBuffer(posns, m_iNumVertices, iPosBlock, false);

			// Clear the Color Buffer
			ViewerVertexBuffer1->clearColorBufferMem(m_iNumVertices, iNumBlocks);
			ViewerVertexBuffer1->writeColorBuffer(colors, m_iNumVertices, iPosBlock, false);

			iAvatar = 2;
		}
		if (e->key() == Qt::Key_3) {
			glClearColor(1.0, 0.5, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			int iPosBlock = 1;
			iNumBlocks = 1;
			filePos = 0;
			QVector3D* posns = ViewerVertexBuffer1->getPosns(filePos);
			QVector3Du* colors = ViewerVertexBuffer1->getColors(filePos);

			// clear the Vertex Buffer
			ViewerVertexBuffer1->clearVertexBufferMem(m_iNumVertices, iNumBlocks);
			ViewerVertexBuffer1->writeVertexBuffer(posns, m_iNumVertices, iPosBlock, false);

			// Clear the Color Buffer
			ViewerVertexBuffer1->clearColorBufferMem(m_iNumVertices, iNumBlocks);
			ViewerVertexBuffer1->writeColorBuffer(colors, m_iNumVertices, iPosBlock, false);

			iAvatar = 3;
		}
		if (e->key() == Qt::Key_4) {
			glClearColor(1.0, 0.5, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			int iPosBlock = 1;
			iNumBlocks = 1;
			filePos = 0;
			QVector3D* posns = ViewerVertexBuffer1->getPosns(filePos);
			QVector3Du* colors = ViewerVertexBuffer1->getColors(filePos);

			// clear the Vertex Buffer
			ViewerVertexBuffer1->clearVertexBufferMem(m_iNumVertices, iNumBlocks);
			ViewerVertexBuffer1->writeVertexBuffer(posns, m_iNumVertices, iPosBlock, false);

			// Clear the Color Buffer
			ViewerVertexBuffer1->clearColorBufferMem(m_iNumVertices, iNumBlocks);
			ViewerVertexBuffer1->writeColorBuffer(colors, m_iNumVertices, iPosBlock, false);

			iAvatar = 4;
		}
	}
	if (iMod == Qt::ControlModifier) {
		if (e->key() == Qt::Key_1) {
			xRot = 225.0;
			yRot = 0.0;
			zRot = 30.0;
			update();
		}
		if (e->key() == Qt::Key_2) {
			xRot = 270.0;
			yRot = 0.0;
			zRot = 0.0;
			update();
		}
		if (e->key() == Qt::Key_3) {
			xRot = 315.0;
			yRot = 0.0;
			zRot = 30.0;
			update();
		}
		if (e->key() == Qt::Key_4) {
			xRot = 180.0;
			yRot = 0.0;
			zRot = 0.0;
			update();
		}
		if (e->key() == Qt::Key_5) {
			xRot = 0.0;
			yRot = 90.0;
			zRot = 0.0;
			update();
		}
		if (e->key() == Qt::Key_6) {
			xRot = 0;
			yRot = 0.0;
			zRot = 0.0;
			update();
		}
		if (e->key() == Qt::Key_7) {
			xRot = 135.0;
			yRot = 0.0;
			zRot = 30.0;
			update();
		}
		if (e->key() == Qt::Key_8) {
			xRot = 270.0;
			yRot = 0.0;
			zRot = 0.0;
			update();
		}
		if (e->key() == Qt::Key_9) {
			xRot = 45.0;
			yRot = 0.0;
			zRot = 30.0;
			update();
		}
	}

	QWidget::keyPressEvent(e);
}
//*/
