#include "pch.h"
#include <map>
#include <queue>
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

				// �����û��ÿ�е����һ���ֶΣ�����Ҫд��ָ�����
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

/// <summary>
/// ��ָ���ļ��������޸�ָ�������ֶε�ֵ��Ȼ��رո��ļ�����ֵ�;�ֵ����һ�£������ڴ�ӳ���ļ��쳣��
/// </summary>
/// <param name="path">Ҫ�޸ĵ��ļ���</param>
/// <param name="contents">Ҫ�޸��ļ����ַ������͵Ķ�ά���ݶԡ�<����������0��ʼ����<�ֶ���������0��ʼ���Էָ����ָ���µ��ֶ�ֵ>></param>
/// <param name="error">������Ϣ��</param>
/// <returns>�Ƿ�����޸Ĳ�����</returns>
bool DelimitedFileMmfEngine::BatchModifyFieldValues(const std::string& path, const std::map<int, std::map<int, std::string>>& contents, std::error_code error) const
{
	try
	{
		mio::mmap_sink rw_mmap = mio::make_mmap_sink(path, error);
		if (error)
		{
			return false;
		}

		// ��ȡ���ַ�������
		int char_index = 0;
		// ��ȡ����������
		int line_index = 0;
		// ��ȡ�����ı���
		std::string str_line;

		// ���п�ʼ�����ַ�������
		int new_line_char_index = 0;

		// ��ʾ��һ�еĴ��޸��ֶε�������¼��<�ڼ����ֶ�,�ֶο�ʼ�����ַ�����>
		std::map<int, int> last_line_field_index_record;

		for (auto c : rw_mmap)
		{
			if (contents.empty())
			{
				return true;
			}
			if (c == '\r')
			{
				char_index++;
				continue;
			}
			if (c == '\n')
			{
				// �����ж�
				if (std::strlen(str_line.c_str()) == 0)
				{
					char_index++;
					// һ�ж�ȡ��Ϻ��ۼƶ������ַ�������Ϊ�������������������Ѿ� +1��
					new_line_char_index = char_index;
					continue;
				}

				// �Ӵ��޸����в�����Ҫ�޸ĵ��С�
				auto iter = contents.find(line_index);
				// �ҵ����޸��С�
				if (iter != contents.end())
				{
					std::vector<std::string> str_fields = Split(str_line, this->delimiter, true);

					int field_index = 0;
					// ��Ҫ�޸ĵ��д�������ǰ�����и��ֶε�char�����洢���������޸�ʹ�á�
					for (auto field : str_fields)
					{
						if (last_line_field_index_record.empty())
						{
							last_line_field_index_record.insert(std::pair<int, int>(field_index, new_line_char_index));
						}
						else
						{
							// �ӵڶ����ֶο�ʼ����Ҫ�ۼ�ǰһ���ֶε�size�ͷָ�����size��
							const auto end_iter = last_line_field_index_record.rbegin();
							const int last_field_index = end_iter->second;
							const int last_field_size = static_cast<int>(str_fields[end_iter->first].size());
							const int delimiter_size = static_cast<int>(delimiter.size());
							const int field_start_index = last_field_index + last_field_size + delimiter_size;
							last_line_field_index_record.insert(std::pair<int, int>(field_index, field_start_index));
						}
						field_index++;
					}

					// ���ݶ�Ӧ�ֶε�������ʼ��һ�ַ��޸ġ�
					std::map<int, std::string> modified_fields = iter->second;
					for (const auto& modified_field : modified_fields)
					{
						int modify_index = last_line_field_index_record[modified_field.first];
						for (auto cha : modified_field.second)
						{
							rw_mmap[modify_index] = cha;
							modify_index++;
						}
					}
				}
				last_line_field_index_record.clear();
				str_line.clear();

				char_index++;
				line_index++;
				// һ�ж�ȡ��Ϻ��ۼƶ������ַ�������Ϊ�������������������Ѿ� +1��
				new_line_char_index = char_index;
				continue;
			}
			char_index++;
			str_line += c;
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
