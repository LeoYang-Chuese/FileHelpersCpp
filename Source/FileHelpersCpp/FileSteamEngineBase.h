#pragma once
#include <string>
#include <system_error>
#include <vector>
#include "FileEngineBase.h"

namespace file_helpers_cpp
{
	/// <summary>
	/// ��ʾ��ȡ�ı��м�¼�����档�ļ����Ķ�ȡ��ʽ��
	/// </summary>
	class __declspec(dllexport) FileSteamEngineBase : public FileEngineBase
	{
	protected:
		FileSteamEngineBase() = default;

		~FileSteamEngineBase() = default;

	public:
		//int CountLines(const std::string& path, std::error_code error) const override;
		//std::string ReadAllText(const std::string path, std::error_code error) const override;
		//std::vector<std::string> ReadAllLines(const std::string path, std::error_code error) const override;
		//std::vector<std::string> ReadAllLines(const std::string path, std::error_code error, int start_line, int max_records) const override;
		//std::vector<std::vector<std::string>> ReadFileAsStringVector(const std::string path, std::error_code error) const override;
		//std::vector<std::vector<double>> ReadFileAsDoubleVector(const std::string path, std::error_code error) const override;

		/// <summary>
		/// ͳ��һ���ļ���������
		/// </summary>
		/// <param name="path">�ļ�·����</param>
		/// <param name="error">������Ϣ��</param>
		/// <returns>�ļ��������ı���������</returns>
		int CountLines(const std::string& path, std::error_code error) const override;

		/// <summary>
		/// ��һ���ı��ļ������ļ��е������ı���ȡ��һ���ַ����У�Ȼ��رմ��ļ���
		/// </summary>
		/// <param name="path">�ļ�·����</param>
		/// <param name="out_all_text">�����ļ��������ı����ַ�����</param>
		/// <param name="error">������Ϣ��</param>
		/// <returns>�Ƿ���ɶ�ȡ������</returns>
		bool ReadAllText(const std::string& path, std::string& out_all_text, std::error_code error) const override;

		/// <summary>
		/// ��һ���ı��ļ������ļ��������ж���һ���ַ���������Ȼ��رո��ļ���
		/// </summary>
		/// <param name="path">�ļ�·����</param>
		/// <param name="out_all_lines">�����ļ������е��ַ���������</param>
		/// <param name="error">������Ϣ��</param>
		/// <returns>�Ƿ���ɶ�ȡ������</returns>
		bool ReadAllLines(const std::string& path, std::vector<std::string>& out_all_lines, std::error_code error) const override;

		/// <summary>
		/// ��һ���ı��ļ������ļ��������ж���һ���ַ���������Ȼ��رո��ļ���
		/// </summary>
		/// <param name="path">�ļ�·����</param>
		/// <param name="out_all_lines">�����ļ������е��ַ���������</param>
		/// <param name="error">������Ϣ��</param>
		/// <param name="start_line">��ʼ��ȡ�ı�����ʼ�С���1��ʼ��</param>
		/// <param name="max_records">Ҫ��ȡ������¼����Int32.MaxValue��-1��ʾ��ȡ���м�¼��</param>
		/// <returns>�Ƿ���ɶ�ȡ������</returns>
		bool ReadAllLines(const std::string& path, std::vector<std::string>& out_all_lines, std::error_code error, int start_line, int max_records) const override;

		/// <summary>
		/// ����һ�����ļ���������д��ָ�����ַ�����Ȼ��ر��ļ��� ���Ŀ���ļ��Ѵ��ڣ��򸲸Ǹ��ļ���
		/// </summary>
		/// <param name="path">Ҫд����ļ���</param>
		/// <param name="contents">Ҫд���ļ����ַ�����</param>
		/// <param name="error">������Ϣ��</param>
		/// <returns>�Ƿ����д�������</returns>
		bool WriteAllText(const std::string& path, const std::string& contents, std::error_code error) const override;

		/// <summary>
		/// ����һ�����ļ���������д��һ���ַ������ϣ�Ȼ��رո��ļ���
		/// </summary>
		/// <param name="path">Ҫд����ļ���</param>
		/// <param name="contents">Ҫд�뵽�ļ��е��С�</param>
		/// <param name="error">������Ϣ��</param>
		/// <returns>�Ƿ����д�������</returns>
		bool WriteAllLines(const std::string& path, const std::vector<std::string>& contents, std::error_code error) const override;
	};
}
