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


#include "gamepadbackend/gamepad.h"

#include <qobject.h>

QT_BEGIN_NAMESPACE
#if(0)
class QGamepadPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QGamepad)

public:
    QGamepadPrivate(int deviceId)
        : deviceId(deviceId)
        , connected(false)
        , axisLeftX(0.0)
        , axisLeftY(0.0)
        , axisRightX(0.0)
        , axisRightY(0.0)
        , buttonA(false)
        , buttonB(false)
        , buttonX(false)
        , buttonY(false)
        , buttonL1(false)
        , buttonR1(false)
        , buttonL2(0.0)
        , buttonR2(0.0)
        , buttonSelect(false)
        , buttonStart(false)
        , buttonL3(false)
        , buttonR3(false)
        , buttonUp(false)
        , buttonDown(false)
        , buttonLeft(false)
        , buttonRight(false)
        , buttonCenter(false)
        , buttonGuide(false)
    {
    }

    QGamepadManager *gamepadManager;

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

    void setConnected(bool isConnected);
    void setName(const QString &name);

    void _q_handleGamepadConnected(int id);
    void _q_handleGamepadNameChanged(int id, const QString &name);
    void _q_handleGamepadDisconnected(int id);
    void _q_handleGamepadAxisEvent(int id, QGamepadBackend::GamepadAxis axis, double value);
    void _q_handleGamepadButtonPressEvent(int id, QGamepadBackend::GamepadButton button, double value);
    void _q_handleGamepadButtonReleaseEvent(int id, QGamepadBackend::GamepadButton button);
};

void QGamepadPrivate::setConnected(bool isConnected)
{
    Q_Q(QGamepad);
    if (connected != isConnected) {
        connected = isConnected;
        emit q->connectedChanged(connected);
    }
}

void QGamepadPrivate::setName(const QString &theName)
{
    Q_Q(QGamepad);
    if (name != theName) {
        name = theName;
        emit q->nameChanged(name);
    }
}

/*!
 * \internal
 */\
void QGamepadPrivate::_q_handleGamepadConnected(int id)
{
    if (id == deviceId) {
        setConnected(true);
    }
}

/*!
 * \internal
 */\
void QGamepadPrivate::_q_handleGamepadNameChanged(int id, const QString &name)
{
    if (id == deviceId)
        setName(name);
}

/*!
 * \internal
 */\
void QGamepadPrivate::_q_handleGamepadDisconnected(int id)
{
    if (id == deviceId) {
        setConnected(false);
    }
}

/*!
 * \internal
 */\
void QGamepadPrivate::_q_handleGamepadAxisEvent(int id, QGamepadBackend::GamepadAxis axis, double value)
{
    Q_Q(QGamepad);
    if (id != deviceId)
        return;

    switch (axis) {
    case QGamepadBackend::AxisLeftX:
        axisLeftX = value;
        emit q->axisLeftXChanged(value);
        break;
    case QGamepadBackend::AxisLeftY:
        axisLeftY = value;
        emit q->axisLeftYChanged(value);
        break;
    case QGamepadBackend::AxisRightX:
        axisRightX = value;
        emit q->axisRightXChanged(value);
        break;
    case QGamepadBackend::AxisRightY:
        axisRightY = value;
        emit q->axisRightYChanged(value);
        break;
    default:
        break;
    }
}

/*!
 * \internal
 */\
void QGamepadPrivate::_q_handleGamepadButtonPressEvent(int id, QGamepadBackend::GamepadButton button, double value)
{
    Q_Q(QGamepad);
    if (id != deviceId)
        return;

    switch (button) {
    case QGamepadBackend::ButtonA:
        buttonA = true;
        emit q->buttonAChanged(true);
        break;
    case QGamepadBackend::ButtonB:
        buttonB = true;
        emit q->buttonBChanged(true);
        break;
    case QGamepadBackend::ButtonX:
        buttonX = true;
        emit q->buttonXChanged(true);
        break;
    case QGamepadBackend::ButtonY:
        buttonY = true;
        emit q->buttonYChanged(true);
        break;
    case QGamepadBackend::ButtonL1:
        buttonL1 = true;
        emit q->buttonL1Changed(true);
        break;
    case QGamepadBackend::ButtonR1:
        buttonR1 = true;
        emit q->buttonR1Changed(true);
        break;
    case QGamepadBackend::ButtonL2:
        buttonL2 = value;
        emit q->buttonL2Changed(value);
        break;
    case QGamepadBackend::ButtonR2:
        buttonR2 = value;
        emit q->buttonR2Changed(value);
        break;
    case QGamepadBackend::ButtonL3:
        buttonL3 = true;
        emit q->buttonL3Changed(true);
        break;
    case QGamepadBackend::ButtonR3:
        buttonR3 = true;
        emit q->buttonR3Changed(true);
        break;
    case QGamepadBackend::ButtonSelect:
        buttonSelect = true;
        emit q->buttonSelectChanged(true);
        break;
    case QGamepadBackend::ButtonStart:
        buttonStart = true;
        emit q->buttonStartChanged(true);
        break;
    case QGamepadBackend::ButtonUp:
        buttonUp = true;
        emit q->buttonUpChanged(true);
        break;
    case QGamepadBackend::ButtonDown:
        buttonDown = true;
        emit q->buttonDownChanged(true);
        break;
    case QGamepadBackend::ButtonLeft:
        buttonLeft = true;
        emit q->buttonLeftChanged(true);
        break;
    case QGamepadBackend::ButtonRight:
        buttonRight = true;
        emit q->buttonRightChanged(true);
        break;
    case QGamepadBackend::ButtonCenter:
        buttonCenter = true;
        emit q->buttonCenterChanged(true);
        break;
    case QGamepadBackend::ButtonGuide:
        buttonGuide = true;
        emit q->buttonGuideChanged(true);
        break;
    default:
        break;
    }

}

/*!
 * \internal
 */\
void QGamepadPrivate::_q_handleGamepadButtonReleaseEvent(int id, QGamepadBackend::GamepadButton button)
{
    Q_Q(QGamepad);
    if (id != deviceId)
        return;

    switch (button) {
    case QGamepadBackend::ButtonA:
        buttonA = false;
        emit q->buttonAChanged(false);
        break;
    case QGamepadBackend::ButtonB:
        buttonB = false;
        emit q->buttonBChanged(false);
        break;
    case QGamepadBackend::ButtonX:
        buttonX = false;
        emit q->buttonXChanged(false);
        break;
    case QGamepadBackend::ButtonY:
        buttonY = false;
        emit q->buttonYChanged(false);
        break;
    case QGamepadBackend::ButtonL1:
        buttonL1 = false;
        emit q->buttonL1Changed(false);
        break;
    case QGamepadBackend::ButtonR1:
        buttonR1 = false;
        emit q->buttonR1Changed(false);
        break;
    case QGamepadBackend::ButtonL2:
        buttonL2 = 0.0;
        emit q->buttonL2Changed(0.0);
        break;
    case QGamepadBackend::ButtonR2:
        buttonR2 = 0.0;
        emit q->buttonR2Changed(0.0);
        break;
    case QGamepadBackend::ButtonL3:
        buttonL3 = false;
        emit q->buttonL3Changed(false);
        break;
    case QGamepadBackend::ButtonR3:
        buttonR3 = false;
        emit q->buttonR3Changed(false);
        break;
    case QGamepadBackend::ButtonSelect:
        buttonSelect = false;
        emit q->buttonSelectChanged(false);
        break;
    case QGamepadBackend::ButtonStart:
        buttonStart = false;
        emit q->buttonStartChanged(false);
        break;
    case QGamepadBackend::ButtonUp:
        buttonUp = false;
        emit q->buttonUpChanged(false);
        break;
    case QGamepadBackend::ButtonDown:
        buttonDown = false;
        emit q->buttonDownChanged(false);
        break;
    case QGamepadBackend::ButtonLeft:
        buttonLeft = false;
        emit q->buttonLeftChanged(false);
        break;
    case QGamepadBackend::ButtonRight:
        buttonRight = false;
        emit q->buttonRightChanged(false);
        break;
    case QGamepadBackend::ButtonCenter:
        buttonCenter = false;
        emit q->buttonCenterChanged(false);
        break;
    case QGamepadBackend::ButtonGuide:
        buttonGuide = false;
        emit q->buttonGuideChanged(false);
        break;
    default:
        break;
    }
}
#endif
/*!
   \class QGamepad
   \inmodule QtGamepad
   \brief A gamepad device connected to a system

   QGamepad is used to access the current state of gamepad hardware connected
   to a system.
 */

/*!
 * Constructs a QGamepad with the given \a deviceId and \a parent.
 */
QGamepad::QGamepad(int deviceId, QObject *parent, QGamepadManager *manager)
    //: QObject(*new QGamepadPrivate(deviceId), parent)
{
    //Q_D(QGamepad);
    QGamepad::deviceId = deviceId;
    gamepadManager = manager;
    connect(manager, SIGNAL(gamepadConnected(int)), this, SLOT(_q_handleGamepadConnected(int)));
    connect(manager, SIGNAL(gamepadNameChanged(int, QString)), this, SLOT(_q_handleGamepadNameChanged(int, QString)));
    connect(manager, SIGNAL(gamepadDisconnected(int)), this, SLOT(_q_handleGamepadDisconnected(int)));
    connect(manager, SIGNAL(gamepadAxisEvent(int,QGamepadBackend::GamepadAxis,double)), this, SLOT(_q_handleGamepadAxisEvent(int,QGamepadBackend::GamepadAxis,double)));
    connect(manager, SIGNAL(gamepadButtonPressEvent(int,QGamepadBackend::GamepadButton,double)), this, SLOT(_q_handleGamepadButtonPressEvent(int,QGamepadBackend::GamepadButton,double)));
    connect(manager, SIGNAL(gamepadButtonReleaseEvent(int,QGamepadBackend::GamepadButton)), this, SLOT(_q_handleGamepadButtonReleaseEvent(int,QGamepadBackend::GamepadButton)));

    setConnected(manager->isGamepadConnected(deviceId));
    setName(manager->gamepadName(deviceId));
}

/*!
 * \brief Destroys the QGamepad.
 */
QGamepad::~QGamepad()
{
}

void QGamepad::setConnected(bool isConnected)
{
    //Q_Q(QGamepad);
    if (connected != isConnected) {
        connected = isConnected;
        emit connectedChanged(connected);
    }
}

void QGamepad::setName(const QString &theName)
{
    //Q_Q(QGamepad);
    if (name != theName) {
        name = theName;
        emit nameChanged(name);
    }
}

/*!
 * \property QGamepad::deviceId
 *
 * This property holds the deviceId of the gamepad device.  Multiple gamepad devices can be
 * connected at any given time, so setting this property defines which gamepad to use.
 *
 * \sa QGamepadManager::connectedGamepads()
 */
int QGamepad::getDeviceId() const
{
    //Q_D(const QGamepad);
    return deviceId;
}

/*!
 * \property QGamepad::connected
 * This read-only property holds the connectivity state of the gamepad device.
 * If a gamepad is connected, this property will be true, otherwise false.
 */
bool QGamepad::isConnected() const
{
    //Q_D(const QGamepad);
    return connected;
}

/*!
 * \property QGamepad::getName
 *
 * This read-only property holds the reported name of the gamepad if one
 * is available.
 */
QString QGamepad::getName() const
{
    //Q_D(const QGamepad);
    return name;
}

/*!
 * \property QGamepad::axisLeftX
 *
 * This read-only property holds the value of the left thumbstick's X axis.
 * The axis values range from -1.0 to 1.0.
 */
double QGamepad::getAxisLeftX() const
{
    //Q_D(const QGamepad);
    return axisLeftX;
}

/*!
 * \property QGamepad::axisLeftY
 *
 * This read-only property holds the value of the left thumbstick's Y axis.
 * The axis values range from -1.0 to 1.0.
 */
double QGamepad::getAxisLeftY() const
{
    //Q_D(const QGamepad);
    return axisLeftY;
}

/*!
 * \property QGamepad::axisRightX
 *
 * This read-only property holds the value of the right thumbstick's X axis.
 * The axis values range from -1.0 to 1.0.
 */
double QGamepad::getAxisRightX() const
{
    //Q_D(const QGamepad);
    return axisRightX;
}

/*!
 * \property QGamepad::axisRightY
 *
 * This read-only property holds the value of the right thumbstick's Y axis.
 * The axis values range from -1.0 to 1.0.
 */
double QGamepad::getAxisRightY() const
{
    //Q_D(const QGamepad);
    return axisRightY;
}

/*!
 * \property QGamepad::buttonA
 *
 * This read-only property holds the state of the A button.
 * The value is \c true when pressed, and \c false when not pressed.
 */
bool QGamepad::getButtonA() const
{
    //Q_D(const QGamepad);
    return buttonA;
}

/*!
 * \property QGamepad::buttonB
 *
 * This read-only property holds the state of the B button.
 * The value is \c true when pressed, and \c false when not pressed.
 *
 * \sa QGamepadManager::connectedGamepads()
 */
bool QGamepad::getButtonB() const
{
    //Q_D(const QGamepad);
    return buttonB;
}

/*!
 * \property QGamepad::buttonX
 *
 * This read-only property holds the state of the X button.
 * The value is \c true when pressed, and \c false when not pressed.
 */
bool QGamepad::getButtonX() const
{
    //Q_D(const QGamepad);
    return buttonX;
}

/*!
 * \property QGamepad::buttonY
 *
 * This read-only property holds the state of the Y button.
 * The value is \c true when pressed, and \c false when not pressed.
 */
bool QGamepad::getButtonY() const
{
    //Q_D(const QGamepad);
    return buttonY;
}

/*!
 * \property QGamepad::buttonL1
 *
 * This read-only property holds the state of the left shoulder button.
 * The value is \c true when pressed, and \c false when not pressed.
 */
bool QGamepad::getButtonL1() const
{
    //Q_D(const QGamepad);
    return buttonL1;
}

/*!
 * \property QGamepad::buttonR1
 *
 * This read-only property holds the state of the right shoulder button.
 * The value is \c true when pressed, and \c false when not pressed.
 */
bool QGamepad::getButtonR1() const
{
    //Q_D(const QGamepad);
    return buttonR1;
}

/*!
 * \property QGamepad::buttonL2
 *
 * This read-only property holds the value of the left trigger button.
 * This trigger value ranges from 0.0 when not pressed to 1.0
 * when pressed completely.
 */
double QGamepad::getButtonL2() const
{
    //Q_D(const QGamepad);
    return buttonL2;
}

/*!
 * \property QGamepad::buttonR2
 *
 * This read-only property holds the value of the right trigger button.
 * This trigger value ranges from 0.0 when not pressed to 1.0
 * when pressed completely.
 */
double QGamepad::getButtonR2() const
{
    //Q_D(const QGamepad);
    return buttonR2;
}

/*!
 * \property QGamepad::buttonSelect
 *
 * This read-only property holds the state of the Select button.
 * The value is \c true when pressed, and \c false when not pressed.
 * This button can sometimes be labeled as the Back button on some gamepads.
 */
bool QGamepad::getButtonSelect() const
{
    //Q_D(const QGamepad);
    return buttonSelect;
}

/*!
 * \property QGamepad::buttonStart
 *
 * This read-only property holds the state of the Start button.
 * The value is \c true when pressed, and \c false when not pressed.
 * This button can sometimes be labeled as the Forward button on some gamepads.
 */
bool QGamepad::getButtonStart() const
{
    //Q_D(const QGamepad);
    return buttonStart;
}

/*!
 * \property QGamepad::buttonL3
 *
 * This read-only property holds the state of the left stick button.
 * The value is \c true when pressed, and \c false when not pressed.
 * This button is usually triggered by pressing the left joystick itself.
 */
bool QGamepad::getButtonL3() const
{
    //Q_D(const QGamepad);
    return buttonL3;
}

/*!
 * \property QGamepad::buttonR3
 *
 * This read-only property holds the state of the right stick button.
 * The value is \c true when pressed, and \c false when not pressed.
 * This button is usually triggered by pressing the right joystick itself.
 */
bool QGamepad::getButtonR3() const
{
    //Q_D(const QGamepad);
    return buttonR3;
}

/*!
 * \property QGamepad::buttonUp
 *
 * This read-only property holds the state of the direction pad up button.
 * The value is \c true when pressed, and \c false when not pressed.
 */
bool QGamepad::getButtonUp() const
{
    //Q_D(const QGamepad);
    return buttonUp;
}

/*!
 * \property QGamepad::buttonDown
 *
 * This read-only property holds the state of the direction pad down button.
 * The value is \c true when pressed, and \c false when not pressed.
 */
bool QGamepad::getButtonDown() const
{
    //Q_D(const QGamepad);
    return buttonDown;
}

/*!
 * \property QGamepad::buttonLeft
 *
 * This read-only property holds the state of the direction pad left button.
 * The value is \c true when pressed, and \c false when not pressed.
 */
bool QGamepad::getButtonLeft() const
{
    //Q_D(const QGamepad);
    return buttonLeft;
}

/*!
 * \property QGamepad::buttonRight
 *
 * This read-only property holds the state of the direction pad right button.
 * The value is \c true when pressed, and \c false when not pressed.
 */
bool QGamepad::getButtonRight() const
{
    //Q_D(const QGamepad);
    return buttonRight;
}

/*!
 * \property QGamepad::buttonCenter
 *
 * This read-only property holds the state of the center button.
 * The value is \c true when pressed, and \c false when not pressed.
 */
bool QGamepad::getButtonCenter() const
{
    //Q_D(const QGamepad);
    return buttonCenter;
}

/*!
 * \property QGamepad::buttonGuide
 *
 * This read-only property holds the state of the guide button.
 * The value is \c true when pressed, and \c false when not pressed.
 * This button is typically the one in the center of the gamepad with a logo.
 * Some gamepads will not have a guide button.
 */
bool QGamepad::getButtonGuide() const
{
    //Q_D(const QGamepad);
    return buttonGuide;
}

void QGamepad::setDeviceId(int number)
{
    //Q_D(QGamepad);
    if (deviceId != number) {
        deviceId = number;
        emit deviceIdChanged(number);
        setConnected(gamepadManager->isGamepadConnected(deviceId));
    }
}
/*!
 * \internal
 */\
void QGamepad::_q_handleGamepadConnected(int id)
{
    if (id == deviceId) {
        setConnected(true);
    }
}

/*!
 * \internal
 */\
void QGamepad::_q_handleGamepadNameChanged(int id, const QString &name)
{
    if (id == deviceId)
        setName(name);
}

/*!
 * \internal
 */\
void QGamepad::_q_handleGamepadDisconnected(int id)
{
    if (id == deviceId) {
        setConnected(false);
    }
}

/*!
 * \internal
 */\
void QGamepad::_q_handleGamepadAxisEvent(int id, QGamepadBackend::GamepadAxis axis, double value)
{
    //Q_Q(QGamepad);
    if (id != deviceId)
        return;

    switch (axis) {
    case QGamepadBackend::AxisLeftX:
        axisLeftX = value;
        emit axisLeftXChanged(value);
        break;
    case QGamepadBackend::AxisLeftY:
        axisLeftY = value;
        emit axisLeftYChanged(value);
        break;
    case QGamepadBackend::AxisRightX:
        axisRightX = value;
        emit axisRightXChanged(value);
        break;
    case QGamepadBackend::AxisRightY:
        axisRightY = value;
        emit axisRightYChanged(value);
        break;
    default:
        break;
    }
}

/*!
 * \internal
 */\
void QGamepad::_q_handleGamepadButtonPressEvent(int id, QGamepadBackend::GamepadButton button, double value)
{
    //Q_Q(QGamepad);
    if (id != deviceId)
        return;

    switch (button) {
    case QGamepadBackend::ButtonA:
        buttonA = true;
        emit buttonAChanged(true);
        break;
    case QGamepadBackend::ButtonB:
        buttonB = true;
        emit buttonBChanged(true);
        break;
    case QGamepadBackend::ButtonX:
        buttonX = true;
        emit buttonXChanged(true);
        break;
    case QGamepadBackend::ButtonY:
        buttonY = true;
        emit buttonYChanged(true);
        break;
    case QGamepadBackend::ButtonL1:
        buttonL1 = true;
        emit buttonL1Changed(true);
        break;
    case QGamepadBackend::ButtonR1:
        buttonR1 = true;
        emit buttonR1Changed(true);
        break;
    case QGamepadBackend::ButtonL2:
        buttonL2 = value;
        emit buttonL2Changed(value);
        break;
    case QGamepadBackend::ButtonR2:
        buttonR2 = value;
        emit buttonR2Changed(value);
        break;
    case QGamepadBackend::ButtonL3:
        buttonL3 = true;
        emit buttonL3Changed(true);
        break;
    case QGamepadBackend::ButtonR3:
        buttonR3 = true;
        emit buttonR3Changed(true);
        break;
    case QGamepadBackend::ButtonSelect:
        buttonSelect = true;
        emit buttonSelectChanged(true);
        break;
    case QGamepadBackend::ButtonStart:
        buttonStart = true;
        emit buttonStartChanged(true);
        break;
    case QGamepadBackend::ButtonUp:
        buttonUp = true;
        emit buttonUpChanged(true);
        break;
    case QGamepadBackend::ButtonDown:
        buttonDown = true;
        emit buttonDownChanged(true);
        break;
    case QGamepadBackend::ButtonLeft:
        buttonLeft = true;
        emit buttonLeftChanged(true);
        break;
    case QGamepadBackend::ButtonRight:
        buttonRight = true;
        emit buttonRightChanged(true);
        break;
    case QGamepadBackend::ButtonCenter:
        buttonCenter = true;
        emit buttonCenterChanged(true);
        break;
    case QGamepadBackend::ButtonGuide:
        buttonGuide = true;
        emit buttonGuideChanged(true);
        break;
    default:
        break;
    }

}

/*!
 * \internal
 */\
void QGamepad::_q_handleGamepadButtonReleaseEvent(int id, QGamepadBackend::GamepadButton button)
{
    //Q_Q(QGamepad);
    if (id != deviceId)
        return;

    switch (button) {
    case QGamepadBackend::ButtonA:
        buttonA = false;
        emit buttonAChanged(false);
        break;
    case QGamepadBackend::ButtonB:
        buttonB = false;
        emit buttonBChanged(false);
        break;
    case QGamepadBackend::ButtonX:
        buttonX = false;
        emit buttonXChanged(false);
        break;
    case QGamepadBackend::ButtonY:
        buttonY = false;
        emit buttonYChanged(false);
        break;
    case QGamepadBackend::ButtonL1:
        buttonL1 = false;
        emit buttonL1Changed(false);
        break;
    case QGamepadBackend::ButtonR1:
        buttonR1 = false;
        emit buttonR1Changed(false);
        break;
    case QGamepadBackend::ButtonL2:
        buttonL2 = 0.0;
        emit buttonL2Changed(0.0);
        break;
    case QGamepadBackend::ButtonR2:
        buttonR2 = 0.0;
        emit buttonR2Changed(0.0);
        break;
    case QGamepadBackend::ButtonL3:
        buttonL3 = false;
        emit buttonL3Changed(false);
        break;
    case QGamepadBackend::ButtonR3:
        buttonR3 = false;
        emit buttonR3Changed(false);
        break;
    case QGamepadBackend::ButtonSelect:
        buttonSelect = false;
        emit buttonSelectChanged(false);
        break;
    case QGamepadBackend::ButtonStart:
        buttonStart = false;
        emit buttonStartChanged(false);
        break;
    case QGamepadBackend::ButtonUp:
        buttonUp = false;
        emit buttonUpChanged(false);
        break;
    case QGamepadBackend::ButtonDown:
        buttonDown = false;
        emit buttonDownChanged(false);
        break;
    case QGamepadBackend::ButtonLeft:
        buttonLeft = false;
        emit buttonLeftChanged(false);
        break;
    case QGamepadBackend::ButtonRight:
        buttonRight = false;
        emit buttonRightChanged(false);
        break;
    case QGamepadBackend::ButtonCenter:
        buttonCenter = false;
        emit buttonCenterChanged(false);
        break;
    case QGamepadBackend::ButtonGuide:
        buttonGuide = false;
        emit buttonGuideChanged(false);
        break;
    default:
        break;
    }
}

QT_END_NAMESPACE

//#include "moc_gamepad.cpp"

