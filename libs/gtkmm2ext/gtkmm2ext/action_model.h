/*
    Copyright (C) 2009-2013 Paul Davis
    Author: Johannes Mueller

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#include <string>

#include <gtkmm/treestore.h>
#include <gtkmm/treemodelcolumn.h>

namespace ActionManager {

class ActionModel
{
public:
	static const ActionModel& instance ();

	const Glib::RefPtr<Gtk::TreeStore> model () const { return _model; }

	const Gtk::TreeModelColumn<std::string>& name () const { return _columns.name; }
	const Gtk::TreeModelColumn<std::string>& path () const { return _columns.path; }

	struct Columns : public Gtk::TreeModel::ColumnRecord {
		Columns() {
			add (name);
			add (path);
		}
		Gtk::TreeModelColumn<std::string> name;
		Gtk::TreeModelColumn<std::string> path;
	};

	const Columns& columns() const { return _columns; }

private:
	ActionModel ();

	const Columns _columns;
	Glib::RefPtr<Gtk::TreeStore> _model;
};

}
