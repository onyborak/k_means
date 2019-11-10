#include "Algorithm.h"

#include "AlgorithmImpl.h"

Algorithm::Algorithm() :
	m_Impl_Ptr(std::make_unique<AlgorithmImpl>()) {

}


Algorithm::ClusteringResult Algorithm::Clustering(const std::string &sFilePath,
												  uint8_t nClustersCount,
												  uint8_t nMaxIterationsCount) {
	return m_Impl_Ptr->Clustering(sFilePath, nClustersCount, nMaxIterationsCount);
}

Algorithm::~Algorithm() {

}
