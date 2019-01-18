#ifndef XYVIS_H
#define XYVIS_H

#include <QWidget>
#include <QPainter>

class XYvis : public QWidget
{
    Q_OBJECT
public:
    explicit XYvis(QWidget *parent = nullptr);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

public slots:
    void setCoords(float x, float y);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    float x;
    float y;

signals:

public slots:
};

#endif // XYVIS_H
