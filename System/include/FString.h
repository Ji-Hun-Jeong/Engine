#pragma once
#include <string>
#include <iostream>

namespace Str
{
    class FString
    {
    public:
        FString() : FString("") {}
        FString(const char* _Str);
        FString(const FString& _Other);
        FString(FString&& _Other) noexcept;
        FString& operator = (const char* _Str);
        FString& operator = (const FString& _Other);
        FString& operator = (FString&& _Other) noexcept;
        ~FString();

    public:
        friend bool operator < (const FString& _Str1, const FString& _Str2);
        friend bool operator > (const FString& _Str1, const FString& _Str2);
        friend bool operator == (const FString& _Str1, const FString& _Str2);
        friend bool operator != (const FString& _Str1, const FString& _Str2);
        friend FString operator + (const FString& _Str1, const FString& _Str2);

        FString& operator += (const FString& _Other);

        char operator [] (size_t index) const;

        friend std::ostream& operator << (std::ostream& os, const FString& str);
        friend struct std::hash<FString>;

        void Reset();

    private:
        const std::string* Str;
    };
}

namespace std
{
    template <>
    struct hash<Str::FString>
    {
        size_t operator()(const Str::FString& str) const
        {
            return hash<string>()(*str.Str);
        }
    };
}