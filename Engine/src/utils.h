#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include "export.h"
#include <string>

namespace Utils {
	class ENGINE_API Debug {
	public:
		Debug();
		~Debug();
		static void DebugMessage(std::string mssg);

	};

}


#endif // !UTILS_H

