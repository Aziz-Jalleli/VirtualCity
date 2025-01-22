#ifndef CITYWINDOW_H
#define CITYWINDOW_H

#include <QWidget>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>  // Include for CylinderMesh
#include <QVector3D>
#include <QVector>
#include <memory>
#include "ville.h"

class CityWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CityWindow(std::shared_ptr<Ville> city, QWidget *parent = nullptr);
    ~CityWindow();

    // Method to create a house in front of the camera
    void createHouseInFrontOfCamera();
    void createParkInFrontOfCamera();
    void createFactoryInFrontOfCamera();

    // Method to find an empty position near a target position
    QVector3D findEmptyPosition(const QVector3D &targetPosition);


private:
    // Method to set up the initial 3D scene
    Qt3DCore::QEntity *createScene();

    Qt3DCore::QEntity *rootEntity;          // Root entity of the 3D scene
    std::shared_ptr<Ville> m_city;          // Shared pointer to the city data model
    Qt3DExtras::Qt3DWindow *view;           // 3D window for rendering
    QWidget *container;                     // Container to embed the 3D view in the main window

    QVector<QVector3D> usedPositions;        // List to track occupied positions
    float groundWidth;
    float groundHeight;
    void createSlide(const QVector3D& parkPosition);
    void createSwingSet(const QVector3D& parkPosition);
    void moveCameraForward();
    void moveCameraBackward();
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void focusOutEvent(QFocusEvent *event)override;
    void focusInEvent (QFocusEvent *event)override;

};

#endif // CITYWINDOW_H
