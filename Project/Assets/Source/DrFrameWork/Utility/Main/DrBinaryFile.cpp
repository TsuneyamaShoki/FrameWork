
//! Include
#include "DrBinaryFile.h"
#include <fstream>



//! Constructor
DrBinary::DrBinary() :m_bin(nullptr) ,m_size(0){};
DrBinary::DrBinary(DrString filename)
{
	Load(filename);
}
DrBinary::DrBinary(const DrBinary& bin)
{
	*this = bin;
}

//! Destructor
DrBinary::~DrBinary()
{
	DrSafeDelete(m_bin);
	m_size = 0;
}

//! Load Binary
DrBool DrBinary::Load(DrString fileName)
{
	UnLoad();

	std::ifstream ifs(fileName, std::ifstream::in | std::ifstream::binary);

	if (ifs.fail())
	{
		return DR_FALSE;
	}
	DrInt begin = static_cast<DrInt>(ifs.tellg());
	ifs.seekg(0, ifs.end);

	DrInt end = static_cast<DrInt>(ifs.tellg());
	m_size = (end - begin);
	ifs.clear();
	ifs.seekg(0, ifs.beg);
	m_bin = DrNew(DrByte[m_size]);
	//m_bin[m_size - 1] = '\0';  
	ifs.read((DrS8*)m_bin, m_size);

	return DR_TRUE;
}

//! Release Binary
void DrBinary::UnLoad()
{
	DrSafeDelete(m_bin);
}

//! Get Binary
DrByte* DrBinary::GetBinary()const
{
	return m_bin;
}

//! Get Binary Size
DrInt	DrBinary::GetSize()const
{
	return m_size;
}

//! Deep Copy
DrBinary DrBinary::operator=(const DrBinary& bin)
{
	m_size = bin.GetSize();
	if (m_size > 0)
	{
		m_bin = DrNew(DrByte[m_size]);
		memcpy_s(&m_bin, m_size, bin.GetBinary(), m_size);
	}
	else
		m_bin = nullptr;

	return *this;
}

//! 文字列にシーク
DrByte*	DrBinary::SeekString(const DrChar* target,
	DrInt startIndex, /*= 0 */
	DrInt* outIndex	/*= nullptr */)
{
	if (startIndex > m_size)
		return nullptr;

	DrInt index = startIndex;

	auto Cmp = [&]()
	{
		DrInt i = index;
		DrInt j = 0;
		while (target[j] != '\0' &&
			m_bin[i] != '\0')
		{
			if (target[j] != m_bin[i])
				return DR_FALSE;
			j++;
			i++;
		}

		return DR_TRUE;
	};

	while (m_bin[index] != '\0')
	{
		if (Cmp())
		{
			if (outIndex)
				*outIndex = index;
			return &m_bin[index];
		}

		++index;
	}
	return nullptr;
}

//! 数字にシーク
DrByte* DrBinary::SeekNumber(DrInt startIndex, /*= 0 */
	DrInt* outIndex	/*= nullptr */)
{
	if (startIndex > m_size)
		return nullptr;

	DrInt index = startIndex;

	for (;  m_bin[index] < '0' ||
		m_bin[index] > '9' ||
		m_bin[index] != '-'; ++index)
	{
	};

	if (outIndex)
		*outIndex = index;
	return &m_bin[index];

}