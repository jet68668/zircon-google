// Copyright 2018 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <hwreg/bitfields.h>

namespace thermal {

class TempMonCtl0 : public hwreg::RegisterBase<TempMonCtl0, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempMonCtl0>(0x00); }

    DEF_BIT(3, sense3_en);
    DEF_BIT(2, sense2_en);
    DEF_BIT(1, sense1_en);
    DEF_BIT(0, sense0_en);

    TempMonCtl0& disable_all() {
        set_sense0_en(0);
        set_sense1_en(0);
        set_sense2_en(0);
        set_sense3_en(0);
        return *this;
    }

    TempMonCtl0& enable_all() {
        set_sense0_en(1);
        set_sense1_en(1);
        set_sense2_en(1);
        set_sense3_en(1);
        return *this;
    }

    TempMonCtl0& enable_real() {
        set_sense0_en(1);
        set_sense1_en(1);
        set_sense2_en(1);
        return *this;
    }
};

class TempMonCtl1 : public hwreg::RegisterBase<TempMonCtl1, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempMonCtl1>(0x04); }

    DEF_FIELD(9, 0, period);
};

class TempMonCtl2 : public hwreg::RegisterBase<TempMonCtl2, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempMonCtl2>(0x08); }

    DEF_FIELD(25, 16, filt_interval);
    DEF_FIELD(9, 0, sen_interval);
};

class TempMsrCtl0 : public hwreg::RegisterBase<TempMsrCtl0, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempMsrCtl0>(0x38); }

    static constexpr uint32_t kSample1       = 0;
    static constexpr uint32_t kSample2       = 1;
    static constexpr uint32_t kSample4Drop2  = 2;
    static constexpr uint32_t kSample6Drop2  = 3;
    static constexpr uint32_t kSample10Drop2 = 4;
    static constexpr uint32_t kSample18Drop2 = 5;

    DEF_FIELD(11, 9, msrctl3);
    DEF_FIELD(8, 6, msrctl2);
    DEF_FIELD(5, 3, msrctl1);
    DEF_FIELD(2, 0, msrctl0);
};

class TempAhbPoll : public hwreg::RegisterBase<TempAhbPoll, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempAhbPoll>(0x40); }
};

class TempAhbTimeout : public hwreg::RegisterBase<TempAhbTimeout, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempAhbTimeout>(0x44); }
};

class TempAdcPnp : public hwreg::RegisterBase<TempAdcPnp, uint32_t> {
public:
    static auto Get(uint32_t index) { return hwreg::RegisterAddr<TempAdcPnp>(0x48 + (index * 4)); }
};

class TempAdcMux : public hwreg::RegisterBase<TempAdcMux, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempAdcMux>(0x54); }
};

class TempAdcEn : public hwreg::RegisterBase<TempAdcEn, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempAdcEn>(0x60); }
};

class TempPnpMuxAddr : public hwreg::RegisterBase<TempPnpMuxAddr, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempPnpMuxAddr>(0x64); }
};

class TempAdcMuxAddr : public hwreg::RegisterBase<TempAdcMuxAddr, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempAdcMuxAddr>(0x68); }
};

class TempAdcEnAddr : public hwreg::RegisterBase<TempAdcEnAddr, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempAdcEnAddr>(0x74); }
};

class TempAdcValidAddr : public hwreg::RegisterBase<TempAdcValidAddr, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempAdcValidAddr>(0x78); }
};

class TempAdcVoltAddr : public hwreg::RegisterBase<TempAdcVoltAddr, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempAdcVoltAddr>(0x7c); }
};

class TempRdCtrl : public hwreg::RegisterBase<TempRdCtrl, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempRdCtrl>(0x80); }

    static constexpr uint32_t kValidVoltageSame = 0;
    static constexpr uint32_t kValidVoltageDiff = 1;

    DEF_BIT(0, diff);
};

class TempAdcValidMask : public hwreg::RegisterBase<TempAdcValidMask, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempAdcValidMask>(0x84); }

    static constexpr uint32_t kActiveLow  = 0;
    static constexpr uint32_t kActiveHigh = 1;

    DEF_BIT(5, polarity);
    DEF_FIELD(4, 0, pos);
};

class TempAdcVoltageShift : public hwreg::RegisterBase<TempAdcVoltageShift, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempAdcVoltageShift>(0x88); }

    DEF_FIELD(4, 0, shift);
};

class TempAdcWriteCtrl : public hwreg::RegisterBase<TempAdcWriteCtrl, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempAdcWriteCtrl>(0x8c); }

    DEF_BIT(1, mux_write_en);
    DEF_BIT(0, pnp_write_en);
};

class TempMsr : public hwreg::RegisterBase<TempMsr, uint32_t> {
public:
    static auto Get(uint32_t index) { return hwreg::RegisterAddr<TempMsr>(0x90 + (index * 4)); }

    DEF_BIT(15, valid);
    DEF_FIELD(11, 0, reading);
};

class TempSpare : public hwreg::RegisterBase<TempSpare, uint32_t> {
public:
    static auto Get(uint32_t index) { return hwreg::RegisterAddr<TempSpare>(0xf0 + (index * 4)); }
};

// The following classes represent the temperature calibration fuses.
class TempCalibration0 : public hwreg::RegisterBase<TempCalibration0, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempCalibration0>(0x180); }

    DEF_FIELD(31, 26, slope);
    DEF_FIELD(25, 17, vts0);
    DEF_FIELD(16, 8, vts1);
    DEF_BIT(7, slope_sign);
    DEF_FIELD(6, 1, temp_offset);
    DEF_BIT(0, calibration_en);

    uint32_t get_vts0() const { return vts0() + kVtsOffset; }
    uint32_t get_vts1() const { return vts1() + kVtsOffset; }

private:
    static constexpr uint32_t kVtsOffset = 3350;
};

class TempCalibration1 : public hwreg::RegisterBase<TempCalibration1, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempCalibration1>(0x184); }

    DEF_FIELD(31, 22, adc_gain);
    DEF_FIELD(21, 12, adc_offset);
    DEF_BIT(2, id);

    int32_t get_adc_gain() const { return adc_gain() - kAdcCalOffset; }
    int32_t get_adc_offset() const { return adc_offset() - kAdcCalOffset; }

private:
    static constexpr int32_t kAdcCalOffset = 512;
};

class TempCalibration2 : public hwreg::RegisterBase<TempCalibration2, uint32_t> {
public:
    static auto Get() { return hwreg::RegisterAddr<TempCalibration2>(0x188); }

    DEF_FIELD(31, 23, vts2);
    DEF_FIELD(22, 14, vts3);

    uint32_t get_vts2() const { return vts2() + kVtsOffset; }
    uint32_t get_vts3() const { return vts3() + kVtsOffset; }

private:
    static constexpr uint32_t kVtsOffset = 3350;
};

}  // namespace thermal