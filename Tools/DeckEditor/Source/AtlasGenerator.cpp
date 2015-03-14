/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	AtlasGenerator.cpp
 * Desc: 	Utility class to help generate Texture Atlasses from a number of 
 *			image files.
 *
 * Date: 	01/2011
 *
 * Copyright (C) 2007 - 2011 Xography. <www.gatewayheaven.com>
 *
 * -----------------------------------------------------------------------------
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * -----------------------------------------------------------------------------
 */
#include "AtlasGenerator.h"
#include "DeckEditor.h"
#include "ToolkitUtil.h"

#include "Card.h"
#include <fstream>
#include <Rocket/Core/String.h>

#include <boost/filesystem.hpp>
#include <iostream>


// -----------------------------------------------------------------------------
AtlasGenerator::AtlasGenerator(Arcomage::CardVector& cards) : deck(cards) {

}

// -----------------------------------------------------------------------------
void AtlasGenerator::generateLegacyAtlas() {
	boost::filesystem::path p("Editor/Cache/atlas.cache");
	p.normalize();
	std::ofstream out(p.string());

	out << "/* Generated by Arcomage Tribute Atlas Generator ["<< DeckEditor::Version <<"] */\n\n";

	foreach(Arcomage::Card* c, deck) {
		out <<"/* Atlas for Card #"<< c->getValue("ID") <<"*/\n";
		Rocket::Core::String img(c->getString("Image").c_str());
		img = img.Replace(".", "_");
		out << "." << img.CString() 
			<< " { background-decorator: image; background-image-src: " 
			<< c->getString("Image") 
			<<"; }\n";
	}
	out.close();
}

// -----------------------------------------------------------------------------
void AtlasGenerator::addFile(const std::string& file) {
		boost::filesystem::path p("Editor/Cache/atlas.cache");
		p.normalize();
		std::ofstream out(p.string(), std::ios::out | std::ios::app );	
		out <<"\n/* Temporary Atlas for " << file <<" */\n";
		Rocket::Core::String img(file.c_str());
		img = img.Replace(".", "_");
		out << "." << img.CString() 
			<< " { background-decorator: image; background-image-src: " 
			<< file
			<<"; }\n";
		out.close();
}