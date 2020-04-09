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

#include <gtkmm/box.h>
#include <gtkmm/label.h>

#include "pbd/i18n.h"

#include "widgets/overwrite_rename_dialog.h"

using namespace Gtk;
using namespace ArdourWidgets;

OverwriteRenameDialog::OverwriteRenameDialog (Gtk::Window& parent, std::string title, std::string old_name)
	: Dialog (title, parent, true)
	, _old_name (old_name)
	, _new_name (std::string())
	, _rename_button (0)
	, _rename_editor ()
{
	set_border_width (12);

	_rename_editor.get_buffer()->set_text (old_name);

	Label* label = manage (new Label (string_compose (_("A template of the name ""%1"" already exists."), old_name)));

	get_vbox()->pack_start (*label, false, false, 12);
	get_vbox()->set_spacing (6);

	HBox* rn_bx = manage (new HBox);
	rn_bx->set_spacing (4);
	label = manage (new Label (_("Rename to:")));
	rn_bx->pack_start (*label, false, false);
	rn_bx->pack_start (_rename_editor);

	get_vbox()->pack_start (*rn_bx);

	add_button (_("Overwrite"), OVERWRITE);
	add_button (_("Overwrite all"), OVERWRITE | TO_ALL);
	add_button (_("Skip"), SKIP);
	add_button (_("Skip all"), SKIP | TO_ALL);
	_rename_button = add_button (_("Rename"), RENAME);

	_rename_button->set_sensitive (false);

	_rename_editor.get_buffer()->signal_changed().connect (sigc::mem_fun (*this, &OverwriteRenameDialog::name_changed));
	_rename_editor.set_accepts_tab (false);

	show_all_children();
}

void
OverwriteRenameDialog::name_changed ()
{
	_rename_button->set_sensitive (_rename_editor.get_buffer()->get_text() != _old_name);
}
