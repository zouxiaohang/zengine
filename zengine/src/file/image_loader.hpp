#ifndef _IMAGE_LOADER_H_
#define _IMAGE_LOADER_H_

#include <string>

namespace zengine
{
	class imageLoader
	{
	public:
		explicit imageLoader(const std::string& path) :path_(path){}
		virtual ~imageLoader(){};

		virtual bool load() = 0;

	protected:
		std::string path_;

	protected:
		template<class T>
		struct fileScoped
		{
			explicit fileScoped(T& f) :file_(f){}
			~fileScoped(){ file_.close(); }
			T& file_;
		};
	};
}

#endif