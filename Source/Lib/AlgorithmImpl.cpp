//
// Created by Xiaomi on 09.11.2019.
//

#include "AlgorithmImpl.h"
#include <Error.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <chrono>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include "PrivateCluster.h"
#include "Concurrent.h"

namespace {
bool IsEqual(const std::vector<Cluster::Point> &lhs, const std::vector<Cluster::Point> &rhs) {
	assert(lhs.size() == rhs.size());
	for (size_t i = 0; i < lhs.size(); ++i) {
		auto &lhsPoint = lhs[i];
		auto &rhsPoint = rhs[i];
		assert(lhsPoint.size() == rhsPoint.size());
		for (size_t j = 0; j < lhsPoint.size(); ++j) {
			if (std::fabs(lhsPoint[j] - rhsPoint[j]) >= std::numeric_limits<float>::epsilon()) {
				return false;
			}
		}
	}
	return true;
}
}

Algorithm::ClusteringResult AlgorithmImpl::Clustering(const std::string &sFilePath,
													  uint8_t nClustersCount,
													  uint8_t nMaxIterationsCount) {
	ClearData();
	auto Error = LoadPoints(sFilePath);
	if (Error) {
		return {Error, {}};
	}
	if (nClustersCount >= m_Points.size()) {
		return {Error::InvalidData, {}};
	}
	InitClusters(nClustersCount);

	for (uint8_t i = 0; i < nMaxIterationsCount; ++i) {
		DistributePointsInClusters();
		auto oldCentroids = GetClusterCentroids();
		CountNewCentroids();

		if (IsEqual(oldCentroids, GetClusterCentroids())) {
			break;
		}
	}
	std::vector<Cluster_Ptr> Clusters;
	Clusters.reserve(m_Clusters.size());
	for (auto &Cluster_ptr : m_Clusters) {
		Clusters.push_back(Cluster_ptr);
	}
	return {{}, std::move(Clusters)};
}

std::optional<Error> AlgorithmImpl::LoadPoints(const std::string &sFilePath) {
	std::fstream File(sFilePath);
	if (!File.is_open()) {
		return Error::FailedToReadFile;
	}

	std::string sLine;
	while(std::getline(File, sLine)) {
		std::stringstream sstream(sLine);

		Cluster::Point Point;
		float fValue;
		while (sstream >> fValue) {
			Point.push_back(fValue);
		}
		m_Points.push_back(std::move(Point));
	}
	File.close();

	if (m_Points.empty()) {
		return Error::InvalidData;
	}

	auto nDeminsion = m_Points.front().size();
	for (size_t i = 1; i < m_Points.size(); ++i) {
		if (nDeminsion != m_Points[i].size()) {
			return Error::InvalidData;
		}
	}
	return {};
}

void AlgorithmImpl::ClearData() {
	m_Points.clear();
	m_Clusters.clear();
}

size_t AlgorithmImpl::GenerateRandomPointIndex() const {
	return static_cast<size_t>(std::rand() % m_Points.size());
}

void AlgorithmImpl::InitClusters(uint8_t nClustersCount) {
	m_Clusters.reserve(nClustersCount);
	std::srand(std::chrono::system_clock::now().time_since_epoch().count());
	std::unordered_set<size_t> UsedPointIndexes;
	for (uint8_t i = 0; i < nClustersCount; ++i) {
		auto nIndex = GenerateRandomPointIndex();
		while(!UsedPointIndexes.insert(nIndex).second) {
			nIndex = GenerateRandomPointIndex();
		}

		m_Clusters.push_back(std::make_shared<PrivateCluster>(m_Points[nIndex]));
	}
}

std::vector<Cluster::Point> AlgorithmImpl::GetClusterCentroids() const {
	std::vector<Cluster::Point> Centroids;
	Centroids.reserve(m_Clusters.size());
	for (auto &Cluster_ptr : m_Clusters) {
		Centroids.push_back(Cluster_ptr->GetCentroid());
	}
	return Centroids;
}

void AlgorithmImpl::AppendPointIntoNearestCluster(const Cluster::Point &Point) {
	auto iter = std::min_element(m_Clusters.begin(), m_Clusters.end(), [&Point](const PrivateCluster_Ptr &lhs, const PrivateCluster_Ptr &rhs) {
		return lhs->CountDistance(Point) < rhs->CountDistance(Point);
	});
	assert(iter != m_Clusters.end());
	(*iter)->AppendPoint(Point);
}

void AlgorithmImpl::DistributePointsInClusters() {
	for (auto &Cluster_ptr : m_Clusters) {
		Cluster_ptr->ClearPoints();
	}

	Concurrent::Execute<Cluster::Point>(m_Points, [this](Cluster::Point &Point) {
		AppendPointIntoNearestCluster(Point);
	});
}

void AlgorithmImpl::CountNewCentroids() {
	Concurrent::Execute<PrivateCluster_Ptr>(m_Clusters, [this](PrivateCluster_Ptr &Cluster_ptr) {
		Cluster_ptr->UpdateCentroid();
	});
}
