#pragma once

UENUM(BlueprintType)
enum class ESquadRow : uint8
{
	Vanguard = 0,
	Flank = 1,
	Back = 2
};

UENUM(BlueprintType)
enum class ESquadColumn : uint8
{
	Top = 0,
	Mid = 1,
	Bottom = 2
};
