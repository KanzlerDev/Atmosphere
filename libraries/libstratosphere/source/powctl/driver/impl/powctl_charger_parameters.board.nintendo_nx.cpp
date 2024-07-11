/*
 * Copyright (c) Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stratosphere.hpp>

namespace ams::powctl::driver::impl {

    namespace {

        constexpr inline const PowerState AcceptablePowerStates[] = {
            PowerState::FullAwake,
            PowerState::MinimumAwake,
            PowerState::SleepCharge,
            PowerState::SleepDischarge,
            PowerState::ShutdownChargeMain,
        };

        constexpr inline const PowerState AcceptablePowerStatesForNotAwakeCharge[] = {
            PowerState::SleepCharge,
            PowerState::ShutdownChargeMain,
        };

        constexpr inline const int Max = std::numeric_limits<int>::max();
        constexpr inline const int Min = std::numeric_limits<int>::min();

        constexpr inline const float FloatMax = std::numeric_limits<float>::max();
        constexpr inline const float FloatMin = -FloatMax;

    }

    const ChargeParameters &GetChargeParameters() {
        /* Get the battery version. */
        u8 battery_version;
        if (R_FAILED(cal::GetBatteryVersion(std::addressof(battery_version)))) {
            battery_version = 0;
        }

        if (battery_version == 2) {
            return ChargeParametersForBatteryVersion2;
        } else if (battery_version == 1) {
            return ChargeParametersForBatteryVersion1;
        } else {
            if (spl::GetHardwareType() == spl::HardwareType::Aula) {
                return ChargeParametersForBatteryVersion0ForAula;
            } else {
                return ChargeParametersForBatteryVersion0;
            }
        }
    }

}
