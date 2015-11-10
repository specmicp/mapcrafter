/*
 * Copyright 2012-2015 Moritz Hilscher
 *
 * This file is part of Mapcrafter.
 *
 * Mapcrafter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Mapcrafter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Mapcrafter.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "overlay.h"

#include "../iniconfig.h"
#include "../../util.h"

#include <sstream>

namespace mapcrafter {
namespace util {

template <>
renderer::OverlayType as<renderer::OverlayType>(const std::string& from) {
	if (from == "lighting")
		return renderer::OverlayType::LIGHTING;
	else if (from == "slime")
		return renderer::OverlayType::SLIME;
	else if (from == "spawn")
		return renderer::OverlayType::SPAWN;
	throw std::invalid_argument("Must be 'none', 'spawn', 'slime' or 'lighting'.");
}

}
}

namespace mapcrafter {
namespace config {

OverlaySection::OverlaySection() {
}

OverlaySection::~OverlaySection() {
}

std::string OverlaySection::getPrettyName() const {
	if (isGlobal())
		return "Global overlay section";
	return "Overlay section '" + getSectionName() + "'";
}

void OverlaySection::dump(std::ostream& out) const {
	out << getPrettyName() << ":" << std::endl;
	out << "  name = " << name << std::endl;
	out << "  type = " << type << std::endl;
	out << "  base = " << base << std::endl;
}

std::string OverlaySection::getID() const {
	return getSectionName();
}

std::string OverlaySection::getName() const {
	return name.getValue();
}

renderer::OverlayType OverlaySection::getType() const {
	return type.getValue();
}

bool OverlaySection::isBase() const {
	return base.getValue();
}

void OverlaySection::preParse(const INIConfigSection& section,
		ValidationList& validation) {
	name.setDefault(getSectionName());
}

bool OverlaySection::parseField(const std::string key, const std::string value,
		ValidationList& validation) {
	if (key == "name") {
		name.load(key, value, validation);
	} else if (key == "type") {
		type.load(key, value, validation);
	} else if (key == "base") {
		base.load(key, value, validation);
	} else {
		return false;	
	}
	return true;
}

void OverlaySection::postParse(const INIConfigSection& section,
		ValidationList& validation) {
	base.setDefault(getType() == renderer::OverlayType::LIGHTING);
}

} /* namespace config */
} /* namespace mapcrafter */