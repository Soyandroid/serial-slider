#ifndef _MPR121_CONFIG_H
#define _MPR121_CONFIG_H

#include "mpr121.h"

// Thresholds
#define MPR121CONF_TTH	32	///< Electrode touch threshold
#define MPR121CONF_RTH	32	///< Electrode release threshold
// De-bounce counts
#define MPR121CONF_DR	4	///< Debounce number for release
#define MPR121CONF_DT	0	///< Debounce number for touch
// AFE Configurations
#define MPR121CONF_FFI	MPR121_FFI_6 ///< First Filter Iterations
#define MPR121CONF_CDC	16 ///< Charge Discharge Current
#define MPR121CONF_CDT	MPR121_CDT_500NS ///< Charge Discharge Time
#define MPR121CONF_SFI	MPR121_SFI_4 ///< Second Filter Iterations
#define MPR121CONF_ESI	MPR121_ESI_1MS ///< Electrode Sample Interval
// ECR Configurations
#define MPR121CONF_CL		MPR121_CL_INIT1 ///< Calibration Lock
#define MPR121CONF_ELEPROX	MPR121_ELEPROX_0  ///< proximity detection electrodes
#define MPR121CONF_ELE		8 ///< touch detection electrodes
// Baseline filtering control
#define MPR121CONF_MHDR	1	///< Rising Maximum Half Delta
#define MPR121CONF_NHDR	8	///< Rising Noise Half Delta
#define MPR121CONF_NCLR	1	///< Rising Noise Count Limit
#define MPR121CONF_FDLR	0	///< Rising Filter Delay Count Limit
#define MPR121CONF_MHDF	1	///< Falling Maximum Half Delta
#define MPR121CONF_NHDF	1	///< Falling Noise Half Delta
#define MPR121CONF_NCLF	8	///< Falling Noise Count Limit
#define MPR121CONF_FDLF	4	///< Falling Filter Delay Count Limit
#define MPR121CONF_NHDT	0	///< Touched Noise Half Delta
#define MPR121CONF_NCLT	0	///< Touched Noise Count Limit
#define MPR121CONF_FDLT	0	///< Touched Filter Delay Count Limit
// Auto configuration settings
#define MPR121CONF_USL		156	///< Up-Side Limit
#define MPR121CONF_LSL		101	///< Low-Side Limit
#define MPR121CONF_TL		140	///< Target Level
#define MPR121CONF_AFES		MPR121CONF_FFI	///< Same as FFI
#define MPR121CONF_RETRY	MPR121_RETRY_0	///< Number of retries
#define MPR121CONF_BVA		MPR121CONF_CL	///< Same as CL
#define MPR121CONF_ARE		1	///4< Auto-reconfiguration enable
#define MPR121CONF_ACE		1	///< Auto-configuration enable
#define MPR121CONF_SCTS		1	///< Skip Charge Time Search
#define MPR121CONF_ACFIE	0	///< Auto-configuration fail interrupt enable
#define MPR121CONF_ARFIE	0	///< Auto-reconfiguration fail interrupt enable
#define MPR121CONF_OORIE	0	///< Out-of-range interrupt enable

#endif
