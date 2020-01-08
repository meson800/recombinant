#pragma once

enum StringID
{
    AboutDialogTitle = 0,
    ProgramName,
    BuildInformation,
    License,
    Authors,
    AddDataSources,
    Welcome,
    Viewer,
    NoSequenceSelected,
    Credits,
    STRING_COUNT,
};

enum Language
{
    en_us = 0,
    LANGUAGE_COUNT,
};

extern const char* en_us_strings[StringID::STRING_COUNT];

extern const char** all_strings[Language::LANGUAGE_COUNT];

const char* localizedString(StringID id);
