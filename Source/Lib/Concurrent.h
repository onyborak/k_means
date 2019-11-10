//
// Created by Xiaomi on 10.11.2019.
//

#ifndef CLUSTERING_CONCURRENT_H
#define CLUSTERING_CONCURRENT_H

#include <vector>
#include <functional>
#include <thread>
#include <iostream>

class Concurrent
{
public:
	template <class T>
	using ExecuteFunct = std::function<void(T &)>;

	template <class T>
	static void Execute(std::vector<T> &data, const ExecuteFunct<T> &funct);

private:

};

template<class T>
void Concurrent::Execute(std::vector<T> &data, const Concurrent::ExecuteFunct<T> &funct) {
	if (data.empty()) {
		return;
	}

	std::vector<std::thread> ExecThreads;
	size_t nThreadsCount = std::thread::hardware_concurrency();
	if (nThreadsCount == 0) {
		nThreadsCount = 1;
	}
	if (nThreadsCount > data.size()) {
		nThreadsCount = data.size();
	}
	ExecThreads.reserve(nThreadsCount);

	auto nHandledIndexesPerThread = data.size() / nThreadsCount;
	for (size_t i = 0; i < nThreadsCount; ++i) {
		auto nFirstIndex = i * nHandledIndexesPerThread;
		auto nLastIndex = ((i + 1) == nThreadsCount ? data.size()
													: (i + 1) * nHandledIndexesPerThread) - 1;
		ExecThreads.emplace_back([nFirstIndex, nLastIndex, &data, &funct](){
			for (size_t i = nFirstIndex; i <= nLastIndex; ++i) {
				funct(data[i]);
			}
		});
	}

	for (auto &Thread : ExecThreads) {
		Thread.join();
	}
}


#endif //CLUSTERING_CONCURRENT_H
