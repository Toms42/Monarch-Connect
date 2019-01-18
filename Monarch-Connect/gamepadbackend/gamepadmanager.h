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

#ifndef QGAMEPADMANAGER_H
#define QGAMEPADMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QList>
#include "gamepadbackend/gamepadbackend.h"

//QT_BEGIN_NAMESPACE

//class QGamepadBackend;
//class QGamepad;
//class QGamepadManagerPrivate;

class QGamepadManager : public QObject
{
    Q_OBJECT
    //Q_FLAGS(GamepadButton GamepadButtons)
    //Q_FLAGS(GamepadAxis GamepadAxes)
    Q_PROPERTY(QList<int> connectedGamepads READ getConnectedGamepads NOTIFY connectedGamepadsChanged)

public:

    //Q_DECLARE_FLAGS(GamepadButtons, GamepadButton)

    //Q_DECLARE_FLAGS(GamepadAxes, GamepadAxis)

    //static QGamepadManager* instance();
    QGamepadManager();
    ~QGamepadManager();

    bool isGamepadConnected(int deviceId) const;
    QString gamepadName(int deviceId) const;
    QMap<int, QString> *connectedGamepads;
    const QList<int> getConnectedGamepads() const;

public Q_SLOTS:
    bool isConfigurationNeeded(int deviceId) const;
    bool configureButton(int deviceId, QGamepadBackend::GamepadButton button);
    bool configureAxis(int deviceId, QGamepadBackend::GamepadAxis axis);
    bool setCancelConfigureButton(int deviceId, QGamepadBackend::GamepadButton button);
    void resetConfiguration(int deviceId);
    void setSettingsFile(const QString &file);

signals:
    void connectedGamepadsChanged();
    void gamepadConnected(int deviceId);
    void gamepadNameChanged(int deviceId, const QString &name);
    void gamepadDisconnected(int deviceId);
    void gamepadAxisEvent(int deviceId, QGamepadBackend::GamepadAxis axis, double value);
    void gamepadButtonPressEvent(int deviceId, QGamepadBackend::GamepadButton button, double value);
    void gamepadButtonReleaseEvent(int deviceId, QGamepadBackend::GamepadButton button);
    void buttonConfigured(int deviceId, QGamepadBackend::GamepadButton button);
    void axisConfigured(int deviceId, QGamepadBackend::GamepadAxis axis);
    void configurationCanceled(int deviceId);

private:
    QGamepadBackend *backend;
    //QGamepadManager();
    //~QGamepadManager();

    //Q_DECLARE_PRIVATE(QGamepadManager)
    //Q_DISABLE_COPY(QGamepadManager)
private slots:
    void _q_forwardGamepadConnected(int deviceId);
    void _q_forwardGamepadNameChanged(int deviceId, const QString &name);
    void _q_forwardGamepadDisconnected(int deviceId);
    void _q_forwardGamepadAxisEvent(int deviceId, QGamepadBackend::GamepadAxis axis, double value);
    void _q_forwardGamepadButtonPressEvent(int deviceId, QGamepadBackend::GamepadButton button, double value);
    void _q_forwardGamepadButtonReleaseEvent(int deviceId, QGamepadBackend::GamepadButton button);
};

//QT_END_NAMESPACE

//Q_DECLARE_METATYPE(QGamepadManager::GamepadButton)
//Q_DECLARE_METATYPE(QGamepadManager::GamepadAxis)

#endif // QGAMEPADMANAGER_H
