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

#include "gamepadmanager.h"
#include "xinputbackend.h"
#include "gamepadbackend.h"

#include <QtCore/QLoggingCategory>

//#include <private/qobject_p.h>

QT_BEGIN_NAMESPACE

Q_LOGGING_CATEGORY(gp, "qt.gamepad")

/*
class QGamepadManagerPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QGamepadManager)
public:
    QGamepadManagerPrivate()
        : gamepadBackend(nullptr)
    {
        loadBackend();
    }

    void loadBackend();

    //QGamepadBackend *gamepadBackend;
    QMap<int, QString> connectedGamepads;

    //private slots
    void _q_forwardGamepadConnected(int deviceId);
    void _q_forwardGamepadNameChanged(int deviceId, const QString &name);
    void _q_forwardGamepadDisconnected(int deviceId);
    void _q_forwardGamepadAxisEvent(int deviceId, QGamepadManager::GamepadAxis axis, double value);
    void _q_forwardGamepadButtonPressEvent(int deviceId, QGamepadManager::GamepadButton button, double value);
    void _q_forwardGamepadButtonReleaseEvent(int deviceId, QGamepadManager::GamepadButton button);
};

void QGamepadManagerPrivate::_q_forwardGamepadConnected(int deviceId)
{
    Q_Q(QGamepadManager);
    connectedGamepads.insert(deviceId, QString());
    emit q->gamepadConnected(deviceId);
    emit q->connectedGamepadsChanged();
}

void QGamepadManagerPrivate::_q_forwardGamepadNameChanged(int deviceId, const QString &name)
{
    Q_Q(QGamepadManager);
    connectedGamepads.insert(deviceId, name);
    emit q->gamepadNameChanged(deviceId, name);
}

void QGamepadManagerPrivate::_q_forwardGamepadDisconnected(int deviceId)
{
    Q_Q(QGamepadManager);
    connectedGamepads.remove(deviceId);
    emit q->gamepadDisconnected(deviceId);
    emit q->connectedGamepadsChanged();
}

void QGamepadManagerPrivate::_q_forwardGamepadAxisEvent(int deviceId, QGamepadManager::GamepadAxis axis, double value)
{
    Q_Q(QGamepadManager);
    emit q->gamepadAxisEvent(deviceId, axis, value);
}

void QGamepadManagerPrivate::_q_forwardGamepadButtonPressEvent(int deviceId, QGamepadManager::GamepadButton button, double value)
{
    Q_Q(QGamepadManager);
    emit q->gamepadButtonPressEvent(deviceId, button, value);
}

void QGamepadManagerPrivate::_q_forwardGamepadButtonReleaseEvent(int deviceId, QGamepadManager::GamepadButton button)
{
    Q_Q(QGamepadManager);
    emit q->gamepadButtonReleaseEvent(deviceId, button);
}

void QGamepadManagerPrivate::loadBackend()
{
    QStringList keys = QGamepadBackendFactory::keys();
    qCDebug(gp) << "Available backends:" << keys;
    if (!keys.isEmpty()) {
        QString requestedKey = QString::fromUtf8(qgetenv("QT_GAMEPAD"));
        QString targetKey = keys.first();
        if (!requestedKey.isEmpty() && keys.contains(requestedKey))
            targetKey = requestedKey;
        if (!targetKey.isEmpty()) {
            qCDebug(gp) << "Loading backend" << targetKey;
            gamepadBackend = QGamepadBackendFactory::create(targetKey, QStringList());
        }
    }

    if (!gamepadBackend) {
        //Use dummy backend
        gamepadBackend = new QGamepadBackend();
        qCDebug(gp) << "Using dummy backend";
    }
}
*/
/*!
   \class QGamepadManager
   \inmodule QtGamepad
   \brief Queries attached gamepads and related events.

   QGamepadManager provides a high-level interface for querying the attached
   gamepads and events related to all of the connected devices.
 */

/*!
 * Constructor for QGamepadManager.
 */

QGamepadManager::QGamepadManager()// :
    //QObject(*new QGamepadManagerPrivate(), nullptr)
{
    //Q_D(QGamepadManager);
    backend = new QXInputGamepadBackend();
    connectedGamepads = new QMap<int, QString>();

    qRegisterMetaType<QGamepadBackend::GamepadButton>("QGamepadBackend::GamepadButton");
    qRegisterMetaType<QGamepadBackend::GamepadAxis>("QGamepadBackend::GamepadAxis");

    connect(backend, SIGNAL(gamepadAdded(int)), this, SLOT(_q_forwardGamepadConnected(int)));
    connect(backend, SIGNAL(gamepadNamed(int, QString)), this, SLOT(_q_forwardGamepadNameChanged(int, QString)));
    connect(backend, SIGNAL(gamepadRemoved(int)), this, SLOT(_q_forwardGamepadDisconnected(int)));
    connect(backend, SIGNAL(gamepadAxisMoved(int,QGamepadBackend::GamepadAxis,double)), this, SLOT(_q_forwardGamepadAxisEvent(int,QGamepadBackend::GamepadAxis,double)));
    connect(backend, SIGNAL(gamepadButtonPressed(int,QGamepadBackend::GamepadButton,double)), this, SLOT(_q_forwardGamepadButtonPressEvent(int,QGamepadBackend::GamepadButton,double)));
    connect(backend, SIGNAL(gamepadButtonReleased(int,QGamepadBackend::GamepadButton)), this, SLOT(_q_forwardGamepadButtonReleaseEvent(int,QGamepadBackend::GamepadButton)));

    connect(backend, &QGamepadBackend::buttonConfigured, this, &QGamepadManager::buttonConfigured);
    connect(backend, &QGamepadBackend::axisConfigured, this, &QGamepadManager::axisConfigured);
    connect(backend, &QGamepadBackend::configurationCanceled, this, &QGamepadManager::configurationCanceled);

    if (!backend->start())
        qCWarning(gp) << "Failed to start gamepad backend";
}

/*!
 * Destructor for QGamepadManager.
 */

QGamepadManager::~QGamepadManager()
{
    //Q_D(QGamepadManager);
    //QGamepadManager d = this;
    backend->stop();
    backend->deleteLater();
}

/*!
    Returns the instance of the QGamepadManager.
*/

/*
QGamepadManager *QGamepadManager::instance()
{
    static QGamepadManager instance;
    return &instance;
}*/

/*!
    Returns a boolean indicating whether the gamepad with
    the specified \a deviceId is connected or not.
*/
bool QGamepadManager::isGamepadConnected(int deviceId) const
{
    //Q_D(const QGamepadManager);
    return connectedGamepads->contains(deviceId);
}

/*!
    Returns the name of the gamepad identified by \a deviceId.
    If \a deviceId does not identify a connected gamepad, returns an empty string.

    \since 5.11
*/
QString QGamepadManager::gamepadName(int deviceId) const
{
    //Q_D(const QGamepadManager);
    return connectedGamepads->value(deviceId);
}

/*!
    Returns a QList containing the \l {QGamepad::}{deviceId}
    values of the connected gamepads.
*/
const QList<int> QGamepadManager::getConnectedGamepads() const
{
    //Q_D(const QGamepadManager);
    return connectedGamepads->keys();
}

/*!
    Returns a boolean indicating whether configuration
    is needed for the specified \a deviceId.
*/
bool QGamepadManager::isConfigurationNeeded(int deviceId) const
{
    //Q_D(const QGamepadManager);
    return backend->isConfigurationNeeded(deviceId);
}

/*!
    Configures the specified \a button on the gamepad with
    this \a deviceId.
    Returns \c true in case of success.
*/
bool QGamepadManager::configureButton(int deviceId, QGamepadBackend::GamepadButton button)
{
    //Q_D(QGamepadManager);
    return backend->configureButton(deviceId, button);
}

/*!
    Configures \a axis on the gamepad with the specified \a deviceId.
    Returns \c true in case of success.
*/
bool QGamepadManager::configureAxis(int deviceId, QGamepadBackend::GamepadAxis axis)
{
    //Q_D(QGamepadManager);
    return backend->configureAxis(deviceId, axis);
}

/*!
    Configures \a button as the cancel button on the gamepad with
    id \a deviceId.
    Returns \c true in case of success.
*/
bool QGamepadManager::setCancelConfigureButton(int deviceId, QGamepadBackend::GamepadButton button)
{
    //Q_D(QGamepadManager);
    return backend->setCancelConfigureButton(deviceId, button);
}

/*!
    Resets the configuration on the gamepad with the
    specified \a deviceId.
*/
void QGamepadManager::resetConfiguration(int deviceId)
{
    //Q_D(QGamepadManager);
    backend->resetConfiguration(deviceId);
}

/*!
    Sets the name of the \a file that stores the button and axis
    configuration data.
*/
void QGamepadManager::setSettingsFile(const QString &file)
{
    //Q_D(QGamepadManager);
    backend->setSettingsFile(file);
}

void QGamepadManager::_q_forwardGamepadConnected(int deviceId)
{
    //Q_Q(QGamepadManager);
    connectedGamepads->insert(deviceId, QString());
    emit gamepadConnected(deviceId);
    emit connectedGamepadsChanged();
}

void QGamepadManager::_q_forwardGamepadNameChanged(int deviceId, const QString &name)
{
    //Q_Q(QGamepadManager);
    connectedGamepads->insert(deviceId, name);
    emit gamepadNameChanged(deviceId, name);
}

void QGamepadManager::_q_forwardGamepadDisconnected(int deviceId)
{
    //Q_Q(QGamepadManager);
    connectedGamepads->remove(deviceId);
    emit gamepadDisconnected(deviceId);
    emit connectedGamepadsChanged();
}

void QGamepadManager::_q_forwardGamepadAxisEvent(int deviceId, QGamepadBackend::GamepadAxis axis, double value)
{
    //Q_Q(QGamepadManager);
    emit gamepadAxisEvent(deviceId, axis, value);
}

void QGamepadManager::_q_forwardGamepadButtonPressEvent(int deviceId, QGamepadBackend::GamepadButton button, double value)
{
    //Q_Q(QGamepadManager);
    emit gamepadButtonPressEvent(deviceId, button, value);
}

void QGamepadManager::_q_forwardGamepadButtonReleaseEvent(int deviceId, QGamepadBackend::GamepadButton button)
{
    //Q_Q(QGamepadManager);
    emit gamepadButtonReleaseEvent(deviceId, button);
}

QT_END_NAMESPACE

//#include "moc_qgamepadmanager.cpp"
