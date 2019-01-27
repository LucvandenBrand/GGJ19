
//{{BLOCK(playerSprite)

//======================================================================
//
//	playerSprite, 16x16@8, 
//	+ palette 256 entries, not compressed
//	+ 4 tiles Metatiled by 2x2 not compressed
//	Total size: 512 + 256 = 768
//
//	Time-stamp: 2019-01-27, 13:14:36
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const unsigned int playerSpriteTiles[64] __attribute__((aligned(4))) __attribute__((visibility("hidden")))=
{
	0x00000000,0x19191900,0x00000000,0x190B1919,0x00000000,0x0B090B19,0x00000000,0x0B0B0B18,
	0x00000000,0x090B0B17,0x00000000,0x0B0B1700,0x00000000,0x17170000,0x00000000,0x0E0E0C0C,
	0x00181819,0x00000000,0x18191919,0x00000000,0x1819090B,0x00000000,0x180B0B0B,0x00000000,
	0x170B0B09,0x00000000,0x00170B0B,0x00000000,0x00001717,0x00000000,0x0C0C0E0E,0x00000000,
	0x00000000,0x0C0C0C0B,0x0B000000,0x0E0E0C00,0x0B000000,0x0C0C0C00,0x0B000000,0x0E0E0C00,
	0x00000000,0x0C0C0000,0x00000000,0x000D0000,0x00000000,0x000C0000,0x00000000,0x000B0B00,
	0x0B0C0C0C,0x00000000,0x000C0E0E,0x0000000B,0x000C0C0C,0x0000000B,0x000C0E0E,0x0000000B,
	0x00000C0C,0x00000000,0x00000D00,0x00000000,0x00000C00,0x00000000,0x000B0B00,0x00000000,
};

const unsigned short playerSpritePal[256] __attribute__((aligned(4))) __attribute__((visibility("hidden")))=
{
	0x0000,0x7FFF,0x5EF7,0x4631,0x739C,0x4631,0x1237,0x092E,
	0x0DB3,0x0047,0x1237,0x5F7F,0x28E1,0x1460,0x7F06,0x1D2B,
	0x0D35,0x159D,0x0465,0x4EF4,0x4270,0x35F9,0x1D55,0x1DF2,
	0x16FA,0x1BBF,0x0047,0x06E0,0x0465,0x0465,0x0465,0x0465,
	0x0465,0x0465,0x1084,0x1084,0x1084,0x1084,0x1084,0x1084,
	0x14A5,0x14A5,0x14A5,0x14A5,0x14A5,0x14A5,0x14A5,0x14A5,
	0x18C6,0x18C6,0x18C6,0x18C6,0x18C6,0x18C6,0x18C6,0x18C6,
	0x1CE7,0x1CE7,0x1CE7,0x1CE7,0x1CE7,0x1CE7,0x1CE7,0x1CE7,

	0x2108,0x2108,0x2108,0x2108,0x2108,0x2108,0x2108,0x2108,
	0x2529,0x2529,0x2529,0x2529,0x2529,0x2529,0x2529,0x2529,
	0x294A,0x294A,0x294A,0x294A,0x294A,0x294A,0x294A,0x294A,
	0x2D6B,0x2D6B,0x2D6B,0x2D6B,0x2D6B,0x2D6B,0x2D6B,0x2D6B,
	0x318C,0x318C,0x318C,0x318C,0x318C,0x318C,0x318C,0x318C,
	0x35AD,0x35AD,0x35AD,0x35AD,0x35AD,0x35AD,0x35AD,0x35AD,
	0x39CE,0x39CE,0x39CE,0x39CE,0x39CE,0x39CE,0x39CE,0x39CE,
	0x3DEF,0x3DEF,0x3DEF,0x3DEF,0x3DEF,0x3DEF,0x3DEF,0x3DEF,

	0x4210,0x4210,0x4210,0x4210,0x4210,0x4210,0x4210,0x4210,
	0x4631,0x4631,0x4631,0x4631,0x4631,0x4631,0x4631,0x4631,
	0x4A52,0x4A52,0x4A52,0x4A52,0x4A52,0x4A52,0x4A52,0x4A52,
	0x4E73,0x4E73,0x4E73,0x4E73,0x4E73,0x4E73,0x4E73,0x4E73,
	0x5294,0x5294,0x5294,0x5294,0x5294,0x5294,0x5294,0x5294,
	0x56B5,0x56B5,0x56B5,0x56B5,0x56B5,0x56B5,0x56B5,0x56B5,
	0x5AD6,0x5AD6,0x5AD6,0x5AD6,0x5AD6,0x5AD6,0x5AD6,0x5AD6,
	0x5EF7,0x5EF7,0x5EF7,0x5EF7,0x5EF7,0x5EF7,0x5EF7,0x5EF7,

	0x6318,0x6318,0x6318,0x6318,0x6318,0x6318,0x6318,0x6318,
	0x6739,0x6739,0x6739,0x6739,0x6739,0x6739,0x6739,0x6739,
	0x6B5A,0x6B5A,0x6B5A,0x6B5A,0x6B5A,0x6B5A,0x6B5A,0x6B5A,
	0x6F7B,0x6F7B,0x6F7B,0x6F7B,0x6F7B,0x6F7B,0x6F7B,0x6F7B,
	0x739C,0x739C,0x739C,0x739C,0x739C,0x739C,0x739C,0x739C,
	0x77BD,0x77BD,0x77BD,0x77BD,0x77BD,0x77BD,0x77BD,0x77BD,
	0x7BDE,0x7BDE,0x7BDE,0x7BDE,0x7BDE,0x7BDE,0x7BDE,0x7BDE,
	0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,
};

//}}BLOCK(playerSprite)
