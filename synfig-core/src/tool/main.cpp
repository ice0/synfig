/* === S Y N F I G ========================================================= */
/*!	\file tool/main.cpp
**	\brief SYNFIG Tool
**
**	$Id$
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
**	Copyright (c) 2007, 2008 Chris Moore
**	Copyright (c) 2009-2015 Diego Barrios Romero
**
**	This package is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License as
**	published by the Free Software Foundation; either version 2 of
**	the License, or (at your option) any later version.
**
**	This package is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
**	General Public License for more details.
**	\endlegal
*/
/* ========================================================================= */

/* === H E A D E R S ======================================================= */

#ifdef USING_PCH
#	include "pch.h"
#else
#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include <iostream>
#include <string>
#include <list>

#include <glibmm.h>

#include <synfig/localization.h>
#include <synfig/general.h>

#include <synfig/module.h>
#include <synfig/importer.h>
#include <synfig/cairoimporter.h>
#include <synfig/layer.h>
#include <synfig/canvas.h>
#include <synfig/target.h>
#include <synfig/targetparam.h>
#include <synfig/string.h>
#include <synfig/paramdesc.h>
#include <synfig/main.h>
#include <autorevision.h>
#include "definitions.h"
#include "progress.h"
#include "job.h"
#include "synfigtoolexception.h"
#include "optionsprocessor.h"
#include "joblistprocessor.h"
#include "printing_functions.h"

//#include "named_type.h"
#endif

std::string _appendAlphaToFilename(std::string input_filename)
{

	std::size_t found = input_filename.rfind(".");
	if (found == std::string::npos) return input_filename + "-alpha"; // extension not found, just add to the end
	
	return input_filename.substr(0, found) + "-alpha" + input_filename.substr(found);

    /*bfs::path filename(input_filename);
    bfs::path alpha_filename(filename.stem().string() + "-alpha" +
        filename.extension().string());
    return bfs::path(filename.parent_path() / alpha_filename).string();*/
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	Glib::init(); // need to use Gio functions before app is started

	SynfigToolGeneralOptions::create_singleton_instance(argv[0]);

	std::string binary_path =
		SynfigToolGeneralOptions::instance()->get_binary_path();

#ifdef ENABLE_NLS
	/*bst::filesystem::path locale_path =
		binary_path.parent_path().parent_path();*/
	std::string locale_path = get_absolute_path(binary_path + "../../share/locale");
	//locale_path = locale_path/"share"/"locale";
	//bindtextdomain("synfig", Glib::locale_from_utf8(locale_path.string()).c_str() );
	bindtextdomain("synfig", Glib::locale_from_utf8(locale_path).c_str() );
	bind_textdomain_codeset("synfig", "UTF-8");
	textdomain("synfig");
#endif

	if(!SYNFIG_CHECK_VERSION())
	{
		std::cerr << _("FATAL: Synfig Version Mismatch") << std::endl;
		return SYNFIGTOOL_BADVERSION;
	}

	try
	{
		if(argc == 1)
		{
			throw (SynfigToolException(SYNFIGTOOL_MISSINGARGUMENT));
		}


		SynfigCommandLineParser parser;
		parser.parse(argc, argv);

        // Switch options ---------------------------------------------
        parser.process_settings_options();

#ifdef _DEBUG
		// DEBUG options ----------------------------------------------
		parser.process_debug_options();
#endif

		// Trivial info options -----------------------------------------------
		parser.process_trivial_info_options();

		// Synfig Main initialization needs to be after verbose and
		// before any other where it's used
		Progress p(binary_path.c_str());
		//synfig::Main synfig_main(binary_path.parent_path().string(), &p);
		synfig::Main synfig_main(get_absolute_path(binary_path + "/.."), &p);

		// Info options -----------------------------------------------
		parser.process_info_options();

		std::list<Job> job_list;

		// Processing --------------------------------------------------
		Job job;
		job = parser.extract_job();
		job.desc = job.canvas->rend_desc() = parser.extract_renddesc(job.canvas->rend_desc());

		if (job.extract_alpha) {
			job.alpha_mode = synfig::TARGET_ALPHA_MODE_REDUCE;
			job_list.push_front(job);
			job.alpha_mode = synfig::TARGET_ALPHA_MODE_EXTRACT;
			job.outfilename = _appendAlphaToFilename(job.outfilename);
			job_list.push_front(job);
		} else {
			job_list.push_front(job);
		}

		process_job_list(job_list, parser.extract_targetparam());

		return SYNFIGTOOL_OK;

    }
    catch (SynfigToolException& e) {
    	exit_code code = e.get_exit_code();
    	if (code != SYNFIGTOOL_HELP && code != SYNFIGTOOL_OK)
    		std::cerr << e.get_message().c_str() << std::endl;
    	if (code == SYNFIGTOOL_MISSINGARGUMENT)
    		print_usage();

    	return code;
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
