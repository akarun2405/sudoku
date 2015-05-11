/*
 * square.h
 *
 *  Created on: May 11, 2015
 *      Author: Arun
 */

#ifndef SQUARE_H_
#define SQUARE_H_

#include <algorithm>
#include <vector>

namespace Phoenix {

class Square
{
public:
	Square();

	const int number() const;
	int& number();

	const std::vector<int>& probabilities() const;
	std::vector<int>& probabilities();

	void removeFromProbabilities(const int number);

private:
	int d_number;
	std::vector<int> d_probabilities;
};

inline Square::Square()
: d_number(0)
{}

inline const int Square::number() const
{
	return d_number;
}

inline int& Square::number()
{
	return d_number;
}

inline 	const std::vector<int>& Square::probabilities() const
{
	return d_probabilities;
}

inline std::vector<int>& Square::probabilities()
{
	return d_probabilities;
}

inline void Square::removeFromProbabilities(const int number)
{
	d_probabilities.erase(std::remove(d_probabilities.begin(),
			                          d_probabilities.end(),
									  number),
			              d_probabilities.end());
}

}  // namespace Phoenix
#endif /* SQUARE_H_ */
