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
	const char * const file::header_ = "zengine image";

	file::file(const std::string& filePath)
	{
		assert(filePath != "");

		close();

		ifs_.open(filePath);
		assert(ifs_.is_open());

		std::string fileHeader;
		std::getline(ifs_, fileHeader);
		assert(fileHeader == header_);

		std::string strVerticeNum, verticesLine;
		std::getline(ifs_, strVerticeNum);
		auto verticeNum = atoi(strVerticeNum.c_str());
		//vertices_.resize(verticeNum);
		
		while (std::getline(ifs_, verticesLine) && verticeNum--)
		{
			//std::stringstream ss(verticesLine);
			auto vertices = split(verticesLine);
			for (const auto& v : vertices)
			{
				vertices_.emplace_back(toVector3(v));
			}
		}
	}

	std::vector<std::string> file::split(const std::string& verticeLine, const std::string& delimiter)const
	{
		std::vector<std::string> vs;
		size_t prev = 0;
		auto curr = verticeLine.find(" ");
		while (curr != std::string::npos)
		{
			vs.emplace_back(verticeLine.substr(prev, curr));
			prev = curr + 1;
			curr = verticeLine.find(" ", prev);
		}
		vs.emplace_back(verticeLine.substr(prev, verticeLine.size()));
		return vs;
	}

	void file::close()
	{
		if (ifs_.is_open())
			ifs_.close();
	}

	modelPtr file::getModel()const
	{
		return std::make_shared<model>(vertices_);
	}
}