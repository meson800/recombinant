﻿//  Copyright(C) 2019. See AUTHORS file for contact information.
//
//  This program is free software; you can redistribute itand /or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License along
//  with this program; if not, write to the Free Software Foundation, Inc.,
//	51 Franklin Street, Fifth Floor, Boston, MA 02110 - 1301 USA.
// Use wxWidget's macro to create WinMain, or the equivilant on MacOSX/Linux...
// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".

#include "wx_headers.h"

#include "MainFrame.h"

class Recombinant : public wxApp
{
   public:
    virtual bool OnInit()
    {
        MainFrame* frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(Recombinant);
