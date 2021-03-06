// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

// PERI_CRG registers
#define PERI_CRG_CLK_EN4                        0x40

#define PERI_CRG_RSTEN4                         0x90
#define PERI_CRG_RSTDIS4                        0x94
#define PERI_CRG_ISODIS                         0x148

#define PERI_CRG_GT_CLK_USB3OTG_REF             (1 << 0)
#define PERI_CRG_GT_ACLK_USB3OTG                (1 << 1)

#define PERI_CRG_IP_RST_USB3OTGPHY_POR          (1 << 3)
#define PERI_CRG_IP_RST_USB3OTG                 (1 << 5)
#define PERI_CRG_IP_RST_USB3OTG_32K             (1 << 6)
#define PERI_CRG_IP_RST_USB3OTG_AHBIF           (1 << 7)
#define PERI_CRG_IP_RST_USB3OTG_MUX             (1 << 8)
#define PERI_CRG_ISODIS_REFCLK_ISO_EN           (1 << 25)

#define PERI_CRG_UFS_ISODIS                     0x424
#define PERI_CRG_UFS_ISOEN                      0x420
#define PERI_CRG_UFS_RSTEN3                     0x84
#define PERI_CRG_UFS_RSTDIS3                    0x88
#define PERI_CRG_UFS_CLKDIV16                   0xE8
#define PERI_CRG_UFS_CLKDIV17                   0xEC

#define PERI_CRG_UFS_IO                         (1 << 14)
#define PERI_CRG_UFS_RST                        (1 << 12)
#define PERI_CRG_UFS_ARST                       (1 << 7)

// PCTRL registers
#define PCTRL_CTRL3                             0x10
#define PCTRL_CTRL24                            0x064

#define PCTRL_CTRL3_USB_TCXO_EN                 (1 << 1)
#define PCTRL_CTRL3_MSK_START                   16
#define PCTRL_CTRL24_SC_CLK_USB3PHY_3MUX1_SEL   (1 << 25)

//UFS Sysctrl registers
#define UFS_SCTRL_PSW_PWR_CTRL                  0x04
#define UFS_SCTRL_PHY_ISO_EN                    0x08
#define UFS_SCTRL_HC_LP_CTRL                    0x0C
#define UFS_SCTRL_PHY_CLK_CTRL                  0x10
#define UFS_SCTRL_PSW_CLK_CTRL                  0x14
#define UFS_SCTRL_CLK_GATE_BYPASS               0x18
#define UFS_SCTRL_RST_CTRL_EN                   0x1C
#define UFS_SCTRL_SYSCTRL                       0x5C
#define UFS_SCTRL_DEV_RST_CTRL                  0x60

#define UFS_SCTRL_CLK_FREQ_CFG                  0x39
#define UFS_SCTRL_REF_CLK_SEL_MASK              (3 << 8)
#define UFS_SCTRL_CLK_FREQ_MASK                 0xFF
#define UFS_SCTRL_CLK_GATE_BYPASS_MASK          0x3F
#define UFS_SCTRL_SYSCTRL_BYPASS_MASK           (0x3F << 16)
#define UFS_SCTRL_REF_CLK_SRC_SEl               (1 << 0)
#define UFS_SCTRL_REF_CLK_ISO_EN                (1 << 16)
#define UFS_SCTRL_REF_CLK_EN                    (1 << 24)
#define UFS_SCTRL_PSW_MTCMOS_EN                 (1 << 0)
#define UFS_SCTRL_PSW_CLK_EN                    (1 << 4)
#define UFS_SCTRL_PSW_ISO_CTRL                  (1 << 16)
#define UFS_SCTRL_PHY_ISO_CTRL                  (1 << 0)
#define UFS_SCTRL_LP_ISOL_EN                    (1 << 16)
#define UFS_SCTRL_LP_RSTN                       (1 << 0)
#define UFS_SCTRL_PWR_READY                     (1 << 8)
#define UFS_SCTRL_MASK_DEV_RST                  (1 << 16)
#define UFS_SCTRL_MASK_UFS_RST                  (1 << 0)

// USBOTG_BC registers
#define USB3OTG_CTRL0                           0x00
#define USB3OTG_CTRL1                           0x04
#define USB3OTG_CTRL2                           0x08
#define USB3OTG_CTRL3                           0x0C
#define USB3OTG_CTRL4                           0x10
#define USB3OTG_CTRL5                           0x14
#define USB3OTG_CTRL6                           0x18
#define USB3OTG_CTRL7                           0x1C
#define USB3OTG_STS0                            0x20
#define USB3OTG_STS1                            0x24
#define USB3OTG_STS2                            0x28
#define USB3OTG_STS3                            0x2C
#define BC_CTRL0                                0x30
#define BC_CTRL1                                0x34
#define BC_CTRL2                                0x38
#define BC_STS0                                 0x3C
#define RAM_CTRL                                0x40
#define USB3OTG_STS4                            0x44
#define USB3PHY_CTRL                            0x48
#define USB3PHY_STS                             0x4C
#define USB3OTG_PHY_CR_STS                      0x50
#define USB3OTG_PHY_CR_CTRL                     0x54
#define USB3_RES                                0x58

// USB3OTG_CTRL0 BITS
#define USB3OTG_CTRL0_ABB_GT_EN                 (1 << 15)

// USB3OTG_CTRL2 bits
# define USB3OTG_CTRL2_POWERDOWN_HSP            (1 << 0)
# define USB3OTG_CTRL2_POWERDOWN_SSP            (1 << 1)

// USB3OTG_CTRL3 bits
#define USB3OTG_CTRL3_VBUSVLDEXT                (1 << 6)
#define USB3OTG_CTRL3_VBUSVLDEXTSEL             (1 << 5)

// USB3OTG_CTRL7 bits
#define USB3OTG_CTRL7_REF_SSP_EN                (1 << 16)

// LDO3 Enable Reg
#define LDO3_ENABLE_REG                         (0x60 << 2)
#define LDO3_ENABLE_BIT                         (0x2)

// DSI0
#define PERRSTDIS3                              0x088
#define TXDPHY0_CFG_OFFSET                      0x30
#define TXDPHY0_CFG_BIT                         28
#define TXDPHY0_REF_OFFSET                      0x30
#define TXDPHY0_REF_BIT                         29
#define PCLK_GATE_DSI0_OFFSET                   0x50
#define PCLK_GATE_DSI0_BIT                      28

#define CLKGATE_SEPARATED_ENABLE                0x0
#define CLKGATE_SEPARATED_DISABLE               0x4
#define CLKGATE_SEPARATED_STATUS                0x8
