//
// Created by Xiaomi on 09.11.2019.
//

#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include <vector>
#include <memory>

class Cluster {
public:
	using Point = std::vector<float>;

	virtual std::vector<Point> GetPoints() const = 0;
	virtual Point GetCentroid() const = 0;

	virtual std::string ToString() const = 0;
};

using Cluster_Ptr = std::shared_ptr<Cluster>;

std::ostream &operator<<(std::ostream &stream, const Cluster::Point &Point);
std::ostream &operator<<(std::ostream &stream, const std::vector<Cluster::Point> &Points);
std::ostream &operator<<(std::ostream &stream, const std::vector<Cluster_Ptr> &Clusters);

#endif //CLUSTERING_CLUSTER_H
