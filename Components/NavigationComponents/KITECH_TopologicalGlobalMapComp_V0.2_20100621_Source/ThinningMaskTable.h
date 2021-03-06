#pragma once

#define ELM_PATTERN2_SIZE	8
const BYTE _elmPattern2[ELM_PATTERN2_SIZE][8] =
{
	{1,1,0,0,0,0,0,0},
	{0,1,1,0,0,0,0,0},
	{0,0,1,1,0,0,0,0},
	{0,0,0,1,1,0,0,0},
	{0,0,0,0,1,1,0,0},
	{0,0,0,0,0,1,1,0},
	{0,0,0,0,0,0,1,1},
	{1,0,0,0,0,0,0,1}
};

#define ELM_PATTERN3_SIZE	12
const BYTE _elmPattern3[ELM_PATTERN3_SIZE][8] =
{
	{1,1,0,0,0,0,0,1},
	{1,1,1,0,0,0,0,0},
	{0,1,1,1,0,0,0,0},
	{0,0,1,1,1,0,0,0},
	{0,0,0,1,1,1,0,0},
	{0,0,0,0,1,1,1,0},
	{0,0,0,0,0,1,1,1},
	{1,0,0,0,0,0,1,1},
	{1,0,0,0,0,1,1,0},
	{1,0,1,1,0,0,0,0},
	{1,0,1,0,0,0,0,1},
	{1,1,0,0,0,0,1,0}
};

#define ELM_PATTERN4_SIZE	10
const BYTE _elmPattern4[ELM_PATTERN4_SIZE][8] = 
{
	{1,1,1,0,0,0,0,1},
	{1,1,1,1,0,0,0,0},
	{0,1,1,1,1,0,0,0},
	{0,0,1,1,1,1,0,0},
	{0,0,0,1,1,1,1,0},
	{0,0,0,0,1,1,1,1},
	{1,0,0,0,0,1,1,1},
	{1,1,0,0,0,0,1,1},
	{1,0,1,1,0,0,0,1},
	{1,1,0,0,0,1,1,0}
};

#define ELM_PATTERN5_SIZE	8
const BYTE _elmPattern5[ELM_PATTERN5_SIZE][8] =
{
	{1,1,1,1,0,0,0,1},
	{1,1,1,1,1,0,0,0},
	{0,1,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,0},
	{0,0,0,1,1,1,1,1},
	{1,0,0,0,1,1,1,1},
	{1,1,0,0,0,1,1,1},
	{1,1,1,0,0,0,1,1}
};

#define ELM_PATTERN6_SIZE	8
const BYTE _elmPattern6[ELM_PATTERN6_SIZE][8] =
{
	{1,1,1,1,1,0,0,1},
	{1,1,1,1,1,1,0,0},
	{0,1,1,1,1,1,1,0},
	{0,0,1,1,1,1,1,1},
	{1,0,0,1,1,1,1,1},
	{1,1,0,0,1,1,1,1},
	{1,1,1,0,0,1,1,1},
	{1,1,1,1,0,0,1,1}
};

#define ELM_PATTERN7_SIZE	4
const BYTE _elmPattern7[ELM_PATTERN7_SIZE][8] =
{
	{1,1,1,1,0,1,1,1},
	{1,1,1,1,1,1,0,1},
	{0,1,1,1,1,1,1,1},
	{1,1,0,1,1,1,1,1}
};

const BYTE _psvPattern1[4*3] = 
{
	3,0,3,
	1,1,1,
	1,1,1,
	3,0,3
};

const BYTE _psvPattern2[4*3] = 
{
	3,0,0,
	1,1,0,
	0,1,0,
	0,0,3
};

const BYTE _psvPattern3[4*3] = 
{
	3,0,0,
	0,1,0,
	0,1,1,
	0,0,3
};

const BYTE _psvPattern4[3*4] = 
{
	3,0,0,0,
	0,1,1,0,
	0,0,1,3
};

const BYTE _psvPattern5[3*4] = 
{
	3,1,1,3,
	0,1,1,0,
	3,1,1,3
};

const BYTE _psvPattern6[3*4] = 
{
	0,0,0,3,
	0,1,1,0,
	3,1,0,0
};

const BYTE _psvPattern7[4*4] = 
{
	0,0,0,0,
	0,1,1,0,
	0,1,1,0,
	0,0,0,0
};