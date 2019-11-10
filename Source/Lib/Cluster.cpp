//
// Created by Xiaomi on 10.11.2019.
//

#include <Cluster.h>
#include <ostream>
#include <cassert>
#include <sstream>

std::ostream &operator<<(std::ostream &stream, const Cluster::Point &Point) {
	stream << "[ ";
	for (auto &value : Point) {
		stream << value << ", ";
	}
	stream << "]";
	return stream;
}

std::ostream &operator<<(std::ostream &stream, const std::vector<Cluster::Point> &Points) {
	stream << "{";
	for (auto &Point : Points) {
		stream << Point << std::endl;
	}
	stream << "}";
	return stream;
}

std::ostream &operator<<(std::ostream &stream, const std::vector<Cluster_Ptr> &Clusters) {
	for (auto &Cluster_ptr : Clusters) {
		stream << "Cluster = { " << Cluster_ptr->ToString() << " }" << std::endl;
	}
	return stream;
}
