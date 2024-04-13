#ifndef FILENAMETABLE_HPP
#define FILENAMETABLE_HPP

#include <vector>
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <string>

#include "../../include/util/BinaryReader.hpp"
#include "../../include/util/BinaryWriter.hpp"

class FileNameTable {
	enum class NodeType: char {
		FILE = 'f',
		DIRECTORY = 'd'
	};

	class Node {
	public:
		Node(uint16_t id, const std::string& name, FileNameTable::NodeType type) : m_id(id), m_name(name), m_type(type) {};
		virtual ~Node() = default;
		uint16_t getId() const { return m_id; };
		std::string getName() { return m_name; };
		//void setName(const std::string& name) { m_name = name; };
		FileNameTable::NodeType getType() const { return m_type; };
	private:
		uint16_t m_id;
		std::string m_name;
		FileNameTable::NodeType m_type;
	};

	class File : public Node {
	public:
		File(uint16_t id, const std::string& name) : Node(id, name, FileNameTable::NodeType::FILE) {};
	};

	class Directory : public Node {
	public:
		Directory(uint16_t id, const std::string& name) :
			Node(id, name, FileNameTable::NodeType::DIRECTORY),
			m_itemOffset(0),
			m_firstFileId(0),
			m_parentId(0),
			m_currentOrderedChild(0){
		};

		void addChild(std::string& name, std::shared_ptr<Node> node) {
			m_orderedChildren.push_back(node);
			m_children[name] = node;
		};

		std::shared_ptr<Node> getChild(const std::string& name) const {
			auto it = m_children.find(name);
			if (it == m_children.end()) {
				throw std::runtime_error("Could not find node " + name);
			}
			return it->second;
		};

		uint32_t getItemOffset() const {
			return m_itemOffset;
		};

		void setItemOffset(uint32_t itemOffset) {
			m_itemOffset = itemOffset;
		};

		uint16_t getFirstFileId() const {
			return m_firstFileId;
		};

		void setFirstFileId(uint16_t firstFileId) {
			m_firstFileId = firstFileId;
		};

		uint16_t getParentId() const {
			return m_parentId;
		};

		void setParentId(uint16_t parentId) {
			m_parentId = parentId;
		};

		// Iterator for ordered children
		void goToFirstOrderedChild() {
			m_currentOrderedChild = 0;
		};

		bool hasNextOrderedChild() {
			return m_currentOrderedChild < m_orderedChildren.size();
		};

		std::shared_ptr<Node> getNextOrderedChild() {
			return m_orderedChildren[m_currentOrderedChild++];
		};
		// END iterator for ordered children
	private:
		std::vector<std::shared_ptr<Node>> m_orderedChildren; // For tracking order
		std::unordered_map<std::string, std::shared_ptr<Node>> m_children; // For quick access by name

		uint32_t m_itemOffset;
		uint16_t m_firstFileId;
		uint16_t m_parentId;

		size_t m_currentOrderedChild; // Iterator for ordered children
	};

public:
	FileNameTable();
	FileNameTable(BinaryReader &romReader, uint32_t address, uint32_t size);

	uint16_t getFileIdByPath(const char* path, char dirSeparator) const;

	void writeToFile(BinaryWriter& writer, uint32_t offset) const;
private:
	std::vector<uint8_t>* getData() const;

	uint32_t m_size;
	std::shared_ptr<Directory> m_root;
	std::vector<std::shared_ptr<Directory>> m_mainTables;

	// constants
	static const uint16_t ROOT_DIRECTORY_ID = 0xF000;
};

#endif