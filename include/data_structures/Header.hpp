#ifndef HEADER_HPP
#define HEADER_HPP

#include <vector>
#include <cstdint>

#include "../util/BinaryReader.hpp"
#include "../util/BinaryWriter.hpp"

class Header {
public:
	Header();
	Header(BinaryReader &romReader);

	std::vector<uint8_t> getGameTitle() const;
	void setGameTitle(const std::vector<uint8_t> &gameTitle);

	uint32_t getGameCode() const;
	void setGameCode(uint32_t gameCode);

	uint16_t getMakerCode() const;
	void setMakerCode(uint16_t makerCode);

	uint8_t getUnitCode() const;
	void setUnitCode(uint8_t unitCode);

	uint8_t getEncryptionSeedSelect() const;
	void setEncryptionSeedSelect(uint8_t encryptionSeed);

	uint8_t getDeviceCapacity() const;
	void setDeviceCapacity(uint8_t deviceCapacity);

	// Reserved 7bytes

	uint16_t getGameRevision() const;
	void setGameRevision(uint16_t gameRevision);

	uint8_t getRomVersion() const;
	void setRomVersion(uint8_t romVersion);

	uint8_t getInternalFlags() const;
	void setInternalFlags(uint8_t internalFlags);

	uint32_t getArm9RomAddress() const;
	void setArm9RomAddress(uint32_t arm9RomAddress);

	uint32_t getArm9EntryAddress() const;
	void setArm9EntryAddress(uint32_t arm9EntryAddress);

	uint32_t getArm9RamAddress() const;
	void setArm9RamAddress(uint32_t arm9RamAddress);

	uint32_t getArm9Size() const;
	void setArm9Size(uint32_t arm9Size);

	uint32_t getArm7RomAddress() const;
	void setArm7RomAddress(uint32_t arm7RomAddress);

	uint32_t getArm7EntryAddress() const;
	void setArm7EntryAddress(uint32_t arm7EntryAddress);

	uint32_t getArm7RamAddress() const;
	void setArm7RamAddress(uint32_t arm7RamAddress);

	uint32_t getArm7Size() const;
	void setArm7Size(uint32_t arm7Size);

	uint32_t getFileNameTableAddress() const;
	void setFileNameTableAddress(uint32_t fileNameTableAddress);

	uint32_t getFileNameTableSize() const;
	void setFileNameTableSize(uint32_t fileNameTableSize);

	uint32_t getFileAllocationTableAddress() const;
	void setFileAllocationTableAddress(uint32_t fileAllocationTableAddress);

	uint32_t getFileAllocationTableSize() const;
	void setFileAllocationTableSize(uint32_t fileAllocationTableSize);

	uint32_t getArm9OverlayAddress() const;
	void setArm9OverlayAddress(uint32_t arm9OverlayAddress);

	uint32_t getArm9OverlaySize() const;
	void setArm9OverlaySize(uint32_t arm9OverlaySize);

	uint32_t getArm7OverlayAddress() const;
	void setArm7OverlayAddress(uint32_t arm7OverlayAddress);

	uint32_t getArm7OverlaySize() const;
	void setArm7OverlaySize(uint32_t arm7OverlaySize);

	uint32_t getNormalCardControlRegister() const;
	void setNormalCardControlRegister(uint32_t normalCardControlRegister);

	uint32_t getSecureCardControlRegister() const;
	void setSecureCardControlRegister(uint32_t secureCardControlRegister);

	uint32_t getIconBannerAddress() const;
	void setIconBannerAddress(uint32_t iconBannerAddress);

	uint16_t getSecureAreaCrc() const;
	void setSecureAreaCrc(uint16_t secureAreaCrc);

	uint16_t getSecureTransferTimeout() const;
	void setSecureTransferTimeout(uint16_t secureTransferTimeout);

	uint32_t getArm9AutoLoad() const;
	void setArm9AutoLoad(uint32_t arm9AutoLoad);

	uint32_t getArm7AutoLoad() const;
	void setArm7AutoLoad(uint32_t arm7AutoLoad);

	uint64_t getSecureDisable() const;
	void setSecureDisable(uint64_t secureDisable);

	uint32_t getNtrRegionRomSize() const;
	void setNtrRegionRomSize(uint32_t ntrRegionRomSize);

	uint32_t getHeaderSize() const;
	void setHeaderSize(uint32_t headerSize);

	// Reserved 56bytes

	std::vector<uint8_t> getNintendoLogo() const; //156bytes
	void setNintendoLogo(const std::vector<uint8_t> &nintendoLogo);

	uint16_t getNintendoLogoCrc() const;
	void setNintendoLogoCrc(uint16_t nintendoLogoCrc);

	uint16_t getHeaderCrc() const;
	void setHeaderCrc(uint16_t headerCrc);

	// Debugger reserved 32bytes

	void writeToFile(BinaryWriter& writer) const;

private:
	std::vector<uint8_t> m_data;

	// Constants
	static const size_t HEADER_SIZE;
};
#endif