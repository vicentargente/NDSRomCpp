#include "../../include/data_structures/Header.hpp"
#include "../../include/util/CRC.hpp"

const size_t Header::HEADER_SIZE = 0x180;

Header::Header() : m_data(0) {}

Header::Header(BinaryReader& romReader): m_data(HEADER_SIZE) {
	size_t originalRomPosition = romReader.tellg();
	romReader.seekg(0);

	romReader.readBytes(m_data);

	romReader.seekg(originalRomPosition);
}

std::vector<uint8_t> Header::getGameTitle() const {
	return std::vector<uint8_t>(m_data.begin(), m_data.begin() + 0xC);
}

void Header::setGameTitle(const std::vector<uint8_t>& gameTitle) {
	std::copy(gameTitle.begin(), gameTitle.end(), m_data.begin());
}

uint32_t Header::getGameCode() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0xC]);
}

void Header::setGameCode(uint32_t gameCode) {
	*reinterpret_cast<uint32_t*>(&m_data[0xC]) = gameCode;
}

uint16_t Header::getMakerCode() const {
	return *reinterpret_cast<const uint16_t*>(&m_data[0x10]);
}

void Header::setMakerCode(uint16_t makerCode) {
	*reinterpret_cast<uint16_t*>(&m_data[0x10]) = makerCode;
}

uint8_t Header::getUnitCode() const {
	return m_data[0x12];
}

void Header::setUnitCode(uint8_t unitCode) {
	m_data[0x12] = unitCode;
}

uint8_t Header::getEncryptionSeedSelect() const {
	return m_data[0x13];
}

void Header::setEncryptionSeedSelect(uint8_t encryptionSeed) {
	m_data[0x13] = encryptionSeed;
}

uint8_t Header::getDeviceCapacity() const {
	return m_data[0x14];
}

void Header::setDeviceCapacity(uint8_t deviceCapacity) {
	m_data[0x14] = deviceCapacity;
}

uint16_t Header::getGameRevision() const {
	return *reinterpret_cast<const uint16_t*>(&m_data[0x1C]);
}

void Header::setGameRevision(uint16_t gameRevision) {
	*reinterpret_cast<uint16_t*>(&m_data[0x1C]) = gameRevision;
}

uint8_t Header::getRomVersion() const {
	return m_data[0x1E];
}

void Header::setRomVersion(uint8_t romVersion) {
	m_data[0x1E] = romVersion;
}

uint8_t Header::getInternalFlags() const {
	return m_data[0x1F];
}

void Header::setInternalFlags(uint8_t internalFlags) {
	m_data[0x1F] = internalFlags;
}

uint32_t Header::getArm9RomAddress() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x20]);
}

void Header::setArm9RomAddress(uint32_t arm9RomAddress) {
	*reinterpret_cast<uint32_t*>(&m_data[0x20]) = arm9RomAddress;
}

uint32_t Header::getArm9EntryAddress() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x24]);
}

void Header::setArm9EntryAddress(uint32_t arm9EntryAddress) {
	*reinterpret_cast<uint32_t*>(&m_data[0x24]) = arm9EntryAddress;
}

uint32_t Header::getArm9RamAddress() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x28]);
}

void Header::setArm9RamAddress(uint32_t arm9RamAddress) {
	*reinterpret_cast<uint32_t*>(&m_data[0x28]) = arm9RamAddress;
}

uint32_t Header::getArm9Size() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x2C]);
}

void Header::setArm9Size(uint32_t arm9Size) {
	*reinterpret_cast<uint32_t*>(&m_data[0x2C]) = arm9Size;
}

uint32_t Header::getArm7RomAddress() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x30]);
}

void Header::setArm7RomAddress(uint32_t arm7RomAddress) {
	*reinterpret_cast<uint32_t*>(&m_data[0x30]) = arm7RomAddress;
}

uint32_t Header::getArm7EntryAddress() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x34]);
}

void Header::setArm7EntryAddress(uint32_t arm7EntryAddress) {
	*reinterpret_cast<uint32_t*>(&m_data[0x34]) = arm7EntryAddress;
}

uint32_t Header::getArm7RamAddress() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x38]);
}

void Header::setArm7RamAddress(uint32_t arm7RamAddress) {
	*reinterpret_cast<uint32_t*>(&m_data[0x38]) = arm7RamAddress;
}

uint32_t Header::getArm7Size() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x3C]);
}

void Header::setArm7Size(uint32_t arm7Size) {
	*reinterpret_cast<uint32_t*>(&m_data[0x3C]) = arm7Size;
}

uint32_t Header::getFileNameTableAddress() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x40]);
}

void Header::setFileNameTableAddress(uint32_t fileNameTableAddress) {
	*reinterpret_cast<uint32_t*>(&m_data[0x40]) = fileNameTableAddress;
}

uint32_t Header::getFileNameTableSize() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x44]);
}

void Header::setFileNameTableSize(uint32_t fileNameTableSize) {
	*reinterpret_cast<uint32_t*>(&m_data[0x44]) = fileNameTableSize;
}

uint32_t Header::getFileAllocationTableAddress() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x48]);
}

void Header::setFileAllocationTableAddress(uint32_t fileAllocationTableAddress) {
	*reinterpret_cast<uint32_t*>(&m_data[0x48]) = fileAllocationTableAddress;
}

uint32_t Header::getFileAllocationTableSize() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x4C]);
}

void Header::setFileAllocationTableSize(uint32_t fileAllocationTableSize) {
	*reinterpret_cast<uint32_t*>(&m_data[0x4C]) = fileAllocationTableSize;
}

uint32_t Header::getArm9OverlayAddress() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x50]);
}

void Header::setArm9OverlayAddress(uint32_t arm9OverlayAddress) {
	*reinterpret_cast<uint32_t*>(&m_data[0x50]) = arm9OverlayAddress;
}

uint32_t Header::getArm9OverlaySize() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x54]);
}

void Header::setArm9OverlaySize(uint32_t arm9OverlaySize) {
	*reinterpret_cast<uint32_t*>(&m_data[0x54]) = arm9OverlaySize;
}

uint32_t Header::getArm7OverlayAddress() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x58]);
}

void Header::setArm7OverlayAddress(uint32_t arm7OverlayAddress) {
	*reinterpret_cast<uint32_t*>(&m_data[0x58]) = arm7OverlayAddress;
}

uint32_t Header::getArm7OverlaySize() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x5C]);
}

void Header::setArm7OverlaySize(uint32_t arm7OverlaySize) {
	*reinterpret_cast<uint32_t*>(&m_data[0x5C]) = arm7OverlaySize;
}

uint32_t Header::getNormalCardControlRegister() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x60]);
}

void Header::setNormalCardControlRegister(uint32_t normalCardControlRegister) {
	*reinterpret_cast<uint32_t*>(&m_data[0x60]) = normalCardControlRegister;
}

uint32_t Header::getSecureCardControlRegister() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x64]);
}

void Header::setSecureCardControlRegister(uint32_t secureCardControlRegister) {
	*reinterpret_cast<uint32_t*>(&m_data[0x64]) = secureCardControlRegister;
}

uint32_t Header::getIconBannerAddress() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x68]);
}

void Header::setIconBannerAddress(uint32_t iconBannerAddress) {
	*reinterpret_cast<uint32_t*>(&m_data[0x68]) = iconBannerAddress;
}

uint16_t Header::getSecureAreaCrc() const {
	return *reinterpret_cast<const uint16_t*>(&m_data[0x6C]);
}

void Header::setSecureAreaCrc(uint16_t secureAreaCrc) {
	*reinterpret_cast<uint16_t*>(&m_data[0x6C]) = secureAreaCrc;
}

uint16_t Header::getSecureTransferTimeout() const {
	return *reinterpret_cast<const uint16_t*>(&m_data[0x6E]);
}

void Header::setSecureTransferTimeout(uint16_t secureTransferTimeout) {
	*reinterpret_cast<uint16_t*>(&m_data[0x6E]) = secureTransferTimeout;
}

uint32_t Header::getArm9AutoLoad() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x70]);
}

void Header::setArm9AutoLoad(uint32_t arm9AutoLoad) {
	*reinterpret_cast<uint32_t*>(&m_data[0x70]) = arm9AutoLoad;
}

uint32_t Header::getArm7AutoLoad() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x74]);
}

void Header::setArm7AutoLoad(uint32_t arm7AutoLoad) {
	*reinterpret_cast<uint32_t*>(&m_data[0x74]) = arm7AutoLoad;
}

uint64_t Header::getSecureDisable() const {
	return *reinterpret_cast<const uint64_t*>(&m_data[0x78]);
}

void Header::setSecureDisable(uint64_t secureDisable) {
	*reinterpret_cast<uint64_t*>(&m_data[0x78]) = secureDisable;
}

uint32_t Header::getNtrRegionRomSize() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x80]);
}

void Header::setNtrRegionRomSize(uint32_t ntrRegionRomSize) {
	*reinterpret_cast<uint32_t*>(&m_data[0x80]) = ntrRegionRomSize;
}

uint32_t Header::getHeaderSize() const {
	return *reinterpret_cast<const uint32_t*>(&m_data[0x84]);
}

void Header::setHeaderSize(uint32_t headerSize) {
	*reinterpret_cast<uint32_t*>(&m_data[0x84]) = headerSize;
}

std::vector<uint8_t> Header::getNintendoLogo() const {
	return std::vector<uint8_t>(m_data.begin() + 0xC0, m_data.begin() + 0xC0 + 0x9C);
}

void Header::setNintendoLogo(const std::vector<uint8_t>& nintendoLogo) {
	std::copy(nintendoLogo.begin(), nintendoLogo.end(), m_data.begin() + 0xC0);
}

uint16_t Header::getNintendoLogoCrc() const {
	return *reinterpret_cast<const uint16_t*>(&m_data[0x15C]);
}

void Header::setNintendoLogoCrc(uint16_t nintendoLogoCrc) {
	*reinterpret_cast<uint16_t*>(&m_data[0x15C]) = nintendoLogoCrc;
}

uint16_t Header::getHeaderCrc() const {
	return *reinterpret_cast<const uint16_t*>(&m_data[0x15E]);
}

void Header::setHeaderCrc(uint16_t headerCrc) {
	*reinterpret_cast<uint16_t*>(&m_data[0x15E]) = headerCrc;
}

void Header::recalculateNintendoLogoCrc()
{
	uint16_t crc = CRC16::calculate(this->m_data, 0xC0, 0x9C);
	this->setNintendoLogoCrc(crc);
}

void Header::recalculateHeaderCrc()
{
	uint16_t crc = CRC16::calculate(this->m_data, 0, 0x015E);
	this->setHeaderCrc(crc);
}

void Header::writeToFile(BinaryWriter& writer) const {
	writer.writeBytes(m_data, 0);
}