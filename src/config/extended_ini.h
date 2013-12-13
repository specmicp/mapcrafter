/*
 * Copyright 2012, 2013 Moritz Hilscher
 *
 * This file is part of mapcrafter.
 *
 * mapcrafter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * mapcrafter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with mapcrafter.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EXTENDED_CONFIG_H_
#define EXTENDED_CONFIG_H_

#include "../util.h"

//#include "validation.h"

#include <iostream>
#include <string>
#include <map>

namespace mapcrafter {
namespace config {

class ValidationMessage;

typedef std::pair<std::string, std::string> ConfigEntry;

class ConfigSection {
private:
	std::string type;
	std::string name;

	std::vector<ConfigEntry> entries;

	int getEntryIndex(const std::string& key) const;
public:
	ConfigSection(const std::string& type = "", const std::string& name = "");
	~ConfigSection();
	
	const std::string& getType() const;
	const std::string& getName() const;
	std::string getNameType() const;

	bool isNamed() const;
	bool isEmpty() const;

	bool has(const std::string& key) const;
	
	std::string get(const std::string& key, const std::string& default_value = "") const;
	template<typename T>
	T get(const std::string& key, T default_value = T()) const {
		if (has(key))
			return util::as<T>(get(key));
		return default_value;
	}
	
	const std::vector<ConfigEntry> getEntries() const;

	void set(const std::string& key, const std::string& value);
	void remove(const std::string& key);
};

std::ostream& operator<<(std::ostream& out, const ConfigSection& section);

class ConfigFile {
private:
	std::vector<ConfigSection> sections;
	ConfigSection root;

	ConfigSection empty_section;

	int getSectionIndex(const std::string& type, const std::string& name) const;
public:
	ConfigFile();
	~ConfigFile();

	bool load(std::istream& in, ValidationMessage& msg);
	bool load(std::istream& in);
	bool loadFile(const std::string& filename, ValidationMessage& msg);
	bool loadFile(const std::string& filename);

	bool write(std::ostream& out) const;
	bool writeFile(const std::string& filename) const;

	bool hasSection(const std::string& type, const std::string& name) const;

	const ConfigSection& getRootSection() const;
	ConfigSection& getRootSection();
	const ConfigSection& getSection(const std::string& type, const std::string& name) const;
	ConfigSection& getSection(const std::string& type, const std::string& name);

	const std::vector<ConfigSection> getSections() const;

	ConfigSection& addSection(const std::string& type, const std::string& name);
	ConfigSection& addSection(const ConfigSection& section);

	void removeSection(const std::string& type, const std::string& name);
};

} /* namespace config */
} /* namespace mapcrafter */

#endif /* EXTENDED_CONFIG_H_ */
