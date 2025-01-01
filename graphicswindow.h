#ifndef GRAPHICSWINDOW_H
#define GRAPHICSWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

class GraphicsWindow : public QWidget
{
    Q_OBJECT

public:
    GraphicsWindow(QGraphicsScene *scene, QWidget *parent = nullptr);

    void addBuilding(const QString&, const QString&);
    void createCityLayout(int, int);

    ~GraphicsWindow();

    void setupScene();

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    QVector<QPointF> availableSpots;
};

#endif // GRAPHICSWINDOW_H
