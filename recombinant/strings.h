#pragma once

enum StringID
{
    AboutDialogTitle = 0,
    BuildInformation,
    License,
    Authors,
    AddDataSources,
    Welcome,
};

enum Language
{
    en_us = 0,
};

const char* en_us_strings[];

const char** all_strings[];

const char* localizedString(StringID id);
