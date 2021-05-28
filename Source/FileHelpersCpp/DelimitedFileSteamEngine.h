#pragma once
#include "FileSteamEngineBase.h"

namespace file_helpers_cpp
{
	/// <summary>
	/// 基于文件流的用于读取带分隔符的文本行记录的引擎。
	/// </summary>
	class __declspec(dllexport) DelimitedFileSteamEngine : public FileSteamEngineBase
	{
	private:
		/// <summary>
		/// 定义分隔符字段。
		/// </summary>
		std::string delimiter;

	public:
		/// <summary>
		/// 有参构造函数。
		/// </summary>
		/// <param name="delimiter">分隔符。</param>
		DelimitedFileSteamEngine(const std::string& delimiter);

		/// <summary>
		/// 析构函数。
		/// </summary>
		virtual ~DelimitedFileSteamEngine() = default;

		/// <summary>
		/// 打开一个文本文件，将文件中的所有文本读取到一个字符串类型的二维向量，然后关闭此文件。
		/// </summary>
		/// <param name="path">文件路径。</param>
		/// <param name="out_string_vector">包含文件所有行的字符串类型的二维向量。</param>
		/// <param name="error">错误信息。</param>
		/// <returns>是否完成读取操作。</returns>
		bool ReadFileAsStringVector(const std::string& path, std::vector<std::vector<std::string>>& out_string_vector, std::error_code error) const override;

		/// <summary>
		/// 打开一个文本文件，将文件中的所有文本读取到一个字符串类型的二维向量，然后关闭此文件。
		/// </summary>
		/// <param name="path">文件路径。</param>
		/// <param name="out_double_vector">包含文件所有行的double类型的二维向量。</param>
		/// <param name="error">错误信息。</param>
		/// <returns>是否完成读取操作。</returns>
		bool ReadFileAsDoubleVector(const std::string& path, std::vector<std::vector<double>>& out_double_vector, std::error_code error) const override;

		/// <summary>
		/// 创建一个新文件，向其中写入一个字符串类型的二维向量的集合，然后关闭该文件。
		/// </summary>
		/// <param name="path">要写入的文件。</param>
		/// <param name="contents">要写入文件的字符串类型的二维向量。</param>
		/// <param name="error">错误信息。</param>
		/// <returns>是否完成写入操作。</returns>
		bool WriteAllStringVector(const std::string& path, const std::vector<std::vector<std::string>>& contents, std::error_code error) const override;

		/// <summary>
		/// 创建一个新文件，向其中写入一个double类型的二维向量的集合，然后关闭该文件。
		/// </summary>
		/// <param name="path">要写入的文件。</param>
		/// <param name="contents">要写入文件的double类型的二维向量。</param>
		/// <param name="error">错误信息。</param>
		/// <returns>是否完成写入操作。</returns>
		bool WriteAllDoubleVector(const std::string& path, const std::vector<std::vector<double>>& contents, std::error_code error) const override;
	};
}
