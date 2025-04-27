#pragma once

namespace Path
{
	extern void Init(const Str::FString& _ProjectName);
	extern void SetProjectPath(const Str::FString& _ProjectName);
	extern const Str::FString& GetProjectPath();
}

