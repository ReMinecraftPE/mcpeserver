/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "Options.hpp"
#include "Util.hpp"
#include "Server.hpp"

Options::Option
	Options::Option::MUSIC            (0,  "options.music",          true,  false),
	Options::Option::SOUND            (1,  "options.sound",          true,  false),
	Options::Option::INVERT_MOUSE     (2,  "options.invertMouse",    false, true),
	Options::Option::SENSITIVITY      (3,  "options.sensitivity",    true,  false),
	Options::Option::RENDER_DISTANCE  (4,  "options.renderDistance", false, false),
	Options::Option::VIEW_BOBBING     (5,  "options.viewBobbing",    false, true),
	Options::Option::ANAGLYPH         (6,  "options.anaglyph",       false, true),
	Options::Option::LIMIT_FRAMERATE  (7,  "options.limitFramerate", false, true),
	Options::Option::DIFFICULTY       (8,  "options.difficulty",     false, false),
	Options::Option::GRAPHICS         (9,  "options.graphics",       false, false),
	Options::Option::AMBIENT_OCCLUSION(10, "options.ao",             false, true),
	Options::Option::GUI_SCALE        (11, "options.guiScale",       false, false);

void Options::initDefaultValues()
{
	field_238 = 2;
	field_244 = 1.0f;
	field_23C = 0;
	field_248 = 1.0f;
	field_23D = 0; // @NOTE: third person?
	field_0   = 1.0f;
	field_23E = 0;
	field_4   = 1.0f;
	m_bFlyCheat = false;
	field_241 = 0;
	field_8   = 0.5f;
	field_24C = 0;
	field_16  = 0;
	field_18  = 0;
	field_240 = 1;
	field_10  = 2;
	field_14  = 1;
	field_19  = 1;
	field_1C = "Default";
	m_playerName = "Steve";
	m_bServerVisibleDefault = true;
	

#ifdef ORIGINAL_CODE
	field_10 = 2;
	field_23D = 0;
	field_19 = 0;
#endif
}

Options::Options()
{
	initDefaultValues();
}

std::string getMessage(const Options::Option& option)
{
	return "Options::getMessage - Not implemented";
}

void Options::load()
{
	// stub
}

void Options::save()
{
	// stub
}

std::string Options::getMessage(const Options::Option& option)
{
	return "Options::getMessage - Not implemented";
}

bool Options::readBool(const std::string& str)
{
	std::string trimmed = Util::stringTrim(str);
	if (trimmed == "true" || trimmed == "1")
		return true;
	if (trimmed == "false" || trimmed == "0")
		return false;

	return false;
}

#ifndef ORIGINAL_CODE
int Options::readInt(const std::string& str)
{
	int f;
	
	if (!sscanf(str.c_str(), "%d", &f))
		f = 0;

	return f;
}
#endif

void Options::update(const std::vector<std::string>& strings)
{
	for (int i = 0; i<int(strings.size()); i += 2)
	{
		std::string key = strings[i], value = strings[i + 1];

		if (key == "mp_username")
			m_playerName = value;
		else if (key == "mp_server_visible_default")
			m_bServerVisibleDefault = readBool(value);
		else if (key == "gfx_viewdistance")
			field_10 = readInt(value);
	}
}
