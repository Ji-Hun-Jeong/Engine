#include "pch.h"
#include "Path.h"

namespace Path
{
	Str::FString SolutionPath;
	Str::FString ProjectPath;

	void Init(const Str::FString& _ProjectName)
	{
		char Path[255] = { 0 };
		GetCurrentDirectoryA(255, Path);
		SolutionPath = Path;

		SetProjectPath(_ProjectName);
	}

	void SetProjectPath(const Str::FString& _ProjectName)
	{
		ProjectPath = SolutionPath + "\\" + _ProjectName + "\\";
	}

	const Str::FString& GetProjectPath()
	{
		return ProjectPath;
	}
}