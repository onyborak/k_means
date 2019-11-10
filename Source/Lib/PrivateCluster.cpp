//
// Created by Xiaomi on 10.11.2019.
//

#include "PrivateCluster.h"
#include <ostream>
#include <cassert>
#include <sstream>


PrivateCluster::PrivateCluster(const Point &Centroid) :
	m_Centroid(Centroid) {

}

std::vector<Cluster::Point> PrivateCluster::GetPoints() const {
	return m_Points;
}

Cluster::Point PrivateCluster::GetCentroid() const {
	return m_Centroid;
}

void PrivateCluster::ClearPoints() {
	m_Points.clear();
}

std::string PrivateCluster::ToString() const {
	std::stringstream ss;
	ss << "Centroid = " << m_Centroid << " | Points = " << m_Points.size();
	return ss.str();
}

float PrivateCluster::CountDistance(const Cluster::Point &point) const {
	assert(point.size() == m_Centroid.size());
	float fSum = 0;
	for (size_t i = 0; i < point.size(); ++i) {
		fSum += std::pow(point[i] - m_Centroid[i], 2);
	}
	return sqrt(fSum);
}

void PrivateCluster::AppendPoint(const Point &Point) {
	std::lock_guard lock(mutex);
	m_Points.push_back(Point);
}

void PrivateCluster::UpdateCentroid() {
	m_Centroid.clear();
	if (m_Points.empty()) {
		return;
	}

	m_Centroid.resize(m_Points.front().size(), 0);
	for (auto Point : m_Points) {
		for (size_t i = 0; i < Point.size(); ++i) {
			m_Centroid[i] += Point[i];
		}
	}
	for (auto &fValue : m_Centroid) {
		fValue = fValue / m_Points.size();
	}
}