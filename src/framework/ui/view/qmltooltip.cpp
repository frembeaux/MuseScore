/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "qmltooltip.h"

#include <QWidget>
#include <QToolTip>
#include <QGuiApplication>
#include <QStyleHints>
#include <QCursor>
#include <QQuickWindow>

#include "log.h"

using namespace mu::ui;

QmlToolTip::QmlToolTip(QObject* parent)
    : QObject(parent)
{
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &QmlToolTip::doShowToolTip);
}

void QmlToolTip::show(QQuickItem* item, const QString& text)
{
    if (item != m_item) {
        if (m_item) {
            disconnect(m_item, &QObject::destroyed, this, &QmlToolTip::doHide);
        }

        m_item = item;
        m_text = text;

        if (m_item) {
            connect(m_item, &QObject::destroyed, this, &QmlToolTip::doHide);

            const int interval = item ? qApp->styleHints()->mousePressAndHoldInterval() : 100;
            m_timer.start(interval);
        } else {
            doHide();
        }
    }
}

void QmlToolTip::hide(QQuickItem* item)
{
    if (m_item != item) {
        return;
    }

    doHide();
}

void QmlToolTip::doShowToolTip()
{
    if (!m_item) {
        return;
    }

    const QPointF topLeft = m_item->mapToGlobal(QPointF(0, 0));
    const QRect rect(topLeft.x(), topLeft.y(), m_item->width(), m_item->height());
    const QPoint pos(QCursor::pos());

    if (rect.contains(pos)) {
        QToolTip::showText(pos, m_text);
    }
}

void QmlToolTip::doHide()
{
    if (m_item) {
        disconnect(m_item, &QObject::destroyed, this, &QmlToolTip::doHide);
    }

    m_timer.stop();
    m_item = nullptr;
    m_text = QString();
    QToolTip::hideText();
}
