#ifndef FILENAMETABLE_H
#define FILENAMETABLE_H

#include <vector>
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <string>

#include "../../include/util/BinaryReader.h"

class FileNameTable {
	struct Entry {
		uint16_t id;
		std::string name;
	};

	struct MainTable {
		uint16_t parentDirectoryId;
		std::vector<Entry> subDirectories;
		std::vector<Entry> subFiles;

		void addSubDirectory(Entry e) {
			subDirectories.push_back(e);
		}

		void addSubFile(Entry e) {
			subFiles.push_back(e);
		}
	};

	class Node {
	public:
		Node(uint16_t id) : m_id(id) {};
		virtual ~Node() = default;
		uint16_t getId() const { return m_id; };
	private:
		uint16_t m_id;
	};

	class File : public Node {
	public:
		File(uint16_t id) : Node(id) {};
	};

	class Directory : public Node {
	public:
		Directory(uint16_t id) : Node(id) {};

		void addChild(std::string &name, std::shared_ptr<Node> node) {
			m_children[name] = node;
		}

		std::shared_ptr<Node> getChild(const std::string &name) const {
			auto it = m_children.find(name);
			if (it == m_children.end()) {
				throw std::runtime_error("Could not find node " + name);
			}
			return it->second;
		}
	private:
		std::unordered_map<std::string, std::shared_ptr<Node>> m_children;
	};

public:
	FileNameTable();
	FileNameTable(BinaryReader &romReader, uint32_t offset, uint32_t size);
	uint16_t getFileIdByPath(const char* path, char dirSeparator) const;
private:
	std::shared_ptr<Directory> m_root;

	// constants
	static const uint16_t ROOT_DIRECTORY_ID = 0xF000;
};

#endif