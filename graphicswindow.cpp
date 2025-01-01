#include "graphicswindow.h"
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include "batimentgraphicsitem.h"
#include <QMessageBox>
GraphicsWindow::GraphicsWindow(QGraphicsScene *scene, QWidget *parent)
    : QWidget(parent), scene(scene) {

    // Set up the QGraphicsView to display the scene
    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setRenderHint(QPainter::SmoothPixmapTransform);

    // Set the size of the view if needed
    view->setFixedSize(800, 600);

    // Add the scene items
    setupScene();  // Ensure setupScene is called here
}

GraphicsWindow::~GraphicsWindow() {
    delete view;
    delete scene;
}

void GraphicsWindow::setupScene() {
    // Example of adding a building (a rectangle) to the scene
    QGraphicsRectItem* rectItem = new QGraphicsRectItem(0, 0, 100, 100);  // Create a rectangle
    rectItem->setBrush(Qt::lightGray);  // Set its color
    scene->addItem(rectItem);  // Add it to the scene
}

void GraphicsWindow::createCityLayout(int rows, int cols) {
    // Get the dimensions of the current view
    int viewWidth = this->width();
    int viewHeight = this->height();

    // Calculate the size of blocks and streets dynamically
    int totalBlocks = rows * cols;
    int streetWidth = 5; // Keep streets proportionally small
    int blockSize = qMin((viewWidth - (cols + 1) * streetWidth) / cols,
                         (viewHeight - (rows + 1) * streetWidth) / rows);

    // Clear the scene if it already contains items
    scene->clear();
    availableSpots.clear();

    // Create the city grid
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int x = col * (blockSize + streetWidth) + streetWidth; // X position with street margin
            int y = row * (blockSize + streetWidth) + streetWidth; // Y position with street margin

            // Create the gray "street" background
            QRectF streetRect(x - streetWidth / 2, y - streetWidth / 2, blockSize + streetWidth, blockSize + streetWidth);
            QGraphicsRectItem *streetBackground = new QGraphicsRectItem(streetRect);
            streetBackground->setBrush(Qt::gray); // Set it to gray
            scene->addItem(streetBackground);

            // Create the green building block
            QRectF buildingRect(x, y, blockSize, blockSize);
            QGraphicsRectItem *building = new QGraphicsRectItem(buildingRect);
            building->setBrush(Qt::green); // Set the building color to green
            scene->addItem(building);

            // Add the building position to the list of available spots
            availableSpots.append(QPointF(x, y));
        }
    }

    // Adjust the scene rectangle to fit everything
    scene->setSceneRect(0, 0, cols * (blockSize + streetWidth), rows * (blockSize + streetWidth));
}



void GraphicsWindow::addBuilding(const QString &name, const QString &type)
{
    if (availableSpots.isEmpty()) {
        QMessageBox::warning(nullptr, "City Full", "No available spots to add a building.");
        return;
    }

    // Get the first available spot
    QPointF position = availableSpots.takeFirst();

    // Define the size of the building
    QRectF rect(position.x(), position.y(), 50, 50);

    // Load the appropriate pixmap
    QPixmap pixmap;
    if (type == "Maison") {
        pixmap.load(":/images/images/house.png");
    } else if (type == "Usine") {
        pixmap.load(":/images/images/usine.png"); // Replace with the actual path to your factory image
    } else if (type == "Parc") {
        pixmap.load(":/images/images/park.png");   // Replace with the actual path to your park image
    } else {
        qWarning() << "Unknown building type:" << type;
        return; // Exit if the type is not recognized
    }


    // Scale the pixmap and create the item
    pixmap = pixmap.scaled(50, 50, Qt::KeepAspectRatio);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
    item->setPos(position);
    scene->addItem(item);

    // Add the name label below the building
    QGraphicsTextItem *textItem = new QGraphicsTextItem(name);
    textItem->setFont(QFont("Arial", 8));
    textItem->setDefaultTextColor(Qt::black);
    textItem->setPos(position.x(), position.y() + 40); // Position below the building
    scene->addItem(textItem);
}

