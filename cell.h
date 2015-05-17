/*
 * square.h
 *
 *  Created on: May 11, 2015
 *      Author: Arun
 */

#ifndef CELL_H_
#define CELL_H_

#include <algorithm>
#include <vector>

namespace Phoenix {

class Cell {
public:
	Cell();

	const int number() const;
	int& number();

	const std::vector<int>& probabilities() const;
	std::vector<int>& probabilities();

	void removeFromProbabilities(const int number);

private:
	int d_number;
	std::vector<int> d_probabilities;
};

inline Cell::Cell()
: d_number(0)
{}

inline const int Cell::number() const
{
	return d_number;
}

inline int& Cell::number()
{
	return d_number;
}

inline 	const std::vector<int>& Cell::probabilities() const
{
	return d_probabilities;
}

inline std::vector<int>& Cell::probabilities()
{
	return d_probabilities;
}

inline void Cell::removeFromProbabilities(const int number)
{
	d_probabilities.erase(std::remove(d_probabilities.begin(),
			                          d_probabilities.end(),
									  number),
			              d_probabilities.end());
}

}  // namespace Phoenix
#endif /* CELL_H_ */
