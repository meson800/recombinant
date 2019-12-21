#pragma once

enum StringID
{
    AboutDialogTitle = 0,
    BuildInformation,
    License,
    Authors,
};

enum Language
{
    en_us = 0,
};

const char* en_us_strings[] = {
    "About Recombinant",
    "Build information: ",
    "License",
    "Authors",
};

const char** all_strings[] = {en_us_strings};

const char* localizedString(StringID id)
{
    return all_strings[Language::en_us][id];
}
