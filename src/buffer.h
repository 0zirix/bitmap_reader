#pragma once

#include <vector>

#ifdef PLATFORM_WINDOWS
#include <winsock.h>
#pragma comment (lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#endif

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

namespace Buffer {

	i8  read_i8(const  std::vector<u8>& bytes, size_t& offset);
	i16 read_i16(const std::vector<u8>& bytes, size_t& offset, bool swap = true);
	i32 read_i32(const std::vector<u8>& bytes, size_t& offset, bool swap = true);
	i64 read_i64(const std::vector<u8>& bytes, size_t& offset, bool swap = true);

	u8  read_u8(const  std::vector<u8>& bytes, size_t& offset);
	u16 read_u16(const std::vector<u8>& bytes, size_t& offset, bool swap = true);
	u32 read_u32(const std::vector<u8>& bytes, size_t& offset, bool swap = true);
	u64 read_u64(const std::vector<u8>& bytes, size_t& offset, bool swap = true);

	std::vector<u8> read_bytes(const std::vector<u8>& bytes, size_t n, size_t& offset, bool swap = true);

	void write_i8(std::vector<u8>& buffer,  i8 value);
	void write_i16(std::vector<u8>& buffer, i16 value, bool swap = true);
	void write_i32(std::vector<u8>& buffer, i32 value, bool swap = true);
	void write_i64(std::vector<u8>& buffer, i64 value, bool swap = true);

	void write_u8(std::vector<u8>& buffer,  u8 value);
	void write_u16(std::vector<u8>& buffer, u16 value, bool swap = true);
	void write_u32(std::vector<u8>& buffer, u32 value, bool swap = true);
	void write_u64(std::vector<u8>& buffer, u64 value, bool swap = true);

	void write_bytes(std::vector<u8>& buffer, const std::vector<u8>& bytes, bool swap = true);
}
