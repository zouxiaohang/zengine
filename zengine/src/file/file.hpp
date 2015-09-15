#ifndef _FILE_H_
#define _FILE_H_

#include "../math/vector.hpp"
#include "../core/model.hpp"

#include <fstream>
#include <memory>
#include <vector>

namespace zengine
{
	class file
	{
	public:
		using modelPtr = std::shared_ptr<model>;
	public:
		explicit file(const std::string& filePath);
		~file(){ close(); }
		file(const file&) = delete;
		file& operator = (const file&) = delete;

		//std::vector<vector3> vertices()const{ return vertices_; }
		//size_t vSize()const{ return vertices_.size(); }

		modelPtr getModel()const;
	private:
		void close();
		std::vector<std::string> split(const std::string& verticeLine, const std::string& delimiter = " ")const;

	private:
		struct header
		{
			header(std::size_t nv = 0) :numOfVertices_(nv){}
			std::size_t numOfVertices_;
		};
	private:
		std::ifstream ifs_;
		std::vector<vector3> vertices_;
		header header_;
	private:
		static const char * const headerMagic_;
	};
}

#endif