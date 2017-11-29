//
// PROJECT:         Aspia Remote Desktop
// FILE:            base/devices/physical_drive_enumerator.h
// LICENSE:         Mozilla Public License Version 2.0
// PROGRAMMERS:     Dmitry Chapyshev (dmitry@aspia.ru)
//

#ifndef _ASPIA_BASE__DEVICES__PHYSICAL_DRIVE_ENUMERATOR_H
#define _ASPIA_BASE__DEVICES__PHYSICAL_DRIVE_ENUMERATOR_H

#include "base/devices/device.h"

#include <setupapi.h>
#include <winioctl.h>

namespace aspia {

class PhysicalDriveEnumerator
{
public:
    PhysicalDriveEnumerator();
    ~PhysicalDriveEnumerator();

    bool IsAtEnd() const;
    void Advance();

    enum class BusType
    {
        UNKNOWN             = 0,
        SCSI                = 1,
        ATAPI               = 2,
        ATA                 = 3,
        IEEE1394            = 4,
        SSA                 = 5,
        FIBRE               = 6,
        USB                 = 7,
        RAID                = 8,
        ISCSI               = 9,
        SAS                 = 10,
        SATA                = 11,
        SD                  = 12,
        MMC                 = 13,
        VIRTUAL             = 14,
        FILE_BACKED_VIRTUAL = 15
    };

    enum class TransferMode
    {
        UNKNOWN       = 0,
        PIO           = 1,
        PIO_DMA       = 2,
        ULTRA_DMA_133 = 3,
        ULTRA_DMA_100 = 4,
        ULTRA_DMA_66  = 5,
        ULTRA_DMA_44  = 6,
        ULTRA_DMA_33  = 7,
        ULTRA_DMA_25  = 8,
        ULTRA_DMA_16  = 9,
        SATA_600      = 10,
        SATA_300      = 11,
        SATA_150      = 12
    };

    enum Features
    {
        FEATURE_48BIT_LBA                     = 1,
        FEATURE_ADVANCED_POWER_MANAGEMENT     = 2,
        FEATURE_AUTOMATIC_ACOUSTIC_MANAGEMENT = 4,
        FEATURE_SMART                         = 8,
        FEATURE_SMART_ERROR_LOGGING           = 16,
        FEATURE_SMART_SELF_TEST               = 32,
        FEATURE_STREAMING                     = 64,
        FEATURE_GENERAL_PURPOSE_LOGGING       = 128,
        FEATURE_SECURITY_MODE                 = 256,
        FEATURE_POWER_MANAGEMENT              = 512,
        FEATURE_WRITE_CACHE                   = 1024,
        FEATURE_READ_LOCK_AHEAD               = 2048,
        FEATURE_HOST_PROTECTED_AREA           = 4096,
        FEATURE_RELEASE_INTERRUPT             = 8192,
        FEATURE_POWER_UP_IN_STANDBY           = 16384,
        FEATURE_DEVICE_CONFIGURATION_OVERLAY  = 32768,
        FEATURE_SERVICE_INTERRUPT             = 65536,
        FEATURE_NATIVE_COMMAND_QUEUING        = 131072,
        FEATURE_TRIM                          = 262144
    };

    std::string GetModelNumber() const;
    std::string GetSerialNumber() const;
    std::string GetFirmwareRevision() const;
    BusType GetBusType() const;
    TransferMode GetCurrentTransferMode() const;
    int GetRotationRate() const; // in RPM.
    uint64_t GetDriveSize() const;
    uint32_t GetBufferSize() const; // in bytes.
    int GetMultisectors() const;
    int GetECCSize() const;
    bool IsRemovable() const;
    int64_t GetCylindersNumber() const;
    uint32_t GetTracksPerCylinder() const;
    uint32_t GetSectorsPerTrack() const;
    uint32_t GetBytesPerSector() const;
    uint16_t GetHeadsNumber() const;
    uint64_t GetSupportedFeatures() const;
    uint64_t GetEnabledFeatures() const;

private:
#pragma pack (push, id_data, 1)
    struct IdentifyData
    {
        uint16_t general_configuration;          // 0
        uint16_t number_of_cylinders;            // 1
        uint16_t spec_config;                    // 2
        uint16_t number_of_heads;                // 3
        uint16_t unformatted_bytes_per_track;    // 4
        uint16_t unformatted_bytes_per_sector;   // 5
        uint16_t sectors_per_track;              // 6
        uint16_t vendor_unique1[3];              // 7-9
        char serial_number[20];                  // 10-19
        uint16_t buffer_type;                    // 20
        uint16_t buffer_size;                    // 21
        uint16_t ecc_size;                       // 22
        char firmware_revision[8];               // 23-26
        char model_number[40];                   // 27-46
        uint8_t maximum_block_transfer;          // 47
        uint8_t vendor_unique2;
        uint16_t double_word_io;                 // 48
        uint16_t capabilities1;                  // 49
        uint16_t capabilities2;                  // 50
        uint8_t vendor_unique3;                  // 51
        uint8_t pio_cycle_timing_mode;
        uint8_t vendor_unique4;                  // 52
        uint8_t dma_cycle_timing_mode;
        uint16_t bs;                             // 53
        uint16_t number_of_current_cylinders;    // 54
        uint16_t number_of_current_heads;        // 55
        uint16_t current_sectors_per_track;      // 56
        uint32_t current_sector_capacity;        // 57, 58
        uint16_t current_multi_sector_setting;   // 59
        uint32_t user_addressable_sectors;       // 60, 61
        uint16_t single_word_dma;                // 62
        uint16_t multi_word_dma;                 // 63
        uint8_t pio_mode;                        // 64
        uint8_t reserved1;
        uint16_t minimum_mwx_fer_cycle_time;     // 65
        uint16_t recommended_mwx_fer_cycle_time; // 66
        uint16_t minimum_pio_cycle_time;         // 67
        uint16_t minimum_pio_cycle_time_iordy;   // 68
        uint16_t reserved2[2];                   // 69, 70
        uint16_t release_time_overlapped;        // 71
        uint16_t release_time_service_command;   // 72
        uint16_t major_revision;                 // 73
        uint16_t minor_revision;                 // 74
        uint16_t reserved3;                      // 75
        uint16_t sata_capabilities;              // 76
        uint16_t reserved4;                      // 77
        uint16_t sata_features_suported;         // 78
        uint16_t sata_features_enabled;          // 79
        uint16_t major_version;                  // 80
        uint16_t minor_version;                  // 81
        uint16_t command_set_support1;           // 82
        uint16_t command_set_support2;           // 83
        uint16_t command_set_support3;           // 84
        uint16_t command_set_enabled1;           // 85
        uint16_t command_set_enabled2;           // 86
        uint16_t command_set_default;            // 87
        uint16_t ultra_dma_mode;                 // 88
        uint16_t reserved5;                      // 89
        uint16_t reserved6;                      // 90
        uint16_t reserved7;                      // 91
        uint16_t reserved8;                      // 92
        uint16_t reserved9;                      // 93
        uint16_t reserved10;                     // 94
        uint16_t reserved11;                     // 95
        uint16_t reserved12;                     // 96
        uint16_t reserved13;                     // 97
        uint32_t reserved14;                     // 98, 99
        uint64_t reserved15;                     // 100-103
        uint16_t reserved16;                     // 104
        uint16_t reserved17;                     // 105
        uint16_t reserved18;                     // 106
        uint16_t reserved19;                     // 107
        uint16_t reserved20;                     // 108
        uint16_t reserved21;                     // 109
        uint16_t reserved22;                     // 110
        uint16_t reserved23;                     // 111
        uint16_t reserved24[4];                  // 112-115
        uint16_t reserved25;                     // 116
        uint32_t reserved26;                     // 117, 118
        uint16_t reserved27[8];                  // 119-126
        uint16_t special_functions_enabled;      // 127
        uint16_t reserved28;                     // 128
        uint16_t reserved29[31];                 // 129-159
        uint16_t reserved30;                     // 160
        uint16_t reserved31[7];                  // 161-167
        uint16_t reserved32;                     // 168
        uint16_t data_set_management;            // 169
        uint16_t reserved33[4];                  // 170-173
        uint16_t reserved34[2];                  // 174, 175
        char reserved35[60];                     // 176-205
        uint16_t reserved36;                     // 206
        uint16_t reserved37[2];                  // 207, 208
        uint16_t reserved38;                     // 209
        uint32_t reserved39;                     // 210, 211
        uint32_t reserved40;                     // 212, 213
        uint16_t nv_cache_capabilities;          // 214
        uint32_t nv_cache_logical_blocks_size;   // 215, 216
        uint16_t rotation_rate;                  // 217
        uint16_t reserved41;                     // 218
        uint16_t nv_cache_options1;              // 219
        uint16_t nv_cache_options2;              // 220
        uint16_t reserved42;                     // 221
        uint16_t reserved43;                     // 222
        uint16_t reserved44;                     // 223
        uint16_t reserved45[10];                 // 224-233
        uint16_t reserved46;                     // 234
        uint16_t reserved47;                     // 235
        uint16_t reserved48[19];                 // 236-254
        uint16_t reserved49;                     // 255
    };
#pragma pack (pop, id_data)

    bool GetDriveInfo(DWORD device_number) const;
    uint16_t GetMajorVersion() const;

    HDEVINFO device_info_;
    mutable DWORD device_index_ = 0;
    mutable Device device_;
    mutable IdentifyData id_data_;
    mutable DISK_GEOMETRY geometry_;

    DISALLOW_COPY_AND_ASSIGN(PhysicalDriveEnumerator);
};

} // namespace aspia

#endif // _ASPIA_BASE__DEVICES__PHYSICAL_DRIVE_ENUMERATOR_H
