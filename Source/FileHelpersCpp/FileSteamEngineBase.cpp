#include "pch.h"
#include <fstream>
#include <iostream>
#include "FileSteamEngineBase.h"

using namespace file_helpers_cpp;

/// <summary>
/// ͳ��һ���ļ���������
/// </summary>
/// <param name="path">�ļ�·����</param>
/// <param name="error">������Ϣ��</param>
/// <returns>�ļ��������ı���������</returns>
int FileSteamEngineBase::CountLines(const std::string& path, std::error_code error) const
{
	int line_count = 0;
	std::ifstream infile(path.c_str(), std::ios::in);

	if (!infile.good())
	{
		error = std::make_error_code(std::errc::bad_file_descriptor);
		return -1;
	}

	line_count = std::count(std::istreambuf_iterator<char>(infile),
		std::istreambuf_iterator<char>(), '\n');

	infile.close();
	return line_count;
}

/// <summary>
/// ��һ���ı��ļ������ļ��е������ı���ȡ��һ���ַ����У�Ȼ��رմ��ļ���
/// </summary>
/// <param name="path">�ļ�·����</param>
/// <param name="out_all_text">�����ļ��������ı����ַ�����</param>
/// <param name="error">������Ϣ��</param>
/// <returns>�Ƿ���ɶ�ȡ������</returns>
bool FileSteamEngineBase::ReadAllText(const std::string& path, std::string& out_all_text, std::error_code error)  const
{
	std::ifstream infile;
	infile.open(path, std::ios::in);
	if (!infile.is_open())
	{
		error = std::make_error_code(std::errc::bad_file_descriptor);
		return false;
	}
	infile >> out_all_text;
	infile.close();
	return true;
}

/// <summary>
/// ��һ���ı��ļ������ļ��������ж���һ���ַ���������Ȼ��رո��ļ���
/// </summary>
/// <param name="path">�ļ�·����</param>
/// <param name="out_all_lines">�����ļ������е��ַ���������</param>
/// <param name="error">������Ϣ��</param>
/// <returns>�Ƿ���ɶ�ȡ������</returns>
bool FileSteamEngineBase::ReadAllLines(const std::string& path, std::vector<std::string>& out_all_lines, std::error_code error) const
{
	const int line_count = CountLines(path, error);
	out_all_lines.reserve(line_count);
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
		if (str_line == "\r\n")
		{
			str_line.clear();
			continue;
		}

		out_all_lines.push_back(str_line);
		str_line.clear();
	}
	infile.close();
	return true;
}

/// <summary>
/// ��һ���ı��ļ������ļ��������ж���һ���ַ���������Ȼ��رո��ļ���
/// </summary>
/// <param name="path">�ļ�·����</param>
/// <param name="out_all_lines">�����ļ������е��ַ���������</param>
/// <param name="error">������Ϣ��</param>
/// <param name="start_line">��ʼ��ȡ�ı�����ʼ�С���1��ʼ��</param>
/// <param name="max_records">Ҫ��ȡ������¼����Int32.MaxValue��-1��ʾ��ȡ���м�¼��</param>
/// <returns>�Ƿ���ɶ�ȡ������</returns>
bool FileSteamEngineBase::ReadAllLines(const std::string& path, std::vector<std::string>& out_all_lines, std::error_code error, int start_line, int max_records)  const
{
	out_all_lines.reserve(max_records);
	std::ifstream infile;
	infile.open(path, std::ios::in);
	if (!infile.is_open())
	{
		error = std::make_error_code(std::errc::bad_file_descriptor);
		return false;
	}

	std::string str_line;
	int readed_line_number = 1;

	while (getline(infile, str_line))
	{
		// �ǿ����ж�
		if (str_line != "\r\n" && readed_line_number >= start_line)
		{
			out_all_lines.push_back(str_line);
			if (out_all_lines.size() >= max_records)
			{
				break;
			}
		}

		str_line.clear();
		readed_line_number++;
	}

	return true;
}

/// <summary>
/// ����һ�����ļ���������д��ָ�����ַ�����Ȼ��ر��ļ��� ���Ŀ���ļ��Ѵ��ڣ��򸲸Ǹ��ļ���
/// </summary>
/// <param name="path">Ҫд����ļ���</param>
/// <param name="contents">Ҫд���ļ����ַ�����</param>
/// <param name="error">������Ϣ��</param>
/// <returns>�Ƿ����д�������</returns>
bool FileSteamEngineBase::WriteAllText(const std::string& path, const std::string& contents, std::error_code error) const
{
	// ʼ�ո��Ǵ������ļ���
	PreAllocateFile(path);

	std::ofstream outfile(path);
	outfile << contents << std::endl;
	outfile.close();
	return true;
}

/// <summary>
/// ����һ�����ļ���������д��һ���ַ������ϣ�Ȼ��رո��ļ���
/// </summary>
/// <param name="path">Ҫд����ļ���</param>
/// <param name="contents">Ҫд�뵽�ļ��е��С�</param>
/// <param name="error">������Ϣ��</param>
/// <returns>�Ƿ����д�������</returns>
bool FileSteamEngineBase::WriteAllLines(const std::string& path, const std::vector<std::string>& contents, std::error_code error) const
{
	// ʼ�ո��Ǵ������ļ���
	PreAllocateFile(path);

	std::ofstream outfile(path, std::ios::app);
	for (const auto& line : contents)
	{
		outfile << line << std::endl;
	}
	outfile.close();
	return true;
}