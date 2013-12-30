//
//  Random.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/12/05.
//
//

#ifndef coconut_Random_h
#define coconut_Random_h

#define USE_RANDOM_DEVICE							0

#include <random>
#include <vector>

namespace coconut {
	
	class Random {
	private:
		
#if USE_RANDOM_DEVICE
		static std::random_device rd;
#endif
		
		Random();

	public:
		
		static std::mt19937 mt;
	
		template<class T>
		T select(int size, const T values[]) {
			int r = mt() % size;
			return values[r];
		}

		int selectOfRange(int start, int end, int step = 1) {
			int num = (end - start) / step + 1;
			int r = mt() % num;
			return start + r * step;
		}
		
	};
	
	template <class T>
	class TRandomInt {
	private:
		std::uniform_int_distribution<T> dist;
	public:
		TRandomInt(T start, T end) : dist(start, end) {
		}
		T operator()() {
			return dist(Random::mt);
		}
	};
	typedef TRandomInt<int> RandomInt;
	typedef TRandomInt<char> RandomChar;
	
	template <class T>
	class TRandomReal {
	private:
		std::uniform_real_distribution<T> dist;
	public:
		TRandomReal(T start, T end) : dist(start, end) {
		}
		T operator()() {
			return dist(Random::mt);
		}
	};
	typedef TRandomReal<float> RandomFloat;
	typedef TRandomReal<double> RandomDouble;
	
	template <class T>
	class TNormalDist {
	private:
		std::normal_distribution<T> dist;
	public:
		TNormalDist(T mean, T stddev) : dist(mean, stddev) {
		}
		T operator()() {
			return dist(Random::mt);
		}
	};
	typedef TNormalDist<float> NormalDistFloat;
	typedef TNormalDist<double> NormalDistDouble;
	
	template <class T>
	class RandomSelector {
	private:
		std::vector<T> arr;
		std::uniform_int_distribution<int> dist;
	public:
		RandomSelector(int size, const T src[]) : dist(0, size-1) {
			for (int i = 0; i < size; i++) {
				arr.push_back(src[i]);
			}
		}
		RandomSelector(const std::vector<T>& arr) : arr(arr), dist(0, arr.size()-1) {
		}
		T operator()() {
			return arr[dist(Random::mt)];
		}
	};
}

#endif
