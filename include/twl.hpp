#ifndef TWL_HPP__
#define TWL_HPP__

#include "3ds.h"
#include <string>
//#include "types.h"

// Break out the TIDLOW
#define TIDLOW(x)   (x & 0x00000000FFFFFFFFL) 
// Break out the TIDHIGH, not sure this is needed
#define TIDHIGH(x) ((x & 0xFFFFFFFF00000000L) >> 32)
// break out the App Type 
#define TIDTYPE(x) ((x & 0x0000FFFF00000000L) >> 32)

#define CONTENT_MAX 11
#define OFFSET_BANNER 0
#define OFFSET_HEADER 0x4020
#define OFFSET_FOOTER 0x4130
#define OFFSET_TMD 0x4630
#define SIZE_BANNER 0x4000
#define SIZE_HEADER 0xF0
#define SIZE_FOOTER 0x4E0

extern const char* content_namelist[];


#define SIZE_FOOTER 0x4E0
#define SIZE_CTCERTBIN 0x19E

typedef u8 sha256_hash[0x20];

typedef struct ecc_point_t
{
	uint8_t r[0x1e];
	uint8_t s[0x1e];
} __attribute__((packed)) ecc_point_t;

typedef struct ecc_cert_t
{
	struct {
		uint32_t type;
		ecc_point_t val;
		uint8_t padding[0x40];
	} sig;
	char issuer[0x40];
	uint32_t key_type;
	char key_id[0x40];
	uint32_t unk;
	ecc_point_t pubkey;
	uint8_t padding2[0x3c];
} __attribute__((packed)) ecc_cert_t;

typedef struct footer_t
{
	sha256_hash banner_hash;
	sha256_hash hdr_hash;
	sha256_hash tmd_hash;
	sha256_hash content_hash[8];
	sha256_hash savedata_hash;
	sha256_hash bannersav_hash;
	ecc_point_t sig;
	ecc_cert_t ap;
	ecc_cert_t ct;
} footer_t;


Result import_tad(std::string TADfile);
Result export_tad(std::string dir, u64 uTID);

void getSection(u8 *dsiware_pointer, u32 section_size, u8 *key, u8 *output);
void placeSection(u8 *dsiware_pointer, u8 *section, u32 section_size, u8 *key, u8 *key_cmac);
Result doSigning(u8 *ctcert_bin, footer_t *footer);
void fixcrc16(u16 *checksum, u8 *message, u32 len);



#endif
