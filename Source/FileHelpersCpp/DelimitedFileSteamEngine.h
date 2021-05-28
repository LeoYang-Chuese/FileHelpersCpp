#pragma once
#include "FileSteamEngineBase.h"

namespace file_helpers_cpp
{
	/// <summary>
	/// �����ļ��������ڶ�ȡ���ָ������ı��м�¼�����档
	/// </summary>
	class __declspec(dllexport) DelimitedFileSteamEngine : public FileSteamEngineBase
	{
	private:
		/// <summary>
		/// ����ָ����ֶΡ�
		/// </summary>
		std::string delimiter;

	public:
		/// <summary>
		/// �вι��캯����
		/// </summary>
		/// <param name="delimiter">�ָ�����</param>
		DelimitedFileSteamEngine(const std::string& delimiter);

		/// <summary>
		/// ����������
		/// </summary>
		virtual ~DelimitedFileSteamEngine() = default;

		/// <summary>
		/// ��һ���ı��ļ������ļ��е������ı���ȡ��һ���ַ������͵Ķ�ά������Ȼ��رմ��ļ���
		/// </summary>
		/// <param name="path">�ļ�·����</param>
		/// <param name="out_string_vector">�����ļ������е��ַ������͵Ķ�ά������</param>
		/// <param name="error">������Ϣ��</param>
		/// <returns>�Ƿ���ɶ�ȡ������</returns>
		bool ReadFileAsStringVector(const std::string& path, std::vector<std::vector<std::string>>& out_string_vector, std::error_code error) const override;

		/// <summary>
		/// ��һ���ı��ļ������ļ��е������ı���ȡ��һ���ַ������͵Ķ�ά������Ȼ��رմ��ļ���
		/// </summary>
		/// <param name="path">�ļ�·����</param>
		/// <param name="out_double_vector">�����ļ������е�double���͵Ķ�ά������</param>
		/// <param name="error">������Ϣ��</param>
		/// <returns>�Ƿ���ɶ�ȡ������</returns>
		bool ReadFileAsDoubleVector(const std::string& path, std::vector<std::vector<double>>& out_double_vector, std::error_code error) const override;

		/// <summary>
		/// ����һ�����ļ���������д��һ���ַ������͵Ķ�ά�����ļ��ϣ�Ȼ��رո��ļ���
		/// </summary>
		/// <param name="path">Ҫд����ļ���</param>
		/// <param name="contents">Ҫд���ļ����ַ������͵Ķ�ά������</param>
		/// <param name="error">������Ϣ��</param>
		/// <returns>�Ƿ����д�������</returns>
		bool WriteAllStringVector(const std::string& path, const std::vector<std::vector<std::string>>& contents, std::error_code error) const override;

		/// <summary>
		/// ����һ�����ļ���������д��һ��double���͵Ķ�ά�����ļ��ϣ�Ȼ��رո��ļ���
		/// </summary>
		/// <param name="path">Ҫд����ļ���</param>
		/// <param name="contents">Ҫд���ļ���double���͵Ķ�ά������</param>
		/// <param name="error">������Ϣ��</param>
		/// <returns>�Ƿ����д�������</returns>
		bool WriteAllDoubleVector(const std::string& path, const std::vector<std::vector<double>>& contents, std::error_code error) const override;
	};
}
