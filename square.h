/*
 * square.h
 *
 *  Created on: May 11, 2015
 *      Author: Arun
 */

#ifndef SQUARE_H_
#define SQUARE_H_

#include <vector>

namespace Phoenix {

class Square
{
public:
	int number();
  int no;
  std::vector<int> prob;
  Square(){no = 0;}
};


inline Square::number()
{
	return no;
}


}  // namespace Phoenix



#endif /* SQUARE_H_ */
