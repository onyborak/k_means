//
// Created by Xiaomi on 10.11.2019.
//

#include <Error.h>
#include <ostream>


std::ostream &operator<<(std::ostream &stream, Error nError) {
	switch (nError) {
		case Error::FailedToReadFile:
			stream << "FailedToReadFile";
			break;

		case Error::InvalidData:
			stream << "InvalidData";
			break;
	}
	return stream;
}

