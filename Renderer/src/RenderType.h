#pragma once

enum class eCategoryVS
{
	Color, End,
};
enum class eCategoryPS
{
	Color, End,
};
enum class eCategorySS
{
	Linear, End,
};
enum class eCategoryRS
{
	SolidCw, End,
};
enum class eCategoryRTV
{
	BackBuffer, End,
};
enum class eCategoryDSS
{
	Basic, End,
};
enum class eCategoryDSV
{
	BackBuffer, End,
};
enum class eCategoryIL
{
	Basic, End,
};
enum class eCategoryVP
{
	Basic, End,
};
enum class eCategoryTopology
{
	Triangle, End,
};
enum class eCategoryClearFlag
{
	ClearDepth = 1,
	ClearStnecil = 2,
	End = 100,
};
enum class eCategoryVSConst
{
	Basic,
	End,
};
enum class eCategoryPSConst
{
	Basic,
	End,
};