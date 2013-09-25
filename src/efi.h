/*
 * Copyright (C) 2001, 2003 Dell Computer Corporation <Matt_Domsch@dell.com>
 * Copyright (C) 2012-2013 Gary Lin <glin@suse.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 *
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */

#ifndef EFI_H
#define EFI_H

/*
 * Extensible Firmware Interface
 * Based on 'Extensible Firmware Interface Specification'
 *      version 1.02, 12 December, 2000
 */
#include <stdint.h>
#include <dirent.h>

#define BITS_PER_LONG (sizeof(unsigned long) * 8)

#define EFI_ERROR(x) ((x) | (1L << (BITS_PER_LONG - 1)))

#define EFI_SUCCESS		0
#define EFI_LOAD_ERROR          EFI_ERROR(1)
#define EFI_INVALID_PARAMETER   EFI_ERROR(2)
#define EFI_UNSUPPORTED		EFI_ERROR(3)
#define EFI_BAD_BUFFER_SIZE     EFI_ERROR(4)
#define EFI_BUFFER_TOO_SMALL	EFI_ERROR(5)
#define EFI_NOT_FOUND           EFI_ERROR(14)
#define EFI_OUT_OF_RESOURCES    EFI_ERROR(15)

/*******************************************************
 * Boot Option Attributes
 *******************************************************/
#define LOAD_OPTION_ACTIVE 0x00000001

/******************************************************
 * EFI Variable Attributes
 ******************************************************/
#define EFI_VARIABLE_NON_VOLATILE 0x0000000000000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS 0x0000000000000002
#define EFI_VARIABLE_RUNTIME_ACCESS 0x0000000000000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD 0x0000000000000008
#define EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS 0x0000000000000010
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS 0x0000000000000020
#define EFI_VARIABLE_APPEND_WRITE       0x0000000000000040


typedef struct {
	uint8_t  b[16];
} efi_guid_t;

#define EFI_GUID(a,b,c,d0,d1,d2,d3,d4,d5,d6,d7) \
((efi_guid_t) \
{{ (a) & 0xff, ((a) >> 8) & 0xff, ((a) >> 16) & 0xff, ((a) >> 24) & 0xff, \
  (b) & 0xff, ((b) >> 8) & 0xff, \
  (c) & 0xff, ((c) >> 8) & 0xff, \
  (d0), (d1), (d2), (d3), (d4), (d5), (d6), (d7) }})


/******************************************************
 * GUIDs
 ******************************************************/
#define DEVICE_PATH_PROTOCOL \
EFI_GUID( 0x09576e91, 0x6d3f, 0x11d2, 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b)
#define EFI_GLOBAL_VARIABLE \
EFI_GUID( 0x8BE4DF61, 0x93CA, 0x11d2, 0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C)
#define EDD10_HARDWARE_VENDOR_PATH_GUID \
EFI_GUID( 0xCF31FAC5, 0xC24E, 0x11d2, 0x85, 0xF3, 0x00, 0xA0, 0xC9, 0x3E, 0xC9, 0x3B)
#define BLKX_UNKNOWN_GUID \
EFI_GUID( 0x47c7b225, 0xc42a, 0x11d2, 0x8e, 0x57, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b)
#define DIR_UNKNOWN_GUID \
EFI_GUID( 0x47c7b227, 0xc42a, 0x11d2, 0x8e, 0x57, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b)
#define ESP_UNKNOWN_GUID \
EFI_GUID( 0x47c7b226, 0xc42a, 0x11d2, 0x8e, 0x57, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b)
#define EFI_IMAGE_SECURITY_DATABASE_GUID \
EFI_GUID( 0xd719b2cb, 0x3d3a, 0x4596, 0xa3, 0xbc, 0xda, 0xd0, 0x0e, 0x67, 0x65, 0x6f)

static inline int
efi_guidcmp(efi_guid_t left, efi_guid_t right)
{
	return memcmp(&left, &right, sizeof (efi_guid_t));
}


typedef unsigned long efi_status_t;
typedef uint8_t  efi_bool_t;
typedef uint16_t efi_char16_t;		/* UNICODE character */

typedef struct _efi_variable_t {
        const char   *VariableName;
        efi_guid_t    VendorGuid;
        unsigned long DataSize;
        uint8_t      *Data;
        uint32_t      Attributes;
} __attribute__((packed)) efi_variable_t;


typedef struct {
	uint8_t  type;
	uint8_t  subtype;
	uint16_t length;
	uint8_t  data[1];
} __attribute__((packed)) EFI_DEVICE_PATH;

typedef struct {
	uint32_t attributes;
	uint16_t file_path_list_length;
	efi_char16_t description[1];
	EFI_DEVICE_PATH _unused_file_path_list[1];
} __attribute__((packed)) EFI_LOAD_OPTION;


typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint32_t _HID;
	uint32_t _UID;
} __attribute__((packed)) ACPI_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	efi_guid_t vendor_guid;
	uint8_t data[1];
} __attribute__((packed)) VENDOR_DEVICE_PATH;

#define EDD10_HARDWARE_VENDOR_PATH_LENGTH 24

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint8_t function;
	uint8_t device;
} __attribute__((packed)) PCI_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint8_t  socket;
} __attribute__((packed)) PCCARD_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint32_t memory_type;
	uint64_t start;
	uint64_t end;
} __attribute__((packed)) MEMORY_MAPPED_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint32_t controller;
} __attribute__((packed)) CONTROLLER_DEVICE_PATH;


typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint16_t id;
	uint16_t lun;
} __attribute__((packed)) SCSI_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint8_t  primary_secondary;
	uint8_t  slave_master;
	uint16_t lun;
} __attribute__((packed)) ATAPI_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint32_t reserved;
	uint64_t wwn;
	uint64_t lun;
} __attribute__((packed)) FIBRE_CHANNEL_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint32_t reserved;
	uint64_t guid;
} __attribute__((packed)) I1394_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint8_t  port;
	uint8_t  endpoint;
} __attribute__((packed)) USB_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint16_t vendor;
	uint16_t product;
	uint8_t  class;
	uint8_t  subclass;
	uint8_t  protocol;
} __attribute__((packed)) USB_CLASS_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint32_t tid;
} __attribute__((packed)) I2O_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint8_t macaddr[32];
	uint8_t iftype;
} __attribute__((packed)) MAC_ADDR_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint32_t local_ip;
	uint32_t remote_ip;
	uint16_t local_port;
	uint16_t remote_port;
	uint16_t protocol;
	uint8_t  static_addr;
} __attribute__((packed)) IPv4_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint8_t  local_ip[16];
	uint8_t  remote_ip[16];
	uint16_t local_port;
	uint16_t remote_port;
	uint16_t protocol;
	uint8_t  static_addr;
} __attribute__((packed)) IPv6_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint32_t reserved;
	uint64_t node_guid;
	uint64_t ioc_guid;
	uint64_t id;
} __attribute__((packed)) INFINIBAND_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint32_t reserved;
	uint64_t baud_rate;
	uint8_t  data_bits;
	uint8_t  parity;
	uint8_t  stop_bits;
} __attribute__((packed)) UART_DEVICE_PATH;


typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint32_t part_num;
	uint64_t start;
	uint64_t size;
	uint8_t  signature[16];
	uint8_t  mbr_type;
	uint8_t  signature_type;
	uint8_t  padding[6]; /* Emperically needed */
} __attribute__((packed)) HARDDRIVE_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint32_t boot_entry;
	uint64_t start;
	uint64_t size;
} __attribute__((packed)) CDROM_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	efi_char16_t path_name[1];
} __attribute__((packed)) FILE_PATH_DEVICE_PATH;


typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	efi_guid_t guid;
} __attribute__((packed)) MEDIA_PROTOCOL_DEVICE_PATH;

typedef struct {
	uint8_t type;
	uint8_t subtype;
	uint16_t length;
	uint16_t device_type;
	uint16_t status_flag;
	uint8_t  description[1];
} __attribute__((packed)) BIOS_BOOT_SPEC_DEVICE_PATH;

typedef struct {
	uint8_t  type;
	uint8_t  subtype;
	uint16_t length;
} __attribute__((packed)) END_DEVICE_PATH;


struct efivar_kernel_calls {
        efi_status_t (*read)(const char *name, efi_variable_t *var);
        efi_status_t (*edit)(const char *name, efi_variable_t *var);
        efi_status_t (*create)(efi_variable_t *var);
        efi_status_t (*delete)(efi_variable_t *var);
        char *path;
};


/* Used for ACPI _HID */
#define EISAID_PNP0A03 0xa0341d0

/* Exported functions */
extern char * efi_guid_unparse(efi_guid_t *guid, char *out);

extern efi_status_t test_variable (efi_variable_t *var);
extern efi_status_t read_variable (efi_variable_t *var);
extern efi_status_t edit_variable (efi_variable_t *var);
extern efi_status_t delete_variable (efi_variable_t *var);
extern efi_status_t edit_protected_variable (efi_variable_t *var);

extern int efichar_strlen (const efi_char16_t *p, int max);
extern unsigned long efichar_from_char (efi_char16_t *dest, const char *src, size_t dest_len);
extern unsigned long efichar_to_char (char *dest, const efi_char16_t *src, size_t dest_len);

extern int variable_to_name(efi_variable_t *var, char *name);

#endif /* EFI_H */
