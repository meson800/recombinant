#include "strings.h"

const char* en_us_strings[] = {
    "About Recombinant",
    "Recombinant",
    "Build information: ",
    "License",
    "Authors",
    "Add a data source to begin!",
    "Welcome to Recombinant!",
    "Viewer",
    "No sequence selected!",
    "Credits",
};

const char** all_strings[] = {en_us_strings};

const char* localizedString(StringID id)
{
    return all_strings[Language::en_us][id];
}
