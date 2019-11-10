//
// Created by Xiaomi on 09.11.2019.
//

#ifndef CLUSTERING_ALGORITHMIMPL_H
#define CLUSTERING_ALGORITHMIMPL_H

#include <Algorithm.h>
#include <Cluster.h>

class PrivateCluster;
enum class Error;

class AlgorithmImpl
{
public:
	Algorithm::ClusteringResult Clustering(const std::string &sFilePath, uint8_t nClustersCount, uint8_t nMaxIterationsCount);

private:
	void ClearData();

	std::optional<Error> LoadPoints(const std::string &sFilePath);
	void InitClusters(uint8_t nClustersCount);
	size_t GenerateRandomPointIndex() const;
	void CountNewCentroids();
	void DistributePointsInClusters();
	std::vector<Cluster::Point> GetClusterCentroids() const;

	std::vector<Cluster::Point> m_Points;
	std::vector<std::shared_ptr<PrivateCluster>> m_Clusters;
	void AppendPointIntoNearestCluster(const Cluster::Point &Point);
};


#endif //CLUSTERING_ALGORITHMIMPL_H
