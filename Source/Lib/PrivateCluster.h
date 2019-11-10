//
// Created by Xiaomi on 10.11.2019.
//

#ifndef CLUSTERING_PRIVATECLUSTER_H
#define CLUSTERING_PRIVATECLUSTER_H

#include <Cluster.h>
#include <mutex>

class PrivateCluster : public Cluster
{
public:
	PrivateCluster(const Point &Centroid);

	void AppendPoint(const Point &Point);
	void ClearPoints();

	float CountDistance(const Point &point) const;
	void UpdateCentroid();

	std::vector<Point> GetPoints() const override;
	Point GetCentroid() const override;

	std::string ToString() const override;

private:
	mutable std::mutex mutex;
	std::vector<Point> m_Points;
	Point m_Centroid;
};

using PrivateCluster_Ptr = std::shared_ptr<PrivateCluster>;


#endif //CLUSTERING_PRIVATECLUSTER_H
