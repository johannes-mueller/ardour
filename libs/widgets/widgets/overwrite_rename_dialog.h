/*
 * Copyright (C) 2020 Johannes Mueller <github@johannes-mueller.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef WIDGETS_OVERWRITE_RENAME_DIALOG_H
#define WIDGETS_OVERWRITE_RENAME_DIALOG_H

#include <string>

#include <gtkmm/button.h>
#include <gtkmm/dialog.h>
#include <gtkmm/textview.h>

#include "widgets/visibility.h"

namespace ArdourWidgets {

class LIBWIDGETS_API  OverwriteRenameDialog : public Gtk::Dialog
{
public:
	enum Response {
	       RENAME    = 0x00,
	       SKIP      = 0x01,
	       OVERWRITE = 0x02,
	       TO_ALL    = 0x10
	};

	OverwriteRenameDialog (Gtk::Window& praent, std::string title, std::string old_name);

	std::string new_name () const { return _new_name; }

private:
	void name_changed ();
	std::string _old_name, _new_name;
	Gtk::Button* _rename_button;
	Gtk::TextView _rename_editor;
};

} /* namespace */

#endif
