#pragma once
#include <vector>
//Class holding algorithm methods.
class AlgorithmHelper
{
public:
	AlgorithmHelper();
	~AlgorithmHelper();

	//Tells if a vector contains the specified object.
	template<typename T> static bool VectorContains(std::vector<T> heystack, T needle);
	//Joins two vectors.
	template<typename T> static std::vector<T> JoinVectors(const std::vector<T> vectorA, const std::vector<T> vectorB);
	//Appends a vector to another.
	template<typename T> static void AppendVector(std::vector<T>& mainVector, const std::vector<T> toAppend);
};

template<typename T>
inline bool AlgorithmHelper::VectorContains(std::vector<T> heystack, T needle)
{
	return find(heystack.begin(), heystack.end(), needle) != heystack.end();
}

template<typename T>
inline std::vector<T> AlgorithmHelper::JoinVectors(const std::vector<T> vectorA, const std::vector<T> vectorB)
{
	//Implemented as suggested at:
	//https://stackoverflow.com/a/3177252/1997617

	std::vector<T> joinedVector;

	joinedVector.reserve(vectorA.size() + vectorB.size());
	joinedVector.insert(joinedVector.end(), vectorA.begin(), vectorA.end());
	joinedVector.insert(joinedVector.end(), vectorB.begin(), vectorB.end());

	return joinedVector;
}

template<typename T>
inline void AlgorithmHelper::AppendVector(std::vector<T>& mainVector, const std::vector<T> toAppend)
{
	mainVector.insert(mainVector.end(), toAppend.begin(), toAppend.end());
}
