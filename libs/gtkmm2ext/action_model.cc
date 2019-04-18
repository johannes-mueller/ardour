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

#include <vector>

#include "pbd/i18n.h"
#include "pbd/strsplit.h"

#include "gtkmm2ext/actions.h"
#include "gtkmm2ext/action_model.h"

using namespace std;
using namespace Gtk;

const ActionManager::ActionModel&
ActionManager::ActionModel::instance ()
{
	static ActionManager::ActionModel am;
	return am;
}

ActionManager::ActionModel::ActionModel ()
{
	_model = TreeStore::create (_columns);
	_model->clear ();

	typedef std::map<string,TreeIter> NodeMap;
	NodeMap nodes;
	NodeMap::iterator r;

	TreeIter rowp;
	TreeModel::Row parent;

	rowp = _model->append ();
	parent = *(rowp);
	parent[_columns.name] = _("Disabled");

	vector<string> paths;
	vector<string> labels;
	vector<string> tooltips;
	vector<string> keys;
	vector<Glib::RefPtr<Gtk::Action> > actions;

	ActionManager::get_all_actions (paths, labels, tooltips, keys, actions);

	vector<string>::iterator k;
	vector<string>::iterator p;
	vector<string>::iterator t;
	vector<string>::iterator l;

	for (l = labels.begin(), k = keys.begin(), p = paths.begin(), t = tooltips.begin(); l != labels.end(); ++k, ++p, ++t, ++l) {

		TreeModel::Row row;
		vector<string> parts;
		parts.clear ();
		split (*p, parts, '/');

		if (parts.empty()) {
			continue;
		}

		//kinda kludgy way to avoid displaying menu items as mappable
		if ( parts[0] == _("Main_menu") )
			continue;
		if ( parts[0] == _("JACK") )
			continue;
		if ( parts[0] == _("redirectmenu") )
			continue;
		if ( parts[0] == _("Editor_menus") )
			continue;
		if ( parts[0] == _("RegionList") )
			continue;
		if ( parts[0] == _("ProcessorMenu") )
			continue;

		if ((r = nodes.find (parts[0])) == nodes.end()) {
			/* top level is missing */

			TreeIter rowp;
			TreeModel::Row parent;
			rowp = _model->append();
			nodes[parts[0]] = rowp;
			parent = *(rowp);
			parent[_columns.name] = parts[0];

			row = *(_model->append (parent.children()));
		} else {
			row = *(_model->append ((*r->second)->children()));
		}

		/* add this action */

		if (l->empty ()) {
			row[_columns.name] = *t;
		} else {
			row[_columns.name] = *l;
		}

		row[_columns.path] = *p;
	}
}
