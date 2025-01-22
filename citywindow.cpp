#include "citywindow.h"
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QOrbitCameraController>
#include <QVBoxLayout>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DRender/QMesh> // Ensure this is correct for your version
#include <QRandomGenerator>
#include <QVector3D>
#include <QColor>
#include <QDebug>
#include <QKeyEvent>

CityWindow::CityWindow(std::shared_ptr<Ville> city, QWidget *parent)
    : QWidget(parent), m_city(city), rootEntity(new Qt3DCore::QEntity())
{

    // Create a 3D window
    view = new Qt3DExtras::Qt3DWindow();
    setFocusPolicy(Qt::StrongFocus);

    // Set up the scene
    Qt3DCore::QEntity *sceneEntity = createScene();

    // Set the root entity in the 3D view
    view->setRootEntity(sceneEntity);

    // Embed the 3D view in a QWidget container
    container = QWidget::createWindowContainer(view, this);
    container->setMinimumSize(800, 600);

    // Set up the layout for the 3D view
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(container);
    setLayout(layout);
}

CityWindow::~CityWindow()
{
    delete view;
}

Qt3DCore::QEntity *CityWindow::createScene()
{
    // Create ground plane
    Qt3DExtras::QPlaneMesh *groundMesh = new Qt3DExtras::QPlaneMesh();
    groundMesh->setWidth(100);
    groundMesh->setHeight(100);

    // Store the ground dimensions in member variables for later use
    groundWidth = groundMesh->width();
    groundHeight = groundMesh->height();

    // Material for the ground
    Qt3DExtras::QPhongMaterial *groundMaterial = new Qt3DExtras::QPhongMaterial();
    groundMaterial->setDiffuse(QColor(Qt::green));

    // Transform for the ground
    Qt3DCore::QTransform *groundTransform = new Qt3DCore::QTransform();

    // Combine ground components
    Qt3DCore::QEntity *groundEntity = new Qt3DCore::QEntity(rootEntity);
    groundEntity->addComponent(groundMesh);
    groundEntity->addComponent(groundMaterial);
    groundEntity->addComponent(groundTransform);

    // Set up the camera
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(75.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 20, 50));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // Add orbit camera controller
    Qt3DExtras::QOrbitCameraController *cameraController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    cameraController->setCamera(camera);
    cameraController->setLinearSpeed(10.0f);
    cameraController->setLookSpeed(150.0f);

    return rootEntity;
}

void CityWindow::moveCameraForward()
{
    // Get the current position of the camera
    Qt3DRender::QCamera *camera = view->camera();
    QVector3D currentPosition = camera->position();

    // Move the camera forward (along the z-axis)
    QVector3D newPosition = currentPosition + QVector3D(0.0f, 0.0f, -1.0f); // Negative value moves it forward
    camera->setPosition(newPosition);
}

void CityWindow::moveCameraBackward()
{
    // Get the current position of the camera
    Qt3DRender::QCamera *camera = view->camera();
    QVector3D currentPosition = camera->position();

    // Move the camera backward (along the z-axis)
    QVector3D newPosition = currentPosition + QVector3D(0.0f, 0.0f, 1.0f); // Positive value moves it backward
    camera->setPosition(newPosition);
}
void CityWindow::keyPressEvent(QKeyEvent *event)
{
    // Check if the pressed key is the Up arrow key (for moving forward)
    if (event->key() == Qt::Key_Z) {
        moveCameraForward();
    }

    // Check if the pressed key is the Down arrow key (for moving backward)
    else if (event->key() == Qt::Key_S) {
        moveCameraBackward();
    }

    // Call the base class implementation if necessary
    QWidget::keyPressEvent(event);
}

void CityWindow::keyReleaseEvent(QKeyEvent *event)
{
    // Handle key release events if needed (e.g., stop movement or reset state)
    QWidget::keyReleaseEvent(event);
}
void CityWindow::focusOutEvent(QFocusEvent *event)
{
    // Handle when the window loses focus, if necessary
    QWidget::focusOutEvent(event);
    qDebug() << "Main window gained focus!";

}
void CityWindow::focusInEvent(QFocusEvent *event)
{
    // Handle when the window gains focus
    QWidget::focusInEvent(event);
    qDebug() << "City window gained focus!";
}


void CityWindow::createHouseInFrontOfCamera()
{
    // Get the camera's position and forward direction
    Qt3DRender::QCamera *camera = view->camera();
    QVector3D cameraPosition = camera->position();
    QVector3D cameraForward = (camera->viewCenter() - cameraPosition).normalized();

    // Place the house a certain distance in front of the camera
    float distance = 10.0f; // Distance from the camera to place the house
    QVector3D targetPosition = cameraPosition + cameraForward * distance;

    // Find the closest unoccupied position near the target position
    QVector3D housePosition = findEmptyPosition(targetPosition);

    // Create the building base (cube)
    Qt3DExtras::QCuboidMesh *buildingMesh = new Qt3DExtras::QCuboidMesh();
    buildingMesh->setXExtent(4.0f);
    buildingMesh->setYExtent(4.0f);
    buildingMesh->setZExtent(4.0f);

    // Material for the building base
    Qt3DExtras::QPhongMaterial *buildingMaterial = new Qt3DExtras::QPhongMaterial();
    buildingMaterial->setDiffuse(QColor(Qt::blue));

    // Transform for the building base
    Qt3DCore::QTransform *buildingTransform = new Qt3DCore::QTransform();
    buildingTransform->setTranslation(housePosition);

    // Combine building components
    Qt3DCore::QEntity *buildingEntity = new Qt3DCore::QEntity(rootEntity);
    buildingEntity->addComponent(buildingMesh);
    buildingEntity->addComponent(buildingMaterial);
    buildingEntity->addComponent(buildingTransform);

    // Create the roof (pyramid)
    Qt3DExtras::QConeMesh *roofMesh = new Qt3DExtras::QConeMesh();
    roofMesh->setTopRadius(0.0f);
    roofMesh->setBottomRadius(3.0f);
    roofMesh->setLength(2.5f);
    roofMesh->setRings(4);
    roofMesh->setSlices(8);

    // Material for the roof
    Qt3DExtras::QPhongMaterial *roofMaterial = new Qt3DExtras::QPhongMaterial();
    roofMaterial->setDiffuse(QColor(Qt::red));

    // Transform for the roof
    Qt3DCore::QTransform *roofTransform = new Qt3DCore::QTransform();
    roofTransform->setTranslation(housePosition + QVector3D(0.0f, 3.5f, 0.0f)); // Positioned above the cube

    // Combine roof components
    Qt3DCore::QEntity *roofEntity = new Qt3DCore::QEntity(rootEntity);
    roofEntity->addComponent(roofMesh);
    roofEntity->addComponent(roofMaterial);
    roofEntity->addComponent(roofTransform);

    // Mark this position as used
    usedPositions.append(housePosition);
}

void CityWindow::createParkInFrontOfCamera()
{
    // Get the camera's position and forward direction
    Qt3DRender::QCamera *camera = view->camera();
    QVector3D cameraPosition = camera->position();
    QVector3D cameraForward = (camera->viewCenter() - cameraPosition).normalized();

    // Place the park a certain distance in front of the camera
    float distance = 10.0f;
    QVector3D targetPosition = cameraPosition + cameraForward * distance;

    // Find the closest unoccupied position near the target
    QVector3D parkPosition = findEmptyPosition(targetPosition);

    // Create the park base (a green area, a flat cuboid) as a playground ground
    Qt3DExtras::QCuboidMesh *parkMesh = new Qt3DExtras::QCuboidMesh();
    parkMesh->setXExtent(20.0f); // Increase the size for a playground feel
    parkMesh->setYExtent(0.1f);  // Keep it flat
    parkMesh->setZExtent(15.0f);

    // Material for the park base (grass-like green color)
    Qt3DExtras::QPhongMaterial *parkMaterial = new Qt3DExtras::QPhongMaterial();
    parkMaterial->setDiffuse(QColor(144, 238, 144));

    // Transform for the park base
    Qt3DCore::QTransform *parkTransform = new Qt3DCore::QTransform();
    parkTransform->setTranslation(parkPosition);

    // Combine park components
    Qt3DCore::QEntity *parkEntity = new Qt3DCore::QEntity(rootEntity);
    parkEntity->addComponent(parkMesh);
    parkEntity->addComponent(parkMaterial);
    parkEntity->addComponent(parkTransform);

    // Add trees around the playground to make it more natural
    for (int i = 0; i < 2; ++i) { // Generate multiple trees around the park
        // Generate random positions within the park area
        QVector3D treePosition = parkPosition + QVector3D(
                                     (rand() % 15) - 7, // X random value between -7 and 7
                                     0.0f,              // No vertical movement for the tree position
                                     (rand() % 10) - 5   // Z random value between -5 and 5
                                     );

        // Tree trunk (cylinder) and foliage (cone)
        Qt3DExtras::QCylinderMesh *treeTrunkMesh = new Qt3DExtras::QCylinderMesh();
        treeTrunkMesh->setRadius(0.4f);  // Adjusted trunk radius
        treeTrunkMesh->setLength(3.0f);  // Adjusted trunk length

        Qt3DExtras::QConeMesh *treeFoliageMesh = new Qt3DExtras::QConeMesh();
        treeFoliageMesh->setTopRadius(0.0f);
        treeFoliageMesh->setBottomRadius(3.0f);
        treeFoliageMesh->setLength(4.0f);

        // Material for the tree trunk and foliage
        Qt3DExtras::QPhongMaterial *treeMaterial = new Qt3DExtras::QPhongMaterial();
        treeMaterial->setDiffuse(QColor(139, 69, 19));  // Brown color for trunk

        Qt3DExtras::QPhongMaterial *foliageMaterial = new Qt3DExtras::QPhongMaterial();
        foliageMaterial->setDiffuse(QColor(Qt::green));  // Dark green color for foliage

        // Transform for the tree trunk and foliage
        Qt3DCore::QTransform *treeTransform = new Qt3DCore::QTransform();
        treeTransform->setTranslation(treePosition + QVector3D(0.0f, 1.5f, 0.0f)); // Position tree trunk

        // Combine tree components (trunk and foliage)
        Qt3DCore::QEntity *treeTrunkEntity = new Qt3DCore::QEntity(rootEntity);
        treeTrunkEntity->addComponent(treeTrunkMesh);
        treeTrunkEntity->addComponent(treeMaterial);
        treeTrunkEntity->addComponent(treeTransform);

        Qt3DCore::QEntity *treeFoliageEntity = new Qt3DCore::QEntity(rootEntity);
        treeFoliageEntity->addComponent(treeFoliageMesh);
        treeFoliageEntity->addComponent(foliageMaterial);
        treeFoliageEntity->addComponent(treeTransform);
    }

    // Add playground equipment (like a slide and swings)
    createSlide(parkPosition);
    createSwingSet(parkPosition);

    // Mark the park position as used
    usedPositions.append(parkPosition);
}

void CityWindow::createSlide(const QVector3D& parkPosition)
{
    // Create a simple slide (a combination of a ramp and a slide part)
    Qt3DExtras::QCuboidMesh *slideRampMesh = new Qt3DExtras::QCuboidMesh();
    slideRampMesh->setXExtent(4.0f);
    slideRampMesh->setYExtent(0.2f);
    slideRampMesh->setZExtent(1.0f);

    Qt3DExtras::QCuboidMesh *slideBaseMesh = new Qt3DExtras::QCuboidMesh();
    slideBaseMesh->setXExtent(2.0f);
    slideBaseMesh->setYExtent(0.5f);
    slideBaseMesh->setZExtent(3.0f);

    // Materials for the slide (colorful)
    Qt3DExtras::QPhongMaterial *slideMaterial = new Qt3DExtras::QPhongMaterial();
    slideMaterial->setDiffuse(QColor(255, 0, 0));  // Red color for the slide

    Qt3DCore::QTransform *slideTransform = new Qt3DCore::QTransform();
    slideTransform->setTranslation(parkPosition + QVector3D(3.0f, 1.0f, 0.0f)); // Position the slide

    // Combine slide components
    Qt3DCore::QEntity *slideRampEntity = new Qt3DCore::QEntity(rootEntity);
    slideRampEntity->addComponent(slideRampMesh);
    slideRampEntity->addComponent(slideMaterial);
    slideRampEntity->addComponent(slideTransform);

    Qt3DCore::QEntity *slideBaseEntity = new Qt3DCore::QEntity(rootEntity);
    slideBaseEntity->addComponent(slideBaseMesh);
    slideBaseEntity->addComponent(slideMaterial);
    slideBaseEntity->addComponent(slideTransform);
}

void CityWindow::createSwingSet(const QVector3D& parkPosition)
{
    // Create swing set (a combination of ropes and seat)
    Qt3DExtras::QCylinderMesh *swingSeatMesh = new Qt3DExtras::QCylinderMesh();
    swingSeatMesh->setRadius(0.5f);
    swingSeatMesh->setLength(0.2f);

    Qt3DExtras::QCylinderMesh *swingRopeMesh = new Qt3DExtras::QCylinderMesh();
    swingRopeMesh->setRadius(0.1f);
    swingRopeMesh->setLength(6.0f);

    // Materials for the swing set
    Qt3DExtras::QPhongMaterial *seatMaterial = new Qt3DExtras::QPhongMaterial();
    seatMaterial->setDiffuse(QColor(139, 69, 19));  // Brown color for the seat

    Qt3DExtras::QPhongMaterial *ropeMaterial = new Qt3DExtras::QPhongMaterial();
    ropeMaterial->setDiffuse(QColor(Qt::black));  // Black color for the ropes

    // Swing seat
    Qt3DCore::QTransform *seatTransform = new Qt3DCore::QTransform();
    seatTransform->setTranslation(parkPosition + QVector3D(-4.0f, 2.5f, 0.0f)); // Position the seat

    Qt3DCore::QEntity *seatEntity = new Qt3DCore::QEntity(rootEntity);
    seatEntity->addComponent(swingSeatMesh);
    seatEntity->addComponent(seatMaterial);
    seatEntity->addComponent(seatTransform);

    // Swing rope
    Qt3DCore::QTransform *ropeTransform = new Qt3DCore::QTransform();
    ropeTransform->setTranslation(parkPosition + QVector3D(-4.0f, 5.0f, 0.0f)); // Position the rope

    Qt3DCore::QEntity *ropeEntity = new Qt3DCore::QEntity(rootEntity);
    ropeEntity->addComponent(swingRopeMesh);
    ropeEntity->addComponent(ropeMaterial);
    ropeEntity->addComponent(ropeTransform);
}



void CityWindow::createFactoryInFrontOfCamera()
{
    // Get the camera's position and forward direction
    Qt3DRender::QCamera *camera = view->camera();
    QVector3D cameraPosition = camera->position();
    QVector3D cameraForward = (camera->viewCenter() - cameraPosition).normalized();

    // Place the factory a certain distance in front of the camera
    float distance = 10.0f;
    QVector3D targetPosition = cameraPosition + cameraForward * distance;

    // Find the closest unoccupied position near the target
    QVector3D factoryPosition = findEmptyPosition(targetPosition);

    // Create the factory base (rectangular building)
    Qt3DExtras::QCuboidMesh *factoryMesh = new Qt3DExtras::QCuboidMesh();
    factoryMesh->setXExtent(8.0f);
    factoryMesh->setYExtent(5.0f);
    factoryMesh->setZExtent(6.0f);

    // Material for the factory base
    Qt3DExtras::QPhongMaterial *factoryMaterial = new Qt3DExtras::QPhongMaterial();
    factoryMaterial->setDiffuse(QColor(Qt::gray));

    // Transform for the factory base
    Qt3DCore::QTransform *factoryTransform = new Qt3DCore::QTransform();
    factoryTransform->setTranslation(factoryPosition);

    // Combine factory components
    Qt3DCore::QEntity *factoryEntity = new Qt3DCore::QEntity(rootEntity);
    factoryEntity->addComponent(factoryMesh);
    factoryEntity->addComponent(factoryMaterial);
    factoryEntity->addComponent(factoryTransform);

    // Create the chimney (a small cylinder)
    Qt3DExtras::QCylinderMesh *chimneyMesh = new Qt3DExtras::QCylinderMesh();
    chimneyMesh->setRadius(0.5f);
    chimneyMesh->setLength(4.0f);

    // Material for the chimney
    Qt3DExtras::QPhongMaterial *chimneyMaterial = new Qt3DExtras::QPhongMaterial();
    chimneyMaterial->setDiffuse(QColor(Qt::darkGray));

    // Transform for the chimney
    Qt3DCore::QTransform *chimneyTransform = new Qt3DCore::QTransform();
    chimneyTransform->setTranslation(factoryPosition + QVector3D(0.0f, 3.0f, 2.5f)); // Positioned on top of the factory

    // Combine chimney components
    Qt3DCore::QEntity *chimneyEntity = new Qt3DCore::QEntity(rootEntity);
    chimneyEntity->addComponent(chimneyMesh);
    chimneyEntity->addComponent(chimneyMaterial);
    chimneyEntity->addComponent(chimneyTransform);

    // Mark this position as used
    usedPositions.append(factoryPosition);
}


QVector3D CityWindow::findEmptyPosition(const QVector3D &targetPosition)
{
    // Set the minimum distance between houses
    float minDistance = 15.0f;
    QVector3D potentialPosition = targetPosition;

    // Ensure the house stays within the ground bounds (using the stored ground dimensions)
    potentialPosition.setX(qBound(-groundWidth / 2, potentialPosition.x(), groundWidth / 2));  // Limit x to ground width
    potentialPosition.setZ(qBound(-groundHeight / 2, potentialPosition.z(), groundHeight / 2)); // Limit z to ground height

    // Adjust Y-coordinate to ensure the house is on the ground (y = 0)
    potentialPosition.setY(0.0f);

    // Check for collisions or proximity with existing houses
    while (true) {
        bool isPositionOccupied = false;

        for (const QVector3D &occupiedPos : usedPositions) {
            // Check if the distance from any occupied position is too close
            if ((occupiedPos - potentialPosition).length() < minDistance) {
                isPositionOccupied = true;
                break;
            }
        }

        if (!isPositionOccupied) {
            // Found an empty position on the ground
            break;
        } else {
            // Try moving the position slightly
            potentialPosition += QVector3D(minDistance, 0.0f, 0.0f); // Offset position
            // Ensure the house stays within the ground bounds after offset
            potentialPosition.setX(qBound(-groundWidth / 2, potentialPosition.x(), groundWidth / 2));  // Limit x to ground width
            potentialPosition.setZ(qBound(-groundHeight / 2, potentialPosition.z(), groundHeight / 2)); // Limit z to ground height
        }
    }

    return potentialPosition;
}
