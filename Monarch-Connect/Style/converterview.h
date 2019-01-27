#ifndef CONVERTERVIEW_H
#define CONVERTERVIEW_H

#include <QWidget>

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QFormLayout>

class ConverterView : public QWidget
{
    Q_OBJECT
private:
    QPushButton *_power;
    QLineEdit *_data;
    QLineEdit *_status;

public:
    QLineEdit *_minAmplitude;
    QLineEdit *_maxAmplitude;
    QLineEdit *_minRoll;
    QLineEdit *_maxRoll;
    QLineEdit *_minDihedral;
    QLineEdit *_maxDihedral;
    QLineEdit *_minAngV;
    QLineEdit *_maxAngV;
    QLineEdit *_glideThresh;
public:
    explicit ConverterView(QWidget *parent = nullptr);
signals:
    void pressed();

public slots:
    void setData(QString data);
    void setStatus(QString data);
};

#endif // CONVERTERVIEW_H
