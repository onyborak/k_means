//
// Created by Xiaomi on 09.11.2019.
//

#ifndef CLUSTERING_ERROR_H
#define CLUSTERING_ERROR_H

#include <string>

enum class Error {
	FailedToReadFile,
	InvalidData
};

std::ostream &operator<<(std::ostream &stream, Error nError);

#endif //CLUSTERING_ERROR_H
