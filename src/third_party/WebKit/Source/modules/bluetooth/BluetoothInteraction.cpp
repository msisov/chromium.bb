// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "config.h"
#include "modules/bluetooth/BluetoothInteraction.h"

#include "modules/bluetooth/BluetoothUUIDs.h"

namespace blink {

BluetoothUUIDs* BluetoothInteraction::uuids()
{
    if (!m_bluetoothUUIDs)
        m_bluetoothUUIDs = new BluetoothUUIDs;
    return m_bluetoothUUIDs.get();
}

}; // blink
