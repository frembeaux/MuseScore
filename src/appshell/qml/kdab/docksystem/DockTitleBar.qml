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

import QtQuick 2.15

import MuseScore.Ui 1.0
import MuseScore.UiComponents 1.0

import "qrc:/kddockwidgets/private/quick/qml/" as KDDW

Item {
    id: root

    required property QtObject titleBarCpp

    property alias heightWhenVisible: titleBar.heightWhenVisible

    width: parent.width
    height: visible ? heightWhenVisible : 0

    visible: Boolean(titleBarCpp)

    KDDW.TitleBarBase {
        id: titleBar

        anchors.fill: parent

        heightWhenVisible: 30

        StyledTextLabel {
            id: titleLabel

            anchors.centerIn: parent

            font: ui.theme.bodyBoldFont
            text: titleBar.title
        }
    }
}
