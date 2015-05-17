/*
 * sudoku.h
 *
 *  Created on: May 11, 2015
 *      Author: Arun
 */

#ifndef SUDOKU_H_
#define SUDOKU_H_

#include <cell.h>

#include <string>
#include <vector>

namespace Phoenix {

class Sudoku {
public:

	/// @brief Construct from a 81 character
	///        string
	Sudoku(std::string input);

private:
	std::vector<std::vector<Cell> > d_matrix;
};

}  // namespace Phoenix



#endif /* SUDOKU_H_ */
