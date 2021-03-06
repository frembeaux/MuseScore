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
#include "clock.h"

using namespace mu::audio;

Clock::Clock()
{
}

Clock::time_t Clock::time() const
{
    return m_time;
}

float Clock::timeInSeconds() const
{
    return m_time / static_cast<float>(m_sampleRate);
}

Clock::time_t Clock::timeInMiliSeconds() const
{
    return m_time * 1000 / m_sampleRate;
}

void Clock::setSampleRate(unsigned int sampleRate)
{
    m_sampleRate = sampleRate;
}

void Clock::forward(Clock::time_t samples)
{
    auto deltaMiliseconds = samples * 1000 / m_sampleRate;
    runCallbacks(m_beforeCallbacks, deltaMiliseconds);

    if (m_status == Running) {
        m_time += samples;
        m_timeChanged.send(m_time);
        runCallbacks(m_afterCallbacks, deltaMiliseconds);
    }
}

void Clock::start()
{
    m_status = Running;
}

void Clock::reset()
{
    m_time = 0;
}

void Clock::stop()
{
    m_status = Stoped;
    reset();
}

void Clock::pause()
{
    m_status = Paused;
}

void Clock::seek(time_t time)
{
    m_time = time;
    m_timeChanged.send(m_time);
}

void Clock::seekMiliseconds(Clock::time_t value)
{
    m_time = value * m_sampleRate / 1000;
    m_timeChanged.send(m_time);
}

void Clock::seekSeconds(float seconds)
{
    seek(seconds * m_sampleRate);
}

mu::async::Channel<Clock::time_t> Clock::timeChanged() const
{
    return m_timeChanged;
}

void Clock::addBeforeCallback(Clock::SyncCallback callback)
{
    m_beforeCallbacks.push_back(callback);
}

void Clock::addAfterCallback(Clock::SyncCallback callback)
{
    m_afterCallbacks.push_back(callback);
}

void Clock::runCallbacks(const std::list<Clock::SyncCallback>& list, time_t milliseconds)
{
    for (auto& callback : list) {
        callback(milliseconds);
    }
}
