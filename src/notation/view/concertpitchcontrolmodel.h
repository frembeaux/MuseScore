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

#ifndef MU_NOTATION_CONCERTPITCHCONTROLMODEL_H
#define MU_NOTATION_CONCERTPITCHCONTROLMODEL_H

#include <QObject>

#include "modularity/ioc.h"
#include "async/asyncable.h"
#include "actions/actionable.h"
#include "actions/iactionsdispatcher.h"
#include "context/iglobalcontext.h"

namespace mu::notation {
class ConcertPitchControlModel : public QObject, public async::Asyncable, public actions::Actionable
{
    Q_OBJECT

    INJECT(notation, context::IGlobalContext, context)
    INJECT(notation, actions::IActionsDispatcher, dispatcher)

    Q_PROPERTY(bool concertPitchEnabled READ concertPitchEnabled WRITE setConcertPitchEnabled NOTIFY concertPitchEnabledChanged)

public:
    explicit ConcertPitchControlModel(QObject* parent = nullptr);

    bool concertPitchEnabled() const;

    Q_INVOKABLE void load();

public slots:
    void setConcertPitchEnabled(bool enabled);

signals:
    void concertPitchEnabledChanged();

private:
    INotationStylePtr style() const;
    INotationPtr notation() const;
};
}

#endif // MU_NOTATION_CONCERTPITCHCONTROLMODEL_H
