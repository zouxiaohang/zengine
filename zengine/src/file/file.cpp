#include "file.hpp"

#include <cassert>
#include <string>
#include <sstream>

namespace zengine
{
	namespace
	{
		vector3 toVector3(const std::string& vs)
		{
			auto pos1 = vs.find(",");
			auto pos2 = vs.rfind(",");

			auto strX = vs.substr(0, pos1);
			auto strY = vs.substr(pos1 + 1, pos2);
			auto strZ = vs.substr(pos2 + 1, vs.size());

			return vector3(std::stof(strX), std::stof(strY), std::stof(strZ));
		}
	}
	const char * const file::headerMagic_ = "zengine image";

	file::file(const std::string& filePath)
	{
		assert(filePath != "");

		close();

		ifs_.open(filePath);
		assert(ifs_.is_open());

		std::string fileHeader;
		std::getline(ifs_, fileHeader);
		assert(fileHeader == headerMagic_);

		std::string strVerticeNum, verticesLine;
		std::getline(ifs_, strVerticeNum);
		auto vn = atoi(strVerticeNum.c_str());
		header_.numOfVertices_ = vn;

		//parse vertices data
		{
			while (vn--)
			{
				std::getline(ifs_, verticesLine);
				auto v = split(verticesLine);
				{
					vertices_.emplace_back(toVector3(v[0]));
				}
				{
					if (v.size() >= 2)
					{
						auto t = split(v[1], ",");
						tcs_.emplace_back(std::stof(t[0]), std::stof(t[1]));
					}
				}
				
			}
			assert(header_.numOfVertices_ == vertices_.size());
		}
	}

	std::vector<std::string> file::split(const std::string& verticeLine, const std::string& delimiter)const
	{
		std::vector<std::string> vs;
		size_t prev = 0;
		auto curr = verticeLine.find(delimiter);
		while (curr != std::string::npos)
		{
			vs.emplace_back(verticeLine.substr(prev, curr - prev));
			prev = curr + 1;
			curr = verticeLine.find(delimiter, prev);
		}
		vs.emplace_back(verticeLine.substr(prev, verticeLine.size() - prev));
		return vs;
	}

	void file::close()
	{
		if (ifs_.is_open())
			ifs_.close();
	}

	modelPtr file::getModel()const
	{
		return std::make_shared<model>(vertices_, tcs_);
	}
}