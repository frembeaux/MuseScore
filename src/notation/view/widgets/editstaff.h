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

#ifndef MU_NOTATION_EDITSTAFF_H
#define MU_NOTATION_EDITSTAFF_H

#include <QDialog>

#include "ui_editstaff.h"
#include "libmscore/stafftype.h"

#include "modularity/ioc.h"
#include "context/iglobalcontext.h"

namespace mu {
namespace notation {
class EditStaff;
class EditStaffType;

//---------------------------------------------------------
//   EditStaff
//    edit staff and part properties
//---------------------------------------------------------

class EditStaff : public QDialog, private Ui::EditStaffBase
{
    Q_OBJECT

    INJECT(notation, mu::context::IGlobalContext, globalContext)

    Q_PROPERTY(int staffIdx READ staffIdx WRITE setStaffIdx NOTIFY staffIdxChanged)

    EditStaff(QWidget* parent = nullptr);
    EditStaff(const EditStaff&);

    static int metaTypeId();

    virtual void hideEvent(QHideEvent*);
    void apply();
    void setStaff(Ms::Staff*, const Ms::Fraction& tick);
    void updateInterval(const Ms::Interval&);
    void updateStaffType(const Ms::StaffType& staffType);
    void updateInstrument();
    void updateNextPreviousButtons();

protected:
    QString midiCodeToStr(int midiCode);

private slots:
    void bboxClicked(QAbstractButton* button);
    void editStringDataClicked();
    void showInstrumentDialog();
    void showStaffTypeDialog();
    void minPitchAClicked();
    void maxPitchAClicked();
    void minPitchPClicked();
    void maxPitchPClicked();
    void lineDistanceChanged();
    void numOfLinesChanged();
    void showClefChanged();
    void showTimeSigChanged();
    void showBarlinesChanged();
    void gotoNextStaff();
    void gotoPreviousStaff();
    void invisibleChanged();
    void transpositionChanged();
    void setStaffIdx(int staffIdx);

signals:
    void instrumentChanged();
    void staffIdxChanged(int staffIdx);

private:
    INotationPartsPtr notationParts() const;

    int staffIdx() const;
    void updateCurrentStaff();

    Staff* staff(int staffIndex) const;
    instruments::Instrument instrument() const;

    void applyStaffProperties();
    void applyPartProperties();

    bool isInstrumentChanged();

private:
    int m_staffIdx = -1;
    Ms::Staff* m_staff = nullptr;
    Ms::Staff* m_orgStaff = nullptr;
    ID m_partId;
    ID m_instrumentId;
    instruments::Instrument m_instrument;
    instruments::Instrument m_orgInstrument;
    int m_minPitchA, m_maxPitchA, m_minPitchP, m_maxPitchP;
    Ms::Fraction m_tickStart, m_tickEnd;

    EditStaffType* editStaffTypeDialog = nullptr;
};
}
}

Q_DECLARE_METATYPE(mu::notation::EditStaff)

#endif
