#include "SDataStream.h"
#include <iostream>
//((uint8_t*)&v)[3];
#define pv(i) ((uint8_t*)&v)[i]

SDataStream::SDataStream()
{
}

void SDataStream::setByteOrder(ByteOrder order)
{
	_order = order;
}

ByteOrder SDataStream::byteOrder() const
{
	return _order;
}

std::string SDataStream::str() const
{
	return _data;
}

SDataStream& SDataStream::write(const char* s, uint32_t len)
{
	_data.append(s, len);
	//_data.append(" ");
	return *this;
}

SDataStream& SDataStream::operator<<(int8_t v)
{
	uint8_t buf[2] = { 0 };
	buf[0] = MetaType::Int8;
	buf[1] = v;
	write((char*)buf, 2);
	return *this;
}

SDataStream& SDataStream::operator<<(uint8_t v)
{
	uint8_t buf[2] = { 0 };
	buf[0] = MetaType::UInt8;
	buf[1] = v;
	write((char*)buf, 2);
	return *this;
}

SDataStream& SDataStream::operator<<(int16_t v)
{
	uint8_t buf[3] = { 0 };
	buf[0] = MetaType::Int16;
	switch (_order)
	{
	case ByteOrder::BigEndian:
		buf[1] = pv(1);
		buf[2] = pv(0);
		break;
	case ByteOrder::LittleEndian:
		buf[1] = pv(0);
		buf[2] = pv(1);
		break;
	}
	write((char*)buf, 3);
	return *this;
}

SDataStream& SDataStream::operator<<(uint16_t v)
{
	uint8_t buf[3] = { 0 };
	buf[0] = MetaType::UInt16;
	switch (_order)
	{
	case ByteOrder::BigEndian:
		buf[1] = pv(1);
		buf[2] = pv(0);
		break;
	case ByteOrder::LittleEndian:

		buf[1] = pv(0);
		buf[2] = pv(1);;
		break;
	}
	write((char*)buf, 3);
	return *this;
}

SDataStream& SDataStream::operator<<(int32_t v)
{
	uint8_t buf[5] = { 0 };
	buf[0] = MetaType::Int32;
	switch (_order)
	{
	//大端存储
	case ByteOrder::BigEndian:
		buf[1] = pv(3);
		buf[2] = pv(2);
		buf[3] = pv(1);
		buf[4] = pv(0);
		break;
	//小端
	case ByteOrder::LittleEndian:
		buf[1] = pv(0);
		buf[2] = pv(1);
		buf[3] = pv(2);
		buf[4] = pv(3);
		break;
	}
	write((char*)buf, 5);
	return *this;
}

SDataStream& SDataStream::operator<<(uint32_t v)
{
	uint8_t buf[5] = { 0 };
	buf[0] = MetaType::UInt32;
	switch (_order)
	{
	case ByteOrder::BigEndian:
		buf[1] = pv(3);
		buf[2] = pv(2);
		buf[3] = pv(1);
		buf[4] = pv(0);
		break;
	case ByteOrder::LittleEndian:

		buf[1] = pv(0);
		buf[2] = pv(1);
		buf[3] = pv(2);
		buf[4] = pv(3);
		break;
	}
	write((char*)buf, 5);
	return *this;
}

SDataStream& SDataStream::operator<<(int64_t v)
{
	uint8_t buf[9] = { 0 };
	buf[0] = MetaType::Int64;
	switch (_order)
	{
	case ByteOrder::BigEndian:
		buf[1] = pv(7);
		buf[2] = pv(6);
		buf[3] = pv(5);
		buf[4] = pv(4);
		buf[5] = pv(3);
		buf[6] = pv(2);
		buf[7] = pv(1);
		buf[8] = pv(0);
		break;
	case ByteOrder::LittleEndian:

		buf[1] = pv(0);
		buf[2] = pv(1);
		buf[3] = pv(2);
		buf[4] = pv(3);
		buf[5] = pv(4);
		buf[6] = pv(5);
		buf[7] = pv(6);
		buf[8] = pv(7);
		break;
	}
	write((char*)buf, 9);
	return *this;
}

SDataStream& SDataStream::operator<<(uint64_t v)
{
	uint8_t buf[9] = { 0 };
	buf[0] = MetaType::UInt64;
	switch (_order)
	{
	case ByteOrder::BigEndian:
		buf[1] = pv(7);
		buf[2] = pv(6);
		buf[3] = pv(5);
		buf[4] = pv(4);
		buf[5] = pv(3);
		buf[6] = pv(2);
		buf[7] = pv(1);
		buf[8] = pv(0);
		break;
	case ByteOrder::LittleEndian:

		buf[1] = pv(0);
		buf[2] = pv(1);
		buf[3] = pv(2);
		buf[4] = pv(3);
		buf[5] = pv(4);
		buf[6] = pv(5);
		buf[7] = pv(6);
		buf[8] = pv(7);
		break;
	}
	write((char*)buf, 9);
	return *this;
}

SDataStream& SDataStream::operator<<(float v)
{
	uint8_t buf[5] = { 0 };
	buf[0] = MetaType::Real32;
	buf[1] = pv(0);
	buf[2] = pv(1);
	buf[3] = pv(2);
	buf[4] = pv(3);

	write((char*)buf, 5);
	return *this;
}

SDataStream& SDataStream::operator<<(double v)
{
	uint8_t buf[9] = { 0 };
	buf[0] = MetaType::Real64;
	buf[1] = pv(0);
	buf[2] = pv(1);
	buf[3] = pv(2);
	buf[4] = pv(3);
	buf[5] = pv(4);
	buf[6] = pv(5);
	buf[7] = pv(6);
	buf[8] = pv(7);

	write((char*)buf, 9);
	return *this;
}

SDataStream& SDataStream::operator<<(const char* v)
{
	size_t srcLen = strlen(v);
	uint8_t* psrc = (uint8_t*)&srcLen;

	uint8_t* buf = new uint8_t[9 + srcLen];
	buf[0] = MetaType::String;
	//写入字符串长度
	switch (_order)
	{
	case ByteOrder::BigEndian:
		for (int i = 0; i < 8; i++)
		{
			buf[i + 1] = psrc[7 - i];
		}
		break;
	case ByteOrder::LittleEndian:
		for (int i = 0; i < 8; i++)
		{
			buf[i + 1] = psrc[i];
		}
		break;
	};
	//写入数据
	for (int i = 0; i < srcLen; ++i)
	{
		buf[9 + i] = v[i];
	}

	write((char*)buf, 9 + srcLen);
	delete[] buf;
	return *this;
}

SDataStream& SDataStream::operator<<(const std::string& v)
{
	SDataStream::operator<<(v.data());
	return *this;
}

std::ostream& operator<<(std::ostream& out, const SDataStream& other)
{
	//throw gcnew System::NotImplementedException();

	for (auto c : other._data)
	{
		if (c == '\0')
			std::cout << "\\x0";
		else if (c >= -1 && c <= 255 && isprint(c))
			std::cout << (uint8_t)c;
		else
			std::cout << "\\x" << std::to_string((uint8_t)c);
	}
	return out;
}
