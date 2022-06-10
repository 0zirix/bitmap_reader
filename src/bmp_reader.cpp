#include "bmp_reader.h"

std::optional<BMP::Bitmap> BMP::read(const std::string& filename)
{
	// Open file
	std::fstream file(filename, std::ios_base::in | std::ios_base::binary);
	std::vector<u8> buffer(std::istreambuf_iterator<char>(file), {});

	if (!file.is_open()) {
		std::cout << "Cannot open file: " << filename << std::endl;
		return std::nullopt;
	}

	Bitmap bitmap;
	size_t offset = 0;

	// Signature
	bitmap.header.signature = Buffer::read_u16(buffer, offset, false);

	if (bitmap.header.signature != 0x424d) {
		std::cout << "Unrecognized file format: invalid header signature." << std::endl;
		return std::nullopt;
	}

	// Header
	bitmap.header.file_size = Buffer::read_u32(buffer, offset);
	bitmap.header.reserved = Buffer::read_u32(buffer, offset);
	bitmap.header.data_offset = Buffer::read_u32(buffer, offset);

	// Infos
	bitmap.infos.size = Buffer::read_u32(buffer, offset);
	bitmap.infos.width = Buffer::read_u32(buffer, offset);
	bitmap.infos.height = Buffer::read_u32(buffer, offset);
	bitmap.infos.planes = Buffer::read_u16(buffer, offset);
	bitmap.infos.bit_count = Buffer::read_u16(buffer, offset);
	bitmap.infos.compression = Buffer::read_u32(buffer, offset);
	bitmap.infos.image_size = Buffer::read_u32(buffer, offset);
	bitmap.infos.x_ppm = Buffer::read_u32(buffer, offset);
	bitmap.infos.y_ppm = Buffer::read_u32(buffer, offset);
	bitmap.infos.colors_used = Buffer::read_u32(buffer, offset);
	bitmap.infos.colors_important = Buffer::read_u32(buffer, offset);

	std::cout << bitmap.header << std::endl;
	std::cout << bitmap.infos << std::endl;

	if (bitmap.infos.bit_count == 24) {
		size_t pixels_offset = bitmap.header.data_offset;

		// Pixels
		auto data = Buffer::read_bytes(
			buffer,
			bitmap.header.file_size - offset,
			pixels_offset
		);

		// We got all the pixels
		if (data.size() == bitmap.infos.width * bitmap.infos.height * 3)
			bitmap.pixels = std::move(data);
		else
			std::cout << "Error while reading pixels data" << std::endl;
	}

	file.close();

	return bitmap;
}

bool BMP::write(const std::string& filename, const Bitmap& bitmap)
{
	std::vector<u8> buffer;

	// Header
	Buffer::write_u16(buffer, bitmap.header.signature);
	Buffer::write_u32(buffer, htonl(bitmap.header.file_size));
	Buffer::write_u32(buffer, htonl(bitmap.header.reserved));
	Buffer::write_u32(buffer, htonl(bitmap.header.data_offset));

	// Infos
	Buffer::write_u32(buffer, htonl(bitmap.infos.size));
	Buffer::write_u32(buffer, htonl(bitmap.infos.width));
	Buffer::write_u32(buffer, htonl(bitmap.infos.height));
	Buffer::write_u16(buffer, htonl(bitmap.infos.planes));
	Buffer::write_u16(buffer, htons(bitmap.infos.bit_count));
	Buffer::write_u32(buffer, htonl(bitmap.infos.compression));
	Buffer::write_u32(buffer, htonl(bitmap.infos.image_size));
	Buffer::write_u32(buffer, htonl(bitmap.infos.x_ppm));
	Buffer::write_u32(buffer, htonl(bitmap.infos.y_ppm));
	Buffer::write_u32(buffer, htonl(bitmap.infos.colors_used));
	Buffer::write_u32(buffer, htonl(bitmap.infos.colors_important));

	// Pixels
	for (u64 i = 0; i < bitmap.pixels.size(); i += 3) {
		Buffer::write_u8(buffer, bitmap.pixels.at(i + 0));
		Buffer::write_u8(buffer, bitmap.pixels.at(i + 1));
		Buffer::write_u8(buffer, bitmap.pixels.at(i + 2));
	}

	// Write file
	std::ofstream file(filename, std::ios_base::out | std::ios_base::binary);

	if (file.is_open()) {
		for (auto byte : buffer)
			file << byte;
		
		file.close();

		std::cout << "Written BMP file: " << filename << std::endl;
		return true;
	}

	std::cout << "Error while writing the BMP file: " << filename << std::endl;

	return false;
}
