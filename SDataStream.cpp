#ifndef SDATASTREAM_H_
#define SDATASTREAM_H_
#include<string>
#include<ostream>
enum  MetaType :uint8_t
{
	Int8,
	UInt8,
	Int16,
	UInt16,
	Int32,
	UInt32,
	Int64,
	UInt64,
	Real32,
	Real64,
	String,

};

enum class ByteOrder
{
	BigEndian,			//大端
	LittleEndian		//小端
};

class SDataStream
{
public:
	SDataStream();

	void setByteOrder(ByteOrder order);
	ByteOrder byteOrder()const;

	std::string str()const;
	SDataStream& write(const char* s, uint32_t len);
	SDataStream& operator<<(int8_t v);
	SDataStream& operator<<(uint8_t v);
	SDataStream& operator<<(int16_t v);
	SDataStream& operator<<(uint16_t v);
	SDataStream& operator<<(int32_t v);
	SDataStream& operator<<(uint32_t v);
	SDataStream& operator<<(int64_t v);
	SDataStream& operator<<(uint64_t v);
	SDataStream& operator<<(float v);
	SDataStream& operator<<(double v);
	SDataStream& operator<<(const char* v);
	SDataStream& operator<<(const std::string& v);
	//友元函数，输出字符等
	friend std::ostream& operator<<(std::ostream& out, const SDataStream& other);
private:
	std::string _data;
	ByteOrder _order = ByteOrder::LittleEndian;
};
#endif // !SDATASTREAM_H_







