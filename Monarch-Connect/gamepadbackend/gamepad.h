/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Gamepad module
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef QGAMEPAD_H
#define QGAMEPAD_H

#include <QtCore/QObject>
//#include <QtGamepad/qtgamepadglobal.h>
//#include <QtGamepad/QGamepadManager>
#include "gamepadmanager.h"
#include <QString>


//QT_BEGIN_NAMESPACE

//class QGamepadPrivate;

class QGamepad : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int deviceId READ getDeviceId WRITE setDeviceId NOTIFY deviceIdChanged)
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)
    //Q_PROPERTY(QString name READ name NOTIFY nameChanged) ///TODO: fix this
    Q_PROPERTY(double axisLeftX READ getAxisLeftX NOTIFY axisLeftXChanged)
    Q_PROPERTY(double axisLeftY READ getAxisLeftY NOTIFY axisLeftYChanged)
    Q_PROPERTY(double axisRightX READ getAxisRightX NOTIFY axisRightXChanged)
    Q_PROPERTY(double axisRightY READ getAxisRightY NOTIFY axisRightYChanged)
    Q_PROPERTY(bool buttonA READ getButtonA NOTIFY buttonAChanged)
    Q_PROPERTY(bool buttonB READ getButtonB NOTIFY buttonBChanged)
    Q_PROPERTY(bool buttonX READ getButtonX NOTIFY buttonXChanged)
    Q_PROPERTY(bool buttonY READ getButtonY NOTIFY buttonYChanged)
    Q_PROPERTY(bool buttonL1 READ getButtonL1 NOTIFY buttonL1Changed)
    Q_PROPERTY(bool buttonR1 READ getButtonR1 NOTIFY buttonR1Changed)
    Q_PROPERTY(double buttonL2 READ getButtonL2 NOTIFY buttonL2Changed)
    Q_PROPERTY(double buttonR2 READ getButtonR2 NOTIFY buttonR2Changed)
    Q_PROPERTY(bool buttonSelect READ getButtonSelect NOTIFY buttonSelectChanged)
    Q_PROPERTY(bool buttonStart READ getButtonStart NOTIFY buttonStartChanged)
    Q_PROPERTY(bool buttonL3 READ getButtonL3 NOTIFY buttonL3Changed)
    Q_PROPERTY(bool buttonR3 READ getButtonR3 NOTIFY buttonR3Changed)
    Q_PROPERTY(bool buttonUp READ getButtonUp NOTIFY buttonUpChanged)
    Q_PROPERTY(bool buttonDown READ getButtonDown NOTIFY buttonDownChanged)
    Q_PROPERTY(bool buttonLeft READ getButtonLeft NOTIFY buttonLeftChanged)
    Q_PROPERTY(bool buttonRight READ getButtonRight NOTIFY buttonRightChanged)
    Q_PROPERTY(bool buttonCenter READ getButtonCenter NOTIFY buttonCenterChanged)
    Q_PROPERTY(bool buttonGuide READ getButtonGuide NOTIFY buttonGuideChanged)

public:
    explicit QGamepad(int deviceId = 0, QObject *parent = nullptr, QGamepadManager *manager = nullptr);
    ~QGamepad();
    //virtual ~QGamepad();
    QGamepadManager *gamepadManager;

    int getDeviceId() const;

    bool isConnected() const;

    QString getName() const;

    double getAxisLeftX() const;
    double getAxisLeftY() const;
    double getAxisRightX() const;
    double getAxisRightY() const;
    bool getButtonA() const;
    bool getButtonB() const;
    bool getButtonX() const;
    bool getButtonY() const;
    bool getButtonL1() const;
    bool getButtonR1() const;
    double getButtonL2() const;
    double getButtonR2() const;
    bool getButtonSelect() const;
    bool getButtonStart() const;
    bool getButtonL3() const;
    bool getButtonR3() const;
    bool getButtonUp() const;
    bool getButtonDown() const;
    bool getButtonLeft() const;
    bool getButtonRight() const;
    bool getButtonCenter() const;
    bool getButtonGuide() const;

Q_SIGNALS:

    void deviceIdChanged(int value);
    void connectedChanged(bool value);
    void nameChanged(QString value);
    void axisLeftXChanged(double value);
    void axisLeftYChanged(double value);
    void axisRightXChanged(double value);
    void axisRightYChanged(double value);
    void buttonAChanged(bool value);
    void buttonBChanged(bool value);
    void buttonXChanged(bool value);
    void buttonYChanged(bool value);
    void buttonL1Changed(bool value);
    void buttonR1Changed(bool value);
    void buttonL2Changed(double value);
    void buttonR2Changed(double value);
    void buttonSelectChanged(bool value);
    void buttonStartChanged(bool value);
    void buttonL3Changed(bool value);
    void buttonR3Changed(bool value);
    void buttonUpChanged(bool value);
    void buttonDownChanged(bool value);
    void buttonLeftChanged(bool value);
    void buttonRightChanged(bool value);
    void buttonCenterChanged(bool value);
    void buttonGuideChanged(bool value);

public Q_SLOTS:

    void setDeviceId(int number);

private:
    //Q_DECLARE_PRIVATE(QGamepad)
    void setConnected(bool isConnected);
    void setName(const QString &name);

    int deviceId;
    bool connected;
    QString name;
    double axisLeftX;
    double axisLeftY;
    double axisRightX;
    double axisRightY;
    bool buttonA;
    bool buttonB;
    bool buttonX;
    bool buttonY;
    bool buttonL1;
    bool buttonR1;
    double buttonL2;
    double buttonR2;
    bool buttonSelect;
    bool buttonStart;
    bool buttonL3;
    bool buttonR3;
    bool buttonUp;
    bool buttonDown;
    bool buttonLeft;
    bool buttonRight;
    bool buttonCenter;
    bool buttonGuide;

private slots:
    //Q_DISABLE_COPY(QGamepad)

    void _q_handleGamepadConnected(int);
    void _q_handleGamepadNameChanged(int, const QString &);
    void _q_handleGamepadDisconnected(int);
    void _q_handleGamepadAxisEvent(int, QGamepadBackend::GamepadAxis, double);
    void _q_handleGamepadButtonPressEvent(int, QGamepadBackend::GamepadButton, double);
    void _q_handleGamepadButtonReleaseEvent(int, QGamepadBackend::GamepadButton);

};

//QT_END_NAMESPACE

//Q_DECLARE_METATYPE(QGamepad*)

#endif
