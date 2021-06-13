#pragma once
#include "FileMMFEngineBase.h"

namespace file_helpers_cpp
{
	/// <summary>
	/// �����ڴ�ӳ���ļ������ڶ�ȡ���ָ������ı��м�¼�����档
	/// </summary>
	class __declspec(dllexport) DelimitedFileMmfEngine : public FileMmfEngineBase
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
		DelimitedFileMmfEngine(const std::string& delimiter);

		/// <summary>
		/// ����������
		/// </summary>
		virtual ~DelimitedFileMmfEngine() = default;

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

		/// <summary>
		/// ��ָ���ļ��������޸�ָ�������ֶε�ֵ��Ȼ��رո��ļ�����ֵ�;�ֵ����һ�£������ڴ�ӳ���ļ��쳣��
		/// </summary>
		/// <param name="path">Ҫ�޸ĵ��ļ���</param>
		/// <param name="contents">Ҫ�޸��ļ����ַ������͵Ķ�ά���ݶԡ�</param>
		/// <param name="error">������Ϣ��</param>
		/// <returns>�Ƿ�����޸Ĳ�����</returns>
		bool BatchModifyFieldValues(const std::string& path, const std::map<int, std::map<int, std::string>>& contents, std::error_code error) const override;
	};
}
