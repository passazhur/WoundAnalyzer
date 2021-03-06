#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QPolygonF>
#include <opencv2/opencv.hpp>

#include "Utilities/Logger/logger.h"


/// Manages image
/// \todo move it all to ImageInterface
class ImageManager : public QObject
{
    Q_OBJECT

    public : bool isImageOpened = false;

    private: cv::Mat _myImage;
    public : const cv::Mat & getImage() const {return _myImage;}
    private: cv::Mat _myFilteredImage;
    private: cv::Mat _myDrawingLayer;

    public : double drawingLayerTransparency = 0.5;

    public : double zoomFactor = 1.0;
    public : double rulerFactor = 1.0;
    public : double rulerLength = 0;

    public : double filterFactorA = 1.0;
    public : double filterFactorB = 1.0;
    public : double filterFactorC = 1.0;
    public : double filterFactorD = 1.0;
    public : double filterFactorE = 1.0;
    public : double filterIterations = 0;

    public : void cleanDrawingLayer();

    public : void highlightCircle(
            const QPointF &p,
            const QColor &col,
            int radius); // note that node has radius thickness + 4

    public : void highlightLine(
            const QPointF &a,
            const QPointF &b,
            const QColor &col,
            int thickness); // note that line has thickness thickness + 2

    public : double drawPolygon( // returns the area of polygon
            const QPolygonF &polygon,
            const QColor &pec,
            const QColor &pc,
            const QColor &pt,
            int thickness,
            bool drawText = true); // note that node has radius thickness + 2

    public : double drawRuler( // returns the length of the ruler
            const QPolygonF &ruler,
            const QColor &rec,
            const QColor &rc,
            const QColor &rt,
            int thickness,
            bool drawText = true); // note that node has radius thickness + 2

    public : void applyFiltration();

    public : void floodFill(QPoint p);

    private: cv::Mat _blendLayers() const;

    public : const QPixmap getImageAsQPixmap() const;
    public : const QImage getImageAsQImage() const;

    private: void _onLoadImageCleanup();
    public : void openImage(const cv::Mat &image);
    public : void openImage(const QString &fileName);
    public : void saveImage(const QString &fileName) const;

    public : static QImage Mat2QImage(const cv::Mat &src);

    private: ImageManager(QObject *parent = nullptr);
    private: ~ImageManager();

    public : static ImageManager *instance();
};

#endif // IMAGEMANAGER_H
