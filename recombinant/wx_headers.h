#pragma once
//  Copyright(C) 2019. See AUTHORS file for contact information.
//  This is free software, licensed under the GPL Version 2 license (or at your
//  option) a later version. See the LICENSE file for more details.

// This header disables MSVC warnings just for wxWidgets,
// because MSVC doesn't have a concept of limiting warnings on some includes.
#ifdef _MSC_VER
#pragma warning(disable : 4996)
#pragma warning(push, 0)
#endif

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#ifdef _MSC_VER
#pragma warning(default : 4996)
#pragma warning(pop)
#endif
