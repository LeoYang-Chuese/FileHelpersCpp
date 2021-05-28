#include "pch.h"
#include "mio.hpp"
#include "DelimitedFileMMFEngine.h"
#include "StringUtils.h"

using namespace file_helpers_cpp;

/// <summary>
/// �вι��캯����
/// </summary>
/// <param name="delimiter"></param>
DelimitedFileMmfEngine::DelimitedFileMmfEngine(const std::string& delimiter)
{
	this->delimiter = delimiter;
}

/// <summary>
/// ��һ���ı��ļ������ļ��е������ı���ȡ��һ���ַ������͵Ķ�ά������Ȼ��رմ��ļ���
/// </summary>
/// <param name="path">�ļ�·����</param>
/// <param name="out_string_vector">�����ļ������е��ַ������͵Ķ�ά������</param>
/// <param name="error">������Ϣ��</param>
/// <returns>�Ƿ���ɶ�ȡ������</returns>
bool DelimitedFileMmfEngine::ReadFileAsStringVector(const std::string& path, std::vector<std::vector<std::string>>& out_string_vector, std::error_code error) const
{
	const int line_count = FileMmfEngineBase::CountLines(path, error);
	out_string_vector.reserve(line_count);

	mio::mmap_source read_mmap = mio::make_mmap_source(path, error);
	if (error)
	{
		return false;
	}

	std::string str_line;

	for (auto& c : read_mmap)
	{
		if (c == '\r')
		{
			// �����ж�
			if (std::strlen(str_line.c_str()) == 0)
			{
				str_line.clear();
				continue;
			}

			std::vector<std::string> str_fields = Split(str_line, this->delimiter, true);
			out_string_vector.push_back(str_fields);
			str_line.clear();
			continue;
		}
		if (c == '\n')
		{
			continue;
		}
		str_line += c;
	}

	read_mmap.unmap();
	return true;
}

/// <summary>
/// ��һ���ı��ļ������ļ��е������ı���ȡ��һ���ַ������͵Ķ�ά������Ȼ��رմ��ļ���
/// </summary>
/// <param name="path">�ļ�·����</param>
/// <param name="out_double_vector">�����ļ������е�double���͵Ķ�ά������</param>
/// <param name="error">������Ϣ��</param>
/// <returns>�Ƿ���ɶ�ȡ������</returns>
bool DelimitedFileMmfEngine::ReadFileAsDoubleVector(const std::string& path, std::vector<std::vector<double>>& out_double_vector, std::error_code error) const
{
	const int line_count = FileMmfEngineBase::CountLines(path, error);
	out_double_vector.reserve(line_count);

	mio::mmap_source read_mmap = mio::make_mmap_source(path, error);
	if (error)
	{
		return false;
	}

	std::string str_line;

	for (auto& c : read_mmap)
	{
		if (c == '\r')
		{
			// �����ж�
			if (std::strlen(str_line.c_str()) == 0)
			{
				str_line.clear();
				continue;
			}

			std::vector<double> double_fields = SplitIntoDouble(str_line, this->delimiter, true);
			out_double_vector.push_back(double_fields);
			str_line.clear();
			continue;
		}
		if (c == '\n')
		{
			continue;
		}
		str_line += c;
	}

	read_mmap.unmap();
	return true;
}

/// <summary>
/// ����һ�����ļ���������д��һ���ַ������͵Ķ�ά�����ļ��ϣ�Ȼ��رո��ļ���
/// </summary>
/// <param name="path">Ҫд����ļ���</param>
/// <param name="contents">Ҫд���ļ����ַ������͵Ķ�ά������</param>
/// <param name="error">������Ϣ��</param>
/// <returns>�Ƿ����д�������</returns>
bool DelimitedFileMmfEngine::WriteAllStringVector(const std::string& path, const std::vector<std::vector<std::string>>& contents, std::error_code error) const
{
	try
	{
		long characters_size = 0;
		const int delimiter_size = delimiter.size();

		// ����contentsռ�õ��ַ���������ʽ����󳤶ȡ�
		for (std::vector<std::string> line_vector : contents)
		{
			const int rn_size = 1;
			int field_index = 0;
			for (auto field : line_vector)
			{
				field_index++;
				characters_size += field.size();
				if (field_index < line_vector.size())
					characters_size += delimiter_size;
			}
			// ���ϻ��з�����
			characters_size += 1;
		}

		// ʼ�ո��Ǵ������ļ���
		std::string error_msg;
		const bool result = PreAllocateFile(path, error_msg, characters_size);
		if (!result)
		{
			return false;
		}

		mio::mmap_sink rw_mmap = mio::make_mmap_sink(path, error);
		if (error)
		{
			return false;
		}

		int char_index = 0;
		int line_index = 0;
		for (std::vector<std::string> line_vector : contents)
		{
			line_index++;
			int field_index = 0;
			for (auto field : line_vector)
			{
				field_index++;
				for (auto c : field)
				{
					rw_mmap[char_index] = c;
					char_index++;
				}

				if (field_index < line_vector.size())
				{
					for (auto c : delimiter)
					{
						rw_mmap[char_index] = c;
						char_index++;
					}
				}
			}
			rw_mmap[char_index] = '\n';
			char_index++;

			// ע�⣺�����ԣ�ÿ80w������ͬ��һ�����ܺ��ڴ�ռ����ѡ�
			if (line_index >= 800000)
			{
				rw_mmap.sync(error);
				line_index = 0;
			}
		}

		rw_mmap.sync(error);
		rw_mmap.unmap();
		return true;
	}
	catch (std::exception& ex)
	{
		auto msg = ex.what();
		return false;
	}
}

/// <summary>
/// ����һ�����ļ���������д��һ��double���͵Ķ�ά�����ļ��ϣ�Ȼ��رո��ļ����ļ������򸲸ǡ�
/// </summary>
/// <param name="path">Ҫд����ļ���</param>
/// <param name="contents">Ҫд���ļ���double���͵Ķ�ά������</param>
/// <param name="error">������Ϣ��</param>
/// <returns>�Ƿ����д�������</returns>
bool DelimitedFileMmfEngine::WriteAllDoubleVector(const std::string& path, const std::vector<std::vector<double>>& contents, std::error_code error) const
{
	try
	{
		long characters_size = 0;
		const int delimiter_size = delimiter.size();

		// ����contentsռ�õ��ַ���������ʽ����󳤶ȡ�
		for (std::vector<double> line_vector : contents)
		{
			const int rn_size = 1;
			int field_index = 0;
			for (auto field : line_vector)
			{
				field_index++;
				const auto field_str = std::to_string(field);
				characters_size += field_str.size();
				if (field_index < line_vector.size())
					characters_size += delimiter_size;
			}
			// ���ϻ��з�����
			characters_size += 1;
		}

		// ʼ�ո��Ǵ������ļ���
		std::string error_msg;
		const bool result = PreAllocateFile(path, error_msg, characters_size);
		if (!result)
		{
			return false;
		}

		mio::mmap_sink rw_mmap = mio::make_mmap_sink(path, error);
		if (error)
		{
			return false;
		}

		int char_index = 0;
		int line_index = 0;
		for (std::vector<double> line_vector : contents)
		{
			line_index++;
			int field_index = 0;
			for (auto field : line_vector)
			{
				field_index++;
				const auto field_str = std::to_string(field);
				for (auto c : field_str)
				{
					rw_mmap[char_index] = c;
					char_index++;
				}

				if (field_index < line_vector.size())
				{
					for (auto c : delimiter)
					{
						rw_mmap[char_index] = c;
						char_index++;
					}
				}
			}

			rw_mmap[char_index] = '\n';
			char_index++;

			// ע�⣺�����ԣ�ÿ80w������ͬ��һ�����ܺ��ڴ�ռ����ѡ�
			if (line_index >= 800000)
			{
				rw_mmap.sync(error);
				line_index = 0;
			}
		}

		rw_mmap.sync(error);
		rw_mmap.unmap();
		return true;
	}
	catch (std::exception& ex)
	{
		auto msg = ex.what();
		return false;
	}
}
