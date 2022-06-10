#include "buffer.h"

i8 Buffer::read_i8(const std::vector<u8>& bytes, size_t& offset) {
	auto byte = bytes.at(offset);
	offset += sizeof(i8);

	return byte;
}

i16 Buffer::read_i16(const std::vector<u8>& bytes, size_t& offset, bool swap) {
	i16 out;

	out = i16(bytes.at(offset + 0)) << 8;
	out |= i16(bytes.at(offset + 1)) << 0;

	if (swap)
		out = ntohs(out);

	offset += sizeof(u16);

	return out;
}

i32 Buffer::read_i32(const std::vector<u8>& bytes, size_t& offset, bool swap) {
	i32 out;

	out = i32(bytes.at(offset + 0)) << 24;
	out |= i32(bytes.at(offset + 1)) << 16;
	out |= i32(bytes.at(offset + 2)) << 8;
	out |= i32(bytes.at(offset + 3)) << 0;

	if (swap)
		out = ntohl(out);

	offset += sizeof(i32);

	return out;
}

i64 Buffer::read_i64(const std::vector<u8>& bytes, size_t& offset, bool swap) {
	i64 out;

	out = i64(bytes.at(offset + 0)) << 56;
	out |= i64(bytes.at(offset + 1)) << 48;
	out |= i64(bytes.at(offset + 2)) << 40;
	out |= i64(bytes.at(offset + 3)) << 32;
	out |= i64(bytes.at(offset + 4)) << 24;
	out |= i64(bytes.at(offset + 5)) << 16;
	out |= i64(bytes.at(offset + 6)) << 8;
	out |= i64(bytes.at(offset + 7)) << 0;

	if (swap)
		out = ntohl(out);

	offset += sizeof(i64);

	return out;
}

u8 Buffer::read_u8(const std::vector<u8>& bytes, size_t& offset) {
	auto byte = bytes.at(offset);
	offset += sizeof(u8);
	return byte;
}

u16 Buffer::read_u16(const std::vector<u8>& bytes, size_t& offset, bool swap) {
	u16 out;

	out = u16(bytes.at(offset + 0)) << 8;
	out |= u16(bytes.at(offset + 1)) << 0;

	if (swap)
		out = ntohs(out);


	offset += sizeof(u16);

	return out;
}

u32 Buffer::read_u32(const std::vector<u8>& bytes, size_t& offset, bool swap) {
	u32 out;

	out = u32(bytes.at(offset + 0)) << 24;
	out |= u32(bytes.at(offset + 1)) << 16;
	out |= u32(bytes.at(offset + 2)) << 8;
	out |= u32(bytes.at(offset + 3)) << 0;

	if (swap)
		out = ntohl(out);

	offset += sizeof(u32);

	return out;
}

u64 Buffer::read_u64(const std::vector<u8>& bytes, size_t& offset, bool swap) {
	u64 out;

	out = u64(bytes.at(offset + 0)) << 56;
	out |= u64(bytes.at(offset + 1)) << 48;
	out |= u64(bytes.at(offset + 2)) << 40;
	out |= u64(bytes.at(offset + 3)) << 32;
	out |= u64(bytes.at(offset + 4)) << 24;
	out |= u64(bytes.at(offset + 5)) << 16;
	out |= u64(bytes.at(offset + 6)) << 8;
	out |= u64(bytes.at(offset + 7)) << 0;

	if (swap)
		out = ntohl(out);

	offset += sizeof(u64);

	return out;
}

std::vector<u8> Buffer::read_bytes(const std::vector<u8>& bytes, size_t n, size_t& offset) {
	std::vector<u8> out;

	for (size_t i = 0; i < n; ++i)
		out.push_back(bytes.at(offset + i));

	return out;
}

void Buffer::write_i8(std::vector<u8>& buffer, i8 value) {
	buffer.push_back(value);
}

void Buffer::write_i16(std::vector<u8>& buffer, i16 value) {
	buffer.push_back(value >> 8);
	buffer.push_back(value >> 0);
}

void Buffer::write_i32(std::vector<u8>& buffer, i32 value) {
	buffer.push_back(value >> 24);
	buffer.push_back(value >> 16);
	buffer.push_back(value >> 8);
	buffer.push_back(value >> 0);
}

void Buffer::write_i64(std::vector<u8>& buffer, i64 value) {
	buffer.push_back(value >> 56);
	buffer.push_back(value >> 48);
	buffer.push_back(value >> 40);
	buffer.push_back(value >> 32);
	buffer.push_back(value >> 24);
	buffer.push_back(value >> 16);
	buffer.push_back(value >> 8);
	buffer.push_back(value >> 0);
}

void Buffer::write_u8(std::vector<u8>& buffer, u8 value) {
	buffer.push_back(value);
}

void Buffer::write_u16(std::vector<u8>& buffer, u16 value) {
	buffer.push_back(value >> 8);
	buffer.push_back(value >> 0);
}

void Buffer::write_u32(std::vector<u8>& buffer, u32 value) {
	buffer.push_back(value >> 24);
	buffer.push_back(value >> 16);
	buffer.push_back(value >> 8);
	buffer.push_back(value >> 0);
}

void Buffer::write_u64(std::vector<u8>& buffer, u64 value) {
	buffer.push_back(value >> 56);
	buffer.push_back(value >> 48);
	buffer.push_back(value >> 40);
	buffer.push_back(value >> 32);
	buffer.push_back(value >> 24);
	buffer.push_back(value >> 16);
	buffer.push_back(value >> 8);
	buffer.push_back(value >> 0);
}

void Buffer::write_bytes(std::vector<u8>& buffer, const std::vector<u8>& bytes) {
	for (auto byte : bytes)
		buffer.push_back(byte);
}
