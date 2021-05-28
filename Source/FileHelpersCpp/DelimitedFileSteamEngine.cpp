#include "pch.h"
#include <fstream>
#include "DelimitedFileSteamEngine.h"
#include "StringUtils.h"

using namespace file_helpers_cpp;

/// <summary>
/// �вι��캯����
/// </summary>
/// <param name="delimiter"></param>
DelimitedFileSteamEngine::DelimitedFileSteamEngine(const std::string& delimiter)
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
bool DelimitedFileSteamEngine::ReadFileAsStringVector(const std::string& path, std::vector<std::vector<std::string>>& out_string_vector, std::error_code error) const
{
	//const int line_count = FileSteamEngineBase::CountLines(path, error);
	//out_string_vector.reserve(line_count);

	std::ifstream infile;
	infile.open(path, std::ios::in);
	if (!infile.is_open())
	{
		error = std::make_error_code(std::errc::bad_file_descriptor);
		return false;
	}
	std::string str_line;
	while (std::getline(infile, str_line))
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
	}

	return true;
}

/// <summary>
/// ��һ���ı��ļ������ļ��е������ı���ȡ��һ���ַ������͵Ķ�ά������Ȼ��رմ��ļ���
/// </summary>
/// <param name="path">�ļ�·����</param>
/// <param name="out_double_vector">�����ļ������е�double���͵Ķ�ά������</param>
/// <param name="error">������Ϣ��</param>
/// <returns>�Ƿ���ɶ�ȡ������</returns>
bool DelimitedFileSteamEngine::ReadFileAsDoubleVector(const std::string& path, std::vector<std::vector<double>>& out_double_vector, std::error_code error) const
{
	//const int line_count = FileSteamEngineBase::CountLines(path, error);
	//out_double_vector.reserve(line_count);

	std::ifstream infile;
	infile.open(path, std::ios::in);
	if (!infile.is_open())
	{
		error = std::make_error_code(std::errc::bad_file_descriptor);
		return false;
	}
	std::string str_line;
	while (std::getline(infile, str_line))
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
	}

	return true;
}

/// <summary>
/// ����һ�����ļ���������д��һ���ַ������͵Ķ�ά�����ļ��ϣ�Ȼ��رո��ļ���
/// </summary>
/// <param name="path">Ҫд����ļ���</param>
/// <param name="contents">Ҫд���ļ����ַ������͵Ķ�ά������</param>
/// <param name="error">������Ϣ��</param>
/// <returns>�Ƿ����д�������</returns>
bool DelimitedFileSteamEngine::WriteAllStringVector(const std::string& path, const std::vector<std::vector<std::string>>& contents, std::error_code error) const
{
	// ʼ�ո��Ǵ������ļ���
	AllocateFile(path);

	std::ofstream outfile(path, std::ios::app);
	for (const auto& line_vector : contents)
	{
		int index = 0;
		for (auto field : line_vector)
		{
			index++;
			outfile << field;
			if (index < line_vector.size())
				outfile << delimiter;
		}
		outfile << "\n";
	}
	outfile.close();
	return true;
}

/// <summary>
/// ����һ�����ļ���������д��һ��double���͵Ķ�ά�����ļ��ϣ�Ȼ��رո��ļ����ļ������򸲸ǡ�
/// </summary>
/// <param name="path">Ҫд����ļ���</param>
/// <param name="contents">Ҫд���ļ���double���͵Ķ�ά������</param>
/// <param name="error">������Ϣ��</param>
/// <returns>�Ƿ����д�������</returns>
bool DelimitedFileSteamEngine::WriteAllDoubleVector(const std::string& path, const std::vector<std::vector<double>>& contents, std::error_code error) const
{
	// ʼ�ո��Ǵ������ļ���
	AllocateFile(path);

	std::ofstream outfile(path, std::ios::app);
	for (const auto& line_vector : contents)
	{
		int index = 0;
		for (auto field : line_vector)
		{
			index++;
			outfile << std::to_string(field);
			if (index < line_vector.size())
				outfile << delimiter;
		}
		outfile << "\n";
	}
	outfile.close();
	return true;
}
