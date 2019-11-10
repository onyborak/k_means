#ifndef CLUSTERING_ALGORITHM_H
#define CLUSTERING_ALGORITHM_H

#include <optional>
#include <vector>
#include <memory>

enum class Error;
class Cluster;
using Cluster_Ptr = std::shared_ptr<Cluster>;
class AlgorithmImpl;

class Algorithm {
public:
	Algorithm();
	~Algorithm();

	struct ClusteringResult {
		std::optional<Error> m_Error;
		std::vector<Cluster_Ptr> m_Clusters;
	};
	ClusteringResult Clustering(const std::string &sFilePath, uint8_t nClustersCount, uint8_t nMaxIterationsCount);

private:
	std::unique_ptr<AlgorithmImpl> m_Impl_Ptr;
};

#endif //CLUSTERING_ALGORITHM_H
